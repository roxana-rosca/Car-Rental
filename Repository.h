#pragma once
#include "Car.h"
#include "VectorDinamicTemplate.h"
#include <utility>
#include <vector>
#include <map>
#include <string>

using std::vector;
using std::map;

class RepositoryException{
private:
    string errorMsg;
public:
    explicit RepositoryException(string errorMsg): errorMsg{std::move(errorMsg)}{};
    string getErrorMessage(){
        return this->errorMsg;
    }
};


class AbstractRepo{
public:

    virtual void store(const Car& c)=0;

    virtual const Car& find(const string& nr_i)=0;

    virtual bool exists(const Car& c)=0;

    virtual int cauta_indice(const string& nr_i)=0;

    virtual int deleteCar(const string& nr_i)=0;

    virtual int modifyPlateNumber(const string& nr_i, const string& new_nr_i)=0;

    virtual vector<Car>& getAllCars() =0;

    // destructor virtual
    virtual ~AbstractRepo()=default;
};


class LabRepo:public AbstractRepo{
private:
    double probabilitate;
    map<string,Car> allCars; // cheia=producatorul masinii, valoarea=obiectul de tip Car
public:
    LabRepo()=default;

    LabRepo(double p):probabilitate{p}{};

    // returneaza probabilitatea
    float get_probabilitate() const;

    // verifica daca o functie va arunca sau nu exceptie
    // returneaza 1 daca in urma generarii random arunca exceptie, 0 in caz contrar
    int arunca_exceptie();

    void store(const Car& c);

    const Car& find(const string& nr_i);

    bool exists(const Car& c);

    int cauta_indice(const string& nr_i);

    int deleteCar(const string& nr_i);

    int modifyPlateNumber(const string& nr_i, const string& new_nr_i);

    vector<Car>& getAllCars() override;

};


class Repository: public AbstractRepo {
    vector<Car> allCars;
    //VectorDinamic<Car> allCars;

public:
    // Constructor
    Repository() = default;


    /*
     * Constructor de copiere
     * -nu permitem copiere Repository
     */
    Repository(const Repository& ot) = delete;

    /*
     * Adauga o masina in lista
     * @param c: masina care se adauga (Car)
     * @return: -
     *
     * @throws: RepoException daca o masina cu acelasi numar de inmatriculare exista deja
     */
    virtual void store(const Car& c);

    /*
     * Returneaza o lista cu toate masinile
     * @return: lista cu masinile (vector of Car objects)
     */
    [[nodiscard]] vector<Car>& getAllCars();

    /*
     * Cauta o masina cu numarul de inmatriculare dat
     *
     * @param nr_i: numarul de inmatriculare dupa care se cauta
     * @returns: entitatea Car cu numarul de inmatriculare dat (daca acesta exista)
     * @throws: RepoException daca nu exista o masina cu numarul de inmatriculare dat
     */
    const Car& find(const string& nr_i);

    /*
     * Verifica daca o masina data exista in lista
     *
     * @param c: masina care se cauta in lista de masini
     * @return: true daca melodia exista, false altfe;
     */
    bool exists(const Car& c);

    /*
     * Cauta pozitia pe care se afla masina cu numarul de inmatriculare dat
     *
     * @return: pozitia pe care se afla, -1 daca nu exista
     */
    int cauta_indice(const string& nr_i);

    /*
     * Sterge elementul cu numarul de inmatriculare dat
     *
     * @return: 1 daca masina a fost stearsa cu succes
     * @throws: RepositoryException daca nu exista
     */
    virtual int deleteCar(const string& nr_i);

    /*
     * Modifica numarul de inmatriculare al unei masini
     *
     * @return: 1 daca masina a fost modificata cu succes
     *
     * @throws: RepositoryException daca nu exista o masina cu numarul de inmatriculare dat
     */
    int modifyPlateNumber(const string& nr_i, const string& new_nr_i);

};


class FileRepository:public Repository{
private:
    string fName; // nume fisier
    void loadFromFile();
    void writeToFile();
public:
    FileRepository(string fName):Repository(), fName{std::move(fName)}
    {
        loadFromFile(); // incarcam datele din fisier
    }


    void store(const Car& c) override{
        Repository::store(c);
        writeToFile();
    }

    int deleteCar(const string &nr_i) override{
        Repository::deleteCar(nr_i);
        writeToFile();
        return 1;
    }

};

void testeRepo();
