@echo off
echo 🔧 Compilation du projet Pong avec menu...

:: Chemin vers g++ MSYS2 UCRT64
set COMPILER=C:\msys64\ucrt64\bin\g++.exe

:: Commande de compilation
%COMPILER% main.cpp menu.cpp pong.cpp ^
 -IC:/msys64/ucrt64/include ^
 -LC:/msys64/ucrt64/lib ^
 -lsfml-graphics -lsfml-window -lsfml-system ^
 -o mon_jeu.exe

:: Vérifie si la compilation a réussi
IF EXIST mon_jeu.exe (
    echo ✅ Compilation réussie !
) ELSE (
    echo ❌ Erreur lors de la compilation.
)

pause
