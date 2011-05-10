#include "ogreresourcemanager.hpp"
#include "ogreresource.hpp"
#define _self wrap<Ogre::ResourceManager*>(self)
VALUE rb_cOgreResourceManager;
VALUE rb_cOgreFontManager;
VALUE rb_cOgreMeshManager;
VALUE rb_cOgreMaterialManager;
VALUE rb_cOgreCompositorManager;
VALUE rb_cOgreGpuProgramManager;
VALUE rb_cOgreHighLevelGpuProgramManager;
VALUE rb_cOgreSkeletonManager;
VALUE rb_cOgreTextureManager;

VALUE OgreFontManager_alloc(VALUE self)
{
	return wrap(Ogre::FontManager::getSingletonPtr());
}
VALUE OgreMeshManager_alloc(VALUE self)
{
	return wrap(Ogre::MeshManager::getSingletonPtr());
}
VALUE OgreMaterialManager_alloc(VALUE self)
{
	return wrap(Ogre::MaterialManager::getSingletonPtr());
}
VALUE OgreCompositorManager_alloc(VALUE self)
{
	return wrap(Ogre::CompositorManager::getSingletonPtr());
}
VALUE OgreGpuProgramManager_alloc(VALUE self)
{
	return wrap(Ogre::GpuProgramManager::getSingletonPtr());
}
VALUE OgreHighLevelGpuProgramManager_alloc(VALUE self)
{
	return wrap(Ogre::HighLevelGpuProgramManager::getSingletonPtr());
}
VALUE OgreSkeletonManager_alloc(VALUE self)
{
	return wrap(Ogre::SkeletonManager::getSingletonPtr());
}
VALUE OgreTextureManager_alloc(VALUE self)
{
	return wrap(Ogre::TextureManager::getSingletonPtr());
}


/*

*/
VALUE OgreResourceManager_remove(VALUE self,VALUE name)
{
	_self->remove(rb_string_value_cstr(&name));
	return self;
}
/*

*/
VALUE OgreResourceManager_resourceExists(VALUE self,VALUE name)
{
	return _self->resourceExists(rb_string_value_cstr(&name)) ? Qtrue : Qfalse;
}
/*

*/
VALUE OgreResourceManager_unload(VALUE self,VALUE name)
{
	_self->unload(rb_string_value_cstr(&name));
	return self;
}
/*

*/
VALUE OgreResourceManager_getResourceType(VALUE self)
{
	return wrap(_self->getResourceType());
}
/*

*/
VALUE OgreResourceManager_getScriptPatterns(VALUE self)
{
	return wrap<Ogre::String>(_self->getScriptPatterns());
}
/*

*/
VALUE OgreResourceManager_getVerbose(VALUE self)
{
	return _self->getVerbose() ? Qtrue : Qfalse;
}
/*

*/
VALUE OgreResourceManager_setVerbose(VALUE self,VALUE val)
{
	_self->setVerbose(RTEST(val));
	return val;
}
/*
 * call-seq:
 *   resourcemanager.inspect -> String
 * 
 * Human-readable description. 
 * ===Return value
 * String
*/
VALUE OgreResourceManager_inspect(VALUE self)
{
	if(rb_obj_is_kind_of(self,rb_mSingleton)){
		VALUE array[2];
		array[0]=rb_str_new2("#<%s>");
		array[1]=rb_class_of(self);
		return rb_f_sprintf(2,array);	
	}else{
		VALUE array[3];
		array[0]=rb_str_new2("#<%s:%s>");
		array[1]=rb_class_of(self);
		array[2]=OgreResourceManager_getResourceType(self);
		return rb_f_sprintf(3,array);
	}
}
/*


*/
VALUE OgreResourceManager_each(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	Ogre::ResourceManager::ResourceMapIterator map = _self->getResourceIterator();
	Ogre::ResourceManager::ResourceMapIterator::iterator it;
	for (it = map.begin(); it != map.end(); ++it)
		rb_yield_values(2,ULONG2NUM(it->first),wrap(it->second));
	return self;
}
/*


*/
VALUE OgreResourceManager_method_missing(int argc,VALUE *argv,VALUE self)
{
	VALUE temp = rb_funcall(self,rb_intern("instance"),0);
	return rb_funcall2(temp,rb_intern("send"),argc,argv);
}

void Init_OgreResourceManager(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_mSingleton = rb_define_module("Singleton");
#endif
	rb_cOgreResourceManager = rb_define_class_under(rb_mOgre,"ResourceManager",rb_cObject);
	rb_undef_alloc_func(rb_cOgreResourceManager);

	rb_define_singleton_method(rb_cOgreResourceManager,"method_missing",RUBY_METHOD_FUNC(OgreSingleton_method_missing),-1);// in ogre.y

	rb_define_method(rb_cOgreResourceManager,"remove",RUBY_METHOD_FUNC(OgreResourceManager_remove),1);
	rb_define_method(rb_cOgreResourceManager,"resourceExists?",RUBY_METHOD_FUNC(OgreResourceManager_resourceExists),1);
	rb_define_method(rb_cOgreResourceManager,"unload",RUBY_METHOD_FUNC(OgreResourceManager_unload),1);
	
	rb_define_method(rb_cOgreResourceManager,"resourceType",RUBY_METHOD_FUNC(OgreResourceManager_getResourceType),0);
	rb_define_method(rb_cOgreResourceManager,"scriptPatterns",RUBY_METHOD_FUNC(OgreResourceManager_getScriptPatterns),0);
	
	rb_define_method(rb_cOgreResourceManager,"verbose",RUBY_METHOD_FUNC(OgreResourceManager_getVerbose),0);
	rb_define_method(rb_cOgreResourceManager,"verbose=",RUBY_METHOD_FUNC(OgreResourceManager_setVerbose),1);
	
	rb_define_method(rb_cOgreResourceManager,"inspect",RUBY_METHOD_FUNC(OgreResourceManager_inspect),0);
	rb_define_method(rb_cOgreResourceManager,"each",RUBY_METHOD_FUNC(OgreResourceManager_each),0);
	
	rb_include_module(rb_cOgreResourceManager,rb_mEnumerable);
	
	rb_cOgreFontManager = rb_define_class_under(rb_mOgre,"FontManager",rb_cOgreResourceManager);
	rb_define_alloc_func(rb_cOgreFontManager,OgreFontManager_alloc);
	rb_funcall(rb_cOgreFontManager,rb_intern("include"),1,rb_mSingleton);

	rb_cOgreMeshManager = rb_define_class_under(rb_mOgre,"MeshManager",rb_cOgreResourceManager);
	rb_define_alloc_func(rb_cOgreMeshManager,OgreMeshManager_alloc);
	rb_funcall(rb_cOgreMeshManager,rb_intern("include"),1,rb_mSingleton);

	rb_cOgreMaterialManager = rb_define_class_under(rb_mOgre,"MaterialManager",rb_cOgreResourceManager);
	rb_define_alloc_func(rb_cOgreMaterialManager,OgreMaterialManager_alloc);
	rb_funcall(rb_cOgreMaterialManager,rb_intern("include"),1,rb_mSingleton);

	rb_cOgreCompositorManager = rb_define_class_under(rb_mOgre,"CompositorManager",rb_cOgreResourceManager);
	rb_define_alloc_func(rb_cOgreCompositorManager,OgreCompositorManager_alloc);
	rb_funcall(rb_cOgreCompositorManager,rb_intern("include"),1,rb_mSingleton);

	rb_cOgreGpuProgramManager = rb_define_class_under(rb_mOgre,"GpuProgramManager",rb_cOgreResourceManager);
	rb_define_alloc_func(rb_cOgreGpuProgramManager,OgreGpuProgramManager_alloc);
	rb_funcall(rb_cOgreGpuProgramManager,rb_intern("include"),1,rb_mSingleton);

	rb_cOgreHighLevelGpuProgramManager = rb_define_class_under(rb_mOgre,"HighLevelGpuProgramManager",rb_cOgreResourceManager);
	rb_define_alloc_func(rb_cOgreHighLevelGpuProgramManager,OgreHighLevelGpuProgramManager_alloc);
	rb_funcall(rb_cOgreHighLevelGpuProgramManager,rb_intern("include"),1,rb_mSingleton);

	rb_cOgreSkeletonManager = rb_define_class_under(rb_mOgre,"SkeletonManager",rb_cOgreResourceManager);
	rb_define_alloc_func(rb_cOgreSkeletonManager,OgreSkeletonManager_alloc);
	rb_funcall(rb_cOgreSkeletonManager,rb_intern("include"),1,rb_mSingleton);

	rb_cOgreTextureManager = rb_define_class_under(rb_mOgre,"TextureManager",rb_cOgreResourceManager);
	rb_define_alloc_func(rb_cOgreTextureManager,OgreTextureManager_alloc);
	rb_funcall(rb_cOgreTextureManager,rb_intern("include"),1,rb_mSingleton);

	#if 0
	rb_include_module(rb_cOgreFontManager,rb_mSingleton);
	rb_include_module(rb_cOgreMeshManager,rb_mSingleton);
	rb_include_module(rb_cOgreMaterialManager,rb_mSingleton);
	rb_include_module(rb_cOgreCompositorManager,rb_mSingleton);
	rb_include_module(rb_cOgreGpuProgramManager,rb_mSingleton);
	rb_include_module(rb_cOgreHighLevelGpuProgramManager,rb_mSingleton);
	rb_include_module(rb_cOgreSkeletonManager,rb_mSingleton);
	rb_include_module(rb_cOgreTextureManager,rb_mSingleton);
	#endif

}
