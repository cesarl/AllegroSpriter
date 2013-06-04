#include				"ImageManager.hh"

using namespace				AlSpriter;

ImageManager::ImageManager()
{}

ImageManager::~ImageManager()
{
  t_iter				it;

  it = this->list_.begin();
  while (it != this->list_.end())
    {
      al_destroy_bitmap(it->second);
      ++it;
    }
  this->list_.clear();
}

ImageManager				&ImageManager::getInstance()
{
  static ImageManager			that;

  return that;
}

ALLEGRO_BITMAP				*ImageManager::load(std::string const & path)
{
  t_iter				it;
  ALLEGRO_BITMAP			*bmp;

  it = this->list_.find(path);
  if (it != this->list_.end())
    return it->second;
  bmp = al_load_bitmap(path.c_str());
  if (!bmp)
    {
      std::cerr << "Error : ImageManager::load : Bitmap " << path << " cannot be loaded." << std::endl;
      return NULL;
    }
  this->list_.insert(t_pair(path, bmp));
  return bmp;
}

ALLEGRO_BITMAP				*ImageManager::get(std::string const & path)
{
  t_iter				it;

  it = this->list_.find(path);
  if (it != this->list_.end())
    return it->second;
  return NULL;
}
