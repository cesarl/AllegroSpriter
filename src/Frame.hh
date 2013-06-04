#ifndef					__AL_SPRITER_FRAME_HH__
# define				__AL_SPRITER_FRAME_HH__

#include				<rapidxml.hpp>
#include				<string>
#include				<iostream>
#include				<cstdlib>
#include				<vector>
#include				"Sprite.hh"

namespace				AlSpriter
{
  class					Frame
  {
  public:
    Frame();
    ~Frame();
    bool				parseXml(const rapidxml::xml_node<char>& node,
						 std::string const &rootPath);
    const std::string			&getName() const;
    void				draw() const;
  private:
    std::string				name_;
    std::vector<Sprite*>		list_;
    typedef std::vector<Sprite*>::iterator		t_iter;
    typedef std::vector<Sprite*>::const_iterator	t_const_iter;
  };
}
#endif					// __AL_SPRITER_FRAME_HH__
