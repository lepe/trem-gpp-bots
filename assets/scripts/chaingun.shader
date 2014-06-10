models/weapons/chaingun/chaingun
{
	cull disable
	{
		map models/weapons/chaingun/chaingun.tga
		rgbGen lightingDiffuse
	}
	{
		map models/weapons/chaingun/chaingun_effect.jpg
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 1.5 
	}
	{
		map models/weapons/chaingun/chaingun_effect0.jpg
		blendfunc add
		rgbGen identityLighting
	}
}

