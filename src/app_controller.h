#ifndef APP_CONTROLLER_H
#define APP_CONTROLLER_H

#include "tray_menu.h"
#include "screen_controller.h"

class AppController {
public:
    AppController();
    void run();

private:
    TrayMenu* trayMenu;
    ScreenController* screenController;
};

#endif // APP_CONTROLLER_H