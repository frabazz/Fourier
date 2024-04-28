#include "Component.hpp"
#include <SDL2/SDL.h>
#include <memory>
#include <vector>

typedef std::pair<double, double> dpair;

typedef struct sample_data {
    std::shared_ptr< std::vector<dpair> > data;
    double min_y, max_y;
} sample_data_t;

typedef std::shared_ptr<sample_data_t> (*sample_generator) (std::shared_ptr<dpair> range, int max_values);

class Plotter : public Component{
    public:
        Plotter(SDL_Rect* _renderArea, SDL_Renderer* _renderer, sample_generator, std::shared_ptr<dpair> range, SDL_Color* ax_color, SDL_Color* f_color);
        void updateRange(std::shared_ptr<dpair> new_range);

    private:
        sample_generator _generator;
        std::shared_ptr<dpair> _range;
        std::shared_ptr<sample_data> _sample;
        SDL_Color *_ax_color, *_f_color;
        void componentRender() override;
};
