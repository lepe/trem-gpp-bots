models/weapons/mdriver/mdriver
{
	cull disable
	{
		map models/weapons/mdriver/mdriver.jpg
		rgbGen lightingDiffuse
	}
	{
		map models/weapons/mdriver/mdriver_power.tga
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 1 
	}
	{
		map models/weapons/mdriver/mdriver_power1.tga
		blendfunc add
		rgbGen wave sin 0 1 0 0.5 
	}
}

