#pragma once
#include <QWidget.h>
#include "ListaDeLucru.h"
#include <QListWidget.h>
#include <QLayout.h>
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
#include <QTableWidget>
#include <QPainter>

class ListaDeLucruGUI:public QWidget, public Observer{
friend class GUI;
friend class GUIModel;
private:
    Service &srv;

    QHBoxLayout* mainLayout = new QHBoxLayout;

    QListWidget* carsListWidget = new QListWidget;
    //QTableWidget* carsTableWidget = new QTableWidget;

    QPushButton* btnGolesteLista;
    QPushButton* btnAdaugaInLista;
    QPushButton* btnGenereazaRandom;
    QPushButton* btnExport;
    QPushButton* btnReload;

    QGroupBox* groupBox1 = new QGroupBox(tr("Adauga"));
    QGroupBox* groupBox2 = new QGroupBox(tr("Genereaza"));
    QGroupBox* groupBox3 = new QGroupBox(tr("Export"));

    QLineEdit* editAdauga;
    QLineEdit* editGenereaza;
    QLineEdit* editExport;

    QLabel* lAdauga = new  QLabel("Numar de inmatriculare:");
    QLabel* lGenereaza = new QLabel("Numar de masini:");
    QLabel* lExport = new QLabel("Nume fisier:");

    // observer
    QPushButton* btnClose;
    QPushButton* btnLabelWindow;
    QPushButton* btnTableWindow;

    // desenare
    QBrush bgBrush;
    QPushButton* btnDrawWindow;

    void initGUIcomponents();

    void connectSignalSlots();

    void reloadList(const vector<Car>& cars);

    void addToList();

    void addRandomToList();

    void exportList();

    void update() override{
        this->reloadList(srv.getListaDeLucru());
    }

public:
    ListaDeLucruGUI(Service& s);
};

class ListaDeLucruGUILabel:public QWidget, public Observer{
private:
    ListaDeLucru& l;

    QLabel* lblNoCars;
    QLineEdit* editNoCars;

    void initGUI(){
        QHBoxLayout* ly = new QHBoxLayout{};
        this->setLayout(ly);
        lblNoCars = new QLabel{"Numar de masini:"};
        editNoCars = new QLineEdit{};
        ly->addWidget(lblNoCars);
        ly->addWidget(editNoCars);
        setAttribute(Qt::WA_DeleteOnClose); // daca vreau sa se distruga fereastra imediat dupa inchidere
        l.addObserver(this);
    }

    void update() override{
        this->editNoCars->setText(QString::number(l.getAlldeSpalat().size()));
    }

    ~ListaDeLucruGUILabel(){
        l.removeObserver(this);
    }

public:
    ListaDeLucruGUILabel(ListaDeLucru& lista): l{lista}{
        initGUI();
    };
};

class ListaDeLucruTable: public QWidget, public Observer{
private:
    ListaDeLucru &l;

    QTableWidget* table;
    QPushButton* btnEmpty;

    void initGUI(){
        QHBoxLayout* ly = new QHBoxLayout;
        this->setLayout(ly);

        table = new QTableWidget;
        btnEmpty = new QPushButton{"Empty"};

        ly->addWidget(table);
        ly->addWidget(btnEmpty);

        setAttribute(Qt::WA_DeleteOnClose);
        l.addObserver(this);
    }

    void reloadTableData(const vector<Car> &cars){
        this->table->setColumnCount(4);
        this->table->setRowCount(cars.size());
        for(int i=0;i<cars.size();i++){
            table->setItem(i,0,new QTableWidgetItem(QString::fromStdString(cars[i].get_nr_inmatriculare())));
            table->setItem(i,1,new QTableWidgetItem(QString::fromStdString(cars[i].get_producator())));
            table->setItem(i,2,new QTableWidgetItem(QString::fromStdString(cars[i].get_model())));
            table->setItem(i,3,new QTableWidgetItem(QString::fromStdString(cars[i].get_tip())));

        }
    }

    void connectSignalSlots(){
        l.addObserver(this);

        QObject::connect(btnEmpty, &QPushButton::clicked,[&](){
            l.emptyListaDeLucru();
            reloadTableData(l.getAlldeSpalat());
        });
    }

public:
    ListaDeLucruTable(ListaDeLucru& lista): l{lista}{
        initGUI();
        connectSignalSlots();
    }

    void update() override{
        this->reloadTableData(l.getAlldeSpalat());
    }

    ~ListaDeLucruTable(){
        l.removeObserver(this);
    }
};

class ListaDeLucruGUIDraw: public QWidget, public Observer{
private:
    ListaDeLucru& l;

    void paintEvent(QPaintEvent* ev) override{
        QPainter p{this};
        int x=0;
        int y=0;
        for(auto car:l.getAlldeSpalat()){
            x = rand() % 400 + 1;
            y = rand() % 400 + 1;
            QRectF target(x,y,100,94);
            QRectF source(0,0,732,720);
            QImage image(R"(C:\Users\roxan\CLionProjects\oop\inchiriere_masini_QT\car1.png)");

            p.drawImage(target,image,source);

            x+=40;
        }
    }

    void update() override{
        repaint();
    }

    ~ListaDeLucruGUIDraw(){
        l.removeObserver(this);
    }
public:
    ListaDeLucruGUIDraw(ListaDeLucru& lista):l{lista}{
        l.addObserver(this);
    }
};

