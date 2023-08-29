/******************************************************************************************************
 * @file hob_Loop.cpp                                                                                 *
 * @date:      @author:                   Reason for change:                                          *
 * 23.07.2023  Gaina Stefan               Initial version.                                            *
 * 24.07.2023  Gaina Stefan               Move frames per second in render.                           *
 * 26.08.2023  Gaina Stefan               Improved logs.                                              *
 * 29.08.2023  Gaina Stefan               Made m_isRunning atomic.                                    *
 * @details This file implements the class defined in hob_Loop.hpp.                                   *
 * @todo N/A.                                                                                         *
 * @bug The execution is blocked when the window is being moved. This is a SDL limitation on Windows. *
 *****************************************************************************************************/

/******************************************************************************************************
 * HEADER FILE INCLUDES                                                                               *
 *****************************************************************************************************/

#include <exception>
#include <plog.h>

#include "hob_Loop.hpp"
#include "hob_Renderer.hpp"
#include "hob_Cursor.hpp"
#include "hob_FramesPerSecond.hpp"

/******************************************************************************************************
 * METHOD DEFINITIONS                                                                                 *
 *****************************************************************************************************/

namespace hob
{

Ping Loop::s_ping = {};

Loop::Loop(void) noexcept
	: m_nextScene{ Scene::QUIT }
	, m_isRunning{ false }
{
	SDL_Event event     = {};
	int32_t   errorCode = 0L;

	plog_trace("Loop is being constructed. (size: %" PRIu64 ") (1: %" PRIu64 ") (2: %" PRIu64 ")", sizeof(*this), sizeof(m_nextScene), sizeof(m_isRunning));
	event.type = SDL_MOUSEMOTION;

	errorCode = SDL_PushEvent(&event);
	if (1L != errorCode)
	{
		plog_warn("Failed to push mouse motion event! (error code: %" PRId32 ") (SDL error message: %s)", errorCode, SDL_GetError());
	}
}

Scene Loop::start(void) noexcept
{
	uint8_t failedRenderCount = 0U;

	plog_debug("Loop is being started.");
	if (true == m_isRunning.load())
	{
		plog_warn("Loop is already started!");
		return Scene::QUIT;
	}

	m_isRunning.store(true);
	while (true == m_isRunning.load())
	{
		handleEvents();

SKIP_HANDLE_EVENTS:

		try
		{
			render();
		}
		catch (...)
		{
			plog_fatal("Render failed, not handling events until graphics synchronize!");

			++failedRenderCount;
			if (UINT8_MAX == failedRenderCount)
			{
				plog_fatal("Maximum retry attempts reached! (failed count: %" PRIu16 ")", static_cast<uint16_t>(failedRenderCount));
				return Scene::QUIT;
			}

			goto SKIP_HANDLE_EVENTS;
		}
		failedRenderCount = 0U;
	}

	return m_nextScene;
}

void Loop::stop(const Scene nextScene) noexcept
{
	plog_debug("Loop is being stopped.");
	if (false == m_isRunning.load())
	{
		plog_warn("Loop is already stopped!");
		return;
	}
	m_nextScene = nextScene;
	m_isRunning.store(false);
}

void Loop::pingReceived(void) const noexcept
{
	plog_verbose("Ping has been received.");
	s_ping.update();
}

void Loop::pingStop(void) const noexcept
{
	plog_verbose("Ping is being stopped.");
	s_ping.clean();
}

void Loop::handleEvents(void) noexcept
{
	SDL_Event event = {};

	plog_verbose("Events are being handled.");
	while (1L == SDL_PollEvent(&event))
	{
		plog_verbose("Event received.");
		handleEvent(event);
	}
}

void Loop::render(void) noexcept(false)
{
	static FramesPerSecond framesPerSecond = {};

	int32_t errorCode = 0L;

	plog_verbose("Scene is being rendered.");

	errorCode = SDL_RenderClear(Renderer::getInstance().get());
	if (0L != errorCode)
	{
		plog_error("Renderer failed to be cleared! (error code: %" PRId32 ") (error message: %s)", errorCode, SDL_GetError());
		throw std::exception();
	}

	draw();
	Cursor::getInstance().draw();
	framesPerSecond.draw();
	s_ping.draw();

	SDL_RenderPresent(Renderer::getInstance().get());
}

} /*< namespace hob */
