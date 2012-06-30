#include "ogrevector3.hpp"
#include "ogrepolygon.hpp"
#define _self wrap<Ogre::Polygon*>(self)
VALUE rb_cOgrePolygon;

template <>
VALUE wrap< Ogre::Polygon >(Ogre::Polygon *polygon )
{
	return Data_Wrap_Struct(rb_cOgrePolygon, NULL, free, polygon);
}

template <>
VALUE wrap< Ogre::Polygon::EdgeMap >(const Ogre::Polygon::EdgeMap &edge )
{
	VALUE result = rb_hash_new();
	Ogre::Polygon::EdgeMap::const_iterator it;
	for ( it=edge.begin() ; it != edge.end(); it++ ){
		VALUE temp = wrap(it->first);
		if(NIL_P(rb_hash_lookup(result,temp)))
			rb_hash_aset(result,temp,rb_ary_new());
		rb_ary_push(rb_hash_aref(result,temp),wrap(it->second));
	}
	return result;
}


namespace RubyOgre {
namespace Polygon {

VALUE _alloc(VALUE self)
{
	return wrap(new Ogre::Polygon);
}
/*
 * call-seq:
 *   [id] -> Vector3 or nil
 * 
 * returns the Vector3 of the given id. if id out of range, return nil.
*/
VALUE _get(VALUE self,VALUE i)
{
	if(NUM2UINT(i) < _self->getVertexCount())
		return wrap(_self->getVertex(NUM2UINT(i)));
	else
		return Qnil;
}
/*
 * call-seq:
 *   [id]=Vector3
 * 
 * stets the vector3 on the position
*/
VALUE _set(VALUE self,VALUE i,VALUE val)
{
	if(NUM2UINT(i) > _self->getVertexCount())
		rb_raise(rb_eRangeError,"index must be <= size");
	_self->insertVertex(*wrap<Ogre::Vector3*>(val),NUM2UINT(i));
	return val;
}
/*
 * call-seq:
 *   << Vector3
 * 
 * adds an Vector3 at the end 
*/
VALUE _push(VALUE self,VALUE val)
{
	_self->insertVertex(*wrap<Ogre::Vector3*>(val));
	return val;
}
/*

*/
VALUE _delete(VALUE self,VALUE i)
{
	_self->deleteVertex(NUM2UINT(i));
	return self;
}
/*
 * call-seq:
 *   size -> Integer
 * 
 * returns the size of the Polygon.
*/
VALUE _size(VALUE self)
{
	return INT2NUM(_self->getVertexCount());
}
/*

*/
VALUE _pointinside(VALUE self,VALUE val)
{
	return _self->isPointInside(*wrap<Ogre::Vector3*>(val)) ? Qtrue : Qfalse;
}
/*
 * call-seq:
 *   each {|point| }
 *   each -> Enumerator
 * 
 * iterates the Polygon
*/
VALUE _each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	for (size_t i = 0; i < _self->getVertexCount(); ++i)
		rb_yield(wrap(_self->getVertex(i)));
	return self;
}
/*

*/
VALUE _uniqself(VALUE self)
{
	_self->removeDuplicates();
	return self;
}
/*

*/
VALUE _edgemap(VALUE self)
{
	Ogre::Polygon::EdgeMap map;
	_self->storeEdges(&map);
	return wrap(map);
}
/*
 * call-seq:
 *   == other -> bool
 * 
 * equals the Polygon with an other Polygon
*/
VALUE _equal(VALUE self,VALUE val)
{
	if(rb_obj_is_kind_of(val,rb_cOgrePolygon))
		return *_self == *wrap<Ogre::Polygon*>(val) ? Qtrue : Qfalse;
	else
		return Qfalse;
}
/*
 * call-seq:
 *   clear -> self
 * 
 * clears the Polygon
*/
VALUE _clear(VALUE self)
{
	_self->reset();
	return self;
}

}
}

/*
 * Document-class: Ogre::Polygon
 * 
 * This class represents an Polygon of Vector3.
*/ 
void Init_OgrePolygon(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	using namespace RubyOgre::Polygon;

	rb_cOgrePolygon = rb_define_class_under(rb_mOgre,"Polygon",rb_cObject);
	rb_define_alloc_func(rb_cOgrePolygon,_alloc);
	rb_include_module(rb_cOgrePolygon,rb_mEnumerable);
	
	rb_define_method(rb_cOgrePolygon,"[]",RUBY_METHOD_FUNC(_get),1);
	rb_define_method(rb_cOgrePolygon,"[]=",RUBY_METHOD_FUNC(_set),2);
	rb_define_method(rb_cOgrePolygon,"<<",RUBY_METHOD_FUNC(_push),1);
	rb_define_method(rb_cOgrePolygon,"size",RUBY_METHOD_FUNC(_size),0);
	rb_define_method(rb_cOgrePolygon,"delete",RUBY_METHOD_FUNC(_delete),1);
	rb_define_method(rb_cOgrePolygon,"pointinside?",RUBY_METHOD_FUNC(_pointinside),1);
	rb_define_method(rb_cOgrePolygon,"each",RUBY_METHOD_FUNC(_each),0);
	rb_define_method(rb_cOgrePolygon,"uniq!",RUBY_METHOD_FUNC(_uniqself),0);
	rb_define_method(rb_cOgrePolygon,"edgemap",RUBY_METHOD_FUNC(_edgemap),0);
	rb_define_method(rb_cOgrePolygon,"clear",RUBY_METHOD_FUNC(_clear),0);
	
	rb_define_method(rb_cOgrePolygon,"==",RUBY_METHOD_FUNC(_equal),1);

	registerklass<Ogre::Polygon>(rb_cOgrePolygon);
}
