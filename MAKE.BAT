@echo off
rem del sentry??.zip
pkzip -ex -wh sentry65 @make.lst
pkzip sentry65 -z < comments.txt
