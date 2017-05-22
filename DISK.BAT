@echo off
label a: sentry_v65
pkunzip -d sentry65.zip a:
copy sentry65.zip a:
md a:\share
copy share\sentry65.zip a:\share
echo.
echo Now write-protect the disk.
echo.
