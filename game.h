#pragma once

class CGame {
public:
	class CSysModule;

private:
	void* m_table;

public:
	bool        m_bExternallySuppliedWindow;
	HWND        m_hWindow;
	HINSTANCE   m_hInstance;
	WNDPROC	    m_ChainedWindowProc;
	int	        m_x;
	int	        m_y;
	int	        m_width;
	int	        m_height;
	bool        m_bActiveApp;
	CSysModule* m_hUnicodeModule;
	int	        m_iDesktopWidth, m_iDesktopHeight, m_iDesktopRefreshRate;
	RECT        m_rcLastRestoredClientRect;
};