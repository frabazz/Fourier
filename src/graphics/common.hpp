
#ifndef COMPONENT_COMMON_H
#define COMPONENT_COMMON_H

#include <vector>
#include <string>
#include <SDL2/SDL.h>


typedef std::pair<double, double> dpair;
typedef std::pair<std::string, std::string> spair;

typedef std::vector<dpair> vdpair;

struct color_theme{
    SDL_Color primary_color;
    SDL_Color secondary_color;
    SDL_Color background_color;
};

#endif
