/*
 * ogrepose.cpp
 *
 *  Created on: 18.09.2012
 *      Author: hanmac
 */

#include "ogrepose.hpp"
#include "ogrevector3.hpp"
#include "ogreexception.hpp"

#define _self wrap<Ogre::Pose*>(self)
VALUE rb_cOgrePose;

namespace RubyOgre {
namespace Pose {

singlereturn(getName)
singlereturn(getTarget)

singlefunc(clearVertices)

/*
 *
 */
VALUE _add(int argc,VALUE *argv,VALUE self)
{
	VALUE index, offset, normal;
	rb_scan_args(argc, argv, "11",&index,&offset,&normal);
	if(NIL_P(normal))
		_self->addVertex(NUM2UINT(index),wrap<Ogre::Vector3>(offset));
	else
		_self->addVertex(NUM2UINT(index),wrap<Ogre::Vector3>(offset),wrap<Ogre::Vector3>(normal));
	return self;
}

/*
*/
VALUE _each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap<size_t,Ogre::Vector3>(_self->getVertexOffsetIterator());
	return self;
}

/*
*/
VALUE _each_normal(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap<size_t,Ogre::Vector3>(_self->getNormalsIterator());
	return self;
}

}}

void Init_OgrePose(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	using namespace RubyOgre::Pose;

	rb_cOgrePose = rb_define_class_under(rb_mOgre,"Pose",rb_cObject);
	rb_undef_alloc_func(rb_cOgrePose);

	rb_define_method(rb_cOgrePose,"name",RUBY_METHOD_FUNC(_getName),0);
	rb_define_method(rb_cOgrePose,"target",RUBY_METHOD_FUNC(_getTarget),0);

	rb_define_method(rb_cOgrePose,"add",RUBY_METHOD_FUNC(_add),-1);
	rb_define_method(rb_cOgrePose,"clear",RUBY_METHOD_FUNC(_clearVertices),0);


	rb_define_method(rb_cOgrePose,"each",RUBY_METHOD_FUNC(_each),0);
	rb_define_method(rb_cOgrePose,"each_normal",RUBY_METHOD_FUNC(_each_normal),0);

	rb_include_module(rb_cOgrePose,rb_mEnumerable);
}
