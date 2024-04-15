#pragma once
#include <assert.h>

constexpr auto INITIAL_CAPACITY = 5;
template<typename T>
class IteratorVector; // forward declaration -  avem nevoie de a implementa anumite metode in clasa VectorDinamic care se bazeaza pe iterator

template<typename T>
class VectorDinamic{
private:
    // reprezentare
    T* elems;
    int capacitate;
    int lungime;

    //resize
    void resize();
public:
    // Constructor
    VectorDinamic();

    // Constructor copiere
    VectorDinamic(const VectorDinamic& ot);

    // Assignment operator
    VectorDinamic& operator=(const VectorDinamic& ot);

    // Destructor
    ~VectorDinamic();

    // add element in vector
    void add(T elem);

    // get element on position in vector
    T& get(int poz);

    // set element on position in vector
    void set(T elem, int poz);

    // get size - length of vector
    int size();

    // iterator methods
    friend class IteratorVector<T>;

    // pentru a putea folosi for each
    IteratorVector<T> begin();
    IteratorVector<T> end();

    // stergerea unui element de pe pozitia poz
    void erase(int poz);

};

template<typename T>
class IteratorVector{
private:
    const VectorDinamic<T>& vec;
    int poz=0;
public:
    explicit IteratorVector(const VectorDinamic<T>& v) noexcept;
    IteratorVector(const VectorDinamic<T>& v, int poz) noexcept;
    [[nodiscard]] bool valid() const;
    T& element() const;
    void next();
    T& operator*();
    IteratorVector& operator++();
    bool operator==(const IteratorVector& ot) noexcept;
    bool operator!=(const IteratorVector& ot) noexcept;
};

template<typename T>
VectorDinamic<T>::VectorDinamic() {
    this->elems = new T[INITIAL_CAPACITY];
    this->lungime = 0;
    this->capacitate = INITIAL_CAPACITY;
}

template<typename T>
VectorDinamic<T>::VectorDinamic(const VectorDinamic& ot) {
    // Constructor de copiere
    // se creeaza un nou vector dinamic pe baza unuia existent

    // alocare capacitate
    this->elems = new T[ot.capacitate];

    // copiem elementele, setam lungime, valoare
    for(int i = 0; i < ot.lungime; i++)
    {
        this->elems[i] = ot.elems[i];
    }
    this->lungime = ot.lungime;
    this->capacitate = ot.capacitate;
}

template<typename T>
VectorDinamic<T>& VectorDinamic<T>::operator=(const VectorDinamic<T> &ot) {
    // daca v1=v1 nu are sens sa facem op de mai jos
    if(this == &ot){
        return *this;
    }

    // fiindca in obiectul curent punem altceva prin assignment, eliberam memoria alocata anterior
    delete[] this->elems;

    // copiem elementele din ot si setam lungime, capacitate
    this->elems = new T[ot.capacitate];
    for(int i = 0; i < ot.lungime; i++){
        elems[i] = ot.elems[i];
    }
    this->lungime = ot.lungime;
    this->capacitate = ot.capacitate;
    return *this;
}

template<typename T>
void VectorDinamic<T>::resize() {
    int newCapacity = this->capacitate * 2;
    T* newElems = new T[newCapacity];
    for(int i = 0; i < this->lungime; i++){
        newElems[i] = this->elems[i];
    }
    delete[] this->elems;
    this->elems = newElems;
    this->capacitate = newCapacity;
}

template<typename T>
VectorDinamic<T>::~VectorDinamic(){
    delete[] this->elems;
}

template<typename T>
void VectorDinamic<T>::add(T elem){
    if(this->lungime == this->capacitate)
        resize();
    this->elems[this->lungime] = elem;
    this->lungime++;
}

template<typename T>
T& VectorDinamic<T>::get(int poz) {
    // verificare pozitie valida
    return this->elems[poz];
}

template<typename T>
void VectorDinamic<T>::set(T elem, int poz) {
    // verificare pozitie valida

    this->elems[poz] = elem;
}

template<typename T>
int VectorDinamic<T>::size() {
    return this->lungime;
}

template<typename T>
void VectorDinamic<T>::erase(int poz){
    for(int i = poz; i < this->lungime-1; i++)
    {
        this->elems[i] = this->elems[i+1];
    }
    this->lungime--;
}


template<typename T>
IteratorVector<T> VectorDinamic<T>::begin() {
    return IteratorVector<T>(*this);
}

template<typename T>
IteratorVector<T>VectorDinamic<T>::end(){
    return IteratorVector<T>(*this, this->lungime);
}


template<typename T>
IteratorVector<T>::IteratorVector(const VectorDinamic<T> &v) noexcept: vec{v}{};

template<typename T>
IteratorVector<T>::IteratorVector(const VectorDinamic<T> &v, int poz) noexcept: vec{v}, poz{poz} {};

template<typename T>
bool IteratorVector<T>::valid() const {
    return this->poz < this->vec.lungime;
}

template<typename T>
T& IteratorVector<T>::element() const {
    return this->vec.elems[this->poz];
}

template<typename T>
void IteratorVector<T>::next() {
    this->poz++;
}

template<typename T>
T& IteratorVector<T>::operator*() {
    return this->element();
}

template<typename T>
IteratorVector<T>& IteratorVector<T>::operator++() {
    this->next();
    return *this;
}

template<typename T>
bool IteratorVector<T>::operator==(const IteratorVector<T> &ot) noexcept {
    return this->poz == ot.poz;
}

template<typename T>
bool IteratorVector<T>::operator!=(const IteratorVector<T> &ot) noexcept {
    return !(*this == ot); // nu merge cu expresia simplificata
}

void testVectorDinamic();
void testAssignmentOperator();