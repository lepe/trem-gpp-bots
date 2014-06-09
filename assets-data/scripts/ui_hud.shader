ui/assets/neutral/squad_h
{
  nopicmip
  {
    map ui/assets/neutral/squad_h.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbgen vertex
  }
}

ui/assets/neutral/squad_v
{
  nopicmip
  {
    map ui/assets/neutral/squad_v.tga
		blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
		rgbgen vertex
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