#include "Repository.h"
#include <assert.h>
#include <algorithm>
#include <fstream>
#include <random>


int Repository::cauta_indice(const string &nr_i) {
    for(int i=0; i<this->allCars.size();i++)
    {
        if(allCars[i].get_nr_inmatriculare() == nr_i)
            return i;
    }
    return -1;
}

int Repository::deleteCar(const string &nr_i) {
    int poz = cauta_indice(nr_i);
    if(poz == -1)
        throw RepositoryException("Masina cu numarul de inmatriculare "+nr_i+" nu exista in lista!\n");
    //this->allCars.erase(poz);
    this->allCars.erase(allCars.begin()+poz);

    return 1;
}

int Repository::modifyPlateNumber(const string &nr_i, const string &new_nr_i) {
    int poz = cauta_indice(nr_i);
    if(poz == -1)
        throw RepositoryException("Masina cu numarul de inmatriculare "+nr_i+" nu exista in lista!\n");
    Car c = find(nr_i);
    c.set_nr_inmatriculare(new_nr_i);
    //this->allCars.set(c,poz);
    this->allCars[poz] = c;
    return 1;
}

const Car& Repository::find(const string& nr_i) {
    /*for(const Car& c: this->allCars)
    {
        if(c.get_nr_inmatriculare() == nr_i)
            return c;
    }
    throw RepositoryException("Masina cu numarul de inmatriculare "+nr_i+" nu exista in lista!\n");
    */

    vector<Car>::iterator f = std::find_if(this->allCars.begin(),this->allCars.end(),
                                           [=](const Car& c){
                                               return c.get_nr_inmatriculare() == nr_i;
                                           });
    if(f != this->allCars.end())
        return (*f);
    else throw RepositoryException("Masina cu numarul de inmatriculare "+nr_i+" nu exista in lista!\n");

}

bool Repository::exists(const Car &c) {
    try{
        find(c.get_nr_inmatriculare());
        return true;
    }
    catch(RepositoryException&)
    {
        return false;
    }
}

void Repository::store(const Car &c) {
    if(exists(c)){
        throw RepositoryException("Masina cu numarul de inmatriculare "+c.get_nr_inmatriculare()+" exista deja in lista!\n");
    }
    this->allCars.push_back(c);
    //this->allCars.add(c);
}

vector<Car>& Repository::getAllCars()  {
    /*
    vector<Car> cars;
    for(const auto& car: this->allCars)
    {
        cars.push_back(car);
    }
    return cars;*/

    // pentru a reduce apelarea constructorului de copiere
    return this->allCars;
}

void FileRepository::loadFromFile() {
    std::ifstream in(fName);
    if(!in.is_open())
    {
        throw RepositoryException("Unable to open file: "+fName+"!\n");
    }
    while(!in.eof())
    {
        string nr_inmatriculare;
        string producator;
        string model;
        string tip;

        in>>nr_inmatriculare;
        in>>producator;
        in>>model;
        in>>tip;

        if(!nr_inmatriculare.empty()) // la salvare am un endl
        {
            Car c{nr_inmatriculare.c_str(),producator.c_str(),model.c_str(),tip.c_str()};
            Repository::store(c);
        }

    }
    in.close();
}

void FileRepository::writeToFile() {
    std::ofstream out(fName);
    if(!out.is_open())
    {
        throw RepositoryException("Unable to open file: "+fName+"!\n");
    }
    for(auto& c:getAllCars())
    {
        out<<c.get_nr_inmatriculare()<<endl;
        out<<c.get_producator()<<endl;
        out<<c.get_model()<<endl;
        out<<c.get_tip()<<endl;
    }
}



float LabRepo::get_probabilitate() const {
    return this->probabilitate;
}

int LabRepo::arunca_exceptie() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0,1);
    double val=dist(gen);
    if(val<this->get_probabilitate())
        return 1;
    return 0;
}

void LabRepo::store(const Car &c) {
    //if(arunca_exceptie()==1)
    //     throw RepositoryException("Exceptie!!!\n");

    string key = c.get_producator();
    allCars.insert({key, c});
}

vector<Car>& LabRepo::getAllCars() {
    vector<Car> cars;

    for(const auto& i:allCars)
    {
        cars.push_back(i.second);
    }

    return cars;
}

const Car &LabRepo::find(const string &nr_i) {
    if(arunca_exceptie()==1)
        throw RepositoryException("Exceptie!!!\n");

    vector<Car> masini=this->getAllCars();
    vector<Car>::iterator f = std::find_if(masini.begin(),masini.end(),
                                           [=](const Car& c){
                                               return c.get_nr_inmatriculare() == nr_i;
                                           });
    if(f != masini.end())
        return (*f);
    else throw RepositoryException("Masina cu numarul de inmatriculare "+nr_i+" nu exista in lista!\n");
}

bool LabRepo::exists(const Car &c) {
    if(arunca_exceptie()==1)
        throw RepositoryException("Exceptie!!!\n");

    try{
        find(c.get_nr_inmatriculare());
        return true;
    }
    catch(RepositoryException&)
    {
        return false;
    }
}

int LabRepo::cauta_indice(const string &nr_i) {
    if(arunca_exceptie()==1)
        throw RepositoryException("Exceptie!!!\n");

    vector<Car> masini=this->getAllCars();
    for(int i=0; i<masini.size();i++)
    {
        if(masini[i].get_nr_inmatriculare() == nr_i)
            return i;
    }
    return -1;
}

//
int LabRepo::deleteCar(const string &nr_i) {
    if(arunca_exceptie()==1)
        throw RepositoryException("Exceptie!!!\n");


    vector<Car> masini=this->getAllCars();

    int poz = cauta_indice(nr_i);
    if(poz == -1)
        throw RepositoryException("Masina cu numarul de inmatriculare "+nr_i+" nu exista in lista!\n");
    //this->allCars.erase(poz);
    masini.erase(masini.begin()+poz);

    return 1;
}

//
int LabRepo::modifyPlateNumber(const string &nr_i, const string &new_nr_i) {
    if(arunca_exceptie()==1)
        throw RepositoryException("Exceptie!!!\n");

    int poz = cauta_indice(nr_i);
    if(poz == -1)
        throw RepositoryException("Masina cu numarul de inmatriculare "+nr_i+" nu exista in lista!\n");
    Car c = find(nr_i);
    c.set_nr_inmatriculare(new_nr_i);
    //this->allCars.set(c,poz);
    this->allCars[c.get_producator()]=c;
    return 1;
}



void testAddRepo()
{
    Repository testRepo;
    Car car1{"CJ12WZB","CITROEN","C3","oras"};
    testRepo.store(car1);
    assert(testRepo.getAllCars().size() == 1);

    Car car2{"CJ12WZB","CITROEN","C5","oras"};
    try{
        testRepo.store(car2);
        assert(false);
    }
    catch(RepositoryException&)
    {
        assert(true);
    }
}

void testFindRepo()
{
    Repository testRepo;

    Car c1{"BZ14GLK","MERCEDES-BENZ","C","Sedan"};
    Car c2{"CL23RER","VOLKSWAGWEN","Passat","Sedan"};
    Car c3{"CJ06AAA","VOLVO","EX90","SUV"};

    testRepo.store(c1);
    testRepo.store(c2);

    assert(testRepo.exists(c1));
    assert(!testRepo.exists(c3));

    auto foundCar = testRepo.find("BZ14GLK");
    assert(foundCar.get_tip() == "Sedan");
    assert(foundCar.get_producator() == "MERCEDES-BENZ");

    try{
        testRepo.find("BC11TTT");
        assert(false);
    }
    catch(RepositoryException& ve)
    {
        assert(ve.getErrorMessage() == "Masina cu numarul de inmatriculare BC11TTT nu exista in lista!\n");
    }
}

void testDeleteRepo()
{
    Repository testRepo;

    Car c1{"BZ14GLK","MERCEDES-BENZ","C","Sedan"};
    Car c2{"CL23RER","VOLKSWAGWEN","Passat","Sedan"};
    Car c3{"CJ06AAA","VOLVO","EX90","SUV"};

    testRepo.store(c1);
    testRepo.store(c2);
    testRepo.store(c3);

    assert(testRepo.cauta_indice("BZ14GLK") == 0);
    assert(testRepo.cauta_indice("ABCDEF") == -1);

    try{
        testRepo.deleteCar("BZ14GLK");
        assert(true);
    }
    catch(RepositoryException&){
        assert(false);
    }

    assert(testRepo.getAllCars().size() == 2);

    try{
        testRepo.deleteCar("ABCDEF");
        assert(false);
    }
    catch(RepositoryException&){
        assert(true);
    }

}

void testModifyRepo()
{
    Repository testRepo;

    Car c1{"BZ14GLK","MERCEDES-BENZ","C","Sedan"};
    Car c2{"CL23RER","VOLKSWAGWEN","Passat","Sedan"};
    Car c3{"CJ06AAA","VOLVO","EX90","SUV"};

    testRepo.store(c1);
    testRepo.store(c2);
    testRepo.store(c3);

    try{
        testRepo.modifyPlateNumber("BZ14GLK","BC14GLK");
        assert(true);
    }
    catch(RepositoryException&)
    {
        assert(false);
    }

    try{
        testRepo.modifyPlateNumber("BZ14GLK","BC14GLK");
        assert(false);
    }
    catch(RepositoryException&)
    {
        assert(true);
    }
}

void testFileRepo()
{
    std::ofstream out("testFileRepo.txt", std::ios::trunc);
    out.close();
    FileRepository fileRepo{"testFileRepo.txt"};
    fileRepo.store(Car{"BV23ABC", "Ford", "Focus", "Hatchback"});

    FileRepository fileRepo1{"testFileRepo.txt"};
    auto c = fileRepo1.find("BV23ABC");
    assert(c.get_producator()=="Ford");
    try{
        fileRepo1.find("AB11AAA");
        assert(false);
    }
    catch(RepositoryException&){
        assert(true);
    }
    assert(fileRepo1.deleteCar("BV23ABC")==1);
    //assert(fileRepo1.getAllCars().empty());

    try{
        FileRepository fileRepo2{"te/stCars.txt"};
        assert(false);
    }
    catch(RepositoryException&){
        assert(true);
    }


}

void testeRepo()
{
    testAddRepo();
    testFindRepo();
    testDeleteRepo();
    testModifyRepo();

    testVectorDinamic();
    testAssignmentOperator();

    testFileRepo();
}