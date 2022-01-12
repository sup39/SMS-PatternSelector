# SMS Pattern Selector
A practice code that lets you select the pattern of Chain Chomp (PV4) and Chain Chomplets (PV1).
If you are using `NTSC-J 1.0`, you can download the gecko code from
[GCT Extension](https://app.sms.sup39.dev/gct-extension/).
If you have any questions or requests, feel free to contact me via
[Twitter](https://twitter.com/sup39x1207) or [Peing](https://peing.net/en/sup39).

## Build
You can use `build.bat` in
[my version of Super-Mario-Sunshine-C-Kit](https://github.com/sup39/Super-Mario-Sunshine-C-Kit)
to build it.

After building, you have to use `04`/`C2`/`C6` to change the original code.
In `NTSC-J 1.0`, I change the code at:

|Address|At Original Function|Inserted Function|
|:-:|--|--|
|`8024F324`|`TSpineEnemy::goToRandomNextGraphNode`|`(mr r6, r31)`|
|`8024F32C`|`TSpineEnemy::goToRandomNextGraphNode`|`getRandomNextIndex`|
|`800ECE40`|`TMarDirector::direct`|`onSetup`|
|`800F9B74`|`TApplication::gameLoop`|`onUpdate`|
|`8020673C`|`TGCConsole2::perform`|`onDraw2D`|

Note that if you are using other code,
you have to aware of at what addresses are changed by the code.
For example, Shine Get Timer also changes the instruction at `800ECE40`,
and therefore I had to change some parts of code of
both Pattern Selector and Shine Get Timer to make them capable to co-exist.
