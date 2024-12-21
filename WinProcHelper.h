#pragma once
#include <iostream>
#include <Windows.h>
#include <shellapi.h>

#define WM_TRAYICON			(WM_USER + 1)

extern NOTIFYICONDATA nid;
extern HINSTANCE hin;

extern int sens;

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


void saveSens(int sens);
int loadSens();