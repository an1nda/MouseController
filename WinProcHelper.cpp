#include "WinProcHelper.h"
#include "resource.h"
#include <fstream>
#include <CommCtrl.h>

NOTIFYICONDATA nid = { 0 };
HINSTANCE hin = nullptr;

void saveSens(int sens) {
	HKEY hkey;
	if (RegCreateKeyEx(HKEY_CURRENT_USER, L"Software\\MouseController", 0, NULL, 0, KEY_SET_VALUE, NULL, &hkey, NULL) == ERROR_SUCCESS) {
		RegSetValueEx(hkey, L"Sensitivity", 0, REG_DWORD, (const BYTE*)&sens, sizeof(sens));
		RegCloseKey(hkey);
	}
}

int loadSens() {
	HKEY hkey;
	int temp = 17;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\MouseController", 0, KEY_READ, &hkey) == ERROR_SUCCESS) {
		DWORD dataSize = sizeof(temp);
		if (RegQueryValueEx(hkey, L"Sensitivity", NULL, NULL, (LPBYTE)&temp, &dataSize) != ERROR_SUCCESS) {
			temp = 17;  // Use default if no value exists
		}
		RegCloseKey(hkey);
	}
	return temp;
}

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
	nid.hIcon = LoadIcon(hin, MAKEINTRESOURCE(IDI_ICON2));

	wcscpy_s(nid.szTip, L"MouseController");

	Shell_NotifyIcon(NIM_ADD, &nid);
}

void delTrayIcon() {
	Shell_NotifyIcon(NIM_DELETE, &nid);
}


INT_PTR CALLBACK SensDialogProc(HWND hdlg, UINT message, WPARAM wparam, LPARAM lparam) {
	static HWND hslider;

	switch (message) {
	case WM_INITDIALOG:
		hslider = GetDlgItem(hdlg, IDC_SLIDER_SENS);

		SendMessage(hslider, TBM_SETRANGE, TRUE, MAKELONG(5, 50));
		SendMessage(hslider, TBM_SETPOS, TRUE, sens);

		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wparam) == IDOK) {
			sens = (int)SendMessage(hslider, TBM_GETPOS, 0, 0);
			saveSens(sens);

			EndDialog(hdlg, LOWORD(wparam));
			return TRUE;
		}
		break;
	}

	return FALSE;
}

LRESULT CALLBACK trayWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_TRAYICON:
		if (LOWORD(lparam) == WM_RBUTTONUP) {
			POINT pt;
			GetCursorPos(&pt);
			HMENU hmenu = CreatePopupMenu();

			AppendMenu(hmenu, MF_STRING, ID_TRAY_SENS_ADJ, L"Adjust Sens");
			AppendMenu(hmenu, MF_STRING, ID_TRAY_EXIT, L"Close");

			SetForegroundWindow(hwnd);
			int cmd = TrackPopupMenu(hmenu, TPM_RETURNCMD | TPM_NONOTIFY, pt.x, pt.y, 0, hwnd, NULL);
			DestroyMenu(hmenu);

			if (cmd == ID_TRAY_SENS_ADJ) {
				if (DialogBox(hin, MAKEINTRESOURCE(IDD_SENS_DLG), hwnd, SensDialogProc) == -1) {
					DWORD dwError = GetLastError();
					MessageBox(hwnd, L"Failed. Error 3.", L"Error", MB_OK | MB_ICONERROR);
				}
			} else if (cmd == ID_TRAY_EXIT) {
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