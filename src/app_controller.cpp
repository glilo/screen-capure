#include "app_controller.h"

AppController::AppController() {
    trayMenu = new TrayMenu();
    screenController = new ScreenController();
}

void AppController::run() {
    // Detectar pantallas y construir el men�
    screenController->detectScreens();
    trayMenu->buildMenu(screenController);
}