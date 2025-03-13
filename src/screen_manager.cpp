#include "screen_manager.h"
#include <stdexcept>
#include <iostream>
#include <QDebug>
#include ".\screen_detector\screen_detector.h"

// Método principal de detección de pantallas
std::vector<Screen> ScreenManager::detectScreens() {
#ifdef _WIN32
    //return detectScreensFFmpeg();
    return getScreensWindows();
#elif __linux__
    return detectScreensLinux();
#elif __APPLE__
    return detectScreensMacOS();
#else
    throw std::runtime_error("Detección de pantallas no implementada para este sistema operativo.");
#endif
}


std::vector<Screen> ScreenManager::getScreensWindows(){
    return detectScreensWindows();
}



// TODO Implementación para Linux (sin implementar)
std::vector<Screen> ScreenManager::detectScreensLinux() {
    throw std::runtime_error("Linux screen detection not implemented.");
}

// TODO Implementación para macOS (sin implementar)
std::vector<Screen> ScreenManager::detectScreensMacOS() {
    throw std::runtime_error("macOS screen detection not implemented.");
}

std::vector<Screen> ScreenManager::detectScreensFFmpeg() {
    avdevice_register_all();
    std::vector<Screen> screens;
    const AVInputFormat* input_format = av_find_input_format("dshow"); // En Windows, gdigrab para captura de pantalla

    if (input_format) {
        AVDictionary* options = nullptr;
        }
    AVFormatContext* format_ctx = avformat_alloc_context();
    if (!format_ctx) {
        throw std::runtime_error("Error: No se pudo asignar AVFormatContext");
        //std::cerr << "Error: No se pudo asignar AVFormatContext" << std::endl;
    }
    AVDeviceInfoList* devices = nullptr;
    // Enumerar los dispositivos de captura

    AVDeviceInfoList* device_list = nullptr; // Puntero a la lista de dispositivos


    try {
        avdevice_list_devices(format_ctx, &device_list);
            for (int i = 0; i < devices->nb_devices; i++) {
                // Procesar cada dispositivo encontrado
                /*screens.emplace_back(i,
                    devices->devices[i]->device_description,
                    devices->devices[i]->device_name);*/
            }
    
    }
    catch (const std::exception& e) {  // Captura excepciones estándar
        std::cout << "Excepción atrapada: " << e.what() << std::endl;
    }

    // Liberar memoria
    //avformat_close_input(&format_context);
    avdevice_free_list_devices(&devices);
   // avformat_free_context(format_context);
    return screens;
    
    
    }

