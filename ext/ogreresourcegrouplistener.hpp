#ifndef __RubyOgreResourceGroupListener_H__
#define __RubyOgreResourceGroupListener_H__

#include "main.hpp"
void Init_OgreResourceGroupListener(VALUE rb_mOgre);
extern VALUE rb_mOgreResourceGroupListener;

class RubyResourceGroupListener : public Ogre::ResourceGroupListener {
	public:
	RubyResourceGroupListener(VALUE val);

	VALUE mRuby;

	void resourceGroupScriptingStarted (const Ogre::String &groupName, size_t scriptCount);
	void scriptParseStarted (const Ogre::String &scriptName, bool &skipThisScript);
	void scriptParseEnded (const Ogre::String &scriptName, bool skipped);
	void resourceGroupScriptingEnded (const Ogre::String &groupName);
	void resourceGroupPrepareStarted (const Ogre::String &groupName, size_t resourceCount);
	void resourcePrepareStarted (const Ogre::ResourcePtr &resource);
	void resourcePrepareEnded (void);
	void worldGeometryPrepareStageStarted (const Ogre::String &description);
	void worldGeometryPrepareStageEnded (void);
	void resourceGroupPrepareEnded (const Ogre::String &groupName);
	void resourceGroupLoadStarted (const Ogre::String &groupName, size_t resourceCount);
	void resourceLoadStarted (const Ogre::ResourcePtr &resource);
	void resourceLoadEnded (void);
	void worldGeometryStageStarted (const Ogre::String &description);
	void worldGeometryStageEnded (void);
	void resourceGroupLoadEnded (const Ogre::String &groupName);
};

//*
template <>
inline VALUE wrap< RubyResourceGroupListener >(RubyResourceGroupListener *obj )
{
	return obj->mRuby;
}
template <>
inline VALUE wrap< Ogre::ResourceGroupListener >(Ogre::ResourceGroupListener *obj )
{
	return wrap<RubyResourceGroupListener>(reinterpret_cast<RubyResourceGroupListener*>(obj));
}
//*/
template <>
inline Ogre::ResourceGroupListener* wrap< Ogre::ResourceGroupListener* >(const VALUE &vmovable)
{
	if ( ! rb_obj_is_kind_of(vmovable, rb_mOgreResourceGroupListener) )
		return NULL;
	Ogre::ResourceGroupListener *movable;
  Data_Get_Struct( vmovable, Ogre::ResourceGroupListener, movable);
	return movable;
}
#endif /* __RubyOgreMovableObject_H__ */
