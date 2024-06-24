#pragma once
#include "UserInterface.h"
#include <SDL.h>
#include <fstream>
#include <string>
#include "UIControls.h"
#include "UIEnums.h"
#include "IControl.h"
#include "AlphaRegister.h"

class MainMenuInterface : public Interface::UserInterface 
{
private:
	void InitializeComponent() override;

public:
	Interface::Button* newGameButton;
	Interface::Button* continueButton;
	Interface::Button* settingsButton;
	Interface::Button* quitButton;
	Interface::Label* gameNameLabel;
	Interface::Rectangle* backgroundRectangle;

	Interface::Rectangle* settingsBackgroundRectangle;
	Interface::Label* settingsLabel;
	Interface::Button* settingsCloseButton;
	Interface::Label* settingsInDevelopmentLabel;

	Interface::Button* load1SaveSlotButton;

	Interface::Rectangle* continueBackgroundRectangle;
	Interface::Label* continueLabel;
	Interface::Button* continueCloseButton;
	int slot1Level = 0;
	int slot1Money = 0;


	MainMenuInterface(SDL_Renderer* renderer, SDL_Window* window);

};

