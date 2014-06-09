models/players/level2/level2adv_bot
{    
  {
    map models/players/level2/lvl2_fx_bot.tga
    blendFunc GL_ONE GL_ZERO
    tcmod scale 7 7
    tcMod scroll 5 -5
    tcmod rotate 360
    rgbGen identity
  }

  {
    map models/players/level2/level2adv_bot.tga
    blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
    rgbGen lightingDiffuse
  }
  {
	map models/players/level2/level2adv_eyes.tga
	blendfunc add
	rgbGen wave triangle 0 1 0 0.5 
  }
}

models/players/level2/electric_s_bot
{
  {
    map models/players/level2/electric_bot.jpg
    blendfunc add
    tcMod scroll 10.0 0.5
  }
}

