#ifndef __RubyOgreResourceGroup_H__
#define __RubyOgreResourceGroup_H__

#include "main.hpp"
void Init_OgreResourceGroup(VALUE rb_mOgre);
extern VALUE rb_cOgreResourceGroup;

struct RubyResourceGroup
{
	std::string name;
};

template <>
VALUE wrap< RubyResourceGroup >(RubyResourceGroup *resgroup );

template <>
RubyResourceGroup* wrap< RubyResourceGroup* >(const VALUE &vresgroup);
#endif /* __RubyOgreResourceGroup_H__ */
