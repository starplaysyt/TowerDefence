#include "Level1Interface.h"

namespace Level1ControlsEvents {
	void newWaveClickEvent(Interface::IControl* sender, SDL_MouseButtonEvent e) {
		AlphaRegister::isNewWaveRequested = true;
	}

	void menuClickEvent(Interface::IControl* sender, SDL_MouseButtonEvent e) {
		Level1Interface* inter = (Level1Interface*)sender->owner;
		*inter->backgroundRectangle->Visible = true;
		*inter->backToPlayButton->Visible = true;
		*inter->saveGameButton->Visible = true;
		*inter->quitGameButton->Visible = true;
	}

	void shopClickEvent(Interface::IControl* sender, SDL_MouseButtonEvent e) {
		Level1Interface* inter = (Level1Interface*)sender->owner;
		if (AlphaRegister::currentBuildingMode == ARegisterEnums::Building)
		{
			AlphaRegister::currentBuildingMode = ARegisterEnums::None;
			*inter->shopButton->Text = "Build mode";
		}
		else {
			AlphaRegister::currentBuildingMode = ARegisterEnums::Building;
			*inter->shopButton->Text = "Build mode: ON";
		}
			
	}

	void load1SaveSlotButtonClickEvent(Interface::IControl* sender, SDL_MouseButtonEvent e) {
		Level1Interface* inter = (Level1Interface*)sender->owner;
		
		std::ofstream out;
		out.open("Data/Saves/saveSlot1.txt");      
		if (out.is_open())
		{
			out << AlphaRegister::currentPlayingLevel << ":" << AlphaRegister::moneyCount << std::endl;
		}
		out.close();
		std::cout << "File has been written" << std::endl;
		*inter->load1SaveSlotButton->Text = "Level: " + std::to_string(AlphaRegister::currentPlayingLevel) + ", Money: " + std::to_string(AlphaRegister::moneyCount);
	}

	void FormMoveEvent(Interface::IOwner* sender, SDL_MouseMotionEvent e) {
		
	}

	void backToGameClickEvent(Interface::IControl* sender, SDL_MouseButtonEvent e) {
		Level1Interface* inter = (Level1Interface*)sender->owner;
		*inter->backgroundRectangle->Visible = false;
		*inter->backToPlayButton->Visible = false;
		*inter->saveGameButton->Visible = false;
		*inter->quitGameButton->Visible = false;
	}

	void saveGameClickEvent(Interface::IControl* sender, SDL_MouseButtonEvent e) {
		Level1Interface* own = (Level1Interface*)sender->owner;
		*own->continueBackgroundRectangle->Visible = true;
		*own->continueLabel->Visible = true;
		*own->continueCloseButton->Visible = true;
		*own->load1SaveSlotButton->Visible = true;

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

			std::cout << "Save file opened with args: " << strings[0] << ", " << strings[1] << std::endl;

			*own->load1SaveSlotButton->Text = "Level: " + strings[0] + ", Money: " + strings[1];
		}
		else
		{
			std::cout << "Cannot open save file" << std::endl;
			*own->load1SaveSlotButton->Text = "Save is not exists";
		}
	}

	void quitGameClickEvent(Interface::IControl* sender, SDL_MouseButtonEvent e) {
		AlphaRegister::currentPlayingLevel = 0;
		AlphaRegister::LogRegisterChanges("currentPlayingLevel", "Level1Interface.cpp", "Quit to menu button clicked");
		AlphaRegister::isLevelChangingRequested = true;
		AlphaRegister::LogRegisterChanges("isLevelChangingRequested", "Level1Interface.cpp", "Quit to menu button clicked");
	}

	void ContinueCloseButtonClickEvent(Interface::IControl* sender, SDL_MouseButtonEvent e) {
		Level1Interface* own = (Level1Interface*)sender->owner;
		*own->continueBackgroundRectangle->Visible = false;
		*own->continueLabel->Visible = false;
		*own->continueCloseButton->Visible = false;
		*own->load1SaveSlotButton->Visible = false;
	}
}

Level1Interface::Level1Interface(SDL_Renderer* renderer, SDL_Window* window) : UserInterface(window, renderer) {
	InitializeComponent();
}

void Level1Interface::InitializeComponent() {

	backgroundRectangle = new Interface::Rectangle(basicRenderer);
	backgroundRectangle->BackgroundColor->Set(0, 0, 0, 100);
	backgroundRectangle->BorderStyle = Interface::BorderStyle::None;
	backgroundRectangle->Location->Set(20, 60);
	backgroundRectangle->Size->Set(200, 500);
	backgroundRectangle->owner = (IOwner*)this;
	*backgroundRectangle->Visible = false;
	controls.push_back(backgroundRectangle);

	backToPlayButton = new Interface::Button(basicRenderer, textRenderer);
	backToPlayButton->Location->Set(30, 140);
	backToPlayButton->Size->Set(180, 40);
	backToPlayButton->OnClick = &Level1ControlsEvents::backToGameClickEvent;
	*backToPlayButton->TextSize = 16;
	backToPlayButton->TextAllign = Interface::TextAllign::MiddleCenter;
	*backToPlayButton->AutoSize = false;
	*backToPlayButton->Visible = false;
	backToPlayButton->BackgroundColor->Set(0, 0, 0, 255);
	backToPlayButton->ForegroundColor->Set(255, 255, 255, 255);
	*backToPlayButton->Text = "Back to play";
	backToPlayButton->owner = (IOwner*)this;
	controls.push_back(backToPlayButton);

	saveGameButton = new Interface::Button(basicRenderer, textRenderer);
	saveGameButton->Location->Set(30, 210);
	saveGameButton->Size->Set(180, 40);
	saveGameButton->OnClick = &Level1ControlsEvents::saveGameClickEvent;
	*saveGameButton->TextSize = 16;
	saveGameButton->TextAllign = Interface::TextAllign::MiddleCenter;
	*saveGameButton->AutoSize = false;
	*saveGameButton->Visible = false;
	saveGameButton->BackgroundColor->Set(0, 0, 0, 255);
	saveGameButton->ForegroundColor->Set(255, 255, 255, 255);
	*saveGameButton->Text = "Save game";
	saveGameButton->owner = (IOwner*)this;
	controls.push_back(saveGameButton);

	quitGameButton = new Interface::Button(basicRenderer, textRenderer);
	quitGameButton->Location->Set(30, 280);
	quitGameButton->Size->Set(180, 40);
	quitGameButton->OnClick = &Level1ControlsEvents::quitGameClickEvent;
	*quitGameButton->TextSize = 16;
	quitGameButton->TextAllign = Interface::TextAllign::MiddleCenter;
	*quitGameButton->AutoSize = false;
	*quitGameButton->Visible = false;
	quitGameButton->BackgroundColor->Set(0, 0, 0, 255);
	quitGameButton->ForegroundColor->Set(255, 255, 255, 255);
	*quitGameButton->Text = "Quit game";
	quitGameButton->owner = (IOwner*)this;
	controls.push_back(quitGameButton);

	waveNumberLabel = new Interface::Label(basicRenderer, textRenderer);
	waveNumberLabel->Location->Set(850, 20);
	*waveNumberLabel->AutoSize = true;
	*waveNumberLabel->TextSize = 20;
	waveNumberLabel->BackgroundColor->Set(0, 0, 0, 0);
	waveNumberLabel->ForegroundColor->Set(255, 255, 255, 255);
	*waveNumberLabel->Text = "Wave 0";
	waveNumberLabel->owner = (IOwner*)this;
	controls.push_back(waveNumberLabel);

	levelNumberLabel = new Interface::Label(basicRenderer, textRenderer);
	levelNumberLabel->Location->Set(740, 20);
	*levelNumberLabel->AutoSize = true;
	*levelNumberLabel->TextSize = 20;
	levelNumberLabel->BackgroundColor->Set(0, 0, 0, 0);
	levelNumberLabel->ForegroundColor->Set(255, 255, 255, 255);
	*levelNumberLabel->Text = "Level 1";
	levelNumberLabel->owner = (IOwner*)this;
	controls.push_back(levelNumberLabel);

	moneyCountLabel = new Interface::Label(basicRenderer, textRenderer);
	moneyCountLabel->Location->Set(740, 40);
	*moneyCountLabel->AutoSize = true;
	*moneyCountLabel->TextSize = 20;
	moneyCountLabel->BackgroundColor->Set(0, 0, 0, 0);
	moneyCountLabel->ForegroundColor->Set(255, 255, 255, 255);
	*moneyCountLabel->Text = "Money: ";
	moneyCountLabel->owner = (IOwner*)this;
	controls.push_back(moneyCountLabel);

	shopButton = new Interface::Button(basicRenderer, textRenderer);
	shopButton->Location->Set(120, 20);
	shopButton->Size->Set(160, 25);
	shopButton->OnClick = &Level1ControlsEvents::shopClickEvent;
	*shopButton->TextSize = 16;
	shopButton->TextAllign = Interface::TextAllign::MiddleCenter;
	*shopButton->AutoSize = false;
	shopButton->BackgroundColor->Set(0, 0, 0, 255);
	shopButton->ForegroundColor->Set(255, 255, 255, 255);
	*shopButton->Text = "Build mode";
	shopButton->owner = (IOwner*)this;
	controls.push_back(shopButton);

	menuButton = new Interface::Button(basicRenderer, textRenderer);
	menuButton->Location->Set(20, 20);
	menuButton->Size->Set(80, 25);
	menuButton->OnClick = &Level1ControlsEvents::menuClickEvent;
	*menuButton->TextSize = 16;
	menuButton->TextAllign = Interface::TextAllign::MiddleCenter;
	*menuButton->AutoSize = false;
	menuButton->BackgroundColor->Set(0, 0, 0, 255);
	menuButton->ForegroundColor->Set(255, 255, 255, 255);
	*menuButton->Text = "Menu";
	menuButton->owner = (IOwner*)this;
	controls.push_back(menuButton);

	newWaveButton = new Interface::Button(basicRenderer, textRenderer);
	newWaveButton->Location->Set(750, 500);
	newWaveButton->Size->Set(180, 40);
	newWaveButton->OnClick = &Level1ControlsEvents::newWaveClickEvent;
	*newWaveButton->TextSize = 12;
	newWaveButton->TextAllign = Interface::TextAllign::MiddleCenter;
	*newWaveButton->AutoSize = false;
	newWaveButton->BackgroundColor->Set(0, 0, 0, 255);
	newWaveButton->ForegroundColor->Set(255, 255, 255, 255);
	*newWaveButton->Text = "New Wave is coming in: ";
	newWaveButton->owner = (IOwner*)this;
	controls.push_back(newWaveButton);



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
	*continueLabel->Text = "Save...";
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
	continueCloseButton->OnClick = &Level1ControlsEvents::ContinueCloseButtonClickEvent;
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
	load1SaveSlotButton->OnClick = &Level1ControlsEvents::load1SaveSlotButtonClickEvent;
	load1SaveSlotButton->owner = (IOwner*)this;
	controls.push_back(load1SaveSlotButton);





	OnMove = &Level1ControlsEvents::FormMoveEvent;
}
