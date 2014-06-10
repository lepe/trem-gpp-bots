models/players/human_base/armour
{
	cull disable
	{
		map models/players/human_base/armour.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/human_base/hexagonal_shields.tga
		blendfunc add
		rgbGen wave triangle 1 1 0 0.3 
	}
}

