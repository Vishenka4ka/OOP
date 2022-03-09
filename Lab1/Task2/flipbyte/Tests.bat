SET MyProgram="%~1"

if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Если нет аргументов, то должна произойти ошибка
%MyProgram% > %TEMP%output.txt && goto err
fc %TEMP%output.txt NoArguments_result.txt > nul || goto err
echo Test 1 passed succsessfuly

REM Если аргумент, задающий число - пустая строкой
%MyProgram% "" > %TEMP%output.txt && goto err
fc %TEMP%output.txt NumberIsEmpty_result.txt > nul || goto err
echo Test 2 passed succsessfuly

REM Если число задано не в 10-тиричной системе счисления
%MyProgram% "2f6" > %TEMP%output.txt && goto err
fc %TEMP%output.txt NumberInWrongNotation_result.txt > nul || goto err
echo Test 3 passed succsessfuly

REM Если заданное число выходит за пределы диапазона от 0 до 255
%MyProgram% "256" > %TEMP%output.txt && goto err
fc %TEMP%output.txt NumberInWrongRange_result.txt > nul || goto err
echo Test 4 passed succsessfuly

REM Если число задано корректно
%MyProgram% "6" > %TEMP%output.txt || goto err
fc %TEMP%output.txt FirstByte_result.txt > nul || goto err
echo Test 5 passed succsessfuly

REM Если число задано корректно
%MyProgram% "158" > %TEMP%output.txt || goto err
fc %TEMP%output.txt SecondByte_result.txt > nul || goto err
echo Test 6 passed succsessfuly

REM Если число отрицательное (выходит за пределы диапазона)
%MyProgram% "-1" > %TEMP%output.txt && goto err
fc %TEMP%output.txt NumberInWrongRange_result.txt > nul || goto err
echo Test 7 passed succsessfuly

echo All test passed succsessfuly
exit /B 0

:err
echo Test failed
exit /B 1