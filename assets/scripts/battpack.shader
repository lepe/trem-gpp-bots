models/players/human_base/battpack
{
	cull disable
	{
		map models/players/human_base/battpack.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/human_base/battpack_effect.tga
		blendfunc add
		rgbGen wave noise 0 1 0 10 
	}
}

