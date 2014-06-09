models/players/builder/builder
{
	cull disable
	{
		map models/players/builder/builder_bot.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/builder/builder_eyes.tga
		blendfunc add
		rgbGen wave sin 0 1 0 0.2 
	}
}

