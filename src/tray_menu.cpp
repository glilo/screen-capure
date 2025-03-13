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

void TrayMenu::buildMenu(const std::vector<Screen>& screens) {
    // Crear menús dinámicamente para las pantallas detectadas
    for (const auto& screen : screens) {
        QMenu* screenSubMenu = new QMenu(QString::fromStdString(screen.getName()), this);

        // Añadir resolución
        QAction* resolutionAction = new QAction(
            QString::fromStdString("Resolution: " + screen.getResolution()), screenSubMenu);
        resolutionAction->setEnabled(false);
        screenSubMenu->addAction(resolutionAction);

        // Añadir acción de prueba
        QAction* dummyAction = new QAction("No Action Yet", screenSubMenu);
        screenSubMenu->addAction(dummyAction);

        addMenu(screenSubMenu); // Añadir el submenú al menú principal
    }

    createQuitAction();
}

void TrayMenu::createQuitAction() {
    // Añadir la acción de salir
    QAction* quitAction = new QAction("Salir", this);
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
    addAction(quitAction);
}