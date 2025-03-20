#include "tray_menu.h"
#include <QAction>
#include <QApplication>
#include <QDebug>
#include <QSystemTrayIcon>


TrayMenu::TrayMenu(QWidget* parent) : QMenu(parent), trayIcon(nullptr) {
    initializeTrayIcon(); // Configuramos el ícono de la bandeja al crear la instancia
}

void TrayMenu::initializeTrayIcon() {
    // Establecer el ícono
    QIcon icon(":/share_screen/resource/img/image.ico");
    trayIcon.setIcon(icon);

    // Verificar si el ícono se cargó correctamente
    if (icon.isNull()) {
        qWarning("No se pudo cargar el icono de la bandeja.");
        return;
    }

    // Asignar el menú al tray icon
    trayIcon.setContextMenu(this);

    // Mostrar el tray icon
    trayIcon.show();
}

void TrayMenu::buildMenu(ScreenController* screenController) {
    // Crear menús dinámicamente para las pantallas detectadas
    for (auto &screen : screenController->getScreens()) {
        QMenu* screenSubMenu = new QMenu(QString::fromStdString(screen.getName()), this);

        // Añadir resolución
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


        // Añadir acción de prueba
       
        addMenu(screenSubMenu); // Añadir el submenú al menú principal
    }
    createRefreshAction(screenController);
    createQuitAction();
}

void TrayMenu::createQuitAction() {
    // Añadir la acción de salir
    QAction* quitAction = new QAction("Exit", this);
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
    addAction(quitAction);
}

void TrayMenu::createRefreshAction(ScreenController* screenController) {
    QAction* refreshAction = new QAction("Refresh", this);
    connect(refreshAction, &QAction::triggered, this, [this, screenController]() {
        this->refreshMenu(screenController);  // Pasando el parámetro a refreshMenu
        });
    addAction(refreshAction);

}

void TrayMenu::refreshMenu(ScreenController* screenController) {
    this->clear();  // Limpiar el menú antes de actualizar
    screenController->stopAllCaptures(); // Detener todas las capturas activas
    screenController->detectScreens();   // Redetectar pantallas
    buildMenu(screenController);

}