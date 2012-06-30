#include "ogrebillboardchain.hpp"
#include "ogreribbontrail.hpp"
#include "ogrenode.hpp"
#define _self wrap<Ogre::RibbonTrail*>(self)
VALUE rb_cOgreRibbonTrail;

namespace RubyOgre {
namespace RibbonTrail {

macro_attr(TrailLength,double)

/*
*/
VALUE _each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap(_self->getNodeIterator());
	return self;
}

/*
*/
VALUE _add(int argc,VALUE* argv,VALUE self)
{
	VALUE node,other;
	rb_scan_args(argc, argv, "11",&node,&other);
	if(argc==1)
		_self->addNode(wrap<Ogre::Node*>(node));
	else
		rb_call_super(argc,argv);
	return self;
}

/*
*/
VALUE _remove(VALUE self,VALUE node)
{
	if(rb_obj_is_kind_of(node, rb_cOgreNode))
		_self->removeNode(wrap<Ogre::Node*>(node));
	else
		rb_call_super(1,&node);
	return self;
}

}}
/*
 * Document-class: Ogre::RibbonTrail
 * 
 * This class represents an RibbonTrail. 
*/
void Init_OgreRibbonTrail(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_cOgreBillboardChain = rb_define_class_under(rb_mOgre,"BillboardChain",rb_cObject);
#endif
	using namespace RubyOgre::RibbonTrail;

	rb_cOgreRibbonTrail = rb_define_class_under(rb_mOgre,"RibbonTrail",rb_cOgreBillboardChain);
	rb_define_method(rb_cOgreRibbonTrail,"each_node",RUBY_METHOD_FUNC(_each),0);
	
	rb_define_method(rb_cOgreRibbonTrail,"add",RUBY_METHOD_FUNC(_add),-1);
	rb_define_method(rb_cOgreRibbonTrail,"remove",RUBY_METHOD_FUNC(_remove),1);
	
	rb_define_attr_method(rb_cOgreRibbonTrail,"trailLength",_getTrailLength,_setTrailLength);

	registerklass<Ogre::RibbonTrail>(rb_cOgreRibbonTrail);
}
