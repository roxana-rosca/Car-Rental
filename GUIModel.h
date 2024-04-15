#pragma once
#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include "Service.h"
#include "ListaDeLucruGUI.h"
#include "MyTableModel.h"

using namespace std;

class GUIModel: public QWidget {
private:
    Service &srv;

    ListaDeLucruGUI* cos;

    // layout main
    QHBoxLayout* lyMain = new QHBoxLayout;

    // adaugare
    QGroupBox* groupBox1 = new QGroupBox(tr("Adaugare"));

    QLabel* lblNrInmatriculare = new QLabel{"Numar de inmatriculare:"};
    QLabel* lblProducator = new QLabel{"Producator:"};
    QLabel* lblModel = new QLabel{"Model:"};
    QLabel* lblTip = new QLabel{"Tip:"};

    QLineEdit* editNrInmatriculare;
    QLineEdit* editProducator;
    QLineEdit* editModel;
    QLineEdit* editTip;

    QPushButton* btnAddCar;

    // sortare
    QGroupBox* groupBox = new QGroupBox(tr("Sortare:"));

    QRadioButton* radioSrtNrInmatriculare = new QRadioButton(QString::fromStdString("Numar de inmatriculare"));
    QRadioButton* radioSrtTip = new QRadioButton(QString::fromStdString("Tip"));
    QRadioButton* radioSrtProducatorModel = new QRadioButton(QString::fromStdString("Producator+Model"));
    QPushButton* btnSortCars;


    // filtrare
    QGroupBox* groupBox2 = new QGroupBox(tr("Filtrare"));

    QLabel* lblFilterCriteriaProducer = new QLabel{"Producator dupa care se filtreaza:"};
    QLineEdit* editFilterProducator;
    QPushButton* btnFilterCarsByProducer;

    QLabel* lblFilterCriteriaType = new QLabel{"Tipul dupa care se filtreaza:"};
    QLineEdit* editFilterTip;
    QPushButton* btnFilterCarsByType;

    // stergere
    QGroupBox* groupBox3 = new QGroupBox(tr("Stergere"));

    QLabel* lblNrDeInmDeSters = new QLabel{"Numarul de inmatriculare al masinii care se va sterge:"};
    QLineEdit* editStergere;
    QPushButton* btnStergeMasina;

    // modificare
    QGroupBox* groupBox4 = new QGroupBox(tr("Modificare"));

    QLabel* lblNrDeInmDeModif = new QLabel{"Numar de inmatriculare curent:"};
    QLabel *lblNrDeInmNou = new QLabel{"Numar de inmatriculare nou:"};

    QLineEdit* editModif1;
    QLineEdit* editModif2;

    QPushButton* btnModifica;

    // reload data
    QPushButton* btnReloadData;

    // UNDO
    QPushButton* btnUndo;

    // COS
    QPushButton* btnCos;

    // layout butoane dinamice
    QVBoxLayout* lyBtnDinamice = new QVBoxLayout;
    QWidget* wBtnDinamice = new QWidget;

    // tabel masini
    //QTableWidget* tableCars;
    MyTableModel* model;
    QTableView* tableCars = new QTableView;

    void initializeGUIComponents();

    void connectSignalSlots();

    void reloadCarList(vector<Car> cars);

    void reloadDynBtns();

    void clearLayout();

public:
    GUIModel(Service& carSrv):srv{carSrv}{
        initializeGUIComponents();

        this->model = new MyTableModel{srv.getAllCars()};
        this->tableCars->setModel(model);

        connectSignalSlots();
        reloadCarList(srv.getAllCars());
        reloadDynBtns();

        cos = new ListaDeLucruGUI(srv);
        cos->initGUIcomponents();
        cos->connectSignalSlots();

    }

    void guiAddCar();


    void guiDeleteCar();


    void guiModifyCar();
};



