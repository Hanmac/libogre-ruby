
/*

*/
VALUE OgreSingleton_method_missing(int argc,VALUE *argv,VALUE self)
{
	VALUE temp = rb_funcall(self,rb_intern("instance"),0);
	return rb_funcall2(temp,rb_intern("send"),argc,argv);
}
