#pragma once
#include "Repository.h"
#include "Validator.h"
#include "ListaDeLucru.h"
#include <functional>
#include <map>
#include "DTO.h"
#include "Export.h"
#include "Undo.h"
#include <memory>

using std::function;
using std::unique_ptr;

class Service {
private:
    //Repository& repo;
    AbstractRepo& repo;
    Validator& validator;

    ListaDeLucru deSpalatCurent;

    // pointer la ActiuneUndo pentru un apel polimorfic
    std::vector<unique_ptr<ActiuneUndo>> undoActions;

    /*
     * Filtreaza lista de masini dupa un anumit criteriu
     *
     * @param fct: functia dupa care se filtreaza lista de masini
     * @return: lista cu masinile care indeplinesc criteriul dat
     */
    vector<Car> filter(const function<bool(const Car&)>& fct);

    /*
     * Functie de sortare proprie
     *
     * @param maiMicF: functia de comparare folosita pentru sortare
     * @return: lista cu masini sortate dupa criteriul dat (vector cu elemente de tip Car)
     */
    vector<Car> generalSort(bool(*maiMicF)(const Car&, const Car&));

public:
    // Constructor
    Service(AbstractRepo& car_repo, Validator& car_validator): repo{car_repo}, validator{car_validator}{};

    // Constructor de copiere
    // nu avem nevoie, in aplicatie va exista un singur service
    Service(const Service& ot) = delete;

    /*
     * Adaugare masina cu datele date
     * @param nr_i: numarul de inmatriculare a masinii care se adauga (string)
     * @param p: producatorul masinii care se adauga (string)
     * @param model: modelul masinii care se adauga (string)
     * @param tip: tipul masinii care se adauga (string)
     *
     * @throws:
     *  RepositoryException daca mai exista o masina cu numarul de inmatriculare dat
     *  ValidationException daca masina nu este valida
     */
    void addCar(string nr_i, string p, string model, string tip);

    /*
     * Returneaza un vector cu toate masinile disponibile
     *
     * @return: lista cu toate masinile disponibile (vector cu obiecte de tip Car)
     */
    vector<Car>& getAllCars() noexcept{
        return this->repo.getAllCars();
    }

    /*
     * Filtrare dupa producator
     * Returneaza o lista de masini cu producatorul dat
     *
     * @param p: producatorul dupa care se filtreaza
     * @return: lista cu masinile care au producatorul dat (vector cu elemente de tip Car)
     */
    vector<Car> filtrareProducator(const string& p);

    /*
     * Filtrare dupa tip
     * Returneaza o lista de masini cu tipul dat
     *
     * @param tip: tipul masinii dupa care se filtreaza
     * @return: lista cu masinile care au tipul dat (vector cu elemente de tip Car)
     */
    vector<Car> filtrareTip(const string& tip);

    /*
     * Sortare dupa numar de inmatriculare
     *
     * @return: lista de masini sortate dupa numarul de inmatriculare
     */
    vector<Car> sortByPlateNumber();

    /*
     * Sortare dupa tipul masinii
     *
     * @return: lista cu masinile sortate dupa tip
     */
    vector<Car> sortByType();

    /*
     * Sortare dupa producator + model masina
     *
     * @return: lista cu masini sortate dupa producator + model
     */
    vector<Car> sortByCompanyAndModel();

    /*
     * Cautare masina dupa un numar de inmatriculare
     *
     * @return: masina cu numarul de inmatriculare dat daca exista
     * @throws: RepositoryException daca masina nu exista
     */
    Car findCar(const string& nr_i);

    /*
     * Sterge masina cu numarul de inmatriculare dat
     *
     * @return: 1, daca masina a fost stearsa cu succes
     * @throws: RepositoryException daca nu exista o masina cu numarul de inmatriculare dat in lista
     */
    int deleteCar(const string& nr_i);

    /*
     * Modifica numarul de inmatriculare al unei masini
     *
     * @return: daca masina a fost modificata cu succes
     * @throws: ValidationException daca numarul de inmatriculare nou nu este valid
     * @throws: RepositoryException daca nu exista o masina cu numarul de inmatriculare dat
     */
    int modifyCar(const string& nr_i, const string& new_nr_i);

    /*
     * Adauga o masina cu numarul de inmatriculare dat in lista de lucru
     *
     * @param nr_i: numarul de inmatriculare a masinii care se adauga (string)
     *
     * post: masina de adauga in lista de lucru
     * @throws: RepositoryException daca nu exista o masina cu numarul de inmatriculare dat
     */
    void addListaDeLucru(string& nr_i);

    /*
     * Returneaza un vector cu toate masinile din lista de lucru
     */
    const vector<Car>& getListaDeLucru();


    ListaDeLucru& getListaDeLucruNew(){
        return this->deSpalatCurent;
    };

    /*
     * Adauga masini random in lista de lucru.
     *
     * @param howMany: cate masini se adauga (int)
     *
     * @return: numarul de masini adaugate in lista de lucru
     * post: se adauga masinile in lista de lucru
     */
    int addRandomToListaDeLucru(int howMany);

    /*
     * Elimina toate masinile din lista de lucru.
     *
     * post: lista de lucru goala
     */
    void emptyListaDeLucru();

    /*
     * Creeaza un raport folosind un dictionar
     * (cate masini din fiecare model exista)
     * Dictionarul are structura:
     * map<model, DTO>
     */
    map<string , DTO> creare_raport();


    /*
     * Exporta lista de lucru intr-un fisier de tip CVS
     */
    void exportaListaDeLucruCVS(const string& fName) const;

    /*
     * Exporta lista de lucru intr-un fisier de tip HTML
     */
    void exportaListaDeLucruHTML(const string& fName) const;


    /*
     * Realizeaza undo la operatia de adaugare, stergere, respectiv modificare.
     */
    void undo();
};

void testeService();


