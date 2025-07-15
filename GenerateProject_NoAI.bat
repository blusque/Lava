@echo off
echo Building Lava Engine WITHOUT AI features...
echo.

:: Generate project files without AI support
vendor\premake\premake5.exe vs2022

echo.
echo Project files generated successfully!
echo AI features are DISABLED in this build.
echo.
echo Open Lava.sln in Visual Studio to build the engine.
echo.
pause
