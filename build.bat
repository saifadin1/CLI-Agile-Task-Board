@echo off
cls

echo ==========================================
echo    CLI AGILE TASK BOARD BUILDER
echo ==========================================
echo.

REM Clean up old build
if exist my_program.exe (
    echo Removing old my_program.exe...
    del my_program.exe
)

REM Ensure data directory exists
if not exist data mkdir data
echo Data directory ready.

echo.
echo Compiling sources...
echo.

REM Compile all source files
g++ src/main.cpp src/core/Board.cpp src/core/Task.cpp src/core/User.cpp src/database/DatabaseManager.cpp src/database/DatabaseSeeder.cpp src/database/TaskDAO.cpp src/utils/ANSIhelpers.cpp -x c lib/sqlite3/sqlite3.c -I include -I include/core -I include/database -I lib/sqlite3 -o my_program.exe

REM Check if compilation was successful
if %errorlevel% equ 0 (
    echo.
    echo ==========================================
    echo       BUILD SUCCESSFUL!
    echo ==========================================
    echo.
    echo Starting Application...
    echo ------------------------------------------
    my_program.exe
) else (
    echo.
    echo ==========================================
    echo       BUILD FAILED!
    echo ==========================================
    echo.
    echo Check the error messages above.
    pause
)