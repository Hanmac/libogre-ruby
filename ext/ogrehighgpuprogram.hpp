/*
 * ogrehighgpuprogram.hpp
 *
 *  Created on: 29.08.2012
 *      Author: hanmac
 */

#ifndef __RubyHighOgreGpuProgram_H__
#define __RubyHighOgreGpuProgram_H__

#include "main.hpp"
void Init_OgreHighGpuProgram(VALUE rb_mOgre);
extern VALUE rb_cOgreHighGpuProgram;


template <>
VALUE wrap< Ogre::HighLevelGpuProgramPtr >(const Ogre::HighLevelGpuProgramPtr &gpupogram );

#endif /* __RubyOgreGpuProgram_H__ */
