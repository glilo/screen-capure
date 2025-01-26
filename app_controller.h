#ifndef APP_CONTROLLER_H
#define APP_CONTROLLER_H

#include "screen_manager.h"
#include "tray_menu.h"

class AppController {
public:
    AppController();
    void run();

private:
    TrayMenu* trayMenu;
};

#endif // APP_CONTROLLER_H