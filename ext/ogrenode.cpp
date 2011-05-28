#include "ogrenode.hpp"
//#include "ogrenodelistener.hpp"
#define _self wrap<Ogre::Node*>(self)

VALUE rb_cOgreNode;

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
//	return temp ? wrap(temp) : Qnil;
	return Qnil;
}

/*
*/

VALUE OgreNode_setListener(VALUE self,VALUE val)
{
	_self->setListener(NULL);
//	_self->setListener(wrap<Ogre::Node::Listener*>(val));
	return val;
}

void Init_OgreNode(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	rb_cOgreNode = rb_define_class_under(rb_mOgre,"Node",rb_cObject);

	
	rb_define_method(rb_cOgreNode,"name",RUBY_METHOD_FUNC(OgreNode_getName),0);
	rb_define_method(rb_cOgreNode,"numChildren",RUBY_METHOD_FUNC(OgreNode_numChildren),0);
	
	rb_define_method(rb_cOgreNode,"addChild",RUBY_METHOD_FUNC(OgreNode_addChild),1);
	
	rb_define_method(rb_cOgreNode,"inspect",RUBY_METHOD_FUNC(OgreNode_inspect),0);
	
	rb_define_method(rb_cOgreNode,"listener",RUBY_METHOD_FUNC(OgreNode_getListener),0);
	rb_define_method(rb_cOgreNode,"listener=",RUBY_METHOD_FUNC(OgreNode_setListener),1);
}
