#include "ogreresource.hpp"
#include "ogreexception.hpp"
#include "ogrebone.hpp"
#define _self wrap<Ogre::SkeletonPtr>(self)
#define _manager Ogre::SkeletonManager::getSingletonPtr()

VALUE rb_cOgreSkeleton;

template <>
VALUE wrap< Ogre::SkeletonPtr >(const Ogre::SkeletonPtr &skeleton )
{
	if(!skeleton.get())
		return Qnil;

	return Data_Wrap_Struct(rb_cOgreSkeleton, NULL, free, new Ogre::SkeletonPtr(skeleton));
}

template <>
Ogre::SkeletonPtr wrap< Ogre::SkeletonPtr >(const VALUE &vskeleton)
{
	if(rb_obj_is_kind_of(vskeleton,rb_cString))
		return _manager->getByName(wrap<Ogre::String>(vskeleton));

	return *unwrapPtr<Ogre::SkeletonPtr>(vskeleton, rb_cOgreSkeleton);
}


namespace RubyOgre
{
namespace Skeleton
{

singlereturn(getRootBone)

/*
*/
VALUE _createBone(int argc,VALUE *argv,VALUE self)
{
	VALUE arg1,arg2;
	rb_scan_args(argc, argv, "02",&arg1,&arg2);
	return wrap(_self->createBone());
}
/*
*/
VALUE _each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap(_self->getBoneIterator());
	return self;
}
/*
*/
VALUE _getBone(VALUE self,VALUE name)
{
	return wrap(_self->getBone(wrap<Ogre::String>(name)));
}

}
}

void Init_OgreSkeleton(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_cOgreResource = rb_define_class_under(rb_mOgre,"Resource",rb_cObject);
#endif
	using namespace RubyOgre::Skeleton;

	rb_cOgreSkeleton = rb_define_class_under(rb_mOgre,"Skeleton",rb_cOgreResource);
	
	rb_define_method(rb_cOgreSkeleton,"createBone",RUBY_METHOD_FUNC(_createBone),-1);
	rb_define_method(rb_cOgreSkeleton,"each",RUBY_METHOD_FUNC(_each),0);
	rb_define_method(rb_cOgreSkeleton,"[]",RUBY_METHOD_FUNC(_getBone),1);
}
