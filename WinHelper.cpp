#include "WinHelper.h"

void notif(bool en) {
	nid.uFlags = NIF_INFO;
	wcscpy_s(nid.szInfo, L"MouseController");
	wcscpy_s(nid.szInfo, 
		(en ? L"MouseController Enabled!" : L"MouseController Disabled!"));
	nid.dwInfoFlags = NIIF_INFO;

	Shell_NotifyIcon(NIM_MODIFY, &nid);
}

void ShowTrayIcon(HINSTANCE hin, HWND hwnd) {

}
void RemoveTrayIcon() {

}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	return 0;
}
int APIENTRY wWinMain(HINSTANCE hin, HINSTANCE prevhin, LPWSTR lpCmdLine, int nCmdShow) {
	return 0;
}
