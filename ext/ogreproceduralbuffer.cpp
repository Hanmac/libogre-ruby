/*
 * ogreproceduralbuffer.cpp
 *
 *  Created on: 16.09.2012
 *      Author: hanmac
 */

#include "ogreproceduralbuffer.hpp"
#include "ogreproceduralgenerator.hpp"

typedef std::map<ID,ProceduralGeneratorFactory*> factorymap;
factorymap factories;

void ProceduralBuffer::addForm(ID sym,VALUE opt)
{
	factorymap::iterator it = factories.find(sym);
	if(it != factories.end())
	{
		ProceduralGeneratorFactory *factory = it->second;
		ProceduralGenerator *gen = factory->createInstance(opt);
		gen->addToBuffer(this);
		factory->deleteInstance(gen);
	}
}
