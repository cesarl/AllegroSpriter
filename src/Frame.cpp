#include				"Frame.hh"

using namespace				AlSpriter;

Frame::Frame()
{}

Frame::~Frame()
{}

bool					Frame::parseXml(const rapidxml::xml_node<char> &node,
							std::string const &rootPath)
{
  //read name
  rapidxml::xml_node<char>		*nameNode = node.first_node("name");
  if (!nameNode)
    {
      std::cerr << "Error: Invalid Spriter file: Frame without name!" << std::endl;
      return false;
    }

  this->name_ = nameNode->value();

  //read and create sprites
  for (rapidxml::xml_node<char> *curNode = node.first_node("sprite");
       curNode;
       curNode = curNode->next_sibling("sprite"))
    {
      Sprite				*sprite;

      sprite = new Sprite;
      if (!sprite)
	return false;

      //get <image>
      rapidxml::xml_node<char> *node = curNode->first_node("image");
      if (!node)
	{
	  std::cerr << "Error: Invalid Spriter file: Frame \"" << this->name_ << "\" lacks <image> node!" << std::endl;
	  return false;
	}
      if (!sprite->setBitmap(node->value(), rootPath))
	{
	  return false;
	}

      //get <color> [0x000000 ; 0xffffff]
      node = curNode->first_node("color");
      if(!node)
      	{
      	  std::cerr << "Error: Invalid Spriter file: Frame \"" << this->name_ << "\" lacks <color> node!" << std::endl;
      	  return false;
      	}

      int intColor = atoi(node->value());

      //get <opacity> [0.f ; 100.f]
      node = curNode->first_node("opacity");
      if(!node)
      	{
      	  std::cerr << "Error: Invalid Spriter file: Frame \"" << this->name_ << "\" lacks <opacity> node!" << std::endl;
      	  return false;
      	}
      float opacity = atof(node->value());

      int colorR = (intColor & 0xff0000) >> 16;
      int colorG = (intColor & 0x00ff00) >> 8;
      int colorB = (intColor & 0x0000ff) >> 0;
      int colorA = opacity / 100.f * 255.f;

      sprite->setColor(al_map_rgba(colorR, colorG, colorB, colorA));

      //get <angle> (in degrees, around upper left corner)
      node = curNode->first_node("angle");
      if(!node)
      	{
      	  std::cerr << "Error: Invalid Spriter file: Frame \"" << this->name_ << "\" lacks <angle> node!" << std::endl;
      	  return false;
      	}

      sprite->setRotation(atof(node->value()));

      //get <width> (in pixels)
      node = curNode->first_node("width");
      if(!node)
      	{
      	  std::cerr << "Error: Invalid Spriter file: Frame \"" << this->name_ << "\" lacks <width> node!" << std::endl;
      	  return false;
      	}

      sprite->setWidth(atoi(node->value()));

      //get <height> (in pixels)
      node = curNode->first_node("height");
      if(!node)
      	{
      	  std::cerr << "Error: Invalid Spriter file: Frame \"" << this->name_ << "\" lacks <height> node!" << std::endl;
      	  return false;
      	}
      sprite->setHeight(atof(node->value()));

      // //get <xflip>
      // node = curNode->first_node("xflip");
      // if(!node)
      // 	{
      // 	  sf::err() << "Error: Invalid Spriter file: Frame \"" << mName << "\" lacks <xflip> node!" << std::endl;
      // 	  return false;
      // 	}
      // //            if(atoi(node->value())) width *= -1;

      // //get <yflip>
      // node = curNode->first_node("yflip");
      // if(!node)
      // 	{
      // 	  sf::err() << "Error: Invalid Spriter file: Frame \"" << mName << "\" lacks <yflip> node!" << std::endl;
      // 	  return false;
      // 	}
      // //            if(atoi(node->value())) height *= -1;

      //get <x> (in pixels)
      node = curNode->first_node("x");
      if(!node)
      	{
      	  std::cerr << "Error: Invalid Spriter file: Frame \"" << this->name_ << "\" lacks <x> node!" << std::endl;
      	  return false;
      	}
      sprite->setX(atoi(node->value()));

      //get <y> (in pixels)
      node = curNode->first_node("y");
      if(!node)
      	{
      	  std::cerr << "Error: Invalid Spriter file: Frame \"" << this->name_ << "\" lacks <y> node!" << std::endl;
      	  return false;
      	}
      sprite->setY(atoi(node->value()));

      // //create Sprite
      // //width/height is negative if the axis is flipped, in that case we need to reposition the origin to upper left
      // sprite->setOrigin((width < 0 ? width : 0), (height < 0 ? height : 0));
      // sprite->setPosition(x, y);
      // sprite->setScale(width / float(tex->getSize().x), height / float(tex->getSize().y));
      // sprite->setRotation(-angle);
      // sprite->setColor(color);
      this->list_.push_back(sprite);
    }
  return true;
}

const std::string			&Frame::getName() const
{
  return this->name_;
}

void					Frame::draw() const
{
  t_const_iter				it;

  it = this->list_.begin();
  while (it != this->list_.end())
    {
      (*it)->draw();
      ++it;
    }
}
