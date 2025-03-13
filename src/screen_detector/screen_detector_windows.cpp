#ifdef _WIN32
#include <windows.h>
#include <setupapi.h>
#include <devguid.h>
#include <regstr.h>
#pragma comment(lib, "Setupapi.lib")
#endif
#include "../screen.h"
#include <vector>
#include <QDebug>
#include "screen_detector.h"

static std::string wideCharToString(const WCHAR* wideCharStr) {
    std::wstring ws(wideCharStr);
    std::string str(ws.begin(), ws.end());
    return str;
}

static void detectScreensWindows(std::vector<Screen>& screens) {

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
        std::string name = wideCharToString(monitorInfo.szDevice);
        if (name.find("\\\\.\\") == 0) name = name.substr(4);
        qDebug() << "Dispositivo: " << name;
        int id = static_cast<int>(screens->size());
        std::string resolution = std::to_string(monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left) +
            "x" +
            std::to_string(monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top);
        std::string xPos = std::to_string(monitorInfo.rcMonitor.left);
        std::string yPos = std::to_string(monitorInfo.rcMonitor.top);

        // Agregar el monitor detectado al vector
        screens->emplace_back(id, "Desconocido (" + name + ")", resolution, name, xPos, yPos);

        return TRUE; // Continuar enumerando
        };

    // Enumerar monitores en el sistema
    if (!EnumDisplayMonitors(nullptr, nullptr, enumMonitors, reinterpret_cast<LPARAM>(&screens))) {
        throw std::runtime_error("Failed to enumerate monitors using EnumDisplayMonitors.");
    }
}


static std::string getMonitorInfo(DWORD property, const char* propertyName, HDEVINFO hDevInfo, SP_DEVINFO_DATA DeviceInfoData, bool processHardwareID = false) {
    DWORD size = 0;
    SetupDiGetDeviceRegistryPropertyW(hDevInfo, &DeviceInfoData, property, NULL, NULL, 0, &size);

    if (size == 0) {
        qDebug() << propertyName << ": No disponible";
        return "Desconocido";
    }
    std::vector<WCHAR> buffer(size / sizeof(WCHAR) + 1, 0);  // Buffer para Unicode
    if (SetupDiGetDeviceRegistryPropertyW(hDevInfo, &DeviceInfoData, property, NULL,
        (PBYTE)buffer.data(), size, &size)) {
        std::string result = QString::fromWCharArray(buffer.data()).toStdString();

        // Si es el ID de hardware, extraer solo la parte después de "MONITOR\"
        qDebug() << propertyName << ": " << result;
        return result;
    }
    else {
        qDebug() << propertyName << ": Error al obtener datos";
        return "Desconocido";
    }
}

static std::map<std::string, std::string> GetMonitorModels() {
    HDEVINFO hDevInfo;
    SP_DEVINFO_DATA DeviceInfoData;
    std::map<std::string, std::string> monitorModels;

    hDevInfo = SetupDiGetClassDevsW(&GUID_DEVCLASS_MONITOR, 0, 0, DIGCF_PRESENT);
    if (hDevInfo == INVALID_HANDLE_VALUE) {
        qDebug() << "Error al obtener la lista de monitores.";
        return monitorModels;
    }
    DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
    for (DWORD i = 0; SetupDiEnumDeviceInfo(hDevInfo, i, &DeviceInfoData); i++) {
        qDebug() << "------------------------";
        qDebug() << "Monitor " << i + 1 << ":";
        getMonitorInfo(SPDRP_HARDWAREID, "ID de hardware", hDevInfo, DeviceInfoData, false);
        std::string nameMonitor = getMonitorInfo(SPDRP_FRIENDLYNAME, "Modelo", hDevInfo, DeviceInfoData);
        monitorModels[std::to_string(i + 1)] = nameMonitor;
    }
    SetupDiDestroyDeviceInfoList(hDevInfo);
    return monitorModels;
}



static void mapScreenData(std::vector<Screen>& screens, const std::map<std::string, std::string>& mapsModelScreen) {
    for (auto& screen : screens) {  // Usamos referencia para modificar directamente
        auto it = mapsModelScreen.find(std::string(1, screen.getNameId().back()));  // Buscamos el name en el mapa
        if (it != mapsModelScreen.end()) {  // Si lo encontramos, actualizamos description
            screen.setName(it->second + " (" + it->first + ")");
        }
    }
}

std::vector<Screen> detectScreensWindows() {
    std::vector<Screen> screens;
    detectScreensWindows(screens);
    std::map<std::string, std::string> mapsModelScreen = GetMonitorModels();
    mapScreenData(screens, mapsModelScreen);
    return screens;
}