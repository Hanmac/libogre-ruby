#ifndef __RubyOgreDataStream_H__
#define __RubyOgreDataStream_H__

#include "main.hpp"
void Init_OgreDataStream(VALUE rb_mOgre);
extern VALUE rb_cOgreDataStream;

struct rb_ogre_datastream_holder
{
Ogre::DataStreamPtr ptr;
};

template <>
inline VALUE wrap< Ogre::DataStreamPtr >(const Ogre::DataStreamPtr &datastream )
{
	rb_ogre_datastream_holder *tmp = new rb_ogre_datastream_holder;
	tmp->ptr=datastream;
	return Data_Wrap_Struct(rb_cOgreDataStream, NULL, free, tmp);
}
template <>
inline VALUE wrap< Ogre::DataStream >(Ogre::DataStream *datastream )
{
	return Data_Wrap_Struct(rb_cOgreDataStream, NULL, NULL, datastream);
}
template <>
inline VALUE wrap< Ogre::DataStreamList >(const Ogre::DataStreamList &vec )
{
	VALUE result = rb_ary_new();
	Ogre::DataStreamList::const_iterator it;
	for ( it=vec.begin() ; it != vec.end(); it++ )
		rb_ary_push(result,wrap(*it));
	return result;
}

template <>
inline VALUE wrap< Ogre::DataStreamListPtr >(const Ogre::DataStreamListPtr &vec )
{
	VALUE result = rb_ary_new();
	Ogre::DataStreamList::const_iterator it;
	for ( it=vec->begin() ; it != vec->end(); it++ )
		rb_ary_push(result,wrap(*it));
	return result;
}

template <>
inline Ogre::DataStreamPtr wrap< Ogre::DataStreamPtr >(const VALUE &vdatastream)
{
	if ( ! rb_obj_is_kind_of(vdatastream, rb_cOgreDataStream) )
		rb_raise(rb_eTypeError,"exepted %s got %s!",rb_class2name(rb_cOgreDataStream),rb_obj_classname(vdatastream));
	rb_ogre_datastream_holder *datastream;
  Data_Get_Struct( vdatastream, rb_ogre_datastream_holder, datastream);
	return datastream->ptr;
}

template <>
inline Ogre::DataStream* wrap< Ogre::DataStream* >(const VALUE &vdatastream)
{
	return wrap<Ogre::DataStreamPtr>(vdatastream).get();
}
#endif /* __RubyOgreDataStream_H__ */
