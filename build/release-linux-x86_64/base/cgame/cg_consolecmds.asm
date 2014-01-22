code
proc CG_SizeUp_f 8 8
ADDRGP4 $118
ARGP4
ADDRGP4 cg_viewsize+12
INDIRI4
CNSTI4 10
ADDI4
CNSTI4 100
GEI4 $122
ADDRLP4 0
ADDRGP4 cg_viewsize+12
INDIRI4
CNSTI4 10
ADDI4
ASGNI4
ADDRGP4 $123
JUMPV
LABELV $122
ADDRLP4 0
CNSTI4 100
ASGNI4
LABELV $123
ADDRLP4 0
INDIRI4
ARGI4
ADDRLP4 4
ADDRGP4 va
CALLP4
ASGNP4
ADDRGP4 $117
ARGP4
ADDRLP4 4
INDIRP4
ARGP4
ADDRGP4 trap_Cvar_Set
CALLV
pop
LABELV $116
endproc CG_SizeUp_f 8 8
proc CG_SizeDown_f 8 8
ADDRGP4 $118
ARGP4
ADDRGP4 cg_viewsize+12
INDIRI4
CNSTI4 10
SUBI4
CNSTI4 30
LEI4 $128
ADDRLP4 0
ADDRGP4 cg_viewsize+12
INDIRI4
CNSTI4 10
SUBI4
ASGNI4
ADDRGP4 $129
JUMPV
LABELV $128
ADDRLP4 0
CNSTI4 30
ASGNI4
LABELV $129
ADDRLP4 0
INDIRI4
ARGI4
ADDRLP4 4
ADDRGP4 va
CALLP4
ASGNP4
ADDRGP4 $117
ARGP4
ADDRLP4 4
INDIRP4
ARGP4
ADDRGP4 trap_Cvar_Set
CALLV
pop
LABELV $124
endproc CG_SizeDown_f 8 8
proc CG_Viewpos_f 0 20
ADDRGP4 $131
ARGP4
ADDRGP4 cg+112072+24
INDIRF4
CVFI4 4
ARGI4
ADDRGP4 cg+112072+24+4
INDIRF4
CVFI4 4
ARGI4
ADDRGP4 cg+112072+24+8
INDIRF4
CVFI4 4
ARGI4
ADDRGP4 cg+112440+4
INDIRF4
CVFI4 4
ARGI4
ADDRGP4 CG_Printf
CALLV
pop
LABELV $130
endproc CG_Viewpos_f 0 20
export CG_RequestScores
proc CG_RequestScores 0 4
ADDRGP4 cg+113488
INDIRI4
CNSTI4 2000
ADDI4
ADDRGP4 cg+109556
INDIRI4
GEI4 $143
ADDRGP4 cg+113488
ADDRGP4 cg+109556
INDIRI4
ASGNI4
ADDRGP4 $149
ARGP4
ADDRGP4 trap_SendClientCommand
CALLV
pop
CNSTI4 1
RETI4
ADDRGP4 $142
JUMPV
LABELV $143
CNSTI4 0
RETI4
LABELV $142
endproc CG_RequestScores 0 4
proc CG_scrollScoresDown_f 0 12
ADDRGP4 menuScoreboard
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $151
ADDRGP4 cg+115304
INDIRI4
CNSTI4 0
EQI4 $151
ADDRGP4 menuScoreboard
INDIRP4
ARGP4
CNSTI4 2
ARGI4
CNSTI4 1
ARGI4
ADDRGP4 Menu_ScrollFeeder
CALLV
pop
ADDRGP4 menuScoreboard
INDIRP4
ARGP4
CNSTI4 3
ARGI4
CNSTI4 1
ARGI4
ADDRGP4 Menu_ScrollFeeder
CALLV
pop
LABELV $151
LABELV $150
endproc CG_scrollScoresDown_f 0 12
proc CG_scrollScoresUp_f 0 12
ADDRGP4 menuScoreboard
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $155
ADDRGP4 cg+115304
INDIRI4
CNSTI4 0
EQI4 $155
ADDRGP4 menuScoreboard
INDIRP4
ARGP4
CNSTI4 2
ARGI4
CNSTI4 0
ARGI4
ADDRGP4 Menu_ScrollFeeder
CALLV
pop
ADDRGP4 menuScoreboard
INDIRP4
ARGP4
CNSTI4 3
ARGI4
CNSTI4 0
ARGI4
ADDRGP4 Menu_ScrollFeeder
CALLV
pop
LABELV $155
LABELV $154
endproc CG_scrollScoresUp_f 0 12
proc CG_ScoresDown_f 4 16
ADDRGP4 cg+115300
INDIRI4
CNSTI4 0
NEI4 $159
ADDRGP4 menuScoreboard
INDIRP4
ARGP4
CNSTI4 2
ARGI4
CNSTI4 0
ARGI4
CNSTP4 0
ARGP4
ADDRGP4 Menu_SetFeederSelection
CALLV
pop
ADDRGP4 menuScoreboard
INDIRP4
ARGP4
CNSTI4 3
ARGI4
CNSTI4 0
ARGI4
CNSTP4 0
ARGP4
ADDRGP4 Menu_SetFeederSelection
CALLV
pop
LABELV $159
ADDRLP4 0
ADDRGP4 CG_RequestScores
CALLI4
ASGNI4
ADDRLP4 0
INDIRI4
CNSTI4 0
EQI4 $162
ADDRGP4 cg+115300
INDIRI4
CNSTI4 0
NEI4 $163
ADDRGP4 cg_debugRandom+12
INDIRI4
CNSTI4 0
EQI4 $167
ADDRGP4 $170
ARGP4
ADDRGP4 CG_Printf
CALLV
pop
LABELV $167
ADDRGP4 cg+115300
CNSTI4 1
ASGNI4
ADDRGP4 cg+113492
CNSTI4 0
ASGNI4
ADDRGP4 $163
JUMPV
LABELV $162
ADDRGP4 cg+115300
CNSTI4 1
ASGNI4
LABELV $163
LABELV $158
endproc CG_ScoresDown_f 4 16
proc CG_ScoresUp_f 0 0
ADDRGP4 cg+115300
INDIRI4
CNSTI4 0
EQI4 $175
ADDRGP4 cg+115300
CNSTI4 0
ASGNI4
ADDRGP4 cg+115308
ADDRGP4 cg+109556
INDIRI4
ASGNI4
LABELV $175
LABELV $174
endproc CG_ScoresUp_f 0 0
export CG_ClientList_f
proc CG_ClientList_f 20 12
ADDRLP4 8
CNSTI4 0
ASGNI4
ADDRLP4 0
CNSTI4 0
ASGNI4
LABELV $182
ADDRLP4 4
CNSTI4 1508
ADDRLP4 0
INDIRI4
MULI4
ADDRGP4 cgs+41460
ADDP4
ASGNP4
ADDRLP4 4
INDIRP4
INDIRI4
CNSTI4 0
NEI4 $187
ADDRGP4 $183
JUMPV
LABELV $187
ADDRLP4 12
ADDRLP4 4
INDIRP4
CNSTI4 68
ADDP4
INDIRI4
ASGNI4
ADDRLP4 12
INDIRI4
CNSTI4 0
LTI4 $189
ADDRLP4 12
INDIRI4
CNSTI4 3
GTI4 $189
ADDRLP4 12
INDIRI4
CNSTI4 2
LSHI4
ADDRGP4 $198
ADDP4
INDIRP4
JUMPV
lit
align 4
LABELV $198
address $196
address $192
address $194
address $196
code
LABELV $192
ADDRGP4 $193
ARGP4
ADDRLP4 0
INDIRI4
ARGI4
ADDRLP4 4
INDIRP4
CNSTI4 4
ADDP4
ARGP4
ADDRGP4 Com_Printf
CALLV
pop
ADDRGP4 $190
JUMPV
LABELV $194
ADDRGP4 $195
ARGP4
ADDRLP4 0
INDIRI4
ARGI4
ADDRLP4 4
INDIRP4
CNSTI4 4
ADDP4
ARGP4
ADDRGP4 Com_Printf
CALLV
pop
ADDRGP4 $190
JUMPV
LABELV $189
LABELV $196
ADDRGP4 $197
ARGP4
ADDRLP4 0
INDIRI4
ARGI4
ADDRLP4 4
INDIRP4
CNSTI4 4
ADDP4
ARGP4
ADDRGP4 Com_Printf
CALLV
pop
LABELV $190
ADDRLP4 8
ADDRLP4 8
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
LABELV $183
ADDRLP4 0
ADDRLP4 0
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
ADDRLP4 0
INDIRI4
CNSTI4 64
LTI4 $182
ADDRGP4 $199
ARGP4
ADDRLP4 8
INDIRI4
ARGI4
ADDRGP4 Com_Printf
CALLV
pop
LABELV $181
endproc CG_ClientList_f 20 12
proc CG_UIMenu_f 8 8
CNSTI4 1
ARGI4
ADDRLP4 0
ADDRGP4 CG_Argv
CALLP4
ASGNP4
ADDRGP4 $201
ARGP4
ADDRLP4 0
INDIRP4
ARGP4
ADDRLP4 4
ADDRGP4 va
CALLP4
ASGNP4
ADDRLP4 4
INDIRP4
ARGP4
ADDRGP4 trap_SendConsoleCommand
CALLV
pop
LABELV $200
endproc CG_UIMenu_f 8 8
data
align 4
LABELV commands
address $202
address CG_ScoresDown_f
address $203
address CG_ScoresUp_f
address $204
address BG_MemoryInfo
address $205
address CG_ClientList_f
address $206
address CG_DestroyTestPS_f
address $207
address CG_DestroyTestTS_f
address $208
address CG_TestModelNextFrame_f
address $209
address CG_TestModelNextSkin_f
address $210
address CG_TestModelPrevFrame_f
address $211
address CG_TestModelPrevSkin_f
address $212
address CG_scrollScoresDown_f
address $213
address CG_scrollScoresUp_f
address $214
address CG_SizeDown_f
address $215
address CG_SizeUp_f
address $216
address CG_TestGun_f
address $217
address CG_TestModel_f
address $218
address CG_TestPS_f
address $219
address CG_TestTS_f
address $220
address CG_UIMenu_f
address $221
address CG_Viewpos_f
address $222
address CG_NextWeapon_f
address $223
address CG_Weapon_f
address $224
address CG_PrevWeapon_f
export CG_ConsoleCommand
code
proc CG_ConsoleCommand 12 20
CNSTI4 0
ARGI4
ADDRLP4 4
ADDRGP4 CG_Argv
CALLP4
ASGNP4
ADDRLP4 4
INDIRP4
ARGP4
ADDRGP4 commands
ARGP4
CNSTU4 23
ARGU4
CNSTU4 8
ARGU4
ADDRGP4 cmdcmp
ARGP4
ADDRLP4 8
ADDRGP4 bsearch
CALLP4
ASGNP4
ADDRLP4 0
ADDRLP4 8
INDIRP4
ASGNP4
ADDRLP4 0
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $226
CNSTI4 0
RETI4
ADDRGP4 $225
JUMPV
LABELV $226
ADDRLP4 0
INDIRP4
CNSTI4 4
ADDP4
INDIRP4
CALLV
pop
CNSTI4 1
RETI4
LABELV $225
endproc CG_ConsoleCommand 12 20
export CG_InitConsoleCommands
proc CG_InitConsoleCommands 4 4
ADDRLP4 0
CNSTI4 0
ASGNI4
ADDRGP4 $232
JUMPV
LABELV $229
ADDRLP4 0
INDIRI4
CNSTI4 3
LSHI4
ADDRGP4 commands
ADDP4
INDIRP4
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
LABELV $230
ADDRLP4 0
ADDRLP4 0
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
LABELV $232
ADDRLP4 0
INDIRI4
CVIU4 4
CNSTU4 23
LTU4 $229
ADDRGP4 $233
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $234
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $235
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $236
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $237
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $238
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $239
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $240
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $241
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $242
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $243
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $244
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $245
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $246
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $247
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $248
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $249
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $250
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $251
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $252
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $253
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $254
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $255
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $256
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $257
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $258
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $259
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $260
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $261
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $262
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $263
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $264
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $265
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $266
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $267
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
ADDRGP4 $268
ARGP4
ADDRGP4 trap_AddCommand
CALLV
pop
LABELV $228
endproc CG_InitConsoleCommands 4 4
import menuScoreboard
import trap_GetDemoName
import trap_GetDemoPos
import trap_GetDemoState
import trap_GetEntityToken
import trap_getCameraInfo
import trap_startCamera
import trap_loadCamera
import trap_RealTime
import trap_SnapVector
import trap_CIN_SetExtents
import trap_CIN_DrawCinematic
import trap_CIN_RunCinematic
import trap_CIN_StopCinematic
import trap_CIN_PlayCinematic
import trap_Key_GetOverstrikeMode
import trap_Key_SetOverstrikeMode
import trap_Key_SetBinding
import trap_Key_GetBindingBuf
import trap_Key_KeynumToStringBuf
import trap_Key_GetKey
import trap_Key_SetCatcher
import trap_Key_GetCatcher
import trap_Key_IsDown
import trap_R_RegisterFont
import trap_MemoryRemaining
import testPrintFloat
import testPrintInt
import trap_SetUserCmdValue
import trap_GetUserCmd
import trap_GetCurrentCmdNumber
import trap_GetServerCommand
import trap_GetSnapshot
import trap_GetCurrentSnapshotNumber
import trap_GetGameState
import trap_GetGlconfig
import trap_R_RemapShader
import trap_R_LerpTag
import trap_R_ModelBounds
import trap_R_DrawStretchPic
import trap_R_SetColor
import trap_R_RenderScene
import trap_R_LightForPoint
import trap_R_AddAdditiveLightToScene
import trap_R_AddLightToScene
import trap_R_inPVS
import trap_R_AddPolysToScene
import trap_R_AddPolyToScene
import trap_R_AddRefEntityToScene
import trap_R_ClearScene
import trap_R_RegisterShaderNoMip
import trap_R_RegisterShader
import trap_R_RegisterSkin
import trap_R_RegisterModel
import trap_R_LoadWorldMap
import trap_S_StopBackgroundTrack
import trap_S_StartBackgroundTrack
import trap_S_RegisterSound
import trap_S_Respatialize
import trap_S_UpdateEntityPosition
import trap_S_AddRealLoopingSound
import trap_S_AddLoopingSound
import trap_S_ClearLoopingSounds
import trap_S_StartLocalSound
import trap_S_StopLoopingSound
import trap_S_StartSound
import trap_CM_MarkFragments
import trap_CM_TransformedBiSphereTrace
import trap_CM_BiSphereTrace
import trap_CM_TransformedCapsuleTrace
import trap_CM_CapsuleTrace
import trap_CM_TransformedBoxTrace
import trap_CM_BoxTrace
import trap_CM_TransformedPointContents
import trap_CM_PointContents
import trap_CM_TempBoxModel
import trap_CM_InlineModel
import trap_CM_NumInlineModels
import trap_CM_LoadMap
import trap_UpdateScreen
import trap_SendClientCommand
import trap_AddCommand
import trap_SendConsoleCommand
import trap_FS_GetFileList
import trap_FS_Seek
import trap_FS_FCloseFile
import trap_FS_Write
import trap_FS_Read
import trap_FS_FOpenFile
import trap_LiteralArgs
import trap_Args
import trap_Argv
import trap_Argc
import trap_Cvar_VariableStringBuffer
import trap_Cvar_Set
import trap_Cvar_Update
import trap_Cvar_Register
import trap_Milliseconds
import trap_Error
import trap_Print
import CG_TutorialText
import CG_WritePTRCode
import CG_ReadPTRCode
import CG_DestroyTestTS_f
import CG_TestTS_f
import CG_AddTrails
import CG_IsTrailSystemValid
import CG_DestroyTrailSystem
import CG_SpawnNewTrailSystem
import CG_RegisterTrailSystem
import CG_LoadTrailSystems
import CG_DestroyTestPS_f
import CG_TestPS_f
import CG_ParticleSystemEntity
import CG_AddParticles
import CG_SetParticleSystemNormal
import CG_IsParticleSystemValid
import CG_IsParticleSystemInfinite
import CG_DestroyParticleSystem
import CG_SpawnNewParticleSystem
import CG_RegisterParticleSystem
import CG_LoadParticleSystems
import CG_SetAttachmentOffset
import CG_SetAttachmentParticle
import CG_SetAttachmentTag
import CG_SetAttachmentCent
import CG_SetAttachmentPoint
import CG_AttachToParticle
import CG_AttachToTag
import CG_AttachToCent
import CG_AttachToPoint
import CG_Attached
import CG_AttachmentCentNum
import CG_AttachmentVelocity
import CG_AttachmentAxis
import CG_AttachmentDir
import CG_AttachmentPoint
import CG_CheckChangedPredictableEvents
import CG_TransitionPlayerState
import CG_Respawn
import CG_ShaderStateChanged
import CG_SetConfigValues
import CG_ParseServerinfo
import CG_ExecuteNewServerCommands
import CG_ProcessSnapshots
import CG_ImpactMark
import CG_AddMarks
import CG_InitMarkPolys
import CG_AlienSense
import CG_Scanner
import CG_UpdateEntityPositions
import CG_DrawItemSelectText
import CG_DrawItemSelect
import CG_AddPlayerWeapon
import CG_AddViewWeapon
import CG_ShotgunFire
import CG_Bullet
import CG_MissileHitEntity
import CG_MissileHitWall
import CG_FireWeapon
import CG_RegisterWeapon
import CG_InitWeapons
import CG_RegisterUpgrade
import CG_InitUpgrades
import CG_Weapon_f
import CG_PrevWeapon_f
import CG_NextWeapon_f
import CG_PositionRotatedEntityOnTag
import CG_PositionEntityOnTag
import CG_AdjustPositionForMover
import CG_Beam
import CG_AddPacketEntities
import CG_SetEntitySoundPosition
import CG_DrawBoundingBox
import CG_PainEvent
import CG_EntityEvent
import CG_CheckEvents
import CG_PredictPlayerState
import CG_BiSphereTrace
import CG_CapTrace
import CG_Trace
import CG_PointContents
import CG_BuildSolidList
import CG_ModelDoor
import CG_AnimMapObj
import CG_RunLerpFrame
import CG_AlienBuildableExplosion
import CG_HumanBuildableExplosion
import CG_InitBuildables
import CG_DrawBuildableStatus
import CG_BuildableStatusParse
import CG_Buildable
import CG_GhostBuildable
import CG_GetPlayerLocation
import CG_Bleed
import CG_PlayerDisconnect
import CG_CustomSound
import CG_PrecacheClientInfo
import CG_NewClientInfo
import CG_ResetPlayerEntity
import CG_Corpse
import CG_Player
import CG_DrawField
import CG_ResetPainBlend
import CG_UpdateMediaFraction
import CG_DrawLoadingScreen
import CG_Text_PaintChar
import CG_GetKillerText
import CG_GetTeamColor
import CG_SetPrintString
import CG_RunMenuScript
import CG_GetValue
import CG_OwnerDraw
import CG_DrawActive
import CG_CenterPrint
import CG_AddSpeed
import CG_AddLagometerSnapshotInfo
import CG_AddLagometerFrameInfo
import CG_GetColorCharForHealth
import CG_KeyBinding
import CG_WorldToScreen
import CG_DrawTopBottom
import CG_DrawSides
import CG_DrawRect
import CG_ColorForHealth
import CG_TileClear
import CG_FadeColor
import CG_DrawStrlen
import CG_ClearClipRegion
import CG_SetClipRegion
import CG_DrawFadePic
import CG_DrawPic
import CG_FillRect
import CG_AdjustFrom640
import CG_DrawPlane
import CG_OffsetShoulderView
import CG_OffsetThirdPersonView
import CG_OffsetFirstPersonView
import CG_DrawActiveFrame
import CG_AddBufferedSound
import CG_TestModelPrevSkin_f
import CG_TestModelNextSkin_f
import CG_TestModelPrevFrame_f
import CG_TestModelNextFrame_f
import CG_TestGun_f
import CG_TestModel_f
import CG_addSmoothOp
import CG_AddNotifyText
import CG_RemoveNotifyLine
import CG_FileExists
import CG_BuildSpectatorString
import CG_ClientIsReady
import CG_SetScoreSelection
import CG_EventHandling
import CG_MouseEvent
import CG_KeyEvent
import CG_LoadMenus
import CG_LastAttacker
import CG_CrosshairPlayer
import CG_UpdateCvars
import CG_PlayerCount
import CG_StartMusic
import CG_Error
import CG_Printf
import CG_Argv
import CG_ConfigString
import cg_chatTeamPrefix
import cg_emoticons
import cg_voice
import cg_projectileNudge
import cg_optimizePrediction
import cg_debugRandom
import ui_humanTeamVoteActive
import ui_alienTeamVoteActive
import ui_voteActive
import ui_dialog
import ui_stages
import ui_carriage
import ui_currentClass
import cg_debugVoices
import cg_unlagged
import cg_sprintToggle
import cg_stickySpec
import cg_painBlendZoom
import cg_painBlendScale
import cg_painBlendMax
import cg_painBlendDownRate
import cg_painBlendUpRate
import cg_tutorial
import cg_disableScannerPlane
import cg_disableCommandDialogs
import cg_disableBuildDialogs
import cg_disableUpgradeDialogs
import cg_disableWarningDialogs
import cg_debugPVS
import cg_debugTrails
import cg_debugParticles
import cg_lightFlare
import cg_consoleLatency
import cg_bounceParticles
import cg_depthSortParticles
import cg_disableBlueprintErrors
import cg_wwSmoothTime
import cg_drawBBOX
import cg_drawSurfNormal
import cg_noTaunt
import cg_timescale
import cg_timescaleFadeSpeed
import cg_timescaleFadeEnd
import cg_cameraMode
import pmove_msec
import pmove_fixed
import cg_smoothClients
import cg_hudFiles
import cg_noVoiceText
import cg_noVoiceChats
import cg_teamChatsOnly
import cg_blood
import cg_paused
import cg_stats
import cg_synchronousClients
import cg_drawSpeed
import cg_lagometer
import cg_stereoSeparation
import cg_thirdPersonRange
import cg_thirdPersonPitchFollow
import cg_staticDeathCam
import cg_thirdPersonShoulderViewMode
import cg_thirdPersonAngle
import cg_thirdPerson
import cg_tracerLength
import cg_tracerWidth
import cg_tracerChance
import cg_gun_z
import cg_gun_y
import cg_gun_x
import cg_gun_frame
import cg_drawGun
import cg_viewsize
import cg_addMarks
import cg_footsteps
import cg_showmiss
import cg_noPlayerAnims
import cg_debugMove
import cg_nopredict
import cg_errorDecay
import cg_debugEvents
import cg_debugPosition
import cg_debugAnim
import cg_animSpeed
import cg_draw2D
import cg_teamOverlayUserinfo
import cg_teamOverlayMaxPlayers
import cg_teamOverlaySortMode
import cg_drawTeamOverlay
import cg_crosshairSize
import cg_drawCrosshairNames
import cg_drawCrosshair
import cg_drawChargeBar
import cg_drawSnapshot
import cg_drawDemoState
import cg_drawFPS
import cg_drawClock
import cg_drawTimer
import cg_shadows
import cg_swingSpeed
import cg_runroll
import cg_runpitch
import cg_centertime
import cg_teslaTrailTime
import cg_markPolys
import cg_buildables
import cg_upgrades
import cg_weapons
import cgDC
import cg_entities
import cg
import cgs
import g_nameBind2
import g_nameBind1
import BindingFromName
import trap_Parse_SourceFileAndLine
import trap_Parse_ReadToken
import trap_Parse_FreeSource
import trap_Parse_LoadSource
import trap_Parse_AddGlobalDefine
import UI_EscapeEmoticons
import UI_Text_IsEmoticon
import UI_Text_EmHeight
import UI_Text_EmWidth
import UI_Text_Height
import UI_Text_Width
import UI_Text_Paint_Limit
import UI_Text_Paint
import UI_DrawTextBlock
import Item_Text_Wrap
import Item_Text_Wrapped_Paint
import trap_R_SetClipRegion
import Controls_SetDefaults
import Controls_SetConfig
import Controls_GetConfig
import UI_OutOfMemory
import UI_InitMemory
import UI_Alloc
import UI_RemoveCaptureFunc
import UI_InstallCaptureFunc
import Display_CacheAll
import Menu_SetFeederSelection
import Menu_Paint
import Menu_Update
import Menus_CloseAll
import LerpColor
import Display_HandleKey
import Menus_CloseByName
import Menus_FindByName
import Display_KeyBindPending
import Display_CursorType
import Display_MouseMove
import Display_CaptureItem
import Display_GetContext
import Menus_ReplaceActive
import Menus_Activate
import Menus_AnyFullScreenVisible
import Menu_Reset
import Menus_ReplaceActiveByName
import Menus_ActivateByName
import Menu_PaintAll
import Menu_UpdateAll
import Menu_New
import Menu_Count
import PC_Script_Parse
import PC_String_Parse
import PC_Rect_Parse
import PC_Int_Parse
import PC_Color_Parse
import PC_Float_Parse
import Script_Parse
import String_Parse
import Rect_Parse
import Int_Parse
import Color_Parse
import Float_Parse
import Menu_ScrollFeeder
import Menu_HandleMouseMove
import Menu_HandleKey
import Menu_GetFocused
import Menu_PostParse
import Item_Init
import Menu_Init
import Display_ExpandMacros
import Init_Display
import String_Report
import String_Init
import String_Alloc
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
LABELV $268
byte 1 117
byte 1 110
byte 1 105
byte 1 103
byte 1 110
byte 1 111
byte 1 114
byte 1 101
byte 1 0
align 1
LABELV $267
byte 1 105
byte 1 103
byte 1 110
byte 1 111
byte 1 114
byte 1 101
byte 1 0
align 1
LABELV $266
byte 1 100
byte 1 101
byte 1 99
byte 1 111
byte 1 110
byte 1 115
byte 1 116
byte 1 114
byte 1 117
byte 1 99
byte 1 116
byte 1 0
align 1
LABELV $265
byte 1 100
byte 1 101
byte 1 115
byte 1 116
byte 1 114
byte 1 111
byte 1 121
byte 1 0
align 1
LABELV $264
byte 1 105
byte 1 116
byte 1 101
byte 1 109
byte 1 116
byte 1 111
byte 1 103
byte 1 103
byte 1 108
byte 1 101
byte 1 0
align 1
LABELV $263
byte 1 105
byte 1 116
byte 1 101
byte 1 109
byte 1 100
byte 1 101
byte 1 97
byte 1 99
byte 1 116
byte 1 0
align 1
LABELV $262
byte 1 105
byte 1 116
byte 1 101
byte 1 109
byte 1 97
byte 1 99
byte 1 116
byte 1 0
align 1
LABELV $261
byte 1 114
byte 1 101
byte 1 108
byte 1 111
byte 1 97
byte 1 100
byte 1 0
align 1
LABELV $260
byte 1 115
byte 1 101
byte 1 108
byte 1 108
byte 1 0
align 1
LABELV $259
byte 1 98
byte 1 117
byte 1 121
byte 1 0
align 1
LABELV $258
byte 1 98
byte 1 117
byte 1 105
byte 1 108
byte 1 100
byte 1 0
align 1
LABELV $257
byte 1 99
byte 1 108
byte 1 97
byte 1 115
byte 1 115
byte 1 0
align 1
LABELV $256
byte 1 116
byte 1 101
byte 1 97
byte 1 109
byte 1 118
byte 1 111
byte 1 116
byte 1 101
byte 1 0
align 1
LABELV $255
byte 1 99
byte 1 97
byte 1 108
byte 1 108
byte 1 116
byte 1 101
byte 1 97
byte 1 109
byte 1 118
byte 1 111
byte 1 116
byte 1 101
byte 1 0
align 1
LABELV $254
byte 1 118
byte 1 111
byte 1 116
byte 1 101
byte 1 0
align 1
LABELV $253
byte 1 99
byte 1 97
byte 1 108
byte 1 108
byte 1 118
byte 1 111
byte 1 116
byte 1 101
byte 1 0
align 1
LABELV $252
byte 1 115
byte 1 101
byte 1 116
byte 1 118
byte 1 105
byte 1 101
byte 1 119
byte 1 112
byte 1 111
byte 1 115
byte 1 0
align 1
LABELV $251
byte 1 108
byte 1 101
byte 1 118
byte 1 101
byte 1 108
byte 1 115
byte 1 104
byte 1 111
byte 1 116
byte 1 0
align 1
LABELV $250
byte 1 102
byte 1 111
byte 1 108
byte 1 108
byte 1 111
byte 1 119
byte 1 0
align 1
LABELV $249
byte 1 116
byte 1 101
byte 1 97
byte 1 109
byte 1 0
align 1
LABELV $248
byte 1 110
byte 1 111
byte 1 99
byte 1 108
byte 1 105
byte 1 112
byte 1 0
align 1
LABELV $247
byte 1 110
byte 1 111
byte 1 116
byte 1 97
byte 1 114
byte 1 103
byte 1 101
byte 1 116
byte 1 0
align 1
LABELV $246
byte 1 103
byte 1 111
byte 1 100
byte 1 0
align 1
LABELV $245
byte 1 103
byte 1 105
byte 1 118
byte 1 101
byte 1 0
align 1
LABELV $244
byte 1 109
byte 1 116
byte 1 0
align 1
LABELV $243
byte 1 109
byte 1 0
align 1
LABELV $242
byte 1 118
byte 1 115
byte 1 97
byte 1 121
byte 1 95
byte 1 108
byte 1 111
byte 1 99
byte 1 97
byte 1 108
byte 1 0
align 1
LABELV $241
byte 1 118
byte 1 115
byte 1 97
byte 1 121
byte 1 95
byte 1 116
byte 1 101
byte 1 97
byte 1 109
byte 1 0
align 1
LABELV $240
byte 1 118
byte 1 115
byte 1 97
byte 1 121
byte 1 0
align 1
LABELV $239
byte 1 115
byte 1 97
byte 1 121
byte 1 95
byte 1 116
byte 1 101
byte 1 97
byte 1 109
byte 1 0
align 1
LABELV $238
byte 1 115
byte 1 97
byte 1 121
byte 1 0
align 1
LABELV $237
byte 1 117
byte 1 105
byte 1 95
byte 1 109
byte 1 101
byte 1 115
byte 1 115
byte 1 97
byte 1 103
byte 1 101
byte 1 109
byte 1 111
byte 1 100
byte 1 101
byte 1 52
byte 1 0
align 1
LABELV $236
byte 1 117
byte 1 105
byte 1 95
byte 1 109
byte 1 101
byte 1 115
byte 1 115
byte 1 97
byte 1 103
byte 1 101
byte 1 109
byte 1 111
byte 1 100
byte 1 101
byte 1 51
byte 1 0
align 1
LABELV $235
byte 1 117
byte 1 105
byte 1 95
byte 1 109
byte 1 101
byte 1 115
byte 1 115
byte 1 97
byte 1 103
byte 1 101
byte 1 109
byte 1 111
byte 1 100
byte 1 101
byte 1 50
byte 1 0
align 1
LABELV $234
byte 1 117
byte 1 105
byte 1 95
byte 1 109
byte 1 101
byte 1 115
byte 1 115
byte 1 97
byte 1 103
byte 1 101
byte 1 109
byte 1 111
byte 1 100
byte 1 101
byte 1 0
align 1
LABELV $233
byte 1 107
byte 1 105
byte 1 108
byte 1 108
byte 1 0
align 1
LABELV $224
byte 1 119
byte 1 101
byte 1 97
byte 1 112
byte 1 112
byte 1 114
byte 1 101
byte 1 118
byte 1 0
align 1
LABELV $223
byte 1 119
byte 1 101
byte 1 97
byte 1 112
byte 1 111
byte 1 110
byte 1 0
align 1
LABELV $222
byte 1 119
byte 1 101
byte 1 97
byte 1 112
byte 1 110
byte 1 101
byte 1 120
byte 1 116
byte 1 0
align 1
LABELV $221
byte 1 118
byte 1 105
byte 1 101
byte 1 119
byte 1 112
byte 1 111
byte 1 115
byte 1 0
align 1
LABELV $220
byte 1 117
byte 1 105
byte 1 95
byte 1 109
byte 1 101
byte 1 110
byte 1 117
byte 1 0
align 1
LABELV $219
byte 1 116
byte 1 101
byte 1 115
byte 1 116
byte 1 84
byte 1 83
byte 1 0
align 1
LABELV $218
byte 1 116
byte 1 101
byte 1 115
byte 1 116
byte 1 80
byte 1 83
byte 1 0
align 1
LABELV $217
byte 1 116
byte 1 101
byte 1 115
byte 1 116
byte 1 109
byte 1 111
byte 1 100
byte 1 101
byte 1 108
byte 1 0
align 1
LABELV $216
byte 1 116
byte 1 101
byte 1 115
byte 1 116
byte 1 103
byte 1 117
byte 1 110
byte 1 0
align 1
LABELV $215
byte 1 115
byte 1 105
byte 1 122
byte 1 101
byte 1 117
byte 1 112
byte 1 0
align 1
LABELV $214
byte 1 115
byte 1 105
byte 1 122
byte 1 101
byte 1 100
byte 1 111
byte 1 119
byte 1 110
byte 1 0
align 1
LABELV $213
byte 1 115
byte 1 99
byte 1 111
byte 1 114
byte 1 101
byte 1 115
byte 1 85
byte 1 112
byte 1 0
align 1
LABELV $212
byte 1 115
byte 1 99
byte 1 111
byte 1 114
byte 1 101
byte 1 115
byte 1 68
byte 1 111
byte 1 119
byte 1 110
byte 1 0
align 1
LABELV $211
byte 1 112
byte 1 114
byte 1 101
byte 1 118
byte 1 115
byte 1 107
byte 1 105
byte 1 110
byte 1 0
align 1
LABELV $210
byte 1 112
byte 1 114
byte 1 101
byte 1 118
byte 1 102
byte 1 114
byte 1 97
byte 1 109
byte 1 101
byte 1 0
align 1
LABELV $209
byte 1 110
byte 1 101
byte 1 120
byte 1 116
byte 1 115
byte 1 107
byte 1 105
byte 1 110
byte 1 0
align 1
LABELV $208
byte 1 110
byte 1 101
byte 1 120
byte 1 116
byte 1 102
byte 1 114
byte 1 97
byte 1 109
byte 1 101
byte 1 0
align 1
LABELV $207
byte 1 100
byte 1 101
byte 1 115
byte 1 116
byte 1 114
byte 1 111
byte 1 121
byte 1 84
byte 1 101
byte 1 115
byte 1 116
byte 1 84
byte 1 83
byte 1 0
align 1
LABELV $206
byte 1 100
byte 1 101
byte 1 115
byte 1 116
byte 1 114
byte 1 111
byte 1 121
byte 1 84
byte 1 101
byte 1 115
byte 1 116
byte 1 80
byte 1 83
byte 1 0
align 1
LABELV $205
byte 1 99
byte 1 108
byte 1 105
byte 1 101
byte 1 110
byte 1 116
byte 1 108
byte 1 105
byte 1 115
byte 1 116
byte 1 0
align 1
LABELV $204
byte 1 99
byte 1 103
byte 1 97
byte 1 109
byte 1 101
byte 1 95
byte 1 109
byte 1 101
byte 1 109
byte 1 111
byte 1 114
byte 1 121
byte 1 0
align 1
LABELV $203
byte 1 45
byte 1 115
byte 1 99
byte 1 111
byte 1 114
byte 1 101
byte 1 115
byte 1 0
align 1
LABELV $202
byte 1 43
byte 1 115
byte 1 99
byte 1 111
byte 1 114
byte 1 101
byte 1 115
byte 1 0
align 1
LABELV $201
byte 1 109
byte 1 101
byte 1 110
byte 1 117
byte 1 32
byte 1 37
byte 1 115
byte 1 10
byte 1 0
align 1
LABELV $199
byte 1 76
byte 1 105
byte 1 115
byte 1 116
byte 1 101
byte 1 100
byte 1 32
byte 1 37
byte 1 50
byte 1 100
byte 1 32
byte 1 99
byte 1 108
byte 1 105
byte 1 101
byte 1 110
byte 1 116
byte 1 115
byte 1 10
byte 1 0
align 1
LABELV $197
byte 1 37
byte 1 50
byte 1 100
byte 1 32
byte 1 83
byte 1 32
byte 1 32
byte 1 32
byte 1 37
byte 1 115
byte 1 10
byte 1 0
align 1
LABELV $195
byte 1 37
byte 1 50
byte 1 100
byte 1 32
byte 1 94
byte 1 53
byte 1 72
byte 1 32
byte 1 32
byte 1 32
byte 1 94
byte 1 55
byte 1 37
byte 1 115
byte 1 10
byte 1 0
align 1
LABELV $193
byte 1 37
byte 1 50
byte 1 100
byte 1 32
byte 1 94
byte 1 49
byte 1 65
byte 1 32
byte 1 32
byte 1 32
byte 1 94
byte 1 55
byte 1 37
byte 1 115
byte 1 10
byte 1 0
align 1
LABELV $170
byte 1 67
byte 1 71
byte 1 95
byte 1 83
byte 1 99
byte 1 111
byte 1 114
byte 1 101
byte 1 115
byte 1 68
byte 1 111
byte 1 119
byte 1 110
byte 1 95
byte 1 102
byte 1 58
byte 1 32
byte 1 115
byte 1 99
byte 1 111
byte 1 114
byte 1 101
byte 1 115
byte 1 32
byte 1 111
byte 1 117
byte 1 116
byte 1 32
byte 1 111
byte 1 102
byte 1 32
byte 1 100
byte 1 97
byte 1 116
byte 1 101
byte 1 10
byte 1 0
align 1
LABELV $149
byte 1 115
byte 1 99
byte 1 111
byte 1 114
byte 1 101
byte 1 10
byte 1 0
align 1
LABELV $131
byte 1 40
byte 1 37
byte 1 105
byte 1 32
byte 1 37
byte 1 105
byte 1 32
byte 1 37
byte 1 105
byte 1 41
byte 1 32
byte 1 58
byte 1 32
byte 1 37
byte 1 105
byte 1 10
byte 1 0
align 1
LABELV $118
byte 1 37
byte 1 105
byte 1 0
align 1
LABELV $117
byte 1 99
byte 1 103
byte 1 95
byte 1 118
byte 1 105
byte 1 101
byte 1 119
byte 1 115
byte 1 105
byte 1 122
byte 1 101
byte 1 0
