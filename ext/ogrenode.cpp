#include "ogrenode.hpp"
#include "ogrevector3.hpp"

#include "ogrequaternion.hpp"
//#include "ogrenodelistener.hpp"
#define _self wrap<Ogre::Node*>(self)

VALUE rb_cOgreNode;

macro_attr(Node,Position,Ogre::Vector3)
macro_attr(Node,Scale,Ogre::Vector3)
/*
*/
VALUE OgreNode_getName(VALUE self)
{
	return wrap(_self->getName());
}


/*
*/
VALUE OgreNode_numChildren(VALUE self)
{
	return UINT2NUM(_self->numChildren());
}

/*
*/
VALUE OgreNode_addChild(VALUE self,VALUE val)
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
VALUE OgreNode_inspect(VALUE self)
{
	VALUE array[3];
	array[0]=rb_str_new2("#<%s:%s>");
	array[1]=rb_class_of(self);
	if(_self==NULL)
		array[2]=rb_str_new2("(destroyed)");
	else
		array[2]=OgreNode_getName(self);
	return rb_f_sprintf(3,array);
}

/*
*/
VALUE OgreNode_getListener(VALUE self)
{
	Ogre::Node::Listener *temp = _self->getListener();
	return temp ? wrap(temp) : Qnil;
}
/*
*/
VALUE OgreNode_setListener(VALUE self,VALUE val)
{
	_self->setListener(wrap<Ogre::Node::Listener*>(val));
	return val;
}
/*
*/
VALUE OgreNode_each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap(_self->getChildIterator());
	return self;
}

/*
*/
VALUE OgreNode_getChild(VALUE self,VALUE name)
{
	Ogre::Node *node = NULL;
	if(rb_obj_is_kind_of(name,rb_cString))
		node = _self->getChild(rb_string_value_cstr(&name));
	if(rb_obj_is_kind_of(name,rb_cNumeric))
		node = _self->getChild(NUM2ULONG(name));
	
	return node ? wrap(node) : Qnil;
}

/*
*/
VALUE OgreNode_removeChild(VALUE self,VALUE name)
{
	if(rb_obj_is_kind_of(name,rb_cString))
		_self->removeChild(rb_string_value_cstr(&name));
	else if(rb_obj_is_kind_of(name,rb_cNumeric))
		_self->removeChild(NUM2ULONG(name));
	else
		_self->removeChild(wrap<Ogre::Node*>(name));
	return self;
}

/*
*/
VALUE OgreNode_createChild(int argc,VALUE *argv,VALUE self)
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
		return wrap(_self->createChild(rb_string_value_cstr(&name),vec,rotate));
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

void Init_OgreNode(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	
	rb_define_attr(rb_cOgreNode,"listener",1,1);
	rb_define_attr(rb_cOgreNode,"position",1,1);
	rb_define_attr(rb_cOgreNode,"scale",1,1);
#endif
	rb_cOgreNode = rb_define_class_under(rb_mOgre,"Node",rb_cObject);
	rb_undef_alloc_func(rb_cOgreNode);
	
	rb_define_method(rb_cOgreNode,"name",RUBY_METHOD_FUNC(OgreNode_getName),0);
	rb_define_method(rb_cOgreNode,"numChildren",RUBY_METHOD_FUNC(OgreNode_numChildren),0);
	
	rb_define_method(rb_cOgreNode,"addChild",RUBY_METHOD_FUNC(OgreNode_addChild),1);
	rb_define_method(rb_cOgreNode,"removeChild",RUBY_METHOD_FUNC(OgreNode_removeChild),1);

	rb_define_method(rb_cOgreNode,"createChild",RUBY_METHOD_FUNC(OgreNode_createChild),-1);

	rb_define_method(rb_cOgreNode,"inspect",RUBY_METHOD_FUNC(OgreNode_inspect),0);

	rb_define_attr_method(rb_cOgreNode,"listener",OgreNode_getListener,OgreNode_setListener);
	
	rb_define_attr_method(rb_cOgreNode,"position",OgreNode_getPosition,OgreNode_setPosition);
	rb_define_attr_method(rb_cOgreNode,"scale",OgreNode_getScale,OgreNode_setScale);
	

	rb_define_method(rb_cOgreNode,"each",RUBY_METHOD_FUNC(OgreNode_each),0);
	rb_include_module(rb_cOgreNode,rb_mEnumerable);
	rb_define_method(rb_cOgreNode,"[]",RUBY_METHOD_FUNC(OgreNode_getChild),1);
}
