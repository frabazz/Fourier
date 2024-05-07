#include "Component.hpp"
#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include <string>
#include <mutex>

class Plotter;

/*
** probably shit code, the generator should calculate a function in the given range
** at n points, and return a vector with values, max_x and max_y (to avoid useless
** calculations).
**
** The callback structure is necessary because the generator might be handled by a
** thread asynchronously
 */

typedef std::pair<double, double> dpair;
typedef void (*sample_generator) (dpair* range, int npoints, Plotter* plotter);


class Plotter : public Component{
    public:
        Plotter(SDL_Rect* _renderArea, SDL_Renderer* _renderer, sample_generator, dpair* range, SDL_Color* ax_color, SDL_Color* f_color, std::string x_unit, std::string y_unit);
        void updateRange(std::shared_ptr<dpair> new_range);
        void feedEvent(SDL_Event* e) override;
        void recalc(double min_x, double min_y, std::vector<dpair>* values);

    private:
        std::mutex vecmutex;
        sample_generator _generator;
        bool _generator_status;
        dpair* _range;
        std::vector<dpair>* _data;
        double _min_y, _max_y;
        double _x_scale, _y_scale;
        SDL_Color *_ax_color, *_f_color;
        bool _is_mouse_over;
        int _mouse_x, _mouse_y;
        std::string _x_unit, _y_unit;
        double scaleX(double x);
        double scaleY(double y);
        void componentRender() override;
};
