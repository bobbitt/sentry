@echo off

if .%4 == . goto three
c:\bin\xgrep -n -y "%1 %2 %3 %4" *.c
c:\bin\xgrep -n -y "%1 %2 %3 %4" *.h
goto end
:three

if .%3 == . goto two
c:\bin\xgrep -n -y "%1 %2 %3" *.c
c:\bin\xgrep -n -y "%1 %2 %3" *.h
goto end
:two

if .%2 == . goto one
c:\bin\xgrep -n -y "%1 %2" *.c
c:\bin\xgrep -n -y "%1 %2" *.h
goto end
:one

c:\bin\xgrep -n -y "%1" *.c
c:\bin\xgrep -n -y "%1" *.h

:end
