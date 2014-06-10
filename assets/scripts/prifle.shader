models/weapons/prifle/prifle
{
	cull disable
	{
		map models/weapons/prifle/prifle.jpg
		rgbGen lightingDiffuse
	}
	{
		map models/weapons/prifle/prifle_effect.jpg
		blendfunc add
		rgbGen wave triangle 1 1 0 0.1 
	}
	{
		animmap 5 models/weapons/prifle/prifle_tray5.tga models/weapons/prifle/prifle_tray3.tga models/weapons/prifle/prifle_tray1.tga models/weapons/prifle/prifle_tray0.tga models/weapons/prifle/prifle_tray2.tga models/weapons/prifle/prifle_tray4.tga
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 1 
	}
}
