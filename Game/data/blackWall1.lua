Object = 
{
   name = "blackWall",
   position = { 0.0, 280.0},
	rotation = 0,
	
	collider = { 
		center = {0.0 , 20.0},
		extents = {400.0, 20.0}
	},
	
   physics_settings = {
      mass = 10.0,
      drag = 0.5,
      gravity = false,
	  isStatic = true
   },

   render_settings = {
      sprite = "data\\blackWall.dds"
   }
}