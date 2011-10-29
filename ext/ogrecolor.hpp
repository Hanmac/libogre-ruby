#ifndef __RubyOgreColor_H__
#define __RubyOgreColor_H__

#include "main.hpp"
void Init_OgreColor(VALUE rb_mOgre);
extern VALUE rb_cOgreColor;


template <>
inline VALUE wrap< Ogre::ColourValue >(Ogre::ColourValue *color )
{
	return Data_Wrap_Struct(rb_cOgreColor, NULL, free, color);
}

template <>
inline Ogre::ColourValue* wrap< Ogre::ColourValue* >(const VALUE &vcolor)
{
	if (rb_obj_is_kind_of(vcolor, rb_cOgreColor)){
		Ogre::ColourValue *color;
		Data_Get_Struct( vcolor, Ogre::ColourValue, color);
		return color;
	}else if(rb_respond_to(vcolor,rb_intern("red")) && 
	 rb_respond_to(vcolor,rb_intern("blue")) &&
	 rb_respond_to(vcolor,rb_intern("green")) &&
	 rb_respond_to(vcolor,rb_intern("alpha"))){
	 double temp;
	 Ogre::ColourValue *color = new Ogre::ColourValue;
	 temp = NUM2DBL(rb_funcall(vcolor,rb_intern("red"),0));
	 if(temp > 1.0)
	 	temp /=256;
	 color->r = temp;
	 temp = NUM2DBL(rb_funcall(vcolor,rb_intern("blue"),0));
	 if(temp > 1.0)
	 	temp /=256;
	 color->b = temp;
	 
	 temp = NUM2DBL(rb_funcall(vcolor,rb_intern("green"),0));
	 if(temp > 1.0)
	 	temp /=256;
	 color->g = temp;
	 
	 temp = NUM2DBL(rb_funcall(vcolor,rb_intern("alpha"),0));
	 if(temp > 1.0)
	 	temp /=256;
	 color->a = temp;
	 return color;
	}else{
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreColor),rb_obj_classname(vcolor));
		return NULL;
	}
}
template <>
inline Ogre::ColourValue wrap< Ogre::ColourValue >(const VALUE &vcolor)
{
	return *wrap< Ogre::ColourValue* >(vcolor);
}
#endif /* __RubyOgreColor_H__ */
