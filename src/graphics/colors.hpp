#ifndef F_COLORS_HPP
#define F_COLORS_HPP

#include <SDL2/SDL.h>

namespace Color {

    constexpr SDL_Color BLACK = {0, 0, 0, 255};
    constexpr SDL_Color WHITE = {255, 255, 255, 255};
    constexpr SDL_Color RED = {255, 0, 0, 255};
    constexpr SDL_Color GREEN = {0, 255, 0, 255};
    constexpr SDL_Color BLUE = {0, 0, 255, 255};


    constexpr SDL_Color GRAY = {128, 128, 128, 255};
    constexpr SDL_Color LIGHT_GRAY = {192, 192, 192, 255};
    constexpr SDL_Color DARK_GRAY = {64, 64, 64, 255};


    constexpr SDL_Color CYAN = {0, 255, 255, 255};
    constexpr SDL_Color MAGENTA = {255, 0, 255, 255};
    constexpr SDL_Color YELLOW = {255, 255, 0, 255};


    constexpr SDL_Color ORANGE = {255, 165, 0, 255};
    constexpr SDL_Color BROWN = {165, 42, 42, 255};
    constexpr SDL_Color PINK = {255, 192, 203, 255};


    constexpr SDL_Color SKY_BLUE = {135, 206, 235, 255};
    constexpr SDL_Color NAVY_BLUE = {0, 0, 128, 255};
    constexpr SDL_Color TEAL = {0, 128, 128, 255};
    constexpr SDL_Color TURQUOISE = {64, 224, 208, 255};


    constexpr SDL_Color FOREST_GREEN = {34, 139, 34, 255};
    constexpr SDL_Color OLIVE = {128, 128, 0, 255};
    constexpr SDL_Color GOLD = {255, 215, 0, 255};
    constexpr SDL_Color TAN = {210, 180, 140, 255};


    constexpr SDL_Color PURPLE = {128, 0, 128, 255};
    constexpr SDL_Color VIOLET = {238, 130, 238, 255};
    constexpr SDL_Color INDIGO = {75, 0, 130, 255};
    constexpr SDL_Color LAVENDER = {230, 230, 250, 255};


    constexpr SDL_Color NEON_GREEN = {57, 255, 20, 255};
    constexpr SDL_Color NEON_BLUE = {77, 77, 255, 255};
    constexpr SDL_Color NEON_PINK = {255, 20, 147, 255};


    constexpr SDL_Color TRANSPARENT = {0, 0, 0, 0};
}

#endif 
