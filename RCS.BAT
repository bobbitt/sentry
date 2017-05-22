@echo off
for %%f in (*.h) do ci -r%1 %%f
for %%f in (*.c) do ci -r%1 %%f
for %%f in (rcs\*.h) do echo co -l %%f
for %%f in (rcs\*.c) do echo co -l %%f
