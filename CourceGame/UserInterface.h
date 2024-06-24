#pragma once
#include <SDL.h>
#include <vector>
#include "IControl.h"
#include "TextRenderer.h"
#include "BasicRenderer.h"

namespace Interface {
	class UserInterface : public IOwner
	{
	public:

		virtual void InitializeComponent();

		void Draw();
		bool CheckupEvents(SDL_Event* e);

		UserInterface(SDL_Window* window, SDL_Renderer* renderer);

		~UserInterface();

		void (*OnMove) (IOwner*, SDL_MouseMotionEvent) { };

	private:
		SDL_Renderer* renderer;
		SDL_Window* window;

	protected:
		BasicRenderer* basicRenderer;
		TextRenderer* textRenderer;
		std::vector<IControl*> controls;
		
	};
}

