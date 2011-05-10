#ifndef __RubyOgreMain_H__
#define __RubyOgreMain_H__

#include <ruby.h>
#include <Ogre.h>
#include <typeinfo>

template <typename T>
VALUE wrap(T *arg){
	rb_warn("unknown convertion from %s to VALUE. return nil instat.",typeid(T).name());
	return Qnil;
};

template <typename T>
T wrap(const VALUE &arg){
	rb_warn("unknown convertion from VALUE to %s. return %s() instat.",typeid(T).name(),typeid(T).name());
	return T();
};

extern VALUE rb_mSingleton;


template <typename T,typename Y,typename P,typename A>
VALUE wrap(Ogre::multimap<T,Y,P,A> arg){
	VALUE result = rb_hash_new();
	typename Ogre::multimap<T,Y,P,A>::iterator it;
	for ( it=arg.begin() ; it != arg.end(); it++ ){
		VALUE temp = wrap(it->first);
		if(NIL_P(rb_hash_lookup(result,temp)))
			rb_hash_aset(result,temp,rb_ary_new());
		rb_ary_push(rb_hash_aref(result,temp),wrap(it->second));
	}
	return result;
};

//*template <>
template <typename T>
VALUE wrap(const Ogre::Singleton<T> &s){
	return wrap<T*>(s);
}

template <typename T>
VALUE wrap(const T &arg){
	return wrap(new T(arg));
};
/*
template <typename T>
VALUE wrap(Ogre::SharedPtr<T> ptr){
	return wrap<T>(ptr.get());
};
*/

template <typename T>
VALUE wrap(const std::vector<T> &vec){
	VALUE result = rb_ary_new();
	typename std::vector<T>::const_iterator it;
	for ( it=vec.begin() ; it != vec.end(); it++ )
		rb_ary_push(result,wrap(*it));
	return result;
};


template <typename T>
VALUE wrap(const typename Ogre::vector<T>::type &vec){
	VALUE result = rb_ary_new();
	typename Ogre::vector<T>::type::const_iterator it;
	for ( it=vec.begin() ; it != vec.end(); it++ )
		rb_ary_push(result,wrap(*it));
	return result;
};

template <typename T>
VALUE wrap(const typename Ogre::vector<T*>::type &vec){
	VALUE result = rb_ary_new();
	typename Ogre::vector<T*>::type::const_iterator it;
	for ( it=vec.begin() ; it != vec.end(); it++ )
		rb_ary_push(result,wrap<T>(*it));
	return result;
};

template <typename T>
VALUE wrap(const Ogre::SharedPtr<typename Ogre::list<T>::type> &vec){
	VALUE result = rb_ary_new();
	typename Ogre::list<T>::type::const_iterator it;
	for ( it=vec->begin() ; it != vec->end(); ++it ){
		rb_ary_push(result,wrap<T>(*it));
	}
	return result;
};


template <typename T>
VALUE wrap(const Ogre::SharedPtr<typename Ogre::vector<T>::type> &vec){
	VALUE result = rb_ary_new();
	typename Ogre::vector<T>::type::const_iterator it;
	for ( it=vec->begin() ; it != vec->end(); ++it ){
		rb_ary_push(result,wrap<T>(*it));
	}
	return result;
};

template <>
inline VALUE wrap< Ogre::String >(const Ogre::String &st )
{
	return rb_str_new2(st.c_str());
}
/*
template <>
inline VALUE wrap< Ogre::StringVector >(const Ogre::StringVector &vec )
{
	return wrap((const Ogre::vector<Ogre::String>::type)vec);
}
*/

template <>
inline VALUE wrap< Ogre::NameValuePairList >(const Ogre::NameValuePairList &map )
{
	VALUE result = rb_hash_new();
	Ogre::NameValuePairList::const_iterator it;
	for ( it=map.begin() ; it != map.end(); it++ )
		rb_hash_aset(result,wrap(it->first),wrap(it->second));
	return result;
}
/*

*/
VALUE OgreSingleton_method_missing(int argc,VALUE *argv,VALUE self);
#endif /* __RubyOgreMain_H__ */

