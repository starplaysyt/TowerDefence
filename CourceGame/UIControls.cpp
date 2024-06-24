#pragma once
#include "UIControls.h"
#include "EventFunctionAliases.h" //This should be here, god knows why, if it is declared in UIControls.h there is a stupid linker error 
//UPD: I know why, but it's gonna take a while to describe, so i'm gonna leave this as it is 
using namespace Interface;

//TODO: Fix destructors

#pragma region Rectangle Methods
Rectangle::Rectangle(BasicRenderer* renderer) {
    Visible = new bool(); *Visible = true;
    assignedRenderer = renderer;
    Location = new Vector2();
    Size = new Vector2();
    BorderStyle = BorderStyle::None;
    BackgroundColor = new Color();
    ForegroundColor = new Color();
}

bool Rectangle::IsMouseInside(Vector2 position) {
    return false;
}

void Rectangle::EventCheckup(Uint32 type, SDL_Event* args) {

}

void Rectangle::Draw() {
    if (!*Visible) return;
    switch (BorderStyle) {
    case BorderStyle::None:
        assignedRenderer->SetColor(*BackgroundColor);
        assignedRenderer->FillRect(*Location, *Size);
        break;
    case BorderStyle::FixedSingle:
        assignedRenderer->SetColor(*BackgroundColor);
        assignedRenderer->FillRect(*Location, *Size);
        assignedRenderer->SetColor(*ForegroundColor);
        assignedRenderer->DrawRect(*Location, *Size);
        break;
    default:
        std::cout << "<RectangleRenderer> This BorderStyle is not supported";
        break;
    }
}

Rectangle::~Rectangle() {
    delete Visible;
    delete Location;
    delete Size;
    delete ForegroundColor;
    delete BackgroundColor;
}
#pragma endregion

#pragma region Circle Methods
Circle::Circle(BasicRenderer* renderer) {
    Visible = new bool(); *Visible = true;
    assignedRenderer = renderer;
    Location = new Vector2();
    Radius = new int(); *Radius = 0;
    BorderStyle = BorderStyle::None;
    ForegroundColor = new Color();
    BackgroundColor = new Color();
}

bool Circle::IsMouseInside(Vector2 position) {
    return false;
}

void Circle::EventCheckup(Uint32 type, SDL_Event* args) {

}

void Circle::Draw() {
    if (!*Visible) return;
    switch (BorderStyle) {
    case BorderStyle::None:
        assignedRenderer->SetColor(*BackgroundColor);
        assignedRenderer->FillCircle(*Location, *Radius);
        break;
    case BorderStyle::FixedSingle:
        assignedRenderer->SetColor(*BackgroundColor);
        assignedRenderer->FillCircle(*Location, *Radius);
        assignedRenderer->SetColor(*ForegroundColor);
        assignedRenderer->DrawCircle(*Location, *Radius);
        break;
    default:
        std::cout << "<CircleRenderer> This BorderStyle is not supported";
        break;
    }
}

Circle::~Circle() {
    delete Visible;
    delete Location;
    delete Radius;
    delete ForegroundColor;
    delete BackgroundColor;
}
#pragma endregion

#pragma region Label Methods
Label::Label(BasicRenderer* renderer, TextRenderer* textRenderer) {
    Visible = new bool(); *Visible = true;
    assignedRenderer = renderer;
    assignedTextRenderer = textRenderer;
    Location = new Vector2;
    Size = new Vector2;
    AutoSize = new bool(); *AutoSize = true;
    BorderStyle = BorderStyle::None;
    ForegroundColor = new Color();
    BackgroundColor = new Color();
    TextSize = new int(); *TextSize = 20;
    Text = new std::string(); *Text = "";
    TextAllign = TextAllign::TopLeft;
}

bool Label::IsMouseInside(Vector2 position) {
    return false;
}

void Label::EventCheckup(Uint32 type, SDL_Event* args) {

}

void Label::Draw() {
    if (!*Visible) return;
    assignedTextRenderer->SetRendererColor(ForegroundColor);
    auto* dst = new SDL_Rect();
    dst->x = Location->x;
    dst->y = Location->y;
    SDL_Texture* texture = assignedTextRenderer->CreateTextTexture(*Text, dst, *TextSize);
    assignedRenderer->SetColor(*BackgroundColor);
    if (!*AutoSize) {
        switch (TextAllign) {
        case TextAllign::TopLeft:
            break;
        case TextAllign::TopCenter:
            dst->x = dst->x + (Size->x - dst->w) / 2;
            break;
        case TextAllign::TopRight:
            dst->x = dst->x + (Size->x - dst->w);
            break;
        case TextAllign::MiddleLeft:
            dst->y = dst->y + (Size->y - dst->h) / 2;
            break;
        case TextAllign::MiddleCenter:
            dst->y = dst->y + (Size->y - dst->h) / 2;
            dst->x = dst->x + (Size->x - dst->w) / 2;
            break;
        case TextAllign::MiddleRight:
            dst->y = dst->y + (Size->y - dst->h) / 2;
            dst->x = dst->x + (Size->x - dst->w);
            break;
        case TextAllign::BottomLeft:
            dst->y = dst->y + (Size->y - dst->h);
            break;
        case TextAllign::BottomCenter:
            dst->y = dst->y + (Size->y - dst->h);
            dst->x = dst->x + (Size->x - dst->w) / 2;
            break;
        case TextAllign::BottomRight:
            dst->y = dst->y + (Size->y - dst->h);
            dst->x = dst->x + (Size->x - dst->w);
            break;
        }
    }
    else {
        Size->x = dst->w;
        Size->y = dst->h;
    }
    assignedRenderer->FillRect(*Location, *Size);
    assignedTextRenderer->PasteTextTexture(texture, dst);
    SDL_DestroyTexture(texture);
    delete dst;
}

Label::~Label() {
    delete Location;
    delete Size;
    delete ForegroundColor;
    delete BackgroundColor;
    delete AutoSize;
    delete Text;
}
#pragma endregion

#pragma region Button Methods
Button::Button(BasicRenderer* renderer, TextRenderer* textRenderer) {
    Visible = new bool(); *Visible = true;
    assignedRenderer = renderer;
    assignedTextRenderer = textRenderer;
    Location = new Vector2();
    Size = new Vector2();
    AutoSize = new bool(); *AutoSize = true;
    BorderStyle = BorderStyle::None;
    ForegroundColor = new Color();
    BackgroundColor = new Color();
    Text = new std::string(); *Text = "";
    TextAllign = TextAllign::TopLeft;
    TextSize = new int(); *TextSize = 20;
    OnClick = &Events::BasicEventsAliases::MouseClickEvent;
    OnEnter = &Events::BasicEventsAliases::MouseMotionEvent;
    OnMove = &Events::BasicEventsAliases::MouseMotionEvent;
    OnLeft = &Events::BasicEventsAliases::MouseMotionEvent;
    OnMouseDown = &Events::BasicEventsAliases::MouseClickEvent;
    OnMouseUp = &Events::BasicEventsAliases::MouseClickEvent;
    isMouseInside = new bool(); *isMouseInside = false;
    isClicked = new bool(); *isClicked = false;
    
}

bool Button::IsMouseInside(Vector2 position) {
    if (position.x > Location->x && position.x < Location->x + Size->x)
        if (position.y > Location->y && position.y < Location->y + Size->y) {
            return true;
        }
    return false;
}

void Button::EventCheckup(Uint32 type, SDL_Event* event) {
    if (!*Visible) return;
    switch (type) {
    case 0: //nullevent code designed for leaving/not-encountered events or stuff
        if (*isMouseInside) {
            *isMouseInside = false;
            if (event->type == SDL_MOUSEMOTION) OnLeft(this, event->motion); //idk what <CENSORED> should happen for this checkup worked
        }
        if (*isClicked) {
            *isClicked = false;
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
        *isClicked = true;
        OnMouseDown(this, event->button);
        break;
    case SDL_MOUSEBUTTONUP:
        OnMouseUp(this, event->button);
        if (*isClicked)
            OnClick(this, event->button);
        *isClicked = false;
    case SDL_MOUSEMOTION:
        if (*isMouseInside) {
            OnMove(this, event->motion);
        }
        else {
            *isMouseInside = true;
            OnEnter(this, event->motion);
        }
        break;
    default:
        std::cout << "Button " << *Text << " >>> Unhandled event happened. It's not supported by the way." << std::endl;
        //TODO: REMOVE <CENSORED> <CENSORED>, IT IS <CENSORED> WRONG(stupid <CENSORED>, it's designed for act like that, though)
        //UTODO: It should work like that
        break;
    }
}

void Button::Draw() {
    if (!*Visible) return;
    assignedTextRenderer->SetRendererColor(ForegroundColor);
    assignedRenderer->SetColor(*BackgroundColor);
    if (*isMouseInside) {
        assignedRenderer->SetColor(*ForegroundColor);
        assignedTextRenderer->SetRendererColor(BackgroundColor);
    }

    if (*isClicked) {
        Location->Set(Location->x + 2, Location->y + 2);
    }

    auto* dst = new SDL_Rect();
    dst->x = Location->x;
    dst->y = Location->y;
    SDL_Texture* texture = assignedTextRenderer->CreateTextTexture(*Text, dst, *TextSize);

    if (!*AutoSize) {
        switch (TextAllign) {
        case TextAllign::TopLeft:
            break;
        case TextAllign::TopCenter:
            dst->x = dst->x + (Size->x - dst->w) / 2;
            break;
        case TextAllign::TopRight:
            dst->x = dst->x + (Size->x - dst->w);
            break;
        case TextAllign::MiddleLeft:
            dst->y = dst->y + (Size->y - dst->h) / 2;
            break;
        case TextAllign::MiddleCenter:
            dst->y = dst->y + (Size->y - dst->h) / 2;
            dst->x = dst->x + (Size->x - dst->w) / 2;
            break;
        case TextAllign::MiddleRight:
            dst->y = dst->y + (Size->y - dst->h) / 2;
            dst->x = dst->x + (Size->x - dst->w);
            break;
        case TextAllign::BottomLeft:
            dst->y = dst->y + (Size->y - dst->h);
            break;
        case TextAllign::BottomCenter:
            dst->y = dst->y + (Size->y - dst->h);
            dst->x = dst->x + (Size->x - dst->w) / 2;
            break;
        case TextAllign::BottomRight:
            dst->y = dst->y + (Size->y - dst->h);
            dst->x = dst->x + (Size->x - dst->w);
            break;
        }
    }
    else {
        Size->x = dst->w;
        Size->y = dst->h;
    }


    assignedRenderer->FillRect(*Location, *Size);
    if (BorderStyle == BorderStyle::FixedSingle) {
        assignedRenderer->SetColor(*isMouseInside ? *BackgroundColor : *ForegroundColor);
        assignedRenderer->DrawRect(*Location, *Size);
    }
    assignedTextRenderer->PasteTextTexture(texture, dst);

    //Destruct area

    SDL_DestroyTexture(texture);
    delete dst;
    if (*isClicked) {
        Location->Set(Location->x - 2, Location->y - 2);
    }
}

Button::~Button() {
    delete Visible;
    delete TextSize;
    delete Location;
    delete Size;
    delete ForegroundColor;
    delete BackgroundColor;
    delete AutoSize;
    delete Text;
}
#pragma endregion



//#endregion