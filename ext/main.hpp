#ifndef __RubyOgreMain_H__
#define __RubyOgreMain_H__

#include <ruby.h>
#include <Ogre.h>

template <typename T>
VALUE wrap(T *arg){ return Qnil;};

template <typename T>
VALUE wrap(const T &arg){
	T *temp = new T(arg);
	return wrap(temp);
};
template <typename T>
T wrap(const VALUE &arg){};

extern VALUE rb_mSingleton;


template <>
inline VALUE wrap< Ogre::String >(const Ogre::String &st )
{
	return rb_str_new2(st.c_str());
}

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

/*
template <typename T>
VALUE wrap(const Ogre::SharedPtr<T> &ptr){
	rb_warn("ptr");
	return wrap<T>(ptr.get());
};
*/
template <typename T>
VALUE wrap(Ogre::list<T> &vec){
	VALUE result = rb_ary_new();
	typename Ogre::list<T>::iterator it;
	for ( it=vec.begin() ; it != vec.end(); it++ )
		rb_ary_push(result,wrap(*it));
	return result;
};

template <typename T>
VALUE wrap(Ogre::list<T> *vec){
	VALUE result = rb_ary_new();
	typename Ogre::list<T>::iterator it;
	for ( it=vec->begin() ; it != vec->end(); it++ )
		rb_ary_push(result,wrap(*it));
	return result;
};
template <typename T>
VALUE wrap(const Ogre::vector<T> &vec){
	VALUE result = rb_ary_new();
	typename Ogre::vector<T>::iterator it;
	for ( it=vec.begin() ; it != vec.end(); it++ )
		rb_ary_push(result,wrap(*it));
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
}

template <>
inline VALUE wrap< Ogre::NameValuePairList >(const Ogre::NameValuePairList &map )
{
	VALUE result = rb_hash_new();
	Ogre::NameValuePairList::const_iterator it;
	for ( it=map.begin() ; it != map.end(); it++ )
		rb_hash_aset(result,wrap(it->first),wrap(it->second));
	return result;
}



template <>
inline VALUE wrap< Ogre::StringVectorPtr >(const Ogre::StringVectorPtr &vec )
{
	VALUE result = rb_ary_new();
	
	Ogre::StringVector::const_iterator it;
	for ( it=vec->begin() ; it < vec->end(); it++ )
		rb_ary_push(result,wrap(*it));
	return result;
}
template <>
inline VALUE wrap< Ogre::StringVector >(const Ogre::StringVector &vec )
{
	VALUE result = rb_ary_new();
	
	Ogre::StringVector::const_iterator it;
	for ( it=vec.begin() ; it < vec.end(); it++ )
		rb_ary_push(result,wrap(*it));
	return result;
}

#endif /* __RubyOgreMain_H__ */

