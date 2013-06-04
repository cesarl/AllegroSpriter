#ifndef					__AL_SPRITER_SPRITE_HH__
# define				__AL_SPRITER_SPRITE_HH__

#include				<allegro5/allegro.h>
#include				<allegro5/allegro_image.h>
#include				"ImageManager.hh"

namespace				AlSpriter
{
  class					Sprite
  {
  public:
    Sprite();
    ~Sprite();
    void				initialize(int x,
						   int y,
						   int w,
						   int h,
						   float rotation,
						   ALLEGRO_COLOR const & color,
						   ALLEGRO_BITMAP * bitmap);
    bool				setBitmap(std::string const & path, std::string const & rootPath = "");
    void				setColor(ALLEGRO_COLOR const & color);
    void				setRotation(float angle);
    void				setWidth(int width);
    void				setHeight(int height);
    void				setX(int x);
    void				setY(int y);
    void				draw() const;
  private:
    int					x_;
    int					y_;
    int					w_;
    int					h_;
    float				rotation_;
    ALLEGRO_COLOR			color_;
    ALLEGRO_BITMAP			*bitmap_;
  };
}

#endif					// __AL_SPRITER_SPRITE_HH__
