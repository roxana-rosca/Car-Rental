#include "Car.h"
#include <assert.h>

#include <utility>

string Car::get_nr_inmatriculare() const {
    return this->nr_inmatriculare;
}

string Car::get_producator() const {
    return this->producator;
}

string Car::get_tip() const{
    return this->tip;
}

string Car::get_model() const{
    return this->model;
}

void Car::set_nr_inmatriculare(string new_nr_inmatriculare) {
    this->nr_inmatriculare = std::move(new_nr_inmatriculare);
}

void Car::set_producator(string new_producator) {
    this->producator = std::move(new_producator);
}

void Car::set_tip(string new_tip) {
    this->tip = std::move(new_tip);
}

void Car::set_model(string new_model) {
    this->model = std::move(new_model);
}

bool cmpNrInmatriculare(const Car& c1, const Car &c2)
{
    return c1.get_nr_inmatriculare() < c2.get_nr_inmatriculare();
}

bool cmpTip(const Car& c1, const Car &c2)
{
    return c1.get_tip() < c2.get_tip();
}

bool cmpProdModel(const Car& c1, const Car &c2)
{
    if(c1.get_producator() == c2.get_producator())
        return c1.get_model() < c2.get_model();
    return c1.get_producator() <c2.get_producator();
}

void test_get_set()
{
    Car car1{"CJ12WZB","CITROEN","C3","oras"};
    assert(car1.get_nr_inmatriculare() == "CJ12WZB");
    assert(car1.get_producator() == "CITROEN");
    assert(car1.get_model() == "C3");
    assert(car1.get_tip() == "oras");

    car1.set_nr_inmatriculare("CJ12AAA");
    car1.set_producator("AUDI");
    car1.set_model("A6");
    car1.set_tip("sedan");

    assert(car1.get_nr_inmatriculare() == "CJ12AAA");
    assert(car1.get_producator() == "AUDI");
    assert(car1.get_model() == "A6");
    assert(car1.get_tip() == "sedan");
}

void testeDomain()
{
    test_get_set();
}


