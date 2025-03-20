#include "screen.h"
#include <stdexcept>
#ifdef _WIN32
#include <windows.h>
#endif

// Constructor
Screen::Screen(int id, const std::string& name, const std::string& resolution, const std::string& nameId, const std::string& xPos, const std::string& yPos)
    : id(id), name(name), resolution(resolution), nameId(nameId), xPos(xPos), yPos(yPos) {}

Screen::~Screen()
{
    stopCapture();
}


// Getters
int Screen::getId() const {
    return id;
}

const std::string& Screen::getName() const {
    return name;
}

const std::string& Screen::getResolution() const {
    return resolution;
}

const std::string& Screen::getNameId() const
{
    return nameId;
}

const std::string& Screen::getxPos() const
{
    return xPos;
}

const std::string& Screen::getyPos() const
{
    return yPos;
}

void Screen::setName(const std::string& newName)
{
    name = newName;
}

void Screen::startCapture()
{
    if (isCapturing) return;
    captureThread = new ScreenCaptureThread(resolution, xPos, yPos);
    captureThread->start();
    isCapturing = true;
}

void Screen::stopCapture()
{
    if (captureThread) {
        captureThread->stopCapture();
        if (captureThread != nullptr) {
            captureThread->wait();
            delete captureThread;
            captureThread = nullptr;
        }
    }
    isCapturing = false;
}

