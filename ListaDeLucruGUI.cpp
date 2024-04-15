#include "ListaDeLucruGUI.h"
#include <qtimer.h>


ListaDeLucruGUI::ListaDeLucruGUI(Service &s):srv(s) {
    //initGUIcomponents();
    //connectSignalSlots();
}

void ListaDeLucruGUI::initGUIcomponents() {
    setLayout(mainLayout);


    QWidget* stanga = new QWidget;
    QVBoxLayout* lyStanga = new QVBoxLayout;
    stanga->setLayout(lyStanga);

    btnGolesteLista = new QPushButton("Goleste lista");
    btnAdaugaInLista = new QPushButton("Adauga");
    btnGenereazaRandom = new QPushButton("Genereaza");
    btnExport = new QPushButton("Export");
    btnReload = new QPushButton("Reload");

    editAdauga = new QLineEdit;
    editGenereaza = new QLineEdit;
    editExport = new QLineEdit;


    // adauga in cos
    QVBoxLayout* lyAdauga1 = new QVBoxLayout;

    QHBoxLayout* lyAdauga2 = new QHBoxLayout;
    lyAdauga2->addWidget(lAdauga);
    lyAdauga2->addWidget(editAdauga);
    QWidget* w1 = new QWidget;
    w1->setLayout(lyAdauga2);

    lyAdauga1->addWidget(w1);
    lyAdauga1->addWidget(btnAdaugaInLista);
    groupBox1->setLayout(lyAdauga1);

    lyStanga->addWidget(groupBox1);

    // generare random
    QVBoxLayout* lyRandom1 = new QVBoxLayout;
    QHBoxLayout* lyRandom2 = new QHBoxLayout;
    lyRandom2->addWidget(lGenereaza);
    lyRandom2->addWidget(editGenereaza);
    QWidget* w2 = new QWidget;
    w2->setLayout(lyRandom2);

    lyRandom1->addWidget(w2);
    lyRandom1->addWidget(btnGenereazaRandom);
    groupBox2->setLayout(lyRandom1);

    lyStanga->addWidget(groupBox2);

    // export
    QVBoxLayout* lyExport1 = new QVBoxLayout;
    QHBoxLayout* lyExport2 = new QHBoxLayout;
    lyExport2->addWidget(lExport);
    lyExport2->addWidget(editExport);
    QWidget* w3 = new QWidget;
    w3->setLayout(lyExport2);

    lyExport1->addWidget(w3);
    lyExport1->addWidget(btnExport);
    groupBox3->setLayout(lyExport1);

    lyStanga->addWidget(groupBox3);

    // golire lista
    lyStanga->addWidget(btnGolesteLista);


    btnClose = new QPushButton{"Close"};

    // observer
    btnLabelWindow = new QPushButton{"Fereastra label"};
    btnLabelWindow->setStyleSheet("background-color: cyan");
    btnTableWindow = new QPushButton{"Fereastra lista de lucru tabel"};
    btnTableWindow->setStyleSheet("background-color: magenta");

    lyStanga->addWidget(btnLabelWindow);
    lyStanga->addWidget(btnTableWindow);

    // colorare
    btnDrawWindow = new QPushButton{"Fereastra desen"};
    btnDrawWindow->setStyleSheet("background-color: yellow");
    lyStanga->addWidget(btnDrawWindow);

    lyStanga->addWidget(btnClose);

    // tabel masini
    QWidget* dreapta = new QWidget;
    QVBoxLayout* lyDreapta = new QVBoxLayout;

    dreapta->setLayout(lyDreapta);

    // tabel masini
    /*int noLines = 10;
    int noColumns = 4;
    carsTableWidget = new QTableWidget{noLines,noColumns};

    // header tabel
    QStringList tblHeaderList;
    tblHeaderList<<"Numar de inmatriculare"<<"Producator"<<"Model"<<"Tip";
    this->carsTableWidget->setHorizontalHeaderLabels(tblHeaderList);

    // redimensionare celule din tabel in functie de continut
    this->carsTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    lyDreapta->addWidget(carsTableWidget);*/

    carsListWidget = new QListWidget;
    lyDreapta->addWidget(carsListWidget);

    lyDreapta->addWidget(btnReload);

    mainLayout->addWidget(stanga);
    mainLayout->addWidget(dreapta);


}

void ListaDeLucruGUI::addToList() {
    try {
        string nr_inm = editAdauga->text().toStdString();
        editAdauga->clear();

        this->srv.addListaDeLucru(nr_inm);
        this->reloadList(this->srv.getListaDeLucru());
    }
    catch(RepositoryException& re){
        QMessageBox::warning(this,"Warning",QString::fromStdString(re.getErrorMessage()));
    }

}

void ListaDeLucruGUI::addRandomToList() {

    int nr = editGenereaza->text().toInt();
    editGenereaza->clear();

    this->srv.addRandomToListaDeLucru(nr);
    this->reloadList(this->srv.getListaDeLucru());

}

void ListaDeLucruGUI::exportList() {
    string nume_fis=editExport->text().toStdString();
    editExport->clear();

    if(nume_fis.find(".html")!=std::string::npos)
    {
        srv.exportaListaDeLucruHTML(nume_fis);
        this->reloadList(srv.getListaDeLucru());
        QMessageBox::information(this,"Info",QString::fromStdString("Fisier creat cu succes!"));
    }
    else if(nume_fis.find(".cvs")!=std::string::npos)
    {
        srv.exportaListaDeLucruCVS(nume_fis);
        this->reloadList(srv.getListaDeLucru());
        QMessageBox::information(this,"Info",QString::fromStdString("Fisier creat cu succes!"));
    }
}

void ListaDeLucruGUI::connectSignalSlots()
{
    // golire lista
    QObject::connect(btnGolesteLista,&QPushButton::clicked,[&](){
        srv.emptyListaDeLucru();
        this->reloadList(srv.getListaDeLucru());
    });

    // reload
    QObject::connect(btnReload,&QPushButton::clicked,[&](){
        this->reloadList(srv.getListaDeLucru());
    });

    // adaugare
    QObject::connect(btnAdaugaInLista,&QPushButton::clicked,this,&ListaDeLucruGUI::addToList);

    // generare random
    QObject::connect(btnGenereazaRandom,&QPushButton::clicked,this,&ListaDeLucruGUI::addRandomToList);

    // export
    QObject::connect(btnExport,&QPushButton::clicked,this,&ListaDeLucruGUI::exportList);

    // close
    QObject::connect(btnClose,&QPushButton::clicked,this, &ListaDeLucruGUI::close);

    // observer!!
    srv.getListaDeLucruNew().addObserver(this);

    // label window
    QObject::connect(btnLabelWindow,&QPushButton::clicked,this,[&](){
        auto labelWindow = new ListaDeLucruGUILabel{srv.getListaDeLucruNew()};
        labelWindow->show();
    });

    // table window
    QObject::connect(btnTableWindow,&QPushButton::clicked,this,[&](){
       auto tableWindow = new ListaDeLucruTable{srv.getListaDeLucruNew()};
       tableWindow->show();
    });

    // desenare
    QObject::connect(btnDrawWindow,&QPushButton::clicked,this,[&](){
        auto drawWindow = new ListaDeLucruGUIDraw{srv.getListaDeLucruNew()};
        drawWindow->show();
    });
}

void ListaDeLucruGUI::reloadList(const vector<Car>& cars)
{
    /*this->carsTableWidget->clearContents();
    this->carsTableWidget->setRowCount(cars.size());

    int lineNumber=0;
    for(auto& car:cars){
        this->carsTableWidget->setItem(lineNumber,0,new QTableWidgetItem(QString::fromStdString(car.get_nr_inmatriculare())));
        this->carsTableWidget->setItem(lineNumber,1,new QTableWidgetItem(QString::fromStdString(car.get_producator())));
        this->carsTableWidget->setItem(lineNumber,2,new QTableWidgetItem(QString::fromStdString(car.get_model())));
        this->carsTableWidget->setItem(lineNumber,3,new QTableWidgetItem(QString::fromStdString(car.get_tip())));
        lineNumber++;
    }*/

    this->carsListWidget->clear();

    QListWidgetItem* item1 = new QListWidgetItem;
    string text1="Numar de inmatriculare Producator Model Tip";
    item1->setText(QString::fromStdString(text1));
    this->carsListWidget->addItem(item1);

    int lineNr=1;
    for(auto& car:cars) {
        QListWidgetItem* item = new QListWidgetItem;
        string text = "  "+car.get_nr_inmatriculare()+"  "+car.get_producator()+"  "+car.get_model()+"  "+car.get_tip();
        item->setText(QString::number(lineNr)+QString::fromStdString(text));
        this->carsListWidget->addItem(item);
        lineNr++;
    }
}