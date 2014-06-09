models/players/level1/level1adv_bot
{
	cull disable
	{
		map models/players/level1/level1adv_bot.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/level1/level1adv_eyes.tga
		blendfunc add
		rgbGen wave noise 0 1 0 10 
	}
}

