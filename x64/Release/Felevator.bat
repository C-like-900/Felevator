@echo off
chcp 1251
IF %1 == install (
reg add "HKCR\Directory\Shell\Felevator" /t REG_SZ /d "Извлечь содержимое"
reg add "HKCR\Directory\Shell\Felevator\command" /t REG_SZ /d "%~dp0Felevator.exe %%1"
)
IF %1 == uninstall (
reg delete "HKCR\Directory\Shell\Felevator" /f
)
