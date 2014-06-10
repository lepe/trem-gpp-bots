// unsorted stuff

bluesmoke
{
  nopicmip
  {
    map gfx/sprites/smoke_blue.tga
    blendFunc Blend
  }
}

gfx/misc/tracer
{
  cull none
  {
    map gfx/sprites/spark.tga
    blendFunc blend
  }
}

gfx/damage/fullscreen_painblend
{
  {
    map gfx/damage/fullscreen_painblend.tga
    blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
    rgbGen vertex
    alphaGen vertex
    tcMod rotate 90
  }

  {
    map gfx/damage/fullscreen_painblend.tga
    blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
    rgbGen vertex
    alphaGen vertex
    tcMod rotate -90
  }
}

gfx/sprites/smoke
{
  cull none
  entityMergable
  {
    map gfx/sprites/smoke.tga
    blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
    rgbGen    vertex
    alphaGen  vertex
  }
}

gfx/sprites/green_acid
{
  nopicmip
  {
    clampmap gfx/sprites/green_acid.tga
    blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
    rgbGen    vertex
    alphaGen  vertex
  }
}

gfx/sprites/spark
{
  cull none
  {
    map gfx/sprites/spark.tga
    blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
    rgbGen    vertex
    alphaGen  vertex
  }
}

gfx/sprites/bubble
{
  sort  underwater
  cull none
  entityMergable
  {
    map gfx/sprites/bubble.jpg
    blendFunc GL_ONE GL_ONE
    rgbGen    vertex
    alphaGen  vertex
  }
}

gfx/sprites/poisoncloud
{
  cull none
  entityMergable
  {
    map gfx/sprites/poisoncloud.tga
    blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
    rgbGen    vertex
    alphaGen  vertex
  }
}

gfx/sprites/chatballoon
{
	{
		map gfx/sprites/chatballoon.tga
		blendfunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
	}
}

gfx/misc/nopower
{
  {
    map gfx/misc/nopower.tga
    blendfunc add
    rgbGen identity
  }
}

models/mapobjects/plant_life/fern_leaf
{
  cull disable
  nopicmip
  {
    map models/mapobjects/plant_life/fern_leaf.tga
    alphaFunc GE128
    depthWrite
    rgbGen vertex
  }
}

models/mapobjects/plant_life/palm_leaf
{
  cull disable
  nopicmip
  {
    map models/mapobjects/plant_life/palm_leaf.tga
    alphaFunc GE128
    depthWrite
    rgbGen vertex
  }
}

models/mapobjects/plant_life/grass
{
  cull disable
  nopicmip
  {
    map models/mapobjects/plant_life/grass.tga
    alphaFunc GE128
    depthWrite
    rgbGen vertex
  }
}