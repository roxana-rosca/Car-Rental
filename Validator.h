#pragma once
#include "Car.h"
#include <utility>
#include <vector>
#include <string>

using std::string;
using std::vector;

class ValidationException{
    vector<string> errorMsg;
public:
    explicit ValidationException(vector<string> errorMessages): errorMsg{std::move(errorMessages)}{};

    string getErrorMessages(){
        string fullMsg;
        for(const string& e:errorMsg)
        {
            fullMsg+=e+"\n";
        }
        return fullMsg;}
};

/*
 * Clasa pentru validarea masinilor
 * O masina este valida daca:
 *  are un numar de inmatriculare format din cel putin 6 caractere si cel mult 8 caractere
 *  producatorul are mai mult de 2 caractere
 *  modelul nu este vid
 *  tipul nu este vid
 */
class Validator{
public:
    static void valideaza_masina(const Car& c)
    {
        vector<string> errors;
        if(c.get_nr_inmatriculare().size() < 6 || c.get_nr_inmatriculare().size() > 8)
            errors.emplace_back("Numarul de inmatriculare este invalid!");
        if(c.get_producator().size() <= 2)
            errors.emplace_back("Producator invalid!");
        if(c.get_model().empty())
            errors.emplace_back("Modelul nu poate sa fie vid!");
        if(c.get_tip().empty())
            errors.emplace_back("Tipul masinii nu poate sa fie vid!");

        if(!errors.empty())
            throw ValidationException(errors);
    }
};