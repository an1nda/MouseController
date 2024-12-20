#pragma once
#include <iostream>
#include <Windows.h>
#include <Xinput.h>

/*
* Helper Functions to accomplish Controller input to
* mouse/keyboard translations.
* 
*/
int convert(SHORT a, int b);
void mouseMove(int dx, int dy);
void mouseScroll(int dy);
void handleButton(UINT XINPUT_MASK, bool is, bool* was);


