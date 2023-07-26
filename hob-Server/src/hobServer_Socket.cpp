/******************************************************************************************************
 * @file hobServer_Socket.cpp                                                                         *
 * @date:      @author:                   Reason for change:                                          *
 * 26.07.2023  Gaina Stefan               Initial version.                                            *
 * @details This file implements the class defined in hobServer_Socket.hpp.                           *
 * @todo N/A.                                                                                         *
 * @bug No known bugs.                                                                                *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <exception>
#include <WS2tcpip.h>
#include <plog.h>

#include "hobServer_Socket.hpp"
#include "hobServer_Common.hpp"
#include "hob_Version.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hobServer
{

Socket::Socket(void) noexcept
	: m_serverSocket        { INVALID_SOCKET }
	, m_clientSockets       { INVALID_SOCKET, INVALID_SOCKET }
	, m_waitConnectionThread{}
{
	plog_debug(LOG_PREFIX "Socket is being constructed.");
}

Socket::~Socket(void) noexcept
{
	plog_debug(LOG_PREFIX "Socket is being destructed.");
	close();
}

void Socket::create(uint16_t port, Callback callback) noexcept(false)
{
	static constexpr const u_long BLOCKING = 0U;

	sockaddr_in server     = {};
	int32_t     errorCode  = ERROR_SUCCESS;
	u_long      socketMode = BLOCKING;

	plog_debug(LOG_PREFIX "Server socket is being created.");
	if (INVALID_SOCKET != m_serverSocket || INVALID_SOCKET != m_clientSockets[0] || INVALID_SOCKET != m_clientSockets[1])
	{
		plog_error(LOG_PREFIX "Socket is already created!");
		throw std::exception();
	}

	m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == m_serverSocket)
	{
		plog_error(LOG_PREFIX "Server socket failed to be created! (error code: %" PRId32 ")", WSAGetLastError());
		throw std::exception();
	}

	errorCode = ioctlsocket(m_serverSocket, FIONBIO, &socketMode);
	if (ERROR_SUCCESS != errorCode)
	{
		plog_error(LOG_PREFIX "Failed to set socket to blocking mode! error code: %" PRId32 ")", errorCode);
		goto CLEAN_SOCKET;
	}

	server.sin_family      = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port        = htons(port);

	errorCode = ::bind(m_serverSocket, reinterpret_cast<sockaddr*>(&server), sizeof(server));
	if (SOCKET_ERROR == errorCode)
	{
		plog_error(LOG_PREFIX "Socket failed to be binded! (error code: %" PRId32 ")", WSAGetLastError());
		goto CLEAN_SOCKET;
	}

	if (nullptr == callback)
	{
		plog_warn(LOG_PREFIX "Callback is invalid, function is blocking!");
		waitConnectionFunction(nullptr);
		return;
	}

	if (true == m_waitConnectionThread.joinable())
	{
		plog_debug(LOG_PREFIX "Wait connection thread is being joined.");
		m_waitConnectionThread.join();
		plog_debug(LOG_PREFIX "Wait connection thread has joined.");
	}
	m_waitConnectionThread = std::thread{ std::bind(&Socket::waitConnectionFunction, this, callback) };

	return;

CLEAN_SOCKET:

	close();

	throw std::exception();
}

void Socket::close(void) noexcept
{
	int32_t errorCode = ERROR_SUCCESS;

	plog_trace(LOG_PREFIX "Server socket is being closed.");
	if (INVALID_SOCKET != m_serverSocket)
	{
		errorCode = closesocket(m_serverSocket);
		if (ERROR_SUCCESS != errorCode)
		{
			plog_error(LOG_PREFIX "Server socket failed to be closed! (error code: %" PRId32 ")", errorCode);
		}
		m_serverSocket = INVALID_SOCKET;
	}
	else
	{
		plog_warn(LOG_PREFIX "Server socket is already closed!");
	}

	closeClient(ClientType::PLAYER_1);
	closeClient(ClientType::PLAYER_2);

	if (true == m_waitConnectionThread.joinable())
	{
		plog_debug(LOG_PREFIX "Wait connection thread is being joined.");
		m_waitConnectionThread.join();
		plog_debug(LOG_PREFIX "Wait connection thread has joined.");
	}
}

void Socket::receiveUpdate(Message& updateMessage, ClientType clientType) const noexcept
{
	int32_t receivedBytes = 0L;
	size_t  index         = 0ULL;

	plog_verbose(LOG_PREFIX "Querrying for updates.");
	switch (clientType)
	{
		case ClientType::PLAYER_1:
		{
			index = 0ULL;
			break;
		}
		case ClientType::PLAYER_2:
		{
			index = 1ULL;
			break;
		}
		default:
		{
			plog_error(LOG_PREFIX "Invalid client type! (%" PRId32 ")", static_cast<int32_t>(clientType));
			break;
		}
	}

	if (INVALID_SOCKET == m_clientSockets[index])
	{
		plog_fatal(LOG_PREFIX "Connection is not established!");
		return;
	}
	plog_debug(LOG_PREFIX "Waiting for updates to arrive.");

	receivedBytes = recv(m_clientSockets[index], reinterpret_cast<char*>(&updateMessage), sizeof(Message), 0L);
	if (0L == receivedBytes)
	{
		plog_info(LOG_PREFIX "Connection was lost!");
		updateMessage.type = MessageType::END_COMMUNICATION;
	}
	else if (0L > receivedBytes)
	{
		plog_fatal(LOG_PREFIX "Invalid number of bytes received! (bytes: %" PRId32 ")", receivedBytes);
		updateMessage.type = MessageType::END_COMMUNICATION;
	}
	else
	{
		plog_debug(LOG_PREFIX "Received an updated! (bytes: %" PRId32 ")", receivedBytes);
	}
}

void Socket::sendUpdate(const Message& updateMessage, ClientType clientType) const noexcept
{
	size_t index = 0ULL;

	plog_trace(LOG_PREFIX "Update is being sent.");
	switch (clientType)
	{
		case ClientType::PLAYER_1:
		{
			index = 0ULL;
			break;
		}
		case ClientType::PLAYER_2:
		{
			index = 1ULL;
			break;
		}
		default:
		{
			plog_error(LOG_PREFIX "Invalid client type! (%" PRId32 ")", static_cast<int32_t>(clientType));
			break;
		}
	}

	if (INVALID_SOCKET == m_clientSockets[index])
	{
		plog_fatal(LOG_PREFIX "Connection is not established!");
		return;
	}
	send(m_clientSockets[index], reinterpret_cast<const char*>(&updateMessage), sizeof(Message), 0L);
}

void Socket::waitConnectionFunction(Callback callback) noexcept
{
	int32_t     errorCode      = ERROR_SUCCESS;
	size_t      index          = 0ULL;
	ClientType  clientTypes[2] = { ClientType::PLAYER_1, ClientType::PLAYER_2 };
	sockaddr_in client         = {};
	int32_t     addressLength  = sizeof(client);
	Message     versionMessage = {};

	plog_info(LOG_PREFIX "Waiting for incoming connections!");

	errorCode = listen(m_serverSocket, 2L);
	if (ERROR_SUCCESS != errorCode)
	{
		plog_fatal(LOG_PREFIX "Server failed to open for connections! (error code: %" PRId32 ")", errorCode);
		return;
	}

WAIT_FOR_CONNECTION:

	m_clientSockets[index] = accept(m_serverSocket, reinterpret_cast<sockaddr*>(&client), &addressLength);
	if (INVALID_SOCKET == m_serverSocket)
	{
		plog_warn(LOG_PREFIX "Server socket was closed!");
		if (1ULL == index)
		{
			closeClient(clientTypes[index]);
		}
		return;
	}

	if (INVALID_SOCKET == m_clientSockets[index])
	{
		plog_error(LOG_PREFIX "Connection failed to be accepted! (WSA error code: %" PRId32 ")", WSAGetLastError());
		goto WAIT_FOR_CONNECTION;
	}
	plog_info(LOG_PREFIX "Connection accepted successfully!");

	receiveUpdate(versionMessage, clientTypes[index]);
	if (MessageType::VERSION != versionMessage.type)
	{
		plog_error(LOG_PREFIX "First message received is not checking to match versions! (message type: %" PRId32 ")", static_cast<int32_t>(versionMessage.type));
		goto ABORT_CONNECTION;
	}

	plog_info(LOG_PREFIX "Version message received! (version: %" PRIu8 ".%" PRIu8 ".%" PRIu8 ")", versionMessage.payload.version.major,
		versionMessage.payload.version.minor, versionMessage.payload.version.patch);
	if (hob::VERSION_MAJOR != versionMessage.payload.version.major
	 || hob::VERSION_MINOR != versionMessage.payload.version.minor
	 || hob::VERSION_PATCH != versionMessage.payload.version.patch)
	{
		plog_error(LOG_PREFIX "Versions are not matching!");
		goto ABORT_CONNECTION;
	}

	if (0ULL == index)
	{
		++index;
		goto WAIT_FOR_CONNECTION;
	}

	if (nullptr != callback)
	{
		(*callback)();
	}
	return;

ABORT_CONNECTION:

	versionMessage.type = MessageType::END_COMMUNICATION;
	sendUpdate(versionMessage, clientTypes[index]);

	closeClient(clientTypes[index]);

	goto WAIT_FOR_CONNECTION;
}

void Socket::closeClient(ClientType clientType) noexcept
{
	size_t  index     = 0ULL;
	int32_t errorCode = ERROR_SUCCESS;

	plog_debug(LOG_PREFIX  "Client socket is being closed. (client type: %" PRId32 ")", static_cast<int32_t>(clientType));
	switch (clientType)
	{
		case ClientType::PLAYER_1:
		{
			index = 0ULL;
			break;
		}
		case ClientType::PLAYER_2:
		{
			index = 1ULL;
			break;
		}
		default:
		{
			plog_error(LOG_PREFIX "Invalid client type! (%" PRId32 ")", static_cast<int32_t>(clientType));
			break;
		}
	}

	if (INVALID_SOCKET != m_clientSockets[index])
	{
		errorCode = closesocket(m_clientSockets[index]);
		if (ERROR_SUCCESS != errorCode)
		{
			plog_error(LOG_PREFIX "Client socket %" PRIu64 " socket failed to be closed! (error code: %" PRId32 ")", index, errorCode);
		}
		m_clientSockets[index] = INVALID_SOCKET;
	}
	else
	{
		plog_warn(LOG_PREFIX "Client socket %" PRIu64 " is already closed!", index);
	}
}

} /*< namespace hobServer */
