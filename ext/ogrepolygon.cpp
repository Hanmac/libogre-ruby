#include "ogrevector3.hpp"
#include "ogrepolygon.hpp"
#define _self wrap<Ogre::Polygon*>(self)
VALUE rb_cOgrePolygon;

VALUE OgrePolygon_alloc(VALUE self)
{
	Ogre::Polygon *temp = new Ogre::Polygon;
	return wrap(temp);
}
/*

*/
VALUE OgrePolygon_get(VALUE self,VALUE i)
{
	if(NUM2UINT(i) < _self->getVertexCount())
		return wrap(_self->getVertex(NUM2UINT(i)));
	else
		return Qnil;
}
/*

*/
VALUE OgrePolygon_set(VALUE self,VALUE i,VALUE val)
{
	if(NUM2UINT(i) > _self->getVertexCount())
		rb_raise(rb_eRangeError,"index must be <= size");
	if(rb_obj_is_kind_of(val,rb_cOgreVector3)){
		_self->insertVertex(*wrap<Ogre::Vector3*>(val),NUM2UINT(i));
	}else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreVector3),rb_obj_classname(val));
	return val;
}
/*

*/
VALUE OgrePolygon_push(VALUE self,VALUE val)
{
	if(rb_obj_is_kind_of(val,rb_cOgreVector3))
		_self->insertVertex(*wrap<Ogre::Vector3*>(val));
	else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreVector3),rb_obj_classname(val));
	return val;
}
/*

*/
VALUE OgrePolygon_delete(VALUE self,VALUE i)
{
	_self->deleteVertex(NUM2UINT(i));
	return self;
}
/*

*/
VALUE OgrePolygon_size(VALUE self)
{
	return INT2NUM(_self->getVertexCount());
}
/*

*/
VALUE OgrePolygon_pointinside(VALUE self,VALUE val)
{
	if(rb_obj_is_kind_of(val,rb_cOgreVector3))
		return _self->isPointInside(*wrap<Ogre::Vector3*>(val)) ? Qtrue : Qfalse;
	else
		rb_raise(rb_eTypeError,"Exepted %s got %s!",rb_class2name(rb_cOgreVector3),rb_obj_classname(val));
}
/*

*/
VALUE OgrePolygon_each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	for (size_t i = 0; i < _self->getVertexCount(); i++)
		rb_yield(wrap(_self->getVertex(i)));
	return self;
}
/*

*/
VALUE OgrePolygon_uniqself(VALUE self)
{
	_self->removeDuplicates();
	return self;
}
/*

*/
VALUE OgrePolygon_edgemap(VALUE self)
{
	Ogre::Polygon::EdgeMap map;
	_self->storeEdges(&map);
	return wrap(map);
}
/*

*/
VALUE OgrePolygon_equal(VALUE self,VALUE val)
{
	if(rb_obj_is_kind_of(val,rb_cOgrePolygon))
		return *_self == *wrap<Ogre::Polygon*>(val) ? Qtrue : Qfalse;
	else
		return Qfalse;
}
/*

*/
VALUE OgrePolygon_clear(VALUE self)
{
	_self->reset();
	return self;
}

void Init_OgrePolygon(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	rb_cOgrePolygon = rb_define_class_under(rb_mOgre,"Polygon",rb_cObject);
	rb_define_alloc_func(rb_cOgrePolygon,OgrePolygon_alloc);
	rb_include_module(rb_cOgrePolygon,rb_mEnumerable);
	
	rb_define_method(rb_cOgrePolygon,"[]",RUBY_METHOD_FUNC(OgrePolygon_get),1);
	rb_define_method(rb_cOgrePolygon,"[]=",RUBY_METHOD_FUNC(OgrePolygon_set),2);
	rb_define_method(rb_cOgrePolygon,"<<",RUBY_METHOD_FUNC(OgrePolygon_push),1);
	rb_define_method(rb_cOgrePolygon,"size",RUBY_METHOD_FUNC(OgrePolygon_size),0);
	rb_define_method(rb_cOgrePolygon,"delete",RUBY_METHOD_FUNC(OgrePolygon_delete),1);
	rb_define_method(rb_cOgrePolygon,"pointinside?",RUBY_METHOD_FUNC(OgrePolygon_pointinside),1);
	rb_define_method(rb_cOgrePolygon,"each",RUBY_METHOD_FUNC(OgrePolygon_each),0);
	rb_define_method(rb_cOgrePolygon,"uniq!",RUBY_METHOD_FUNC(OgrePolygon_uniqself),0);
	rb_define_method(rb_cOgrePolygon,"edgemap",RUBY_METHOD_FUNC(OgrePolygon_edgemap),0);
	rb_define_method(rb_cOgrePolygon,"clear",RUBY_METHOD_FUNC(OgrePolygon_clear),0);
	
	rb_define_method(rb_cOgrePolygon,"==",RUBY_METHOD_FUNC(OgrePolygon_equal),1);
}