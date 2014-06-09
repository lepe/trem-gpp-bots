models/weapons/shotgun/shotgun
{
	cull disable
	{
		map models/weapons/shotgun/shotgun.tga
		rgbGen lightingDiffuse
	}
	{
		map models/weapons/shotgun/shotgun_effect.tga
		blendfunc add
		rgbGen wave triangle 0 1 0 1 
	}
}

