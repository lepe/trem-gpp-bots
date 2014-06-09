models/players/human_bsuit/human_bsuit_bot
{
	cull disable
	{
		map models/players/human_bsuit/human_bsuit_bot.tga
		rgbGen lightingDiffuse
	}
	{
		map models/players/human_bsuit/human_bsuit_effects_shields.tga
		blendfunc add
		rgbGen wave inversesawtooth 0 1 0 0.7 
	}
	{
		map models/players/human_bsuit/human_bsuit_effects.tga
		blendfunc add
		rgbGen wave triangle 0 1 0 0.1 
	}
	{
		map models/players/human_bsuit/human_bsuit_eye.tga
		blendfunc add
		rgbGen wave sin 0 1 0 0.5 
	}
}

