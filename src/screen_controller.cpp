#include "screen_controller.h"

ScreenController::ScreenController(QObject* parent)
{
}

void ScreenController::detectScreens()
{
	screens = ScreenManager::detectScreens();
}

void ScreenController::startScreenCapture(int screenId)
{
	if (screenId >= 0 && screenId < screens.size()) {
		screens[screenId].startCapture();
	}
}

void ScreenController::stopScreenCapture(int screenId)
{
	if (screenId >= 0 && screenId < screens.size()) {
		screens[screenId].stopCapture();
	}
}

const std::vector<Screen>& ScreenController::getScreens() const
{
	return screens;
}

void ScreenController::stopAllCaptures() {
	for (int id = 0; id < screens.size();  id++) {
		if (screens[id].isCapturing) {
			stopScreenCapture(id);  // Detiene cada captura activa
		}
	}
	screens.clear(); // Limpia el vector de pantallas
}
