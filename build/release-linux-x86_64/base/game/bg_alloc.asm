export BG_Alloc
code
proc BG_Alloc 48 12
ADDRLP4 4
ADDRFP4 0
INDIRI4
CVIU4 4
CNSTU4 4
ADDU4
CNSTU4 31
ADDU4
CNSTI4 -32
CVIU4 4
BANDU4
CVUI4 4
ASGNI4
ADDRLP4 16
CNSTP4 0
ASGNP4
ADDRLP4 20
CNSTP4 0
ASGNP4
ADDRLP4 24
CNSTI4 1048577
ASGNI4
ADDRLP4 0
ADDRGP4 freeHead
INDIRP4
ASGNP4
ADDRGP4 $64
JUMPV
LABELV $61
ADDRLP4 0
INDIRP4
INDIRI4
CNSTU4 3735928383
CVUI4 4
EQI4 $65
CNSTI4 1
ARGI4
ADDRGP4 $67
ARGP4
ADDRGP4 Com_Error
CALLV
pop
LABELV $65
ADDRLP4 0
INDIRP4
CNSTI4 4
ADDP4
INDIRI4
ADDRLP4 4
INDIRI4
LTI4 $68
ADDRLP4 0
INDIRP4
CNSTI4 4
ADDP4
INDIRI4
ADDRLP4 4
INDIRI4
NEI4 $70
ADDRLP4 12
ADDRLP4 0
INDIRP4
CNSTI4 8
ADDP4
INDIRP4
ASGNP4
ADDRLP4 8
ADDRLP4 0
INDIRP4
CNSTI4 12
ADDP4
INDIRP4
ASGNP4
ADDRLP4 12
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $72
ADDRLP4 12
INDIRP4
CNSTI4 12
ADDP4
ADDRLP4 8
INDIRP4
ASGNP4
LABELV $72
ADDRLP4 8
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $74
ADDRLP4 8
INDIRP4
CNSTI4 8
ADDP4
ADDRLP4 12
INDIRP4
ASGNP4
LABELV $74
ADDRLP4 0
INDIRP4
CVPU4 4
ADDRGP4 freeHead
INDIRP4
CVPU4 4
NEU4 $76
ADDRGP4 freeHead
ADDRLP4 8
INDIRP4
ASGNP4
LABELV $76
ADDRLP4 16
ADDRLP4 0
INDIRP4
ASGNP4
ADDRGP4 $63
JUMPV
LABELV $70
ADDRLP4 0
INDIRP4
CNSTI4 4
ADDP4
INDIRI4
ADDRLP4 24
INDIRI4
GEI4 $78
ADDRLP4 20
ADDRLP4 0
INDIRP4
ASGNP4
ADDRLP4 24
ADDRLP4 0
INDIRP4
CNSTI4 4
ADDP4
INDIRI4
ASGNI4
LABELV $78
LABELV $68
LABELV $62
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 12
ADDP4
INDIRP4
ASGNP4
LABELV $64
ADDRLP4 0
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $61
LABELV $63
ADDRLP4 32
CNSTU4 0
ASGNU4
ADDRLP4 16
INDIRP4
CVPU4 4
ADDRLP4 32
INDIRU4
NEU4 $80
ADDRLP4 20
INDIRP4
CVPU4 4
ADDRLP4 32
INDIRU4
EQU4 $80
ADDRLP4 36
ADDRLP4 20
INDIRP4
CNSTI4 4
ADDP4
ASGNP4
ADDRLP4 36
INDIRP4
ADDRLP4 36
INDIRP4
INDIRI4
ADDRLP4 4
INDIRI4
SUBI4
ASGNI4
ADDRLP4 28
ADDRLP4 20
INDIRP4
CNSTI4 4
ADDP4
INDIRI4
ADDRLP4 20
INDIRP4
ADDP4
ASGNP4
ADDRLP4 16
ADDRLP4 28
INDIRP4
ASGNP4
LABELV $80
ADDRLP4 16
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $82
ADDRLP4 36
ADDRGP4 freeMem
ASGNP4
ADDRLP4 36
INDIRP4
ADDRLP4 36
INDIRP4
INDIRI4
ADDRLP4 4
INDIRI4
SUBI4
ASGNI4
ADDRLP4 16
INDIRP4
ARGP4
CNSTI4 0
ARGI4
ADDRLP4 4
INDIRI4
CVIU4 4
ARGU4
ADDRGP4 memset
CALLP4
pop
ADDRLP4 44
ADDRLP4 16
INDIRP4
ASGNP4
ADDRLP4 16
ADDRLP4 44
INDIRP4
CNSTI4 4
ADDP4
ASGNP4
ADDRLP4 44
INDIRP4
ADDRLP4 4
INDIRI4
ASGNI4
ADDRLP4 16
INDIRP4
RETP4
ADDRGP4 $60
JUMPV
LABELV $82
CNSTI4 1
ARGI4
ADDRGP4 $84
ARGP4
ADDRFP4 0
INDIRI4
ARGI4
ADDRGP4 Com_Error
CALLV
pop
CNSTP4 0
RETP4
LABELV $60
endproc BG_Alloc 48 12
export BG_Free
proc BG_Free 24 0
ADDRLP4 8
ADDRFP4 0
INDIRP4
ASGNP4
ADDRLP4 8
ADDRLP4 8
INDIRP4
CNSTI4 -4
ADDP4
ASGNP4
ADDRLP4 12
ADDRGP4 freeMem
ASGNP4
ADDRLP4 12
INDIRP4
ADDRLP4 12
INDIRP4
INDIRI4
ADDRLP4 8
INDIRP4
INDIRI4
ADDI4
ASGNI4
ADDRLP4 0
ADDRGP4 freeHead
INDIRP4
ASGNP4
ADDRGP4 $89
JUMPV
LABELV $86
ADDRLP4 4
ADDRLP4 0
INDIRP4
CNSTI4 4
ADDP4
INDIRI4
ADDRLP4 0
INDIRP4
ADDP4
ASGNP4
ADDRLP4 4
INDIRP4
CVPU4 4
ADDRLP4 8
INDIRP4
CVPU4 4
NEU4 $90
ADDRLP4 20
ADDRLP4 0
INDIRP4
CNSTI4 4
ADDP4
ASGNP4
ADDRLP4 20
INDIRP4
ADDRLP4 20
INDIRP4
INDIRI4
ADDRLP4 8
INDIRP4
INDIRI4
ADDI4
ASGNI4
ADDRGP4 $85
JUMPV
LABELV $90
LABELV $87
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 12
ADDP4
INDIRP4
ASGNP4
LABELV $89
ADDRLP4 0
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $86
ADDRLP4 0
ADDRLP4 8
INDIRP4
ASGNP4
ADDRLP4 0
INDIRP4
CNSTI4 4
ADDP4
ADDRLP4 8
INDIRP4
INDIRI4
ASGNI4
ADDRLP4 0
INDIRP4
CNSTU4 3735928383
CVUI4 4
ASGNI4
ADDRLP4 0
INDIRP4
CNSTI4 8
ADDP4
CNSTP4 0
ASGNP4
ADDRLP4 0
INDIRP4
CNSTI4 12
ADDP4
ADDRGP4 freeHead
INDIRP4
ASGNP4
ADDRGP4 freeHead
INDIRP4
CNSTI4 8
ADDP4
ADDRLP4 0
INDIRP4
ASGNP4
ADDRGP4 freeHead
ADDRLP4 0
INDIRP4
ASGNP4
LABELV $85
endproc BG_Free 24 0
export BG_InitMemory
proc BG_InitMemory 4 0
ADDRLP4 0
ADDRGP4 freeHead
ASGNP4
ADDRLP4 0
INDIRP4
ADDRGP4 memoryPool
ASGNP4
ADDRLP4 0
INDIRP4
INDIRP4
CNSTU4 3735928383
CVUI4 4
ASGNI4
ADDRGP4 freeHead
INDIRP4
CNSTI4 4
ADDP4
CNSTI4 1048576
ASGNI4
ADDRGP4 freeHead
INDIRP4
CNSTI4 12
ADDP4
CNSTP4 0
ASGNP4
ADDRGP4 freeHead
INDIRP4
CNSTI4 8
ADDP4
CNSTP4 0
ASGNP4
ADDRGP4 freeMem
CNSTI4 1048576
ASGNI4
LABELV $92
endproc BG_InitMemory 4 0
export BG_DefragmentMemory
proc BG_DefragmentMemory 36 12
ADDRLP4 8
ADDRGP4 freeHead
INDIRP4
ASGNP4
ADDRGP4 $97
JUMPV
LABELV $94
ADDRLP4 4
ADDRLP4 8
INDIRP4
CNSTI4 4
ADDP4
INDIRI4
ADDRLP4 8
INDIRP4
ADDP4
ASGNP4
ADDRLP4 0
ADDRGP4 freeHead
INDIRP4
ASGNP4
ADDRGP4 $101
JUMPV
LABELV $98
ADDRLP4 0
INDIRP4
INDIRI4
CNSTU4 3735928383
CVUI4 4
EQI4 $102
CNSTI4 1
ARGI4
ADDRGP4 $104
ARGP4
ADDRGP4 Com_Error
CALLV
pop
LABELV $102
ADDRLP4 0
INDIRP4
CVPU4 4
ADDRLP4 4
INDIRP4
CVPU4 4
NEU4 $105
ADDRLP4 0
INDIRP4
CNSTI4 8
ADDP4
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $107
ADDRLP4 20
CNSTI4 12
ASGNI4
ADDRLP4 0
INDIRP4
CNSTI4 8
ADDP4
INDIRP4
ADDRLP4 20
INDIRI4
ADDP4
ADDRLP4 0
INDIRP4
ADDRLP4 20
INDIRI4
ADDP4
INDIRP4
ASGNP4
LABELV $107
ADDRLP4 0
INDIRP4
CNSTI4 12
ADDP4
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $109
ADDRLP4 28
CNSTI4 8
ASGNI4
ADDRLP4 32
ADDRLP4 0
INDIRP4
ADDRLP4 28
INDIRI4
ADDP4
INDIRP4
ASGNP4
ADDRLP4 0
INDIRP4
CNSTI4 12
ADDP4
INDIRP4
ADDRLP4 28
INDIRI4
ADDP4
ADDRLP4 32
INDIRP4
ASGNP4
ADDRLP4 32
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $111
ADDRGP4 freeHead
ADDRLP4 0
INDIRP4
CNSTI4 12
ADDP4
INDIRP4
ASGNP4
LABELV $111
LABELV $109
ADDRLP4 24
CNSTI4 4
ASGNI4
ADDRLP4 28
ADDRLP4 8
INDIRP4
ADDRLP4 24
INDIRI4
ADDP4
ASGNP4
ADDRLP4 28
INDIRP4
ADDRLP4 28
INDIRP4
INDIRI4
ADDRLP4 0
INDIRP4
ADDRLP4 24
INDIRI4
ADDP4
INDIRI4
ADDI4
ASGNI4
ADDRLP4 0
INDIRP4
ARGP4
CNSTI4 0
ARGI4
CNSTU4 16
ARGU4
ADDRGP4 memset
CALLP4
pop
ADDRLP4 8
ADDRGP4 freeHead
INDIRP4
ASGNP4
ADDRLP4 32
CNSTP4 0
ASGNP4
ADDRLP4 0
ADDRLP4 32
INDIRP4
ASGNP4
ADDRLP4 4
ADDRLP4 32
INDIRP4
ASGNP4
ADDRGP4 $106
JUMPV
LABELV $105
ADDRLP4 0
ADDRLP4 0
INDIRP4
CNSTI4 12
ADDP4
INDIRP4
ASGNP4
LABELV $106
LABELV $99
LABELV $101
ADDRLP4 0
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $98
ADDRLP4 4
INDIRP4
CVPU4 4
CNSTU4 0
EQU4 $113
ADDRLP4 8
ADDRLP4 8
INDIRP4
CNSTI4 12
ADDP4
INDIRP4
ASGNP4
LABELV $113
LABELV $95
LABELV $97
ADDRLP4 8
INDIRP4
CVPU4 4
CNSTU4 0
NEU4 $94
LABELV $93
endproc BG_DefragmentMemory 36 12
export BG_MemoryInfo
proc BG_MemoryInfo 40 20
ADDRLP4 0
ADDRGP4 memoryPool
ASGNP4
ADDRLP4 12
ADDRGP4 memoryPool+1048576
ASGNP4
ADDRGP4 $117
ARGP4
ADDRLP4 0
INDIRP4
ARGP4
ADDRLP4 12
INDIRP4
ARGP4
ADDRLP4 20
CNSTI4 1048576
ASGNI4
ADDRLP4 20
INDIRI4
ADDRGP4 freeMem
INDIRI4
SUBI4
ARGI4
ADDRLP4 20
INDIRI4
ARGI4
ADDRGP4 Com_Printf
CALLV
pop
ADDRGP4 $119
JUMPV
LABELV $118
ADDRLP4 24
CNSTI4 0
ASGNI4
ADDRLP4 8
ADDRLP4 24
INDIRI4
ASGNI4
ADDRLP4 4
ADDRLP4 24
INDIRI4
ASGNI4
ADDRLP4 16
ADDRLP4 0
INDIRP4
ASGNP4
ADDRGP4 $122
JUMPV
LABELV $121
ADDRLP4 32
ADDRLP4 0
INDIRP4
CNSTI4 4
ADDP4
ASGNP4
ADDRLP4 4
ADDRLP4 4
INDIRI4
ADDRLP4 32
INDIRP4
INDIRI4
ADDI4
ASGNI4
ADDRLP4 8
ADDRLP4 8
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
ADDRLP4 0
ADDRLP4 32
INDIRP4
INDIRI4
ADDRLP4 0
INDIRP4
ADDP4
ASGNP4
LABELV $122
ADDRLP4 0
INDIRP4
CVPU4 4
ADDRLP4 12
INDIRP4
CVPU4 4
GEU4 $124
ADDRLP4 0
INDIRP4
INDIRI4
CNSTU4 3735928383
CVUI4 4
EQI4 $121
LABELV $124
ADDRLP4 4
INDIRI4
CNSTI4 0
EQI4 $125
ADDRGP4 $127
ARGP4
ADDRLP4 16
INDIRP4
ARGP4
ADDRLP4 4
INDIRI4
ARGI4
ADDRLP4 8
INDIRI4
ARGI4
ADDRGP4 Com_Printf
CALLV
pop
LABELV $125
ADDRLP4 32
CNSTI4 0
ASGNI4
ADDRLP4 8
ADDRLP4 32
INDIRI4
ASGNI4
ADDRLP4 4
ADDRLP4 32
INDIRI4
ASGNI4
ADDRLP4 16
ADDRLP4 0
INDIRP4
ASGNP4
ADDRGP4 $129
JUMPV
LABELV $128
ADDRLP4 4
ADDRLP4 4
INDIRI4
ADDRLP4 0
INDIRP4
INDIRI4
ADDI4
ASGNI4
ADDRLP4 8
ADDRLP4 8
INDIRI4
CNSTI4 1
ADDI4
ASGNI4
ADDRLP4 0
ADDRLP4 0
INDIRP4
CVPU4 4
ADDRLP4 0
INDIRP4
INDIRI4
CVIU4 4
ADDU4
CVUP4 4
ASGNP4
LABELV $129
ADDRLP4 0
INDIRP4
CVPU4 4
ADDRLP4 12
INDIRP4
CVPU4 4
GEU4 $131
ADDRLP4 0
INDIRP4
INDIRI4
CNSTU4 3735928383
CVUI4 4
NEI4 $128
LABELV $131
ADDRLP4 4
INDIRI4
CNSTI4 0
EQI4 $132
ADDRGP4 $134
ARGP4
ADDRLP4 16
INDIRP4
ARGP4
ADDRLP4 4
INDIRI4
ARGI4
ADDRLP4 8
INDIRI4
ARGI4
ADDRGP4 Com_Printf
CALLV
pop
LABELV $132
LABELV $119
ADDRLP4 0
INDIRP4
CVPU4 4
ADDRLP4 12
INDIRP4
CVPU4 4
LTU4 $118
LABELV $115
endproc BG_MemoryInfo 40 20
bss
align 4
LABELV freeMem
skip 4
align 4
LABELV freeHead
skip 4
align 1
LABELV memoryPool
skip 1048576
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
LABELV $134
byte 1 32
byte 1 32
byte 1 37
byte 1 112
byte 1 58
byte 1 32
byte 1 37
byte 1 100
byte 1 32
byte 1 98
byte 1 121
byte 1 116
byte 1 101
byte 1 115
byte 1 32
byte 1 97
byte 1 108
byte 1 108
byte 1 111
byte 1 99
byte 1 97
byte 1 116
byte 1 101
byte 1 100
byte 1 32
byte 1 40
byte 1 37
byte 1 100
byte 1 32
byte 1 99
byte 1 104
byte 1 117
byte 1 110
byte 1 107
byte 1 115
byte 1 41
byte 1 10
byte 1 0
align 1
LABELV $127
byte 1 32
byte 1 32
byte 1 37
byte 1 112
byte 1 58
byte 1 32
byte 1 37
byte 1 100
byte 1 32
byte 1 98
byte 1 121
byte 1 116
byte 1 101
byte 1 115
byte 1 32
byte 1 102
byte 1 114
byte 1 101
byte 1 101
byte 1 32
byte 1 40
byte 1 37
byte 1 100
byte 1 32
byte 1 99
byte 1 104
byte 1 117
byte 1 110
byte 1 107
byte 1 115
byte 1 41
byte 1 10
byte 1 0
align 1
LABELV $117
byte 1 37
byte 1 112
byte 1 45
byte 1 37
byte 1 112
byte 1 58
byte 1 32
byte 1 37
byte 1 100
byte 1 32
byte 1 111
byte 1 117
byte 1 116
byte 1 32
byte 1 111
byte 1 102
byte 1 32
byte 1 37
byte 1 100
byte 1 32
byte 1 98
byte 1 121
byte 1 116
byte 1 101
byte 1 115
byte 1 32
byte 1 97
byte 1 108
byte 1 108
byte 1 111
byte 1 99
byte 1 97
byte 1 116
byte 1 101
byte 1 100
byte 1 10
byte 1 0
align 1
LABELV $104
byte 1 66
byte 1 71
byte 1 95
byte 1 68
byte 1 101
byte 1 102
byte 1 114
byte 1 97
byte 1 103
byte 1 109
byte 1 101
byte 1 110
byte 1 116
byte 1 77
byte 1 101
byte 1 109
byte 1 111
byte 1 114
byte 1 121
byte 1 58
byte 1 32
byte 1 77
byte 1 101
byte 1 109
byte 1 111
byte 1 114
byte 1 121
byte 1 32
byte 1 99
byte 1 111
byte 1 114
byte 1 114
byte 1 117
byte 1 112
byte 1 116
byte 1 105
byte 1 111
byte 1 110
byte 1 32
byte 1 100
byte 1 101
byte 1 116
byte 1 101
byte 1 99
byte 1 116
byte 1 101
byte 1 100
byte 1 33
byte 1 10
byte 1 0
align 1
LABELV $84
byte 1 66
byte 1 71
byte 1 95
byte 1 65
byte 1 108
byte 1 108
byte 1 111
byte 1 99
byte 1 58
byte 1 32
byte 1 102
byte 1 97
byte 1 105
byte 1 108
byte 1 101
byte 1 100
byte 1 32
byte 1 111
byte 1 110
byte 1 32
byte 1 97
byte 1 108
byte 1 108
byte 1 111
byte 1 99
byte 1 97
byte 1 116
byte 1 105
byte 1 111
byte 1 110
byte 1 32
byte 1 111
byte 1 102
byte 1 32
byte 1 37
byte 1 105
byte 1 32
byte 1 98
byte 1 121
byte 1 116
byte 1 101
byte 1 115
byte 1 10
byte 1 0
align 1
LABELV $67
byte 1 66
byte 1 71
byte 1 95
byte 1 65
byte 1 108
byte 1 108
byte 1 111
byte 1 99
byte 1 58
byte 1 32
byte 1 77
byte 1 101
byte 1 109
byte 1 111
byte 1 114
byte 1 121
byte 1 32
byte 1 99
byte 1 111
byte 1 114
byte 1 114
byte 1 117
byte 1 112
byte 1 116
byte 1 105
byte 1 111
byte 1 110
byte 1 32
byte 1 100
byte 1 101
byte 1 116
byte 1 101
byte 1 99
byte 1 116
byte 1 101
byte 1 100
byte 1 33
byte 1 10
byte 1 0
