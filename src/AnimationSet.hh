#ifndef					__AL_SPRITER_ANIMATION_SET_HH__
# define				__AL_SPRITER_ANIMATION_SET_HH__

#include				<string>
#include				<fstream>
#include				<vector>
#include				<map>
#include				<iostream>
#include				<rapidxml.hpp>
#include				"Frame.hh"
#include				"Animation.hh"

namespace				AlSpriter
{
  class					AnimationSet
  {
  public:
    AnimationSet();
    ~AnimationSet();
    bool				loadFromFile(std::string const & path, std::string const & rootPath);
    bool				parseXml(std::string const & str, std::string const & rootPath);
    void				draw() const;
    void				update(float time);
  private:
    std::map<std::string, Frame*>	frameList_;
    std::map<std::string, Animation*>	animationList_;
typedef std::map<std::string, Animation*>			t_animationList;
    t_animationList::iterator		currentAnimation_;
    typedef std::map<std::string, Frame*>::iterator		t_frame_iter;
    typedef std::pair<std::string, Frame*>			t_frame_pair;
    typedef std::map<std::string, Animation*>::iterator		t_animation_iter;
    typedef std::pair<std::string, Animation*>			t_animation_pair;
  };
}

#endif					// __AL_SPRITER_ANIMATION_SET_HH__
