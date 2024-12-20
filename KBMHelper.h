#pragma once
#include <iostream>
#include <Windows.h>
#include <Xinput.h>

#define KEY_HOLD	0x01
#define KEY_RELEASE	0x02

/*
* Helper Functions to accomplish Controller input to
* mouse/keyboard translations.
* 
*/
int convert(SHORT a, int b);
void mouseMove(int dx, int dy);
void mouseScroll(int dy);
void handleButton(UINT XINPUT_MASK, bool is, bool* was);
void simulateKeyPress(BYTE type, BYTE key);