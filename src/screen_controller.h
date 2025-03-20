#pragma once
#include "screen.h"
#include <vector>
#include "screen_manager.h"



class ScreenController
{
private:
	std::vector<Screen> screens;
public:
	explicit ScreenController(QObject* parent = nullptr);
	void detectScreens();
	void startScreenCapture(int screenId);
	void stopScreenCapture(int screenId);
	const std::vector<Screen>& getScreens() const;
	void stopAllCaptures();
};

