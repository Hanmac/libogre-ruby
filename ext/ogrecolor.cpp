#include "ogrecolor.hpp"

#define _self wrap<Ogre::ColourValue*>(self)
VALUE rb_cOgreColor;

VALUE OgreColor_alloc(VALUE self)
{
	return wrap(new Ogre::ColourValue);
}

macro_attr_prop_with_func(Color,r,DBL2NUM,NUM2DBL)
macro_attr_prop_with_func(Color,g,DBL2NUM,NUM2DBL)
macro_attr_prop_with_func(Color,b,DBL2NUM,NUM2DBL)
macro_attr_prop_with_func(Color,a,DBL2NUM,NUM2DBL)
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
	OgreColor_set_r(self,red);
	OgreColor_set_g(self,green);
	OgreColor_set_b(self,blue);
	if(!NIL_P(alpha))
		OgreColor_set_a(self,alpha);
	return self;
}
/*
*/
VALUE OgreColor_initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	OgreColor_set_r(self,OgreColor_get_r(other));
	OgreColor_set_g(self,OgreColor_get_g(other));
	OgreColor_set_b(self,OgreColor_get_b(other));
	OgreColor_set_a(self,OgreColor_get_a(other));
	return result;
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
	Ogre::ColourValue temp = *_self + *wrap<Ogre::ColourValue*>(val);
	temp.saturate();
	return wrap(temp);
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
	Ogre::ColourValue temp = *_self - *wrap<Ogre::ColourValue*>(val);
	temp.saturate();
	return wrap(temp);
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
	if(rb_obj_is_kind_of(val,rb_cNumeric))
		return wrap(*_self * NUM2DBL(val));
	else
		return wrap(*_self * *wrap<Ogre::ColourValue*>(val));
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
	if(rb_obj_is_kind_of(val,rb_cNumeric))
		return wrap(*_self / NUM2DBL(val));
	else
		return wrap(*_self / *wrap<Ogre::ColourValue*>(val));
}
VALUE OgreColor_get_hue(VALUE self)
{
	Ogre::Real hue,saturation,brightness;
	_self->getHSB(&hue, &saturation, &brightness);
	return DBL2NUM(hue);
}
VALUE OgreColor_get_saturation(VALUE self)
{
	Ogre::Real hue,saturation,brightness;
	_self->getHSB(&hue, &saturation, &brightness);
	return DBL2NUM(saturation);
}
VALUE OgreColor_get_brightness(VALUE self)
{
	Ogre::Real hue,saturation,brightness;
	_self->getHSB(&hue, &saturation, &brightness);
	return DBL2NUM(brightness);
}
VALUE OgreColor_set_hue(VALUE self,VALUE val)
{
	Ogre::Real hue,saturation,brightness;
	_self->getHSB(&hue, &saturation, &brightness);
	_self->setHSB(NUM2DBL(val), saturation, brightness);
	_self->saturate();
	return val;
}
VALUE OgreColor_set_saturation(VALUE self,VALUE val)
{
	Ogre::Real hue,saturation,brightness;
	_self->getHSB(&hue, &saturation, &brightness);
	_self->setHSB(hue, NUM2DBL(val), brightness);
	_self->saturate();
	return val;
}
VALUE OgreColor_set_brightness(VALUE self,VALUE val)
{
	Ogre::Real hue,saturation,brightness;
	_self->getHSB(&hue, &saturation, &brightness);
	_self->setHSB(hue, saturation, NUM2DBL(val));
	_self->saturate();
	return val;
}
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
VALUE OgreColor_get_rgba(VALUE self)
{
	return ULONG2NUM(_self->getAsRGBA());
}
VALUE OgreColor_get_argb(VALUE self)
{
	return ULONG2NUM(_self->getAsARGB());
}
VALUE OgreColor_get_bgra(VALUE self)
{
	return ULONG2NUM(_self->getAsBGRA());
}
VALUE OgreColor_get_abgr(VALUE self)
{
	return ULONG2NUM(_self->getAsABGR());
}
VALUE OgreColor_set_rgba(VALUE self,VALUE val)
{
	_self->setAsRGBA(NUM2ULONG(val));
	return val;
}
VALUE OgreColor_set_argb(VALUE self,VALUE val)
{
	_self->setAsARGB(NUM2ULONG(val));
	return val;
}
VALUE OgreColor_set_bgra(VALUE self,VALUE val)
{
	_self->setAsBGRA(NUM2ULONG(val));
	return val;
}
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
	array[2]=OgreColor_get_r(self);
	array[3]=OgreColor_get_g(self);
	array[4]=OgreColor_get_b(self);
	array[5]=OgreColor_get_a(self);
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
	rb_ary_push(result,OgreColor_get_r(self));
	rb_ary_push(result,OgreColor_get_g(self));
	rb_ary_push(result,OgreColor_get_b(self));
	rb_ary_push(result,OgreColor_get_a(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 * 
 * packs a Color into an string.
*/
VALUE OgreColor_marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,OgreColor_get_r(self));
	rb_ary_push(result,OgreColor_get_g(self));
	rb_ary_push(result,OgreColor_get_b(self));
	rb_ary_push(result,OgreColor_get_a(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("dddd"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 * 
 * loads a string into an Color.
*/
VALUE OgreColor_marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("dddd"));
	OgreColor_set_a(self,rb_ary_pop(result));
	OgreColor_set_b(self,rb_ary_pop(result));
	OgreColor_set_g(self,rb_ary_pop(result));
	OgreColor_set_r(self,rb_ary_pop(result));
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

/* Document-const: Zero
 * Color(0.0,0.0,0.0,0.0). */
/* Document-const: Black
 * Color(0.0,0.0,0.0,1.0). */
/* Document-const: White
 * Color(1.0,1.0,1.0,1.0). */
/* Document-const: Red
 * Color(1.0,0.0,0.0,1.0). */
/* Document-const: Green
 * Color(0.0,1.0,0.0,1.0). */
/* Document-const: Blue
 * Color(0.0,0.0,1.0,1.0). */
 
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
	rb_define_private_method(rb_cOgreColor,"initialize_copy",RUBY_METHOD_FUNC(OgreColor_initialize_copy),1);
	
	rb_define_attr_method(rb_cOgreColor,"red",OgreColor_get_r,OgreColor_set_r);
	rb_define_attr_method(rb_cOgreColor,"blue",OgreColor_get_b,OgreColor_set_b);
	rb_define_attr_method(rb_cOgreColor,"green",OgreColor_get_g,OgreColor_set_g);
	rb_define_attr_method(rb_cOgreColor,"alpha",OgreColor_get_a,OgreColor_set_a);
	
	rb_define_attr_method(rb_cOgreColor,"hue",OgreColor_get_hue,OgreColor_set_hue);
	rb_define_attr_method(rb_cOgreColor,"saturation",OgreColor_get_saturation,OgreColor_set_saturation);
	rb_define_attr_method(rb_cOgreColor,"brightness",OgreColor_get_brightness,OgreColor_set_brightness);


	rb_define_attr_method(rb_cOgreColor,"hsb",OgreColor_get_hsb,OgreColor_set_hsb);

	rb_define_attr_method(rb_cOgreColor,"rgba",OgreColor_get_rgba,OgreColor_set_rgba);
	rb_define_attr_method(rb_cOgreColor,"argb",OgreColor_get_argb,OgreColor_set_argb);
	rb_define_attr_method(rb_cOgreColor,"bgra",OgreColor_get_bgra,OgreColor_set_bgra);
	rb_define_attr_method(rb_cOgreColor,"abgr",OgreColor_get_abgr,OgreColor_set_abgr);


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
/*	
//	rb_define_alias(rb_cFloat,"malOgreColor","*");
//	rb_define_method(rb_cFloat,"*",RUBY_METHOD_FUNC(Numeric_mal_OgreColor),1);
//	rb_define_alias(rb_cInteger,"malOgreColor","*");
//	rb_define_method(rb_cInteger,"*",RUBY_METHOD_FUNC(Numeric_mal_OgreColor),1);
*/

	rb_define_method(rb_cOgreColor,"marshal_dump",RUBY_METHOD_FUNC(OgreColor_marshal_dump),0);	
	rb_define_method(rb_cOgreColor,"marshal_load",RUBY_METHOD_FUNC(OgreColor_marshal_load),1);
}
