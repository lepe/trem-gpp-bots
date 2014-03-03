export SP_info_null
code
proc SP_info_null 0 4
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 G_FreeEntity
CALLV
pop
LABELV $81
endproc SP_info_null 0 4
export SP_info_notnull
proc SP_info_notnull 4 8
ADDRLP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRLP4 0
INDIRP4
ARGP4
ADDRLP4 0
INDIRP4
CNSTI4 92
ADDP4
ARGP4
ADDRGP4 G_SetOrigin
CALLV
pop
LABELV $82
endproc SP_info_notnull 4 8
export SP_light
proc SP_light 0 4
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 G_FreeEntity
CALLV
pop
LABELV $83
endproc SP_light 0 4
export TeleportPlayer
proc TeleportPlayer 36 16
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 trap_UnlinkEntity
CALLV
pop
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 20
ADDP4
ADDRFP4 4
INDIRP4
INDIRB
ASGNB 12
ADDRLP4 0
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 28
ADDP4
ASGNP4
ADDRLP4 0
INDIRP4
ADDRLP4 0
INDIRP4
INDIRF4
CNSTF4 1065353216
ADDF4
ASGNF4
ADDRFP4 8
INDIRP4
ARGP4
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 32
ADDP4
ARGP4
ADDRLP4 4
CNSTP4 0
ASGNP4
ADDRLP4 4
INDIRP4
ARGP4
ADDRLP4 4
INDIRP4
ARGP4
ADDRGP4 AngleVectors
CALLV
pop
ADDRLP4 8
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 32
ADDP4
ASGNP4
ADDRLP4 8
INDIRP4
CNSTF4 1137180672
ADDRLP4 8
INDIRP4
INDIRF4
MULF4
ASGNF4
ADDRLP4 12
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 36
ADDP4
ASGNP4
ADDRLP4 12
INDIRP4
CNSTF4 1137180672
ADDRLP4 12
INDIRP4
INDIRF4
MULF4
ASGNF4
ADDRLP4 16
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 40
ADDP4
ASGNP4
ADDRLP4 16
INDIRP4
CNSTF4 1137180672
ADDRLP4 16
INDIRP4
INDIRF4
MULF4
ASGNF4
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 16
ADDP4
CNSTI4 160
ASGNI4
ADDRLP4 20
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 12
ADDP4
ASGNP4
ADDRLP4 20
INDIRP4
ADDRLP4 20
INDIRP4
INDIRI4
CNSTI4 64
BORI4
ASGNI4
ADDRLP4 24
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 112
ADDP4
ASGNP4
ADDRLP4 24
INDIRP4
ADDRLP4 24
INDIRP4
INDIRI4
CNSTI4 2
BXORI4
ASGNI4
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 G_UnlaggedClear
CALLV
pop
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 G_ClearPlayerZapEffects
CALLV
pop
ADDRFP4 0
INDIRP4
ARGP4
ADDRFP4 8
INDIRP4
ARGP4
ADDRGP4 G_SetClientViewAngle
CALLV
pop
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ARGP4
ADDRFP4 0
INDIRP4
ARGP4
CNSTI4 1
ARGI4
ADDRGP4 BG_PlayerStateToEntityState
CALLV
pop
ADDRFP4 0
INDIRP4
CNSTI4 496
ADDP4
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 20
ADDP4
INDIRB
ASGNB 12
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 1740
ADDP4
INDIRI4
CNSTI4 0
NEI4 $85
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 G_KillBox
CALLV
pop
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 trap_LinkEntity
CALLV
pop
LABELV $85
LABELV $84
endproc TeleportPlayer 36 16
export SP_misc_teleporter_dest
proc SP_misc_teleporter_dest 0 0
LABELV $87
endproc SP_misc_teleporter_dest 0 0
export SP_misc_model
proc SP_misc_model 0 4
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 G_FreeEntity
CALLV
pop
LABELV $88
endproc SP_misc_model 0 4
export locateCamera
proc locateCamera 52 8
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 0
INDIRP4
CNSTI4 664
ADDP4
INDIRP4
ARGP4
ADDRLP4 20
ADDRGP4 G_PickTarget
CALLP4
ASGNP4
ADDRLP4 0
ADDRLP4 20
INDIRP4
ASGNP4
ADDRLP4 0
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $90
ADDRGP4 $92
ARGP4
ADDRGP4 G_Printf
CALLV
pop
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 G_FreeEntity
CALLV
pop
ADDRGP4 $89
JUMPV
LABELV $90
ADDRFP4 0
INDIRP4
CNSTI4 520
ADDP4
ADDRLP4 0
INDIRP4
INDIRI4
ASGNI4
ADDRLP4 0
INDIRP4
CNSTI4 536
ADDP4
INDIRI4
CNSTI4 1
BANDI4
CNSTI4 0
EQI4 $93
ADDRFP4 0
INDIRP4
CNSTI4 172
ADDP4
CNSTI4 25
ASGNI4
ADDRGP4 $94
JUMPV
LABELV $93
ADDRLP4 0
INDIRP4
CNSTI4 536
ADDP4
INDIRI4
CNSTI4 2
BANDI4
CNSTI4 0
EQI4 $95
ADDRFP4 0
INDIRP4
CNSTI4 172
ADDP4
CNSTI4 75
ASGNI4
LABELV $95
LABELV $94
ADDRLP4 0
INDIRP4
CNSTI4 536
ADDP4
INDIRI4
CNSTI4 4
BANDI4
CNSTI4 0
EQI4 $97
ADDRFP4 0
INDIRP4
CNSTI4 188
ADDP4
CNSTI4 0
ASGNI4
ADDRGP4 $98
JUMPV
LABELV $97
ADDRFP4 0
INDIRP4
CNSTI4 188
ADDP4
CNSTI4 1
ASGNI4
LABELV $98
ADDRLP4 24
CNSTI4 168
ASGNI4
ADDRFP4 0
INDIRP4
ADDRLP4 24
INDIRI4
ADDP4
ADDRLP4 0
INDIRP4
ADDRLP4 24
INDIRI4
ADDP4
INDIRI4
ASGNI4
ADDRFP4 0
INDIRP4
CNSTI4 104
ADDP4
ADDRLP4 0
INDIRP4
CNSTI4 92
ADDP4
INDIRB
ASGNB 12
ADDRLP4 0
INDIRP4
CNSTI4 664
ADDP4
INDIRP4
ARGP4
ADDRLP4 28
ADDRGP4 G_PickTarget
CALLP4
ASGNP4
ADDRLP4 16
ADDRLP4 28
INDIRP4
ASGNP4
ADDRLP4 16
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $99
ADDRLP4 36
CNSTI4 92
ASGNI4
ADDRLP4 4
ADDRLP4 16
INDIRP4
ADDRLP4 36
INDIRI4
ADDP4
INDIRF4
ADDRLP4 0
INDIRP4
ADDRLP4 36
INDIRI4
ADDP4
INDIRF4
SUBF4
ASGNF4
ADDRLP4 44
CNSTI4 96
ASGNI4
ADDRLP4 4+4
ADDRLP4 16
INDIRP4
ADDRLP4 44
INDIRI4
ADDP4
INDIRF4
ADDRLP4 0
INDIRP4
ADDRLP4 44
INDIRI4
ADDP4
INDIRF4
SUBF4
ASGNF4
ADDRLP4 48
CNSTI4 100
ASGNI4
ADDRLP4 4+8
ADDRLP4 16
INDIRP4
ADDRLP4 48
INDIRI4
ADDP4
INDIRF4
ADDRLP4 0
INDIRP4
ADDRLP4 48
INDIRI4
ADDP4
INDIRF4
SUBF4
ASGNF4
ADDRLP4 4
ARGP4
ADDRGP4 VectorNormalize
CALLF4
pop
ADDRGP4 $100
JUMPV
LABELV $99
ADDRLP4 0
INDIRP4
CNSTI4 116
ADDP4
ARGP4
ADDRLP4 4
ARGP4
ADDRGP4 G_SetMovedir
CALLV
pop
LABELV $100
ADDRLP4 4
ARGP4
ADDRLP4 32
ADDRGP4 DirToByte
CALLI4
ASGNI4
ADDRFP4 0
INDIRP4
CNSTI4 184
ADDP4
ADDRLP4 32
INDIRI4
ASGNI4
LABELV $89
endproc locateCamera 52 8
export SP_misc_portal_surface
proc SP_misc_portal_surface 20 4
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRLP4 4
CNSTF4 0
ASGNF4
ADDRFP4 0
INDIRP4
CNSTI4 452
ADDP4
ADDRLP4 4
INDIRF4
ASGNF4
ADDRFP4 0
INDIRP4
CNSTI4 448
ADDP4
ADDRLP4 4
INDIRF4
ASGNF4
ADDRFP4 0
INDIRP4
CNSTI4 444
ADDP4
ADDRLP4 4
INDIRF4
ASGNF4
ADDRLP4 12
CNSTF4 0
ASGNF4
ADDRFP4 0
INDIRP4
CNSTI4 464
ADDP4
ADDRLP4 12
INDIRF4
ASGNF4
ADDRFP4 0
INDIRP4
CNSTI4 460
ADDP4
ADDRLP4 12
INDIRF4
ASGNF4
ADDRFP4 0
INDIRP4
CNSTI4 456
ADDP4
ADDRLP4 12
INDIRF4
ASGNF4
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 trap_LinkEntity
CALLV
pop
ADDRFP4 0
INDIRP4
CNSTI4 432
ADDP4
CNSTI4 64
ASGNI4
ADDRFP4 0
INDIRP4
CNSTI4 4
ADDP4
CNSTI4 8
ASGNI4
ADDRFP4 0
INDIRP4
CNSTI4 664
ADDP4
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $104
ADDRFP4 0
INDIRP4
CNSTI4 104
ADDP4
ADDRFP4 0
INDIRP4
CNSTI4 92
ADDP4
INDIRB
ASGNB 12
ADDRGP4 $105
JUMPV
LABELV $104
ADDRFP4 0
INDIRP4
CNSTI4 764
ADDP4
ADDRGP4 locateCamera
ASGNP4
ADDRFP4 0
INDIRP4
CNSTI4 760
ADDP4
ADDRGP4 level+32
INDIRI4
CNSTI4 100
ADDI4
ASGNI4
LABELV $105
LABELV $103
endproc SP_misc_portal_surface 20 4
export SP_misc_portal_camera
proc SP_misc_portal_camera 20 12
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRLP4 8
CNSTF4 0
ASGNF4
ADDRFP4 0
INDIRP4
CNSTI4 452
ADDP4
ADDRLP4 8
INDIRF4
ASGNF4
ADDRFP4 0
INDIRP4
CNSTI4 448
ADDP4
ADDRLP4 8
INDIRF4
ASGNF4
ADDRFP4 0
INDIRP4
CNSTI4 444
ADDP4
ADDRLP4 8
INDIRF4
ASGNF4
ADDRLP4 16
CNSTF4 0
ASGNF4
ADDRFP4 0
INDIRP4
CNSTI4 464
ADDP4
ADDRLP4 16
INDIRF4
ASGNF4
ADDRFP4 0
INDIRP4
CNSTI4 460
ADDP4
ADDRLP4 16
INDIRF4
ASGNF4
ADDRFP4 0
INDIRP4
CNSTI4 456
ADDP4
ADDRLP4 16
INDIRF4
ASGNF4
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 trap_LinkEntity
CALLV
pop
ADDRGP4 $108
ARGP4
ADDRGP4 $109
ARGP4
ADDRLP4 0
ARGP4
ADDRGP4 G_SpawnFloat
CALLI4
pop
ADDRFP4 0
INDIRP4
CNSTI4 168
ADDP4
CNSTF4 1132462080
ADDRLP4 0
INDIRF4
CNSTF4 1135869952
DIVF4
MULF4
CVFI4 4
ASGNI4
LABELV $107
endproc SP_misc_portal_camera 20 12
export SP_toggle_particle_system
proc SP_toggle_particle_system 4 0
ADDRLP4 0
ADDRFP4 0
INDIRP4
CNSTI4 8
ADDP4
ASGNP4
ADDRLP4 0
INDIRP4
ADDRLP4 0
INDIRP4
INDIRI4
CNSTI4 256
BXORI4
ASGNI4
ADDRFP4 0
INDIRP4
CNSTI4 760
ADDP4
CNSTI4 0
ASGNI4
LABELV $110
endproc SP_toggle_particle_system 4 0
export SP_use_particle_system
proc SP_use_particle_system 4 4
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 SP_toggle_particle_system
CALLV
pop
ADDRFP4 0
INDIRP4
CNSTI4 2168
ADDP4
INDIRF4
CNSTF4 0
LEF4 $112
ADDRFP4 0
INDIRP4
CNSTI4 764
ADDP4
ADDRGP4 SP_toggle_particle_system
ASGNP4
ADDRFP4 0
INDIRP4
CNSTI4 760
ADDP4
ADDRGP4 level+32
INDIRI4
CNSTF4 1148846080
ADDRFP4 0
INDIRP4
CNSTI4 2168
ADDP4
INDIRF4
MULF4
CVFI4 4
ADDI4
ASGNI4
LABELV $112
LABELV $111
endproc SP_use_particle_system 4 4
export SP_misc_particle_system
proc SP_misc_particle_system 16 12
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 0
INDIRP4
ARGP4
ADDRFP4 0
INDIRP4
CNSTI4 92
ADDP4
ARGP4
ADDRGP4 G_SetOrigin
CALLV
pop
ADDRGP4 $116
ARGP4
ADDRGP4 $117
ARGP4
ADDRLP4 0
ARGP4
ADDRGP4 G_SpawnString
CALLI4
pop
ADDRGP4 $118
ARGP4
ADDRGP4 $109
ARGP4
ADDRFP4 0
INDIRP4
CNSTI4 2168
ADDP4
ARGP4
ADDRGP4 G_SpawnFloat
CALLI4
pop
ADDRLP4 0
INDIRP4
ARGP4
ADDRLP4 8
ADDRGP4 G_ParticleSystemIndex
CALLI4
ASGNI4
ADDRFP4 0
INDIRP4
CNSTI4 160
ADDP4
ADDRLP4 8
INDIRI4
ASGNI4
ADDRFP4 0
INDIRP4
CNSTI4 536
ADDP4
INDIRI4
CNSTI4 1
BANDI4
CNSTI4 0
EQI4 $119
ADDRLP4 12
ADDRFP4 0
INDIRP4
CNSTI4 8
ADDP4
ASGNP4
ADDRLP4 12
INDIRP4
ADDRLP4 12
INDIRP4
INDIRI4
CNSTI4 256
BORI4
ASGNI4
LABELV $119
ADDRFP4 0
INDIRP4
CNSTI4 780
ADDP4
ADDRGP4 SP_use_particle_system
ASGNP4
ADDRFP4 0
INDIRP4
CNSTI4 4
ADDP4
CNSTI4 15
ASGNI4
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 trap_LinkEntity
CALLV
pop
LABELV $115
endproc SP_misc_particle_system 16 12
export SP_use_anim_model
proc SP_use_anim_model 8 0
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 0
INDIRP4
CNSTI4 536
ADDP4
INDIRI4
CNSTI4 1
BANDI4
CNSTI4 0
EQI4 $122
ADDRFP4 0
INDIRP4
CNSTI4 8
ADDP4
INDIRI4
CNSTI4 256
BANDI4
CNSTI4 0
EQI4 $124
ADDRLP4 0
ADDRFP4 0
INDIRP4
CNSTI4 8
ADDP4
ASGNP4
ADDRLP4 0
INDIRP4
ADDRLP4 0
INDIRP4
INDIRI4
CNSTI4 -257
BANDI4
ASGNI4
ADDRGP4 $123
JUMPV
LABELV $124
ADDRLP4 4
ADDRFP4 0
INDIRP4
CNSTI4 8
ADDP4
ASGNP4
ADDRLP4 4
INDIRP4
ADDRLP4 4
INDIRP4
INDIRI4
CNSTI4 256
BORI4
ASGNI4
ADDRGP4 $123
JUMPV
LABELV $122
ADDRFP4 0
INDIRP4
CNSTI4 8
ADDP4
INDIRI4
CNSTI4 4096
BANDI4
CNSTI4 0
EQI4 $126
ADDRLP4 0
ADDRFP4 0
INDIRP4
CNSTI4 8
ADDP4
ASGNP4
ADDRLP4 0
INDIRP4
ADDRLP4 0
INDIRP4
INDIRI4
CNSTI4 -4097
BANDI4
ASGNI4
ADDRGP4 $127
JUMPV
LABELV $126
ADDRLP4 4
ADDRFP4 0
INDIRP4
CNSTI4 8
ADDP4
ASGNP4
ADDRLP4 4
INDIRP4
ADDRLP4 4
INDIRP4
INDIRI4
CNSTI4 4096
BORI4
ASGNI4
LABELV $127
LABELV $123
LABELV $121
endproc SP_use_anim_model 8 0
export SP_misc_anim_model
proc SP_misc_anim_model 32 4
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 0
INDIRP4
CNSTI4 188
ADDP4
ADDRFP4 0
INDIRP4
CNSTI4 2564
ADDP4
INDIRF4
CVFI4 4
ASGNI4
ADDRFP4 0
INDIRP4
CNSTI4 192
ADDP4
ADDRFP4 0
INDIRP4
CNSTI4 2568
ADDP4
INDIRF4
CVFI4 4
ASGNI4
ADDRFP4 0
INDIRP4
CNSTI4 200
ADDP4
ADDRFP4 0
INDIRP4
CNSTI4 2572
ADDP4
INDIRF4
CVFI4 4
ASGNI4
ADDRFP4 0
INDIRP4
CNSTI4 196
ADDP4
ADDRFP4 0
INDIRP4
CNSTI4 2576
ADDP4
INDIRF4
CVFI4 4
ASGNI4
ADDRFP4 0
INDIRP4
CNSTI4 128
ADDP4
ADDRFP4 0
INDIRP4
CNSTI4 632
ADDP4
INDIRF4
ASGNF4
ADDRFP4 0
INDIRP4
CNSTI4 548
ADDP4
INDIRP4
ARGP4
ADDRLP4 24
ADDRGP4 G_ModelIndex
CALLI4
ASGNI4
ADDRFP4 0
INDIRP4
CNSTI4 160
ADDP4
ADDRLP4 24
INDIRI4
ASGNI4
ADDRFP4 0
INDIRP4
CNSTI4 780
ADDP4
ADDRGP4 SP_use_anim_model
ASGNP4
ADDRFP4 0
INDIRP4
CNSTI4 4
ADDP4
CNSTI4 16
ASGNI4
ADDRFP4 0
INDIRP4
CNSTI4 536
ADDP4
INDIRI4
CNSTI4 2
BANDI4
CNSTI4 0
EQI4 $129
ADDRLP4 28
ADDRFP4 0
INDIRP4
CNSTI4 8
ADDP4
ASGNP4
ADDRLP4 28
INDIRP4
ADDRLP4 28
INDIRP4
INDIRI4
CNSTI4 4096
BORI4
ASGNI4
LABELV $129
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 trap_LinkEntity
CALLV
pop
LABELV $128
endproc SP_misc_anim_model 32 4
export SP_use_light_flare
proc SP_use_light_flare 4 0
ADDRLP4 0
ADDRFP4 0
INDIRP4
CNSTI4 8
ADDP4
ASGNP4
ADDRLP4 0
INDIRP4
ADDRLP4 0
INDIRP4
INDIRI4
CNSTI4 256
BXORI4
ASGNI4
LABELV $131
endproc SP_use_light_flare 4 0
proc findEmptySpot 128 28
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 4
ADDRFP4 4
INDIRF4
ASGNF4
ADDRFP4 8
ADDRFP4 8
INDIRP4
ASGNP4
ADDRLP4 108
CNSTF4 0
ASGNF4
ADDRLP4 88+8
ADDRLP4 108
INDIRF4
ASGNF4
ADDRLP4 88+4
ADDRLP4 108
INDIRF4
ASGNF4
ADDRLP4 88
ADDRLP4 108
INDIRF4
ASGNF4
ADDRLP4 104
CNSTI4 -1
ASGNI4
LABELV $135
ADDRLP4 100
CNSTI4 -1
ASGNI4
LABELV $139
ADDRLP4 84
CNSTI4 -1
ASGNI4
LABELV $143
ADDRLP4 0
ADDRLP4 104
INDIRI4
CVIF4 4
ADDRFP4 4
INDIRF4
MULF4
ASGNF4
ADDRLP4 0+4
ADDRLP4 100
INDIRI4
CVIF4 4
ADDRFP4 4
INDIRF4
MULF4
ASGNF4
ADDRLP4 0+8
ADDRLP4 84
INDIRI4
CVIF4 4
ADDRFP4 4
INDIRF4
MULF4
ASGNF4
ADDRLP4 12
ADDRFP4 0
INDIRP4
INDIRF4
ADDRLP4 0
INDIRF4
ADDF4
ASGNF4
ADDRLP4 12+4
ADDRFP4 0
INDIRP4
CNSTI4 4
ADDP4
INDIRF4
ADDRLP4 0+4
INDIRF4
ADDF4
ASGNF4
ADDRLP4 12+8
ADDRFP4 0
INDIRP4
CNSTI4 8
ADDP4
INDIRF4
ADDRLP4 0+8
INDIRF4
ADDF4
ASGNF4
ADDRLP4 24
ARGP4
ADDRLP4 12
ARGP4
ADDRLP4 120
CNSTP4 0
ASGNP4
ADDRLP4 120
INDIRP4
ARGP4
ADDRLP4 120
INDIRP4
ARGP4
ADDRLP4 12
ARGP4
CNSTI4 -1
ARGI4
CNSTI4 1
ARGI4
ADDRGP4 trap_Trace
CALLV
pop
ADDRLP4 24
INDIRI4
CNSTI4 0
NEI4 $153
ADDRLP4 24
ARGP4
ADDRLP4 12
ARGP4
ADDRLP4 124
CNSTP4 0
ASGNP4
ADDRLP4 124
INDIRP4
ARGP4
ADDRLP4 124
INDIRP4
ARGP4
ADDRFP4 0
INDIRP4
ARGP4
CNSTI4 -1
ARGI4
CNSTI4 1
ARGI4
ADDRGP4 trap_Trace
CALLV
pop
ADDRLP4 0
ADDRLP4 0
INDIRF4
ADDRLP4 24+8
INDIRF4
MULF4
ASGNF4
ADDRLP4 0+4
ADDRLP4 0+4
INDIRF4
ADDRLP4 24+8
INDIRF4
MULF4
ASGNF4
ADDRLP4 0+8
ADDRLP4 0+8
INDIRF4
ADDRLP4 24+8
INDIRF4
MULF4
ASGNF4
ADDRLP4 88
ADDRLP4 88
INDIRF4
ADDRLP4 0
INDIRF4
ADDF4
ASGNF4
ADDRLP4 88+4
ADDRLP4 88+4
INDIRF4
ADDRLP4 0+4
INDIRF4
ADDF4
ASGNF4
ADDRLP4 88+8
ADDRLP4 88+8
INDIRF4
ADDRLP4 0+8
INDIRF4
ADDF4
ASGNF4
LABELV $153
LABELV $144
ADDRLP4 84
ADDRLP4 84
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
ADDRLP4 84
INDIRI4
CNSTI4 1
LEI4 $143
LABELV $140
ADDRLP4 100
ADDRLP4 100
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
ADDRLP4 100
INDIRI4
CNSTI4 1
LEI4 $139
LABELV $136
ADDRLP4 104
ADDRLP4 104
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
ADDRLP4 104
INDIRI4
CNSTI4 1
LEI4 $135
ADDRLP4 88
ARGP4
ADDRGP4 VectorNormalize
CALLF4
pop
ADDRLP4 88
ADDRLP4 88
INDIRF4
ADDRFP4 4
INDIRF4
MULF4
ASGNF4
ADDRLP4 88+4
ADDRLP4 88+4
INDIRF4
ADDRFP4 4
INDIRF4
MULF4
ASGNF4
ADDRLP4 88+8
ADDRLP4 88+8
INDIRF4
ADDRFP4 4
INDIRF4
MULF4
ASGNF4
ADDRFP4 8
INDIRP4
ADDRFP4 0
INDIRP4
INDIRF4
ADDRLP4 88
INDIRF4
ADDF4
ASGNF4
ADDRLP4 116
CNSTI4 4
ASGNI4
ADDRFP4 8
INDIRP4
ADDRLP4 116
INDIRI4
ADDP4
ADDRFP4 0
INDIRP4
ADDRLP4 116
INDIRI4
ADDP4
INDIRF4
ADDRLP4 88+4
INDIRF4
ADDF4
ASGNF4
ADDRLP4 120
CNSTI4 8
ASGNI4
ADDRFP4 8
INDIRP4
ADDRLP4 120
INDIRI4
ADDP4
ADDRFP4 0
INDIRP4
ADDRLP4 120
INDIRI4
ADDP4
INDIRF4
ADDRLP4 88+8
INDIRF4
ADDF4
ASGNF4
LABELV $132
endproc findEmptySpot 128 28
export SP_misc_light_flare
proc SP_misc_light_flare 24 12
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 0
INDIRP4
CNSTI4 4
ADDP4
CNSTI4 18
ASGNI4
ADDRFP4 0
INDIRP4
CNSTI4 676
ADDP4
INDIRP4
ARGP4
ADDRLP4 4
ADDRGP4 G_ShaderIndex
CALLI4
ASGNI4
ADDRFP4 0
INDIRP4
CNSTI4 160
ADDP4
ADDRLP4 4
INDIRI4
ASGNI4
ADDRFP4 0
INDIRP4
CNSTI4 104
ADDP4
ADDRFP4 0
INDIRP4
CNSTI4 632
ADDP4
INDIRB
ASGNB 12
ADDRFP4 0
INDIRP4
CNSTI4 92
ADDP4
ARGP4
CNSTF4 1090519040
ARGF4
ADDRFP4 0
INDIRP4
CNSTI4 128
ADDP4
ARGP4
ADDRGP4 findEmptySpot
CALLV
pop
ADDRFP4 0
INDIRP4
CNSTI4 780
ADDP4
ADDRGP4 SP_use_light_flare
ASGNP4
ADDRGP4 $175
ARGP4
ADDRGP4 $176
ARGP4
ADDRFP4 0
INDIRP4
CNSTI4 688
ADDP4
ARGP4
ADDRGP4 G_SpawnFloat
CALLI4
pop
ADDRFP4 0
INDIRP4
CNSTI4 84
ADDP4
ADDRFP4 0
INDIRP4
CNSTI4 688
ADDP4
INDIRF4
CVFI4 4
ASGNI4
ADDRGP4 $177
ARGP4
ADDRGP4 $109
ARGP4
ADDRFP4 0
INDIRP4
CNSTI4 208
ADDP4
ARGP4
ADDRGP4 G_SpawnInt
CALLI4
pop
ADDRFP4 0
INDIRP4
CNSTI4 536
ADDP4
INDIRI4
CNSTI4 1
BANDI4
CNSTI4 0
EQI4 $178
ADDRLP4 20
ADDRFP4 0
INDIRP4
CNSTI4 8
ADDP4
ASGNP4
ADDRLP4 20
INDIRP4
ADDRLP4 20
INDIRP4
INDIRI4
CNSTI4 256
BORI4
ASGNI4
LABELV $178
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 trap_LinkEntity
CALLV
pop
LABELV $174
endproc SP_misc_light_flare 24 12
import nodethink
import spawnnode
import trap_RemoveCommand
import trap_AddCommand
import trap_SendGameStat
import trap_SnapVector
import trap_GetEntityToken
import trap_GetUsercmd
import trap_BotFreeClient
import trap_BotAllocateClient
import trap_EntityContact
import trap_EntitiesInBox
import trap_UnlinkEntity
import trap_LinkEntity
import trap_AreasConnected
import trap_AdjustAreaPortalState
import trap_InPVSIgnorePortals
import trap_InPVS
import trap_PointContents
import trap_Trace
import trap_SetBrushModel
import trap_GetServerinfo
import trap_SetUserinfo
import trap_GetUserinfo
import trap_SetConfigstringRestrictions
import trap_GetConfigstring
import trap_SetConfigstring
import trap_SendServerCommand
import trap_DropClient
import trap_LocateGameData
import trap_Cvar_VariableStringBuffer
import trap_Cvar_VariableIntegerValue
import trap_Cvar_Set
import trap_Cvar_Update
import trap_Cvar_Register
import trap_SendConsoleCommand
import trap_FS_Seek
import trap_FS_GetFileList
import trap_FS_FCloseFile
import trap_FS_Write
import trap_FS_Read
import trap_FS_FOpenFile
import trap_Args
import trap_Argv
import trap_Argc
import trap_RealTime
import trap_Milliseconds
import trap_Error
import trap_Print
import g_bot_lcannon
import g_bot_flamer
import g_bot_prifle
import g_bot_chaingun
import g_bot_mdriver
import g_bot_lasgun
import g_bot_psaw
import g_bot_shotgun
import g_bot_mgun
import g_bot_evolve
import g_bot_spawnprotection
import g_bot
import g_level4_range
import g_level3UPG_range
import g_level3_range
import g_level2UPG_range
import g_level2_range
import g_level1UPG_range
import g_level1_range
import g_level0_range
import g_human_strafe
import g_human_range
import g_pathpassword
import g_pathediting
import g_censorship
import g_allowTeamOverlay
import g_publicAdminMessages
import g_specChat
import g_privateMessages
import g_adminMaxBan
import g_adminTempBan
import g_admin
import g_emoticonsAllowedInNames
import g_layoutAuto
import g_layouts
import g_mapConfigs
import g_shove
import g_floodMinTime
import g_floodMaxDemerits
import g_voiceChats
import g_debugVoices
import g_sayAreaRange
import g_initialMapRotation
import g_nextMap
import g_mapRotationStack
import g_mapRotationNodes
import g_currentMapRotation
import g_debugMapRotation
import g_markDeconstruct
import g_disabledBuildables
import g_disabledClasses
import g_disabledEquipment
import g_unlagged
import g_freeFundPeriod
import g_teamImbalanceWarnings
import g_alienStage3Threshold
import g_alienStage2Threshold
import g_alienMaxStage
import g_alienCredits
import g_alienStage
import g_humanStage3Threshold
import g_humanStage2Threshold
import g_humanMaxStage
import g_humanCredits
import g_humanStage
import g_humanRepeaterMaxZones
import g_humanRepeaterBuildQueueTime
import g_humanRepeaterBuildPoints
import g_humanBuildQueueTime
import g_humanBuildPoints
import g_alienBuildQueueTime
import g_alienBuildPoints
import pmove_msec
import pmove_fixed
import g_smoothClients
import g_teamForceBalance
import g_suddenDeathVoteDelay
import g_suddenDeathVotePercent
import g_voteLimit
import g_allowVote
import g_doWarmup
import g_warmup
import g_motd
import g_synchronousClients
import g_debugDamage
import g_debugMove
import g_inactivity
import g_knockback
import g_speed
import g_gravity
import g_needpass
import g_password
import g_dretchPunt
import g_friendlyBuildableFire
import g_friendlyFire
import g_suddenDeathTime
import g_timelimit
import g_maxNameChanges
import g_minNameChangePeriod
import g_lockTeamsAtStart
import g_restarted
import g_maxGameClients
import g_maxclients
import g_cheats
import g_dedicated
import g_entities
import level
import G_namelog_cleanup
import G_namelog_update_name
import G_namelog_update_score
import G_namelog_restore
import G_namelog_disconnect
import G_namelog_connect
import G_ClearRotationStack
import G_MapExists
import G_ShutdownMapRotations
import G_InitMapRotations
import G_MapRotationActive
import G_StopMapRotation
import G_StartMapRotation
import G_AdvanceMapRotation
import G_PrintRotations
import G_WriteSessionData
import G_InitSessionData
import G_ReadSessionData
import G_UpdateTeamConfigStrings
import CheckTeamStatus
import TeamplayInfoMessage
import Team_GetLocation
import G_ChangeTeam
import G_LeaveTeam
import OnSameTeam
import G_TeamCommand
import G_TeamFromString
import G_RunClient
import ClientEndFrame
import ClientThink
import G_UnlaggedOff
import G_UnlaggedOn
import G_UnlaggedCalc
import G_UnlaggedClear
import G_UnlaggedStore
import ClientCommand
import ClientBegin
import ClientDisconnect
import ClientUserinfoChanged
import ClientConnect
import G_TimeTilSuddenDeath
import LogExit
import G_CheckVote
import G_ExecuteVote
import G_Vote
import G_Error
import G_Printf
import SendScoreboardMessageToAllClients
import G_LogPrintf
import G_AdminMessage
import G_RunThink
import FindIntermissionPoint
import CalculateRanks
import G_MapConfigs
import MoveClientToIntermission
import ScoreboardMessage
import FireWeapon3
import FireWeapon2
import FireWeapon
import G_UnregisterCommands
import G_RegisterCommands
import ConsoleCommand
import SpotWouldTelefrag
import player_die
import ClientSpawn
import BeginIntermission
import respawn
import G_SelectHumanLockSpawnPoint
import G_SelectAlienLockSpawnPoint
import G_SelectSpawnPoint
import G_SelectTremulousSpawnPoint
import G_SetClientViewAngle
import TeamCount
import G_AddCreditToClient
import G_ClearPlayerZapEffects
import G_UpdateZaps
import G_CrushAttack
import G_ChargeAttack
import CheckCkitRepair
import CheckPounceAttack
import CheckGrabAttack
import CheckVenomAttack
import SnapVectorTowards
import CalcMuzzlePoint
import G_GiveClientMaxAmmo
import G_ForceWeaponChange
import ShineTorch
import G_Checktrigger_stages
import trigger_teleporter_touch
import manualTriggerSpectator
import Touch_DoorTrigger
import G_RunMover
import launch_grenade
import fire_hive
import fire_bounceBall
import fire_slowBlob
import fire_paraLockBlob
import fire_lockblob
import fire_luciferCannon
import fire_pulseRifle
import fire_blaster
import fire_flamer
import G_RunMissile
import G_InitDamageLocations
import G_LogDestruction
import AddScore
import body_die
import G_RewardAttackers
import G_SelectiveRadiusDamage
import G_RadiusDamage
import G_SelectiveDamage
import G_Damage
import CanDamage
import G_ClosestEnt
import G_Visible
import G_CloseMenus
import G_TriggerMenuArgs
import G_TriggerMenu
import G_ClientIsLagging
import BuildShaderStateConfig
import AddRemap
import G_SetOrigin
import G_BroadcastEvent
import G_AddEvent
import G_AddPredictableEvent
import vectoyaw
import vtos
import tv
import G_TouchSolids
import G_TouchTriggers
import G_EntitiesFree
import G_FreeEntity
import G_Sound
import G_TempEntity
import G_Spawn
import G_InitGentity
import G_SetMovedir
import G_UseTargets
import G_PickTarget
import G_Find
import G_KillBox
import G_SoundIndex
import G_ModelIndex
import G_ShaderIndex
import G_ParticleSystemIndex
import G_AddressCompare
import G_AddressParse
import G_BuildLogRevert
import G_BuildLogAuto
import G_BuildLogSet
import G_BuildLogNew
import G_InPowerZone
import G_RepeaterEntityForPoint
import G_PowerEntityForEntity
import G_PowerEntityForPoint
import G_FindPower
import G_GetMarkedBuildPoints
import G_GetBuildPoints
import G_QueueBuildPoints
import G_NextQueueTime
import G_BaseSelfDestruct
import G_LayoutLoad
import G_LayoutSelect
import G_LayoutList
import G_LayoutSave
import FinishSpawningBuildable
import G_SpawnBuildable
import G_SetIdleBuildableAnim
import G_SetBuildableAnim
import G_BuildIfValid
import G_CanBuild
import G_ClearDeconMarks
import G_BuildableRange
import G_BuildableThink
import G_FindCreep
import G_Overmind
import G_Reactor
import G_FindDCC
import G_IsDCCBuilt
import G_IsPowered
import G_CheckSpawnPoint
import G_Physics
import G_CensorString
import G_LoadCensors
import G_ListCommands
import G_FloodLimited
import Cmd_AdminMessage_f
import Cmd_Test_f
import Cmd_ListMaps_f
import Cmd_PrivateMessage_f
import G_SanitiseString
import G_UnEscapeString
import G_DecolorString
import G_Say
import ConcatArgsPrintable
import ConcatArgs
import G_ClientNumbersFromString
import G_ClientNumberFromString
import G_ToggleFollow
import G_FollowNewClient
import G_FollowLockView
import G_StopFromFollowing
import G_StopFollowing
import botShootIfTargetInRange
import botGetDistanceBetweenPlayer
import botTargetInRange
import botFindClosestEnemy
import botAimAtTarget
import G_BotIntermissionThink
import G_BotSpectatorThink
import G_FastThink
import G_FrameAim
import G_BotThink
import G_BotCmd
import G_BotReload
import G_DeleteBots
import G_BotDel
import G_BotAdd
import G_Bots
import G_Rand
import G_NewString
import G_SpawnEntitiesFromString
import G_SpawnVector
import G_SpawnInt
import G_SpawnFloat
import G_SpawnString
import G_PrintSpawnQueue
import G_GetPosInSpawnQueue
import G_RemoveFromSpawnQueue
import G_PushSpawnQueue
import G_SearchSpawnQueue
import G_PeekSpawnQueue
import G_PopSpawnQueue
import G_GetSpawnQueueLength
import G_InitSpawnQueue
import G_admin_cleanup
import G_admin_duration
import G_admin_buffer_end
import G_admin_buffer_begin
import G_admin_buffer_print
import G_admin_print
import G_password
import G_drawnodes
import G_admin_botcmd
import G_admin_bot
import G_admin_revert
import G_admin_buildlog
import G_admin_builder
import G_admin_pause
import G_admin_lock
import G_admin_namelog
import G_admin_nextmap
import G_admin_restart
import G_admin_rename
import G_admin_spec999
import G_admin_endvote
import G_admin_allready
import G_admin_admintest
import G_admin_adminhelp
import G_admin_showbans
import G_admin_denybuild
import G_admin_mute
import G_admin_changemap
import G_admin_listplayers
import G_admin_listlayouts
import G_admin_listadmins
import G_admin_putteam
import G_admin_unban
import G_admin_ban
import G_admin_adjustban
import G_admin_kick
import G_admin_setlevel
import G_admin_time
import G_admin_authlog
import G_admin_admin
import G_admin_name_check
import G_admin_permission
import G_admin_readconfig
import G_admin_cmd_check
import G_admin_ban_check
import G_admin_cmdlist
import G_admin_unregister_cmds
import G_admin_register_cmds
import cmdcmp
import BG_TeamName
import BG_LoadEmoticons
import BG_VoiceTrackFind
import BG_VoiceTrackByNum
import BG_VoiceCmdByNum
import BG_VoiceCmdFind
import BG_VoiceByName
import BG_PrintVoices
import BG_VoiceInit
import BG_PrimaryWeapon
import BG_BuildableIsAllowed
import BG_ClassIsAllowed
import BG_UpgradeIsAllowed
import BG_WeaponIsAllowed
import BG_InitAllowedGameElements
import BG_ParseCSVBuildableList
import BG_ParseCSVClassList
import BG_ParseCSVEquipmentList
import atoi_neg
import atof_neg
import BG_PlayerTouchesItem
import BG_PlayerStateToEntityStateExtraPolate
import BG_PlayerStateToEntityState
import BG_AddPredictableEventToPlayerstate
import BG_EvaluateTrajectoryDelta
import BG_EvaluateTrajectory
import BG_MemoryInfo
import BG_DefragmentMemory
import BG_Free
import BG_InitMemory
import BG_Alloc
import BG_UpgradeAllowedInStage
import BG_Upgrade
import BG_UpgradeByName
import BG_WeaponAllowedInStage
import BG_Weapon
import BG_WeaponByName
import BG_InitClassConfigs
import BG_AlienCanEvolve
import BG_ClassCanEvolveFromTo
import BG_ClassHasAbility
import BG_ClassBoundingBox
import BG_ClassConfig
import BG_ClassAllowedInStage
import BG_Class
import BG_ClassByName
import BG_InitBuildableConfigs
import BG_BuildableBoundingBox
import BG_BuildableConfig
import BG_BuildableAllowedInStage
import BG_Buildable
import BG_BuildableByEntityName
import BG_BuildableByName
import BG_UnpackEntityNumbers
import BG_PackEntityNumbers
import BG_HasEnergyWeapon
import BG_GetPlayerWeapon
import BG_PlayerPoisonCloudTime
import BG_PlayerCanChangeWeapon
import BG_GetValueOfPlayer
import BG_PositionBuildableRelativeToPlayer
import BG_GetClientViewOrigin
import BG_GetClientNormal
import BG_RotateAxis
import BG_UpgradeIsActive
import BG_DeactivateUpgrade
import BG_ActivateUpgrade
import BG_InventoryContainsUpgrade
import BG_RemoveUpgradeFromInventory
import BG_AddUpgradeToInventory
import BG_SlotsForInventory
import BG_InventoryContainsWeapon
import BG_WeaponIsFull
import BG_EventName
import Pmove
import PM_UpdateViewAngles
import Com_Printf
import Com_Error
import Info_NextPair
import Info_Validate
import Info_SetValueForKey_Big
import Info_SetValueForKey
import Info_RemoveKey_big
import Info_RemoveKey
import Info_ValueForKey
import Com_TruncateLongString
import va
import Q_CountChar
import Q_ParseNewlines
import Q_CleanStr
import Q_PrintStrlen
import Q_strcat
import Q_strncpyz
import Q_stristr
import Q_strrchr
import Q_strupr
import Q_strlwr
import Q_stricmpn
import Q_strncmp
import Q_stricmp
import Q_isintegral
import Q_isanumber
import Q_isalpha
import Q_isupper
import Q_islower
import Q_isprint
import Com_ClientListParse
import Com_ClientListString
import Com_ClientListRemove
import Com_ClientListAdd
import Com_ClientListContains
import Com_RandomBytes
import Com_SkipCharset
import Com_SkipTokens
import Com_sprintf
import Com_HexStrToInt
import Parse3DMatrix
import Parse2DMatrix
import Parse1DMatrix
import SkipRestOfLine
import SkipBracedSection
import COM_MatchToken
import COM_ParseWarning
import COM_ParseError
import COM_Compress
import COM_ParseExt
import COM_Parse
import COM_GetCurrentParseLine
import COM_BeginParseSession
import COM_DefaultExtension
import COM_StripExtension
import COM_GetExtension
import COM_SkipPath
import Com_Clamp
import DistanceBetweenLineSegments
import DistanceBetweenLineSegmentsSquared
import VectorMaxComponent
import VectorMinComponent
import pointToLineDistance
import VectorDistance
import ProjectPointOntoVector
import GetPerpendicularViewVector
import Q_isnan
import PerpendicularVector
import AngleVectors
import VectorMatrixMultiply
import MatrixMultiply
import MakeNormalVectors
import RotateAroundDirection
import RotatePointAroundVector
import ProjectPointOnPlane
import PlaneFromPoints
import AngleDelta
import AngleNormalize180
import AngleNormalize360
import AnglesSubtract
import AngleSubtract
import LerpAngle
import AngleMod
import BoundsIntersectPoint
import BoundsIntersectSphere
import BoundsIntersect
import BoxOnPlaneSide
import SetPlaneSignbits
import AxisCopy
import AxisClear
import AxisToAngles
import AnglesToAxis
import vectoangles
import Q_crandom
import Q_random
import Q_rand
import Q_acos
import Q_log2
import VectorRotate
import Vector4Scale
import VectorNormalize2
import VectorNormalize
import CrossProduct
import VectorInverse
import VectorNormalizeFast
import DistanceSquared
import Distance
import VectorLengthSquared
import VectorLength
import VectorCompare
import AddPointToBounds
import ClearBounds
import RadiusFromBounds
import NormalizeColor
import ColorBytes4
import ColorBytes3
import _VectorMA
import _VectorScale
import _VectorCopy
import _VectorAdd
import _VectorSubtract
import _DotProduct
import ByteToDir
import DirToByte
import ClampShort
import ClampChar
import Q_rsqrt
import Q_fabs
import axisDefault
import vec3_origin
import g_color_table
import Q_StripIndentMarker
import colorDkGrey
import colorMdGrey
import colorLtGrey
import colorWhite
import colorCyan
import colorMagenta
import colorYellow
import colorBlue
import colorGreen
import colorRed
import colorBlack
import bytedirs
import Hunk_Alloc
import FloatSwap
import LongSwap
import ShortSwap
import rint
import pow
import acos
import fabs
import abs
import tan
import atan2
import cos
import sin
import sqrt
import floor
import ceil
import memcpy
import memset
import memmove
import sscanf
import Q_snprintf
import Q_vsnprintf
import strtol
import _atoi
import atoi
import strtod
import _atof
import atof
import toupper
import tolower
import strncpy
import strstr
import strrchr
import strchr
import strcmp
import strcpy
import strcat
import strlen
import bsearch
import rand
import srand
import qsort
lit
align 1
LABELV $177
byte 1 109
byte 1 105
byte 1 110
byte 1 100
byte 1 105
byte 1 115
byte 1 116
byte 1 0
align 1
LABELV $176
byte 1 50
byte 1 48
byte 1 48
byte 1 0
align 1
LABELV $175
byte 1 115
byte 1 112
byte 1 101
byte 1 101
byte 1 100
byte 1 0
align 1
LABELV $118
byte 1 119
byte 1 97
byte 1 105
byte 1 116
byte 1 0
align 1
LABELV $117
byte 1 0
align 1
LABELV $116
byte 1 112
byte 1 115
byte 1 78
byte 1 97
byte 1 109
byte 1 101
byte 1 0
align 1
LABELV $109
byte 1 48
byte 1 0
align 1
LABELV $108
byte 1 114
byte 1 111
byte 1 108
byte 1 108
byte 1 0
align 1
LABELV $92
byte 1 67
byte 1 111
byte 1 117
byte 1 108
byte 1 100
byte 1 110
byte 1 39
byte 1 116
byte 1 32
byte 1 102
byte 1 105
byte 1 110
byte 1 100
byte 1 32
byte 1 116
byte 1 97
byte 1 114
byte 1 103
byte 1 101
byte 1 116
byte 1 32
byte 1 102
byte 1 111
byte 1 114
byte 1 32
byte 1 109
byte 1 105
byte 1 115
byte 1 99
byte 1 95
byte 1 112
byte 1 111
byte 1 114
byte 1 116
byte 1 97
byte 1 108
byte 1 95
byte 1 115
byte 1 117
byte 1 114
byte 1 102
byte 1 97
byte 1 99
byte 1 101
byte 1 10
byte 1 0
