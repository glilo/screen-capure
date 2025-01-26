#include "screen_manager.h"
#include <stdexcept>
#ifdef _WIN32
#include <windows.h>
#endif
#include <iostream>
#include <QDebug>

// Método principal de detección de pantallas
std::vector<Screen> ScreenManager::detectScreens() {
#ifdef _WIN32
    return detectScreensWindows();
#elif __linux__
    return detectScreensLinux();
#elif __APPLE__
    return detectScreensMacOS();
#else
    throw std::runtime_error("Detección de pantallas no implementada para este sistema operativo.");
#endif
}

static std::string wideCharToString(const WCHAR* wideCharStr) {
    if (!wideCharStr) {
        return {};
    }

    int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, wideCharStr, -1, nullptr, 0, nullptr, nullptr);
    if (sizeNeeded <= 0) {
        throw std::runtime_error("Failed to convert wide character string to multibyte string.");
    }

    std::string result(sizeNeeded, '\0');
    WideCharToMultiByte(CP_UTF8, 0, wideCharStr, -1, &result[0], sizeNeeded, nullptr, nullptr);

    result.resize(sizeNeeded - 1);
    return result;
}


std::vector<Screen> ScreenManager::detectScreensWindows() {
    std::vector<Screen> screens;

    // Lambda que actúa como callback para EnumDisplayMonitors
    auto enumMonitors = [](HMONITOR hMonitor, HDC, LPRECT, LPARAM lParam) -> BOOL {
        auto* screens = reinterpret_cast<std::vector<Screen>*>(lParam);

        if (hMonitor == nullptr) {
            qDebug() << "Invalid HMONITOR handle.";
            return FALSE; // Interrumpimos la enumeración
        }

        //MONITORINFOEX monitorInfo;
        //monitorInfo.cbSize = sizeof(monitorInfo);

        MONITORINFOEX monitorInfo;
        ZeroMemory(&monitorInfo, sizeof(monitorInfo)); // Inicializar a 0 por seguridad
        monitorInfo.cbSize = sizeof(MONITORINFOEX);

        // Obtener información del monitor actual
        if (!GetMonitorInfoW(hMonitor, &monitorInfo)) {
            DWORD error = GetLastError();
            qDebug() << "Failed to retrieve monitor information using GetMonitorInfoW." << error;
            return FALSE;
        }

        // Extraer datos del monitor
        std::string name= wideCharToString(monitorInfo.szDevice);
        int id = static_cast<int>(screens->size());
        std::string resolution = std::to_string(monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left) +
            "x" +
            std::to_string(monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top);

        // Agregar el monitor detectado al vector
        screens->emplace_back(id, name, resolution);

        return TRUE; // Continuar enumerando
        };

    // Enumerar monitores en el sistema
    if (!EnumDisplayMonitors(nullptr, nullptr, enumMonitors, reinterpret_cast<LPARAM>(&screens))) {
        throw std::runtime_error("Failed to enumerate monitors using EnumDisplayMonitors.");
    }

    return screens;
}

// TODO Implementación para Linux (sin implementar)
std::vector<Screen> ScreenManager::detectScreensLinux() {
    throw std::runtime_error("Linux screen detection not implemented.");
}

// TODO Implementación para macOS (sin implementar)
std::vector<Screen> ScreenManager::detectScreensMacOS() {
    throw std::runtime_error("macOS screen detection not implemented.");
}