#ifndef __RubyOgreFileInfo_H__
#define __RubyOgreFileInfo_H__

#include "main.hpp"
void Init_OgreFileInfo(VALUE rb_mOgre);
extern VALUE rb_cOgreFileInfo;


template <>
inline VALUE wrap< Ogre::FileInfo >(Ogre::FileInfo *fileinfo )
{
	return Data_Wrap_Struct(rb_cOgreFileInfo, NULL, free, fileinfo);
}
template <>
inline VALUE wrap< Ogre::FileInfo >(Ogre::FileInfo fileinfo )
{
	Ogre::FileInfo *temp = new Ogre::FileInfo(fileinfo);
	return wrap(temp);
}
template <>
inline VALUE wrap< Ogre::FileInfoList >(Ogre::FileInfoList vec )
{
	VALUE result = rb_ary_new();
	Ogre::FileInfoList::iterator it;
	for ( it=vec.begin() ; it < vec.end(); it++ )
		rb_ary_push(result,wrap(*it));
	return result;
}

template <>
inline VALUE wrap< Ogre::FileInfoListPtr >(Ogre::FileInfoListPtr vec )
{
	VALUE result = rb_ary_new();
	Ogre::FileInfoList::iterator it;
	for ( it=vec->begin() ; it < vec->end(); it++ )
		rb_ary_push(result,wrap(*it));
	return result;
}


template <>
inline Ogre::FileInfo* wrap< Ogre::FileInfo* >(const VALUE &vfileinfo)
{
	if ( ! rb_obj_is_kind_of(vfileinfo, rb_cOgreFileInfo) )
		return NULL;
	Ogre::FileInfo *fileinfo;
  Data_Get_Struct( vfileinfo, Ogre::FileInfo, fileinfo);
	return fileinfo;
}
#endif /* __RubyOgreFileInfo_H__ */
