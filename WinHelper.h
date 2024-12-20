#pragma once
#include <iostream>
#include <Windows.h>
#include <shellapi.h>

#define WM_TRAYICON (WM_USER + 1)

extern NOTIFYICONDATA nid;

/*
* Helper Functions to accomplish a tray icon.
* 
*/
void ShowTrayIcon(HINSTANCE hin, HWND hwnd);
void RemoveTrayIcon();
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
int APIENTRY wWinMain(HINSTANCE hin, HINSTANCE prevhin, LPWSTR lpCmdLine, int nCmdShow);


/*
* Helper Functions to create a notification system.
*/
void notif(bool en);