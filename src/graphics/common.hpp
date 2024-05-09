
#ifndef COMPONENT_COMMON_H
#define COMPONENT_COMMON_H

#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <mutex>

typedef std::pair<double, double> dpair;
typedef std::pair<std::string, std::string> spair;

typedef std::vector<dpair> vdpair;

struct color_theme{
    SDL_Color primary_color;
    SDL_Color secondary_color;
    SDL_Color background_color;
};

struct generator_data {
    dpair* range;
    double* min_y;
    double* max_y;
    int npoints;
    std::vector<dpair>* data;
};

typedef void (*sample_generator)(generator_data data);
typedef void (*async_sample_generator)(generator_data data, std::mutex* vecmutex);

struct PlotterConfig {
    sample_generator generator;
    dpair* range;
    spair* units;
    color_theme* theme;
};

struct AsyncPlotterConfig {
    async_sample_generator generator;
    dpair* range;
    spair* units;
    color_theme* theme;
};

#endif
