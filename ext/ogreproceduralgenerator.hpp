/*
 * ogreproceduralgenerator.hpp
 *
 *  Created on: 16.09.2012
 *      Author: hanmac
 */

#ifndef OGREPROCEDURALGENERATOR_HPP_
#define OGREPROCEDURALGENERATOR_HPP_

#include "ogreproceduralbuffer.hpp"

class ProceduralGenerator
{
public:
	ProceduralGenerator(VALUE opts);
	virtual ~ProceduralGenerator() {}

	virtual void addToBuffer(ProceduralBuffer *buff) const= 0;
protected:
	void addPoint(ProceduralBuffer *buffer,
		const Ogre::Vector3& position,
		const Ogre::Vector3& normal, const Ogre::Vector2& uv) const;
private:
	Ogre::Quaternion mOrientation;
	Ogre::Vector3 mScale;
	Ogre::Vector3 mPosition;
	// Whether a transform has been defined or not
	bool mTransform;
	bool mEnableNormals;
};

class ProceduralGeneratorFactory
{
public:
	virtual ~ProceduralGeneratorFactory() {}

	virtual ProceduralGenerator* createInstance(VALUE opts) = 0;
	virtual void deleteInstance(ProceduralGenerator* obj) {delete obj;};
};

template <typename T>
class TplProceduralGeneratorFactory : public ProceduralGeneratorFactory
{
public:
	ProceduralGenerator* createInstance(VALUE opts){ return new T(opts);}
};

#endif /* OGREPROCEDURALGENERATOR_HPP_ */
