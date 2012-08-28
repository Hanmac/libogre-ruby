require_relative "../ext/ogre"

Ogre.load_plugin("RenderSystem_GL")

Ogre::add_resource_location("media","FileSystem",:default)
Ogre::ResourceGroup.initialise_group

Ogre.show_config_dialog unless Ogre.load_config

rw = Ogre.create_render_window(true,"Ruby-Test")

sm = Ogre.create_scene_manager("DefaultSceneManager")

sm.ambient_light = Ogre::Color.new(0,0,0)

Ogre::Texture::create_manual("MyFirstRtt",:default,:type_2d,512,512,1,0,:r8g8b8,:rendertarget)

p "one"
Ogre::GpuProgram.each {|g| p g }
p "two"
Ogre::GpuProgram.high_each {|*,n| p n,n.language }
p "three"
Ogre::Material::create("RTTMaterial",:default)[0][0].create.texture_name = "MyFirstRtt"

sm.root_scene_node.create_child.tap {|scene|
	scene_mask = 0b010
	
	camera = sm.create_camera("cam",
		position: Ogre::Vector3.new(0,100,500),
		look_at: Ogre::Vector3.new(0,0,-10),
		near_clip_distance: 5
	)
  
	scene.attach(camera)

	vp = rw.add_viewport(camera)
	vp.visibility_mask = scene_mask
	vp.background_color = Ogre::Color.new(0,0,0)

	scene.create_child.tap {|c|
		c.attach(sm.create_entity(Ogre::Mesh.create_plane("ground",
			nil, Ogre::Plane.new(:unit_y,0), 1500, 1500,
			xsegments: 20, ysegments: 20, normals: true,
			text_coords: 1, utile: 5, vtile: 5, upVector: :unit_z
		),"GroundEntity",material: "Rockwall",visibility_flags: scene_mask))
	}
	
	scene.create_child.tap {|c|
		c.attach(sm.create_entity(:cube,"globe",material: "RTTMaterial",visibility_flags: scene_mask))

		c.position = Ogre::Vector3.new(0,10,0)
		c.scale = Ogre::Vector3.new(2,2,2)
		
		c.roll Ogre::Degree.new(45)
		c.pitch Ogre::Degree.new(45)
	}

	
	
	scene.attach(sm.create_light("pointLight",
		type: :point,
		position: Ogre::Vector3.new(0, 150, 250),
		diffuse_color: Ogre::Color.new(1.0, 1.0, 0.0),
		specular_color: Ogre::Color.new(0.75, 0.50, 0.0),
		visibility_flags: scene_mask
	))
	
	
	scene.attach(sm.create_light("directionalLight",
		type: :directional,
		diffuse_color: Ogre::Color.new(0.25, 0.5, 0),
		specular_color: Ogre::Color.new(0.75, 0.5, 0),
		direction: Ogre::Vector3.new( 0, -1, 1 ),
		visibility_flags: scene_mask
	))

#	
#	spotLight = sm.create_light("spotLight",
#		type: :spotlight,
#		diffuse_color: Ogre::Color.new(0, 0, 1.0),
#		specular_color: Ogre::Color.new(0, 0, 1.0),
#		direction: Ogre::Vector3.new(-1, -1, 0),
#		position: Ogre::Vector3.new(300, 300, 0)
#	)
#
#	spotLight.spotlight_inner_angle = Ogre::Degree.new(35)
#	spotLight.spotlight_outer_angle = Ogre::Degree.new(50)
#
#	
#	scene.attach(spotLight)
		
}

#sm.create_scene_node.tap {|scene|
sm.root_scene_node.create_child.tap {|scene|
	scene_mask = 0b100

	camera = sm.create_camera("RTTcam",
		position: Ogre::Vector3.new(0,100,500),
		look_at: Ogre::Vector3.new(0,0,-10),
		near_clip_distance: 5
	)
	scene.attach(camera)
	vp = Ogre::Texture["MyFirstRtt"].render_target.add_viewport(camera)
	vp.visibility_mask = scene_mask
	vp.background_color = Ogre::Color.new(0,1,0)
	
	scene.create_child.tap {|c|
		c.attach(sm.create_entity(:sphere,material: "BumpyMetal",visibility_flags: scene_mask))
		c.scale = Ogre::Vector3.new(2,2,2)
		c.position = Ogre::Vector3.new(0,10,0)
	}
	scene.attach(sm.create_light(
		type: :point,
		position: Ogre::Vector3.new(0, 150, 250),
		diffuse_color: Ogre::Color.new(0.0, 1.0, 0),
		specular_color: Ogre::Color.new(0.0, 0.70, 0.50),
		visibility_flags: scene_mask
	))
}
#class VL
#def viewport_camera_changed(*arg)
#end

#def viewport_dimensions_changed(*arg)
#end

#def viewport_destroyed(*arg)
#	p :dead
#end

#end

#vp.addListener(VL.new)

#ground = Ogre::Mesh.createPlane("ground", nil, plane, 1500, 1500,
#	:xsegments => 20, :ysegments => 20, :normals => true,
#	:text_coords => 1, :utile => 5, :vtile => 5, :upVector => :unit_z
#)

#material.prepare
#p a = rttm.create
#p b = a.create
#p c = b.create#.texture_name = "MyFirstRtt"

#p "----"

#d = rttm[0][0]
#d.create
#d.each {|e| p "AA",e}
#p rttm[0][0][0]

#p Ogre::Material["RTTMaterial"][0][0][0].texture_name

#.create.texture_name = "MyFirstRtt"

class FL
	def initialize(window)
		@window = window
	end
	def frame_started(*args)
		#@window.removeViewport(nil)
		#p @window.lastFPS
#		sleep(0.0010)
		return true
	end
	def frame_rendering_queued(*args)
		return true
	end
	def frame_ended(*args)
		
		return true
	end
end

Ogre.add_frame_listener(FL.new(rw))
#exit
Ogre.start_rendering
