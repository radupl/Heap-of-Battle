/** @file Menu.cpp
 *  @brief Method implementation for the game menu.
 *
 *  @author Gaina Stefan
 *  @bug No known bugs.
 */

/***********************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                *
 **********************************************************************************************************************/

#include <plog.h>

#include "Menu.hpp"
#include "Faction.hpp"

namespace Game
{

/****************************************************************************************************************************************
 * MACROS                                                                                                                               *
 ***************************************************************************************************************************************/

/**
 * @brief Full file path of an image of a building.
*/
#define TEXTURE_FILE_PATH(name) "assets/textures/game_menu/" name ".png"

/**
 * @brief Relative path to the game menu's alliance background texture.
*/
static constexpr const char* MENU_TEXTURE_PATH_ALLIANCE_STONE = "assets/textures/game_menu/alliance_stone.png";

/**
 * @brief Relative path to the game menu's alliance background variation texture.
*/
static constexpr const char* MENU_TEXTURE_PATH_ALLIANCE_STONE_VAR = "assets/textures/game_menu/alliance_stone_1.png";

/**
 * @brief Relative path to the game menu's horde background texture.
*/
static constexpr const char* MENU_TEXTURE_PATH_HORDE_STONE = "assets/textures/game_menu/horde_stone.png";

/**
 * @brief Relative path to the game menu's horde background variation texture.
*/
static constexpr const char* MENU_TEXTURE_PATH_HORDE_STONE_VAR = "assets/textures/game_menu/horde_stone_1.png";

/***********************************************************************************************************************
 * LOCAL VARIABLES                                                                                                     *
 **********************************************************************************************************************/

static std::array<std::string, MENU_TEXTURES_COUNT> textureFilePaths =
{
	MENU_TEXTURE_PATH_ALLIANCE_STONE,
	MENU_TEXTURE_PATH_ALLIANCE_STONE_VAR
};

static std::array<size_t, MENU_COMPONENTS_COUNT> textureIndexes =
{
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,

	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,

	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE_VAR,

	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,

	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,

	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,

	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,

	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,

	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,

	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,

	MENU_TEXTURE_INDEX_STONE,
	MENU_TEXTURE_INDEX_STONE,
	MENU_TEXTURE_INDEX_STONE,
	MENU_TEXTURE_INDEX_STONE,
	MENU_TEXTURE_INDEX_STONE,
	MENU_TEXTURE_INDEX_STONE,

	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,

	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,

	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,

	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,

	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,

	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,

	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE_VAR,

	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,

	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,

	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,

	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,

	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,



	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,

	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE_VAR,

	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,

	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,

	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,

	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,

	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,

	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,

	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,

	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,

	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,

	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,

	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE_VAR,

	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
	MENU_TEXTURE_INDEX_STONE_VAR,
	MENU_TEXTURE_INDEX_STONE    ,
};

static std::array<SDL_Rect, MENU_COMPONENTS_COUNT> destinations =
{
	{
		{ 0L                     , 0L, SCALE / 2L, SCALE / 2L },
		{ SCALE /2L              , 0L, SCALE / 2L, SCALE / 2L },
		{ SCALE                  , 0L, SCALE / 2L, SCALE / 2L },
		{ SCALE + SCALE / 2L     , 0L, SCALE / 2L, SCALE / 2L },
		{ 2L * SCALE             , 0L, SCALE / 2L, SCALE / 2L },
		{ 2L * SCALE + SCALE / 2L, 0L, SCALE / 2L, SCALE / 2L },

		{ 0L                     , SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ SCALE /2L              , SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ SCALE                  , SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ SCALE + SCALE / 2L     , SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ 2L * SCALE             , SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ 2L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L, SCALE / 2L },

		{ 0L                     , SCALE, SCALE / 2L, SCALE / 2L },
		{ SCALE /2L              , SCALE, SCALE / 2L, SCALE / 2L },
		{ SCALE                  , SCALE, SCALE / 2L, SCALE / 2L },
		{ SCALE + SCALE / 2L     , SCALE, SCALE / 2L, SCALE / 2L },
		{ 2L * SCALE             , SCALE, SCALE / 2L, SCALE / 2L },
		{ 2L * SCALE + SCALE / 2L, SCALE, SCALE / 2L, SCALE / 2L },

		{ 0L                     , SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ SCALE /2L              , SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ SCALE                  , SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ SCALE + SCALE / 2L     , SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ 2L * SCALE             , SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ 2L * SCALE + SCALE / 2L, SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },

		{ 0L                     , 2L * SCALE, SCALE / 2L, SCALE / 2L },
		{ SCALE /2L              , 2L * SCALE, SCALE / 2L, SCALE / 2L },
		{ SCALE                  , 2L * SCALE, SCALE / 2L, SCALE / 2L },
		{ SCALE + SCALE / 2L     , 2L * SCALE, SCALE / 2L, SCALE / 2L },
		{ 2L * SCALE             , 2L * SCALE, SCALE / 2L, SCALE / 2L },
		{ 2L * SCALE + SCALE / 2L, 2L * SCALE, SCALE / 2L, SCALE / 2L },

		{ 0L                     , 2L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ SCALE /2L              , 2L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ SCALE                  , 2L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ SCALE + SCALE / 2L     , 2L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ 2L * SCALE             , 2L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ 2L * SCALE + SCALE / 2L, 2L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },

		{ 0L                     , 3L * SCALE, SCALE / 2L, SCALE / 2L },
		{ SCALE /2L              , 3L * SCALE, SCALE / 2L, SCALE / 2L },
		{ SCALE                  , 3L * SCALE, SCALE / 2L, SCALE / 2L },
		{ SCALE + SCALE / 2L     , 3L * SCALE, SCALE / 2L, SCALE / 2L },
		{ 2L * SCALE             , 3L * SCALE, SCALE / 2L, SCALE / 2L },
		{ 2L * SCALE + SCALE / 2L, 3L * SCALE, SCALE / 2L, SCALE / 2L },

		{ 0L                     , 3L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ SCALE /2L              , 3L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ SCALE                  , 3L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ SCALE + SCALE / 2L     , 3L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ 2L * SCALE             , 3L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ 2L * SCALE + SCALE / 2L, 3L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },

		{ 0L                     , 4L * SCALE, SCALE / 2L, SCALE / 2L },
		{ SCALE /2L              , 4L * SCALE, SCALE / 2L, SCALE / 2L },
		{ SCALE                  , 4L * SCALE, SCALE / 2L, SCALE / 2L },
		{ SCALE + SCALE / 2L     , 4L * SCALE, SCALE / 2L, SCALE / 2L },
		{ 2L * SCALE             , 4L * SCALE, SCALE / 2L, SCALE / 2L },
		{ 2L * SCALE + SCALE / 2L, 4L * SCALE, SCALE / 2L, SCALE / 2L },

		{ 0L                     , 4L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ SCALE /2L              , 4L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ SCALE                  , 4L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ SCALE + SCALE / 2L     , 4L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ 2L * SCALE             , 4L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ 2L * SCALE + SCALE / 2L, 4L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },

		{ 0L                     , 5L * SCALE, SCALE / 2L, SCALE / 2L },
		{ SCALE /2L              , 5L * SCALE, SCALE / 2L, SCALE / 2L },
		{ SCALE                  , 5L * SCALE, SCALE / 2L, SCALE / 2L },
		{ SCALE + SCALE / 2L     , 5L * SCALE, SCALE / 2L, SCALE / 2L },
		{ 2L * SCALE             , 5L * SCALE, SCALE / 2L, SCALE / 2L },
		{ 2L * SCALE + SCALE / 2L, 5L * SCALE, SCALE / 2L, SCALE / 2L },

		{ 0L                     , 5L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ SCALE /2L              , 5L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ SCALE                  , 5L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ SCALE + SCALE / 2L     , 5L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ 2L * SCALE             , 5L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ 2L * SCALE + SCALE / 2L, 5L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },

		{ 0L                     , 6L * SCALE, SCALE / 2L, SCALE / 2L },
		{ SCALE /2L              , 6L * SCALE, SCALE / 2L, SCALE / 2L },
		{ SCALE                  , 6L * SCALE, SCALE / 2L, SCALE / 2L },
		{ SCALE + SCALE / 2L     , 6L * SCALE, SCALE / 2L, SCALE / 2L },
		{ 2L * SCALE             , 6L * SCALE, SCALE / 2L, SCALE / 2L },
		{ 2L * SCALE + SCALE / 2L, 6L * SCALE, SCALE / 2L, SCALE / 2L },

		{ 0L                     , 6L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ SCALE /2L              , 6L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ SCALE                  , 6L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ SCALE + SCALE / 2L     , 6L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ 2L * SCALE             , 6L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },
		{ 2L * SCALE + SCALE / 2L, 6L * SCALE + SCALE / 2L, SCALE / 2L, SCALE / 2L },

		{ 0L                     , 7L * SCALE, SCALE / 2L, SCALE / 2L },
		{ SCALE /2L              , 7L * SCALE, SCALE / 2L, SCALE / 2L },
		{ SCALE                  , 7L * SCALE, SCALE / 2L, SCALE / 2L },
		{ SCALE + SCALE / 2L     , 7L * SCALE, SCALE / 2L, SCALE / 2L },
		{ 2L * SCALE             , 7L * SCALE, SCALE / 2L, SCALE / 2L },
		{ 2L * SCALE + SCALE / 2L, 7L * SCALE, SCALE / 2L, SCALE / 2L },

		{ 0L                     , 15L * HSCALE, HSCALE, HSCALE },
		{ SCALE /2L              , 15L * HSCALE, HSCALE, HSCALE },
		{ SCALE                  , 15L * HSCALE, HSCALE, HSCALE },
		{ SCALE + SCALE / 2L     , 15L * HSCALE, HSCALE, HSCALE },
		{ 2L * SCALE             , 15L * HSCALE, HSCALE, HSCALE },
		{ 2L * SCALE + SCALE / 2L, 15L * HSCALE, HSCALE, HSCALE },

		{ 0L                     , 16L * HSCALE, HSCALE, HSCALE },
		{ SCALE /2L              , 16L * HSCALE, HSCALE, HSCALE },
		{ SCALE                  , 16L * HSCALE, HSCALE, HSCALE },
		{ SCALE + SCALE / 2L     , 16L * HSCALE, HSCALE, HSCALE },
		{ 2L * SCALE             , 16L * HSCALE, HSCALE, HSCALE },
		{ 2L * SCALE + SCALE / 2L, 16L * HSCALE, HSCALE, HSCALE },

		{ 0L                     , 17L * HSCALE, HSCALE, HSCALE },
		{ SCALE /2L              , 17L * HSCALE, HSCALE, HSCALE },
		{ SCALE                  , 17L * HSCALE, HSCALE, HSCALE },
		{ SCALE + SCALE / 2L     , 17L * HSCALE, HSCALE, HSCALE },
		{ 2L * SCALE             , 17L * HSCALE, HSCALE, HSCALE },
		{ 2L * SCALE + SCALE / 2L, 17L * HSCALE, HSCALE, HSCALE },

		{ 6L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
		{ 6L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
		{ 6L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
		{ 7L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
		{ 7L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
		{ 7L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },

		{ 8L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
		{ 8L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
		{ 8L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
		{ 9L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
		{ 9L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
		{ 9L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },

		{ 10L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
		{ 10L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
		{ 10L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
		{ 11L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
		{ 11L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
		{ 11L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },

		{ 12L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
		{ 12L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
		{ 12L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
		{ 13L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
		{ 13L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
		{ 13L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },

		{ 14L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
		{ 14L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
		{ 14L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
		{ 15L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
		{ 15L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
		{ 15L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },

		{ 16L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
		{ 16L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
		{ 16L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
		{ 17L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
		{ 17L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
		{ 17L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },

		{ 18L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
		{ 18L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
		{ 18L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
		{ 19L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
		{ 19L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
		{ 19L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },

		{ 20L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
		{ 20L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
		{ 20L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
		{ 21L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
		{ 21L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
		{ 21L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },

		{ 22L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
		{ 22L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
		{ 22L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
		{ 23L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
		{ 23L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
		{ 23L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },

		{ 24L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
		{ 24L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
		{ 24L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
		{ 25L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
		{ 25L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
		{ 25L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },

		{ 26L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
		{ 26L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
		{ 26L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
		{ 27L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
		{ 27L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
		{ 27L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },

		{ 28L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
		{ 28L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
		{ 28L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
		{ 29L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
		{ 29L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
		{ 29L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },

		{ 30L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
		{ 30L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
		{ 30L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
		{ 31L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
		{ 31L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
		{ 31L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },

		{ 32L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
		{ 32L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
		{ 32L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
		{ 33L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
		{ 33L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
		{ 33L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },

		{ 34L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
		{ 34L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
		{ 34L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
		{ 35L * HSCALE, 15L * HSCALE, HSCALE, HSCALE },
		{ 35L * HSCALE, 16L * HSCALE, HSCALE, HSCALE },
		{ 35L * HSCALE, 17L * HSCALE, HSCALE, HSCALE },
	}
};

/***********************************************************************************************************************
 * METHOD DEFINITIONS                                                                                                  *
 **********************************************************************************************************************/

void Menu::setTextureType(bool isAlliance) noexcept
{
	plog_debug("Setting menu's texture type. (type: %" PRId32 ")", static_cast<int32_t>(isAlliance));
	if (true == isAlliance)
	{
		textureFilePaths[MENU_TEXTURE_INDEX_STONE    ] = MENU_TEXTURE_PATH_ALLIANCE_STONE;
		textureFilePaths[MENU_TEXTURE_INDEX_STONE_VAR] = MENU_TEXTURE_PATH_ALLIANCE_STONE_VAR;
		return;
	}
	textureFilePaths[MENU_TEXTURE_INDEX_STONE    ] = MENU_TEXTURE_PATH_HORDE_STONE;
	textureFilePaths[MENU_TEXTURE_INDEX_STONE_VAR] = MENU_TEXTURE_PATH_HORDE_STONE_VAR;
}

Menu::Menu(void) noexcept
	: TextureInitializer
	{
		{
			true == Faction::getFaction() ? TEXTURE_FILE_PATH("alliance_stone") : TEXTURE_FILE_PATH("horde_stone"),
			true == Faction::getFaction() ? TEXTURE_FILE_PATH("alliance_stone_1") : TEXTURE_FILE_PATH("horde_stone_1")
		},
		textureIndexes,
		destinations
	}
{
	plog_trace("Menu is being constructed.");
}

} /*< namespace Game */
