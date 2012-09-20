require_relative "../ext/ogre"

Ogre.load_plugin("RenderSystem_GL")
Ogre.load_plugin("Plugin_CgProgramManager")
Ogre.load_plugin("Plugin_ParticleFX")

Ogre::add_resource_location("media","FileSystem",:default)
Ogre::add_resource_location("media/programs","FileSystem",:default)

Ogre.show_config_dialog unless Ogre.load_config

rw = Ogre.create_render_window(true,"Ruby-Test")

Ogre::ResourceGroup.initialise_group

sm = Ogre.create_scene_manager("DefaultSceneManager")

sm.shadow_technique = :stencil_additive
sm.ambient_light = Ogre::Color.new(0,0,0)

Ogre::Texture::create_manual("MyFirstRtt",:default,:type_2d,512,512,1,0,:r8g8b8,:rendertarget)

["cg","hlsl","glsl","glsles"].each {|l|
p "#{l} #{Ogre::HighGpuProgram.supported?(l) ? "" : "un"}supported"
}

Ogre::Compositor.each{|i,c| p c}

Ogre::Material::create("RTTMaterial",:default)[0][0].create.texture_name = "MyFirstRtt"

cube = nil

sm.root_scene_node.create_child.tap {|scene|
	scene_mask = 0b010
	
	camera = sm.create_camera("cam",
		position: Ogre::Vector3.new(0,100,500),
		look_at: Ogre::Vector3.new(0,0,-10),
		near_clip_distance: 5
	)
	  
	scene.attach(camera)

	vp = rw.add_viewport(camera,nil,nil,nil,nil,nil,
		visibility_mask: scene_mask,
		background_color: Ogre::Color.new(0,0,0))

	#(vp.compositor_chain << "B&W").each{|e| e.enable = true;p e.alive}
	
	scene.create_child.tap {|c|
		c.attach(sm.create_entity(Ogre::Mesh.create_plane("ground",
			nil, Ogre::Plane.new(:unit_y,0), 1500, 1500,
			xsegments: 20, ysegments: 20, normals: true,
			text_coords: 1, utile: 5, vtile: 5, upVector: :unit_z
		),"GroundEntity",material: "Rockwall",visibility_flags: scene_mask))
	}
	
	scene.create_child.tap {|c|
		cube = c
		c.attach(sm.create_entity(:cube,"cube",material: "RTTMaterial",visibility_flags: scene_mask))

		c.position = Ogre::Vector3.new(0,90,0)
		#c.scale = Ogre::Vector3.new(1,1,1)
		
		c.roll Ogre::Degree.new(45)
		c.pitch Ogre::Degree.new(45)
	}

	#scene.create_child.tap {|c|
	scene.attach(sm.create_particle_system("Aureola","Examples/Aureola",visibility_flags: scene_mask))
		#c.attach(ps)
		#c.position = Ogre::Vector3.new(5,5,0)
		#c.scale = Ogre::Vector3.new(5,5,5)
	#}	
	
	scene.attach(sm.create_light("pointLight",
		type: :point,
		position: Ogre::Vector3.new(0, 150, 250),
		diffuse_color: Ogre::Color.new(1.0, 0.80, 0.80),
		#specular_color: Ogre::Color.new(0.75, 0.50, 0.0),
		visibility_flags: scene_mask
	))
	
	
	scene.attach(sm.create_light("directionalLight",
		type: :directional,
		diffuse_color: Ogre::Color.new(0.85, 0.5, 0),
		specular_color: Ogre::Color.new(0.75, 0.5, 0),
		direction: Ogre::Vector3.new( 0, -1, 1 ),
		visibility_flags: scene_mask
	))

	
	scene.attach(sm.create_light("spotLight",
		type: :spotlight,
		diffuse_color: Ogre::Color.new(0, 0, 1.0),
		specular_color: Ogre::Color.new(0, 0, 1.0),
		direction: Ogre::Vector3.new(-1, -1, 0),
		position: Ogre::Vector3.new(300, 300, 0),
		spotlight_inner_angle: Ogre::Degree.new(35),
		spotlight_outer_angle: Ogre::Degree.new(50),
		visibility_flags: scene_mask
	))
		
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
	vp.background_color = Ogre::Color.new(1,0,0)
	
	#(vp.compositor_chain << "Old TV").each(&:enable)
	(vp.compositor_chain << "Invert" << "Old TV").each(&:enable)
	
	scene.create_child.tap {|c|
		c.attach(sm.create_entity(:sphere,material: "BumpyMetal",visibility_flags: scene_mask))
		c.scale = Ogre::Vector3.new(2,2,2)
		c.position = Ogre::Vector3.new(0,10,0)
	}
	scene.attach(sm.create_light(
		type: :point,
		position: Ogre::Vector3.new(0, 150, 250),
		diffuse_color: Ogre::Color.new(1.0, 1.0, 1.0),
		specular_color: Ogre::Color.new(1.0, 0.0, 0.0),
#		specular_color: Ogre::Color.new(0.0, 0.70, 0.50),
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
	def initialize(window,cube)
		@window = window
		@cube = cube
	end
	def frame_started(*args)
		#@window.removeViewport(nil)
		#p @window.lastFPS
#		sleep(0.0010)
		return true
	end
	def frame_rendering_queued(lastevent,lastframe)
		@cube.yaw(Ogre::Degree.new(10) * lastframe)
		return true
	end
	def frame_ended(*args)
		
		return true
	end
end

Ogre.add_frame_listener(FL.new(rw,cube))
#exit

Ogre.start_rendering
