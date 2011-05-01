#ifndef __RubyOgreResourceGroup_H__
#define __RubyOgreResourceGroup_H__

#include "main.hpp"
void Init_OgreResourceGroup(VALUE rb_mOgre);
extern VALUE rb_cOgreResourceGroup;

struct ResourceGroup
{
	std::string name;
};

template <>
inline VALUE wrap< ResourceGroup >(ResourceGroup *resgroup )
{
	return Data_Wrap_Struct(rb_cOgreResourceGroup, NULL, free, resgroup);
}

template <>
inline ResourceGroup* wrap< ResourceGroup* >(const VALUE &vresgroup)
{
	if ( ! rb_obj_is_kind_of(vresgroup, rb_cOgreResourceGroup) )
		return NULL;
	ResourceGroup *resgroup;
  Data_Get_Struct( vresgroup, ResourceGroup, resgroup);
	return resgroup;
}
#endif /* __RubyOgreResourceGroup_H__ */
