Object = 
{
   name = "BlackCube",
   position = { -100.0, 200.0},
	rotation = 0,
	
	collider = { 
		center = {0.0 , 50.0},
		extents = {50.0, 50.0}
	},
	
   physics_settings = {
      mass = 10.0,
      drag = 0.5,
      gravity = false,
	  isStatic = true
   },

   render_settings = {
      sprite = "data\\blackCube.dds"
   }
}