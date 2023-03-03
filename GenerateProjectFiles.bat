@echo off
setlocal ENABLEDELAYEDEXPANSION
set "UE5=%~dp0Engine\Binaries\DotNET\UnrealBuildTool.exe"
echo "Generating project files..."
"!UE5!" -projectfiles -project="%CD%\"
echo "Project files generated."
pause
