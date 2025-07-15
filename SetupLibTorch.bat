@echo off
echo Setting up LibTorch for Lava Engine...
echo.

:: Create vendor directory for LibTorch if it doesn't exist
if not exist "Lava\vendor\libtorch" (
    mkdir "Lava\vendor\libtorch"
)

echo LibTorch Setup Instructions:
echo.
echo 1. Go to https://pytorch.org/get-started/locally/
echo 2. Select:
echo    - PyTorch Build: Stable
echo    - Your OS: Windows
echo    - Package: LibTorch
echo    - Language: C++/Java
echo    - Compute Platform: CPU (or CUDA if you have NVIDIA GPU)
echo.
echo 3. Download the Release version (not Debug)
echo 4. Extract the downloaded zip file
echo 5. Copy the contents to: Lava\vendor\libtorch\
echo.
echo The folder structure should look like:
echo   Lava\vendor\libtorch\
echo   ├── include\
echo   ├── lib\
echo   └── share\
echo.
echo After setup, run: GenerateProject.bat

pause
