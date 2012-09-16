#include "ogrestringinterface.hpp"
#include "ogrevector3.hpp"
#include "ogrematrix3.hpp"
#include "ogrematrix4.hpp"
#include "ogrecolor.hpp"
#include "ogrequaternion.hpp"

#include <iostream>

#define _self wrap<Ogre::StringInterface*>(self)


template <>
Ogre::StringInterface* wrap< Ogre::StringInterface* >(const VALUE &interface)
{
	if(rb_obj_is_kind_of(interface, rb_cOgreResource))
		return wrap< Ogre::Resource* >(interface);
	if(rb_obj_is_kind_of(interface, rb_cOgreParticleSystem))
		return wrap< Ogre::ParticleSystem* >(interface);
	if(rb_obj_is_kind_of(interface, rb_cOgreParticleEmitter))
		return wrap< Ogre::ParticleEmitter* >(interface);
	if(rb_obj_is_kind_of(interface, rb_cOgreParticleAffector))
		return wrap< Ogre::ParticleAffector* >(interface);
	return NULL;
}


VALUE rb_mOgreStringInterface;
namespace RubyOgre {
namespace StringInterface {

VALUE _getParameter_impl(const Ogre::String &param,Ogre::ParameterType type)
{
	switch(type){
	case Ogre::PT_BOOL:
		return wrap(Ogre::StringConverter::parseBool(param));
	case Ogre::PT_REAL:
		return DBL2NUM(Ogre::StringConverter::parseReal(param));
	case Ogre::PT_INT:
		return wrap(Ogre::StringConverter::parseInt(param));
	case Ogre::PT_SHORT:
		return wrap(Ogre::StringConverter::parseInt(param));
	case Ogre::PT_LONG:
		return wrap(Ogre::StringConverter::parseLong(param));
	case Ogre::PT_UNSIGNED_INT:
		return wrap(Ogre::StringConverter::parseUnsignedInt(param));
	case Ogre::PT_UNSIGNED_SHORT:
		return wrap(Ogre::StringConverter::parseUnsignedInt(param));
	case Ogre::PT_UNSIGNED_LONG:
		return wrap(Ogre::StringConverter::parseUnsignedLong(param));
	case Ogre::PT_VECTOR3:
		return wrap(Ogre::StringConverter::parseVector3(param));
	case Ogre::PT_MATRIX3:
		return wrap(Ogre::StringConverter::parseMatrix3(param));
	case Ogre::PT_MATRIX4:
		return wrap(Ogre::StringConverter::parseMatrix4(param));
	case Ogre::PT_QUATERNION:
		return wrap(Ogre::StringConverter::parseQuaternion(param));
	case Ogre::PT_COLOURVALUE:
		return wrap(Ogre::StringConverter::parseColourValue(param));
	default:
		return wrap(param);
	}
}
/*
*/
VALUE _getParameter(VALUE self,VALUE name)
{
	Ogre::String cstring = wrap<Ogre::String>(name);
	Ogre::ParameterList list = _self->getParameters();
	for(Ogre::ParameterList::iterator it = list.begin();
		it != list.end();
		++it)
	{
		if(it->name == cstring){
			return _getParameter_impl(_self->getParameter(cstring),it->paramType);
		}
	}
	//return wrap(_self->getParameter(wrap<Ogre::String>(name)));
	return Qnil;
}

/*
*/
VALUE _setParameter(VALUE self,VALUE name, VALUE val)
{
	Ogre::String cstring = wrap<Ogre::String>(name);
	if(rb_obj_is_kind_of(val,rb_cString))
		_self->setParameter(cstring,wrap<Ogre::String>(val));
	Ogre::ParameterList list = _self->getParameters();
	for(Ogre::ParameterList::iterator it = list.begin();
		it != list.end();
		++it)
	{
		if(it->name == cstring)
			switch(it->paramType){
			case Ogre::PT_BOOL:
				_self->setParameter(cstring,Ogre::StringConverter::toString(RTEST(val)));
				break;
			case Ogre::PT_REAL:
				_self->setParameter(cstring,Ogre::StringConverter::toString((Ogre::Real)NUM2DBL(val)));
				break;
			case Ogre::PT_INT:
				_self->setParameter(cstring,Ogre::StringConverter::toString(NUM2INT(val)));
				break;
			case Ogre::PT_SHORT:
				_self->setParameter(cstring,Ogre::StringConverter::toString(NUM2INT(val)));
				break;
			case Ogre::PT_LONG:
				_self->setParameter(cstring,Ogre::StringConverter::toString(NUM2LONG(val)));
				break;
			case Ogre::PT_UNSIGNED_INT:
				_self->setParameter(cstring,Ogre::StringConverter::toString(NUM2UINT(val)));
				break;
			case Ogre::PT_UNSIGNED_SHORT:
				_self->setParameter(cstring,Ogre::StringConverter::toString(NUM2UINT(val)));
				break;
			case Ogre::PT_UNSIGNED_LONG:
				_self->setParameter(cstring,Ogre::StringConverter::toString(NUM2ULONG(val)));
				break;
			case Ogre::PT_VECTOR3:
				_self->setParameter(cstring,Ogre::StringConverter::toString(wrap<Ogre::Vector3>(val)));
				break;
			case Ogre::PT_MATRIX3:
				_self->setParameter(cstring,Ogre::StringConverter::toString(wrap<Ogre::Matrix3>(val)));
				break;
			case Ogre::PT_MATRIX4:
				_self->setParameter(cstring,Ogre::StringConverter::toString(wrap<Ogre::Matrix4>(val)));
				break;
			case Ogre::PT_QUATERNION:
				_self->setParameter(cstring,Ogre::StringConverter::toString(wrap<Ogre::Quaternion>(val)));
				break;
			case Ogre::PT_COLOURVALUE:
				_self->setParameter(cstring,Ogre::StringConverter::toString(wrap<Ogre::ColourValue>(val)));
				break;
			default:
				break;
			}
	}

	return self;
}

VALUE _each_Parameter(VALUE self)
{
	RETURN_ENUMERATOR(self,0,NULL);
	Ogre::StringInterface *inter = _self;
	const Ogre::ParameterList &list(inter->getParameters());
	for(Ogre::ParameterList::const_iterator it = list.begin();
		it != list.end();
		++it)
	{
		//std::cout << (it->name);
		const Ogre::String str = inter->getParameter(it->name);
		rb_yield_values(2,wrap(it->name),_getParameter_impl(str,it->paramType));
	}


	return self;
}



}
}
/*
 * Document-module: Ogre::StringInterface
 *
 * This module defines access to the parameters
*/
void Init_OgreStringInterface(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
#endif
	using namespace RubyOgre::StringInterface;

	rb_mOgreStringInterface = rb_define_module_under(rb_mOgre,"StringInterface");

	rb_define_method(rb_mOgreStringInterface,"getParameter",RUBY_METHOD_FUNC(_getParameter),1);
	rb_define_method(rb_mOgreStringInterface,"setParameter",RUBY_METHOD_FUNC(_setParameter),2);

	rb_define_method(rb_mOgreStringInterface,"each_param",RUBY_METHOD_FUNC(_each_Parameter),0);
}
