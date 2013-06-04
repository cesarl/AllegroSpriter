#include				"Sprite.hh"

using namespace				AlSpriter;

Sprite::Sprite() :
  x_(0),
  y_(0),
  w_(0),
  h_(0),
  rotation_(0.0f),
  color_(al_map_rgba(255, 255, 255, 255)),
  bitmap_(NULL)
{}

Sprite::~Sprite()
{}

void					Sprite::initialize(int x,
							   int y,
							   int w,
							   int h,
							   float rotation,
							   ALLEGRO_COLOR const & color,
							   ALLEGRO_BITMAP * bitmap)
{
  this->x_ = x;
  this->y_ = y;
  this->w_ = w;
  this->h_ = h;
  this->rotation_ = rotation * ALLEGRO_PI / 180;
  this->color_ = color;
  this->bitmap_ = bitmap;
}

bool					Sprite::setBitmap(std::string const & path,
							  std::string const & rootPath)
{
  this->bitmap_ = ImageManager::getInstance().load(rootPath + path.c_str());
  if (!this->bitmap_)
    return false;
  return true;
}

void					Sprite::setColor(ALLEGRO_COLOR const & color)
{
  this->color_ = color;
}

void					Sprite::setRotation(float angle)
{
  this->rotation_ = angle * ALLEGRO_PI / 180;
}

void					Sprite::setWidth(int width)
{
  this->w_ = width;
}

void					Sprite::setHeight(int height)
{
  this->h_ = height;
}

void					Sprite::setX(int x)
{
  this->x_ = x;
}

void					Sprite::setY(int y)
{
  this->y_ = y;
}

void					Sprite::draw() const
{
  al_draw_tinted_scaled_rotated_bitmap(this->bitmap_,
				       this->color_,
				       0, 0,
				       300 + this->x_, 300 + this->y_,
				       1.0f, 1.0f,
				       this->rotation_, 0);
  std::cout << this->x_ << " " << this->y_ << std::endl;
}
