Object = 
{
   name = "wall",
   position = { 0.0, -50.0},
	rotation = 0,
	
	collider = { 
		center = {0.0 , 50.0},
		extents = {50.0, 50.0}
	},
	
   physics_settings = {
      mass = 10.0,
      drag = 0.5,
      gravity = false
   },
	
   render_settings = {
      sprite = "data\\bcube.dds"
   }
}