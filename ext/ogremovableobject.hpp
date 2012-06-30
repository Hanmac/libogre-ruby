#ifndef __RubyOgreMovableObject_H__
#define __RubyOgreMovableObject_H__

#include "main.hpp"
void Init_OgreMovableObject(VALUE rb_mOgre);
extern VALUE rb_mOgreMovableObject;

#include "ogrelight.hpp"
#include "ogreentity.hpp"
#include "ogreparticlesystem.hpp"
#include "ogrebillboardset.hpp"
#include "ogrebillboardchain.hpp"
#include "ogremovableplane.hpp"
#include "ogrefrustum.hpp"

#endif /* __RubyOgreMovableObject_H__ */
