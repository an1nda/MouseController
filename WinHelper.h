#pragma once
#include <iostream>
#include <Windows.h>
#include <shellapi.h>

#define WM_TRAYICON		(WM_USER + 1)
#define ID_TRAY_EXIT	1001

extern NOTIFYICONDATA nid;
extern HINSTANCE hin;

/*
* Helper Functions to accomplish a tray icon.
* 
*/
void initTrayIcon(HINSTANCE hinstance, HWND hwnd);
void delTrayIcon();
LRESULT CALLBACK trayWindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

/*
* Helper Functions to create a notification system.
*/
void notif(bool en);