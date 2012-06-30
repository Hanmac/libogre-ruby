#ifndef __RubyOgreDegree_H__
#define __RubyOgreDegree_H__

#include "main.hpp"
extern VALUE rb_cOgreDegree;
void Init_OgreDegree(VALUE rb_mOgre);


//#include "ogreradian.hpp"
template <>
VALUE wrap< Ogre::Degree >(Ogre::Degree *degree );

template <>
Ogre::Degree wrap< Ogre::Degree >(const VALUE &vdegree);
#endif /* __RubyOgreDegree_H__ */
