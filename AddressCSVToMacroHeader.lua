--AddressCSVToMacroHeader.lua
--Transforms addresses .csv exported from ghidra to a header file for IHHook using table functionEntries to filter
--TODO convert this to a C# tool or something thats nice to use with strings and can reimplement functionEntries table without much hassle
--and put as a project in the IHHook solution itself and run it as a pre-build step

--REF INPUT DEBUGNOW add
--file .csv

--REF OUTPUT (approx)
--file mgsvtpp_addresses_1_0_15_3_en.h
--std::map<std::string, int64_t> baseAddresses-1_0_15_3_en{
--  {"someFunction", 0x141a08ee0},
--  {"anotherOne", 0x141a08ee0},
--  ...
--};

--REF entry
--{name="<function name>",
--using_default=true,--no address, IHHook is using an actual code implementation
--minimal_hook=true,--a function that's actually currently used by ihhook in a functional way. ie the rest of the addresses can be ignored if you need to get an update out quick by just finding a few addresses.
----SYNC: -^- must update as you use more functions in ihhook, so dont know of approach viablity in long term
--note="some other note",--will append as comment to end of line
--}

--lua api
local functionEntries={
  --lua
  {name="lua_newstate",},
  {name="lua_close",},
  {name="lua_newthread",},

  {name="lua_atpanic",},

  {name="lua_gettop", noAddress="USING_CODE",},
  {name="lua_settop",},
  {name="lua_pushvalue",},
  {name="lua_remove",},
  {name="lua_insert",},
  {name="lua_replace",},
  {name="lua_checkstack",},
  {name="lua_xmove",},

  {name="lua_isnumber",},
  {name="lua_isstring",},
  {name="lua_iscfunction",},
  {name="lua_isuserdata", noAddress="USING_CODE",},
  {name="lua_type",},
  {name="lua_typename", noAddress="USING_CODE",},

  {name="lua_equal", note="tex: lua implementation goes a bit deeper than I'm happy with to use at the moment. No calls in lua distro, so may be hard to find, or have been culled by compilation" },
  {name="lua_rawequal",},
  {name="lua_lessthan",},
  {name="lua_tonumber",},
  {name="lua_tointeger",minimal_hook=true,},
  {name="lua_toboolean",},
  {name="lua_tolstring",minimal_hook=true,},
  {name="lua_objlen",},
  {name="lua_tocfunction",},
  {name="lua_touserdata",},
  {name="lua_tothread",},
  {name="lua_topointer",},

  {name="lua_pushnil",minimal_hook=true,},
  {name="lua_pushnumber",},
  {name="lua_pushinteger",minimal_hook=true,},
  {name="lua_pushlstring",},
  {name="lua_pushstring",minimal_hook=true,},
  {name="lua_pushvfstring",},
  {name="lua_pushfstring",},
  {name="lua_pushcclosure",},
  {name="lua_pushboolean",minimal_hook=true,},
  {name="lua_pushlightuserdata",},
  {name="lua_pushthread",},

  {name="lua_gettable",},
  {name="lua_getfield",minimal_hook=true,},
  {name="lua_rawget",},
  {name="lua_rawgeti",note="via MACRO lua_getref",},
  {name="lua_createtable",minimal_hook=true,},
  {name="lua_newuserdata",},
  {name="lua_getmetatable",},
  {name="lua_getfenv",},

  {name="lua_settable",},
  {name="lua_setfield",minimal_hook=true,},
  {name="lua_rawset",},
  {name="lua_rawseti",minimal_hook=true,},
  {name="lua_setmetatable",},
  {name="lua_setfenv",},

  {name="lua_call",},
  {name="lua_pcall",},
  {name="lua_cpcall",},
  {name="lua_load",},

  {name="lua_dump",},

  {name="lua_yield", noAddress="USING_CODE",},
  {name="lua_resume",},
  {name="lua_status", noAddress="USING_CODE", note="tex DEBUGNOW hmm, address range. ida finds this as sig though, but the prior functions have entries in .pdata which put them in the same range (0x14cdb)",},

  {name="lua_gc",},
  {name="lua_error",},

  {name="lua_next",},
  {name="lua_concat",},

  {name="lua_getallocf", noAddress="NO_USE",note="tex don't really want to mess with allocator function anyway, DEBUGNOW no calls in lua distro, so may be hard to find, or have been culled by compilation" },
  {name="lua_setallocf", noAddress="NO_USE",note="tex don't really want to mess with allocator function anyway"},


  {name="lua_setlevel", noAddress="NO_USE",note="tex: labeled by lua as a hack to be removed in lua 5.2",},

  {name="lua_getstack",},
  {name="lua_getinfo",},
  {name="lua_getlocal",},
  {name="lua_setlocal",},
  {name="lua_getupvalue",},
  {name="lua_setupvalue",},

  {name="lua_sethook",},
  {name="lua_gethook", noAddress="USING_CODE",},
  {name="lua_gethookmask", noAddress="USING_CODE",},
  {name="lua_gethookcount", noAddress="USING_CODE",},
  --lua<


  --lauxlib.h
  {name="luaI_openlib", minimal_hook=true,},
  {name="luaL_register", noAddress="USING_CODE",},
  {name="luaL_getmetafield",},
  {name="luaL_callmeta",},
  {name="luaL_typerror",},
  {name="luaL_argerror",},
  {name="luaL_checklstring",},
  {name="luaL_optlstring",},
  {name="luaL_checknumber",},
  {name="luaL_optnumber", noAddress="USING_CODE",},

  {name="luaL_checkinteger",},
  {name="luaL_optinteger",},

  {name="luaL_checkstack",},
  {name="luaL_checktype",},
  {name="luaL_checkany",},

  {name="luaL_newmetatable",},
  {name="luaL_checkudata",},

  {name="luaL_where",},
  {name="luaL_error",},

  {name="luaL_checkoption",},

  {name="luaL_ref", noAddress="USING_CODE", note="tex: Unsure on this address, see lauxlib_Creathooks CREATE_FUNCPTR(luaL_ref) for more info",},
  {name="luaL_unref", noAddress="USING_CODE",},

  {name="luaL_loadfile",},
  {name="luaL_loadbuffer",},
  {name="luaL_loadstring", noAddress="USING_CODE",},

  {name="luaL_newstate",},

  {name="luaL_gsub",},

  {name="luaL_findtable",},
  --...
  {name="luaL_buffinit", noAddress="USING_CODE",},
  {name="luaL_prepbuffer",},
  {name="luaL_addlstring",},
  {name="luaL_addstring", noAddress="USING_CODE",},
  {name="luaL_addvalue",},
  {name="luaL_pushresult",},
  --lauxlib.h<

  --luaLib.h>
  {name="luaopen_base",},
  {name="luaopen_table",},
  {name="luaopen_io",},
  {name="luaopen_os",},
  {name="luaopen_string",},
  {name="luaopen_math",},
  {name="luaopen_debug",},
  {name="luaopen_package",},
  {name="luaL_openlibs",},
--luaLib.h<

}--functionEntries

local noAddressLegend=[[
// NOT_FOUND - default for a lapi we want to use, and should actually have found the address in prior exes, but aren't in the current exported address list
// NO_USE - something we dont really want to use for whatever reason - TODO addt to getllocf,setallocf, actually give reason why not (dont want to mess with allocator function)
// USING_CODE - using the default lapi code implementation instead of hooking
]]

--enum
local functionNameToEntry={}
for i,entry in ipairs(functionEntries)do
  functionNameToEntry[entry.name]=entry
end

--util
function file_exists(file)
  local f = io.open(file, "rb")
  if f then f:close() end
  return f ~= nil
end

-- get all lines from a file, returns an empty
-- list/table if the file does not exist
function lines_from(file)
  if not file_exists(file) then return {} end
  lines = {}
  for line in io.lines(file) do
    lines[#lines + 1] = line
  end
  return lines
end

function split(s, delimiter)
  local result = {}
  for match in (s..delimiter):gmatch("(.-)"..delimiter) do
    table.insert(result, match)
  end
  return result
end
--util<

--REF input: csv exported by ghidra - functions window > right click > export
--Label Location  Function Signature
--luaX_token2str  141a2d380 thunk undefined luaX_token2str()
--luaX_token2str  14c21d1b0 undefined luaX_token2str()
--..
--read csv
--IN: IO (csvPath)
--OUT:
--{
--  <functionName>={address=address,isThunk=isThunk},
--  ...
--}
function ReadCSV(csvPath)
  print("ReadCSV: "..csvPath)
  local csvEntries={}

  local csvLines=lines_from(csvPath)
  for i=2,#csvLines do--tex skip first line as its column names
    local csvLine=csvLines[i]
    csvLine=csvLine:sub(2,csvLine:len()-1)
    local csvValues=split(csvLine,'","')
    local functionName=csvValues[1]
    local address=csvValues[2]
    local functionSignature=csvValues[3]

    local isThunk=functionSignature:find("thunk")
    --DEBUGNOW thunks will have dupe name, so just leave them out completely for now
    if not isThunk then
      csvEntries[functionName]={address=address}--,isThunk=isThunk}
    end
  end--for csvLines

  return csvEntries
end--ReadCSV

--DEBUGNOW CULL pre addressset header
function ProcessCSVEntriesOld(csvEntries,functionEntries,addrSet)
  local outLines={}
  local notFoundCount=0
  for i,entry in ipairs(functionEntries)do
    local outLine
    --DEBUGNOW is no non-thunk then do we want to use thunk?
    local csvEntry=csvEntries[entry.name]

    --DEBUGNOW just find the missing addresses
    if not csvEntry then
      if not entry.noAddress then
        print(entry.name.." NOT FOUND")
      end
    end

    local address=entry.noAddress and entry.noAddress or "NOT_FOUND" --tex known reason for not having an address
    if csvEntry and not entry.noAddress then
      address="0x"..csvEntry.address
    elseif not entry.noAddress then
      notFoundCount=notFoundCount+1
    end

    outLine='FUNC_DECL_ADDR('..entry.name..', '..address..')'

    if entry.noAddress then
      outLine="//"..outLine --tex comment out
    end

    if address=="NOT_FOUND" then
      outLine="//"..outLine --tex comment out
      outLine=outLine.."//DEBUGNOW NOT_FOUND"
    end

    if entry.minimal_hook then
      outLine=outLine.."//MINIMAL_HOOK "
    end

    if entry.note then
      outLine=outLine.."//"..entry.note
    end

    table.insert(outLines,outLine)
  end

  print(notFoundCount.." addresses out of "..#functionEntries.." missing")--DEBUGNOW

  return outLines
end--ProcessCSVEntriesOld

function ProcessCSVEntries(csvEntries,functionEntries)
  local outLines={}
  local notFoundCount=0
  for i,entry in ipairs(functionEntries)do
    local outLine
    --DEBUGNOW is no non-thunk then do we want to use thunk?
    local csvEntry=csvEntries[entry.name]

    --DEBUGNOW just find the missing addresses
    if not csvEntry then
      if not entry.noAddress then
        print(entry.name.." NOT FOUND")
      end
    end

    local address=entry.noAddress and entry.noAddress or "NOT_FOUND" --tex known reason for not having an address
    if csvEntry and not entry.noAddress then
      address="0x"..csvEntry.address
    elseif not entry.noAddress then
      notFoundCount=notFoundCount+1
    end

    --REF  {"someFunction", 0x141a08ee0},
    outLine='\t\t{\"'..entry.name..'\", '..address..'},'

    if entry.noAddress then
      outLine="//"..outLine --tex comment out
    end

    if address=="NOT_FOUND" then
      outLine="//"..outLine --tex comment out
      outLine=outLine.."//DEBUGNOW NOT_FOUND"
    end

    if entry.minimal_hook then
      outLine=outLine.."//MINIMAL_HOOK "
    end

    if entry.note then
      outLine=outLine.."//"..entry.note
    end

    table.insert(outLines,outLine)
  end

  print(notFoundCount.." addresses out of "..#functionEntries.." missing")--DEBUGNOW

  return outLines
end--ProcessCSVEntriesOld

--write .h file
function WriteH(outLines,hDestPath,header,footer)
  print("WriteH: "..hDestPath)

  --tex inserting to top, so reverse order
  for i=#header,1, -1 do
    table.insert(outLines,1,header[i])
  end
  local outFile=io.open(hDestPath,"w")

  outFile:write(table.concat(outLines,'\n'))
  outFile:write("\n")
  outFile:write(table.concat(footer,'\n'))

  outFile:close()
end--WriteH
--exec>

--DEBUGNOW just using to analyse the address layout
function WriteSortedByAddress(csvEntries,functionEntries,fileName)
  local addresses={}
  for functionName,entry in pairs(csvEntries)do
    table.insert(addresses,entry.address)
  end
  table.sort(addresses)

  local outProcessed={}
  for i,address in ipairs(addresses)do
    for functionName,entry in pairs(csvEntries)do
      if entry.address==address then
        table.insert(outProcessed,{address=address,functionName=functionName})
      end
    end
  end

  local outFile=io.open(fileName,"w")
  for i,entry in ipairs(outProcessed)do
    --outFile:write(entry.address..','..entry.functionName..'\n')
    outFile:write(entry.functionName..','..entry.address..'\n')
  end
  outFile:close()
end--WriteSortedByAddress
--<

--exec>
local exeName="mgsvtpp"

local langs={
  "en",
  "jp",
}

local versions={
  "1_0_15_3",
}

for i,version in ipairs(versions)do
  for j,lang in ipairs(langs)do
    local fileName=exeName.."_adresses_"..version.."_"..lang
    local csvSourcePath=[[D:\GitHub\IHHook\]]..fileName..[[.csv]]
    local hDestPath=[[D:\GitHub\IHHook\IHHook\]]..fileName..[[.h]]

    local header={
      "#pragma once",
      "//GENERATED: by AddressCSVToMacroHeader.lua",
      "//using "..csvSourcePath,
      noAddressLegend,
      "namespace IHHook {",
      "\t"..[[std::map<std::string, int64_t> ]]..fileName..[[{]],
    }
    local footer={
      "\t};//map "..fileName,
      "}//namespace IHHook"
    }

    local csvEntries=ReadCSV(csvSourcePath)
    local outLines=ProcessCSVEntries(csvEntries,functionEntries)
    WriteH(outLines,hDestPath,header,footer)
  end--for langs
end--for versions

--DEBUGNOW
--local fileName=[[D:\GitHub\IHHook\mgstpp-adresses-1.0.15.3--addressSort.csv]]
--WriteSortedByAddress(csvEntries,functionEntries,fileName)
--exec<

