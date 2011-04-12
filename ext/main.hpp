#ifndef __RubyOgreMain_H__
#define __RubyOgreMain_H__

#include <ruby.h>
#include <Ogre.h>

template <typename T>
VALUE wrap(T *arg){ return Qnil;};
template <typename T>
VALUE wrap(T arg){ return Qnil;};
template <typename T>
T wrap(const VALUE &arg){};

#endif /* __RubyOgreMain_H__ */

