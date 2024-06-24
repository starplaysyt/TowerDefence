#pragma once
#include <SDL.h>
#include "Vector2.h"
#include "Color.h"

namespace Interface
{
    class BasicRenderer
    {
    public:
        /*
         * Draws simple line from point pos1 to point pos2.
         */
        void DrawLine(Vector2 pos1, Vector2 pos2);

        /*
         *  Draws a rectangles' border from start point (TopLeft point), with a spec size.
         */
        void DrawRect(Vector2 position, Vector2 size);

        /*
         *  Fills spec zone, in border of rectangle with start point (TopLeft point), with a spec size.
         */
        void FillRect(Vector2 position, Vector2 size);

        /*
         *  Fills spec zone, in border of circle with start center point, with a spec radius.
         */
        void FillCircle(Vector2 centre, int radius);

        /*
         *  Draws a circle's border with start center point, with a spec radius.
         */
        void DrawCircle(Vector2 centre, int radius);

        /*
         *  Switch buffers in order, use at the end of rendering. Standard replacement.
         */
        void CompleteRender();

        /*
         *  Clears buffer. standard replacement
         */
        void ClearRenderer();

        /*
         *  Basic Renderer constructor
         */
        BasicRenderer(SDL_Renderer* sdlRenderer, SDL_Window* window);

        /*
         *  Changes Renderer color. Standard replacement with extension.
         */
        void SetColor(Color color);

        /*
        *   Returns reference to assigned SDL_Renderer
        */

        SDL_Renderer* GetSDLRenderer();

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
    };
}