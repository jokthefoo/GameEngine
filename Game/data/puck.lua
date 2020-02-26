Object = 
{
   name = "puck",
   position = { 0.0, -20.0},
	rotation = 0,
	
	collider = { 
		center = {0.0 , 20.0},
		extents = {20.0, 20.0}
	},
	
   physics_settings = {
      mass = 3.0,
      drag = 0.0,
      gravity = false,
	  isStatic = false
   },

   render_settings = {
      sprite = "data\\blackCubeSmall.dds"
   }
}