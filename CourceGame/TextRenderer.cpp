#include "TextRenderer.h"

using namespace Interface;

void TextRenderer::OpenFontFile(std::string path, int size) {
    if (*isFontOpened) {
        std::cout << "Font File is already opened."; //TODO: Make standard error output
        return;
    }
    TextFont = TTF_OpenFont(path.c_str(), size);
    if (TextFont == nullptr) {
        std::cout << "<TextRenderer> Error throwed in OpenFontFile: " << TTF_GetError() << std::endl;
        *isFontOpened = false;
        return;
    }
    
    *isFontOpened = true;
}

TextRenderer::TextRenderer(BasicRenderer* renderer, SDL_Window* window) {
    this->renderer = renderer;
    this->sdlWindow = window;
    isFontOpened = new bool(); *isFontOpened = false;
    TextSize = new int();
    ForegroundColor = new Color();
}

void TextRenderer::CloseFontFile() {
    if (!*isFontOpened) {
        std::cout << "Font File is already closed."; //TODO: Make standard error output
        return;
    }
    TTF_CloseFont(TextFont);
    *isFontOpened = false;
}

void TextRenderer::SetRendererColor(Color* color) {
    ForegroundColor = color;
}

SDL_Texture* TextRenderer::CreateTextTexture(const std::string& text, SDL_Rect* dst, int size) {
    if (!*isFontOpened) {
        std::cout << "Font File is not loaded."; //TODO: Make standard error output
        return nullptr;
    }
    //std::cout << "Test:: Text Output";
    auto* RpcColor = new SDL_Color();
    RpcColor->r = ForegroundColor->r;
    RpcColor->g = ForegroundColor->g;
    RpcColor->b = ForegroundColor->b;
    RpcColor->a = ForegroundColor->a;
    TTF_SetFontSize(TextFont, size);
    SDL_Surface* surf = TTF_RenderUTF8_Blended(TextFont, text.c_str(), *RpcColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer->GetSDLRenderer(), surf);
    // if (texture == nullptr){
    //     TTF_Quit();
    //     SDL_Quit();
    //     std::cout << "Failed to create texture. Quitting...";
    //     return nullptr;
    // }
    SDL_FreeSurface(surf);
    Uint32* format = new Uint32();
    int* access = new int();
    int* w = new int();
    int* h = new int();
    SDL_QueryTexture(texture, format, access, w, h);
    dst->w = *w;
    dst->h = *h;

    delete format;
    delete access;
    delete w; delete h;
    delete RpcColor;
    return texture;
}

void TextRenderer::PasteTextTexture(SDL_Texture* texture, SDL_Rect* dst) {
    SDL_RenderCopy(renderer->GetSDLRenderer(), texture, 0, dst);
}

TextRenderer::~TextRenderer() {
    delete TextSize;
    delete isFontOpened;
    delete ForegroundColor;
}
