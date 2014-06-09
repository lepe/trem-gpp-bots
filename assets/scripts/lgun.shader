models/weapons/lgun/lgun
{
	cull disable
	{
		map models/weapons/lgun/lgun.jpg
		rgbGen lightingDiffuse
	}
	{
		map models/weapons/lgun/lgun_effect.jpg
		blendfunc add
		rgbGen wave noise 0 1 0 10 
	}
	{
		map models/weapons/lgun/lgun_effect0.jpg
		blendfunc add
		rgbGen identityLighting
	}
	{
		animmap 6 models/weapons/lgun/lgun_tray0.jpg models/weapons/lgun/lgun_tray1.jpg models/weapons/lgun/lgun_tray2.jpg models/weapons/lgun/lgun_tray3.jpg models/weapons/lgun/lgun_tray4.jpg models/weapons/lgun/lgun_tray5.jpg models/weapons/lgun/lgun_tray6.jpg models/weapons/lgun/lgun_tray7.jpg 
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 1 
	}
}

