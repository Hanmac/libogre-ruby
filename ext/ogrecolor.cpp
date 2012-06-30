#include "ogrecolor.hpp"
#include "ogreexception.hpp"
#define _self wrap<Ogre::ColourValue*>(self)
VALUE rb_cOgreColor;

template <>
VALUE wrap< Ogre::ColourValue >(Ogre::ColourValue *color )
{
	return Data_Wrap_Struct(rb_cOgreColor, NULL, free, color);
}

template <>
Ogre::ColourValue* wrap< Ogre::ColourValue* >(const VALUE &vcolor)
{
	return unwrapPtr<Ogre::ColourValue>(vcolor, rb_cOgreColor);
}
template <>
Ogre::ColourValue wrap< Ogre::ColourValue >(const VALUE &vcolor)
{
	if (!rb_obj_is_kind_of(vcolor, rb_cOgreColor) &&
		rb_respond_to(vcolor,rb_intern("red")) &&
		rb_respond_to(vcolor,rb_intern("blue")) &&
		rb_respond_to(vcolor,rb_intern("green")) &&
		rb_respond_to(vcolor,rb_intern("alpha"))){
			 double temp;
			 Ogre::ColourValue color;
			 temp = NUM2DBL(rb_funcall(vcolor,rb_intern("red"),0));
			 if(temp > 1.0)
			 	temp /=256;
			 color.r = temp;
			 temp = NUM2DBL(rb_funcall(vcolor,rb_intern("blue"),0));
			 if(temp > 1.0)
			 	temp /=256;
			 color.b = temp;

			 temp = NUM2DBL(rb_funcall(vcolor,rb_intern("green"),0));
			 if(temp > 1.0)
			 	temp /=256;
			 color.g = temp;

			 temp = NUM2DBL(rb_funcall(vcolor,rb_intern("alpha"),0));
			 if(temp > 1.0)
			 	temp /=256;
			 color.a = temp;
			 return color;
	}else{
		return *wrap< Ogre::ColourValue* >(vcolor);
	}
}

namespace RubyOgre {
namespace Color {

VALUE _alloc(VALUE self)
{
	return wrap(new Ogre::ColourValue);
}

macro_attr_prop(r,double)
macro_attr_prop(g,double)
macro_attr_prop(b,double)
macro_attr_prop(a,double)

macro_attr(AsRGBA,ulong)
macro_attr(AsARGB,ulong)
macro_attr(AsBGRA,ulong)
macro_attr(AsABGR,ulong)

/*
 * call-seq:
 *   Color.new(red,green,blue[,alpha])
 * 
 * creates a new Color Object. 
*/
VALUE _initialize(int argc,VALUE *argv,VALUE self)
{
	VALUE red,green,blue,alpha;
	rb_scan_args(argc, argv, "31",&red,&green,&blue,&alpha);
	_set_r(self,red);
	_set_g(self,green);
	_set_b(self,blue);
	if(!NIL_P(alpha))
		_set_a(self,alpha);
	return self;
}
/*
*/
VALUE _initialize_copy(VALUE self, VALUE other)
{
	VALUE result = rb_call_super(1,&other);
	_set_r(self,_get_r(other));
	_set_g(self,_get_g(other));
	_set_b(self,_get_b(other));
	_set_a(self,_get_a(other));
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
VALUE _plus(VALUE self,VALUE val)
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
VALUE _minus(VALUE self,VALUE val)
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
VALUE _mal(VALUE self,VALUE val)
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
VALUE _durch(VALUE self,VALUE val)
{
	if(rb_obj_is_kind_of(val,rb_cNumeric))
		return wrap(*_self / NUM2DBL(val));
	else
		return wrap(*_self / *wrap<Ogre::ColourValue*>(val));
}
VALUE _get_hue(VALUE self)
{
	Ogre::Real hue,saturation,brightness;
	_self->getHSB(&hue, &saturation, &brightness);
	return DBL2NUM(hue);
}
VALUE _get_saturation(VALUE self)
{
	Ogre::Real hue,saturation,brightness;
	_self->getHSB(&hue, &saturation, &brightness);
	return DBL2NUM(saturation);
}
VALUE _get_brightness(VALUE self)
{
	Ogre::Real hue,saturation,brightness;
	_self->getHSB(&hue, &saturation, &brightness);
	return DBL2NUM(brightness);
}
VALUE _set_hue(VALUE self,VALUE val)
{
	Ogre::Real hue,saturation,brightness;
	_self->getHSB(&hue, &saturation, &brightness);
	_self->setHSB(NUM2DBL(val), saturation, brightness);
	_self->saturate();
	return val;
}
VALUE _set_saturation(VALUE self,VALUE val)
{
	Ogre::Real hue,saturation,brightness;
	_self->getHSB(&hue, &saturation, &brightness);
	_self->setHSB(hue, NUM2DBL(val), brightness);
	_self->saturate();
	return val;
}
VALUE _set_brightness(VALUE self,VALUE val)
{
	Ogre::Real hue,saturation,brightness;
	_self->getHSB(&hue, &saturation, &brightness);
	_self->setHSB(hue, saturation, NUM2DBL(val));
	_self->saturate();
	return val;
}
VALUE _get_hsb(VALUE self)
{
	Ogre::Real hue,saturation,brightness;
	_self->getHSB(&hue, &saturation, &brightness);
	VALUE result = rb_ary_new();
	rb_ary_push(result,DBL2NUM(hue));
	rb_ary_push(result,DBL2NUM(saturation));
	rb_ary_push(result,DBL2NUM(brightness));
	return result;
}
VALUE _set_hsb(VALUE self,VALUE val)
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
/*
 * call-seq:
 *   color.inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE _inspect(VALUE self)
{
	VALUE array[6];
	array[0]=rb_str_new2("#<%s:(%f, %f, %f, %f)>");
	array[1]=rb_class_of(self);
	array[2]=_get_r(self);
	array[3]=_get_g(self);
	array[4]=_get_b(self);
	array[5]=_get_a(self);
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
VALUE _equal(VALUE self,VALUE other)
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
VALUE _nequal(VALUE self,VALUE other)
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
VALUE _hash(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,_get_r(self));
	rb_ary_push(result,_get_g(self));
	rb_ary_push(result,_get_b(self));
	rb_ary_push(result,_get_a(self));
	return rb_funcall(result,rb_intern("hash"),0);
}
/*
 * call-seq:
 *   marshal_dump -> string
 * 
 * packs a Color into an string.
*/
VALUE _marshal_dump(VALUE self)
{
	VALUE result = rb_ary_new();
	rb_ary_push(result,_get_r(self));
	rb_ary_push(result,_get_g(self));
	rb_ary_push(result,_get_b(self));
	rb_ary_push(result,_get_a(self));
	return rb_funcall(result,rb_intern("pack"),1,rb_str_new2("d*"));
}
/*
 * call-seq:
 *   marshal_load(string) -> self
 * 
 * loads a string into an Color.
*/
VALUE _marshal_load(VALUE self,VALUE load)
{
	VALUE result = rb_funcall(load,rb_intern("unpack"),1,rb_str_new2("d*"));
	_set_a(self,rb_ary_pop(result));
	_set_b(self,rb_ary_pop(result));
	_set_g(self,rb_ary_pop(result));
	_set_r(self,rb_ary_pop(result));
	return self;
}

}
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
	using namespace RubyOgre::Color;

	rb_cOgreColor = rb_define_class_under(rb_mOgre,"Color",rb_cObject);
	rb_define_alloc_func(rb_cOgreColor,_alloc);
	
	rb_define_method(rb_cOgreColor,"initialize",RUBY_METHOD_FUNC(_initialize),-1);
	rb_define_private_method(rb_cOgreColor,"initialize_copy",RUBY_METHOD_FUNC(_initialize_copy),1);
	
	rb_define_attr_method(rb_cOgreColor,"red",_get_r,_set_r);
	rb_define_attr_method(rb_cOgreColor,"blue",_get_b,_set_b);
	rb_define_attr_method(rb_cOgreColor,"green",_get_g,_set_g);
	rb_define_attr_method(rb_cOgreColor,"alpha",_get_a,_set_a);
	
	rb_define_attr_method(rb_cOgreColor,"hue",_get_hue,_set_hue);
	rb_define_attr_method(rb_cOgreColor,"saturation",_get_saturation,_set_saturation);
	rb_define_attr_method(rb_cOgreColor,"brightness",_get_brightness,_set_brightness);


	rb_define_attr_method(rb_cOgreColor,"hsb",_get_hsb,_set_hsb);

	rb_define_attr_method(rb_cOgreColor,"rgba",_getAsRGBA,_setAsRGBA);
	rb_define_attr_method(rb_cOgreColor,"argb",_getAsARGB,_setAsARGB);
	rb_define_attr_method(rb_cOgreColor,"bgra",_getAsBGRA,_setAsBGRA);
	rb_define_attr_method(rb_cOgreColor,"abgr",_getAsABGR,_setAsABGR);


	rb_define_method(rb_cOgreColor,"inspect",RUBY_METHOD_FUNC(_inspect),0);

	rb_define_method(rb_cOgreColor,"==",RUBY_METHOD_FUNC(_equal),1);
	rb_define_method(rb_cOgreColor,"!=",RUBY_METHOD_FUNC(_nequal),1);
	
	rb_define_method(rb_cOgreColor,"+",RUBY_METHOD_FUNC(_plus),1);
	rb_define_method(rb_cOgreColor,"-",RUBY_METHOD_FUNC(_minus),1);
	rb_define_method(rb_cOgreColor,"*",RUBY_METHOD_FUNC(_mal),1);
	rb_define_method(rb_cOgreColor,"/",RUBY_METHOD_FUNC(_durch),1);
	
	rb_define_const(rb_cOgreColor,"Zero",wrap(Ogre::ColourValue::ZERO));
	rb_define_const(rb_cOgreColor,"Black",wrap(Ogre::ColourValue::Black));
	rb_define_const(rb_cOgreColor,"White",wrap(Ogre::ColourValue::White));
	rb_define_const(rb_cOgreColor,"Red",wrap(Ogre::ColourValue::Red));
	rb_define_const(rb_cOgreColor,"Green",wrap(Ogre::ColourValue::Green));
	rb_define_const(rb_cOgreColor,"Blue",wrap(Ogre::ColourValue::Blue));
	
	rb_define_alias(rb_cOgreColor,"eql?","==");
	rb_define_method(rb_cOgreColor,"hash",RUBY_METHOD_FUNC(_hash),0);

	rb_define_method(rb_cOgreColor,"marshal_dump",RUBY_METHOD_FUNC(_marshal_dump),0);
	rb_define_method(rb_cOgreColor,"marshal_load",RUBY_METHOD_FUNC(_marshal_load),1);
}
