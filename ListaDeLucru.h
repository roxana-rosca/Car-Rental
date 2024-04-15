#pragma once
#include "Car.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "Observer.h"

using std::vector;

class ListaDeLucru:public Observable {
private:
    vector<Car> deSpalat;
public:
    ListaDeLucru()=default;

    /*
     * Adauga o masina in lista de lucru
     * @param c: masina care se adauga (Car)
     *
     * post: masina va fi adaugata in lista de lucru
     */
    void addCarToListaDeLucru(const Car& c);

    /*
     * Elimina toate masinile din lista de lucru
     *
     * post: lista de lucru este goala
     */
    void emptyListaDeLucru();

    /*
     * Adauga un numar random de masini in lista de lucru
     *
     * @param originalCars: masinile din care se alege (vector<Car>)
     * @param howMany: cate melodii se adauga (int)
     *
     * post: masinile sunt adaugate in lista de lucru curenta
     */
    void addRandomCars(vector<Car> originalCars, int howMany);

    /*
     * Returneaza un vector care contine toate masinile din lista de lucru
     */
    const vector<Car> & getAlldeSpalat() const;
};



