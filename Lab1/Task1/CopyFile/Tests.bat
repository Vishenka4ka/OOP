@echo off 

REM Путь к тестируемой программе передается через 1-й аргумент комнадной строки
SET MyProgram="%~1"

REM Защита от запуска без аргумента, задающего путь к программе
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Copy empty file
%MyProgram% Empty.txt "%TEMP%\output.txt" || goto err
fc Empty.txt "%TEMP%\output.txt" > nul || goto err	
echo Test 1 passed succsessfully

REM Copy non empty file
%MyProgram% NonEmptyFile.txt "%TEMP%\output.txt" || goto err
fc NonEmptyFile.txt "%TEMP%\output.txt" > nul || goto err	
echo Test 2 passed succsessfully

REM Copy nmissing file should fail
%MyProgram% MissingFile.txt "%TEMP%\output.txt" > nul && goto err
echo Test 3 passed succsessfully

REM If output file is not specified, program must fail
%MyProgram% MissingFile.txt > nul && goto err
echo Test 4 passed succsessfully

REM If input and output files are not specified, program must fail
%MyProgram% > nul && goto err
echo Test 5 passed succsessfully

REM Tests passed succsessfully
echo All test passed succsessfully
exit /B 0

REM In case of error
:err
echo Test failed
exit /B 1