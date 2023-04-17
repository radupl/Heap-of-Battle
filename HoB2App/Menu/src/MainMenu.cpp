/** @file MainMenu.cpp
 *  @brief Method implementation for the main menu.
 *
 *  @author Gaina Stefan
 *  @bug No known bugs.
 */

/***********************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                *
 **********************************************************************************************************************/

#include <plog.h>

#include "MainMenu.hpp"
#include "MenuCommon.h"
#include "Cursor.hpp"
#include "Music.hpp"

namespace Menu
{

/***********************************************************************************************************************
 * LOCAL VARIABLES                                                                                                     *
 **********************************************************************************************************************/

static std::array<std::string, MAIN_MENU_TEXTURES_COUNT> s_textureFilePaths =
{
	MENU_TEXTURE_PATH_BACKGROUND                   ,
	"assets/textures/main_menu/logo.png"           ,
	"assets/textures/main_menu/heap_text.png"      ,
	"assets/textures/main_menu/of_text.png"        ,
	"assets/textures/main_menu/battle_text.png"    ,
	"assets/textures/main_menu/2_text.png"         ,
	MENU_TEXTURE_PATH_BUTTON_IDLE                  ,
	MENU_TEXTURE_PATH_BUTTON_ACTIVE                ,
	MENU_TEXTURE_PATH_BUTTON_PRESSED               ,
	"assets/textures/main_menu/start_game_text.png",
	"assets/textures/main_menu/settings_text.png"  ,
	"assets/textures/main_menu/exit_text.png"
};

static std::array<size_t, MAIN_MENU_COMPONENTS_COUNT> s_textureIndexes =
{
	MAIN_MENU_TEXTURE_INDEX_BACKGROUND     ,
	MAIN_MENU_TEXTURE_INDEX_LOGO           ,
	MAIN_MENU_TEXTURE_INDEX_HEAP_TEXT      ,
	MAIN_MENU_TEXTURE_INDEX_OF_TEXT        ,
	MAIN_MENU_TEXTURE_INDEX_BATTLE_TEXT    ,
	MAIN_MENU_TEXTURE_INDEX_2_TEXT         ,
	MAIN_MENU_TEXTURE_INDEX_BUTTON_IDLE    ,
	MAIN_MENU_TEXTURE_INDEX_BUTTON_IDLE    ,
	MAIN_MENU_TEXTURE_INDEX_BUTTON_IDLE    ,
	MAIN_MENU_TEXTURE_INDEX_START_GAME_TEXT,
	MAIN_MENU_TEXTURE_INDEX_SETTINGS_TEXT  ,
	MAIN_MENU_TEXTURE_INDEX_EXIT_TEXT
};

static std::array<SDL_Rect, MAIN_MENU_COMPONENTS_COUNT> s_destinations =
{
	{
		{ 0L                                          , 0L                                       , SCREEN_WIDTH       , SCREEN_HEIGHT      },
		{ 4L * SCALE                                  , 0L                                       , 2L * BAR_WIDTH     , 2L * BAR_HEIGHT    },
		{ 4L * SCALE + SCALE / 2L + SCALE / 4L        , SCALE + SCALE / 2L                       , 3L * SCALE         , SCALE + SCALE / 2L },
		{ 7L * SCALE + SCALE / 2L                     , 2L * SCALE                               , SCALE              , SCALE + SCALE / 2L },
		{ 8L * SCALE + SCALE / 3L                     , SCALE + SCALE / 2L                       , 3L * SCALE         , SCALE + SCALE / 2L },
		{ 7L * SCALE + SCALE / 2L - 2L                , SCALE / 2L - 8L                          , SCALE              , SCALE + SCALE / 2L },
		{ BAR_HORIZONTAL_CENTERED                     , 3L * SCALE + SCALE / 2L                  , BAR_WIDTH          , BAR_HEIGHT         },
		{ BAR_HORIZONTAL_CENTERED                     , 3L * SCALE + SCALE / 2L + 4L * SCALE / 3L, BAR_WIDTH          , BAR_HEIGHT         },
		{ BAR_HORIZONTAL_CENTERED                     , 3L * SCALE + SCALE / 2L + 8L * SCALE / 3L, BAR_WIDTH          , BAR_HEIGHT         },
		{ BAR_HORIZONTAL_CENTERED + SCALE             , 4L * SCALE + SCALE / 4L                  , BAR_TEXT_WIDTH     , BAR_TEXT_HEIGHT    },
		{ BAR_HORIZONTAL_CENTERED + SCALE             , 4L * SCALE + SCALE / 4L + 4L * SCALE / 3L, BAR_TEXT_WIDTH     , BAR_TEXT_HEIGHT    },
		{ BAR_HORIZONTAL_CENTERED + SCALE + SCALE / 2L, 6L * SCALE + 2L * SCALE / 3L + SCALE / 4L, BAR_TEXT_WIDTH / 2L, BAR_TEXT_HEIGHT    }
	}
};

static std::array<std::string, MAIN_MENU_SOUNDS_COUNT> s_soundFilePaths =
{
	MENU_SOUND_PATH_CLICK
};

/***********************************************************************************************************************
 * METHOD DEFINITIONS                                                                                                  *
 **********************************************************************************************************************/

MainMenu::MainMenu(void) noexcept
	: Loop              {}
	, TextureInitializer{ s_textureFilePaths, s_textureIndexes, s_destinations }
	, SoundInitializer  { s_soundFilePaths }
	, m_clickDownIndex  { 0ULL }
{
	Utility::Cursor& cursor = Utility::Cursor::getInstance();

	plog_trace("Main menu is being constructed.");
	Utility::Music::getInstance().start(Utility::Song::MAIN_MENU);
	cursor.setFaction(true);
	cursor.setTexture(Utility::CursorType::IDLE);
}

MainMenu::~MainMenu(void) noexcept
{
	plog_trace("Main menu is being deconstructed.");
}

void MainMenu::draw(void) noexcept
{
	plog_verbose("Main menu is being drawn.");
	TextureInitializer::draw();
}

void MainMenu::handleEvent(const SDL_Event& event) noexcept
{
	Coordinate click      = {};
	uint32_t   mouseState = 0UL;
	size_t     index      = 0ULL;

	plog_verbose("Event is being handled.");
	switch (event.type)
	{
		case SDL_MOUSEBUTTONDOWN:
		{
			mouseState = SDL_GetMouseState(&click.x, &click.y);
			plog_trace("Mouse (%" PRIu32 ") was clicked. (coordinates: %" PRId32 ", %" PRId32 ")", mouseState, click.x, click.y);

			if (LEFT_CLICK != SDL_BUTTON(mouseState))
			{
				plog_trace("Mouse click is not left click.");
				return;
			}

			for (index = MAIN_MENU_COMPONENT_INDEX_BUTTON_START_GAME; index <= MAIN_MENU_COMPONENT_INDEX_BUTTON_EXIT; ++index)
			{
				if (m_componentContainer[index].isMouseInside(click, bar_corrections))
				{
					plog_verbose("Bar is pressed. (index: %" PRIu64 ")", index);
					m_componentContainer[index].updateTexture(m_textureContainer[MAIN_MENU_TEXTURE_INDEX_BUTTON_PRESSED].getRawTexture());
					m_soundContainer[MAIN_MENU_SOUND_INDEX_CLICK].play();
					m_clickDownIndex = index;
					return;
				}
				m_componentContainer[index].updateTexture(m_textureContainer[MAIN_MENU_TEXTURE_INDEX_BUTTON_IDLE].getRawTexture());
			}
			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			mouseState = SDL_GetMouseState(&click.x, &click.y);
			plog_trace("Mouse (%" PRIu32 ") was released. (coordinates: %" PRId32 ", %" PRId32 ")", mouseState, click.x, click.y);

			if (0ULL != m_clickDownIndex && m_componentContainer[m_clickDownIndex].isMouseInside(click, bar_corrections))
			{
				switch (m_clickDownIndex)
				{
					case MAIN_MENU_COMPONENT_INDEX_BUTTON_START_GAME:
					{
						plog_debug("Start game bar was selected, clicked and released.");
						stopLoop(Scene::MULTIPLAYER);
						break;
					}
					case MAIN_MENU_COMPONENT_INDEX_BUTTON_SETTINGS:
					{
						plog_debug("Settings bar was selected, clicked and released.");
						stopLoop(Scene::SETTINGS);
						break;
					}
					case MAIN_MENU_COMPONENT_INDEX_BUTTON_EXIT:
					{
						plog_debug("Exit bar was selected, clicked and released.");
						stopLoop(Scene::QUIT);
						break;
					}
				}
			}
			m_clickDownIndex = 0ULL;
			//break; <- commented so buttons get reselected appropriately.
		}
		case SDL_MOUSEMOTION:
		{
			mouseState = SDL_GetMouseState(&click.x, &click.y);
			plog_verbose("Mouse (%" PRIu32 ") was moved. (coordinates: %" PRId32 ", %" PRId32 ")", mouseState, click.x, click.y);

			Utility::Cursor::getInstance().updatePosition(click);

			if (LEFT_CLICK == SDL_BUTTON(mouseState))
			{
				plog_verbose("Mouse left click is pressed.");
				return;
			}

			for (index = MAIN_MENU_COMPONENT_INDEX_BUTTON_START_GAME; index <= MAIN_MENU_COMPONENT_INDEX_BUTTON_EXIT; ++index)
			{
				if (m_componentContainer[index].isMouseInside(click, bar_corrections))
				{
					plog_verbose("Bar is selected. (index: %" PRIu64 ")", index);
					m_componentContainer[index].updateTexture(m_textureContainer[MAIN_MENU_TEXTURE_INDEX_BUTTON_ACTIVE].getRawTexture());
					return;
				}
				m_componentContainer[index].updateTexture(m_textureContainer[MAIN_MENU_TEXTURE_INDEX_BUTTON_IDLE].getRawTexture());
			}
			break;
		}
		case SDL_QUIT:
		{
			plog_info("Command to quit game was given!");
			stopLoop(Scene::QUIT);
			break;
		}
		default:
		{
			plog_verbose("Event received but not handled.");
			break;
		}
	}
}

} /*< namespace Menu */
