#include "Component.hpp"
#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include <string>

typedef std::pair<double, double> dpair;

typedef std::shared_ptr<std::vector<dpair>> (*sample_generator) (std::shared_ptr<dpair> range, double* min_y, double* max_y, int npoints);

class Plotter : public Component{
    public:
        Plotter(SDL_Rect* _renderArea, SDL_Renderer* _renderer, sample_generator, std::shared_ptr<dpair> range, SDL_Color* ax_color, SDL_Color* f_color, std::string x_unit, std::string y_unit);
        void updateRange(std::shared_ptr<dpair> new_range);
        void feedEvent(SDL_Event* e) override;

    private:
        sample_generator _generator;
        std::shared_ptr<dpair> _range;
        std::shared_ptr<std::vector<dpair>> _data;
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
