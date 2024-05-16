#ifndef GRAPHIC_COMPONENT_H
#define GRAPHIC_COMPONENT_H

#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <string>

#include "Event.hpp"

class Component {
    public:
        Component(SDL_Rect* renderArea, SDL_Renderer* renderer);
        void render();
    protected:
        SDL_Rect* _renderArea;
        SDL_Renderer* _renderer;
        TTF_Font* _default_font;

        //rendering primitives
        void fillRect(SDL_Rect* rect);
        void drawRect(SDL_Rect* rect);
        void drawLine(float x1, float y1, float x2, float y2);
        void drawPoint(float x, float y);
        void drawLineAA(float x1, float y1, float x2, float y2, SDL_Color color);
        void setColor(SDL_Color c);
        void drawToolTip(std::string text, SDL_Rect* area, SDL_Color bgcolor);

        //implemented specifically by components
        virtual void componentRender() = 0;
        virtual void feedEvent(events::Event* e) = 0;
};

#endif
