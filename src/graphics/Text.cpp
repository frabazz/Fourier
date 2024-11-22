#include "Text.hpp"

#include <SDL_ttf.h>
#include <iostream>

std::map<int, TTF_Font *> *Text::font_cache = NULL;

Text::Text(SDL_Rect renderArea, std::string text, int font_size, SDL_Color color)
    : Component(renderArea) {
  _text = text;
  _font_size = font_size;
  _color = color;

  auto it = font_cache->find(font_size);
  if (it == font_cache->end()) {
    _font = TTF_OpenFont(FONT_DIR, font_size);
    if(_font)
      std::cout << "error opening font" << std::endl;
  } else
    _font = it->second;

  SDL_Surface *surf = TTF_RenderText_Blended(_font, _text.c_str(), _color);
  if (surf == NULL) {
    TTF_CloseFont(_font);
    std::cout << "error rendering text" << std::endl;
  }

  _texture = SDL_CreateTextureFromSurface(_renderer, surf);
  if(_texture == NULL)
    std::cout << "error creating texture" << std::endl;
  
  SDL_FreeSurface(surf);
}

void Text::regenTexture(){  
  SDL_Surface *surf = TTF_RenderText_Blended(_font, _text.c_str(), _color);
  if (surf == NULL) {
    TTF_CloseFont(_font);
    std::cout << "error rendering text" << std::endl;
  }

  _texture = SDL_CreateTextureFromSurface(_renderer, surf);
  if(_texture == NULL)
    std::cout << "error creating texture" << std::endl;
  SDL_FreeSurface(surf);
  
}




void Text::componentRender(){
  SDL_Rect render_rect = _renderArea;
  SDL_QueryTexture(_texture, NULL, NULL, &_renderArea.w, &_renderArea.h);
  SDL_RenderCopy(_renderer, _texture, NULL, &render_rect);
}

void Text::setColor(SDL_Color color){
  _color = color;
  regenTexture();
}

void Text::setText(std::string text){
  _text = text;
  regenTexture();
}

void Text::feedEvent(SDL_Event* ev){}

Text::~Text(){
  SDL_DestroyTexture(_texture);
}

void Text::freeFonts(){
  for(auto it : *font_cache)
    TTF_CloseFont(it.second);
  
}
