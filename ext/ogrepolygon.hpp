#ifndef __RubyOgrePolygon_H__
#define __RubyOgrePolygon_H__

#include "main.hpp"
void Init_OgrePolygon(VALUE rb_mOgre);
extern VALUE rb_cOgrePolygon;


template <>
inline VALUE wrap< Ogre::Polygon >(Ogre::Polygon *polygon )
{
	return Data_Wrap_Struct(rb_cOgrePolygon, NULL, free, polygon);
}

template <>
inline VALUE wrap< Ogre::Polygon >(Ogre::Polygon polygon )
{
	Ogre::Polygon *temp = new Ogre::Polygon(polygon);
	return wrap(temp);
}

template <>
inline VALUE wrap< Ogre::Polygon::EdgeMap >(Ogre::Polygon::EdgeMap edge )
{
	VALUE result = rb_hash_new();
	Ogre::Polygon::EdgeMap::iterator it;
	for ( it=edge.begin() ; it != edge.end(); it++ ){
		VALUE temp = wrap(it->first);
		if(NIL_P(rb_hash_lookup(result,temp)))
			rb_hash_aset(result,temp,rb_ary_new());
		rb_ary_push(rb_hash_aref(result,temp),wrap(it->second));
	}
	return result;
}
template <>
inline Ogre::Polygon* wrap< Ogre::Polygon* >(const VALUE &vpolygon)
{
	if ( ! rb_obj_is_kind_of(vpolygon, rb_cOgrePolygon) )
		return NULL;
	Ogre::Polygon *polygon;
  Data_Get_Struct( vpolygon, Ogre::Polygon, polygon);
	return polygon;
}
#endif /* __RubyOgrePolygon_H__ */
