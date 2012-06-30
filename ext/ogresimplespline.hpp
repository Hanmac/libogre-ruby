#ifndef __RubyOgreSimpleSpline_H__
#define __RubyOgreSimpleSpline_H__

#include "main.hpp"
void Init_OgreSimpleSpline(VALUE rb_mOgre);
extern VALUE rb_cOgreSimpleSpline;

template <>
VALUE wrap< Ogre::SimpleSpline >(Ogre::SimpleSpline *spline );
#endif /* __RubyOgreSimpleSpline_H__ */
