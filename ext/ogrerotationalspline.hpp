#ifndef __RubyOgreRotationalSpline_H__
#define __RubyOgreRotationalSpline_H__

#include "main.hpp"
void Init_OgreRotationalSpline(VALUE rb_mOgre);
extern VALUE rb_cOgreRotationalSpline;


template <>
VALUE wrap< Ogre::RotationalSpline >(Ogre::RotationalSpline *spline );
#endif /* __RubyOgreRotationalSpline_H__ */
