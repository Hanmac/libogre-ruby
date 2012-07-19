#ifndef __RubyOgreMain_H__
#define __RubyOgreMain_H__

#include <ruby.h>
#include <Ogre.h>
#include <typeinfo>

#include <string>
#include <map>

template< class T > struct remove_pointer                    {typedef T type;};
template< class T > struct remove_pointer<T*>                {typedef T type;};
template< class T > struct remove_pointer<T* const>          {typedef T type;};
template< class T > struct remove_pointer<T* volatile>       {typedef T type;};
template< class T > struct remove_pointer<T* const volatile> {typedef T type;};


typedef std::map<std::string,VALUE > klassregistertype;

struct enumtype
{
	std::string name;
	typedef std::map<int,ID> value_type;
	typedef std::map<ID,int> link_type;
	value_type values;
	link_type links;

	int defaults;

	enumtype& add(int enumo,const char* sym)
	{
		values.insert(std::make_pair(enumo,rb_intern(sym)));
		return *this;
	}
	enumtype& link(int enumo,const char* sym)
		{
			links.insert(std::make_pair(rb_intern(sym),enumo));
			return *this;
		}
};
//typedef std::map<int,ID > enumtype;
typedef std::map<std::string,enumtype > enumregistertype;
extern klassregistertype klassregister;
extern enumregistertype enumregister;

template <typename T>
void registerklass(VALUE klass)
{
	klassregister.insert(std::make_pair(std::string(typeid(T).name()),klass));
}

template <typename T>
enumtype& registerenum(const char* name,int def = 0)
{
	enumtype &type = enumregister[std::string(typeid(T).name())];
	type.name = std::string(name);
	type.defaults = def;
	return type;
}

VALUE wrap(void *obj,VALUE klass);
VALUE wrap(Ogre::MovableObject *obj,VALUE klass);
VALUE wrap(Ogre::Renderable *obj,VALUE klass);
VALUE wrap(Ogre::Node *obj,VALUE klass);
VALUE wrap(Ogre::Frustum *obj,VALUE klass);
VALUE wrap(Ogre::BillboardChain *obj,VALUE klass);
VALUE wrap(Ogre::BillboardSet *obj,VALUE klass);


template <typename T>
VALUE wrap(T *arg){
	if(!arg)
		return Qnil;
	std::map<std::string,VALUE >::iterator it = klassregister.find(typeid(*arg).name());
	if(it != klassregister.end())
		return wrap(arg,it->second);
	it = klassregister.find(typeid(T).name());
	if(it != klassregister.end())
		return wrap(arg,it->second);

	rb_warn("unknown convertion from %s to VALUE. return nil instat.",typeid(*arg).name());
	return Qnil;
};


template <typename T>
T* unwrapPtr(const VALUE &obj,const VALUE &klass)
{
	if (rb_obj_is_kind_of(obj, klass)){
		T *temp;
		Data_Get_Struct( obj, T, temp);
		return temp;
	}else{
		rb_raise(rb_eTypeError,
				"Expected %s got %s!",
				rb_class2name(klass),
				rb_obj_classname(obj)
		);
		return NULL;
	}

}

template <typename T>
struct WrapReturn
{
	WrapReturn(T *val) : mValue(val) {};
	WrapReturn(T &val) : mValue(&val) {};

	T *mValue;

	operator T*() {return mValue;};
	operator T() {return *mValue;};

};


template <typename T>
T wrap(const VALUE &arg){
	if(NIL_P(arg))
		return (T)NULL;
	typedef typename remove_pointer<T>::type rtype;
	klassregistertype::iterator it = klassregister.find(typeid(rtype).name());
	if(it != klassregister.end())
		return WrapReturn<rtype>(unwrapPtr<rtype>(arg,it->second));

	rb_warn("unknown convertion from VALUE to %s. return %s() instat.",typeid(T).name(),typeid(T).name());
	return (T)NULL;
};

template <typename T>
VALUE wrapenum(const T &arg){
	enumtype::value_type &enummap = enumregister[std::string(typeid(T).name())].values;
	enumtype::value_type::iterator it = enummap.find((int)arg);
	if(it != enummap.end())
		return ID2SYM(it->second);
	return Qnil;
}

template <typename T>
T wrapenum(const VALUE &arg){
	enumregistertype::iterator it = enumregister.find(typeid(T).name());
	if(it != enumregister.end())
	{
		if(NIL_P(arg))
			return (T)it->second.defaults;
		else if(SYMBOL_P(arg))
		{
			ID id = SYM2ID(arg);
			enumtype::link_type::iterator it2 = it->second.links.find(id);
			if(it2 != it->second.links.end())
				return (T)it2->second;

			for(enumtype::value_type::iterator it3 = it->second.values.begin();
					it3 != it->second.values.end();
					++it3)
			{
				if(it3->second == id)
					return (T)it3->first;
			}
			rb_raise(rb_eTypeError,"%s is not a %s-Enum.",rb_id2name(id),it->second.name.c_str());
		}else
			return (T)NUM2INT(arg);
	}
	return (T)0;
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

template <typename T>
VALUE wrap(const T &arg){
	return wrap(new T(arg));
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
VALUE wrap< Ogre::String >(const Ogre::String &st );

template <>
Ogre::String wrap< Ogre::String >(const VALUE &val );

template <>
VALUE wrap< bool >(const bool &st );

template <>
bool wrap< bool >(const VALUE &val );

template <>
VALUE wrap< double >(const double &st );

template <>
double wrap< double >(const VALUE &val );


template <>
VALUE wrap< float >(const float &st );

template <>
float wrap< float >(const VALUE &val );


template <>
VALUE wrap< unsigned short >(const unsigned short &st );

template <>
unsigned short wrap< unsigned short >(const VALUE &val );

template <>
VALUE wrap< unsigned int >(const unsigned int &st );

template <>
unsigned int wrap< unsigned int >(const VALUE &val );


/*
template <>
inline VALUE wrap< Ogre::StringVector >(const Ogre::StringVector &vec )
{
	return wrap((const Ogre::vector<Ogre::String>::type)vec);
}
*/

template <>
VALUE wrap< Ogre::NameValuePairList >(const Ogre::NameValuePairList &map );

template <>
Ogre::NameValuePairList* wrap< Ogre::NameValuePairList* >(const VALUE &map );

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

template <typename T>
bool wrapable(const VALUE &obj);

/*
*/
VALUE Ogre_dummy0(VALUE self);
VALUE Ogre_dummy1(VALUE self,VALUE obj1);
VALUE Ogre_dummy2(VALUE self,VALUE obj1,VALUE obj2);
VALUE Ogre_dummy3(VALUE self,VALUE obj1,VALUE obj2,VALUE obj3);
VALUE Ogre_dummy4(VALUE self,VALUE obj1,VALUE obj2,VALUE obj3,VALUE obj4);


void rb_define_attr_method(VALUE klass,std::string name,VALUE(get)(VALUE),VALUE(set)(VALUE,VALUE));

#define RUBYTRY(body) try { body }catch(Ogre::Exception& e){rb_raise(wrap(e));}

#define macro_attr_func(attr,funcget,funcset,wrapget,wrapset) \
VALUE _get##attr(VALUE self)\
{ \
	RUBYTRY(return wrapget(_self->funcget);)\
	return Qnil;\
}\
\
VALUE _set##attr(VALUE self,VALUE other)\
{\
	RUBYTRY(_self->funcset(wrapset(other));)\
	return other;\
}




#define macro_attr(attr,type) macro_attr_func(attr,get##attr(),set##attr,wrap,wrap<type>)
#define macro_attr_enum(attr,type) macro_attr_func(attr,get##attr(),set##attr,wrapenum<type>,wrapenum<type>)
#define macro_attr_with_func(attr,getf,setf) macro_attr_func(attr,get##attr(),set##attr,getf,setf)

//*/
#define macro_attr_prop(attr,type) macro_attr_func(_##attr,attr,attr = ,wrap,wrap<type>)
#define macro_attr_prop_enum(attr,type) macro_attr_func(_##attr,attr,attr = ,wrapenum<type>,wrapenum<type>)
#define macro_attr_prop_with_func(attr,getf,setf) macro_attr_func(_##attr,attr,attr = ,getf,setf)

/*
//#define macro_attr_prop(attr,type) \
//VALUE _get_##attr(VALUE self)\
//{return wrap(_self->attr);}\
//\
//VALUE _set_##attr(VALUE self,VALUE other)\
//{\
//	_self->attr = wrap<type>(other);\
//	return other;\
//}
//*/

#define macro_attr_bool(attr) macro_attr_func(attr,is##attr(),set##attr,wrap,RTEST)

/*
//#define macro_attr_bool(attr) \
//VALUE _get##attr(VALUE self)\
//{return wrap(_self->is##attr());}\
//\
//VALUE _set##attr(VALUE self,VALUE other)\
//{\
//	_self->set##attr(RTEST(other));\
//	return other;\
//}
//*/

#define singlefunc(func) \
VALUE _##func(VALUE self)\
{RUBYTRY(_self->func();)return self;}



#define singlereturn(func) \
VALUE _##func(VALUE self)\
{RUBYTRY(return wrap(_self->func());)return Qnil;}



class RubyAny
{
public:

	RubyAny(VALUE obj);

	virtual ~RubyAny();

	VALUE value;

	inline friend std::ostream& operator << ( std::ostream& o, const Ogre::SharedPtr<RubyAny>& v )
	{
		o << wrap<Ogre::String>(v->value);
		return o;
	}

};



#endif /* __RubyOgreMain_H__ */

