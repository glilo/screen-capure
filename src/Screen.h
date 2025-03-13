#ifndef SCREEN_H
#define SCREEN_H

#include <string>


class Screen {
public:
    // Constructor
    Screen(int id, const std::string& name, const std::string& resolution, const std::string& nameId, const std::string& xPos, const std::string& yPos);

    // Getters
    int getId() const;
    const std::string& getName() const;
    const std::string& getResolution() const;
    const std::string& getNameId() const;
    const std::string& getxPos() const;
    const std::string& getyPos() const;

    //Setters
    void setName(const std::string& newName);





private:
    int id;                     // Identificador �nico de la pantalla
    std::string name;           // Modelo y display de la pantalla 
    std::string resolution;     // Resoluci�n de la pantalla
    std::string nameId;         // display de la pantalla
    std::string xPos;           // posici�n x de la pantalla
    std::string yPos;           // posici�n y de la pantalla
};

#endif // SCREEN_H

