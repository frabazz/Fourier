#include <SDL2/SDL.h>

#ifndef GRAPHIC_COMPONENT_H
#define GRAPHIC_COMPONENT_H

class Component {
    public:
        Component(SDL_Rect* renderArea, SDL_Renderer* renderer);
        void render();
    protected:
        SDL_Rect* _renderArea;
        SDL_Renderer* _renderer;
        void fillRect(SDL_Rect* rect);
        void drawRect(SDL_Rect* rect);
        void drawLine(float x1, float y1, float x2, float y2);
        void drawPoint(float x, float y);
        void drawLineAA(float x1, float y1, float x2, float y2, SDL_Color* color);
        void setColor(SDL_Color* c);
        virtual void componentRender() = 0;
};

#endif
