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
//*
template <typename T>
VALUE wrap(Ogre::SharedPtr<T> &ptr){
	return wrap<T>(ptr.get());
};
//*/

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

template <>
inline Ogre::String wrap< Ogre::String >(const VALUE &val )
{
	return rb_string_value_cstr((volatile VALUE*)(&val));
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

template <typename T>
void wrap_each1(T begin,T end)
{
	for(T cit = begin; cit != end; ++cit)
		rb_yield(wrap(*cit));
}
template <typename T>
void wrap_each2(T begin,T end)
{
	for(T cit = begin; cit != end; ++cit)
			rb_yield_values(2,wrap(cit->first),wrap(cit->second));
}

template <typename T>
void wrap_each2a(T begin,T end)
{
	for(T cit = begin; cit != end; ++cit)
			rb_yield(wrap(cit->first));
}

template <typename T>
void wrap(Ogre::ConstVectorIterator<typename Ogre::vector<T>::type > it)
{
	wrap_each1(it.begin(),it.end());
}


template <typename T>
void wrap(Ogre::VectorIterator<typename Ogre::vector<T>::type > it)
{
	wrap_each1(it.begin(),it.end());
}


template <typename T,typename V>
void wrap(Ogre::ConstMapIterator<typename Ogre::map<T,V>::type > it)
{
	wrap_each2(it.begin(),it.end());
}

template <typename T,typename V>
void wrap(Ogre::MapIterator<typename Ogre::map<T,V>::type > it)
{
	wrap_each2(it.begin(),it.end());
}
/*
*/
VALUE Ogre_dummy0(VALUE self);
VALUE Ogre_dummy1(VALUE self,VALUE obj1);
VALUE Ogre_dummy2(VALUE self,VALUE obj1,VALUE obj2);
VALUE Ogre_dummy3(VALUE self,VALUE obj1,VALUE obj2,VALUE obj3);
VALUE Ogre_dummy4(VALUE self,VALUE obj1,VALUE obj2,VALUE obj3,VALUE obj4);

extern VALUE rb_cOgreRadian;
extern VALUE rb_cOgreDegree;
Ogre::Degree* rb_to_degree(const VALUE &vdegree);
Ogre::Radian* rb_to_radian(const VALUE &vradian);


inline void rb_define_attr_method(VALUE klass,std::string name,VALUE(get)(VALUE),VALUE(set)(VALUE,VALUE))
{
	rb_define_method(klass,name.c_str(),RUBY_METHOD_FUNC(get),0);
	rb_define_method(klass,(name + "=").c_str(),RUBY_METHOD_FUNC(set),1);
}

#define macro_attr(klass,attr,type) \
VALUE Ogre##klass##_get##attr(VALUE self)\
{return wrap(_self->get##attr());}\
\
VALUE Ogre##klass##_set##attr(VALUE self,VALUE other)\
{\
	_self->set##attr(wrap<type>(other));\
	return other;\
}

#define macro_attr_with_func(klass,attr,getfunc,setfunc) \
VALUE Ogre##klass##_get##attr(VALUE self)\
{return getfunc(_self->get##attr() );}\
\
VALUE Ogre##klass##_set##attr(VALUE self,VALUE other)\
{\
	_self->set##attr( setfunc(other) );\
	return other;\
}

//*/
#define macro_attr_prop(klass,attr,type) \
VALUE Ogre##klass##_get_##attr(VALUE self)\
{return wrap(_self->attr);}\
\
VALUE Ogre##klass##_set_##attr(VALUE self,VALUE other)\
{\
	_self->attr = wrap<type>(other);\
	return other;\
}

#define macro_attr_prop_with_func(klass,attr,getfunc,setfunc) \
VALUE Ogre##klass##_get_##attr(VALUE self)\
{return getfunc(_self->attr);}\
\
VALUE Ogre##klass##_set_##attr(VALUE self,VALUE other)\
{\
	_self->attr = setfunc(other);\
	return other;\
}

#define RBOOL(val) (val) ? Qtrue : Qfalse

#endif /* __RubyOgreMain_H__ */

