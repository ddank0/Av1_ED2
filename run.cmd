@echo off
setlocal
cd /d %~dp0

if not exist src\bin mkdir src\bin

echo Compilando...
g++ -std=c++17 -O2 -o src\bin\indexador.exe src\main.cpp src\leitor_arquivos.cpp src\avl_tree.cpp src\exclusion_list.cpp || goto :err

if /I "%1"=="--build" (
  echo Build concluido: src\bin\indexador.exe
  exit /b 0
)

echo.
if /I "%1"=="--test" (
  echo Executando teste com tests\queries.txt
  src\bin\indexador.exe data\texto1.txt < tests\queries.txt
) else (
  echo Executando modo interativo
  src\bin\indexador.exe data\texto1.txt
)
exit /b 0

:err
echo Falha na compilacao.
exit /b 1
