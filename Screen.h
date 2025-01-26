#ifndef SCREEN_H
#define SCREEN_H

#include <string>


class Screen {
public:
    // Constructor
    Screen(int id, const std::string& name, const std::string& resolution);

    // Getters
    int getId() const;
    const std::string& getName() const;
    const std::string& getResolution() const;

private:
    int id;                     // Identificador único de la pantalla
    std::string name;           // Nombre de la pantalla
    std::string resolution;     // Resolución de la pantalla
};

#endif // SCREEN_H

