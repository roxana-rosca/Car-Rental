#pragma once
#include <QAbstractTableModel>
#include <QBrush>
#include <Qt>
#include "Car.h"
#include <utility>
#include <vector>
#include <QFont>

using namespace std;

class MyTableModel: public QAbstractTableModel{
private:
    vector<Car> cars;
public:
    // constructor
    MyTableModel(vector<Car>& c): cars{c}{

    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override{
        return cars.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override{
        return 4;
    }

    //Returns the data stored under the given role for the item referred to by the index.
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override{
        // font roz
        if(role == Qt::ForegroundRole){
            auto car = this->cars[index.row()];
            if(car.get_tip() == "SUV")
                return QBrush(Qt::magenta);
        }

        // liniile cu ultima cifra 1
        if(role == Qt::FontRole){
            QFont f;
            f.setItalic(index.row() % 10 == 1);
            f.setBold(index.row() % 10 == 1);
            return f;
        }

        // background galben
        if(role == Qt::BackgroundRole){
            int row = index.row();
            QModelIndex i = index.sibling(index.row(),1);
            if(i.data().toString() == "Audi"){
                QBrush bg(Qt::yellow);
                return bg;
            }
        }

        if(role == Qt::DisplayRole){
            Car c = cars[index.row()];
            if(index.column()==0){
                return QString::fromStdString(c.get_nr_inmatriculare());
            }
            else if(index.column()==1){
                return QString::fromStdString(c.get_producator());
            }
            else if(index.column()==2){
                return QString::fromStdString(c.get_model());
            }
            else if(index.column()==3){
                return QString::fromStdString(c.get_tip());
            }
        }

        return QVariant{};
    }

    void setCars(vector<Car> c){
        this->cars = std::move(c);
        auto topLeft = createIndex(0,0);
        auto bottomRight = createIndex(rowCount(), columnCount());
        beginResetModel();
        endResetModel();
        //emit dataChanged(topLeft,bottomRight); // nu merge!

    }

    Qt::ItemFlags flags(const QModelIndex& /*index*/) const{
        return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
    }

    QVariant headerData(int section, Qt::Orientation orientation,int role) const{
        if(role == Qt::DisplayRole){
            if(orientation == Qt::Horizontal){
                switch (section) {
                    case 0:
                        return tr("Numar de inmatriculare");
                    case 1:
                        return tr("Producator");
                    case 2:
                        return tr("Model");
                    case 3:
                        return tr("Tip");
                    default:
                        return QString("");
                }
            }
        }
        return QVariant();
    }

};