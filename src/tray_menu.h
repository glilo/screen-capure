#ifndef TRAY_MENU_H
#define TRAY_MENU_H

#include <QSystemTrayIcon>
#include <QMenu>
#include <vector>
#include "screen.h"
#include "screen_controller.h"

class TrayMenu : public QMenu {
    Q_OBJECT // Esta macro es esencial para señales, slots y el sistema de meta-objetos de Qt

public:
    explicit TrayMenu(QWidget* parent = nullptr);
    void buildMenu(ScreenController* screenController);
    void initializeTrayIcon();

private:
    QSystemTrayIcon trayIcon;
    void createQuitAction();
    void createRefreshAction(ScreenController* screenController);
    void refreshMenu(ScreenController* screenController);
};

#endif // TRAY_MENU_H
