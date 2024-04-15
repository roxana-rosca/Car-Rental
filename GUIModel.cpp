#include "GUIModel.h"

void GUIModel::initializeGUIComponents() {
    // QHBoxLayout
    // in stanga: butoane+labels+qlineedits
    // in dreapta: tabelul cu masini
    // se adauga comp. incepand din stanga, pe orizontala

    // main layout
    this->setLayout(lyMain);

    // left part of the window - layout vertical
    QWidget* left = new QWidget;
    QVBoxLayout* lyLeft = new QVBoxLayout;
    left->setLayout(lyLeft);

    // adaugare masina
    //QWidget* form = new QWidget;
    QFormLayout* lyForm = new QFormLayout;
    //form->setLayout(lyForm);
    groupBox1->setLayout(lyForm);

    editNrInmatriculare = new QLineEdit;
    editProducator = new QLineEdit;
    editModel = new QLineEdit;
    editTip = new QLineEdit;

    lyForm->addRow(lblNrInmatriculare, editNrInmatriculare);
    lyForm->addRow(lblProducator, editProducator);
    lyForm->addRow(lblModel, editModel);
    lyForm->addRow(lblTip, editTip);
    btnAddCar = new QPushButton("Adauga o masina");
    lyForm->addWidget(btnAddCar);

    // adaug toate comp legate de adaugare masina
    //lyLeft->addWidget(form);
    lyLeft->addWidget(groupBox1);

    // GroupBox pentru RadioButtons-urile care corespund criteriilor de sortare
    QVBoxLayout* lySortBox = new QVBoxLayout;
    this->groupBox->setLayout(lySortBox);
    lySortBox->addWidget(radioSrtNrInmatriculare);
    lySortBox->addWidget(radioSrtTip);
    lySortBox->addWidget(radioSrtProducatorModel);

    btnSortCars = new QPushButton("Sorteaza masini");
    lySortBox->addWidget(btnSortCars);

    lyLeft->addWidget(groupBox);


    // Form pentru filtrare producator


    //QWidget* formFilter = new QWidget;
    QFormLayout* lyFormFilter = new QFormLayout;
    //formFilter->setLayout(lyFormFilter);
    groupBox2->setLayout(lyFormFilter);

    editFilterProducator = new QLineEdit();
    lyFormFilter->addRow(lblFilterCriteriaProducer, editFilterProducator);
    btnFilterCarsByProducer = new QPushButton("Filtreaza masini dupa producator");
    lyFormFilter->addWidget(btnFilterCarsByProducer);


    //lyLeft->addWidget(formFilter);
    //lyLeft->addWidget(groupBox2);


    // Form pentru filtrare tip
    //QWidget* formFilter1 = new QWidget;
    //QFormLayout* lyFormFilter1 = new QFormLayout;
    //formFilter1->setLayout(lyFormFilter1);
    editFilterTip = new QLineEdit();
    lyFormFilter->addRow(lblFilterCriteriaType,editFilterTip);
    //lyFormFilter1->addRow(lblFilterCriteriaType,editFilterTip);
    btnFilterCarsByType = new QPushButton("Filtreaza masini dupa tip");
    //lyFormFilter1->addWidget(btnFilterCarsByType);
    lyFormFilter->addWidget(btnFilterCarsByType);

    //lyLeft->addWidget(formFilter1);
    lyLeft->addWidget(groupBox2);

    // Form pentru stergere
    //QWidget* formDelete = new QWidget;
    QFormLayout* lyFormDelete = new QFormLayout;

    groupBox3->setLayout(lyFormDelete);

    //formDelete->setLayout(lyFormDelete);
    editStergere = new QLineEdit();
    lyFormDelete->addRow(lblNrDeInmDeSters,editStergere);
    btnStergeMasina = new QPushButton("Sterge masina");
    lyFormDelete->addWidget(btnStergeMasina);
    //lyLeft->addWidget(formDelete);
    lyLeft->addWidget(groupBox3);

    // Form pentru modificare
    QFormLayout* lyFormModify = new QFormLayout;

    groupBox4->setLayout(lyFormModify);

    editModif1 = new QLineEdit();
    lyFormModify->addRow(lblNrDeInmDeModif,editModif1);
    editModif2 = new QLineEdit();
    lyFormModify->addRow(lblNrDeInmNou,editModif2);
    btnModifica = new QPushButton("Modifica masina");
    lyFormModify->addWidget(btnModifica);

    lyLeft->addWidget(groupBox4);


    // butoane dinamice
    wBtnDinamice->setLayout(lyBtnDinamice);
    lyBtnDinamice->addWidget(wBtnDinamice);
    //lyLeft->addWidget(wBtnDinamice);
    lyMain->addWidget(wBtnDinamice);


    // right part of the window
    QWidget* right = new QWidget;
    QVBoxLayout* lyRight = new QVBoxLayout;
    right->setLayout(lyRight);

    /*
    int noLines = 10;
    int noColumns = 4;
    this->tableCars = new QTableWidget{noLines, noColumns};

    // header tabel
    QStringList tblHeaderList;
    tblHeaderList<<"Numar de inmatriculare"<<"Producator"<<"Model"<<"Tip";
    this->tableCars->setHorizontalHeaderLabels(tblHeaderList);

    // redimensionare celule din tabel in functie de continut
    this->tableCars->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
*/
    lyRight->addWidget(tableCars);

    // Reincarcarea datelor
    btnReloadData = new QPushButton("Reload data");
    lyRight->addWidget(btnReloadData);

    // Buton UNDO
    btnUndo = new QPushButton("UNDO");
    lyRight->addWidget(btnUndo);

    // Buton COS
    btnCos = new QPushButton("Lista de lucru");
    lyRight->addWidget(btnCos);

    lyMain->addWidget(left);
    lyMain->addWidget(right);
}


void GUIModel::reloadCarList(vector<Car> cars) {
    this->model->setCars(cars);
}


void GUIModel::connectSignalSlots() {
    // adaugare
    QObject::connect(btnAddCar, &QPushButton::clicked, this,&GUIModel::guiAddCar);

    // sortare
    QObject::connect(btnSortCars, &QPushButton::clicked,[&](){
        if(this->radioSrtNrInmatriculare->isChecked()){
            this->reloadCarList(srv.sortByPlateNumber());
        }
        else if(this->radioSrtTip->isChecked()){
            this->reloadCarList(srv.sortByType());
        }
        else if(this->radioSrtProducatorModel->isChecked()){
            this->reloadCarList(srv.sortByCompanyAndModel());
        }
    });

    // reload
    QObject::connect(btnReloadData, &QPushButton::clicked,[&](){
        this->reloadCarList(srv.getAllCars());
    });

    // filtrare dupa producator
    QObject::connect(btnFilterCarsByProducer,&QPushButton::clicked,[&](){
        string filterP = this->editFilterProducator->text().toStdString();
        if(!srv.filtrareProducator(filterP).empty()){this->reloadCarList(srv.filtrareProducator(filterP));}
        else{QMessageBox::warning(this,"Warning",QString::fromStdString("Producator inexistent!"));}

        editFilterProducator->clear();
    });

    // filtrare dupa tip
    QObject::connect(btnFilterCarsByType,&QPushButton::clicked,[&](){
        string filterT = this->editFilterTip->text().toStdString();
        if(!srv.filtrareTip(filterT).empty()){this->reloadCarList(srv.filtrareTip(filterT));}
        else{QMessageBox::warning(this,"Warning",QString::fromStdString("Tip inexistent!"));}
        editFilterTip->clear();
    });

    // Stergere
    QObject::connect(btnStergeMasina, &QPushButton::clicked, this,&GUIModel::guiDeleteCar);

    // Modificare
    QObject::connect(btnModifica,&QPushButton::clicked,this,&GUIModel::guiModifyCar);

    // UNDO
    QObject::connect(btnUndo,&QPushButton::clicked,[&](){
        try{
            srv.undo();
            this->reloadCarList(srv.getAllCars());
            this->reloadDynBtns();
            QMessageBox::information(this,"Info",QString::fromStdString("Undo realizat cu succes!"));
        }
        catch(RepositoryException&){
            QMessageBox::warning(this,"Warning",QString::fromStdString("Nu se poate face undo!"));
        }
    });

    // cos
    QObject::connect(btnCos,&QPushButton::clicked,[&](){
        cos->show();
    });
}

void GUIModel::guiAddCar() {
    try{
        // preluare detalii din QLineEdit-uri
        string nr_inmatriculare = editNrInmatriculare->text().toStdString();
        string producator = editProducator->text().toStdString();
        string model = editModel->text().toStdString();
        string tip = editTip->text().toStdString();

        // golim QLineEdit-urile
        editNrInmatriculare->clear();
        editProducator->clear();
        editModel->clear();
        editTip->clear();

        this->srv.addCar(nr_inmatriculare,producator,model,tip);
        this->reloadCarList(this->srv.getAllCars());


        // afisare mesaj pentru a anunta utilizatorul ca masina s-a adaugat cu succes
        QMessageBox::information(this,"Info",QString::fromStdString("Masina adaugata cu succes!"));
        this->reloadDynBtns();
    }
    catch(RepositoryException& re){
        QMessageBox::warning(this,"Warning",QString::fromStdString(re.getErrorMessage()));
    }
    catch(ValidationException& ve){
        QMessageBox::warning(this,"Warning",QString::fromStdString(ve.getErrorMessages()));
    }
}

void GUIModel::clearLayout() {
    QLayoutItem* item;
    while((item = lyBtnDinamice->takeAt(0)))
    {
        if(item->layout())
        {
            clearLayout();
            delete item->layout();
        }
        if(item->widget())
        {
            delete item->widget();
        }
        delete item;
    }
}

void GUIModel::reloadDynBtns() {
    clearLayout();
    map<string, DTO> v = srv.creare_raport();
    auto it = v.begin();
    while(it!=v.end())
    {
        auto btnModel = new QPushButton{QString::fromStdString(it->first)};
        lyBtnDinamice->addWidget(btnModel);
        int nr_masini=it->second.get_count();
        string s="Numar masini: "+ to_string(nr_masini);
        QObject::connect(btnModel,&QPushButton::clicked,[this,btnModel,s](){
            QMessageBox::information(nullptr,"Info",QString::fromStdString(s));
        });
        ++it;
    }
}



void GUIModel::guiDeleteCar() {
    try{
        // preluare date din QLineEdit-uri
        string nr_inm = editStergere->text().toStdString();

        this->srv.deleteCar(nr_inm);
        this->reloadCarList(this->srv.getAllCars());


        // golire QLineEdit
        editStergere->clear();

        // afisare mesaj pentru a anunta utilizatorul ca masina s-a adaugat cu succes
        QMessageBox::information(this,"Info",QString::fromStdString("Masina stearsa cu succes!"));
        this->reloadDynBtns();
        //guiReloadDynBtns(w,lyRaport);
    }
    catch(RepositoryException& re){
        QMessageBox::warning(this,"Warning",QString::fromStdString(re.getErrorMessage()));
        // golire QLineEdit
        editStergere->clear();
    }
}

void GUIModel::guiModifyCar() {
    try
    {
        // preluare date din QLineEdit-uri
        string nr_vechi = editModif1->text().toStdString();
        string nr_nou = editModif2->text().toStdString();

        this->srv.modifyCar(nr_vechi,nr_nou);

        this->reloadCarList(this->srv.getAllCars());

        // golire QLineEdit-uri
        editModif1->clear();
        editModif2->clear();

        QMessageBox::information(this,"Info",QString::fromStdString("Masina modificata cu succes!"));
        this->reloadDynBtns();
    }
    catch(RepositoryException& re){
        QMessageBox::warning(this,"Warning",QString::fromStdString(re.getErrorMessage()));
        // golire QLineEdit
        editStergere->clear();
    }
    catch(ValidationException& ve){
        QMessageBox::warning(this,"Warning",QString::fromStdString(ve.getErrorMessages()));
        // golire QLineEdit
        editStergere->clear();
    }
}