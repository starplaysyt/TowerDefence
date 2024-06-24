#pragma once
#include <SDL.h>
#include "Vector2.h"
#include "IOwner.h"

namespace Interface {
    class IControl
    {
    public:
        virtual void Draw() {}
        virtual void EventCheckup(Uint32 type, SDL_Event* args) {}
        virtual bool IsMouseInside(Vector2 position) { return false; }

        IOwner* owner;

    };
}
