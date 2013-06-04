#include				"AnimationSet.hh"

using namespace				AlSpriter;

AnimationSet::AnimationSet()
{}

AnimationSet::~AnimationSet()
{}

bool					AnimationSet::loadFromFile(std::string const & path, std::string const & rootPath)
{
  std::ifstream				file(path.c_str());
  std::string				content;

  if (file.fail())
    {
      std::cerr << "error : AnimationSet::loadFromFile : " << path << " could not be opened." << std::endl;
      return false;
    }
  file.seekg(0, std::ios::end);
  content.reserve(file.tellg());
  file.seekg(0, std::ios::beg);
  content.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  file.close();
  return this->parseXml(content, rootPath);
}

bool					AnimationSet::parseXml(std::string const & str,
							       std::string const & rootPath)
{
  std::vector<char>			xmlString;
  rapidxml::xml_document<char>		xml;
  rapidxml::xml_node<char>		*rootNode;
  Frame					*frame;


  // we copy str content to a vector of char that rapidxml can modify
  xmlString.reserve(str.length() + 1);
  xmlString.assign(str.begin(), str.end());
  xmlString.push_back('\0');

  try
    {
      xml.parse<0>(xmlString.data());

      rootNode = xml.first_node("spriterdata");
      if(!rootNode)
	{
	  std::cerr << "Error: No valid Spriter file (lacks spriterdata node)!" << std::endl;
	  return false;
	}

      //load frames
      for(rapidxml::xml_node<char>* node = rootNode->first_node("frame"); node; node = node->next_sibling("frame"))
	{
	  frame = new Frame();
	  if (!frame)
	    return false;
      	  if(!frame->parseXml(*node, rootPath))
      	    {
      	      delete frame;
      	      // releaseFrames();
      	      // releaseTextures();
      	      return false;
      	    }
	  this->frameList_.insert(t_frame_pair(frame->getName(), frame));
      	}

      //any frames at all?
      if(this->frameList_.empty())
      	{
      	  std::cerr << "Warning: No frames in Spriter file!" << std::endl;
      	}

      //find animation set - in the beta file format there should be only one

      rapidxml::xml_node<char>* animationSetNode = rootNode->first_node("char");
      if(!animationSetNode)
      	{
      	  std::cerr << "Warning: No character in Spriter file!" << std::endl;
      	  // releaseFrames();
      	  // releaseTextures();
      	  return true;
      	}
      if(animationSetNode->next_sibling("char"))
      	{
      	  std::cerr << "Warning: More than one character in Spriter file! Only first one is used." << std::endl;
      	}

      //load animations
      for(rapidxml::xml_node<char>* node = animationSetNode->first_node("anim"); node; node = node->next_sibling("anim"))
      	{
      	  Animation* anim = new Animation();
      	  if(!anim->parseXml(*node, this->frameList_))
      	    {
      	      // releaseAnimations();
      	      // releaseFrames();
      	      // releaseTextures();
      	      return false;
      	    }

      	  //warn about empty animations, don't add them
      	  if(anim->isEmpty())
      	    {
      	      std::cerr << "Warning: Empty animation \"" << anim->getName() << " in Spriter file!" << std::endl;
      	      delete anim;
      	      continue;
      	    }
      	  this->animationList_.insert(t_animation_pair(anim->getName(), anim));
      	}
      //even if there were no animations we succeeded in loading nothing.
      if(this->animationList_.empty())
      	{
      	  //let's warn about this - it's probably unintended.
      	  std::cerr << "Warning: No animations in Spriter file!" << std::endl;
      	  // releaseFrames();
      	  // releaseTextures();
      	  return true;
      	}

      //set current animation to first one available
      this->currentAnimation_ = this->animationList_.begin();
    }
  catch(const rapidxml::parse_error& err)
    {
      std::cerr << "Error parsing XML file: " << err.what();
      return false;
    }
  return true;
}

void					AnimationSet::draw() const
{
  this->currentAnimation_->second->draw();
}

void					AnimationSet::update(float time)
{
  this->currentAnimation_->second->update(time);
}
