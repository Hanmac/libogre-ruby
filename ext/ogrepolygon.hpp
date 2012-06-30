#ifndef __RubyOgrePolygon_H__
#define __RubyOgrePolygon_H__

#include "main.hpp"
void Init_OgrePolygon(VALUE rb_mOgre);
extern VALUE rb_cOgrePolygon;


template <>
VALUE wrap< Ogre::Polygon >(Ogre::Polygon *polygon );

template <>
VALUE wrap< Ogre::Polygon::EdgeMap >(const Ogre::Polygon::EdgeMap &edge );

#endif /* __RubyOgrePolygon_H__ */
