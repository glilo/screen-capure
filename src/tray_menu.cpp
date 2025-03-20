#include "tray_menu.h"
#include <QAction>
#include <QApplication>
#include <QDebug>
#include <QSystemTrayIcon>


TrayMenu::TrayMenu(QWidget* parent) : QMenu(parent), trayIcon(nullptr) {
    initializeTrayIcon(); // Configuramos el �cono de la bandeja al crear la instancia
}

void TrayMenu::initializeTrayIcon() {
    // Establecer el �cono
    QIcon icon(":/share_screen/resource/img/image.ico");
    trayIcon.setIcon(icon);

    // Verificar si el �cono se carg� correctamente
    if (icon.isNull()) {
        qWarning("No se pudo cargar el icono de la bandeja.");
        return;
    }

    // Asignar el men� al tray icon
    trayIcon.setContextMenu(this);

    // Mostrar el tray icon
    trayIcon.show();
}

void TrayMenu::buildMenu(ScreenController* screenController) {
    // Crear men�s din�micamente para las pantallas detectadas
    for (auto &screen : screenController->getScreens()) {
        QMenu* screenSubMenu = new QMenu(QString::fromStdString(screen.getName()), this);

        // A�adir resoluci�n
        QAction* resolutionAction = new QAction(
            QString::fromStdString("Resolution: " + screen.getResolution()), screenSubMenu);
        resolutionAction->setEnabled(false);
        screenSubMenu->addAction(resolutionAction);

        int idScreen = screen.getId();
        QAction* startStopAction = screenSubMenu->addAction("Start");
        connect(startStopAction, &QAction::triggered, this, [this, &screen, screenController, startStopAction]() {
            qDebug() << screen.getNameId();
            if (screen.isCapturing) {
                screenController->stopScreenCapture(screen.getId());
                startStopAction->setText("Start");
            }
            else {
                screenController->startScreenCapture(screen.getId());
                startStopAction->setText("Stop");
            }
            });


        // A�adir acci�n de prueba
       
        addMenu(screenSubMenu); // A�adir el submen� al men� principal
    }
    createRefreshAction(screenController);
    createQuitAction();
}

void TrayMenu::createQuitAction() {
    // A�adir la acci�n de salir
    QAction* quitAction = new QAction("Exit", this);
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
    addAction(quitAction);
}

void TrayMenu::createRefreshAction(ScreenController* screenController) {
    QAction* refreshAction = new QAction("Refresh", this);
    connect(refreshAction, &QAction::triggered, this, [this, screenController]() {
        this->refreshMenu(screenController);  // Pasando el par�metro a refreshMenu
        });
    addAction(refreshAction);

}

void TrayMenu::refreshMenu(ScreenController* screenController) {
    this->clear();  // Limpiar el men� antes de actualizar
    screenController->stopAllCaptures(); // Detener todas las capturas activas
    screenController->detectScreens();   // Redetectar pantallas
    buildMenu(screenController);

}