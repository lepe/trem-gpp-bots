models/weapons/flamer/flamer
{
	cull disable
	{
		map models/weapons/flamer/flamer.jpg
		rgbGen lightingDiffuse
	}
	{
		map models/weapons/flamer/flamer_effect.jpg
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 1.5 
	}
}

