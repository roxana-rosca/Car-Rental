#include <iostream>
#include "UI.h"
#include "Car.h"
#include "Repository.h"
#include "Service.h"
#include "VectorDinamicTemplate.h"
#include <QtWidgets/QApplication>
#include "GUI.h"
#include "ListaDeLucruGUI.h"
#include "GUIModel.h"

using std::cout;
using std::endl;

void testAll()
{
    testeDomain();
    cout<<"Finished domain tests.\n";
    testeRepo();
    cout<<"Finished repo tests.\n";
    testeService();
    cout<<"Finished service tests.\n";
}


int main(int argc, char **argv) {

    QApplication app(argc,argv);

    FileRepository repoFile{R"(C:\Users\roxan\CLionProjects\oop\inchiriere_masini_QT\cmake-build-debug-coverage\cars.txt)"};
    Validator val;
    Service srv{repoFile,val};
    //GUI gui{srv};
    GUIModel gui{srv};

    // full page
    //gui.setWindowState(Qt::WindowMaximized);


    // pornire aplicatie
    gui.show();

    return app.exec();
}
