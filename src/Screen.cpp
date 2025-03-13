#include "screen.h"
#include <stdexcept>
#ifdef _WIN32
#include <windows.h>
#endif

// Constructor
Screen::Screen(int id, const std::string& name, const std::string& resolution, const std::string& nameId, const std::string& xPos, const std::string& yPos)
    : id(id), name(name), resolution(resolution), nameId(nameId), xPos(xPos), yPos(yPos) {}


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

