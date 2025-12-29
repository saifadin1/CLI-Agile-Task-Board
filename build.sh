#!/bin/bash

# --- 🎨 Colors & Formatting ---
BOLD='\033[1m'
GREEN='\033[1;32m'
RED='\033[1;31m'
CYAN='\033[1;36m'
YELLOW='\033[1;33m'
RESET='\033[0m'

# --- ⚙️  Settings ---
OUTPUT="my_program.exe"

# 1. Clear terminal for a fresh look
clear

echo -e "${CYAN}"
echo "==========================================="
echo "   🔨  CLI AGILE TASK BOARD BUILDER  🔨"
echo "===========================================${RESET}"
echo ""

# 2. Clean up old build (Optional but good practice)
if [ -f "$OUTPUT" ]; then
    echo -e "${YELLOW}🧹  Removing old $OUTPUT...${RESET}"
    rm "$OUTPUT"
fi

# 2.5. Ensure data directory exists
echo -e "${CYAN}📁  Ensuring data directory exists...${RESET}"
mkdir -p data

# 3. Compilation Step
echo -e "${BOLD}🚀  Compiling sources...${RESET}"

# Note: We are using -x c for sqlite3 to treat it explicitly as C code
# Compile all .cpp files in src/ directory recursively
g++ src/*.cpp \
    src/core/*.cpp \
    src/ui/*.cpp \
    src/database/*.cpp \
    -x c lib/sqlite3/sqlite3.c \
    -I include \
    -I include/core \
    -I include/ui \
    -I include/database \
    -I lib/sqlite3 \
    -o "$OUTPUT"

# 4. Check Status & Run
if [ $? -eq 0 ]; then
    echo ""
    echo -e "${GREEN}===========================================${RESET}"
    echo -e "${GREEN}      ✅  BUILD SUCCESSFUL!  ✅${RESET}"
    echo -e "${GREEN}===========================================${RESET}"
    echo ""
    
    echo -e "${CYAN}▶️   Starting Application...${RESET}"
    echo "-------------------------------------------"
    # Auto-run the program
    ./"$OUTPUT"
else
    echo ""
    echo -e "${RED}===========================================${RESET}"
    echo -e "${RED}      ❌  BUILD FAILED!  ❌${RESET}"
    echo -e "${RED}===========================================${RESET}"
    # Exit with error code so CI/CD pipelines know it failed
    exit 1
fi