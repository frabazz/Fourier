#include "Component.hpp"
#include <SDL2/SDL.h>
#include <SDL_render.h>

Component::Component(SDL_Rect* renderArea, SDL_Renderer* renderer){
    _renderer = renderer;
    _renderArea = renderArea;
}

void Component::fillRect(SDL_Rect* rect){
    SDL_Rect r = {rect->x + _renderArea->x,  rect->y + _renderArea->y, rect->w, rect->h};
    SDL_RenderFillRect(_renderer, &r);
}

void Component::drawRect(SDL_Rect* rect){
    SDL_Rect r = {rect->x + _renderArea->x,  rect->y + _renderArea->y, rect->w, rect->h};
    SDL_RenderDrawRect(_renderer, &r);
}

void Component::drawPoint(float x, float y){
    SDL_RenderDrawPoint(_renderer, _renderArea->x + x, _renderArea->y + y);
}

void Component::drawLine(float x1, float y1, float x2, float y2){
    SDL_RenderDrawLineF(_renderer, _renderArea->x +x1, _renderArea->y + y1, _renderArea->x + x2, _renderArea->y + y2);
}


inline double fpart(double x){
    return x - std::floor(x);
}

inline double rfpart(double x){
    return 1 - fpart(x);
}

void Component::drawLineAA(float x0, float y0, float x1, float y1, SDL_Color* color) {

    auto fpart = [](double x) { return x - std::floor(x); };

    auto rfpart = [&fpart](double x) { return 1 - fpart(x); };

    auto setBrightness = [this, &color](double c){
        SDL_SetRenderDrawColor(this->_renderer, c*color->r, c*color->g, c*color->b, color->a);
    };

    bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);

    if (steep) {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }

    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    double dx = x1 - x0;
    double dy = y1 - y0;
    double gradient = dy / dx;

    double xend = std::round(x0);
    double yend = y0 + gradient * (xend - x0);
    double xgap = rfpart(x0 + 0.5);
    int xpxl1 = static_cast<int>(xend);
    int ypxl1 = static_cast<int>(yend);



    if (steep) {
        setBrightness(rfpart(yend) * xgap);
        drawPoint(ypxl1, xpxl1);
        setBrightness(fpart(yend) * xgap);
        drawPoint(ypxl1 + 1, xpxl1);
    } else {
        setBrightness(rfpart(yend) * xgap);
        drawPoint(xpxl1, ypxl1);
        setBrightness(fpart(yend) * xgap);
        drawPoint(xpxl1, ypxl1 + 1);
    }

    double intery = yend + gradient;

    xend = std::round(x1);
    yend = y1 + gradient * (xend - x1);
    xgap = fpart(x1 + 0.5);
    int xpxl2 = static_cast<int>(xend);
    int ypxl2 = static_cast<int>(yend);

    if (steep) {
        setBrightness(rfpart(yend) * xgap);
        drawPoint(ypxl2, xpxl2);
        setBrightness(fpart(yend) * xgap);
        drawPoint(ypxl2 + 1, xpxl2);
    } else {
        setBrightness(rfpart(yend) * xgap);
        drawPoint(xpxl2, ypxl2);
        setBrightness(fpart(yend) * xgap);
        drawPoint(xpxl2, ypxl2 + 1);
    }


    if (steep) {
        for (int x = xpxl1 + 1; x < xpxl2; ++x) {
            setBrightness(rfpart(intery));
            drawPoint(static_cast<double>(std::floor(intery)), static_cast<double>(x));
            setBrightness(fpart(intery));
            drawPoint(static_cast<double>(std::floor(intery)) + 1, static_cast<double>(x));
            intery += gradient;
        }
    } else {
        for (int x = xpxl1 + 1; x < xpxl2; ++x) {
            setBrightness(rfpart(intery));
            drawPoint(static_cast<double>(x), static_cast<double>(std::floor(intery)));
            setBrightness(fpart(intery));
            drawPoint(static_cast<double>(x), static_cast<double>(std::floor(intery)) + 1);
            intery += gradient;
        }
    }


    setBrightness(1);
}

void Component::setColor(SDL_Color* c){
    SDL_SetRenderDrawColor(_renderer, c->r, c->g, c->b, c->a);
}

void Component::render(){
    //do stuff, TODO viewport
    componentRender();
}
