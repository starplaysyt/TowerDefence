#pragma once
#include <SDL.h>
#include "IControl.h"
#include "Vector2.h"
#include "UIEnums.h"
#include "Color.h"
#include "BasicRenderer.h"
#include "iostream"
#include "TextRenderer.h"

namespace Interface {
    class Rectangle : public IControl {
    public:
        void Draw() override;

        void EventCheckup(Uint32 type, SDL_Event* event) override;

        bool IsMouseInside(Vector2 position) override;

    public:
        bool* Visible;
        Vector2* Location;
        Vector2* Size;
        BorderStyle::BorderStyleEnum BorderStyle;
        Color* BackgroundColor;
        Color* ForegroundColor;

        Rectangle(BasicRenderer* renderer);

        ~Rectangle();

    private:
        BasicRenderer* assignedRenderer;
    };

    class Circle : public IControl {
    public:
        void Draw() override;

        void EventCheckup(Uint32 type, SDL_Event* event) override;

        bool IsMouseInside(Vector2 position) override;

    public:
        bool* Visible;
        Vector2* Location;
        int* Radius;
        BorderStyle::BorderStyleEnum BorderStyle;
        Color* BackgroundColor;
        Color* ForegroundColor;

        Circle(BasicRenderer* renderer);

        ~Circle();

    private:
        BasicRenderer* assignedRenderer;
    };

    class Label : public IControl {
    public:
        void Draw() override;

        void EventCheckup(Uint32 type, SDL_Event* event) override;

        bool IsMouseInside(Vector2 position) override;

    public:
        bool* Visible;
        Vector2* Location;
        Vector2* Size;
        bool* AutoSize;
        BorderStyle::BorderStyleEnum BorderStyle;
        Color* BackgroundColor;
        Color* ForegroundColor;
        std::string* Text;
        TextAllign::TextAllignEnum TextAllign;
        int* TextSize;
        Label(BasicRenderer* renderer, TextRenderer* textRenderer);

        ~Label();

    private:
        BasicRenderer* assignedRenderer;
        TextRenderer* assignedTextRenderer;
    };

    class Button : public IControl {
    public:

        void Draw() override;

        void EventCheckup(Uint32 type, SDL_Event* event) override;

        bool IsMouseInside(Vector2 position) override;

        void (*OnClick) (IControl*, SDL_MouseButtonEvent) { };

        void (*OnEnter) (IControl*, SDL_MouseMotionEvent) { };

        void (*OnMove) (IControl*, SDL_MouseMotionEvent) { };

        void (*OnLeft) (IControl*, SDL_MouseMotionEvent) { };

        void (*OnMouseDown) (IControl*, SDL_MouseButtonEvent) { };

        void (*OnMouseUp) (IControl*, SDL_MouseButtonEvent) { };

    public:
        bool* Visible;
        Vector2* Location;
        Vector2* Size;
        bool* AutoSize;
        BorderStyle::BorderStyleEnum BorderStyle;
        Color* BackgroundColor;
        Color* ForegroundColor;
        std::string* Text;
        TextAllign::TextAllignEnum TextAllign;
        int* TextSize;

        Button(BasicRenderer* renderer, TextRenderer* textRenderer);

        ~Button();

    private:
        bool* isClicked;
        bool* isMouseInside;
        BasicRenderer* assignedRenderer;
        TextRenderer* assignedTextRenderer;

    };
}


