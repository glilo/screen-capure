#ifndef SCREEN_DETECTOR_H
#define SCREEN_DETECTOR_H

// Declaraciones para cada sistema operativo, usando preprocesadores.
#ifdef _WIN32
std::vector<Screen> detectScreensWindows();
#endif

#endif // SCREEN_DETECTOR_H#pragma once
