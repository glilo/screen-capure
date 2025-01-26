#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include "screen.h"
#include <vector>

// Clase para gestionar pantallas (detecci�n y administraci�n)
class ScreenManager {
public:
    // M�todo para detectar pantallas
    static std::vector<Screen> detectScreens();

private:
    // M�todos auxiliares para cada plataforma
    static std::vector<Screen> detectScreensWindows();
    static std::vector<Screen> detectScreensLinux();
    static std::vector<Screen> detectScreensMacOS();
};

#endif // SCREEN_MANAGER_H