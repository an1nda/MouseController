#include "WinHelper.h"

NOTIFYICONDATA nid = { 0 };
HINSTANCE hin = nullptr;

void notif(bool en) {
	nid.uFlags |= NIF_INFO;
	wcscpy_s(nid.szInfoTitle, L"MouseController");
	wcscpy_s(nid.szInfo, 
		(en ? L"MouseController Enabled!" : L"MouseController Disabled!"));
	nid.dwInfoFlags = NIIF_INFO;

	Shell_NotifyIcon(NIM_MODIFY, &nid);
}

void initTrayIcon(HINSTANCE hinstance, HWND hwnd) {
	hin = hinstance;

	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = hwnd;
	nid.uID = 1;
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	nid.uCallbackMessage = WM_TRAYICON;
	nid.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	wcscpy_s(nid.szTip, L"MouseController");

	Shell_NotifyIcon(NIM_ADD, &nid);
}

void delTrayIcon() {
	Shell_NotifyIcon(NIM_DELETE, &nid);
}

LRESULT CALLBACK trayWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_TRAYICON:
		if (LOWORD(lparam) == WM_RBUTTONUP) {
			POINT pt;
			GetCursorPos(&pt);
			HMENU hmenu = CreatePopupMenu();
			AppendMenu(hmenu, MF_STRING, ID_TRAY_EXIT, L"Close");
			SetForegroundWindow(hwnd);
			int cmd = TrackPopupMenu(hmenu, TPM_RETURNCMD | TPM_NONOTIFY, pt.x, pt.y, 0, hwnd, NULL);
			DestroyMenu(hmenu);

			if (cmd == ID_TRAY_EXIT) {
				PostQuitMessage(0);
			}
		}
		break;

	case WM_DESTROY:
		delTrayIcon();
		PostQuitMessage(0);
		break;
		
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return 0;
}