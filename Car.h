#pragma once
#include <iostream>
#include <string>
#include <utility>

using std::string;
using std::endl;
using std::cout;


class Car {
private:
    string nr_inmatriculare;
    string producator;
    string model;
    string tip;
public:
    Car() = default;

    // Constructor
    Car(string  nr_i,string  p, string m, string  t): nr_inmatriculare{std::move(nr_i)},producator{std::move(p)},model{std::move(m)},tip{std::move(t)}{};

    // Constructor de copiere
    Car(const Car& ot): nr_inmatriculare{ot.nr_inmatriculare}, producator{ot.producator}, model{ot.model}, tip{ot.tip}{
        //cout<<"Copy constructor called."<<endl;
    };

    // gettere
    [[nodiscard]] string get_nr_inmatriculare() const;
    [[nodiscard]] string get_producator() const;
    [[nodiscard]] string get_tip() const;
    [[nodiscard]] string get_model() const;

    // settere
    void set_nr_inmatriculare(string new_nr_inmatriculare);
    void set_producator(string new_producator);
    void set_tip(string new_tip);
    void set_model(string new_model);

};

/*
 * Compara 2 masini dupa numarul de inmatriculare
 *
 * @return: true daca codurile ascii ale nr de inm al masinii c1 sunt mai mici decat codurile ascii ale nr de inm al masinii c2,
 *          false altfel
 */
bool cmpNrInmatriculare(const Car& c1, const Car &c2);

/*
 * Compara 2 masini dupa tipul acestora
 *
 * @return: true daca codurile ascii ale tipului masinii c1 sunt mai mici decat codurile ascii ale tipului masinii c2,
 *          false altfel
 */
bool cmpTip(const Car& c1, const Car &c2);

/*
 * Compara 2 masini dupa producatorul si modelul acestora
 *
 * @return: true daca c1 < c2 (ordonare alfabetica),
 *          false altfel
 */
bool cmpProdModel(const Car& c1, const Car &c2);

void testeDomain();



