gfx/blaster/orange_particle
{  
  cull disable
		nopicmip
  {
    map gfx/blaster/orange_particle.jpg
	   blendFunc Add
    alphaGen vertex
    rgbGen vertex
  }
}

gfx/mdriver/green_particle
{  
  cull disable
		nopicmip
  {
    map gfx/mdriver/green_particle.tga
		  blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
    rgbGen vertex
    alphaGen vertex
  }
}

gfx/mdriver/green_particle2
{  
  cull disable
		nopicmip
  {
    map gfx/mdriver/green_particle2.tga
		  blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
    rgbGen vertex
    alphaGen vertex
  }
}

gfx/mdriver/trail
{
  nomipmaps
  cull disable
		nopicmip
  {
    map gfx/mdriver/trail.tga
    blendFunc blend
  }
}

gfx/psaw/blue_particle
{  
  cull disable
		nopicmip
  {
    map gfx/psaw/blue_particle.jpg
    blendFunc GL_ONE GL_ONE
    alphaGen vertex
    rgbGen vertex
  }
}

gfx/rifle/verysmallrock
{  
  cull disable
		nopicmip
  {
    map gfx/rifle/verysmallrock.tga
    blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
    alphaGen vertex
    rgbGen vertex
  }
}

gfx/prifle/red_blob
{  
  cull disable
		nopicmip
  {
    map gfx/prifle/red_blob.tga
    blendFunc blend
				alphaGen Vertex
  }
}

gfx/prifle/red_blob2
{  
  cull disable
		nopicmip
  {
    map gfx/prifle/red_blob.tga
    blendFunc GL_ONE GL_ONE_MINUS_SRC_COLOR
  }
}

gfx/prifle/red_flash
{  
  cull disable
		nopicmip
  {
    map gfx/prifle/red_flash.tga
    blendFunc GL_ONE GL_ONE_MINUS_SRC_COLOR
  }
}

gfx/prifle/red_flash2
{  
  cull disable
		nopicmip
  {
    map gfx/prifle/red_flash2.tga
    blendFunc GL_ONE GL_ONE_MINUS_SRC_COLOR
  }
}

gfx/prifle/red_streak
{  
  nomipmaps
  cull disable
		nopicmip
  {
    map gfx/prifle/red_streak.tga
    blendFunc blend
				alphaGen Vertex
  }
}

gfx/lcannon/primary
{  
  cull disable
		nopicmip
  {
    animmap 24 gfx/lcannon/primary_1.jpg gfx/lcannon/primary_2.jpg gfx/lcannon/primary_3.jpg gfx/lcannon/primary_4.jpg
    blendFunc GL_ONE GL_ONE
  }
}

gfx/lasgun/purple_particle
{  
  cull disable
		nopicmip
  {
    map gfx/lasgun/purple_particle.tga
    blendFunc GL_ONE GL_ONE
  }
}

radialblast01
{  
  cull disable
  nopicmip
  {
    map gfx/lcannon/radial01.jpg
    blendFunc GL_ONE GL_ONE_MINUS_SRC_COLOR
  }
}

radialblast02
{  
  cull disable
  nopicmip
  {
    map gfx/lcannon/radial02.jpg
    blendFunc GL_ONE GL_ONE_MINUS_SRC_COLOR
  }
}

radialblast03
{  
  cull disable
  nopicmip
  {
    map gfx/lcannon/radial03.jpg
    blendFunc GL_ONE GL_ONE_MINUS_SRC_COLOR
  }
}

radialblast04
{  
  cull disable
  nopicmip
  {
    map gfx/lcannon/radial04.jpg
    blendFunc GL_ONE GL_ONE_MINUS_SRC_COLOR
  }
}

radialblast05
{  
  cull disable
  nopicmip
  {
    map gfx/lcannon/radial05.jpg
    blendFunc GL_ONE GL_ONE_MINUS_SRC_COLOR
  }
}

spark00trail
{  
  nomipmaps
  cull disable
  nopicmip
  {
    map gfx/spark/spark00trail.jpg
    blendFunc GL_ONE GL_ONE_MINUS_SRC_COLOR
  }
}

grenadesprite
{
  cull disable
		nopicmip
  {
    map gfx/grenade/grenadesprite.tga
    blendFunc add
				alphaGen Vertex
  }
}

grenadetrail
{  
  nomipmaps
  cull disable
		nopicmip
  {
    map gfx/grenade/grenadetrail.tga
    blendFunc add
				alphaGen Vertex
  }
}