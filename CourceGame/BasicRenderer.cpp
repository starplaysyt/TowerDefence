#include "BasicRenderer.h"

using namespace Interface;

BasicRenderer::BasicRenderer(SDL_Renderer* sdlRenderer, SDL_Window* window) {
    this->renderer = sdlRenderer;
    this->window = window;
}

void BasicRenderer::CompleteRender() {
    SDL_RenderPresent(renderer);
    SDL_RenderClear(renderer);
}

void BasicRenderer::SetColor(Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void BasicRenderer::DrawLine(Vector2 pos1, Vector2 pos2) {
    SDL_RenderDrawLine(renderer, pos1.x, pos1.y, pos2.x, pos2.y);
}

void BasicRenderer::DrawRect(Vector2 position, Vector2 size) {
    auto rect = new SDL_Rect();
    rect->x = position.x;
    rect->y = position.y;
    rect->w = size.x;
    rect->h = size.y;
    SDL_RenderDrawRect(renderer, rect);
    delete rect;
}

void BasicRenderer::FillRect(Vector2 position, Vector2 size) {
    auto rect = new SDL_Rect();
    rect->x = position.x;
    rect->y = position.y;
    rect->w = size.x;
    rect->h = size.y;
    SDL_RenderFillRect(renderer, rect);
    delete rect;
}

void BasicRenderer::FillCircle(Vector2 centre, int radius) {
    int diameter = (radius * 2);
    int x = (radius - 1);
    int y = 0;
    int tx = 1;
    int ty = 1;
    int error = (tx - diameter);

    while (x >= y)
    {
        SDL_RenderDrawLine(renderer, centre.x - x, centre.y - y, centre.x, centre.y - y);
        SDL_RenderDrawLine(renderer, centre.x - y, centre.y - x, centre.x, centre.y - x);
        SDL_RenderDrawLine(renderer, centre.x - x, centre.y + y, centre.x, centre.y + y);
        SDL_RenderDrawLine(renderer, centre.x - y, centre.y + x, centre.x, centre.y + x);
        SDL_RenderDrawLine(renderer, centre.x + x, centre.y - y, centre.x, centre.y - y);
        SDL_RenderDrawLine(renderer, centre.x + y, centre.y - x, centre.x, centre.y - x);
        SDL_RenderDrawLine(renderer, centre.x + y, centre.y + x, centre.x, centre.y + x);
        SDL_RenderDrawLine(renderer, centre.x + x, centre.y + y, centre.x, centre.y + y);
        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }
        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

void BasicRenderer::DrawCircle(Vector2 centre, int radius) {
    int* diameter = new int(); *diameter = (radius * 2);
    int* x = new int(); *x = (radius - 1);
    int* y = new int(); *y = 0;
    int* tx = new int(); *tx = 1;
    int* ty = new int(); *ty = 1;
    int* error = new int(); *error = (*tx - *diameter);

    while (*x >= *y)
    {
        SDL_RenderDrawPoint(renderer, centre.x + *x, centre.y - *y);
        SDL_RenderDrawPoint(renderer, centre.x + *x, centre.y + *y);
        SDL_RenderDrawPoint(renderer, centre.x - *x, centre.y - *y);
        SDL_RenderDrawPoint(renderer, centre.x - *x, centre.y + *y);
        SDL_RenderDrawPoint(renderer, centre.x + *y, centre.y - *x);
        SDL_RenderDrawPoint(renderer, centre.x + *y, centre.y + *x);
        SDL_RenderDrawPoint(renderer, centre.x - *y, centre.y - *x);
        SDL_RenderDrawPoint(renderer, centre.x - *y, centre.y + *x);

        if (*error <= 0)
        {
            ++* y;
            *error += *ty;
            *ty += 2;
        }
        if (*error > 0)
        {
            --* x;
            *tx += 2;
            *error += (*tx - *diameter);
        }
    }
    delete diameter;
    delete x; delete y; delete tx; delete ty; delete error;
}

void BasicRenderer::ClearRenderer() {
    SDL_RenderClear(renderer);
}

SDL_Renderer* BasicRenderer::GetSDLRenderer() {
    return renderer;
}