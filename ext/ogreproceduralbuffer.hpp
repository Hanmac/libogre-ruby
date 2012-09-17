/*
 * ogreproceduralbuffer.hpp
 *
 *  Created on: 16.09.2012
 *      Author: hanmac
 */

#ifndef OGREPROCEDURALBUFFER_HPP_
#define OGREPROCEDURALBUFFER_HPP_

#include "main.hpp"

class ProceduralBuffer
{
public:
	void addForm(ID sym,VALUE opt);

	Ogre::MeshPtr toMesh(const Ogre::String& name, const Ogre::String& group);
};

#endif /* OGREPROCEDURALBUFFER_HPP_ */
