#include "ogrenode.hpp"
#include "ogrevector3.hpp"
#include "ogreexception.hpp"
#include "ogrequaternion.hpp"
//#include "ogrenodelistener.hpp"
#define _self wrap<Ogre::Node*>(self)

VALUE rb_cOgreNode;

void wrap(Ogre::Node::ChildNodeIterator it )
{
	wrap_each2(it.begin(),it.end());
}

namespace RubyOgre
{
namespace Node
{

macro_attr(Position,Ogre::Vector3)
macro_attr(Scale,Ogre::Vector3)
macro_attr(Orientation,Ogre::Quaternion)

macro_attr(Listener,Ogre::Node::Listener*)

singlereturn(getName)
singlereturn(numChildren)

/*
*/
VALUE _addChild(VALUE self,VALUE val)
{
	_self->addChild(wrap<Ogre::Node*>(self));
	return self;
}

/*
 * call-seq:
 *   node.inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE _inspect(VALUE self)
{
	VALUE array[3];
	array[0]=rb_str_new2("#<%s:%s>");
	array[1]=rb_class_of(self);
	if(_self==NULL)
		array[2]=rb_str_new2("(destroyed)");
	else
		array[2]=_getName(self);
	return rb_f_sprintf(3,array);
}

/*
*/
VALUE _each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap(_self->getChildIterator());
	return self;
}

/*
*/
VALUE _getChild(VALUE self,VALUE name)
{
	Ogre::Node *node = NULL;
	if(rb_obj_is_kind_of(name,rb_cString))
		node = _self->getChild(wrap<Ogre::String>(name));
	if(rb_obj_is_kind_of(name,rb_cNumeric))
		node = _self->getChild(NUM2ULONG(name));
	
	return node ? wrap(node) : Qnil;
}

/*
*/
VALUE _removeChild(VALUE self,VALUE name)
{
	if(rb_obj_is_kind_of(name,rb_cString))
		_self->removeChild(wrap<Ogre::String>(name));
	else if(rb_obj_is_kind_of(name,rb_cNumeric))
		_self->removeChild(NUM2ULONG(name));
	else
		_self->removeChild(wrap<Ogre::Node*>(name));
	return self;
}

/*
*/
VALUE _createChild(int argc,VALUE *argv,VALUE self)
{
	VALUE name,arg1,arg2;
	Ogre::Vector3 vec;
	Ogre::Quaternion rotate;
	rb_scan_args(argc, argv, "03",&name,&arg1,&arg2);
	if(rb_obj_is_kind_of(name,rb_cString))
	{
		if(rb_obj_is_kind_of(arg1,rb_cOgreQuaternion))
		{
			rotate = wrap<Ogre::Quaternion>(arg1);
			vec = Ogre::Vector3::ZERO;
		}else if(NIL_P(arg1))
			vec = Ogre::Vector3::ZERO;
		else
			vec = wrap<Ogre::Vector3>(arg1);
		if(rb_obj_is_kind_of(arg2,rb_cOgreQuaternion))
			rotate = wrap<Ogre::Quaternion>(arg2);
		if(rb_obj_is_kind_of(arg2,rb_cOgreQuaternion))
			rotate = wrap<Ogre::Quaternion>(arg2);
		else
			rotate=Ogre::Quaternion::IDENTITY;
		return wrap(_self->createChild(wrap<Ogre::String>(name),vec,rotate));
	}else{
		rb_scan_args(argc, argv, "02",&arg1,&arg2);
		if(rb_obj_is_kind_of(arg1,rb_cOgreQuaternion))
		{
			rotate = wrap<Ogre::Quaternion>(arg1);
			vec = Ogre::Vector3::ZERO;
		}else if(NIL_P(arg1))
			vec = Ogre::Vector3::ZERO;
		else
			vec = wrap<Ogre::Vector3>(arg1);
		if(rb_obj_is_kind_of(arg2,rb_cOgreQuaternion))
			rotate = wrap<Ogre::Quaternion>(arg2);
		if(rb_obj_is_kind_of(arg2,rb_cOgreQuaternion))
			rotate = wrap<Ogre::Quaternion>(arg2);
		else
			rotate=Ogre::Quaternion::IDENTITY;
		return wrap(_self->createChild(vec,rotate));
	}
}

/*
*/
VALUE _roll(int argc,VALUE *argv,VALUE self)
{
	VALUE angle,space;
	rb_scan_args(argc, argv, "11",&angle,&space);
	_self->roll(wrap<Ogre::Radian>(angle),wrapenum<Ogre::Node::TransformSpace>(space));
	return self;
}
/*
*/
VALUE _yaw(int argc,VALUE *argv,VALUE self)
{
	VALUE angle,space;
	rb_scan_args(argc, argv, "11",&angle,&space);
	_self->yaw(wrap<Ogre::Radian>(angle),wrapenum<Ogre::Node::TransformSpace>(space));
	return self;
}
/*
*/
VALUE _pitch(int argc,VALUE *argv,VALUE self)
{
	VALUE angle,space;
	rb_scan_args(argc, argv, "11",&angle,&space);
	_self->pitch(wrap<Ogre::Radian>(angle),wrapenum<Ogre::Node::TransformSpace>(space));
	return self;
}


}
}
void Init_OgreNode(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	
	rb_define_attr(rb_cOgreNode,"listener",1,1);
	rb_define_attr(rb_cOgreNode,"position",1,1);
	rb_define_attr(rb_cOgreNode,"scale",1,1);
#endif
	using namespace RubyOgre::Node;

	rb_cOgreNode = rb_define_class_under(rb_mOgre,"Node",rb_cObject);
	rb_undef_alloc_func(rb_cOgreNode);
	
	rb_define_method(rb_cOgreNode,"name",RUBY_METHOD_FUNC(_getName),0);
	rb_define_method(rb_cOgreNode,"size",RUBY_METHOD_FUNC(_numChildren),0);
	
	rb_define_method(rb_cOgreNode,"addChild",RUBY_METHOD_FUNC(_addChild),1);
	rb_define_method(rb_cOgreNode,"removeChild",RUBY_METHOD_FUNC(_removeChild),1);

	rb_define_method(rb_cOgreNode,"createChild",RUBY_METHOD_FUNC(_createChild),-1);

	rb_define_method(rb_cOgreNode,"inspect",RUBY_METHOD_FUNC(_inspect),0);

	rb_define_attr_method(rb_cOgreNode,"listener",_getListener,_setListener);
	
	rb_define_attr_method(rb_cOgreNode,"position",_getPosition,_setPosition);
	rb_define_attr_method(rb_cOgreNode,"scale",_getScale,_setScale);


	rb_define_method(rb_cOgreNode,"roll",RUBY_METHOD_FUNC(_roll),-1);
	rb_define_method(rb_cOgreNode,"yaw",RUBY_METHOD_FUNC(_yaw),-1);
	rb_define_method(rb_cOgreNode,"pitch",RUBY_METHOD_FUNC(_pitch),-1);


	rb_define_method(rb_cOgreNode,"each",RUBY_METHOD_FUNC(_each),0);
	rb_include_module(rb_cOgreNode,rb_mEnumerable);
	rb_define_method(rb_cOgreNode,"[]",RUBY_METHOD_FUNC(_getChild),1);

	registerklass<Ogre::Node>(rb_cOgreNode);

	registerenum<Ogre::Node::TransformSpace>("Ogre::Node::TransformSpace")
		.add(Ogre::Node::TS_LOCAL,"local")
		.add(Ogre::Node::TS_PARENT,"parent")
		.add(Ogre::Node::TS_WORLD,"world");

}
