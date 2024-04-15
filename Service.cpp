#include "Service.h"
#include "Validator.h"
#include <assert.h>
#include <functional>
#include <algorithm>
#include <utility>
#include <fstream>
#include <memory>

using std::sort;

void Service::addCar(string nr_i, string p, string model, string tip) {
    Car c(std::move(nr_i),std::move(p),std::move(model),std::move(tip));
    validator.valideaza_masina(c);
    repo.store(c);

    undoActions.push_back(std::make_unique<UndoAdauga>(repo,c));
}


vector<Car> Service::filter(const function<bool(const Car &)>& fct) {
    vector<Car> filteredCars;
    for(const auto&car : repo.getAllCars())
    {
        if(fct(car))
        {
            filteredCars.push_back(car);
            //filteredCars.add(car);
        }
    }
    return filteredCars;
}

vector<Car> Service::filtrareProducator(const string& p) {
    /*return filter([p](const Car& c){
        return c.get_producator() == p;
    });*/
    const vector<Car>& allCars = getAllCars();
    vector<Car> filteredCars;
    std::copy_if(allCars.begin(),allCars.end(), std::back_inserter(filteredCars),
                 [=](const Car& c){
                     return c.get_producator() == p;
    });
    return filteredCars;
}

vector<Car> Service::filtrareTip(const string& tip) {
    /*return filter([tip](const Car& c){
        return c.get_tip() == tip;
    });*/
    const vector<Car>& allCars = getAllCars();
    vector<Car> filteredCars;
    std::copy_if(allCars.begin(),allCars.end(), std::back_inserter(filteredCars),
                 [=](const Car& c){
                     return c.get_tip() == tip;
                 });
    return filteredCars;

}

vector<Car> Service::generalSort(bool (*maiMicF)(const Car &, const Car &)) {
    vector<Car> v{repo.getAllCars()};
    // era size_t inainte
    for (int i = 0; i < v.size(); i++) {
        for (int j = i + 1; j < v.size(); j++) {
            if (!maiMicF(v[i], v[j])) {
                //interschimbam
                Car aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }

            /*if(!maiMicF(v.get(i),v.get(j)))
            {
                Car el1 = v.get(i);
                v.set(v.get(j),i);
                v.set(el1,j);
            }*/
        }
    }
    return v;}

vector<Car> Service::sortByPlateNumber() {
    vector<Car> sorted_copy{repo.getAllCars()};
    sort(sorted_copy.begin(), sorted_copy.end(), cmpNrInmatriculare);
    return sorted_copy;

    //return generalSort(cmpNrInmatriculare);
}

vector<Car> Service::sortByType() {
    vector<Car> sorted_copy{repo.getAllCars()};
    sort(sorted_copy.begin(), sorted_copy.end(), cmpTip);
    return sorted_copy;

    //return generalSort(cmpTip);
}

vector<Car> Service::sortByCompanyAndModel(){
    vector<Car> sorted_copy{repo.getAllCars()};
    sort(sorted_copy.begin(), sorted_copy.end(), cmpProdModel);
    return sorted_copy;

    //return generalSort(cmpProdModel);
}

Car Service::findCar(const string& nr_i) {
    return repo.find(nr_i);
}

int Service::deleteCar(const string &nr_i) {
    Car c=repo.find(nr_i);
    if(repo.deleteCar(nr_i)==1)
    {
        undoActions.push_back(std::make_unique<UndoSterge>(repo,c));
        return 1;
    }
    return 0;
    //return repo.deleteCar(nr_i);
}

int Service::modifyCar(const string& nr_i, const string& new_nr_i) {
    vector<string> errors;
    errors.emplace_back("Numarul de inmatriculare este invalid!");
    if(new_nr_i.size() < 6 || new_nr_i.size() > 8)
        throw ValidationException(errors);
    Car c = repo.find(nr_i);
    if(repo.modifyPlateNumber(nr_i,new_nr_i)==1)
    {
        Car new_car = repo.find(new_nr_i);
        undoActions.push_back(std::make_unique<UndoModifica>(repo,c,new_car));
        return 1;
    }
    return 0;
}

void Service::addListaDeLucru(string &nr_i) {
    const auto& car = repo.find(nr_i);
    deSpalatCurent.addCarToListaDeLucru(car);
}

const vector<Car>& Service::getListaDeLucru() {
    return deSpalatCurent.getAlldeSpalat();
}

int Service::addRandomToListaDeLucru(int howMany) {
    deSpalatCurent.addRandomCars(this->getAllCars(), howMany);
    return deSpalatCurent.getAlldeSpalat().size();
}

void Service::emptyListaDeLucru() {
    deSpalatCurent.emptyListaDeLucru();
}

map<string , DTO> Service::creare_raport()
{
    const vector<Car>& allCars = getAllCars();
    map<string, DTO>New_Map;
    for(const Car& c: allCars)
    {
        if(New_Map.find(c.get_model()) == New_Map.end())
        {
            // masina nu exista inca in dictionar
            string key=c.get_model();
            DTO el(key);
            New_Map.insert({key,el});
        }
        else
        {
            // masina exista deja in dictionar, incrementez count
           DTO el=New_Map[c.get_model()];
           el.inc_count();
           New_Map[c.get_model()]=el;
        }
    }
    return New_Map;
}

void Service::exportaListaDeLucruCVS(const string& fName) const {
    exportToCVS(fName, deSpalatCurent.getAlldeSpalat());
}

void Service::exportaListaDeLucruHTML(const string& fName) const {
    exportToHTML(fName,deSpalatCurent.getAlldeSpalat());
}

void Service::undo() {
    if(undoActions.empty()){
        throw RepositoryException{"Nu se poate face undo!\n"};
    }
    undoActions.back()->doUndo();
    undoActions.pop_back();
}


void testAddService()
{
    Repository testRepo;
    Validator testVal;
    Service testService{testRepo,testVal};

    testService.addCar("BZ14GLK","MERCEDES-BENZ","C","Sedan");
    testService.addCar("CL23RER","VOLKSWAGWEN","Passat","Sedan");
    testService.addCar("CJ06AAA","VOLVO","EX90","SUV");

    assert(testService.getAllCars().size() == 3);

    try{
        testService.addCar("CJ06AAA","VOLVO","EX90","SUV");
        assert(false);
    }
    catch(RepositoryException&){
        assert(true);
    }

    try{
        testService.addCar("CJ13BBB","VOLVO","EX90","SUV");
        assert(true);
    }
    catch (ValidationException&)
    {
        assert(false);
    }

    try{
        testService.addCar("CJ06AAAYYY","VOLVO","EX90","SUV");
        assert(false);
    }
    catch(ValidationException& ve){
        assert(true);
        ve.getErrorMessages();
    }

    try{
        testService.addCar("CL06AAA","V","EX90","SUV");
        assert(false);
    }
    catch(ValidationException&){
        assert(true);
    }

    try{
        testService.addCar("CL06AAA","VOLVO","","SUV");
        assert(false);
    }
    catch(ValidationException&){
        assert(true);
    }

    try{
        testService.addCar("CL06AAA","VOLVO","","");
        assert(false);
    }
    catch(ValidationException&){
        assert(true);
    }
}

void testFilterService()
{
    Repository testRepo;
    Validator testVal;
    Service testService{testRepo,testVal};
    testService.addCar("BV23ABC", "Ford", "Focus", "Hatchback");
    testService.addCar("TM03XYZ", "Toyota", "Corolla", "Sedan");
    testService.addCar("IS12DEF", "Volkswagen", "Golf", "Hatchback");
    testService.addCar("CJ78GHI", "Audi", "A4", "Sedan");
    testService.addCar("NT45JKL", "BMW", "X5", "SUV");
    testService.addCar("VL56MNO", "Mercedes-Benz", "C-Class", "Sedan");
    testService.addCar("HD67PQR", "Honda", "Civic", "Hatchback");

    vector<Car> masini_Honda = testService.filtrareProducator("Honda");
    assert(masini_Honda.size() == 1);
    vector<Car> masini_Skoda = testService.filtrareProducator("Skoda");
    assert(masini_Skoda.size() == 0);

    vector<Car> masini_Sedan = testService.filtrareTip("Sedan");
    assert(masini_Sedan.size() == 3);
    vector<Car> masini_4x4 = testService.filtrareTip("4x4");
    assert(masini_4x4.size() == 0);
}

void testSort()
{
    Repository testRepo;
    Validator testVal;
    Service testService{testRepo,testVal};

    testService.addCar("BV23ABC", "Ford", "Focus", "Hatchback");
    testService.addCar("TM03XYZ", "Toyota", "Corolla", "Sedan");
    testService.addCar("IS12DEF", "Volkswagen", "Golf", "Hatchback");
    testService.addCar("CJ78GHI", "Audi", "A4", "Sedan");
    testService.addCar("NT45JKL", "BMW", "X5", "SUV");
    testService.addCar("VL56MNO", "Mercedes-Benz", "C-Class", "Sedan");
    testService.addCar("HD67PQR", "Honda", "Civic", "Hatchback");

    vector<Car> sortedByPlateNr = testService.sortByPlateNumber();
    assert(sortedByPlateNr[0].get_producator() == "Ford");
    assert(sortedByPlateNr[1].get_producator() == "Audi");

    vector<Car> sortedByType = testService.sortByType();
    assert(sortedByType[0].get_tip() == "Hatchback");
    assert(sortedByType[1].get_tip() == "Hatchback");

    testService.addCar("IS34DEF", "Audi", "Q5", "SUV");
    vector<Car> sortedByCompanyAndModel = testService.sortByCompanyAndModel();
    assert(sortedByCompanyAndModel[0].get_producator() == "Audi");

}

void testFind()
{
    Repository testRepo;
    Validator testVal;
    Service testService{testRepo,testVal};

    testService.addCar("BV23ABC", "Ford", "Focus", "Hatchback");
    testService.addCar("TM03XYZ", "Toyota", "Corolla", "Sedan");
    testService.addCar("IS12DEF", "Volkswagen", "Golf", "Hatchback");
    testService.addCar("CJ78GHI", "Audi", "A4", "Sedan");
    testService.addCar("NT45JKL", "BMW", "X5", "SUV");
    testService.addCar("VL56MNO", "Mercedes-Benz", "C-Class", "Sedan");
    testService.addCar("HD67PQR", "Honda", "Civic", "Hatchback");

    try{
        Car c = testService.findCar("BV23ABC");
        assert(true);
    }
    catch(RepositoryException&){
        assert(false);
    }

    try{
        Car c = testService.findCar("ABCDEF");
        assert(false);
    }
    catch(RepositoryException&){
        assert(true);
    }
}

void testDelete()
{
    Repository testRepo;
    Validator testVal;
    Service testService{testRepo,testVal};

    testService.addCar("BV23ABC", "Ford", "Focus", "Hatchback");
    testService.addCar("TM03XYZ", "Toyota", "Corolla", "Sedan");
    testService.addCar("IS12DEF", "Volkswagen", "Golf", "Hatchback");
    testService.addCar("CJ78GHI", "Audi", "A4", "Sedan");
    testService.addCar("NT45JKL", "BMW", "X5", "SUV");
    testService.addCar("VL56MNO", "Mercedes-Benz", "C-Class", "Sedan");
    testService.addCar("HD67PQR", "Honda", "Civic", "Hatchback");

    try{
        testService.deleteCar("BV23ABC");
        assert(true);
    }
    catch(RepositoryException&)
    {
        assert(false);
    }

    try{
        testService.deleteCar("ABCDEF");
        assert(false);
    }
    catch(RepositoryException&)
    {
        assert(true);
    }
}

void testModify()
{
    Repository testRepo;
    Validator testVal;
    Service testService{testRepo,testVal};

    testService.addCar("BZ14GLK","MERCEDES-BENZ","C","Sedan");
    testService.addCar("CL23RER","VOLKSWAGWEN","Passat","Sedan");
    testService.addCar("CJ06AAA","VOLVO","EX90","SUV");

    assert(testService.getAllCars().size() == 3);

    try{
        testService.modifyCar("BZ14GLK","BZ23GLK");
        assert(true);
    }
    catch(ValidationException&)
    {
        assert(false);
    }

    try{
        testService.modifyCar("BZ14GLK","123");
        assert(false);
    }
    catch(ValidationException&)
    {
        assert(true);
    }

}

void testListaDeLucru()
{
    Repository testRepo;
    Validator testVal;
    Service testService{testRepo,testVal};
    ListaDeLucru testLista;

    assert(testLista.getAlldeSpalat().empty());

    testService.addCar("BV23ABC", "Ford", "Focus", "Hatchback");
    testService.addCar("TM03XYZ", "Toyota", "Corolla", "Sedan");
    testService.addCar("IS12DEF", "Volkswagen", "Golf", "Hatchback");
    testService.addCar("CJ78GHI", "Audi", "A4", "Sedan");
    testService.addCar("NT45JKL", "BMW", "X5", "SUV");
    testService.addCar("VL56MNO", "Mercedes-Benz", "C-Class", "Sedan");
    testService.addCar("HD67PQR", "Honda", "Civic", "Hatchback");

    string nr_i="HD67PQR";
    testService.addListaDeLucru(nr_i);
    assert(testService.getListaDeLucru().size()==1);

    testService.addRandomToListaDeLucru(3);
    assert(testService.getListaDeLucru().size()==3);

    testService.emptyListaDeLucru();
    assert(testService.getListaDeLucru().empty());
}

void testCreareRaport()
{
    Repository testRepo;
    Validator testVal;
    Service testService{testRepo,testVal};
    ListaDeLucru testLista;

    testService.addCar("BV23ABC", "Ford", "Focus", "Hatchback");
    testService.addCar("TM03XYZ", "Toyota", "Corolla", "Sedan");
    testService.addCar("IS12DEF", "Volkswagen", "Golf", "Hatchback");
    testService.addCar("CJ78GHI", "Audi", "A4", "Sedan");
    testService.addCar("NT45JKL", "BMW", "X5", "SUV");
    testService.addCar("VL56MNO", "Mercedes-Benz", "C-Class", "Sedan");
    testService.addCar("HD67PQR", "Honda", "Civic", "Hatchback");
    testService.addCar("CJ88PQR", "Honda", "Civic", "Hatchback");

    map<string,DTO> m=testService.creare_raport();
    assert(m["Focus"].get_count()==1);
}

void testExporta()
{
    Repository testRepo;
    Validator testVal;
    Service testSrv{testRepo,testVal};

    testSrv.addCar("BV23ABC", "Ford", "Focus", "Hatchback");
    testSrv.addCar("TM03XYZ", "Toyota", "Corolla", "Sedan");
    testSrv.addCar("IS12DEF", "Volkswagen", "Golf", "Hatchback");
    testSrv.addCar("CJ78GHI", "Audi", "A4", "Sedan");
    testSrv.addCar("NT45JKL", "BMW", "X5", "SUV");
    testSrv.addCar("VL56MNO", "Mercedes-Benz", "C-Class", "Sedan");
    testSrv.addCar("HD67PQR", "Honda", "Civic", "Hatchback");
    testSrv.addRandomToListaDeLucru(3);

    testSrv.exportaListaDeLucruCVS("testExport.cvs");
    ifstream in("testExport.cvs");
    assert(in.is_open());
    int countLines=0;
    while(!in.eof())
    {
        string line;
        in>>line;
        countLines++;
    }
    in.close();
    assert(countLines == 4); // avem si o linie libera

    testSrv.exportaListaDeLucruHTML("testExport.html");
    in.open("testExport.html");
    assert(in.is_open());

    try{
        testSrv.exportaListaDeLucruCVS("test/Export.cvs");
        assert(false);
    }
    catch(RepositoryException&){
        assert(true);
    }

    try{
        testSrv.exportaListaDeLucruHTML("a/b/c/Export.html");
        assert(false);
    }
    catch(RepositoryException&){
        assert(true);
    }
}

void testUndo()
{
    Repository testRepo;
    Validator testVal;
    Service testSrv{testRepo,testVal};

    testSrv.addCar("BV23ABC", "Ford", "Focus", "Hatchback");
    testSrv.addCar("TM03XYZ", "Toyota", "Corolla", "Sedan");
    testSrv.addCar("IS12DEF", "Volkswagen", "Golf", "Hatchback");
    testSrv.addCar("CJ78GHI", "Audi", "A4", "Sedan");

    assert(testSrv.getAllCars().size() == 4);
    testSrv.undo();
    assert(testSrv.getAllCars().size() == 3);
    testSrv.undo();
    testSrv.undo();
    testSrv.undo();
    try{
        testSrv.undo();
        assert(false);
    }
    catch (RepositoryException&){
        assert(true);
    }

    testSrv.addCar("BV23ABC", "Ford", "Focus", "Hatchback");
    testSrv.addCar("TM03XYZ", "Toyota", "Corolla", "Sedan");
    testSrv.addCar("IS12DEF", "Volkswagen", "Golf", "Hatchback");
    testSrv.addCar("CJ78GHI", "Audi", "A4", "Sedan");

    testSrv.deleteCar("BV23ABC");
    assert(testSrv.getAllCars().size() == 3);
    testSrv.undo();
    assert(testSrv.getAllCars().size() == 4);

    testSrv.modifyCar("BV23ABC","CJ12ABC");
    assert(testSrv.getAllCars().size() == 4);
    testSrv.undo();
    assert(testSrv.getAllCars().size() == 4);

}

void testeService()
{
    testAddService();
    testFilterService();
    testSort();
    testFind();
    testDelete();
    testModify();
    testListaDeLucru();
    testCreareRaport();
    testExporta();
    testUndo();
}
