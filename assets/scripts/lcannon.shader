models/weapons/lcannon/lcannon
{
	cull disable
	{
		map models/weapons/lcannon/lcannon.tga
		rgbGen lightingDiffuse
	}
	{
		map models/weapons/lcannon/lcannon_effect.tga
		blendfunc add
		rgbGen wave triangle 1 1 0 0.1 
	}
	{
		animmap 2 models/weapons/lcannon/lcannon_rays1.jpg models/weapons/lcannon/lcannon_rays2.jpg 
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 1 
	}
}

