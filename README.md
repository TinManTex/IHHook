# IHHook
Version r17 - 2022-07-02 (see github for full changes)  
FoxString hook.  
Bunch of character, buddy, vehicle change hooks.  
ihhook_config.lua (next to ihhook/dinput8 dll) - allows some startup settings of ihhook to be set.  
FNV Hash logging.  
Ghidra scripts to export addresses, func defs, and a refactor and reduction of required steps to get hooks running.  

For MGSV version 1.15 (in title screen), 1.0.15.3 in exe  
For Infinite Heaven r257  

Previously bundled with Infinite Heaven, IHHook has been split into a seperate install and nexus page to isolate feedback and issues.

IHHook source: https://github.com/TinManTex/IHHook
IHHook mod: https://www.nexusmods.com/metalgearsolidvtpp/mods/1226
Infinite Heaven mod: https://www.nexusmods.com/metalgearsolidvtpp/mods/45

## Description 
A proxy dll (of dinput8.dll) that loads with MGSV to provide extended features for modding.


## Dependencies
### Runtime
Microsoft Visual C++ Redistributable for Visual Studio, x64  
https://aka.ms/vs/17/release/VC_redist.x64.exe 

### Development
MSVS v141 - VS 2017 C++ x64/x86 build tools (v14.16)  
Windows 10 SDK (10.0.17763.0)  
(Install via Visual Studio Installer > Individual Components)  

## IHHook features
See this youtube playlist for features that are visually demonstratable  
https://www.youtube.com/playlist?list=PLSKlVTXYh6F9XCIpHUGTSkd9gDzoU6N1s

dear-IMGUI based menu for Infinite Heaven.  
[youtube]ERL7okZVcW4[/youtube]  
https://youtu.be/ERL7okZVcW4

Lua C API support (mostly complete)  
Allows extending the MGSVs embedded lua via C.  
Does not have dynamic library support as mgsv lua is statically compiled, and running the mgsv lua state through a seperate distro of lua isn't desirable since the mgsv lua core is modified from default.  
However it is possible to compile lua C modules into IHHook.  


Logging via spdlog.  
Infinite Heaven uses this for better performance (mostly used for debugging)  
Has it's own seperate log for debug/info output.  


Named Pipe server: Starts up a threaded Named Pipe server with two pipes mgsv_in, mgsv_out.  
Currently used by Infinite Heaven to improve performance when using IHExt and should open further posibilities I was reluctant to persue due to old text file based IH>IHExt communication.  


CityHash logging (currently has to be compiled in with a #define) using emooses cityhash logging (though using spdlog for better performance) that IHHook was initially built off.  


RawInput keyboard processing and blocking (proof of concept)  

## Further info
See IHHHook.h for some comments about the project.

## Thanks
zip for making me smooth out the release process, sorry about taking so long.
sai for mentioning what he had done with ghidra which helped me get past a few hurdles to start finding MGSVs lua functions.  
emoose for CityHook which provided a base to start IHHook from.