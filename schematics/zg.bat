ECHO OFF

set PROJ_NAME=gcsc_ii
mkdir .\gerbers
del /Q .\gerbers\*.*

REM set hr=%hr: =0%
set hr=%time:~0,2%
if "%hr:~0,1%" equ " " set hr=0%hr:~1,1%

set TIMESTAMP=%date:~-4,4%%date:~-10,2%%date:~-7,2%_%hr%%time:~3,2%%time:~6,2%
set FNAME=%PROJ_NAME%_gerbers_%TIMESTAMP%.zip
echo Timestamp: '%TIMESTAMP%'
echo Filename: '%FNAME%'

:MOVE
move %PROJ_NAME%.gtl .\gerbers
move %PROJ_NAME%.gbl .\gerbers
move %PROJ_NAME%.gts .\gerbers
move %PROJ_NAME%.gbs .\gerbers
move %PROJ_NAME%.gtp .\gerbers
move %PROJ_NAME%.gbp .\gerbers
move %PROJ_NAME%.gto .\gerbers
move %PROJ_NAME%.gbo .\gerbers
move %PROJ_NAME%.gp2 .\gerbers
move %PROJ_NAME%.gp3 .\gerbers
move %PROJ_NAME%.txt .\gerbers

:ZIP
zip -j .\gerbers\%FNAME% .\gerbers\*.*

:END
