/*
 * ogregpuprogram.hpp
 *
 *  Created on: 01.07.2012
 *      Author: hanmac
 */

#ifndef __RubyOgreGpuProgram_H__
#define __RubyOgreGpuProgram_H__

#include "main.hpp"
void Init_OgreGpuProgram(VALUE rb_mOgre);
extern VALUE rb_cOgreGpuProgram;


template <>
VALUE wrap< Ogre::GpuProgramPtr >(const Ogre::GpuProgramPtr &gpupogram );

template <>
Ogre::GpuProgram* wrap< Ogre::GpuProgram* >(const VALUE &vgpuprogram);

#endif /* __RubyOgreGpuProgram_H__ */
