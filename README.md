# IHHook 
A proxy dll (of dinput8.dll) that loads with MGSV to provide extended features for modding.

## Dependancies
Microsoft Visual C++ Redistributable for Visual Studio 2019, x64  
Dowload from Other tools and Frameworks:  
https://visualstudio.microsoft.com/downloads/  
(The current redistributable now supports VC 2015,2017 and 2019 in one package).  

## IHHook features
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
sai for mentioning what he had done with ghidra which helped me get past a few hurdles to start finding MGSVs lua functions.  
emoose for CityHook which provided a base to start IHHook from.