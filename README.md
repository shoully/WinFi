# Win-Fi
![Win-Fi Logo](/winfi_logo.png)

OS | License | Compatibility
--- | --- | ---
Windows | GNU GPL v2.0 | Windows 10, 11, 12

Win-Fi is a lightweight, native C++ application designed to transform your PC into a WiFi hotspot using the modern Windows "Mobile Hotspot" feature.

### Features
- **Native & Fast:** Built with pure C++ and the Win32 API for zero overhead.
- **Modern:** Uses the `NetworkOperatorTetheringManager` (C++/WinRT) API for full compatibility with Windows 11 and 12.
- **Simple UI:** Easy SSID and Password configuration.

### How to Build
To build Win-Fi, you need a C++ compiler that supports C++17 and the Windows SDK.

#### Using Visual Studio (Recommended)
1. Open the folder in Visual Studio (or use `CMakeLists.txt`).
2. Ensure you have the **"Desktop development with C++"** workload installed.
3. Build the project as a **Release** or **Debug** x64 target.

#### Using CMake (CLI)
```bash
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

### Important Notes
- **Administrator Privileges:** Managing the Mobile Hotspot is a system-level operation. You **must** run `WinFi.exe` as an **Administrator**.
- **Hardware Support:** Ensure your WiFi card supports Hosted Network or WiFi Direct (most modern laptops do).

### Legacy Manual Setup (netsh)
While Win-Fi is recommended, you can still manually manage the older "Hosted Network" (if supported by your driver) via CMD:

```bash
# Setup
netsh wlan set hostednetwork mode=allow ssid=winfi key=password123
# Start
netsh wlan start hostednetwork
# Stop
netsh wlan stop hostednetwork
```

### License
Win-Fi is licensed under the GNU GPL v2.0 License - see the LICENSE file for details.
