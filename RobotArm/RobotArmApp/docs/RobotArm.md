<title>RobotArm Component Dictionary</title>
# RobotArm Component Dictionary


## Command List

|Mnemonic|ID|Description|Arg Name|Arg Type|Comment
|---|---|---|---|---|---|
|SET_Arm_Angle|0 (0x0)|Set arm angle| | |
| | | |angle|F32|Arm angle|
|SET_Base_Angle|1 (0x1)|Set base angle| | |
| | | |angle|F32|Base angle|
|SET_Height_Angle|2 (0x2)|Set height angle| | |
| | | |angle|F32|Angle to send|
|SET_Length_Angle|3 (0x3)|Set length angle| | |
| | | |angle|F32|Angle to send|

## Telemetry Channel List

|Channel Name|ID|Type|Description|
|---|---|---|---|
|Arm_Angle|0 (0x0)|F32||
|Base_Angle|1 (0x1)|F32||
|Height_Angle|2 (0x2)|F32||
|Length_Angle|3 (0x3)|F32||
|Sched_Cycles|4 (0x4)|I32||

## Event List

|Event Name|ID|Description|Arg Name|Arg Type|Arg Size|Description
|---|---|---|---|---|---|---|
|Sent_Arm_Angle|0 (0x0)|Sent arm angle| | | | |
| | | |angle|F32||The angle|
|Sent_Base_Angle|1 (0x1)|Sent base angle| | | | |
| | | |angle|F32||The angle|
|Sent_Height_Angle|2 (0x2)|Sent height angle| | | | |
| | | |angle|F32||The angle|
|Sent_Length_Angle|3 (0x3)|Sent length angle| | | | |
| | | |angle|F32||The angle|
