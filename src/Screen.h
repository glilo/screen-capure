#ifndef SCREEN_H
#define SCREEN_H

#include <string>
#include "./screen_capture_thread.h"


class Screen {
public:
    bool isCapturing = false;
    ScreenCaptureThread* captureThread = nullptr;
    // Constructor
    Screen(int id, const std::string& name, const std::string& resolution, const std::string& nameId, const std::string& xPos, const std::string& yPos);
    ~Screen();

    // Getters
    int getId() const;
    const std::string& getName() const;
    const std::string& getResolution() const;
    const std::string& getNameId() const;
    const std::string& getxPos() const;
    const std::string& getyPos() const;

    //Setters
    void setName(const std::string& newName);

    void startCapture();
    void stopCapture();






private:
    int id;                     // Identificador �nico de la pantalla
    std::string name;           // Modelo y display de la pantalla 
    std::string resolution;     // Resoluci�n de la pantalla
    std::string nameId;         // display de la pantalla
    std::string xPos;           // posici�n x de la pantalla
    std::string yPos;           // posici�n y de la pantalla
};

#endif // SCREEN_H

