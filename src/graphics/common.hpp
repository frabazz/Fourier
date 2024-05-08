
#ifndef COMPONENT_COMMON_H
#define COMPONENT_COMMON_H

#include <vector>
#include <string>
#include <SDL2/SDL.h>


typedef std::pair<double, double> dpair;
typedef std::pair<std::string, std::string> spair;

typedef std::vector<dpair> vdpair;

typedef struct color_theme{
    SDL_Color primary_color;
    SDL_Color secondary_color;
    SDL_Color background_color;
} color_theme_t;

typedef void (*sample_generator)(dpair* range, int npoints, std::vector<dpair>* points, double* min_y, double* max_y);


#endif
