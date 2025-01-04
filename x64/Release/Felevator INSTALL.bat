@echo off
chcp 1251
powershell -Command "Start-Process cmd -ArgumentList '/c reg add HKCR\Directory\Shell\Felevator /t REG_SZ /d \"Извлечь содержимое\" & reg add HKCR\Directory\Shell\Felevator\command /t REG_SZ /d \"%~dp0Felevator.exe %%1\"' -Verb RunAs"