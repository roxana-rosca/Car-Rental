#pragma once
#include "Service.h"


class UI {
private:
    Service& srv;
public:
    // Constructor
    explicit UI(Service& srv): srv{srv}{};

    // Constructor de copiere
    UI(const UI& ot) = delete;

    static void printMenu();
    void uiAdd();
    void addDefaultCars();
    //static void printCars(VectorDinamic<Car> allCars);
    static void printCars(const vector<Car> &allCars);
    void run();
    void uiFilter();
    void uiSort();
    void uiFind();
    void uiDelete();
    void uiModify();

    static void printListaDeLucruMenu();
    void uiListaDeLucru();
    void uiAddListaDeLucru();
    void uiAddRandomToListaDeLucru();
    void uiEmptyListaDeLucru();
    void uiCreeazaRaport();
    void uiUndo();
};

