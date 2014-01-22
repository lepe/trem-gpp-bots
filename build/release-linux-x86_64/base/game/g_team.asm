export PrintMsg
code
proc PrintMsg 1048 16
ADDRLP4 1028
ADDRFP4 4+4
ASGNP4
ADDRLP4 4
ARGP4
CNSTU4 1024
ARGU4
ADDRFP4 4
INDIRP4
ARGP4
ADDRLP4 1028
INDIRP4
ARGP4
ADDRLP4 1032
ADDRGP4 Q_vsnprintf
CALLI4
ASGNI4
ADDRLP4 1032
INDIRI4
CVIU4 4
CNSTU4 1024
LEU4 $83
ADDRGP4 $85
ARGP4
ADDRGP4 G_Error
CALLV
pop
LABELV $83
ADDRLP4 1028
CNSTP4 0
ASGNP4
ADDRGP4 $87
JUMPV
LABELV $86
ADDRLP4 0
INDIRP4
CNSTI1 39
ASGNI1
LABELV $87
ADDRLP4 4
ARGP4
CNSTI4 34
ARGI4
ADDRLP4 1036
ADDRGP4 strchr
CALLP4
ASGNP4
ADDRLP4 0
ADDRLP4 1036
INDIRP4
ASGNP4
ADDRLP4 1036
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $86
ADDRGP4 $90
ARGP4
ADDRLP4 4
ARGP4
ADDRLP4 1044
ADDRGP4 va
CALLP4
ASGNP4
ADDRFP4 0
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $91
ADDRLP4 1040
CNSTI4 -1
ASGNI4
ADDRGP4 $92
JUMPV
LABELV $91
ADDRLP4 1040
ADDRFP4 0
INDIRP4
CVPU4 4
ADDRGP4 g_entities
CVPU4 4
SUBU4
CVUI4 4
CNSTI4 1668
DIVI4
ASGNI4
LABELV $92
ADDRLP4 1040
INDIRI4
ARGI4
ADDRLP4 1044
INDIRP4
ARGP4
ADDRGP4 trap_SendServerCommand
CALLV
pop
LABELV $81
endproc PrintMsg 1048 16
export G_TeamFromString
proc G_TeamFromString 28 4
ADDRFP4 0
INDIRP4
INDIRI1
CVII4 1
ARGI4
ADDRLP4 4
ADDRGP4 tolower
CALLI4
ASGNI4
ADDRLP4 0
ADDRLP4 4
INDIRI4
ASGNI4
ADDRLP4 12
CNSTI4 97
ASGNI4
ADDRLP4 0
INDIRI4
ADDRLP4 12
INDIRI4
EQI4 $98
ADDRLP4 0
INDIRI4
ADDRLP4 12
INDIRI4
GTI4 $101
LABELV $100
ADDRLP4 0
INDIRI4
CNSTI4 48
EQI4 $97
ADDRLP4 0
INDIRI4
CNSTI4 49
EQI4 $98
ADDRLP4 0
INDIRI4
CNSTI4 50
EQI4 $99
ADDRGP4 $94
JUMPV
LABELV $101
ADDRLP4 24
CNSTI4 104
ASGNI4
ADDRLP4 0
INDIRI4
ADDRLP4 24
INDIRI4
EQI4 $99
ADDRLP4 0
INDIRI4
ADDRLP4 24
INDIRI4
LTI4 $94
LABELV $102
ADDRLP4 0
INDIRI4
CNSTI4 115
EQI4 $97
ADDRGP4 $94
JUMPV
LABELV $97
CNSTI4 0
RETI4
ADDRGP4 $93
JUMPV
LABELV $98
CNSTI4 1
RETI4
ADDRGP4 $93
JUMPV
LABELV $99
CNSTI4 2
RETI4
ADDRGP4 $93
JUMPV
LABELV $94
CNSTI4 3
RETI4
LABELV $93
endproc G_TeamFromString 28 4
export G_TeamCommand
proc G_TeamCommand 16 8
ADDRFP4 0
ADDRFP4 0
INDIRI4
ASGNI4
ADDRLP4 0
CNSTI4 0
ASGNI4
ADDRGP4 $107
JUMPV
LABELV $104
CNSTI4 2544
ADDRLP4 0
INDIRI4
MULI4
ADDRGP4 level
INDIRP4
ADDP4
CNSTI4 428
ADDP4
INDIRI4
CNSTI4 2
NEI4 $109
ADDRLP4 8
CNSTI4 2544
ADDRLP4 0
INDIRI4
MULI4
ADDRGP4 level
INDIRP4
ADDP4
CNSTI4 532
ADDP4
INDIRI4
ASGNI4
ADDRLP4 8
INDIRI4
ADDRFP4 0
INDIRI4
EQI4 $114
ADDRLP4 8
INDIRI4
CNSTI4 0
NEI4 $111
CNSTI4 1668
ADDRLP4 0
INDIRI4
MULI4
ADDRGP4 g_entities
ADDP4
ARGP4
ADDRGP4 $113
ARGP4
ADDRLP4 12
ADDRGP4 G_admin_permission
CALLI4
ASGNI4
ADDRLP4 12
INDIRI4
CNSTI4 0
EQI4 $111
LABELV $114
ADDRLP4 0
INDIRI4
ARGI4
ADDRFP4 4
INDIRP4
ARGP4
ADDRGP4 trap_SendServerCommand
CALLV
pop
LABELV $111
LABELV $109
LABELV $105
ADDRLP4 0
ADDRLP4 0
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
LABELV $107
ADDRLP4 0
INDIRI4
ADDRGP4 level+24
INDIRI4
LTI4 $104
LABELV $103
endproc G_TeamCommand 16 8
export OnSameTeam
proc OnSameTeam 16 0
ADDRLP4 0
CNSTI4 524
ASGNI4
ADDRLP4 4
CNSTU4 0
ASGNU4
ADDRFP4 0
INDIRP4
ADDRLP4 0
INDIRI4
ADDP4
INDIRP4
CVPU4 4
ADDRLP4 4
INDIRU4
EQU4 $118
ADDRFP4 4
INDIRP4
ADDRLP4 0
INDIRI4
ADDP4
INDIRP4
CVPU4 4
ADDRLP4 4
INDIRU4
NEU4 $116
LABELV $118
CNSTI4 0
RETI4
ADDRGP4 $115
JUMPV
LABELV $116
ADDRLP4 8
CNSTI4 524
ASGNI4
ADDRLP4 12
CNSTI4 532
ASGNI4
ADDRFP4 0
INDIRP4
ADDRLP4 8
INDIRI4
ADDP4
INDIRP4
ADDRLP4 12
INDIRI4
ADDP4
INDIRI4
ADDRFP4 4
INDIRP4
ADDRLP4 8
INDIRI4
ADDP4
INDIRP4
ADDRLP4 12
INDIRI4
ADDP4
INDIRI4
NEI4 $119
CNSTI4 1
RETI4
ADDRGP4 $115
JUMPV
LABELV $119
CNSTI4 0
RETI4
LABELV $115
endproc OnSameTeam 16 0
proc G_ClientListForTeam 20 12
ADDRFP4 4
ADDRFP4 4
INDIRI4
ASGNI4
ADDRLP4 4
ARGP4
CNSTI4 0
ARGI4
CNSTU4 8
ARGU4
ADDRGP4 memset
CALLP4
pop
ADDRLP4 0
CNSTI4 0
ASGNI4
ADDRGP4 $126
JUMPV
LABELV $123
ADDRLP4 12
CNSTI4 1668
ADDRLP4 0
INDIRI4
MULI4
ADDRGP4 g_entities
ADDP4
ASGNP4
ADDRLP4 12
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 428
ADDP4
INDIRI4
CNSTI4 2
EQI4 $128
ADDRGP4 $124
JUMPV
LABELV $128
ADDRLP4 12
INDIRP4
CNSTI4 528
ADDP4
INDIRI4
CNSTI4 0
EQI4 $130
ADDRLP4 12
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 216
ADDP4
INDIRI4
ADDRFP4 4
INDIRI4
NEI4 $130
ADDRLP4 4
ARGP4
ADDRLP4 12
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 148
ADDP4
INDIRI4
ARGI4
ADDRGP4 Com_ClientListAdd
CALLV
pop
LABELV $130
LABELV $124
ADDRLP4 0
ADDRLP4 0
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
LABELV $126
ADDRLP4 0
INDIRI4
ADDRGP4 g_maxclients+12
INDIRI4
LTI4 $123
ADDRFP4 0
INDIRP4
ADDRLP4 4
INDIRB
ASGNB 8
LABELV $121
endproc G_ClientListForTeam 20 12
export G_UpdateTeamConfigStrings
proc G_UpdateTeamConfigStrings 16 12
ADDRLP4 0
ARGP4
CNSTI4 1
ARGI4
ADDRGP4 G_ClientListForTeam
CALLV
pop
ADDRLP4 8
ARGP4
CNSTI4 2
ARGI4
ADDRGP4 G_ClientListForTeam
CALLV
pop
ADDRGP4 level+11200
INDIRI4
CNSTI4 0
EQI4 $133
ADDRLP4 0
ARGP4
CNSTI4 0
ARGI4
CNSTU4 8
ARGU4
ADDRGP4 memset
CALLP4
pop
ADDRLP4 8
ARGP4
CNSTI4 0
ARGI4
CNSTU4 8
ARGU4
ADDRGP4 memset
CALLP4
pop
LABELV $133
CNSTI4 7
ARGI4
ADDRLP4 8
ARGP4
ADDRGP4 trap_SetConfigstringRestrictions
CALLV
pop
CNSTI4 10
ARGI4
ADDRLP4 8
ARGP4
ADDRGP4 trap_SetConfigstringRestrictions
CALLV
pop
CNSTI4 13
ARGI4
ADDRLP4 8
ARGP4
ADDRGP4 trap_SetConfigstringRestrictions
CALLV
pop
CNSTI4 16
ARGI4
ADDRLP4 8
ARGP4
ADDRGP4 trap_SetConfigstringRestrictions
CALLV
pop
CNSTI4 8
ARGI4
ADDRLP4 0
ARGP4
ADDRGP4 trap_SetConfigstringRestrictions
CALLV
pop
CNSTI4 11
ARGI4
ADDRLP4 0
ARGP4
ADDRGP4 trap_SetConfigstringRestrictions
CALLV
pop
CNSTI4 14
ARGI4
ADDRLP4 0
ARGP4
ADDRGP4 trap_SetConfigstringRestrictions
CALLV
pop
CNSTI4 17
ARGI4
ADDRLP4 0
ARGP4
ADDRGP4 trap_SetConfigstringRestrictions
CALLV
pop
CNSTI4 28
ARGI4
ADDRLP4 8
ARGP4
ADDRGP4 trap_SetConfigstringRestrictions
CALLV
pop
CNSTI4 29
ARGI4
ADDRLP4 0
ARGP4
ADDRGP4 trap_SetConfigstringRestrictions
CALLV
pop
LABELV $132
endproc G_UpdateTeamConfigStrings 16 12
export G_LeaveTeam
proc G_LeaveTeam 24 12
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRLP4 8
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 532
ADDP4
INDIRI4
ASGNI4
ADDRLP4 8
INDIRI4
CNSTI4 1
NEI4 $137
ADDRGP4 level+15444
ARGP4
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 148
ADDP4
INDIRI4
ARGI4
ADDRGP4 G_RemoveFromSpawnQueue
CALLI4
pop
ADDRGP4 $138
JUMPV
LABELV $137
ADDRLP4 8
INDIRI4
CNSTI4 2
NEI4 $140
ADDRGP4 level+15708
ARGP4
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 148
ADDP4
INDIRI4
ARGI4
ADDRGP4 G_RemoveFromSpawnQueue
CALLI4
pop
ADDRGP4 $141
JUMPV
LABELV $140
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 1740
ADDP4
INDIRI4
CNSTI4 3
NEI4 $136
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 G_StopFollowing
CALLV
pop
ADDRGP4 $136
JUMPV
LABELV $141
LABELV $138
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 G_StopFromFollowing
CALLV
pop
ADDRFP4 0
INDIRP4
ARGP4
ADDRLP4 8
INDIRI4
ARGI4
CNSTI4 0
ARGI4
ADDRGP4 G_Vote
CALLV
pop
ADDRFP4 0
INDIRP4
CNSTI4 1640
ADDP4
CNSTI4 0
ASGNI4
ADDRLP4 4
CNSTI4 0
ASGNI4
ADDRGP4 $148
JUMPV
LABELV $145
ADDRLP4 0
CNSTI4 1668
ADDRLP4 4
INDIRI4
MULI4
ADDRGP4 g_entities
ADDP4
ASGNP4
ADDRLP4 0
INDIRP4
CNSTI4 528
ADDP4
INDIRI4
CNSTI4 0
NEI4 $150
ADDRGP4 $146
JUMPV
LABELV $150
ADDRLP4 12
ADDRLP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ASGNP4
ADDRLP4 12
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $152
ADDRLP4 12
INDIRP4
CNSTI4 428
ADDP4
INDIRI4
CNSTI4 2
NEI4 $152
ADDRLP4 16
ADDRLP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ASGNP4
ADDRLP4 16
INDIRP4
CNSTI4 224
ADDP4
INDIRI4
CNSTI4 32
BANDI4
CNSTI4 0
EQI4 $153
ADDRLP4 16
INDIRP4
CNSTI4 1904
ADDP4
INDIRP4
CVPU4 4
ADDRFP4 0
INDIRP4
CVPU4 4
NEU4 $153
ADDRLP4 20
ADDRLP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 224
ADDP4
ASGNP4
ADDRLP4 20
INDIRP4
ADDRLP4 20
INDIRP4
INDIRI4
CNSTI4 -33
BANDI4
ASGNI4
ADDRGP4 $153
JUMPV
LABELV $152
ADDRLP4 0
INDIRP4
CNSTI4 4
ADDP4
INDIRI4
CNSTI4 5
NEI4 $156
ADDRLP4 0
INDIRP4
CNSTI4 520
ADDP4
INDIRI4
ADDRFP4 0
INDIRP4
INDIRI4
NEI4 $156
ADDRLP4 0
INDIRP4
ARGP4
ADDRGP4 G_FreeEntity
CALLV
pop
LABELV $156
LABELV $153
LABELV $146
ADDRLP4 4
ADDRLP4 4
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
LABELV $148
ADDRLP4 4
INDIRI4
ADDRGP4 level+12
INDIRI4
LTI4 $145
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 G_ClearPlayerZapEffects
CALLV
pop
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ARGP4
ADDRGP4 G_namelog_update_score
CALLV
pop
LABELV $136
endproc G_LeaveTeam 24 12
export G_ChangeTeam
proc G_ChangeTeam 20 16
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRFP4 4
ADDRFP4 4
INDIRI4
ASGNI4
ADDRLP4 0
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 532
ADDP4
INDIRI4
ASGNI4
ADDRLP4 0
INDIRI4
ADDRFP4 4
INDIRI4
NEI4 $159
ADDRGP4 $158
JUMPV
LABELV $159
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 G_LeaveTeam
CALLV
pop
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 536
ADDP4
ADDRGP4 level+32
INDIRI4
ASGNI4
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 532
ADDP4
ADDRFP4 4
INDIRI4
ASGNI4
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 520
ADDP4
CNSTI4 0
ASGNI4
ADDRFP4 0
INDIRP4
ARGP4
CNSTP4 0
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
ADDRGP4 ClientSpawn
CALLV
pop
ADDRLP4 0
INDIRI4
CNSTI4 2
NEI4 $162
ADDRFP4 4
INDIRI4
CNSTI4 1
NEI4 $162
ADDRLP4 8
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 556
ADDP4
ASGNP4
ADDRLP4 8
INDIRP4
CNSTI4 3600
ADDRLP4 8
INDIRP4
INDIRI4
MULI4
CNSTI4 2000
DIVI4
CVIF4 4
CNSTF4 1056964608
ADDF4
CVFI4 4
ASGNI4
ADDRGP4 $163
JUMPV
LABELV $162
ADDRLP4 0
INDIRI4
CNSTI4 1
NEI4 $164
ADDRFP4 4
INDIRI4
CNSTI4 2
NEI4 $164
ADDRLP4 8
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 556
ADDP4
ASGNP4
ADDRLP4 8
INDIRP4
CNSTI4 2000
ADDRLP4 8
INDIRP4
INDIRI4
MULI4
CNSTI4 3600
DIVI4
CVIF4 4
CNSTF4 1056964608
ADDF4
CVFI4 4
ASGNI4
LABELV $164
LABELV $163
ADDRLP4 8
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ASGNP4
ADDRLP4 8
INDIRP4
CNSTI4 288
ADDP4
ADDRLP4 8
INDIRP4
CNSTI4 556
ADDP4
INDIRI4
ASGNI4
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 148
ADDP4
INDIRI4
ARGI4
CNSTI4 0
ARGI4
ADDRGP4 ClientUserinfoChanged
CALLP4
pop
ADDRGP4 G_UpdateTeamConfigStrings
CALLV
pop
ADDRFP4 4
INDIRI4
ARGI4
ADDRLP4 12
ADDRGP4 BG_TeamName
CALLP4
ASGNP4
ADDRGP4 $166
ARGP4
ADDRFP4 0
INDIRP4
CVPU4 4
ADDRGP4 g_entities
CVPU4 4
SUBU4
CVUI4 4
CNSTI4 1668
DIVI4
ARGI4
ADDRLP4 12
INDIRP4
ARGP4
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 468
ADDP4
ARGP4
ADDRGP4 G_LogPrintf
CALLV
pop
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ARGP4
ADDRGP4 G_namelog_update_score
CALLV
pop
ADDRFP4 0
INDIRP4
ARGP4
ADDRGP4 TeamplayInfoMessage
CALLV
pop
LABELV $158
endproc G_ChangeTeam 20 16
export Team_GetLocation
proc Team_GetLocation 32 8
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRLP4 12
CNSTP4 0
ASGNP4
ADDRLP4 8
CNSTF4 1296039936
ASGNF4
ADDRLP4 0
ADDRGP4 level+11240
INDIRP4
ASGNP4
ADDRGP4 $171
JUMPV
LABELV $168
ADDRLP4 16
CNSTI4 496
ASGNI4
ADDRFP4 0
INDIRP4
ADDRLP4 16
INDIRI4
ADDP4
ARGP4
ADDRLP4 0
INDIRP4
ADDRLP4 16
INDIRI4
ADDP4
ARGP4
ADDRLP4 20
ADDRGP4 DistanceSquared
CALLF4
ASGNF4
ADDRLP4 4
ADDRLP4 20
INDIRF4
ASGNF4
ADDRLP4 4
INDIRF4
ADDRLP4 8
INDIRF4
LEF4 $173
ADDRGP4 $169
JUMPV
LABELV $173
ADDRLP4 24
CNSTI4 496
ASGNI4
ADDRFP4 0
INDIRP4
ADDRLP4 24
INDIRI4
ADDP4
ARGP4
ADDRLP4 0
INDIRP4
ADDRLP4 24
INDIRI4
ADDP4
ARGP4
ADDRLP4 28
ADDRGP4 trap_InPVS
CALLI4
ASGNI4
ADDRLP4 28
INDIRI4
CNSTI4 0
NEI4 $175
ADDRGP4 $169
JUMPV
LABELV $175
ADDRLP4 8
ADDRLP4 4
INDIRF4
ASGNF4
ADDRLP4 12
ADDRLP4 0
INDIRP4
ASGNP4
LABELV $169
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 612
ADDP4
INDIRP4
ASGNP4
LABELV $171
ADDRLP4 0
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $168
ADDRLP4 12
INDIRP4
RETP4
LABELV $167
endproc Team_GetLocation 32 8
export TeamplayInfoMessage
proc TeamplayInfoMessage 1240 20
ADDRFP4 0
ADDRFP4 0
INDIRP4
ASGNP4
ADDRLP4 1196
CNSTI4 0
ASGNI4
ADDRLP4 1188
CNSTI4 0
ASGNI4
ADDRLP4 1192
CNSTI4 0
ASGNI4
ADDRGP4 g_allowTeamOverlay+12
INDIRI4
CNSTI4 0
NEI4 $178
ADDRGP4 $177
JUMPV
LABELV $178
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 508
ADDP4
INDIRI4
CNSTI4 0
NEI4 $181
ADDRGP4 $177
JUMPV
LABELV $181
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 532
ADDP4
INDIRI4
CNSTI4 0
NEI4 $183
ADDRLP4 1204
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ASGNP4
ADDRLP4 1204
INDIRP4
CNSTI4 1740
ADDP4
INDIRI4
CNSTI4 1
EQI4 $187
ADDRLP4 1204
INDIRP4
CNSTI4 1744
ADDP4
INDIRI4
CNSTI4 0
GEI4 $185
LABELV $187
ADDRGP4 $177
JUMPV
LABELV $185
ADDRLP4 1200
CNSTI4 1668
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 1744
ADDP4
INDIRI4
MULI4
ADDRGP4 g_entities+524
ADDP4
INDIRP4
CNSTI4 532
ADDP4
INDIRI4
ASGNI4
ADDRGP4 $184
JUMPV
LABELV $183
ADDRLP4 1200
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 532
ADDP4
INDIRI4
ASGNI4
LABELV $184
ADDRLP4 44
CNSTI1 0
ASGNI1
ADDRLP4 1204
CNSTI4 0
ASGNI4
ADDRLP4 36
ADDRLP4 1204
INDIRI4
ASGNI4
ADDRLP4 0
ADDRLP4 1204
INDIRI4
ASGNI4
LABELV $189
ADDRLP4 4
CNSTI4 1668
ADDRLP4 0
INDIRI4
MULI4
ADDRGP4 g_entities
ADDP4
ASGNP4
ADDRLP4 8
ADDRLP4 4
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ASGNP4
ADDRFP4 0
INDIRP4
CVPU4 4
ADDRLP4 4
INDIRP4
CVPU4 4
EQU4 $197
ADDRLP4 8
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $197
ADDRLP4 1200
INDIRI4
ADDRLP4 8
INDIRP4
CNSTI4 532
ADDP4
INDIRI4
NEI4 $197
ADDRLP4 4
INDIRP4
CNSTI4 528
ADDP4
INDIRI4
CNSTI4 0
NEI4 $193
LABELV $197
ADDRGP4 $190
JUMPV
LABELV $193
ADDRLP4 8
INDIRP4
CNSTI4 1740
ADDP4
INDIRI4
CNSTI4 0
EQI4 $198
ADDRLP4 1216
CNSTI4 0
ASGNI4
ADDRLP4 1192
ADDRLP4 1216
INDIRI4
ASGNI4
ADDRLP4 1188
ADDRLP4 1216
INDIRI4
ASGNI4
ADDRGP4 $199
JUMPV
LABELV $198
ADDRLP4 8
INDIRP4
CNSTI4 532
ADDP4
INDIRI4
CNSTI4 2
NEI4 $200
ADDRLP4 1192
ADDRLP4 8
INDIRP4
CNSTI4 152
ADDP4
INDIRI4
ASGNI4
CNSTI4 6
ARGI4
ADDRLP4 8
INDIRP4
CNSTI4 192
ADDP4
ARGP4
ADDRLP4 1220
ADDRGP4 BG_InventoryContainsUpgrade
CALLI4
ASGNI4
ADDRLP4 1220
INDIRI4
CNSTI4 0
EQI4 $202
ADDRLP4 1188
CNSTI4 6
ASGNI4
ADDRGP4 $201
JUMPV
LABELV $202
CNSTI4 5
ARGI4
ADDRLP4 8
INDIRP4
CNSTI4 192
ADDP4
ARGP4
ADDRLP4 1224
ADDRGP4 BG_InventoryContainsUpgrade
CALLI4
ASGNI4
ADDRLP4 1224
INDIRI4
CNSTI4 0
EQI4 $204
ADDRLP4 1188
CNSTI4 5
ASGNI4
ADDRGP4 $201
JUMPV
LABELV $204
CNSTI4 4
ARGI4
ADDRLP4 8
INDIRP4
CNSTI4 192
ADDP4
ARGP4
ADDRLP4 1228
ADDRGP4 BG_InventoryContainsUpgrade
CALLI4
ASGNI4
ADDRLP4 1228
INDIRI4
CNSTI4 0
EQI4 $206
ADDRLP4 1188
CNSTI4 4
ASGNI4
ADDRGP4 $201
JUMPV
LABELV $206
CNSTI4 2
ARGI4
ADDRLP4 8
INDIRP4
CNSTI4 192
ADDP4
ARGP4
ADDRLP4 1232
ADDRGP4 BG_InventoryContainsUpgrade
CALLI4
ASGNI4
ADDRLP4 1232
INDIRI4
CNSTI4 0
EQI4 $208
ADDRLP4 1188
CNSTI4 2
ASGNI4
ADDRGP4 $201
JUMPV
LABELV $208
CNSTI4 1
ARGI4
ADDRLP4 8
INDIRP4
CNSTI4 192
ADDP4
ARGP4
ADDRLP4 1236
ADDRGP4 BG_InventoryContainsUpgrade
CALLI4
ASGNI4
ADDRLP4 1236
INDIRI4
CNSTI4 0
EQI4 $210
ADDRLP4 1188
CNSTI4 1
ASGNI4
ADDRGP4 $201
JUMPV
LABELV $210
ADDRLP4 1188
CNSTI4 0
ASGNI4
ADDRGP4 $201
JUMPV
LABELV $200
ADDRLP4 8
INDIRP4
CNSTI4 532
ADDP4
INDIRI4
CNSTI4 1
NEI4 $212
ADDRLP4 1192
ADDRLP4 8
INDIRP4
CNSTI4 212
ADDP4
INDIRI4
ASGNI4
ADDRLP4 1188
CNSTI4 0
ASGNI4
LABELV $212
LABELV $201
LABELV $199
ADDRGP4 $214
ARGP4
ADDRLP4 1220
ADDRLP4 4
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
ASGNP4
ADDRLP4 1220
INDIRP4
CNSTI4 504
ADDP4
INDIRI4
ARGI4
ADDRLP4 1220
INDIRP4
CNSTI4 192
ADDP4
INDIRI4
CNSTI4 1
GEI4 $216
ADDRLP4 1216
CNSTI4 0
ASGNI4
ADDRGP4 $217
JUMPV
LABELV $216
ADDRLP4 1216
ADDRLP4 4
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 192
ADDP4
INDIRI4
ASGNI4
LABELV $217
ADDRLP4 1216
INDIRI4
ARGI4
ADDRLP4 1192
INDIRI4
ARGI4
ADDRLP4 1188
INDIRI4
ARGI4
ADDRLP4 1224
ADDRGP4 va
CALLP4
ASGNP4
ADDRLP4 32
ADDRLP4 1224
INDIRP4
ASGNP4
ADDRLP4 0
INDIRI4
CNSTI4 4
LSHI4
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 712
ADDP4
ADDP4
ARGP4
ADDRLP4 32
INDIRP4
ARGP4
ADDRLP4 1228
ADDRGP4 strcmp
CALLI4
ASGNI4
ADDRLP4 1228
INDIRI4
CNSTI4 0
NEI4 $218
ADDRGP4 $190
JUMPV
LABELV $218
ADDRLP4 0
INDIRI4
CNSTI4 4
LSHI4
ADDRFP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 712
ADDP4
ADDP4
ARGP4
ADDRLP4 32
INDIRP4
ARGP4
CNSTI4 16
ARGI4
ADDRGP4 Q_strncpyz
CALLV
pop
ADDRLP4 12
ARGP4
CNSTI4 19
ARGI4
ADDRGP4 $220
ARGP4
ADDRLP4 0
INDIRI4
ARGI4
ADDRLP4 32
INDIRP4
ARGP4
ADDRGP4 Com_sprintf
CALLV
pop
ADDRLP4 12
ARGP4
ADDRLP4 1232
ADDRGP4 strlen
CALLU4
ASGNU4
ADDRLP4 40
ADDRLP4 1232
INDIRU4
CVUI4 4
ASGNI4
ADDRLP4 36
INDIRI4
ADDRLP4 40
INDIRI4
ADDI4
CVIU4 4
CNSTU4 1143
LEU4 $221
ADDRGP4 $191
JUMPV
LABELV $221
ADDRLP4 36
INDIRI4
ADDRLP4 44
ADDP4
ARGP4
ADDRLP4 12
ARGP4
ADDRGP4 strcpy
CALLP4
pop
ADDRLP4 36
ADDRLP4 36
INDIRI4
ADDRLP4 40
INDIRI4
ADDI4
ASGNI4
ADDRLP4 1196
ADDRLP4 1196
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
LABELV $190
ADDRLP4 0
ADDRLP4 0
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
ADDRLP4 0
INDIRI4
CNSTI4 64
LTI4 $189
LABELV $191
ADDRLP4 1196
INDIRI4
CNSTI4 0
NEI4 $223
ADDRGP4 $177
JUMPV
LABELV $223
ADDRGP4 $225
ARGP4
ADDRLP4 44
ARGP4
ADDRLP4 1208
ADDRGP4 va
CALLP4
ASGNP4
ADDRFP4 0
INDIRP4
CVPU4 4
ADDRGP4 g_entities
CVPU4 4
SUBU4
CVUI4 4
CNSTI4 1668
DIVI4
ARGI4
ADDRLP4 1208
INDIRP4
ARGP4
ADDRGP4 trap_SendServerCommand
CALLV
pop
LABELV $177
endproc TeamplayInfoMessage 1240 20
export CheckTeamStatus
proc CheckTeamStatus 24 8
ADDRGP4 level+32
INDIRI4
ADDRGP4 level+60
INDIRI4
SUBI4
CNSTI4 500
LEI4 $227
ADDRGP4 level+60
ADDRGP4 level+32
INDIRI4
ASGNI4
ADDRLP4 4
CNSTI4 0
ASGNI4
ADDRGP4 $236
JUMPV
LABELV $233
ADDRLP4 0
CNSTI4 1668
ADDRLP4 4
INDIRI4
MULI4
ADDRGP4 g_entities
ADDP4
ASGNP4
ADDRLP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 428
ADDP4
INDIRI4
CNSTI4 2
EQI4 $238
ADDRGP4 $234
JUMPV
LABELV $238
ADDRLP4 0
INDIRP4
CNSTI4 528
ADDP4
INDIRI4
CNSTI4 0
EQI4 $240
ADDRLP4 16
ADDRLP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 216
ADDP4
INDIRI4
ASGNI4
ADDRLP4 16
INDIRI4
CNSTI4 2
EQI4 $242
ADDRLP4 16
INDIRI4
CNSTI4 1
NEI4 $240
LABELV $242
ADDRLP4 0
INDIRP4
ARGP4
ADDRLP4 20
ADDRGP4 Team_GetLocation
CALLP4
ASGNP4
ADDRLP4 8
ADDRLP4 20
INDIRP4
ASGNP4
ADDRLP4 8
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $243
ADDRLP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 504
ADDP4
ADDRLP4 8
INDIRP4
CNSTI4 208
ADDP4
INDIRI4
ASGNI4
ADDRGP4 $244
JUMPV
LABELV $243
ADDRLP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 504
ADDP4
CNSTI4 0
ASGNI4
LABELV $244
LABELV $240
LABELV $234
ADDRLP4 4
ADDRLP4 4
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
LABELV $236
ADDRLP4 4
INDIRI4
ADDRGP4 g_maxclients+12
INDIRI4
LTI4 $233
ADDRLP4 4
CNSTI4 0
ASGNI4
ADDRGP4 $248
JUMPV
LABELV $245
ADDRLP4 0
CNSTI4 1668
ADDRLP4 4
INDIRI4
MULI4
ADDRGP4 g_entities
ADDP4
ASGNP4
ADDRLP4 0
INDIRP4
CNSTI4 524
ADDP4
INDIRP4
CNSTI4 428
ADDP4
INDIRI4
CNSTI4 2
EQI4 $250
ADDRGP4 $246
JUMPV
LABELV $250
ADDRLP4 0
INDIRP4
CNSTI4 528
ADDP4
INDIRI4
CNSTI4 0
EQI4 $252
ADDRLP4 0
INDIRP4
ARGP4
ADDRGP4 TeamplayInfoMessage
CALLV
pop
LABELV $252
LABELV $246
ADDRLP4 4
ADDRLP4 4
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
LABELV $248
ADDRLP4 4
INDIRI4
ADDRGP4 g_maxclients+12
INDIRI4
LTI4 $245
LABELV $227
ADDRLP4 12
CNSTI4 0
ASGNI4
ADDRGP4 g_teamImbalanceWarnings+12
INDIRI4
ADDRLP4 12
INDIRI4
EQI4 $254
ADDRGP4 level+11200
INDIRI4
ADDRLP4 12
INDIRI4
NEI4 $254
ADDRGP4 level+32
INDIRI4
ADDRGP4 level+16120
INDIRI4
SUBI4
CNSTI4 1000
ADDRGP4 g_teamImbalanceWarnings+12
INDIRI4
MULI4
LEI4 $254
ADDRGP4 level+16124
INDIRI4
CNSTI4 3
GEI4 $254
ADDRGP4 level+68
INDIRI4
ADDRLP4 12
INDIRI4
NEI4 $254
ADDRGP4 level+16120
ADDRGP4 level+32
INDIRI4
ASGNI4
ADDRGP4 level+11244
INDIRI4
CNSTI4 0
LEI4 $265
ADDRGP4 level+11256
INDIRI4
ADDRGP4 level+11252
INDIRI4
SUBI4
CNSTI4 2
LEI4 $265
CNSTI4 -1
ARGI4
ADDRGP4 $270
ARGP4
ADDRGP4 trap_SendServerCommand
CALLV
pop
ADDRLP4 16
ADDRGP4 level+16124
ASGNP4
ADDRLP4 16
INDIRP4
ADDRLP4 16
INDIRP4
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
ADDRGP4 $266
JUMPV
LABELV $265
ADDRGP4 level+11248
INDIRI4
CNSTI4 0
LEI4 $272
ADDRGP4 level+11252
INDIRI4
ADDRGP4 level+11256
INDIRI4
SUBI4
CNSTI4 2
LEI4 $272
CNSTI4 -1
ARGI4
ADDRGP4 $277
ARGP4
ADDRGP4 trap_SendServerCommand
CALLV
pop
ADDRLP4 16
ADDRGP4 level+16124
ASGNP4
ADDRLP4 16
INDIRP4
ADDRLP4 16
INDIRP4
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
ADDRGP4 $273
JUMPV
LABELV $272
ADDRGP4 level+16124
CNSTI4 0
ASGNI4
LABELV $273
LABELV $266
LABELV $254
LABELV $226
endproc CheckTeamStatus 24 8
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
import TeleportPlayer
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
import G_BotSpectatorThink
import G_FastThink
import G_FrameAim
import G_BotThink
import G_BotCmd
import G_BotReload
import G_DeleteBots
import G_BotDel
import G_BotAdd
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
LABELV $277
byte 1 112
byte 1 114
byte 1 105
byte 1 110
byte 1 116
byte 1 32
byte 1 34
byte 1 84
byte 1 101
byte 1 97
byte 1 109
byte 1 115
byte 1 32
byte 1 97
byte 1 114
byte 1 101
byte 1 32
byte 1 105
byte 1 109
byte 1 98
byte 1 97
byte 1 108
byte 1 97
byte 1 110
byte 1 99
byte 1 101
byte 1 100
byte 1 46
byte 1 32
byte 1 65
byte 1 108
byte 1 105
byte 1 101
byte 1 110
byte 1 115
byte 1 32
byte 1 104
byte 1 97
byte 1 118
byte 1 101
byte 1 32
byte 1 109
byte 1 111
byte 1 114
byte 1 101
byte 1 32
byte 1 112
byte 1 108
byte 1 97
byte 1 121
byte 1 101
byte 1 114
byte 1 115
byte 1 46
byte 1 10
byte 1 34
byte 1 0
align 1
LABELV $270
byte 1 112
byte 1 114
byte 1 105
byte 1 110
byte 1 116
byte 1 32
byte 1 34
byte 1 84
byte 1 101
byte 1 97
byte 1 109
byte 1 115
byte 1 32
byte 1 97
byte 1 114
byte 1 101
byte 1 32
byte 1 105
byte 1 109
byte 1 98
byte 1 97
byte 1 108
byte 1 97
byte 1 110
byte 1 99
byte 1 101
byte 1 100
byte 1 46
byte 1 32
byte 1 72
byte 1 117
byte 1 109
byte 1 97
byte 1 110
byte 1 115
byte 1 32
byte 1 104
byte 1 97
byte 1 118
byte 1 101
byte 1 32
byte 1 109
byte 1 111
byte 1 114
byte 1 101
byte 1 32
byte 1 112
byte 1 108
byte 1 97
byte 1 121
byte 1 101
byte 1 114
byte 1 115
byte 1 46
byte 1 10
byte 1 34
byte 1 0
align 1
LABELV $225
byte 1 116
byte 1 105
byte 1 110
byte 1 102
byte 1 111
byte 1 37
byte 1 115
byte 1 0
align 1
LABELV $220
byte 1 32
byte 1 37
byte 1 105
byte 1 32
byte 1 37
byte 1 115
byte 1 0
align 1
LABELV $214
byte 1 37
byte 1 105
byte 1 32
byte 1 37
byte 1 105
byte 1 32
byte 1 37
byte 1 105
byte 1 32
byte 1 37
byte 1 105
byte 1 0
align 1
LABELV $166
byte 1 67
byte 1 104
byte 1 97
byte 1 110
byte 1 103
byte 1 101
byte 1 84
byte 1 101
byte 1 97
byte 1 109
byte 1 58
byte 1 32
byte 1 37
byte 1 100
byte 1 32
byte 1 37
byte 1 115
byte 1 58
byte 1 32
byte 1 37
byte 1 115
byte 1 94
byte 1 55
byte 1 32
byte 1 115
byte 1 119
byte 1 105
byte 1 116
byte 1 99
byte 1 104
byte 1 101
byte 1 100
byte 1 32
byte 1 116
byte 1 101
byte 1 97
byte 1 109
byte 1 115
byte 1 10
byte 1 0
align 1
LABELV $113
byte 1 83
byte 1 80
byte 1 69
byte 1 67
byte 1 65
byte 1 76
byte 1 76
byte 1 67
byte 1 72
byte 1 65
byte 1 84
byte 1 0
align 1
LABELV $90
byte 1 112
byte 1 114
byte 1 105
byte 1 110
byte 1 116
byte 1 32
byte 1 34
byte 1 37
byte 1 115
byte 1 34
byte 1 0
align 1
LABELV $85
byte 1 80
byte 1 114
byte 1 105
byte 1 110
byte 1 116
byte 1 77
byte 1 115
byte 1 103
byte 1 32
byte 1 111
byte 1 118
byte 1 101
byte 1 114
byte 1 114
byte 1 117
byte 1 110
byte 1 0
