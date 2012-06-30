#include "ogrebillboardset.hpp"
#include "ogrebillboard.hpp"
#include "ogrevector3.hpp"
#include "ogrecolor.hpp"
#include "ogremovableobject.hpp"
#include "ogreaxisalignedbox.hpp"
#define _self wrap<Ogre::BillboardSet*>(self)
VALUE rb_cOgreBillboardSet;


namespace RubyOgre {
namespace BillboardSet {

macro_attr(Autoextend,bool)
macro_attr(SortingEnabled,bool)
macro_attr(CullIndividually,bool)
macro_attr(UseAccurateFacing,bool)
macro_attr(AutoUpdate,bool)

macro_attr(PoolSize,size_t)

macro_attr(DefaultWidth,double)
macro_attr(DefaultHeight,double)



macro_attr(MaterialName,Ogre::String)

macro_attr(CommonDirection,Ogre::Vector3)
macro_attr(CommonUpVector,Ogre::Vector3)

macro_attr(BillboardOrigin,Ogre::BillboardOrigin)
macro_attr(BillboardRotationType,Ogre::BillboardRotationType)
macro_attr(BillboardType,Ogre::BillboardType)


/*
*/
VALUE _each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	for (int i = 0; i < _self->getNumBillboards(); ++i)
		rb_yield(wrap(_self->getBillboard(i)));
	return self;
}

/*
*/
VALUE _setBoundingBox(VALUE self,VALUE box)
{
	_self->setBounds(wrap<Ogre::AxisAlignedBox>(box),_self->getBoundingRadius());
	return box;
}

/*
*/
VALUE _setBoundingRadius(VALUE self,VALUE radius)
{
	_self->setBounds(_self->getBoundingBox(),NUM2DBL(radius));
	return radius;
}

}}

/*
 * Document-class: Ogre::BillboardSet
 * 
 * This class represents an BillboardSet. 
*/
void Init_OgreBillboardSet(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_mOgreMovableObject = rb_define_module_under(rb_mOgre,"MovableObject");
	
	rb_define_attr(rb_cOgreBillboardSet,"autoextend",1,1);
	rb_define_attr(rb_cOgreBillboardSet,"sortingEnabled",1,1);
	rb_define_attr(rb_cOgreBillboardSet,"cullIndividually",1,1);

	rb_define_attr(rb_cOgreBillboardSet,"poolSize",1,1);
	rb_define_attr(rb_cOgreBillboardSet,"defaultWidth",1,1);
	rb_define_attr(rb_cOgreBillboardSet,"defaultHeight",1,1);

	rb_define_attr(rb_cOgreBillboardSet,"materialname",1,1);
	rb_define_attr(rb_cOgreBillboardSet,"commonDirection",1,1);
	rb_define_attr(rb_cOgreBillboardSet,"commonUpVector",1,1);
#endif
	using namespace RubyOgre::BillboardSet;

	rb_cOgreBillboardSet = rb_define_class_under(rb_mOgre,"BillboardSet",rb_cObject);
	rb_undef_alloc_func(rb_cOgreBillboardSet);
	rb_include_module(rb_cOgreBillboardSet,rb_mOgreMovableObject);
	rb_define_method(rb_cOgreBillboardSet,"each",RUBY_METHOD_FUNC(_each),0);
	rb_include_module(rb_cOgreBillboardSet,rb_mEnumerable);
	
	rb_define_method(rb_cOgreBillboardSet,"boundingBox=",RUBY_METHOD_FUNC(_setBoundingBox),1);
	rb_define_method(rb_cOgreBillboardSet,"boundingRadius=",RUBY_METHOD_FUNC(_setBoundingRadius),1);

	
	rb_define_attr_method(rb_cOgreBillboardSet,"autoextend",_getAutoextend,_setAutoextend);
	rb_define_attr_method(rb_cOgreBillboardSet,"sortingEnabled",_getSortingEnabled,_setSortingEnabled);
	rb_define_attr_method(rb_cOgreBillboardSet,"cullIndividually",_getCullIndividually,_setCullIndividually);
	
	rb_define_attr_method(rb_cOgreBillboardSet,"poolSize",_getPoolSize,_setPoolSize);
	rb_define_attr_method(rb_cOgreBillboardSet,"defaultWidth",_getDefaultWidth,_setDefaultWidth);
	rb_define_attr_method(rb_cOgreBillboardSet,"defaultHeight",_getDefaultHeight,_setDefaultHeight);
	
	rb_define_attr_method(rb_cOgreBillboardSet,"materialname",_getMaterialName,_setMaterialName);
	rb_define_attr_method(rb_cOgreBillboardSet,"commonDirection",_getCommonDirection,_setCommonDirection);
	rb_define_attr_method(rb_cOgreBillboardSet,"commonUpVector",_getCommonUpVector,_setCommonUpVector);

	registerklass<Ogre::BillboardSet>(rb_cOgreBillboardSet);
}
