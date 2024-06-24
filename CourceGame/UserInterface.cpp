#include "UserInterface.h"

using namespace Interface;

namespace UserInterfaceFunctionAliases {
	void MouseMotionEvent(Interface::IOwner* sender, SDL_MouseMotionEvent e) {

	}
}

UserInterface::UserInterface(SDL_Window* window, SDL_Renderer* renderer) {
	this->renderer = renderer;
	this->window = window;
	
	basicRenderer = new BasicRenderer(renderer, window);

	textRenderer = new TextRenderer(basicRenderer, window);
	
	textRenderer->OpenFontFile("Data/Fonts/font.ttf", 10);

	OnMove = &UserInterfaceFunctionAliases::MouseMotionEvent;
}

void UserInterface::Draw() {
	for (size_t i = 0; i < controls.size(); i++)
	{
		controls[i]->Draw();
	}
}

bool UserInterface::CheckupEvents(SDL_Event* e) {
	bool ret = false;
	for (size_t i = 0; i < controls.size(); i++)
	{
		Vector2* mousePosition = new Vector2();
		SDL_GetMouseState(&mousePosition->x, &mousePosition->y);
		if (controls[i]->IsMouseInside(*mousePosition)) {
			controls[i]->EventCheckup(e->type, e);
			ret = true;
		}
		else
		{
			controls[i]->EventCheckup(0, e);
		}
		delete mousePosition;
	}
	if (e->type == SDL_MOUSEMOTION) {
		OnMove(this, e->motion);
	}
	return ret;
}

void UserInterface::InitializeComponent() {

}

UserInterface::~UserInterface() {
	textRenderer->CloseFontFile();
	delete textRenderer;

	delete basicRenderer;

	for (size_t i = 0; i < controls.size(); i++)
	{
		delete controls[i];
	}
}