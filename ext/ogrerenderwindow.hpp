#ifndef __RubyOgreRenderWindow_H__
#define __RubyOgreRenderWindow_H__

#include "main.hpp"
void Init_OgreRenderWindow(VALUE rb_mOgre);
extern VALUE rb_cOgreRenderWindow;


template <>
inline VALUE wrap< Ogre::RenderWindow >(Ogre::RenderWindow *window )
{
	return Data_Wrap_Struct(rb_cOgreRenderWindow, NULL, NULL, window);
}

template <>
inline Ogre::RenderWindow* wrap< Ogre::RenderWindow* >(const VALUE &vwindow)
{
	if ( ! rb_obj_is_kind_of(vwindow, rb_cOgreRenderWindow) )
		return NULL;
	Ogre::RenderWindow *window;
  Data_Get_Struct( vwindow, Ogre::RenderWindow, window);
	return window;
}
#endif /* __RubyOgreRenderWindow_H__ */
