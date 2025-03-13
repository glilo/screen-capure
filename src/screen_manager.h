#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include "screen.h"
#include <vector>

extern "C" {

#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
#include <libavdevice/avdevice.h>
#include <libavcodec/avcodec.h>

}


// Clase para gestionar pantallas (detección y administración)
class ScreenManager {
public:
    // Método para detectar pantallas
    static std::vector<Screen> detectScreens();

private:
    // Métodos auxiliares para cada plataforma
    static std::vector<Screen> getScreensWindows();
    static std::vector<Screen> detectScreensLinux();
    static std::vector<Screen> detectScreensMacOS();
    static std::vector<Screen> detectScreensFFmpeg();
};

#endif // SCREEN_MANAGER_H