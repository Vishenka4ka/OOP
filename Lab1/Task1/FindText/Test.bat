SET MyProgram="%~1"

REM Защита от запуска без аргумента, задающего путь к программе
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Если отсутствует текст, который нужно искать в файле, то должна произойти ошибка
%MyProgram% MissingFile.txt > nul && goto err
echo Test 1 passed succsessfully

REM Если отсутствует входной файл, то должна произойти ошибка
%MyProgram% > nul && goto err
echo Test 2 passed succsessfully

REM Поиск текста в пустом файле
%MyProgram% EmptyFile.txt "needle" > %TEMP%output.txt || goto err
fc %TEMP%output.txt EmptyFile_results.txt > nul || goto err
echo Test 3 passed succsessfully

REM Поиск текста в файле, в котором содержится только искомый текст
%MyProgram% OnlySearchingTextFile.txt "needle" > %TEMP%output.txt || goto err
fc %TEMP%output.txt OnlySearchingTextFile_results.txt > nul || goto err
echo Test 4 passed succsessfully

REM Поиск текста в файле, в котором не содержится искомого текста
%MyProgram% FileWithoutSearchingText.txt "needle" > %TEMP%output.txt || goto err
fc %TEMP%output.txt FileWithoutSearchingText_results.txt > nul || goto err
echo Test 5 passed succsessfully

REM Поиск текста в одностроковом файле
%MyProgram% SingleLineFile.txt "needle" > %TEMP%output.txt || goto err
fc %TEMP%output.txt SingleLineFile_results.txt > nul || goto err
echo Test 6 passed succsessfully

REM Поиск текста в многостроковом файле
%MyProgram% MultiLineFile.txt "needle" > %TEMP%output.txt || goto err
fc %TEMP%output.txt MultiLineFile_results.txt > nul || goto err
echo Test 7 passed succsessfully

REM Поиск повторяющегося текста в одностроковом файле
%MyProgram% RepeatedTextInLine.txt "needle" > %TEMP%output.txt || goto err
fc %TEMP%output.txt RepeatedTextInLine_results.txt > nul || goto err
echo Test 8 passed succsessfully

REM Поиск пустой строки в файле
%MyProgram% MultiLineFile.txt "" > %TEMP%output.txt && goto err
fc %TEMP%output.txt EmptyStringFile_results.txt > nul || goto err
echo Test 9 passed succsessfully

REM Ошибка в воде имени файла
%MyProgram% MultiLineFileR.txt "needle" > %TEMP%output.txt && goto err
fc %TEMP%output.txt WrongFileName_result.txt > nul || goto err
echo Test 10 passed succsessfully

echo All test passed succsessfully
exit /B 0

:err
echo Test failed
exit /B 1