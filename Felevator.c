#include <windows.h>
#include <locale.h>
#include <stdio.h>

#define ALLOC(memeory)			if(!(memeory)) exit(1)

int WINAPI wWinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hInstPrev, _In_ wchar_t* cmdLine, _In_ int cmdShow)
{
	HANDLE hFind;
	WIN32_FIND_DATAW data;
	size_t pathLen = lstrlenW(cmdLine);
	{
		wchar_t* maskPath = malloc((pathLen + 3) * sizeof(wchar_t));	// Для добавления маски "\*"
		if (!maskPath)
			return 1;
		lstrcpyW(maskPath, cmdLine);
		lstrcatW(maskPath, L"\\*");
		hFind = FindFirstFileExW(maskPath, FindExInfoBasic, &data, FindExSearchLimitToDirectories, 0,
			FIND_FIRST_EX_LARGE_FETCH | FIND_FIRST_EX_CASE_SENSITIVE);
		free(maskPath);
	}
	if (hFind == INVALID_HANDLE_VALUE)	
		return 2;
	wchar_t* oldPath = malloc((pathLen + 2) * sizeof(wchar_t) + sizeof(data.cFileName));	// Для добавления маски "\"
	if(!oldPath)
		return 1;
	wchar_t* newPath = malloc((pathLen + 5) * sizeof(wchar_t) + sizeof(data.cFileName));	// Для добавления маски "\..\"
	if (!newPath)
	{
		free(oldPath);
		return 1;
	}
	do
	{
		if (!lstrcmpW(data.cFileName, L".") || !lstrcmpW(data.cFileName, L".."))
			continue;
		lstrcpyW(oldPath, cmdLine);
		lstrcatW(oldPath, L"\\");
		lstrcatW(oldPath, data.cFileName);
		lstrcpyW(newPath, cmdLine);
		lstrcatW(newPath, L"\\..\\");
		lstrcatW(newPath, data.cFileName);
		MoveFileExW(oldPath, newPath, MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH);
	} while (FindNextFileW(hFind, &data));
	FindClose(hFind);
	free(oldPath);
	free(newPath);
	RemoveDirectoryW(cmdLine);
    return 0;
}

