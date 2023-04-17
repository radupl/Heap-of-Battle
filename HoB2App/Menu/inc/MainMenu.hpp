/** @file MainMenu.hpp
 *  @brief Class definition and method prototypes of the main menu.
 *
 *  @author Gaina Stefan
 *  @bug No known bugs.
 */

#ifndef MAIN_MENU_HPP_
#define MAIN_MENU_HPP_

/***********************************************************************************************************************
 * HEADER FILE INCLUDES                                                                                                *
 **********************************************************************************************************************/

#include "Loop.hpp"
#include "TextureInitializer.hpp"
#include "SoundInitializer.hpp"

namespace Menu
{

/***********************************************************************************************************************
 * TYPE DEFINITIONS                                                                                                    *
 **********************************************************************************************************************/

/*
 * @brief Enumerates main menu's textures index.
 */
enum MainMenuTextureIndex
{
	MAIN_MENU_TEXTURE_INDEX_BACKGROUND      = 0,  /**< Index to the main menu's background texture.        */
	MAIN_MENU_TEXTURE_INDEX_LOGO            = 1,  /**< Index to the main menu's logo texture.              */
	MAIN_MENU_TEXTURE_INDEX_HEAP_TEXT       = 2,  /**< Index to the main menu's "HEAP" text texture.       */
	MAIN_MENU_TEXTURE_INDEX_OF_TEXT         = 3,  /**< Index to the main menu's "OF" text texture.         */
	MAIN_MENU_TEXTURE_INDEX_BATTLE_TEXT     = 4,  /**< Index to the main menu's "BATTLE" texture.          */
	MAIN_MENU_TEXTURE_INDEX_2_TEXT          = 5,  /**< Index to the main menu's "2" text texture.          */
	MAIN_MENU_TEXTURE_INDEX_BUTTON_IDLE     = 6,  /**< Index to the main menu's idle button texture.       */
	MAIN_MENU_TEXTURE_INDEX_BUTTON_ACTIVE   = 7,  /**< Index to the main menu's active button texture.     */
	MAIN_MENU_TEXTURE_INDEX_BUTTON_PRESSED  = 8,  /**< Index to the main menu's pressed button texture.    */
	MAIN_MENU_TEXTURE_INDEX_START_GAME_TEXT = 9,  /**< Index to the main menu's "START GAME" text texture. */
	MAIN_MENU_TEXTURE_INDEX_SETTINGS_TEXT   = 10, /**< Index to the main menu's "SETTINGS" text texture.   */
	MAIN_MENU_TEXTURE_INDEX_EXIT_TEXT       = 11, /**< Index to the main menu's "EXIT" text texture.       */
	MAIN_MENU_TEXTURES_COUNT                = 12  /**< How many textures main menu loads.                  */
};

/*
 * @brief Enumerates main menu's changeable components index.
 */
enum MainMenuComponentIndex
{
	MAIN_MENU_COMPONENT_INDEX_BUTTON_START_GAME = 6, /**< Index to the main menu's start game button component. */
	MAIN_MENU_COMPONENT_INDEX_BUTTON_SETTINGS   = 7, /**< Index to the main menu's settings button component.   */
	MAIN_MENU_COMPONENT_INDEX_BUTTON_EXIT       = 8, /**< Index to the main menu's exit button component.       */
	MAIN_MENU_COMPONENTS_COUNT                  = 12 /**< How many components the main menu uses.               */
};

/**
 * @brief Enumerates main menu's sounds index.
*/
enum MainMenuSoundIndex
{
	MAIN_MENU_SOUND_INDEX_CLICK = 0, /**< Index to the main menu's click sound. */
	MAIN_MENU_SOUNDS_COUNT      = 1  /**< How many sounds the main menu loads.  */
};

/**
 * @brief Main menu scene.
*/
class MainMenu final : public Common::Loop
					 , public Common::TextureInitializer<MAIN_MENU_TEXTURES_COUNT, MAIN_MENU_COMPONENTS_COUNT>
					 , public Common::SoundInitializer<MAIN_MENU_SOUNDS_COUNT>
{
public:
	/**
	 * @brief Loads everything needed for the scene.
	 * @param void
	*/
	MainMenu(void) noexcept;

	/**
	 * @brief Destroys everything that was loaded.
	 * @param void
	*/
	~MainMenu(void) noexcept;

private:
	/**
	 * @brief Handles an event.
	 * @param event: event to be handled.
	 * @return void
	*/
	void handleEvent(const SDL_Event& event) noexcept override;

	/**
	 * @brief Method implementation for drawing scene updates.
	 * @param void
	 * @return void
	*/
	virtual void draw(void) noexcept;

private:
	/**
	 * @brief Holds the index of the component that was previously pressed.
	*/
	size_t m_clickDownIndex;
}; /*< class MainMenu */

} /*< namespace Menu */

#endif /*< MAIN_MENU_HPP_ */
