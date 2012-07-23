#include "ogreresource.hpp"
#include "ogretexture.hpp"

#include "ogreexception.hpp"
#define _manager Ogre::TextureManager::getSingletonPtr()
#define _self wrap<Ogre::TexturePtr>(self)

template <>
VALUE wrap< Ogre::TexturePtr >(const Ogre::TexturePtr &texture )
{
	if(texture.isNull())
		return Qnil;
	return Data_Wrap_Struct(rb_cOgreTexture, NULL, free, new Ogre::TexturePtr(texture));
}

template <>
Ogre::TexturePtr wrap< Ogre::TexturePtr >(const VALUE &vtexture)
{
	if(rb_obj_is_kind_of(vtexture,rb_cString))
		return _manager->getByName(wrap<Ogre::String>(vtexture));
	return *unwrapPtr<Ogre::TexturePtr>(vtexture, rb_cOgreTexture);
}


VALUE rb_cOgreTexture;

macro_attr_enum(TextureType,Ogre::TextureType)
macro_attr_enum(Usage,Ogre::TextureUsage)

macro_attr(Gamma,float)

macro_attr(Height,size_t)
macro_attr(Width,size_t)
macro_attr(Depth,size_t)
macro_attr(NumMipmaps,size_t)

macro_attr_bool(HardwareGammaEnabled)

macro_attr_enum(Format,Ogre::PixelFormat)

macro_attr(DesiredIntegerBitDepth,ushort)
macro_attr(DesiredFloatBitDepth,ushort)

macro_attr(TreatLuminanceAsAlpha,bool)


singlefunc(createInternalResources)
singlefunc(freeInternalResources)


VALUE _getSrcHeight(VALUE self)
{
	return ULONG2NUM(_self->getSrcHeight());
}
VALUE _getSrcWidth(VALUE self)
{
	return ULONG2NUM(_self->getSrcWidth());
}
VALUE _getSrcDepth(VALUE self)
{
	return ULONG2NUM(_self->getSrcDepth());
}
VALUE _loadImage(VALUE self,VALUE image)
{
	_self->loadImage(*wrap<Ogre::Image*>(image));
	return self;
}

VALUE _convertToImage(int argc,VALUE *argv,VALUE self)
{
	VALUE mip;
	rb_scan_args(argc, argv, "01",&mip);

	Ogre::Image img;
	_self->convertToImage(img,RTEST(mip));
	return wrap(img);
}

VALUE _getRenderTarget(int argc,VALUE *argv,VALUE self)
{
	VALUE face,mip,slice;
	rb_scan_args(argc, argv, "03",&face,&mip,&slice);
	size_t cface = 0,cmip = 0,cslice = 0;

	if(!(_self->getUsage() & Ogre::TU_RENDERTARGET))
		return Qnil;

	if(!NIL_P(face) && (cface = NUM2UINT(face)) >= _self->getNumFaces())
		return Qnil;

	if(!NIL_P(mip) && (cmip = NUM2UINT(mip)) >= _self->getNumMipmaps())
		return Qnil;

	if(!NIL_P(slice))
		cslice = NUM2UINT(slice);


	Ogre::HardwarePixelBufferSharedPtr ptr = _self->getBuffer(cface,cmip);
	if(ptr.get())
		return wrap<Ogre::RenderTarget>(ptr->getRenderTarget(cslice));
	return Qnil;
}



//virtual TexturePtr createManual(const String & name, const String& group,
//            TextureType texType, uint width, uint height, uint depth,
//			int num_mips, PixelFormat format, int usage = TU_DEFAULT, ManualResourceLoader* loader = 0,
//			bool hwGammaCorrection = false, uint fsaa = 0, const String& fsaaHint = StringUtil::BLANK);


VALUE _singleton_createManual(int argc,VALUE *argv,VALUE self)
{
	VALUE name,group,texType,width,height,depth,mips,format,usage,loader;
	//gamma,fsaa,fsaaHint;
	rb_scan_args(argc, argv, "82",&name,&group,&texType,&width,&height,&depth,&mips,&format,&usage,&loader);
	RUBYTRY(
		return wrap(_manager->createManual(wrap<Ogre::String>(name),
			unwrapResourceGroup(group,Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME),
				wrapenum<Ogre::TextureType>(texType),
				NUM2UINT(width),NUM2UINT(height),NUM2UINT(depth),
				NUM2INT(mips),wrapenum<Ogre::PixelFormat>(texType),
				wrapenum<Ogre::TextureUsage>(usage)
		));
	)
	return Qnil;
}



/*
virtual size_t 	getHeight (void) const
 	Returns the height of the texture.
virtual size_t 	getWidth (void) const
 	Returns the width of the texture.
virtual size_t 	getDepth (void) const
 	Returns the depth of the texture (only applicable for 3D textures).
virtual size_t 	getSrcHeight (void) const
 	Returns the height of the original input texture (may differ due to hardware requirements).
virtual size_t 	getSrcWidth (void) const
 	Returns the width of the original input texture (may differ due to hardware requirements).
virtual size_t 	getSrcDepth (void) const
 	Returns the original depth of the input texture (only applicable for 3D textures).
virtual void 	setHeight (size_t h)
 	Set the height of the texture; can only do this before load();.
virtual void 	setWidth (size_t w)
 	Set the width of the texture; can only do this before load();.
virtual void 	setDepth (size_t d)
 	Set the depth of the texture (only applicable for 3D textures); ; can only do this before load();.
virtual int 	getUsage () const
 	Returns the TextureUsage indentifier for this Texture.
virtual void 	setUsage (int u)
*/
void Init_OgreTexture(VALUE rb_mOgre)
{
#if 0
	rb_mOgre = rb_define_module("Ogre");
	rb_cOgreResource = rb_define_class_under(rb_mOgre,"Resource",rb_cObject);

	rb_define_attr(rb_cOgreTexture,"gamma",1,1);

	rb_define_attr(rb_cOgreTexture,"height",1,1);
	rb_define_attr(rb_cOgreTexture,"width",1,1);
	rb_define_attr(rb_cOgreTexture,"depth",1,1);
	
	rb_define_attr(rb_cOgreTexture,"usage",1,1);
#endif
	rb_cOgreTexture = rb_define_class_under(rb_mOgre,"Texture",rb_cOgreResource);

	rb_define_attr_method(rb_cOgreTexture,"gamma",_getGamma,_setGamma);

	rb_define_attr_method(rb_cOgreTexture,"height",_getHeight,_setHeight);
	rb_define_attr_method(rb_cOgreTexture,"width",_getWidth,_setWidth);
	rb_define_attr_method(rb_cOgreTexture,"depth",_getDepth,_setDepth);
	rb_define_attr_method(rb_cOgreTexture,"usage",_getUsage,_setUsage);
	rb_define_attr_method(rb_cOgreTexture,"texture_type",_getTextureType,_setTextureType);

	rb_define_method(rb_cOgreTexture,"src_height",RUBY_METHOD_FUNC(_getSrcHeight),0);
	rb_define_method(rb_cOgreTexture,"src_width",RUBY_METHOD_FUNC(_getSrcWidth),0);
	rb_define_method(rb_cOgreTexture,"src_depth",RUBY_METHOD_FUNC(_getSrcDepth),0);

	rb_define_method(rb_cOgreTexture,"to_image",RUBY_METHOD_FUNC(_convertToImage),-1);

	rb_define_singleton_method(rb_cOgreTexture,"create_manual",RUBY_METHOD_FUNC(_singleton_createManual),-1);

	registerenum<Ogre::TextureType>("Ogre::TextureType")
		.add(Ogre::TEX_TYPE_1D,"type_1d")
		.add(Ogre::TEX_TYPE_2D,"type_2d")
		.add(Ogre::TEX_TYPE_3D,"type_3d")
		.add(Ogre::TEX_TYPE_CUBE_MAP,"type_cube_map")
		.add(Ogre::TEX_TYPE_2D_ARRAY,"type_2d_array");

	registerenum<Ogre::TextureUsage>("Ogre::TextureUsage",Ogre::TU_DEFAULT)
		.add(Ogre::TU_STATIC,"static")
		.add(Ogre::TU_DYNAMIC,"dynamic")
		.add(Ogre::TU_WRITE_ONLY,"write_only")
		.add(Ogre::TU_STATIC_WRITE_ONLY,"static_write_only")
		.add(Ogre::TU_DYNAMIC_WRITE_ONLY,"dynamic_write_only")
		.add(Ogre::TU_DYNAMIC_WRITE_ONLY_DISCARDABLE,"dynamic_write_only_discardable")
		.add(Ogre::TU_AUTOMIPMAP,"auto_mipmap")
		.add(Ogre::TU_RENDERTARGET,"rendertarget")
		.add(Ogre::TU_DEFAULT,"default");

	registerenum<Ogre::PixelFormat>("Ogre::PixelFormat")
		.add(Ogre::PF_UNKNOWN,"unknown")
		.add(Ogre::PF_L8,"l8")
		.link(Ogre::PF_BYTE_L,"byte_l")
		.add(Ogre::PF_L16,"l16")
		.link(Ogre::PF_SHORT_L,"short_l")
		.add(Ogre::PF_A8,"a8")
		.link(Ogre::PF_BYTE_A,"byte_a")
		.add(Ogre::PF_A4L4,"a4l4")
		.add(Ogre::PF_BYTE_LA,"byte_la")
		.add(Ogre::PF_R5G6B5,"r5g6b5")
		.add(Ogre::PF_B5G6R5,"b5g6r5")
		.add(Ogre::PF_R3G3B2,"r3g3b2")

		.add(Ogre::PF_A4R4G4B4,"a4r4g4b4")
		.add(Ogre::PF_A1R5G5B5,"a1r5g5b5")

		.add(Ogre::PF_R8G8B8,"r8g8b8")
		.add(Ogre::PF_B8G8R8,"b8g8r8")

		.add(Ogre::PF_A8R8G8B8,"a8r8g8b8")
		.add(Ogre::PF_A8B8G8R8,"a8b8g8r8")

		.add(Ogre::PF_R8G8B8A8,"r8g8b8a8")
		.add(Ogre::PF_B8G8R8A8,"b8g8r8a8")

		.add(Ogre::PF_X8R8G8B8,"x8r8g8b8")
		.add(Ogre::PF_X8B8G8R8,"x8b8g8r8")

		.link(Ogre::PF_BYTE_RGB,"byte_rgb")
		.link(Ogre::PF_BYTE_BGR,"byte_bgr")
		.link(Ogre::PF_BYTE_RGBA,"byte_rgba")
		.link(Ogre::PF_BYTE_BGRA,"byte_bgra")

		.add(Ogre::PF_A2R10G10B10,"a2r10g10b10")
		.add(Ogre::PF_A2B10G10R10,"a2b10g10r10")

		.add(Ogre::PF_DXT1,"dxt1")
		.add(Ogre::PF_DXT2,"dxt2")
		.add(Ogre::PF_DXT3,"dxt3")
		.add(Ogre::PF_DXT4,"dxt4")
		.add(Ogre::PF_DXT5,"dxt5")

		.add(Ogre::PF_FLOAT16_R,"float16_r")
		.add(Ogre::PF_FLOAT16_RGB,"float16_rgb")
		.add(Ogre::PF_FLOAT16_RGBA,"float16_rgba")
		.add(Ogre::PF_FLOAT32_R,"float32_r")
		.add(Ogre::PF_FLOAT32_RGB,"float32_rgb")
		.add(Ogre::PF_FLOAT32_RGBA,"float32_rgba")

		.add(Ogre::PF_FLOAT16_GR,"float16_gr")
		.add(Ogre::PF_FLOAT32_GR,"float32_gr")

		.add(Ogre::PF_DEPTH,"depth")

		.add(Ogre::PF_SHORT_RGBA,"short_rgba")
		.add(Ogre::PF_SHORT_GR,"short_gr")
		.add(Ogre::PF_SHORT_RGB,"short_rgb")

		.add(Ogre::PF_PVRTC_RGB2,"pvrtc_rgb2")
		.add(Ogre::PF_PVRTC_RGBA2,"pvrtc_rgba2")

		.add(Ogre::PF_PVRTC_RGB4,"pvrtc_rgb4")
		.add(Ogre::PF_PVRTC_RGBA4,"pvrtc_rgba4")

		.add(Ogre::PF_R8,"r8")
		.add(Ogre::PF_RG8,"rg8");

}
