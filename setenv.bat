@echo off
:: Get the full path of the directory where the script is located, including the trailing backslash
SET "SCRIPT_DIR=%~dp0"
:: Normalize the path to remove the trailing backslash
SET "SCRIPT_DIR=%SCRIPT_DIR:~0,-1%"
:: Get the parent directory
FOR %%I IN ("%SCRIPT_DIR%") DO SET "PARENT_DIR=%%~dpI"
:: No need to remove the trailing backslash from PARENT_DIR for setting environment variables
SET "SPACE_EDITOR_DIR=%PARENT_DIR%"
:: Optional: Display SPACE_EDITOR_DIR for verification
echo SPACE_EDITOR_DIR=%SPACE_EDITOR_DIR%