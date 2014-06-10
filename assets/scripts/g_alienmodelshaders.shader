// Advanced Marauder

models/players/level2/level2adv
{    
  {
    map models/players/level2/lvl2_fx.tga
    blendFunc GL_ONE GL_ZERO
    tcmod scale 7 7
    tcMod scroll 5 -5
    tcmod rotate 360
    rgbGen identity
  }

  {
    map models/players/level2/adv.tga
    blendFunc GL_SRC_ALPHA GL_ONE_MINUS_SRC_ALPHA
    rgbGen lightingDiffuse
  }
}

models/players/level2/electric_s
{
  {
    map models/players/level2/electric.jpg
    blendfunc add
    tcMod scroll 10 0.5
  }
}





// Booster

models/buildables/booster/booster_head
{
	{
		map models/buildables/booster/booster_head.tga
		rgbGen lightingDiffuse
	}
	{
		map models/buildables/booster/ref_map.tga
		blendfunc filter
		rgbGen identity
		tcMod rotate 5
		tcGen environment 
	}
}

models/buildables/booster/booster_sac
{
	{
		map models/buildables/booster/booster_sac.tga
		rgbGen lightingDiffuse
	}
	{
		map models/buildables/booster/poison.tga
		blendfunc add
		rgbGen wave sin 0 1 0 0.1 
		tcMod scroll -0.05 -0.05
	}
}
models/buildables/booster/pod_strands
{
	cull disable
	{
		map models/buildables/barricade/pod_strands.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
}
models/buildables/hovel/pod_strands
{
	cull disable
	{
		map models/buildables/barricade/pod_strands.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
}





// Egg

models/buildables/eggpod/pod_body
{
 nopicmip
	cull disable
	{
		map models/buildables/eggpod/pod_body.tga
		rgbGen lightingDiffuse
	}
}

models/buildables/eggpod/pod_tip
{
 nopicmip
	cull disable
	{
		map models/buildables/eggpod/pod_tip.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
}

models/buildables/eggpod/pod_tendrils
{
	nopicmip
	cull disable
	{
		map models/buildables/eggpod/pod_tendrils.tga
		rgbGen lightingDiffuse
	}
}

models/buildables/eggpod/pod_strands
{
	nopicmip
	cull disable
	{
		map models/buildables/eggpod/pod_strands.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
}

models/buildables/barricade/pod_strands
{
	nopicmip
	cull disable
	{
		map models/buildables/barricade/pod_strands.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
}
models/buildables/barricade/alien_spike
{
 nopicmip
	{
		map models/buildables/barricade/alien_spike.tga
		rgbGen lightingDiffuse
		}
}

models/buildables/acid_tube/pod_strands
{
 nopicmip
	cull disable
	{
		map models/buildables/eggpod/pod_strands.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
}





// Hive

models/buildables/hive/hive_strands_s
{
	cull disable
	{
		map models/buildables/hive/hive_strands.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
}





// Overmind

models/buildables/overmind/pod_strands
{
	cull disable
	{
		map models/buildables/eggpod/pod_strands.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
}

models/buildables/overmind/over_spike
{
	{
		map models/buildables/overmind/over_spike.tga
		rgbGen lightingDiffuse
	}
	{
		map models/buildables/overmind/ref2.tga
		blendfunc filter
		rgbGen identity
		tcGen environment 
	}
}





// Trapper

models/buildables/trapper/trapper_gills
{
nopicmip
cull disable
	{
		map models/buildables/trapper/trapper_gills.tga
		rgbGen lightingDiffuse
		alphaFunc GE128
	}
	{
		map models/buildables/trapper/trapper_gills.tga
		rgbGen lightingDiffuse
		tcMod scroll -0.01 0
		tcMod scale -1 1
		alphaFunc GE128
	}
}