#ifndef __RubyOgrePlane_H__
#define __RubyOgrePlane_H__

#include "main.hpp"
#include "ogremovableplane.hpp"
void Init_OgrePlane(VALUE rb_mOgre);
extern VALUE rb_cOgrePlane;

template <>
VALUE wrap< Ogre::Plane >(Ogre::Plane *plane );

template <>
VALUE wrap< Ogre::Plane::Side >(const Ogre::Plane::Side &side );

template <>
Ogre::Plane::Side wrap< Ogre::Plane::Side >(const VALUE &arg);

template <>
Ogre::Plane* wrap< Ogre::Plane* >(const VALUE &vplane);

template <>
Ogre::Plane wrap< Ogre::Plane >(const VALUE &vplane);

#endif /* __RubyOgrePlane_H__ */
