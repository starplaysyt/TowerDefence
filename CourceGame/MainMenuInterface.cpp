#include "MainMenuInterface.h"

namespace MenuControlsEvents {
	void SettingsButtonClickEvent(Interface::IControl* sender, SDL_MouseButtonEvent e) {
		MainMenuInterface* own = (MainMenuInterface*)sender->owner;
		if (*own->continueBackgroundRectangle->Visible) {
			own->continueCloseButton->OnClick(sender, e);
		}

		*own->settingsBackgroundRectangle->Visible = true;
		*own->gameNameLabel->Visible = false;
		*own->settingsLabel->Visible = true;
		*own->settingsCloseButton->Visible = true;
		*own->settingsInDevelopmentLabel->Visible = true;
	}

	void SettingsCloseButtonClickEvent(Interface::IControl* sender, SDL_MouseButtonEvent e) {
		MainMenuInterface* own = (MainMenuInterface*)sender->owner;
		*own->settingsBackgroundRectangle->Visible = false;
		*own->gameNameLabel->Visible = true;
		*own->settingsLabel->Visible = false;
		*own->settingsCloseButton->Visible = false;
		*own->settingsInDevelopmentLabel->Visible = false;
	}

	void StartButtonClickEvent(Interface::IControl* sender, SDL_MouseButtonEvent e) {
		AlphaRegister::isLevelChangingRequested = true;
		AlphaRegister::LogRegisterChanges("isLevelChangingRequested", "MainMenuInterface.cpp", "StartButtonClicked");
		AlphaRegister::currentPlayingLevel = 1;
		AlphaRegister::LogRegisterChanges("currentPlayingLevel", "MainMenuInterface.cpp", "StartButtonClicked, set to 1");
		AlphaRegister::isPlayerAlive = true;
		AlphaRegister::currentPlayingWave = 0;
	}

	void ContinueButtonClickEvent(Interface::IControl* sender, SDL_MouseButtonEvent e) {
		MainMenuInterface* own = (MainMenuInterface*)sender->owner;
		if (*own->settingsBackgroundRectangle->Visible) {
			SettingsCloseButtonClickEvent(sender, e);
		}

		*own->continueBackgroundRectangle->Visible = true;
		*own->gameNameLabel->Visible = false;
		*own->continueLabel->Visible = true;
		*own->continueCloseButton->Visible = true;
		*own->load1SaveSlotButton->Visible = true;
	}

	void ContinueCloseButtonClickEvent(Interface::IControl* sender, SDL_MouseButtonEvent e) {
		MainMenuInterface* own = (MainMenuInterface*)sender->owner;
		*own->continueBackgroundRectangle->Visible = false;
		*own->gameNameLabel->Visible = true;
		*own->continueLabel->Visible = false;
		*own->continueCloseButton->Visible = false;
		*own->load1SaveSlotButton->Visible = false;
	}

	void QuitButtonClickEvent(Interface::IControl* sender, SDL_MouseButtonEvent e) {
		AlphaRegister::isGameRunning = false;
	}

	void load1SaveSlotButtonClickEvent(Interface::IControl* sender, SDL_MouseButtonEvent e) {
		MainMenuInterface* own = (MainMenuInterface*)sender->owner;
		if (own->slot1Level != 0) {
			AlphaRegister::isLevelChangingRequested = true;
			AlphaRegister::LogRegisterChanges("isLevelChangingRequested", "MainMenuInterface.cpp", "Trying to load save");
			AlphaRegister::currentPlayingLevel = own->slot1Level;
			AlphaRegister::LogRegisterChanges("currentPlayingLevel", "MainMenuInterface.cpp", "Trying to load save, set to " + std::to_string(own->slot1Level));
			AlphaRegister::moneyCount = own->slot1Money;
			AlphaRegister::LogRegisterChanges("moneyCount", "MainMenuInterface.cpp", "Trying to load save, set to " + std::to_string(own->slot1Money));
			AlphaRegister::isPlayerAlive = true;
			AlphaRegister::currentPlayingWave = 0;
		}
	}
}

void MainMenuInterface::InitializeComponent() {
	backgroundRectangle = new Interface::Rectangle(basicRenderer);
	backgroundRectangle->BackgroundColor->Set(0, 0, 0, 100);
	backgroundRectangle->BorderStyle = Interface::BorderStyle::None;
	backgroundRectangle->Location->Set(20, 20);
	backgroundRectangle->Size->Set(200, 540);
	backgroundRectangle->owner = (IOwner*)this;
	controls.push_back(backgroundRectangle);

	newGameButton = new Interface::Button(basicRenderer, textRenderer);
	newGameButton->Location->Set(30, 140);
	newGameButton->Size->Set(180, 40);
	*newGameButton->TextSize = 19;
	newGameButton->TextAllign = Interface::TextAllign::MiddleCenter;
	*newGameButton->AutoSize = false;
	newGameButton->BackgroundColor->Set(0, 0, 0, 255);
	newGameButton->ForegroundColor->Set(255, 255, 255, 255);
	*newGameButton->Text = "New Game";
	newGameButton->OnClick = &MenuControlsEvents::StartButtonClickEvent;
	newGameButton->owner = (IOwner*)this;
	controls.push_back(newGameButton);

	continueButton = new Interface::Button(basicRenderer, textRenderer);
	continueButton->Location->Set(30, 190);
	continueButton->Size->Set(180, 40);
	*continueButton->TextSize = 19;
	continueButton->TextAllign = Interface::TextAllign::MiddleCenter;
	*continueButton->AutoSize = false;
	continueButton->BackgroundColor->Set(0, 0, 0, 255);
	continueButton->ForegroundColor->Set(255, 255, 255, 255);
	*continueButton->Text = "Continue";
	continueButton->OnClick = &MenuControlsEvents::ContinueButtonClickEvent;
	continueButton->owner = (IOwner*)this;
	controls.push_back(continueButton);

	settingsButton = new Interface::Button(basicRenderer, textRenderer);
	settingsButton->Location->Set(30, 240);
	settingsButton->Size->Set(180, 40);
	*settingsButton->TextSize = 19;
	settingsButton->TextAllign = Interface::TextAllign::MiddleCenter;
	*settingsButton->AutoSize = false;
	settingsButton->BackgroundColor->Set(0, 0, 0, 255);
	settingsButton->ForegroundColor->Set(255, 255, 255, 255);
	*settingsButton->Text = "Settings";
	settingsButton->owner = (IOwner*)this;
	settingsButton->OnClick = &MenuControlsEvents::SettingsButtonClickEvent;
	controls.push_back(settingsButton);

	quitButton = new Interface::Button(basicRenderer, textRenderer);
	quitButton->Location->Set(30, 290);
	quitButton->Size->Set(180, 40);
	*quitButton->TextSize = 19;
	quitButton->TextAllign = Interface::TextAllign::MiddleCenter;
	*quitButton->AutoSize = false;
	quitButton->BackgroundColor->Set(0, 0, 0, 255);
	quitButton->ForegroundColor->Set(255, 255, 255, 255);
	quitButton->OnClick = &MenuControlsEvents::QuitButtonClickEvent;
	*quitButton->Text = "Quit the game";
	quitButton->owner = (IOwner*)this;
	controls.push_back(quitButton);

	gameNameLabel = new Interface::Label(basicRenderer, textRenderer);
	gameNameLabel->Location->Set(340, 30);
	*gameNameLabel->AutoSize = true;
	*gameNameLabel->Text = "Tower Defence";
	*gameNameLabel->TextSize = 40;
	gameNameLabel->ForegroundColor->Set(0, 0, 0, 255);
	gameNameLabel->owner = (IOwner*)this;
	controls.push_back(gameNameLabel);

	settingsBackgroundRectangle = new Interface::Rectangle(basicRenderer);
	settingsBackgroundRectangle->BackgroundColor->Set(0, 0, 0, 100);
	settingsBackgroundRectangle->BorderStyle = Interface::BorderStyle::None;
	settingsBackgroundRectangle->Location->Set(260, 20);
	settingsBackgroundRectangle->Size->Set(560, 540);
	*settingsBackgroundRectangle->Visible = false; //replace
	settingsBackgroundRectangle->owner = (IOwner*)this;
	controls.push_back(settingsBackgroundRectangle);

	settingsLabel = new Interface::Label(basicRenderer, textRenderer);
	settingsLabel->Location->Set(280, 30);
	*settingsLabel->AutoSize = true;
	*settingsLabel->Text = "Settings";
	*settingsLabel->TextSize = 40;
	*settingsLabel->Visible = false;
	settingsLabel->ForegroundColor->Set(255, 255, 255, 255);
	settingsLabel->owner = (IOwner*)this;
	controls.push_back(settingsLabel);

	settingsCloseButton = new Interface::Button(basicRenderer, textRenderer);
	settingsCloseButton->Location->Set(620, 40);
	settingsCloseButton->Size->Set(180, 40);
	*settingsCloseButton->TextSize = 19;
	settingsCloseButton->TextAllign = Interface::TextAllign::MiddleCenter;
	*settingsCloseButton->AutoSize = false;
	*settingsCloseButton->Visible = false;
	settingsCloseButton->BackgroundColor->Set(0, 0, 0, 255);
	settingsCloseButton->ForegroundColor->Set(255, 255, 255, 255);
	*settingsCloseButton->Text = "Close";
	settingsCloseButton->OnClick = &MenuControlsEvents::SettingsCloseButtonClickEvent;
	settingsCloseButton->owner = (IOwner*)this;
	controls.push_back(settingsCloseButton);

	settingsInDevelopmentLabel = new Interface::Label(basicRenderer, textRenderer);
	settingsInDevelopmentLabel->Location->Set(260, 20);
	settingsInDevelopmentLabel->Size->Set(560, 540);
	*settingsInDevelopmentLabel->AutoSize = false;
	settingsInDevelopmentLabel->TextAllign = Interface::TextAllign::MiddleCenter;
	*settingsInDevelopmentLabel->Text = "In Development Now";
	*settingsInDevelopmentLabel->TextSize = 25;
	*settingsInDevelopmentLabel->Visible = false;
	settingsInDevelopmentLabel->ForegroundColor->Set(255, 255, 255, 255);
	settingsInDevelopmentLabel->owner = (IOwner*)this;
	controls.push_back(settingsInDevelopmentLabel);

	continueBackgroundRectangle = new Interface::Rectangle(basicRenderer);
	continueBackgroundRectangle->BackgroundColor->Set(0, 0, 0, 100);
	continueBackgroundRectangle->BorderStyle = Interface::BorderStyle::None;
	continueBackgroundRectangle->Location->Set(260, 20);
	continueBackgroundRectangle->Size->Set(560, 540);
	*continueBackgroundRectangle->Visible = false; //replace
	continueBackgroundRectangle->owner = (IOwner*)this;
	controls.push_back(continueBackgroundRectangle);

	continueLabel = new Interface::Label(basicRenderer, textRenderer);
	continueLabel->Location->Set(280, 30);
	*continueLabel->AutoSize = true;
	*continueLabel->Text = "Continue...";
	*continueLabel->TextSize = 40;
	*continueLabel->Visible = false;
	continueLabel->ForegroundColor->Set(255, 255, 255, 255);
	continueLabel->owner = (IOwner*)this;
	controls.push_back(continueLabel);

	continueCloseButton = new Interface::Button(basicRenderer, textRenderer);
	continueCloseButton->Location->Set(620, 40);
	continueCloseButton->Size->Set(180, 40);
	*continueCloseButton->TextSize = 19;
	continueCloseButton->TextAllign = Interface::TextAllign::MiddleCenter;
	*continueCloseButton->AutoSize = false;
	*continueCloseButton->Visible = false;
	continueCloseButton->BackgroundColor->Set(0, 0, 0, 255);
	continueCloseButton->ForegroundColor->Set(255, 255, 255, 255);
	*continueCloseButton->Text = "Close";
	continueCloseButton->OnClick = &MenuControlsEvents::ContinueCloseButtonClickEvent;
	continueCloseButton->owner = (IOwner*)this;
	controls.push_back(continueCloseButton);

	load1SaveSlotButton = new Interface::Button(basicRenderer, textRenderer);
	load1SaveSlotButton->Location->Set(280, 100);
	load1SaveSlotButton->Size->Set(520, 40);
	*load1SaveSlotButton->TextSize = 19;
	load1SaveSlotButton->TextAllign = Interface::TextAllign::MiddleCenter;
	*load1SaveSlotButton->AutoSize = false;
	*load1SaveSlotButton->Visible = false;
	load1SaveSlotButton->BackgroundColor->Set(0, 0, 0, 255);
	load1SaveSlotButton->ForegroundColor->Set(255, 255, 255, 255);
	*load1SaveSlotButton->Text = "Test";
	load1SaveSlotButton->OnClick = &MenuControlsEvents::load1SaveSlotButtonClickEvent;
	load1SaveSlotButton->owner = (IOwner*)this;
	controls.push_back(load1SaveSlotButton);

	std::string line;
	std::ifstream inputStream("Data/Saves/saveSlot1.txt");
	if (inputStream.is_open()) {
		std::getline(inputStream, line);
		std::string str = line;

		std::vector<std::string> strings;
		char separator = ':';
		int startIndex = 0, endIndex = 0;
		for (int i = 0; i <= str.size(); i++) {

			// If we reached the end of the word or the end of the input.
			if (str[i] == separator || i == str.size()) {
				endIndex = i;
				std::string temp;
				temp.append(str, startIndex, endIndex - startIndex);
				strings.push_back(temp);
				startIndex = endIndex + 1;
			}
		}

		slot1Level = std::stoi(strings[0]);
		slot1Money = std::stoi(strings[1]);

		std::cout << "Save file opened with args: " << slot1Level << ", " << slot1Money << std::endl;

		*load1SaveSlotButton->Text = "Level: " + std::to_string(slot1Level) + ", Money: " + std::to_string(slot1Money);
	}
	else
	{
		std::cout << "Cannot open save file" << std::endl;
		*load1SaveSlotButton->Text = "Save is not exists";
	}

	inputStream.close();
}

MainMenuInterface::MainMenuInterface(SDL_Renderer* renderer, SDL_Window* window) : UserInterface(window, renderer) {
	InitializeComponent();
}