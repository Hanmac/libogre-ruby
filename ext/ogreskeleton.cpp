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
VALUE _eachRoot(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	wrap(_self->getRootBoneIterator());
	return self;
}

/*
*/
VALUE _getBone(VALUE self,VALUE name)
{
	return wrap(_self->getBone(wrap<Ogre::String>(name)));
}

/*
 *
 */
VALUE _export(int argc,VALUE *argv,VALUE self)
{
	VALUE filename,opt,endian = Qnil,version = Qnil;
	rb_scan_args(argc, argv, "11",&filename,&opt);

	if(rb_obj_is_kind_of(opt,rb_cHash))
	{
		endian = rb_hash_aref(opt,ID2SYM(rb_intern("endian")));
		version = rb_hash_aref(opt,ID2SYM(rb_intern("version")));
	}

	Ogre::SkeletonSerializer serial;
	serial.exportSkeleton(_self.get(),
		wrap<Ogre::String>(filename),
		wrapenum<Ogre::SkeletonVersion>(version),
		wrapenum<Ogre::Serializer::Endian>(endian)
	);

	return self;

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
	
	rb_define_method(rb_cOgreSkeleton,"export",RUBY_METHOD_FUNC(_export),-1);

	rb_define_method(rb_cOgreSkeleton,"createBone",RUBY_METHOD_FUNC(_createBone),-1);
	rb_define_method(rb_cOgreSkeleton,"[]",RUBY_METHOD_FUNC(_getBone),1);

	rb_define_method(rb_cOgreSkeleton,"each",RUBY_METHOD_FUNC(_each),0);
	rb_define_method(rb_cOgreSkeleton,"each_root",RUBY_METHOD_FUNC(_eachRoot),0);

	registerenum<Ogre::SkeletonVersion>("Ogre::SkeletonVersion",Ogre::SKELETON_VERSION_LATEST)
		.add(Ogre::SKELETON_VERSION_LATEST,"latest")
		.add(Ogre::SKELETON_VERSION_1_8,"v1_8")
		.add(Ogre::SKELETON_VERSION_1_0,"v1_0");

}
