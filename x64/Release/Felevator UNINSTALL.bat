@echo off
powershell -Command "Start-Process cmd -ArgumentList '/c reg delete HKCR\Directory\Shell\Felevator /f' -Verb RunAs"