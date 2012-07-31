require_relative "../ext/ogre"

Ogre.loadPlugin("RenderSystem_GL")

Ogre::ResourceGroup.addLocation("media","FileSystem",:default)
Ogre::ResourceGroup.initialiseGroup

Ogre.showConfigDialog unless Ogre.loadConfig

rw = Ogre.createRenderWindow(true,"Ruby-Test")

sm = Ogre.createSceneManager("DefaultSceneManager")

sm.ambientLight = Ogre::Color.new(0,0,0)

vp = rw.addViewport(sm.createCamera("cam",
	position: Ogre::Vector3.new(0,100,500),
	look_at: Ogre::Vector3.new(0,0,-10),
	near_clip_distance: 5
))

vp.backgroundColor = Ogre::Color.new(0,0,0)

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

t = Ogre::Texture::create_manual("MyFirstRtt",:default,:type_2d,512,512,1,0,:r8g8b8,:rendertarget)
p t.render_target.addViewport(sm.createCamera("RTTcam"))

material = Ogre::Material::create("RTTMaterial",:default)
pass = material[0][0]
pass.create.texture_name = "MyFirstRtt"

#material.prepare
#p a = rttm.create
#p b = a.create
#p c = b.create#.texture_name = "MyFirstRtt"

#p "----"

#d = rttm[0][0]
#d.create
#d.each {|e| p "AA",e}
#p rttm[0][0][0]

p Ogre::Material["RTTMaterial"][0][0][0].texture_name

#.create.texture_name = "MyFirstRtt"

entGround = sm.createEntity(Ogre::Mesh.createPlane("ground",
	nil, Ogre::Plane.new(:unit_y,0), 1500, 1500,
	:xsegments => 20, :ysegments => 20, :normals => true,
	:text_coords => 1, :utile => 5, :vtile => 5, :upVector => :unit_z
),"GroundEntity")

entSphere = sm.createEntity(:cube,"globe")

entGround.each {|sub| sub.materialname = "Rockwall" }
entSphere.each {|sub| sub.materialname = "RTTMaterial" }
#entSphere.each {|sub| sub.materialname = "RTTMaterial" }
#entSphere.each {|sub| sub.materialname = "BumpyMetal" }

child1 = sm.rootSceneNode.createChild
child2 = sm.rootSceneNode.createChild

child2.position = Ogre::Vector3.new(0,10,0)
child2.scale = Ogre::Vector3.new(2,2,2)

child2.roll Ogre::Degree.new(45)
child2.pitch Ogre::Degree.new(45)
#child2.roll Ogre::Degree.new(45)

child1.attach(entGround)
child2.attach(entSphere)


pointLight = sm.createLight("pointLight",
	type: :point,
	position: Ogre::Vector3.new(0, 150, 250),
	diffuseColor: Ogre::Color.new(1.0, 0.0, 0.0),
	specularColor: Ogre::Color.new(0.75, 0.50, 0.0)
)


directionalLight = sm.createLight("directionalLight",
	type: :directional,
	diffuseColor: Ogre::Color.new(0.25, 0.5, 0),
	specularColor: Ogre::Color.new(0.75, 0.5, 0),
	direction: Ogre::Vector3.new( 0, -1, 1 )
)

spotLight = sm.createLight("spotLight",
	type: :spotlight,
	diffuseColor: Ogre::Color.new(0, 0, 1.0),
	specularColor: Ogre::Color.new(0, 0, 1.0),
	direction: Ogre::Vector3.new(-1, -1, 0),
	position: Ogre::Vector3.new(300, 300, 0)
)
#spotLight.setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));

spotLight.spotlightInnerAngle = Ogre::Degree.new(35)
spotLight.spotlightOuterAngle = Ogre::Degree.new(50)

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

Ogre.addFrameListener(FL.new(rw))
#exit
Ogre.startRendering
