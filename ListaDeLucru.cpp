#include "ListaDeLucru.h"
using std::shuffle;

void ListaDeLucru::addCarToListaDeLucru(const Car &c) {
    this->deSpalat.push_back(c);
    notify();
}

void ListaDeLucru::emptyListaDeLucru() {
    this->deSpalat.clear();
    notify();
}

void ListaDeLucru::addRandomCars(vector<Car> originalCars, int howMany) {
    shuffle(originalCars.begin(),originalCars.end(),std::default_random_engine(std::random_device{}())); // se amesteca vectorul
    while(deSpalat.size() < howMany && originalCars.size() > 0)
    {
        deSpalat.push_back(originalCars.back());
        originalCars.pop_back();
    }
    notify();
}

const vector<Car> & ListaDeLucru::getAlldeSpalat() const {
    return this->deSpalat;
}


