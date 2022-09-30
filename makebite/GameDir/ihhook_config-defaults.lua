--ihhook_config-defaults.lua
--ihhook_config lets you set some start up values for ihhoook
--Currently for debug/development options, nothing the average user needs to bother with.
--This file the defaults/example for ihhook_config
--Rename to ihhook_config.lua to use
--Should be in same folder as ihhook/dinput8 dll
--Even though this is .lua, IHHook has a bespoke and fragile parsing method for this file rather than an actual lua loader
--So stick close to the provided format - dont move the brackets, dont put any spaces before/after the = 
local this={
	debugMode=true,
	openConsole=false,
	enableCityHook=false,--log cityhash calls, which underly strcode functions
	enableFnvHook=false,--log fnvhash
	logFileLoad=false,
	forceUsePatterns=false,
	logFoxStringCreateInPlace=false,
	logTime=false,--prefix |time| before log. time is good for figuring out how long between steps, but makes it harder to compare similar logs.
}--this
return this