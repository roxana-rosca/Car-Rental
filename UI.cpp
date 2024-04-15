#include "UI.h"
#include <iostream>

using namespace std;

void UI::printMenu() {
    cout<<"    -MENIU-"<<endl;
    cout<<"1. Adauga masina.\n";
    cout<<"2. Afiseaza masini.\n";
    cout<<"3. Filtrare.\n";
    cout<<"4. Sortare.\n";
    cout<<"5. Cauta masina.\n";
    cout<<"6. Sterge masina.\n";
    cout<<"7. Modifica numar de inmatriculare.\n";
    cout<<"8. Lista de lucru.\n";
    cout<<"9. Raport.\n";
    cout<<"10. UNDO.\n";
    cout<<"0. Iesire.\n";
}

void UI::uiAdd() {
    string nr_inmatriculare, producator, model, tip;

    cout<<"Adaugati o noua masina!\n";

    cout<<"Numar de inmatriculare: ";
    getline(cin>>ws, nr_inmatriculare);

    cout<<"Producator: ";
    getline(cin>>ws, producator);

    cout<<"Model: ";
    getline(cin>>ws, model);

    cout<<"Tip: ";
    getline(cin>>ws, tip);

    try{
        srv.addCar(nr_inmatriculare,producator,model,tip);
    }
    catch (RepositoryException& re)
    {
        cout<< re.getErrorMessage();
    }
    catch(ValidationException& ve)
    {
        cout<<"Date invalide pentru masina!\n";
        cout<<ve.getErrorMessages();
    }
}

void UI::printCars(const vector<Car> &allCars) {
    if(allCars.empty())
        cout<<"Nu exista masini.\n";
    else
    {
        cout<<"Numar masini din lista: "<<allCars.size()<<endl;
        for(const auto& car : allCars)
        {
            cout<<"Producator: "<<car.get_producator()<<" | Model: "<<car.get_model()<<" | Tip: "<<car.get_tip()<<" | Numar de inmatriculare: "<<car.get_nr_inmatriculare()<<endl;
        }
    }
}

void UI::uiFilter() {
    cout<<"Dupa ce criteriu doriti sa filtrati? (producator, tip):";
    string criteriu;
    cin>>criteriu;

    if(criteriu == "producator")
    {
        cout<<"Producatorul pentru care se filtreaza masinile: ";
        string prod_cautat;
        cin>>prod_cautat;
        printCars(srv.filtrareProducator(prod_cautat));
    }
    else if(criteriu == "tip")
    {
        cout<<"Tipul dupa care filtreaza masinile: ";
        string tip_cautat;
        cin>>tip_cautat;
        printCars(srv.filtrareTip(tip_cautat));
    }
    else
        cout<<"Nu se poate filtra dupa criteriul dat!"<<endl;
}

void UI::uiSort()
{
    cout<<"Dupa ce criteriu doriti sa sortati? (numar inmatriculare -ni , tip - t, producator+model - pm)\n";
    string criteriu;
    cin>>criteriu;
    if(criteriu == "ni")
    {
        cout<<"Sortare dupa numar de inmatriculare:\n";
        printCars(srv.sortByPlateNumber());
    }
    else if(criteriu == "t")
    {
        cout<<"Sortare dupa tipul masinii:\n";
        printCars(srv.sortByType());
    }
    else if(criteriu == "pm")
    {
        cout<<"Sortare dupa producator + model:\n";
        printCars(srv.sortByCompanyAndModel());
    }
    else
        cout<<"Nu se poate sorta dupa criteriul dat!\n";
}

void UI::uiFind() {
    cout<<"Cautati o masina dupa numarul de inmatriculare!\n";
    string nr_i;
    cout<<"Numar de inmatriculare: ";
    cin>>nr_i;
    try{
        Car car=srv.findCar(nr_i);
        cout<<"Masina cautata este:\n";
        cout<<"Producator: "<<car.get_producator()<<" | Model: "<<car.get_model()<<" | Tip: "<<car.get_tip()<<" | Numar de inmatriculare: "<<car.get_nr_inmatriculare()<<endl;

    }
    catch (RepositoryException& re)
    {
        cout<< re.getErrorMessage();
    }
}

void UI::uiDelete() {
    cout<<"Stergeti o masina!\n";
    string nr_i;
    cout<<"Numar de inmatriculare: ";
    cin>>nr_i;
    try{
        srv.deleteCar(nr_i);
        cout<<"Masina a fost stearsa cu succes!\n";
    }
    catch (RepositoryException& re)
    {
        cout<< re.getErrorMessage();
    }
}

void UI::uiModify() {
    cout<<"Modificati numarul de inmatriculare al unei masini!\n";
    cout<<"Dati numarul de inmatriculare a masinii pe care doriti sa o modificati: ";
    string nr_i;
    cin>>nr_i;
    cout<<"Dati noul numar de inmatriculare: ";
    string new_nr_i;
    cin>>new_nr_i;
    try{
        srv.modifyCar(nr_i,new_nr_i);
        cout<<"Masina a fost modificata cu succes!\n";
    }
    catch (RepositoryException& re)
    {
        cout<<re.getErrorMessage();
    }
    catch (ValidationException& ve)
    {
        cout<<ve.getErrorMessages();
    }
}

void UI::uiCreeazaRaport() {
    cout<<"Creati un raport folosind un dictionar!\n";
    cout<<"Raportul contine cate masini din fiecare model exista!\n";
    map<string,DTO> raport=srv.creare_raport();
    auto it= raport.begin();

    while(it!=raport.end())
    {
        cout<<"Model: "<<it->first<<" -> numar masini din modelul respectiv:"<<it->second.get_count()<<endl;
        ++it;
    }
}

void UI::uiUndo() {
    try{
        srv.undo();
        cout<<"Undo realizat cu succes!\n";
    }
    catch(RepositoryException& re){
        cout<<re.getErrorMessage();
    }
}

void UI::addDefaultCars() {
    srv.addCar("BV23ABC", "Ford", "Focus", "Hatchback");
    srv.addCar("TM03XYZ", "Toyota", "Corolla", "Sedan");
    srv.addCar("IS12DEF", "Volkswagen", "Golf", "Hatchback");
    srv.addCar("CJ78GHI", "Audi", "A4", "Sedan");
    srv.addCar("NT45JKL", "BMW", "X5", "SUV");
    srv.addCar("VL56MNO", "Mercedes-Benz", "C-Class", "Sedan");
    srv.addCar("HD67PQR", "Honda", "Civic", "Hatchback");
    srv.addCar("PH09ABC", "Audi", "A3", "Hatchback");
    srv.addCar("IS34DEF", "Audi", "Q5", "SUV");
    srv.addCar("CJ34ABC", "Audi", "Q5", "SUV");
    srv.addCar("SM48MNO", "Mercedes-Benz", "C-Class", "Sedan");
    srv.addCar("MM56MNO", "Mercedes-Benz", "C-Class", "Sedan");
}

void UI::printListaDeLucruMenu() {
    cout<<"-MENIU LISTA DE LUCRU-"<<endl;
    cout<<"1. Programarea unei masini la spalatorie."<<endl;
    cout<<"2. Trimiterea unor masini random la spalatorie."<<endl;
    cout<<"3. Golirea listei de lucru."<<endl;
    cout<<"4. Afisarea listei de lucru."<<endl;
    cout<<"5. Export CVS."<<endl;
    cout<<"6. Export HTML."<<endl;
    cout<<"0. Inapoi la meniul principal."<<endl;
}

void UI::uiAddListaDeLucru() {
    cout<<"Programarea unei masini la spalatorie."<<endl;
    string nr_i;
    cout<<"Dati numarul de inmatriculare:";
    cin>>nr_i;
    try{
        srv.addListaDeLucru(nr_i);
        cout<<"Masina adaugata cu succes!"<<endl;
    }
    catch (RepositoryException& re){
        cout<<re.getErrorMessage();
    }
}

void UI::uiAddRandomToListaDeLucru() {
    int howMany;
    cout<<"Cate masini doriti sa trimiteti la spalat?";
    cin>>howMany;

    try{
        int howManyAdded = srv.addRandomToListaDeLucru(howMany);
        cout<<"S-au adaugat "<<howManyAdded<<" masini.\n";
    }
    catch(RepositoryException& re){
        cout<< re.getErrorMessage();
    }
}

void UI::uiEmptyListaDeLucru() {
    srv.emptyListaDeLucru();
    cout<<"S-au sters toate masinile din lista de lucru curenta!\n";
}

template<typename T>
T myread(const char* msg){
    T cmd{};
    while(true){
        cout<<msg;
        cin>>cmd;
        const bool fail = cin.fail();
        cin.clear(); // resetez failbit
        const auto &aux = cin.ignore(1000,'\n');
        if(!fail && aux.gcount() <= 1){
            break; // am reusit sa citesc un numar
        }
    }
    return cmd;
}

void UI::uiListaDeLucru() {
    int running = 1;
    int cmd;
    while(running)
    {
        printListaDeLucruMenu();
        cout<<">>>";
        cin>>cmd;
        switch (cmd) {
            case 1:
                uiAddListaDeLucru();
                break;
            case 2:
                uiAddRandomToListaDeLucru();
                break;
            case 3:
                uiEmptyListaDeLucru();
                break;
            case 4:
                printCars(srv.getListaDeLucru());
                break;
            case 5:
                srv.exportaListaDeLucruCVS(myread<string>("CVS file:"));
                break;
            case 6:
                srv.exportaListaDeLucruHTML(myread<string>("HTML file:"));
                break;
            case 0:
                running=0;
                cout<<"Revenire meniu principal! ->"<<endl;
                break;
            default:
                cout<<"Optiune invalida! Reincercati!\n";
                break;
        }
    }
}

void UI::run(){
    int running = 1;
    int cmd;
    addDefaultCars();
    while(running)
    {
        printMenu();
        cout<<">>>";
        cin>>cmd;
        switch(cmd)
        {
            case 1:
                uiAdd();
                break;
            case 2:
                printCars(srv.getAllCars());
                break;
            case 3:
                uiFilter();
                break;
            case 4:
                uiSort();
                break;
            case 5:
                uiFind();
                break;
            case 6:
                uiDelete();
                break;
            case 7:
                uiModify();
                break;
            case 8:
                uiListaDeLucru();
                break;
            case 9:
                uiCreeazaRaport();
                break;
            case 10:
                uiUndo();
                break;
            case 0:
                running = 0;
                cout<<"La revedere!!\n";
                break;
            default:
                cout<<"Optiune invalida! Reincercati!\n";
                break;
        }
    }
}
