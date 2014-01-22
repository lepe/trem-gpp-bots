export CG_AttachmentPoint
code
proc CG_AttachmentPoint 24 16
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 4
ADDRFP4 4
INDIRP4
ASGNP4
ADDRFP4 0
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $117
CNSTI4 0
RETI4
ADDRGP4 $116
JUMPV
LABELV $117
ADDRFP4 4
INDIRP4
ADDRFP4 0
INDIRP4
CNSTI4 40
ADDP4
INDIRB
ASGNB 12
ADDRLP4 4
ADDRFP4 0
INDIRP4
INDIRI4
ASGNI4
ADDRLP4 4
INDIRI4
CNSTI4 0
LTI4 $119
ADDRLP4 4
INDIRI4
CNSTI4 3
GTI4 $119
ADDRLP4 4
INDIRI4
CNSTI4 2
LSHI4
ADDRGP4 $143
ADDP4
INDIRP4
JUMPV
lit
align 4
LABELV $143
address $122
address $125
address $128
address $137
code
LABELV $122
ADDRFP4 0
INDIRP4
CNSTI4 8
ADDP4
INDIRI4
CNSTI4 0
NEI4 $123
CNSTI4 0
RETI4
ADDRGP4 $116
JUMPV
LABELV $123
ADDRFP4 4
INDIRP4
ADDRFP4 0
INDIRP4
CNSTI4 52
ADDP4
INDIRB
ASGNB 12
ADDRGP4 $120
JUMPV
LABELV $125
ADDRFP4 0
INDIRP4
CNSTI4 12
ADDP4
INDIRI4
CNSTI4 0
NEI4 $126
CNSTI4 0
RETI4
ADDRGP4 $116
JUMPV
LABELV $126
ADDRGP4 axisDefault
ARGP4
ADDRFP4 0
INDIRP4
CNSTI4 92
ADDP4
ARGP4
ADDRGP4 AxisCopy
CALLV
pop
ADDRFP4 0
INDIRP4
CNSTI4 64
ADDP4
ARGP4
ADDRFP4 0
INDIRP4
CNSTI4 204
ADDP4
ARGP4
ADDRFP4 0
INDIRP4
CNSTI4 344
ADDP4
INDIRI4
ARGI4
ADDRFP4 0
INDIRP4
CNSTI4 348
ADDP4
ARGP4
ADDRGP4 CG_PositionRotatedEntityOnTag
CALLV
pop
ADDRFP4 4
INDIRP4
ADDRFP4 0
INDIRP4
CNSTI4 132
ADDP4
INDIRB
ASGNB 12
ADDRGP4 $120
JUMPV
LABELV $128
ADDRFP4 0
INDIRP4
CNSTI4 16
ADDP4
INDIRI4
CNSTI4 0
NEI4 $129
CNSTI4 0
RETI4
ADDRGP4 $116
JUMPV
LABELV $129
ADDRFP4 0
INDIRP4
CNSTI4 1372
ADDP4
INDIRI4
ADDRGP4 cg+109588+148
INDIRI4
NEI4 $131
ADDRFP4 4
INDIRP4
ADDRGP4 cg+109588+20
INDIRB
ASGNB 12
ADDRGP4 $120
JUMPV
LABELV $131
ADDRLP4 0
CNSTI4 1844
ADDRFP4 0
INDIRP4
CNSTI4 1372
ADDP4
INDIRI4
MULI4
ADDRGP4 cg_entities
ADDP4
ASGNP4
ADDRFP4 4
INDIRP4
ADDRLP4 0
INDIRP4
CNSTI4 1564
ADDP4
INDIRB
ASGNB 12
ADDRGP4 $120
JUMPV
LABELV $137
ADDRFP4 0
INDIRP4
CNSTI4 20
ADDP4
INDIRI4
CNSTI4 0
NEI4 $138
CNSTI4 0
RETI4
ADDRGP4 $116
JUMPV
LABELV $138
ADDRFP4 0
INDIRP4
CNSTI4 1376
ADDP4
INDIRP4
CNSTI4 324
ADDP4
INDIRI4
CNSTI4 0
NEI4 $140
ADDRFP4 0
INDIRP4
CNSTI4 20
ADDP4
CNSTI4 0
ASGNI4
CNSTI4 0
RETI4
ADDRGP4 $116
JUMPV
LABELV $140
ADDRFP4 4
INDIRP4
ADDRFP4 0
INDIRP4
CNSTI4 1376
ADDP4
INDIRP4
CNSTI4 32
ADDP4
INDIRB
ASGNB 12
ADDRGP4 $120
JUMPV
LABELV $119
ADDRGP4 $142
ARGP4
ADDRGP4 CG_Printf
CALLV
pop
LABELV $120
ADDRFP4 0
INDIRP4
CNSTI4 24
ADDP4
INDIRI4
CNSTI4 0
EQI4 $144
ADDRFP4 4
INDIRP4
ADDRFP4 4
INDIRP4
INDIRF4
ADDRFP4 0
INDIRP4
CNSTI4 28
ADDP4
INDIRF4
ADDF4
ASGNF4
ADDRLP4 16
ADDRFP4 4
INDIRP4
CNSTI4 4
ADDP4
ASGNP4
ADDRLP4 16
INDIRP4
ADDRLP4 16
INDIRP4
INDIRF4
ADDRFP4 0
INDIRP4
CNSTI4 32
ADDP4
INDIRF4
ADDF4
ASGNF4
ADDRLP4 20
ADDRFP4 4
INDIRP4
CNSTI4 8
ADDP4
ASGNP4
ADDRLP4 20
INDIRP4
ADDRLP4 20
INDIRP4
INDIRF4
ADDRFP4 0
INDIRP4
CNSTI4 36
ADDP4
INDIRF4
ADDF4
ASGNF4
LABELV $144
ADDRFP4 0
INDIRP4
CNSTI4 40
ADDP4
ADDRFP4 4
INDIRP4
INDIRB
ASGNB 12
CNSTI4 1
RETI4
LABELV $116
endproc CG_AttachmentPoint 24 16
export CG_AttachmentDir
proc CG_AttachmentDir 28 16
ADDRFP4 0
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $147
CNSTI4 0
RETI4
ADDRGP4 $146
JUMPV
LABELV $147
ADDRLP4 16
ADDRFP4 0
INDIRP4
INDIRI4
ASGNI4
ADDRLP4 16
INDIRI4
CNSTI4 0
LTI4 $149
ADDRLP4 16
INDIRI4
CNSTI4 3
GTI4 $149
ADDRLP4 16
INDIRI4
CNSTI4 2
LSHI4
ADDRGP4 $164
ADDP4
INDIRP4
JUMPV
lit
align 4
LABELV $164
address $152
address $153
address $156
address $159
code
LABELV $152
CNSTI4 0
RETI4
ADDRGP4 $146
JUMPV
LABELV $153
ADDRFP4 0
INDIRP4
CNSTI4 12
ADDP4
INDIRI4
CNSTI4 0
NEI4 $154
CNSTI4 0
RETI4
ADDRGP4 $146
JUMPV
LABELV $154
ADDRFP4 4
INDIRP4
ADDRFP4 0
INDIRP4
CNSTI4 92
ADDP4
INDIRB
ASGNB 12
ADDRGP4 $150
JUMPV
LABELV $156
ADDRFP4 0
INDIRP4
CNSTI4 16
ADDP4
INDIRI4
CNSTI4 0
NEI4 $157
CNSTI4 0
RETI4
ADDRGP4 $146
JUMPV
LABELV $157
ADDRLP4 12
CNSTI4 1844
ADDRFP4 0
INDIRP4
CNSTI4 1372
ADDP4
INDIRI4
MULI4
ADDRGP4 cg_entities
ADDP4
ASGNP4
ADDRLP4 12
INDIRP4
CNSTI4 1576
ADDP4
ARGP4
ADDRLP4 0
ARGP4
ADDRLP4 24
CNSTP4 0
ASGNP4
ADDRLP4 24
INDIRP4
ARGP4
ADDRLP4 24
INDIRP4
ARGP4
ADDRGP4 AngleVectors
CALLV
pop
ADDRFP4 4
INDIRP4
ADDRLP4 0
INDIRB
ASGNB 12
ADDRGP4 $150
JUMPV
LABELV $159
ADDRFP4 0
INDIRP4
CNSTI4 20
ADDP4
INDIRI4
CNSTI4 0
NEI4 $160
CNSTI4 0
RETI4
ADDRGP4 $146
JUMPV
LABELV $160
ADDRFP4 0
INDIRP4
CNSTI4 1376
ADDP4
INDIRP4
CNSTI4 324
ADDP4
INDIRI4
CNSTI4 0
NEI4 $162
ADDRFP4 0
INDIRP4
CNSTI4 20
ADDP4
CNSTI4 0
ASGNI4
CNSTI4 0
RETI4
ADDRGP4 $146
JUMPV
LABELV $162
ADDRFP4 4
INDIRP4
ADDRFP4 0
INDIRP4
CNSTI4 1376
ADDP4
INDIRP4
CNSTI4 44
ADDP4
INDIRB
ASGNB 12
ADDRGP4 $150
JUMPV
LABELV $149
ADDRGP4 $142
ARGP4
ADDRGP4 CG_Printf
CALLV
pop
LABELV $150
ADDRFP4 4
INDIRP4
ARGP4
ADDRGP4 VectorNormalize
CALLF4
pop
CNSTI4 1
RETI4
LABELV $146
endproc CG_AttachmentDir 28 16
export CG_AttachmentAxis
proc CG_AttachmentAxis 12 8
ADDRFP4 0
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $166
CNSTI4 0
RETI4
ADDRGP4 $165
JUMPV
LABELV $166
ADDRLP4 4
ADDRFP4 0
INDIRP4
INDIRI4
ASGNI4
ADDRLP4 4
INDIRI4
CNSTI4 0
LTI4 $168
ADDRLP4 4
INDIRI4
CNSTI4 3
GTI4 $168
ADDRLP4 4
INDIRI4
CNSTI4 2
LSHI4
ADDRGP4 $179
ADDP4
INDIRP4
JUMPV
lit
align 4
LABELV $179
address $171
address $172
address $175
address $178
code
LABELV $171
CNSTI4 0
RETI4
ADDRGP4 $165
JUMPV
LABELV $172
ADDRFP4 0
INDIRP4
CNSTI4 12
ADDP4
INDIRI4
CNSTI4 0
NEI4 $173
CNSTI4 0
RETI4
ADDRGP4 $165
JUMPV
LABELV $173
ADDRFP4 0
INDIRP4
CNSTI4 92
ADDP4
ARGP4
ADDRFP4 4
INDIRP4
ARGP4
ADDRGP4 AxisCopy
CALLV
pop
ADDRGP4 $169
JUMPV
LABELV $175
ADDRFP4 0
INDIRP4
CNSTI4 16
ADDP4
INDIRI4
CNSTI4 0
NEI4 $176
CNSTI4 0
RETI4
ADDRGP4 $165
JUMPV
LABELV $176
ADDRLP4 0
CNSTI4 1844
ADDRFP4 0
INDIRP4
CNSTI4 1372
ADDP4
INDIRI4
MULI4
ADDRGP4 cg_entities
ADDP4
ASGNP4
ADDRLP4 0
INDIRP4
CNSTI4 1576
ADDP4
ARGP4
ADDRFP4 4
INDIRP4
ARGP4
ADDRGP4 AnglesToAxis
CALLV
pop
ADDRGP4 $169
JUMPV
LABELV $178
CNSTI4 0
RETI4
ADDRGP4 $165
JUMPV
LABELV $168
ADDRGP4 $142
ARGP4
ADDRGP4 CG_Printf
CALLV
pop
LABELV $169
CNSTI4 1
RETI4
LABELV $165
endproc CG_AttachmentAxis 12 8
export CG_AttachmentVelocity
proc CG_AttachmentVelocity 12 0
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 0
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $181
CNSTI4 0
RETI4
ADDRGP4 $180
JUMPV
LABELV $181
ADDRLP4 4
CNSTI4 0
ASGNI4
ADDRFP4 0
INDIRP4
CNSTI4 20
ADDP4
INDIRI4
ADDRLP4 4
INDIRI4
EQI4 $183
ADDRFP4 0
INDIRP4
CNSTI4 1376
ADDP4
INDIRP4
CNSTI4 324
ADDP4
INDIRI4
ADDRLP4 4
INDIRI4
EQI4 $183
ADDRFP4 4
INDIRP4
ADDRFP4 0
INDIRP4
CNSTI4 1376
ADDP4
INDIRP4
CNSTI4 44
ADDP4
INDIRB
ASGNB 12
CNSTI4 1
RETI4
ADDRGP4 $180
JUMPV
LABELV $183
ADDRFP4 0
INDIRP4
CNSTI4 16
ADDP4
INDIRI4
CNSTI4 0
EQI4 $185
ADDRLP4 8
CNSTI4 1844
ADDRFP4 0
INDIRP4
CNSTI4 1372
ADDP4
INDIRI4
MULI4
ADDRGP4 cg_entities
ADDP4
ASGNP4
ADDRFP4 4
INDIRP4
ADDRLP4 8
INDIRP4
CNSTI4 36
ADDP4
INDIRB
ASGNB 12
CNSTI4 1
RETI4
ADDRGP4 $180
JUMPV
LABELV $185
CNSTI4 0
RETI4
LABELV $180
endproc CG_AttachmentVelocity 12 0
export CG_AttachmentCentNum
proc CG_AttachmentCentNum 4 0
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 0
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $190
ADDRFP4 0
INDIRP4
CNSTI4 16
ADDP4
INDIRI4
CNSTI4 0
NEI4 $188
LABELV $190
CNSTI4 -1
RETI4
ADDRGP4 $187
JUMPV
LABELV $188
ADDRFP4 0
INDIRP4
CNSTI4 1372
ADDP4
INDIRI4
RETI4
LABELV $187
endproc CG_AttachmentCentNum 4 0
export CG_Attached
proc CG_Attached 0 0
ADDRFP4 0
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $192
CNSTI4 0
RETI4
ADDRGP4 $191
JUMPV
LABELV $192
ADDRFP4 0
INDIRP4
CNSTI4 4
ADDP4
INDIRI4
RETI4
LABELV $191
endproc CG_Attached 0 0
export CG_AttachToPoint
proc CG_AttachToPoint 4 0
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 0
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $197
ADDRFP4 0
INDIRP4
CNSTI4 8
ADDP4
INDIRI4
CNSTI4 0
NEI4 $195
LABELV $197
ADDRGP4 $194
JUMPV
LABELV $195
ADDRFP4 0
INDIRP4
CNSTI4 0
ASGNI4
ADDRFP4 0
INDIRP4
CNSTI4 4
ADDP4
CNSTI4 1
ASGNI4
LABELV $194
endproc CG_AttachToPoint 4 0
export CG_AttachToCent
proc CG_AttachToCent 4 0
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 0
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $201
ADDRFP4 0
INDIRP4
CNSTI4 16
ADDP4
INDIRI4
CNSTI4 0
NEI4 $199
LABELV $201
ADDRGP4 $198
JUMPV
LABELV $199
ADDRFP4 0
INDIRP4
CNSTI4 2
ASGNI4
ADDRFP4 0
INDIRP4
CNSTI4 4
ADDP4
CNSTI4 1
ASGNI4
LABELV $198
endproc CG_AttachToCent 4 0
export CG_AttachToTag
proc CG_AttachToTag 4 0
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 0
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $205
ADDRFP4 0
INDIRP4
CNSTI4 12
ADDP4
INDIRI4
CNSTI4 0
NEI4 $203
LABELV $205
ADDRGP4 $202
JUMPV
LABELV $203
ADDRFP4 0
INDIRP4
CNSTI4 1
ASGNI4
ADDRFP4 0
INDIRP4
CNSTI4 4
ADDP4
CNSTI4 1
ASGNI4
LABELV $202
endproc CG_AttachToTag 4 0
export CG_AttachToParticle
proc CG_AttachToParticle 4 0
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 0
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $209
ADDRFP4 0
INDIRP4
CNSTI4 20
ADDP4
INDIRI4
CNSTI4 0
NEI4 $207
LABELV $209
ADDRGP4 $206
JUMPV
LABELV $207
ADDRFP4 0
INDIRP4
CNSTI4 3
ASGNI4
ADDRFP4 0
INDIRP4
CNSTI4 4
ADDP4
CNSTI4 1
ASGNI4
LABELV $206
endproc CG_AttachToParticle 4 0
export CG_SetAttachmentPoint
proc CG_SetAttachmentPoint 0 0
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 0
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $211
ADDRGP4 $210
JUMPV
LABELV $211
ADDRFP4 0
INDIRP4
CNSTI4 52
ADDP4
ADDRFP4 4
INDIRP4
INDIRB
ASGNB 12
ADDRFP4 0
INDIRP4
CNSTI4 8
ADDP4
CNSTI4 1
ASGNI4
LABELV $210
endproc CG_SetAttachmentPoint 0 0
export CG_SetAttachmentCent
proc CG_SetAttachmentCent 4 0
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRLP4 0
CNSTU4 0
ASGNU4
ADDRFP4 0
INDIRP4
CVPU4 4
ADDRLP4 0
INDIRU4
EQU4 $216
ADDRFP4 4
INDIRP4
CVPU4 4
ADDRLP4 0
INDIRU4
NEU4 $214
LABELV $216
ADDRGP4 $213
JUMPV
LABELV $214
ADDRFP4 0
INDIRP4
CNSTI4 1372
ADDP4
ADDRFP4 4
INDIRP4
INDIRI4
ASGNI4
ADDRFP4 0
INDIRP4
CNSTI4 16
ADDP4
CNSTI4 1
ASGNI4
LABELV $213
endproc CG_SetAttachmentCent 4 0
export CG_SetAttachmentTag
proc CG_SetAttachmentTag 0 12
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 0
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $218
ADDRGP4 $217
JUMPV
LABELV $218
ADDRFP4 0
INDIRP4
CNSTI4 204
ADDP4
ADDRFP4 4
INDIRP4
INDIRB
ASGNB 140
ADDRFP4 0
INDIRP4
CNSTI4 344
ADDP4
ADDRFP4 8
INDIRI4
ASGNI4
ADDRFP4 0
INDIRP4
CNSTI4 348
ADDP4
ARGP4
ADDRFP4 12
INDIRP4
ARGP4
CNSTU4 1024
ARGU4
ADDRGP4 strncpy
CALLP4
pop
ADDRFP4 0
INDIRP4
CNSTI4 12
ADDP4
CNSTI4 1
ASGNI4
LABELV $217
endproc CG_SetAttachmentTag 0 12
export CG_SetAttachmentParticle
proc CG_SetAttachmentParticle 0 0
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 0
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $221
ADDRGP4 $220
JUMPV
LABELV $221
ADDRFP4 0
INDIRP4
CNSTI4 1376
ADDP4
ADDRFP4 4
INDIRP4
ASGNP4
ADDRFP4 0
INDIRP4
CNSTI4 20
ADDP4
CNSTI4 1
ASGNI4
LABELV $220
endproc CG_SetAttachmentParticle 0 0
export CG_SetAttachmentOffset
proc CG_SetAttachmentOffset 0 0
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 0
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $224
ADDRGP4 $223
JUMPV
LABELV $224
ADDRFP4 0
INDIRP4
CNSTI4 28
ADDP4
ADDRFP4 4
INDIRP4
INDIRB
ASGNB 12
ADDRFP4 0
INDIRP4
CNSTI4 24
ADDP4
CNSTI4 1
ASGNI4
LABELV $223
endproc CG_SetAttachmentOffset 0 0
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
import CG_CheckChangedPredictableEvents
import CG_TransitionPlayerState
import CG_Respawn
import CG_ShaderStateChanged
import CG_SetConfigValues
import CG_ParseServerinfo
import CG_ExecuteNewServerCommands
import CG_RequestScores
import CG_InitConsoleCommands
import CG_ConsoleCommand
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
LABELV $142
byte 1 94
byte 1 49
byte 1 69
byte 1 82
byte 1 82
byte 1 79
byte 1 82
byte 1 58
byte 1 32
byte 1 73
byte 1 110
byte 1 118
byte 1 97
byte 1 108
byte 1 105
byte 1 100
byte 1 32
byte 1 97
byte 1 116
byte 1 116
byte 1 97
byte 1 99
byte 1 104
byte 1 109
byte 1 101
byte 1 110
byte 1 116
byte 1 84
byte 1 121
byte 1 112
byte 1 101
byte 1 95
byte 1 116
byte 1 32
byte 1 105
byte 1 110
byte 1 32
byte 1 97
byte 1 116
byte 1 116
byte 1 97
byte 1 99
byte 1 104
byte 1 109
byte 1 101
byte 1 110
byte 1 116
byte 1 10
byte 1 0
