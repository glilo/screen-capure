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

void TrayMenu::buildMenu(const std::vector<Screen>& screens) {
    // Crear men�s din�micamente para las pantallas detectadas
    for (const auto& screen : screens) {
        QMenu* screenSubMenu = new QMenu(QString::fromStdString(screen.getName()), this);

        // A�adir resoluci�n
        QAction* resolutionAction = new QAction(
            QString::fromStdString("Resolution: " + screen.getResolution()), screenSubMenu);
        resolutionAction->setEnabled(false);
        screenSubMenu->addAction(resolutionAction);

        // A�adir acci�n de prueba
        QAction* dummyAction = new QAction("No Action Yet", screenSubMenu);
        screenSubMenu->addAction(dummyAction);

        addMenu(screenSubMenu); // A�adir el submen� al men� principal
    }

    createQuitAction();
}

void TrayMenu::createQuitAction() {
    // A�adir la acci�n de salir
    QAction* quitAction = new QAction("Salir", this);
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
    addAction(quitAction);
}