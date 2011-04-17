#include "ogrecolor.hpp"

#define _self wrap<Ogre::ColourValue*>(self)
VALUE rb_cOgreColor;

VALUE OgreColor_alloc(VALUE self)
{
	Ogre::ColourValue *temp = new Ogre::ColourValue;
	return wrap(temp);
}
/*:nodoc:
*/
VALUE OgreColor_get_red(VALUE self)
{
	return DBL2NUM(_self->r);
}
/*:nodoc:
*/
VALUE OgreColor_get_green(VALUE self)
{
	return DBL2NUM(_self->g);
}
/*:nodoc:
*/
VALUE OgreColor_get_blue(VALUE self)
{
	return DBL2NUM(_self->b);
}
/*:nodoc:
*/
VALUE OgreColor_get_alpha(VALUE self)
{
	return DBL2NUM(_self->a);
}
/*:nodoc:
*/
VALUE OgreColor_set_red(VALUE self,VALUE c)
{
	_self->r = NUM2DBL(c);
	_self->saturate();
	return c;
}
/*:nodoc:
*/
VALUE OgreColor_set_green(VALUE self,VALUE c)
{
	_self->g = NUM2DBL(c);
	_self->saturate();
	return c;
}
/*:nodoc:
*/
VALUE OgreColor_set_blue(VALUE self,VALUE c)
{
	_self->b = NUM2DBL(c);
	_self->saturate();
	return c;
}
/*:nodoc:
*/
VALUE OgreColor_set_alpha(VALUE self,VALUE c)
{
	_self->a = NUM2DBL(c);
	_self->saturate();
	return c;
}
/*
 * call-seq:
 *   Color.new(red,green,blue[,alpha])
 * 
 * creates a new Color Object. 
*/
VALUE OgreColor_initialize(int argc,VALUE *argv,VALUE self)
{
	VALUE red,green,blue,alpha;
	rb_scan_args(argc, argv, "31",&red,&green,&blue,&alpha);
	OgreColor_set_red(self,red);
	OgreColor_set_green(self,green);
	OgreColor_set_blue(self,blue);
	if(!NIL_P(alpha))
		OgreColor_set_alpha(self,alpha);
	return self;
}
/*
 * call-seq:
 *   color + other_color -> new_color
 * 
 * adds the colors
 * ===Return value
 * Color
*/
VALUE OgreColor_plus(VALUE self,VALUE val)
{
	if(rb_obj_is_kind_of(val,rb_cOgreColor)){
		Ogre::ColourValue temp = *_self + *wrap<Ogre::ColourValue*>(val);
		temp.saturate();
		return wrap(temp);
	}else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreColor),rb_obj_classname(val));
}
/*
 * call-seq:
 *   color - other_color -> new_color
 * 
 * minus the colors
 * ===Return value
 * Color
*/
VALUE OgreColor_minus(VALUE self,VALUE val)
{
	if(rb_obj_is_kind_of(val,rb_cOgreColor)){
		Ogre::ColourValue temp = *_self - *wrap<Ogre::ColourValue*>(val);
		temp.saturate();
		return wrap(temp);
	}else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreColor),rb_obj_classname(val));
}
/*
 * call-seq:
 *   * other_color -> new_color
 *   * Numeric -> new_color
 *
 * multipicate the colors
 * ===Return value
 * Color
*/
VALUE OgreColor_mal(VALUE self,VALUE val)
{
	if(rb_obj_is_kind_of(val,rb_cOgreColor))
		return wrap(*_self * *wrap<Ogre::ColourValue*>(val));
	else
		return wrap(*_self * NUM2DBL(val));
}
/*
 * call-seq:
 *   color / other_color -> new_color
 *   color / Numeric -> new_color
 * 
 * devide the colors
 * ===Return value
 * Color
*/
VALUE OgreColor_durch(VALUE self,VALUE val)
{
	if(rb_obj_is_kind_of(val,rb_cOgreColor))
		return wrap(*_self / *wrap<Ogre::ColourValue*>(val));
	else
		return wrap(*_self / NUM2DBL(val));
}
/*:nodoc:
*/
VALUE OgreColor_get_hue(VALUE self)
{
	Ogre::Real hue,saturation,brightness;
	_self->getHSB(&hue, &saturation, &brightness);
	return DBL2NUM(hue);
}
/*:nodoc:
*/
VALUE OgreColor_get_saturation(VALUE self)
{
	Ogre::Real hue,saturation,brightness;
	_self->getHSB(&hue, &saturation, &brightness);
	return DBL2NUM(saturation);
}
/*:nodoc:
*/
VALUE OgreColor_get_brightness(VALUE self)
{
	Ogre::Real hue,saturation,brightness;
	_self->getHSB(&hue, &saturation, &brightness);
	return DBL2NUM(brightness);
}
/*:nodoc:
*/
VALUE OgreColor_set_hue(VALUE self,VALUE val)
{
	Ogre::Real hue,saturation,brightness;
	_self->getHSB(&hue, &saturation, &brightness);
	_self->setHSB(NUM2DBL(val), saturation, brightness);
	_self->saturate();
	return val;
}
/*:nodoc:
*/
VALUE OgreColor_set_saturation(VALUE self,VALUE val)
{
	Ogre::Real hue,saturation,brightness;
	_self->getHSB(&hue, &saturation, &brightness);
	_self->setHSB(hue, NUM2DBL(val), brightness);
	_self->saturate();
	return val;
}
/*:nodoc:
*/
VALUE OgreColor_set_brightness(VALUE self,VALUE val)
{
	Ogre::Real hue,saturation,brightness;
	_self->getHSB(&hue, &saturation, &brightness);
	_self->setHSB(hue, saturation, NUM2DBL(val));
	_self->saturate();
	return val;
}
/*:nodoc:
*/
VALUE OgreColor_get_hsb(VALUE self)
{
	Ogre::Real hue,saturation,brightness;
	_self->getHSB(&hue, &saturation, &brightness);
	VALUE result = rb_ary_new();
	rb_ary_push(result,DBL2NUM(hue));
	rb_ary_push(result,DBL2NUM(saturation));
	rb_ary_push(result,DBL2NUM(brightness));
	return result;
}
/*:nodoc:
*/
VALUE OgreColor_set_hsb(VALUE self,VALUE val)
{
	if(rb_obj_is_kind_of(val,rb_cArray))
		if(RARRAY_LEN(val) == 3){
			_self->setHSB(NUM2DBL(RARRAY_PTR(val)[0]), NUM2DBL(RARRAY_PTR(val)[1]), NUM2DBL(RARRAY_PTR(val)[2]));
			_self->saturate();
		}else
			rb_raise(rb_eTypeError,"Exepted Arraysize 3 got %ld!",RARRAY_LEN(val));
	else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cArray),rb_obj_classname(val));
	return val;
}
/*:nodoc:
*/
VALUE OgreColor_get_rgba(VALUE self)
{
	return ULONG2NUM(_self->getAsRGBA());
}
/*:nodoc:
*/
VALUE OgreColor_get_argb(VALUE self)
{
	return ULONG2NUM(_self->getAsARGB());
}
/*:nodoc:
*/
VALUE OgreColor_get_bgra(VALUE self)
{
	return ULONG2NUM(_self->getAsBGRA());
}
/*:nodoc:
*/
VALUE OgreColor_get_abgr(VALUE self)
{
	return ULONG2NUM(_self->getAsABGR());
}
/*:nodoc:
*/
VALUE OgreColor_set_rgba(VALUE self,VALUE val)
{
	_self->setAsRGBA(NUM2ULONG(val));
	return val;
}
/*:nodoc:
*/
VALUE OgreColor_set_argb(VALUE self,VALUE val)
{
	_self->setAsARGB(NUM2ULONG(val));
	return val;
}
/*:nodoc:
*/
VALUE OgreColor_set_bgra(VALUE self,VALUE val)
{
	_self->setAsBGRA(NUM2ULONG(val));
	return val;
}
/*:nodoc:
*/
VALUE OgreColor_set_abgr(VALUE self,VALUE val)
{
	_self->setAsABGR(NUM2ULONG(val));
	return val;
}
/*
 * call-seq:
 *   color.inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE OgreColor_inspect(VALUE self)
{
	VALUE array[6];
	array[0]=rb_str_new2("#<%s:(%f, %f, %f, %f)>");
	array[1]=rb_class_of(self);
	array[2]=OgreColor_get_red(self);
	array[3]=OgreColor_get_green(self);
	array[4]=OgreColor_get_blue(self);
	array[5]=OgreColor_get_alpha(self);
	return rb_f_sprintf(6,array);
}
/*
* call-seq:
 *   color == other -> true or false 
 * 
 * 
 * ===Return value
 * boolean
*/
VALUE OgreColor_equal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreColor))
		return *_self == *wrap<Ogre::ColourValue*>(other) ? Qtrue : Qfalse;
	else
		return Qfalse;
}
/*
* call-seq:
 *   color != other -> true or false 
 * 
 * 
 * ===Return value
 * boolean
*/
VALUE OgreColor_nequal(VALUE self,VALUE other)
{
	if(rb_obj_is_kind_of(other,rb_cOgreColor))
		return *_self != *wrap<Ogre::ColourValue*>(other) ? Qtrue : Qfalse;
	else
		return Qtrue;
}
/*
 * call-seq:
 *   color.hash -> Integer
 * 
 * hash from the combined Color values.
 * ===Return value
 * Integer
*/
VALUE OgreColor_hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,OgreColor_get_red(self));
	rb_ary_push(result,OgreColor_get_green(self));
	rb_ary_push(result,OgreColor_get_blue(self));
	rb_ary_push(result,OgreColor_get_alpha(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*:nodoc:
*/
VALUE OgreColor_marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,OgreColor_get_red(self));
	rb_ary_push(result,OgreColor_get_green(self));
	rb_ary_push(result,OgreColor_get_blue(self));
	rb_ary_push(result,OgreColor_get_alpha(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("dddd"));
}
/*:nodoc:
*/
VALUE OgreColor_marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("dddd"));
	OgreColor_set_alpha(self,rb_ary_pop(result));
	OgreColor_set_blue(self,rb_ary_pop(result));
	OgreColor_set_green(self,rb_ary_pop(result));
	OgreColor_set_red(self,rb_ary_pop(result));
	return self;
}
/*


*/
VALUE Numeric_mal_OgreColor(VALUE self,VALUE val)
{
	if(rb_obj_is_kind_of(val,rb_cOgreColor))
		return wrap(NUM2DBL(self) * *wrap<Ogre::ColourValue*>(val));
	else
		return rb_funcall(self,rb_intern("malOgreColor"),1,val);
}
/*
 * Document-class: Ogre::Color
 * 
 * This class represents an Color. 
*/ 

/* Document-attr: red
 * returns the red value of Color. */
/* Document-attr: blue
 * returns the blue value of Color. */
/* Document-attr: green
 * returns the green value of Color. */
/* Document-attr: alpha
 * returns the alpha value of Color. */
/* Document-attr: hue
 * returns the hue value of Color. */
/* Document-attr: saturation
 * returns the saturation value of Color. */
/* Document-attr: brightness
 * returns the brightness value of Color. */
/* Document-attr: hsb
 * returns the hsb Array [hue,saturation,brightness] of Color. */
/* Document-attr: rgba
 * returns the rgba value as 32Bit of Color. */
/* Document-attr: abgr
 * returns the abgr value as 32Bit of Color. */
/* Document-attr: bgra
 * returns the bgra value as 32Bit of Color. */
/* Document-attr: argb
 * returns the argb value as 32Bit of Color. */

void Init_OgreColor(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	
	rb_define_attr(rb_cOgreColor,"red",1,1);
	rb_define_attr(rb_cOgreColor,"blue",1,1);
	rb_define_attr(rb_cOgreColor,"green",1,1);
	rb_define_attr(rb_cOgreColor,"alpha",1,1);

	rb_define_attr(rb_cOgreColor,"hue",1,1);
	rb_define_attr(rb_cOgreColor,"saturation",1,1);
	rb_define_attr(rb_cOgreColor,"brightness",1,1);
	
	rb_define_attr(rb_cOgreColor,"hsb",1,1);
	
	rb_define_attr(rb_cOgreColor,"rgba",1,1);
	rb_define_attr(rb_cOgreColor,"argb",1,1);
	rb_define_attr(rb_cOgreColor,"bgra",1,1);
	rb_define_attr(rb_cOgreColor,"argb",1,1);

#endif
	rb_cOgreColor = rb_define_class_under(rb_mOgre,"Color",rb_cObject);
	rb_define_alloc_func(rb_cOgreColor,OgreColor_alloc);
	
	rb_define_method(rb_cOgreColor,"initialize",RUBY_METHOD_FUNC(OgreColor_initialize),-1);
	
	rb_define_method(rb_cOgreColor,"red",RUBY_METHOD_FUNC(OgreColor_get_red),0);
	rb_define_method(rb_cOgreColor,"blue",RUBY_METHOD_FUNC(OgreColor_get_blue),0);
	rb_define_method(rb_cOgreColor,"green",RUBY_METHOD_FUNC(OgreColor_get_green),0);
	rb_define_method(rb_cOgreColor,"alpha",RUBY_METHOD_FUNC(OgreColor_get_alpha),0);
	
	rb_define_method(rb_cOgreColor,"red=",RUBY_METHOD_FUNC(OgreColor_set_red),1);
	rb_define_method(rb_cOgreColor,"blue=",RUBY_METHOD_FUNC(OgreColor_set_blue),1);
	rb_define_method(rb_cOgreColor,"green=",RUBY_METHOD_FUNC(OgreColor_set_green),1);
	rb_define_method(rb_cOgreColor,"alpha=",RUBY_METHOD_FUNC(OgreColor_set_alpha),1);
	
	rb_define_method(rb_cOgreColor,"hue",RUBY_METHOD_FUNC(OgreColor_get_hue),0);
	rb_define_method(rb_cOgreColor,"saturation",RUBY_METHOD_FUNC(OgreColor_get_saturation),0);
	rb_define_method(rb_cOgreColor,"brightness",RUBY_METHOD_FUNC(OgreColor_get_brightness),0);

	rb_define_method(rb_cOgreColor,"hue=",RUBY_METHOD_FUNC(OgreColor_set_hue),1);
	rb_define_method(rb_cOgreColor,"saturation=",RUBY_METHOD_FUNC(OgreColor_set_saturation),1);
	rb_define_method(rb_cOgreColor,"brightness=",RUBY_METHOD_FUNC(OgreColor_set_brightness),1);

	rb_define_method(rb_cOgreColor,"hsb",RUBY_METHOD_FUNC(OgreColor_get_hsb),0);
	rb_define_method(rb_cOgreColor,"hsb=",RUBY_METHOD_FUNC(OgreColor_set_hsb),1);

	rb_define_method(rb_cOgreColor,"rgba",RUBY_METHOD_FUNC(OgreColor_get_rgba),0);
	rb_define_method(rb_cOgreColor,"argb",RUBY_METHOD_FUNC(OgreColor_get_argb),0);
	rb_define_method(rb_cOgreColor,"bgra",RUBY_METHOD_FUNC(OgreColor_get_bgra),0);
	rb_define_method(rb_cOgreColor,"abgr",RUBY_METHOD_FUNC(OgreColor_get_abgr),0);

	rb_define_method(rb_cOgreColor,"rgba=",RUBY_METHOD_FUNC(OgreColor_set_rgba),1);
	rb_define_method(rb_cOgreColor,"argb=",RUBY_METHOD_FUNC(OgreColor_set_argb),1);
	rb_define_method(rb_cOgreColor,"bgra=",RUBY_METHOD_FUNC(OgreColor_set_bgra),1);
	rb_define_method(rb_cOgreColor,"abgr=",RUBY_METHOD_FUNC(OgreColor_set_abgr),1);

	rb_define_method(rb_cOgreColor,"inspect",RUBY_METHOD_FUNC(OgreColor_inspect),0);

	rb_define_method(rb_cOgreColor,"==",RUBY_METHOD_FUNC(OgreColor_equal),1);
	rb_define_method(rb_cOgreColor,"!=",RUBY_METHOD_FUNC(OgreColor_nequal),1);
	
	rb_define_method(rb_cOgreColor,"+",RUBY_METHOD_FUNC(OgreColor_plus),1);
	rb_define_method(rb_cOgreColor,"-",RUBY_METHOD_FUNC(OgreColor_minus),1);
	rb_define_method(rb_cOgreColor,"*",RUBY_METHOD_FUNC(OgreColor_mal),1);
	rb_define_method(rb_cOgreColor,"/",RUBY_METHOD_FUNC(OgreColor_durch),1);
	
	rb_define_const(rb_cOgreColor,"Zero",wrap(Ogre::ColourValue::ZERO));
	rb_define_const(rb_cOgreColor,"Black",wrap(Ogre::ColourValue::Black));
	rb_define_const(rb_cOgreColor,"White",wrap(Ogre::ColourValue::White));
	rb_define_const(rb_cOgreColor,"Red",wrap(Ogre::ColourValue::Red));
	rb_define_const(rb_cOgreColor,"Green",wrap(Ogre::ColourValue::Green));
	rb_define_const(rb_cOgreColor,"Blue",wrap(Ogre::ColourValue::Blue));
	
	rb_define_alias(rb_cOgreColor,"eql?","==");
	rb_define_method(rb_cOgreColor,"hash",RUBY_METHOD_FUNC(OgreColor_hash),0);
	
	rb_define_alias(rb_cFloat,"malOgreColor","*");
	rb_define_method(rb_cFloat,"*",RUBY_METHOD_FUNC(Numeric_mal_OgreColor),1);
/*
	rb_define_alias(rb_cInteger,"malOgreColor","*");
	rb_define_method(rb_cInteger,"*",RUBY_METHOD_FUNC(Numeric_mal_OgreColor),1);
*/

	rb_define_method(rb_cOgreColor,"marshal_dump",RUBY_METHOD_FUNC(OgreColor_marshal_dump),0);	
	rb_define_method(rb_cOgreColor,"marshal_load",RUBY_METHOD_FUNC(OgreColor_marshal_load),1);
}
