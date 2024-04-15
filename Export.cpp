#include "Export.h"
#include "Car.h"
#include <fstream>
#include <string>
#include <vector>

void exportToCVS(const std::string &fName, const std::vector<Car>& cars)
{
    std::ofstream out(fName, std::ios::trunc);
    if(!out.is_open())
    {
        throw RepositoryException("Unable to open file: "+fName+"!\n");
    }
    for(const auto &c:cars)
    {
        out<<c.get_nr_inmatriculare()<<","<<c.get_producator()<<","<<c.get_model()<<","<<c.get_tip()<<endl;
    }
    out.close();
}

void exportToHTML(const std::string& fName, const std::vector<Car>& cars)
{
    std::ofstream out(fName, std::ios::trunc);
    //std::ofstream out(fName);
    if(!out.is_open())
    {
        throw RepositoryException("Unable to open file: "+fName+"!\n");
    }

    out<<"<html><body>"<<endl;
    out<<R"(<table border="1" style="width:100% ">)"<<endl;
    //out<<"<table border=\"1\" style=\"width:100 % \">"<<endl;
    for(const auto&c:cars)
    {
        out<<"<tr>"<<endl;
        out<<"<td>"<<c.get_nr_inmatriculare()<<"</td>"<<endl;
        out<<"<td>"<<c.get_producator()<<"</td>"<<endl;
        out<<"<td>"<<c.get_model()<<"</td>"<<endl;
        out<<"<td>"<<c.get_tip()<<"</td>"<<endl;
        out<<"</tr>"<<endl;
    }
    out<<"</table>"<<endl;
    out<<"</body></html>"<<endl;
    out.close();

}