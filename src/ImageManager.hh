#ifndef					__AL_SPRITER_IMAGE_MANAGER_HH__
# define				__AL_SPRITER_IMAGE_MANAGER_HH__

#include				<allegro5/allegro.h>
#include				<allegro5/allegro_image.h>
#include				<rapidxml.hpp>
#include				<string>
#include				<iostream>
#include				<map>

namespace				AlSpriter
{
  class					ImageManager
  {
  public:
    ~ImageManager();
    static ImageManager			&getInstance();
    ALLEGRO_BITMAP			*load(std::string const & path);
    ALLEGRO_BITMAP			*get(std::string const & path);
  private:
    ImageManager();
    std::map<std::string, ALLEGRO_BITMAP*>			list_;
    typedef std::map<std::string, ALLEGRO_BITMAP*>::iterator	t_iter;
    typedef std::pair<std::string, ALLEGRO_BITMAP*>		t_pair;
  };
}
#endif					// __AL_SPRITER_IMAGE_MANAGER_HH__
