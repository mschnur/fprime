<title>ServoComponent Component Dictionary</title>
# ServoComponent Component Dictionary


## Command List

|Mnemonic|ID|Description|Arg Name|Arg Type|Comment
|---|---|---|---|---|---|
|SVO_SETANG|0 (0x0)|Servo angle set command from app| | |
| | | |angle|F32|Input angle from command|
|SVO_DISABLE|1 (0x1)|Command to disable the servo| | |
|SVO_ENABLE|2 (0x2)|Command to enable the servo| | |

## Telemetry Channel List

|Channel Name|ID|Type|Description|
|---|---|---|---|
|SVO_Angle|0 (0x0)|F32|Command angle for servo|
|SVO_Register|1 (0x1)|U16|Register value of servo|

## Event List

|Event Name|ID|Description|Arg Name|Arg Type|Arg Size|Description
|---|---|---|---|---|---|---|
|SVO_AngleChange|0 (0x0)|Angle Change of Servo| | | | |
| | | |initAngle|F32||the initial angle|
| | | |nextAngle|F32||the next angle|
