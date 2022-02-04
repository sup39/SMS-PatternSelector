# SMS Pattern Selector
A practice code that lets you select the pattern of Chain Chomp (PV4) and Chain Chomplets (PV1).
If you are using `NTSC-J 1.0`, you can download the gecko code from
[GCT Extension](https://app.sms.sup39.dev/gct-extension/).

## Build
You can use `build.bat` in
[my version of Super-Mario-Sunshine-C-Kit](https://github.com/sup39/Super-Mario-Sunshine-C-Kit)
to build it.

In `NTSC-J 1.0`, I insert the functions at:

|Address|At Original Function|Inserted Function|
|:-:|--|--|
|`8024F324`|`TSpineEnemy::goToRandomNextGraphNode`|`(mr r6, r31)`|
|`8024F32C`|`TSpineEnemy::goToRandomNextGraphNode`|`getRandomNextIndex`|
|`8020675C`|`TGCConsole2::perform`|`onDraw2D`|
|`8010E418`|`TMarDirector::direct`|`setup`(draw.c)|
