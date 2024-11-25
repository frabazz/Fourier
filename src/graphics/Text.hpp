#define FONT_DIR "../assets/default.ttf"

#include "Component.hpp"
#include <string>
#include <SDL2/SDL_ttf.h>
#include <map>

#ifndef F_TEXT
#define F_TEXT

class Text : public Component{
public:
  static std::map<int, TTF_Font*>* font_cache; // indexed by font size;
  static void freeFonts();
  Text(SDL_Rect renderArea, std::string text, int font_size, SDL_Color color);
  void setText(std::string text);
  void setFontSize(int font_size);
  void setColor(SDL_Color color);
  ~Text();
private:
  std::string _text;
  int _font_size;
  TTF_Font* _font;
  SDL_Texture* _texture;
  SDL_Color _color;

  void regenTexture();
  void componentRender() override;
  void feedEvent(SDL_Event* ev) override;
};



#endif
