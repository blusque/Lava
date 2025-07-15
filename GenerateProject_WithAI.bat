@echo off
echo Building Lava Engine WITH AI features (LibTorch + CUDA)...
echo.

:: Check if LibTorch exists
if not exist "Lava\vendor\libtorch\lib" (
    echo ERROR: LibTorch not found!
    echo Please extract LibTorch to Lava\vendor\libtorch\
    echo.
    echo Download from: https://pytorch.org/get-started/locally/
    echo Select: Windows, LibTorch, C++/Java, CUDA 11.8
    echo.
    pause
    exit /b 1
)

:: Generate project files with AI support
vendor\premake\premake5.exe vs2022 --with-ai

echo.
echo Project files generated successfully!
echo AI features are ENABLED in this build with:
echo   - LibTorch C++ API
echo   - CUDA 11.8 support
echo   - Neural Animation (PFNN)
echo   - AI Content Generation (AIGC)
echo   - Motion Capture
echo.
echo Open Lava.sln in Visual Studio to build the engine.
echo.
pause
