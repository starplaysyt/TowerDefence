#pragma once
#include "UserInterface.h"
#include <SDL.h>
#include "UIControls.h"
#include "UIEnums.h"
#include "IControl.h"
#include "AlphaRegister.h"
#include <fstream>
#include <string>

class Level1Interface : public Interface::UserInterface
{
private:
	void InitializeComponent() override;

public:
	Interface::Button *newWaveButton;

	Interface::Button* menuButton;

	Interface::Button* shopButton;

	Interface::Label* waveNumberLabel;

	Interface::Label* levelNumberLabel;

	Interface::Label* moneyCountLabel;

	Interface::Rectangle* backgroundRectangle;
	Interface::Button* backToPlayButton;
	Interface::Button* saveGameButton;
	Interface::Button* quitGameButton;

	Interface::Rectangle* continueBackgroundRectangle;
	Interface::Label* continueLabel;
	Interface::Button* continueCloseButton;
	Interface::Button* load1SaveSlotButton;

	Level1Interface(SDL_Renderer* renderer, SDL_Window* window);
};

