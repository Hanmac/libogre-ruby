#Encoding: UTF-8
=begin
This file is part of libogre-ruby. 

libogre-ruby is a Ruby binding for the C++ library libogre. 

Copyright © 2011 Hans Mackowiak

libogre-ruby is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

libogre-ruby is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with libogre-ruby; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
=end

require 'mkmf'

dir_config("ogre")
with_cflags("-x c++"){

if(find_executable('pkg-config'))
	pkg_config("OGRE")
	$defs << (" -DOGRE_PLUGINDIR=\\\"#{`pkg-config OGRE --variable plugindir`.chomp}/\\\"")
end

unless(find_library("OgreMain","main") && find_header("Ogre.h"))
	abort("need ogre-dev package.")
end
#have_func("Ogre::Vector3.isNaN","Ogre.h")
#have_struct_member("Ogre::Vector3", "isNaN","Ogre.h")
#have_library("OgreMain","Ogre::Vector3.isNaN","Ogre.h")
$CFLAGS += " -Wall"

unless have_func("rb_string_value_cstr","ruby.h")
	abort("missing VALUE to char convert! You need ruby version >= 1.8.7")
end
unless have_macro("RETURN_ENUMERATOR","ruby.h")
	abort("missing RETURN_ENUMERATOR marco! You need ruby version >= 1.8.7")
end

create_makefile("ogre")
}

