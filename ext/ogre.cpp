#include "ogrecolor.hpp"
#include "ogrevector2.hpp"
#include "ogrevector3.hpp"
#include "ogrevector4.hpp"
#include "ogreradian.hpp"
#include "ogredegree.hpp"
#include "ogresphere.hpp"
#include "ogreroot.hpp"
#include "ogreplane.hpp"
#include "ogreresource.hpp"
#include "ogrerect.hpp"
#include "ogrebox.hpp"
#include "ogreimage.hpp"
#include "ogreexception.hpp"
#include "ogrefileinfo.hpp"
#include "ogreresourcegroup.hpp"
#include "ogrepolygon.hpp"
#include "ogredatastream.hpp"
#include "ogreconfigfile.hpp"
#include "ogrerendertarget.hpp"
#include "ogrerenderwindow.hpp"
#include "ogrerendersystem.hpp"
#include "ogrescenemanager.hpp"
#include "ogremovableobject.hpp"
#include "ogremovableobjectlistener.hpp"
#include "ogrelight.hpp"
#include "ogrenode.hpp"
#include "ogrescenenode.hpp"
#include "ogrebone.hpp"
#include "ogreray.hpp"
#include "ogrelog.hpp"
#include "ogreloglistener.hpp"
#include "ogreaxisalignedbox.hpp"
#include "ogreplaneboundedvolume.hpp"
#include "ogrematrix3.hpp"
#include "ogrematrix4.hpp"
#include "ogrequaternion.hpp"
#include "ogretexture.hpp"
#include "ogremesh.hpp"
#include "ogresubmesh.hpp"
#include "ogresubentity.hpp"
#include "ogrematerial.hpp"
#include "ogretechnique.hpp"
#include "ogrepass.hpp"
#include "ogretextureunitstate.hpp"
#include "ogrelayerblendmode.hpp"

#include "ogrepose.hpp"

#include "ogrecompositor.hpp"
#include "ogrecompositorchain.hpp"
#include "ogretexturedefinition.hpp"
#include "ogrecompositiontechnique.hpp"
#include "ogrecompositorinstance.hpp"

#include "ogreviewport.hpp"

#include "ogrebillboard.hpp"
#include "ogrebillboardchain.hpp"
#include "ogrebillboardchainelement.hpp"

#include "ogreparticle.hpp"
#include "ogreparticleemitter.hpp"

#include "ogrestringinterface.hpp"

#include "ogresimplespline.hpp"
#include "ogrerotationalspline.hpp"

#include <OgreAny.h>

klassregistertype klassregister;
enumregistertype enumregister;

VALUE rb_mOgre;
VALUE globalholder;

VALUE Ogre_dummy0(VALUE self)
{
	return Qnil;
}
VALUE Ogre_dummy1(VALUE self,VALUE obj1)
{
	return Qnil;
}
VALUE Ogre_dummy2(VALUE self,VALUE obj1,VALUE obj2)
{
	return Qnil;
}
VALUE Ogre_dummy3(VALUE self,VALUE obj1,VALUE obj2,VALUE obj3)
{
	return Qnil;
}
VALUE Ogre_dummy4(VALUE self,VALUE obj1,VALUE obj2,VALUE obj3,VALUE obj4)
{
	return Qnil;
}


template <>
VALUE wrap< bool >(const bool &st )
{
	return st ? Qtrue : Qfalse;
}

template <>
bool wrap< bool >(const VALUE &val )
{
	return RTEST(val);
}

template <>
VALUE wrap< double >(const double &st )
{
	return DBL2NUM(st);
}

template <>
double wrap< double >(const VALUE &val )
{
	return NUM2DBL(val);
}


template <>
VALUE wrap< float >(const float &st )
{
	return DBL2NUM(st);
}

template <>
float wrap< float >(const VALUE &val )
{
	return NUM2DBL(val);
}


template <>
VALUE wrap< unsigned short >(const unsigned short &st )
{
	return UINT2NUM(st);
}

template <>
unsigned short wrap< unsigned short >(const VALUE &val )
{
	return NUM2UINT(val);
}

template <>
VALUE wrap< unsigned int >(const unsigned int &st )
{
	return UINT2NUM(st);
}

template <>
unsigned int wrap< unsigned int >(const VALUE &val )
{
	return NUM2UINT(val);
}


template <>
VALUE wrap< Ogre::String >(const Ogre::String &st )
{
	if(st.c_str())
		return rb_str_new2(st.c_str());
	return Qnil;
}

template <>
Ogre::String wrap< Ogre::String >(const VALUE &val )
{
	if(NIL_P(val))
		return "";
	else if (rb_obj_is_kind_of(val, rb_cString))
		return rb_string_value_cstr((volatile VALUE*)(&val));
	else
		return wrap< Ogre::String >(rb_funcall(val,rb_intern("to_s"),0));
}

template <>
VALUE wrap< Ogre::StringVector >(const Ogre::StringVector &vec )
{
	return wrap<Ogre::String>(vec);
}


template <>
VALUE wrap< Ogre::NameValuePairList >(const Ogre::NameValuePairList &map )
{
	VALUE result = rb_hash_new();
	Ogre::NameValuePairList::const_iterator it;
	for ( it=map.begin() ; it != map.end(); it++ )
		rb_hash_aset(result,wrap(it->first),wrap(it->second));
	return result;
}

int foreach(VALUE key, VALUE value, VALUE arg)
{
	((Ogre::NameValuePairList*)(arg))->insert(std::make_pair(wrap<Ogre::String>(key),wrap<Ogre::String>(value)));
	return ST_CONTINUE;
}

template <>
Ogre::NameValuePairList* wrap< Ogre::NameValuePairList* >(const VALUE &map )
{
	Ogre::NameValuePairList *result = new Ogre::NameValuePairList;
	if(!NIL_P(map))
		rb_hash_foreach(map,(int (*)(ANYARGS))(foreach),(VALUE)result);
	return result;
}




RubyAny::RubyAny(VALUE obj)
: value(obj)
{
	rb_hash_aset(globalholder,INT2NUM(obj),obj);
}

RubyAny::~RubyAny() {
	rb_hash_delete(globalholder,INT2NUM(value));
}

VALUE wrap(void *obj,VALUE klass)
{
	return Data_Wrap_Struct(klass, NULL, NULL, obj);
}

#define macro_wrap2(T,V) \
VALUE wrap(T *obj,VALUE klass)\
{\
	VALUE result;\
	Ogre::UserObjectBindings &bind = static_cast<V*>(obj)->getUserObjectBindings(); \
	if(bind.getUserAny().isEmpty())\
	{\
		result = wrap((void*)obj,klass);\
		bind.setUserAny(Ogre::Any(Ogre::SharedPtr<RubyAny>(new RubyAny(result))));\
	}else\
		result = Ogre::any_cast<Ogre::SharedPtr<RubyAny> >(bind.getUserAny())->value;\
	return result;\
}

#define macro_wrap(T) macro_wrap2(T,T)

macro_wrap(Ogre::Node)
macro_wrap(Ogre::MovableObject)
macro_wrap(Ogre::Renderable)
macro_wrap2(Ogre::Frustum,Ogre::MovableObject)
macro_wrap2(Ogre::BillboardChain,Ogre::MovableObject)
macro_wrap2(Ogre::BillboardSet,Ogre::MovableObject)
macro_wrap2(Ogre::ParticleSystem,Ogre::ParticleSystem)

void rb_define_attr_method(VALUE klass,std::string name,VALUE(get)(VALUE),VALUE(set)(VALUE,VALUE))
{
	rb_define_method(klass,name.c_str(),RUBY_METHOD_FUNC(get),0);
	rb_define_method(klass,(name + "=").c_str(),RUBY_METHOD_FUNC(set),1);
}

extern "C" void Init_ogre(void)
{
	rb_mOgre = rb_define_module("Ogre");
	
	Init_OgreRoot(rb_mOgre);
	Init_OgreColor(rb_mOgre);
	Init_OgreVector2(rb_mOgre);
	Init_OgreVector3(rb_mOgre);
	Init_OgreVector4(rb_mOgre);
	Init_OgreRadian(rb_mOgre);
	Init_OgreDegree(rb_mOgre);
	Init_OgreSphere(rb_mOgre);
	Init_OgreRay(rb_mOgre);
	Init_OgrePlane(rb_mOgre);
	
	Init_OgreStringInterface(rb_mOgre);
	
	Init_OgreResource(rb_mOgre);
	Init_OgreFont(rb_mOgre);
	Init_OgreSkeleton(rb_mOgre);
	Init_OgreGpuProgram(rb_mOgre);
	Init_OgreHighGpuProgram(rb_mOgre);
	
	Init_OgreBillboard(rb_mOgre);
	
	
	Init_OgreRect(rb_mOgre);
	Init_OgreBox(rb_mOgre);
	Init_OgreImage(rb_mOgre);
	Init_OgreException(rb_mOgre);
	Init_OgreFileInfo(rb_mOgre);
	Init_OgreResourceGroup(rb_mOgre);


	Init_OgrePolygon(rb_mOgre);
	Init_OgreDataStream(rb_mOgre);
	Init_OgreConfigFile(rb_mOgre);
	Init_OgreRenderTarget(rb_mOgre);
	Init_OgreRenderWindow(rb_mOgre);
	Init_OgreRenderSystem(rb_mOgre);
	Init_OgreSceneManager(rb_mOgre);

	Init_OgreViewport(rb_mOgre);

	Init_OgreMovableObject(rb_mOgre);
	Init_OgreMovableObjectListener(rb_mOgre);
	Init_OgreLight(rb_mOgre);
	Init_OgreMovablePlane(rb_mOgre);
	Init_OgreFrustum(rb_mOgre);
	Init_OgreCamera(rb_mOgre);
	Init_OgreBillboard(rb_mOgre);
	Init_OgreBillboardSet(rb_mOgre);
	Init_OgreBillboardChain(rb_mOgre);
	Init_OgreBillboardChainElement(rb_mOgre);

	Init_OgreRibbonTrail(rb_mOgre);

	Init_OgreNode(rb_mOgre);
	Init_OgreSceneNode(rb_mOgre);
	Init_OgreBone(rb_mOgre);
	
	Init_OgreLog(rb_mOgre);
	Init_OgreLogListener(rb_mOgre);
	Init_OgreAxisAlignedBox(rb_mOgre);
	Init_OgrePlaneBoundedVolume(rb_mOgre);

	Init_OgreMatrix3(rb_mOgre);
	Init_OgreMatrix4(rb_mOgre);
	Init_OgreQuaternion(rb_mOgre);

	Init_OgreTexture(rb_mOgre);
	Init_OgreMaterial(rb_mOgre);
	Init_OgreMesh(rb_mOgre);
	Init_OgreSubMesh(rb_mOgre);
	
	Init_OgrePose(rb_mOgre);

	Init_OgreEntity(rb_mOgre);
	Init_OgreSubEntity(rb_mOgre);

	Init_OgreTechnique(rb_mOgre);
	Init_OgrePass(rb_mOgre);
	Init_OgreTextureUnitState(rb_mOgre);
	Init_OgreLayerBlendMode(rb_mOgre);
	
	Init_OgreCompositor(rb_mOgre);
	Init_OgreCompositionTechnique(rb_mOgre);
	Init_OgreCompositorChain(rb_mOgre);
	Init_OgreCompositorInstance(rb_mOgre);

	Init_OgreTextureDefinition(rb_mOgre);
	
	Init_OgreParticleSystem(rb_mOgre);
	Init_OgreParticle(rb_mOgre);
	Init_OgreParticleEmitter(rb_mOgre);
	Init_OgreParticleAffector(rb_mOgre);
	
	Init_OgreSimpleSpline(rb_mOgre);
	Init_OgreRotationalSpline(rb_mOgre);
	
	VALUE array[4];
	array[0]=rb_str_new2("%d.%d.%d");
	array[1]=INT2NUM(OGRE_VERSION_MAJOR);
	array[2]=INT2NUM(OGRE_VERSION_MINOR);
	array[3]=INT2NUM(OGRE_VERSION_PATCH);
	rb_const_set(rb_mOgre,rb_intern("Version"),rb_f_sprintf(4,array));
	rb_const_set(rb_mOgre,rb_intern("VersionName"),rb_str_new2(OGRE_VERSION_NAME));

	globalholder = rb_hash_new();
	rb_global_variable(&globalholder);

//	rb_warn("%lu klasses",klassregister.size());
//	for(klassregistertype::iterator it = klassregister.begin();
//			it != klassregister.end();
//			++it)
//		rb_warn("%s => %s",it->first.c_str(),rb_class2name(it->second));
//	rb_warn("%lu enums",enumregister.size());
//	for(enumregistertype::iterator it = enumregister.begin();
//				it != enumregister.end();
//				++it)
//	{
//		rb_warn("%s:",it->first.c_str());
//		for(enumregistertype::mapped_type::iterator it2 = it->second.begin();
//						it2 != it->second.end();
//						++it2)
//			rb_warn("%d => %s",it2->first,rb_id2name(it2->second));
//	}
//
}
