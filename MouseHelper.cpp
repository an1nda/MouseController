#include "MouseHelper.h"

int convert(SHORT a, int b) {
    return static_cast<int>(a / 32767.0 * b);
}

void mouseMove(int dx, int dy) {
    POINT p;
    GetCursorPos(&p);
    SetCursorPos(p.x + dx, p.y + dy);
    mouse_event(MOUSEEVENTF_MOVE, dx, dy, 0, 0);
}

void mouseScroll(int dy) {
    mouse_event(MOUSEEVENTF_WHEEL, 0, 0, dy, 0);
}

void handleButton(UINT XINPUT_MASK, bool is, bool* was) {
    DWORD event;
    HWND hwnd;
    if (is && !(*was)) {
        *was = true;

        switch (XINPUT_MASK) {
        case XINPUT_GAMEPAD_A:
            event = MOUSEEVENTF_LEFTDOWN;
            break;

        case XINPUT_GAMEPAD_B:
            event = MOUSEEVENTF_RIGHTDOWN;
            break;

        case XINPUT_GAMEPAD_RIGHT_THUMB:
            event = MOUSEEVENTF_MIDDLEDOWN;
            break;

        /*case XINPUT_GAMEPAD_X:
            break;

        case XINPUT_GAMEPAD_Y:
            break;

        case XINPUT_GAMEPAD_RIGHT_SHOULDER:
            break;

        case XINPUT_GAMEPAD_LEFT_SHOULDER:
            break;

        case XINPUT_GAMEPAD_LEFT_THUMB:
            break;

        case XINPUT_GAMEPAD_START:
            break;

        case XINPUT_GAMEPAD_BACK:
            break;

        case XINPUT_GAMEPAD_DPAD_UP:
            break;

        case XINPUT_GAMEPAD_DPAD_DOWN:
            break;

        case XINPUT_GAMEPAD_DPAD_LEFT:
            break;

        case XINPUT_GAMEPAD_DPAD_RIGHT:
            break;*/

        default:
            return;
        }

        mouse_event(event, 0, 0, 0, 0);
    }
    else if (!is && (*was)) {
        *was = false;

        switch (XINPUT_MASK) {
        case XINPUT_GAMEPAD_A:
            event = MOUSEEVENTF_LEFTUP;
            break;

        case XINPUT_GAMEPAD_B:
            event = MOUSEEVENTF_RIGHTUP;
            break;

        case XINPUT_GAMEPAD_RIGHT_THUMB:
            event = MOUSEEVENTF_MIDDLEUP;
            break;

        /*case XINPUT_GAMEPAD_X:
            break;

        case XINPUT_GAMEPAD_Y:
            break;

        case XINPUT_GAMEPAD_RIGHT_SHOULDER:
            break;

        case XINPUT_GAMEPAD_LEFT_SHOULDER:
            break;

        case XINPUT_GAMEPAD_LEFT_THUMB:
            break;

        case XINPUT_GAMEPAD_START:
            break;

        case XINPUT_GAMEPAD_BACK:
            break;

        case XINPUT_GAMEPAD_DPAD_UP:
            break;

        case XINPUT_GAMEPAD_DPAD_DOWN:
            break;

        case XINPUT_GAMEPAD_DPAD_LEFT:
            break;

        case XINPUT_GAMEPAD_DPAD_RIGHT:
            break;*/

        default:
            return;
        }

        mouse_event(event, 0, 0, 0, 0);
    }
}