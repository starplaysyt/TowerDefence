#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "BasicRenderer.h"
#include "Color.h"

namespace Interface {
    class TextRenderer {
    public:
        /*
         * Open
         */
        void OpenFontFile(std::string path, int size);

        void CloseFontFile();

        /*
         * Creates instance of TextRenderer.
         * Quick guide to use TextRenderer:
         * - First things first you need to open font file, use OpenFontFile.
         * - Use CreateTextTexture and PasteTextTexture for rendering.
         * - After finishing working with TextRendering, use CloseFontFile to
         *      close font file.
         */
        TextRenderer(BasicRenderer* renderer, SDL_Window* window);

        /*
         * Creates texture with text with special size.
         * Use with PasteTextTexture.
         */
        SDL_Texture* CreateTextTexture(const std::string& text, SDL_Rect* dst, int size);

        /*
         * Pastes texture with text into renderers' buffer.
         * Useful with CreateTextTexture.
         * Doesn't destroy texture, you should destroy it manually, same as dst.
         */
        void PasteTextTexture(SDL_Texture* texture, SDL_Rect* dst);

        //TODO: Remove info bout constant text size, if there is some. No more actual.

        ~TextRenderer();

        /*
         * Sets not renderer color, but esp. TextRenderer color cos of special work circuit.
         * To properly set exact Renderer color, ask assigned base renderer
         */
        void SetRendererColor(Color* color);

    private:

        TTF_Font* TextFont;
        int* TextSize;
        bool* isFontOpened;
        BasicRenderer* renderer;
        SDL_Window* sdlWindow;
        Color* ForegroundColor;
    };
}

