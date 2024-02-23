@echo off
cd /d "%~dp0"

echo Deleting Binaries directory...
rmdir /s /q Binaries

echo Deleting Intermediate directory...
rmdir /s /q Intermediate

echo Deleting Saved directory...
rmdir /s /q Saved

echo Deletion complete.
pause
