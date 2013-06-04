#ifndef					__AL_SPRITER_ANIMATION_HH__
# define				__AL_SPRITER_ANIMATION_HH__

#include				<rapidxml.hpp>
#include				<string>
#include				<iostream>
#include				<map>
#include				<vector>
#include				"Frame.hh"

namespace				AlSpriter
{
  class					Animation
  {
  public:
    Animation();
    ~Animation();
    bool				parseXml(const rapidxml::xml_node<char>& node,
						   std::map<std::string, Frame*> const &frameList);
    const std::string			&getName() const;
    bool				isEmpty() const;
    void				draw() const;
    void				update(float time);
  private:
    std::string				name_;
    typedef std::vector<std::pair<float, Frame*> >		t_frameList;
    t_frameList::iterator		currentFrame_;
    std::vector<std::pair<float, Frame*> >			list_;
    typedef std::vector<std::pair<float, Frame*> >::iterator	t_iter;
    typedef std::pair<float, Frame*>				t_pair;
  };
}
#endif					// __AL_SPRITER_ANIMATION_HH__
