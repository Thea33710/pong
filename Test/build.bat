@echo off
echo 🔧 Compilation du projet Pong avec menu...

:: Chemin vers g++ MSYS2 UCRT64
set COMPILER=C:\msys64\ucrt64\bin\g++.exe

:: Compilation
%COMPILER% main.cpp menu.cpp pong.cpp ^
 -IC:/msys64/ucrt64/include ^
 -LC:/msys64/ucrt64/lib ^
 -lsfml-graphics -lsfml-window -lsfml-system ^
 -o mon_jeu.exe

:: Vérifie si la compilation a réussi
if %errorlevel% neq 0 (
    echo ❌ Échec de la compilation.
    pause
    exit /b %errorlevel%
)

echo ✅ Compilation réussie. Lancement du jeu...
start mon_jeu.exe
