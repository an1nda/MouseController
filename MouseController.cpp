// MouseController.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <Xinput.h>
#include <shellapi.h>
#include "MouseHelper.h"
#include "WinHelper.h"

#pragma comment(lib, "Xinput.lib")

#define NUM_INPUTS  14

NOTIFYICONDATA nid;

int main()
{
    std::cout << "Starting App...\n";

    XINPUT_STATE state;
    ZeroMemory(&state, sizeof(XINPUT_STATE));

    /*
    BUTTON TO KEYBOARD MAPPING:
        A       Left Click
        B       Right Click
        X       Touch Keyboard
        Y       Task View
        RB
        LB
        R3      Middle Click
        L3
        Start   Windows Key
        Back

        D-Pad   Media Control (NESW): TBD, Next, Pause/Play, Prev
    */

    // 0  1  2  3  4  5  6  7
    // A  B  X  Y  RB LB R3 L3
    bool isPressed;     
    bool wasPressed[NUM_INPUTS];
    memset(wasPressed, 0, sizeof(bool) * 8);

    UINT XINPUT_MASK[NUM_INPUTS] = {
        XINPUT_GAMEPAD_A,
        XINPUT_GAMEPAD_B,
        XINPUT_GAMEPAD_X,
        XINPUT_GAMEPAD_Y,
        XINPUT_GAMEPAD_RIGHT_SHOULDER,
        XINPUT_GAMEPAD_LEFT_SHOULDER,
        XINPUT_GAMEPAD_RIGHT_THUMB,
        XINPUT_GAMEPAD_LEFT_THUMB,
        XINPUT_GAMEPAD_START,
        XINPUT_GAMEPAD_BACK,
        XINPUT_GAMEPAD_DPAD_UP,
        XINPUT_GAMEPAD_DPAD_DOWN,
        XINPUT_GAMEPAD_DPAD_LEFT,
        XINPUT_GAMEPAD_DPAD_RIGHT
    };


    int sens = 18;
    bool ENABLED = true;
    bool TOGGLED, WASTOGGLED = false;

    while (1) {
        if (XInputGetState(0, &state) == ERROR_SUCCESS) {
            // Start, Back, LB and RB need to be pressed to disable/reenable.
            TOGGLED = (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) &&
                (state.Gamepad.wButtons & XINPUT_GAMEPAD_START) &&
                (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) &&
                (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
            if (TOGGLED && !WASTOGGLED) {
                ENABLED = !ENABLED;
                WASTOGGLED = true;
                notif(ENABLED);

                std::cout << (ENABLED ? "Controller Mouse Input Enabled" : "Controller Mouse Input Disabled") << std::endl;
            }
            else if (!TOGGLED && WASTOGGLED) {
                WASTOGGLED = false;
            }

            if (ENABLED) {
                SHORT lx = state.Gamepad.sThumbLX;
                SHORT ly = state.Gamepad.sThumbLY;

                SHORT rx = state.Gamepad.sThumbRX;
                SHORT ry = state.Gamepad.sThumbRY;

                int Ldx = convert(lx, sens);
                int Ldy = convert(ly, -sens);

                mouseMove(Ldx, Ldy);

                int Rdx = convert(rx, sens * 2);
                int Rdy = convert(ry, -sens * 2);

                mouseScroll(-Rdy);

                for (int i = 0; i < NUM_INPUTS; i++) {
                    isPressed = state.Gamepad.wButtons & XINPUT_MASK[i];
                    handleButton(XINPUT_MASK[i], isPressed, &(wasPressed[i]));
                }
            }
        }
        Sleep(ENABLED ? 10 : 1000);
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
