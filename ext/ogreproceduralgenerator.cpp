/*
 * ogreproceduralgenerator.cpp
 *
 *  Created on: 16.09.2012
 *      Author: hanmac
 */

#include "ogreproceduralgenerator.hpp"

ProceduralGenerator::ProceduralGenerator(VALUE opt) : mTransform(false),mEnableNormals(false)
{
	if(rb_obj_is_kind_of(opt,rb_cHash))
	{
		VALUE temp;
		if(!NIL_P(temp = rb_hash_aref(opt,ID2SYM(rb_intern("orientation")))))
		{
			mOrientation = wrap<Ogre::Quaternion>(temp);
			mTransform = true;
		}
		if(!NIL_P(temp = rb_hash_aref(opt,ID2SYM(rb_intern("position")))))
		{
			mPosition = wrap<Ogre::Vector3>(temp);
			mTransform = true;
		}
		if(!NIL_P(temp = rb_hash_aref(opt,ID2SYM(rb_intern("scale")))))
		{
			mScale = wrap<Ogre::Vector3>(temp);
			mTransform = true;
		}

	}
}

void ProceduralGenerator::addPoint(ProceduralBuffer *buffer,
	const Ogre::Vector3& position,
	const Ogre::Vector3& normal, const Ogre::Vector2& uv) const
{

}

