#pragma once
#include "Car.h"
#include "Repository.h"

class ActiuneUndo{
public:
    // functie pur virtuala-toate clasele derivate vor defini metoda
    virtual void doUndo()=0;

    // Destructor
    virtual ~ActiuneUndo()=default;
};


class UndoAdauga:public ActiuneUndo{
    Car masinaAdaugata;
    //Repository& repo;
    AbstractRepo& repo;
public:
    // Constructor
    UndoAdauga(AbstractRepo& repo, const Car& c):masinaAdaugata{c}, repo{repo}{};

    void doUndo() override{
        repo.deleteCar(masinaAdaugata.get_nr_inmatriculare());
    }
};


class UndoSterge:public ActiuneUndo{
    Car masinaStearsa;
    //Repository& repo;
    AbstractRepo& repo;
public:
    // Constructor
    UndoSterge(AbstractRepo& repo, const Car& c):masinaStearsa{c}, repo{repo}{};

    void doUndo() override{
        repo.store(masinaStearsa);
    }
};


class UndoModifica:public ActiuneUndo{
    Car masinaModificata;
    Car masinaNoua;
    //Repository& repo;
    AbstractRepo& repo;
public:
    // Constructor
    UndoModifica(AbstractRepo& repo, const Car& c, const Car& new_car):masinaModificata{c}, masinaNoua{new_car}, repo{repo}{};

    void doUndo() override{
        repo.deleteCar(masinaNoua.get_nr_inmatriculare());
        repo.store(masinaModificata);
    }
};

