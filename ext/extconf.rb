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

RbConfig::CONFIG["CC"] = RbConfig::CONFIG["CXX"]
RbConfig::CONFIG["CPP"] = RbConfig::CONFIG["CXX"] + " -E"
CONFIG["warnflags"] = RbConfig::CONFIG["warnflags"] = " -Wall"

dir_config("ogre")
pkg_config("OGRE")
unless(find_library("OgreMain","main") && find_header("Ogre.h"))
	abort("need ogre-dev package.")
end
#have_func("Ogre::Vector3.isNaN","Ogre.h")
#have_struct_member("Ogre::Vector3", "isNaN","Ogre.h")
#have_library("OgreMain","Ogre::Vector3.isNaN","Ogre.h")
$CFLAGS += " -Wall"

unless have_func("rb_string_value_cstr","ruby.h")
	abort("missing VALUE to char convert! You need ruby version >= 1.9")
end



create_makefile("ogre")
