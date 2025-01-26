#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include "screen.h"
#include <vector>

// Clase para gestionar pantallas (detección y administración)
class ScreenManager {
public:
    // Método para detectar pantallas
    static std::vector<Screen> detectScreens();

private:
    // Métodos auxiliares para cada plataforma
    static std::vector<Screen> detectScreensWindows();
    static std::vector<Screen> detectScreensLinux();
    static std::vector<Screen> detectScreensMacOS();
};

#endif // SCREEN_MANAGER_H