#include "app_controller.h"

AppController::AppController() {
    trayMenu = new TrayMenu();
}

void AppController::run() {
    // Detectar pantallas y construir el men�
    auto screens = ScreenManager::detectScreens();
    trayMenu->buildMenu(screens);
}