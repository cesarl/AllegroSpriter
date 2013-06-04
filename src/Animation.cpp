#include				"Animation.hh"

using namespace				AlSpriter;

Animation::Animation()
{}

Animation::~Animation()
{}

bool					Animation::parseXml(const rapidxml::xml_node<char> &node,
							    std::map<std::string, Frame*> const &frameList)
{
  //read name
  rapidxml::xml_node<char>* nameNode = node.first_node("name");

  if(!nameNode || *nameNode->value() == '\0')
    {
      std::cerr << "Error: Invalid Spriter file: Animation contains no name!" << std::endl;
      return false;
    }

  this->name_ = nameNode->value();

  //load KeyFrames
  for(rapidxml::xml_node<char>* curNode = node.first_node("frame"); curNode; curNode = curNode->next_sibling("frame"))
    {
      rapidxml::xml_node<char>	*nameNode = curNode->first_node("name");

      if(!nameNode)
	{
	  //no need to clean up, this animation will be deleted due to failed loading anyway.
	  std::cerr << "Error: Invalid Spriter file: Animation \"" << this->name_ << "\" contains a Frame without name!" << std::endl;
	  return false;
	}

      std::string			frameName(nameNode->value());
      rapidxml::xml_node<char>	*durationNode = curNode->first_node("duration");

      if(!durationNode)
	{
	  std::cerr << "Error: Invalid Spriter file: Animation \"" << this->name_ << "\" Frame \"" << frameName << "\" has no duration!" << std::endl;
	  return false;
	}

      t_pair			keyframe;

      keyframe.first = atof(durationNode->value());

      //only use KeyFrames with duration > 0
      if(keyframe.first <= 0)
	{
	  std::cerr
	    << "Warning: Invalid Spriter file: Animation \""
	    << this->name_ << "\" Frame \"" << frameName
	    << "\" has invalid duration "
	    << keyframe.first << "!"
	    << std::endl;
	  continue;
	}

      //TODO: Remove once the time is *actually* in milliseconds, not in centiseconds.
      keyframe.first *= 10;

      std::map<std::string, Frame*>::const_iterator framePos;

      framePos = frameList.find(frameName);

      if(framePos == frameList.end())
	{
	  std::cerr
	    << "Error: Invalid Spriter file: Animation \""
	    << this->name_
	    << "\" references non-existant Frame \""
	    << frameName
	    << "\"!"
	    << std::endl;
	  return false;
	}

      keyframe.second = framePos->second;
      this->list_.push_back(keyframe);
    }

  if(this->list_.empty())
    {
      std::cerr
	<< "Error: Invalid Spriter file: Animation \""
	<< this->name_
	<< "\" contains no frames longer than 0ms!"
	<< std::endl;
      return false;
    }
  this->currentFrame_ = this->list_.begin();
  return true;
}

const std::string			&Animation::getName() const
{
  return this->name_;
}

bool					Animation::isEmpty() const
{
  return this->list_.empty();
}

void					Animation::draw() const
{
  this->currentFrame_->second->draw();
}

void					Animation::update(float time)
{
  ++this->currentFrame_;
  if (this->currentFrame_ == this->list_.end())
    this->currentFrame_ = this->list_.begin();
  (void)(time);
}
