set gamePath=C:\Games\Steam\steamapps\common\MGS_TPP
set proxyName=dinput8.dll
set targetDir=%~1
set targetFile=%~2
echo copytogame.bat
rem echo "%targetDir%"
rem echo "%targetFile%"
rem echo "%gamePath%"
echo copy "%targetDir%%targetFile%" "%gamePath%\%proxyName%"
copy /y /b "%targetDir%%targetFile%" "%gamePath%\%proxyName%"