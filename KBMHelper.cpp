#include "KBMHelper.h"

void simulateKeyPress(BYTE type, BYTE key) {
    if (type == KEY_HOLD) {
        keybd_event(key, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
    }
    else if (type == KEY_RELEASE) {
        keybd_event(key, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
    }
}

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

        case XINPUT_GAMEPAD_X:
            simulateKeyPress(KEY_HOLD, VK_LWIN);
            simulateKeyPress(KEY_HOLD, VK_CONTROL);
            simulateKeyPress(KEY_HOLD, 0x4F); // Letter O
            return;

        case XINPUT_GAMEPAD_Y:
            simulateKeyPress(KEY_HOLD, VK_LWIN);
            simulateKeyPress(KEY_HOLD, VK_TAB);
            return;

        case XINPUT_GAMEPAD_RIGHT_SHOULDER:
            simulateKeyPress(KEY_HOLD, VK_RIGHT);
            return;

        case XINPUT_GAMEPAD_LEFT_SHOULDER:
            simulateKeyPress(KEY_HOLD, VK_LEFT);
            return;

        /*case XINPUT_GAMEPAD_START:
            simulateKeyPress(KEY_HOLD, VK_LWIN);
            return;

        case XINPUT_GAMEPAD_LEFT_THUMB:
            break;

        case XINPUT_GAMEPAD_BACK:
            break;*/

        case XINPUT_GAMEPAD_DPAD_UP:
            simulateKeyPress(KEY_HOLD, VK_MEDIA_STOP);
            return;

        case XINPUT_GAMEPAD_DPAD_DOWN:
            simulateKeyPress(KEY_HOLD, VK_MEDIA_PLAY_PAUSE);
            return;

        case XINPUT_GAMEPAD_DPAD_LEFT:
            simulateKeyPress(KEY_HOLD, VK_MEDIA_PREV_TRACK);
            return;

        case XINPUT_GAMEPAD_DPAD_RIGHT:
            simulateKeyPress(KEY_HOLD, VK_MEDIA_NEXT_TRACK);
            return;

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

        case XINPUT_GAMEPAD_X:
            simulateKeyPress(KEY_RELEASE, 0x4F); // Letter O
            simulateKeyPress(KEY_RELEASE, VK_CONTROL);
            simulateKeyPress(KEY_RELEASE, VK_LWIN);
            return;

        case XINPUT_GAMEPAD_Y:
            simulateKeyPress(KEY_RELEASE, VK_TAB);
            simulateKeyPress(KEY_RELEASE, VK_LWIN);
            return;

        case XINPUT_GAMEPAD_RIGHT_SHOULDER:
            simulateKeyPress(KEY_RELEASE, VK_RIGHT);
            return;

        case XINPUT_GAMEPAD_LEFT_SHOULDER:
            simulateKeyPress(KEY_RELEASE, VK_LEFT);
            return;

        /*case XINPUT_GAMEPAD_START:
            simulateKeyPress(KEY_RELEASE, VK_LWIN);
            return;

        case XINPUT_GAMEPAD_LEFT_THUMB:
            break;

        case XINPUT_GAMEPAD_BACK:
            break;*/

        case XINPUT_GAMEPAD_DPAD_UP:
            simulateKeyPress(KEY_HOLD, VK_MEDIA_STOP);
            return;

        case XINPUT_GAMEPAD_DPAD_DOWN:
            simulateKeyPress(KEY_RELEASE, VK_MEDIA_PLAY_PAUSE);
            return;

        case XINPUT_GAMEPAD_DPAD_LEFT:
            simulateKeyPress(KEY_RELEASE, VK_MEDIA_PREV_TRACK);
            return;

        case XINPUT_GAMEPAD_DPAD_RIGHT:
            simulateKeyPress(KEY_RELEASE, VK_MEDIA_NEXT_TRACK);
            return;

        default:
            return;
        }

        mouse_event(event, 0, 0, 0, 0);
    }
}