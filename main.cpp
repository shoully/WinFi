#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Networking.Connectivity.h>
#include <winrt/Windows.Networking.NetworkOperators.h>
#include <string>

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Networking::Connectivity;
using namespace Windows::Networking::NetworkOperators;

// Global UI Handles
HWND hwndSSID, hwndPass, hwndStatus, hwndStart, hwndStop;

// Helper to update status text
void SetStatus(const std::wstring& text) {
    SetWindowText(hwndStatus, text.c_str());
}

// Modern Hotspot Logic
void HandleHotspot(bool start) {
    try {
        init_apartment();

        // 1. Get the current internet connection profile
        ConnectionProfile profile = NetworkInformation::GetInternetConnectionProfile();
        if (!profile) {
            SetStatus(L"Error: No internet connection found.");
            return;
        }

        // 2. Create the Tethering Manager
        NetworkOperatorTetheringManager manager = NetworkOperatorTetheringManager::CreateFromConnectionProfile(profile);

        // 3. Check capability
        TetheringCapability capability = manager.GetTetheringCapability();
        if (capability != TetheringCapability::Enabled) {
            SetStatus(L"Error: Hotspot not supported or blocked.");
            return;
        }

        if (start) {
            // Get credentials from UI
            wchar_t ssid[100], pass[100];
            GetWindowText(hwndSSID, ssid, 100);
            GetWindowText(hwndPass, pass, 100);

            if (wcslen(ssid) < 1 || wcslen(pass) < 8) {
                SetStatus(L"Error: Password must be >= 8 chars.");
                return;
            }

            SetStatus(L"Configuring...");
            NetworkOperatorTetheringAccessPointConfiguration config = manager.GetCurrentAccessPointConfiguration();
            config.Ssid(ssid);
            config.Passphrase(pass);
            manager.ConfigureAccessPointAsync(config).get();

            SetStatus(L"Starting...");
            auto result = manager.StartTetheringAsync().get();
            if (result.Status() == TetheringOperationStatus::Success) {
                SetStatus(L"Status: Hotspot is ACTIVE");
            } else {
                SetStatus(L"Error: Failed to start.");
            }
        } else {
            SetStatus(L"Stopping...");
            auto result = manager.StopTetheringAsync().get();
            if (result.Status() == TetheringOperationStatus::Success) {
                SetStatus(L"Status: Hotspot STOPPED");
            } else {
                SetStatus(L"Error: Failed to stop.");
            }
        }
    } catch (winrt::hresult_error const& ex) {
        SetStatus(L"Exception: " + std::wstring(ex.message().c_str()));
    }
}

// Win32 Window Procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE:
            CreateWindow(L"STATIC", L"SSID (Network Name):", WS_VISIBLE | WS_CHILD, 20, 20, 200, 20, hwnd, NULL, NULL, NULL);
            hwndSSID = CreateWindow(L"EDIT", L"WinFi_Hotspot", WS_VISIBLE | WS_CHILD | WS_BORDER, 20, 45, 240, 25, hwnd, NULL, NULL, NULL);

            CreateWindow(L"STATIC", L"Password (min 8 chars):", WS_VISIBLE | WS_CHILD, 20, 80, 200, 20, hwnd, NULL, NULL, NULL);
            hwndPass = CreateWindow(L"EDIT", L"shortshort", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_PASSWORD, 20, 105, 240, 25, hwnd, NULL, NULL, NULL);

            hwndStart = CreateWindow(L"BUTTON", L"START", WS_VISIBLE | WS_CHILD, 20, 150, 110, 40, hwnd, (HMENU)1, NULL, NULL);
            hwndStop = CreateWindow(L"BUTTON", L"STOP", WS_VISIBLE | WS_CHILD, 150, 150, 110, 40, hwnd, (HMENU)2, NULL, NULL);

            hwndStatus = CreateWindow(L"STATIC", L"Status: Ready", WS_VISIBLE | WS_CHILD, 20, 210, 240, 40, hwnd, NULL, NULL, NULL);
            return 0;

        case WM_COMMAND:
            if (LOWORD(wParam) == 1) HandleHotspot(true);
            if (LOWORD(wParam) == 2) HandleHotspot(false);
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"WinFiWindowClass";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"Win-Fi Hotspot Manager", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) return 0;

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
