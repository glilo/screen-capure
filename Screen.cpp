#include "screen.h"
#include <stdexcept>
#ifdef _WIN32
#include <windows.h>
#endif

// Constructor
Screen::Screen(int id, const std::string& name, const std::string& resolution)
    : id(id), name(name), resolution(resolution) {}

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

