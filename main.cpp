#include "share_screen.h"
#include <QtWidgets/QApplication>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QIcon>
#include <QMessageBox>
#include <libavformat/avformat.h>
#include "screen_manager.h"
#include <QDebug>
#include "app_controller.h"



int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    AppController controller;
    controller.run();

    return app.exec();
}