#pragma once

#include <Windows.h>

class WinAPI {
public:
	using VirtualQuery_t        = SIZE_T( __stdcall* )( LPCVOID, PMEMORY_BASIC_INFORMATION, SIZE_T );
	using SetWindowLongA_t      = LONG( __stdcall* )( HWND, int, LONG );
	using GetTickCount_t        = LONG( __stdcall* )( );
	using CallWindowProcA_t     = LONG( __stdcall* )( WNDPROC, HWND, UINT, WPARAM, LPARAM );
	using MultiByteToWideChar_t = int( __stdcall* )( UINT, DWORD, LPCCH, int, LPWSTR, int );
	using WideCharToMultiByte_t = int( __stdcall* )( UINT, DWORD, LPCWCH, int, LPSTR, int, LPCCH, LPBOOL );
	using VirtualProtect_t      = BOOL( __stdcall* )( LPVOID, SIZE_T, DWORD, PDWORD );
	using SHGetFolderPathA_t    = HRESULT( __stdcall* )( HWND, int, HANDLE, DWORD, LPTSTR );
	using CreateDirectoryA_t    = BOOL( __stdcall* )( LPCSTR, LPSECURITY_ATTRIBUTES );
	using PathAppendA_t         = BOOL( __stdcall* )( LPSTR, LPCSTR );

	VirtualQuery_t		  VirtualQuery;
	SetWindowLongA_t	  SetWindowLongA;
	GetTickCount_t		  GetTickCount;
	CallWindowProcA_t	  CallWindowProcA;
	MultiByteToWideChar_t MultiByteToWideChar;
	WideCharToMultiByte_t WideCharToMultiByte;
	VirtualProtect_t      VirtualProtect;
	SHGetFolderPathA_t    SHGetFolderPathA;
	CreateDirectoryA_t    CreateDirectoryA;
	PathAppendA_t         PathAppendA;
};

extern WinAPI g_winapi;