@echo off
setlocal enabledelayedexpansion

REM --- Settings ---
set OUTPUT=my_program.exe

REM 1. Clear terminal for a fresh look
cls

echo.
echo ===========================================
echo    🔨  CLI AGILE TASK BOARD BUILDER  🔨
echo ===========================================
echo.

REM 2. Clean up old build (Optional but good practice)
if exist "%OUTPUT%" (
    echo 🧹  Removing old %OUTPUT%...
    del "%OUTPUT%"
)

REM 2.5. Ensure data directory exists
echo 📁  Ensuring data directory exists...
if not exist data mkdir data

REM 3. Compilation Step
echo.
echo 🚀  Compiling sources...

REM Note: We are using -x c for sqlite3 to treat it explicitly as C code
REM Compile all .cpp files in src/ directory recursively
g++ src/*.cpp src/core/*.cpp src/ui/*.cpp src/database/*.cpp src/utils/*.cpp -x c lib/sqlite3/sqlite3.c -I include -I include/core -I include/ui -I include/database -I lib/sqlite3 -o "%OUTPUT%"

REM 4. Check Status & Run
if %errorlevel% equ 0 (
    echo.
    echo ===========================================
    echo       ✅  BUILD SUCCESSFUL!  ✅
    echo ===========================================
    echo.
    
    echo ▶️   Starting Application...
    echo -------------------------------------------
    REM Auto-run the program
    "%OUTPUT%"
) else (
    echo.
    echo ===========================================
    echo       ❌  BUILD FAILED!  ❌
    echo ===========================================
    REM Exit with error code so CI/CD pipelines know it failed
    exit /b 1
)