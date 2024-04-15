#pragma once
#include <string>
#include <vector>
#include "Car.h"
#include "Repository.h"

/*
 * Scrie in fisierul fName lista de masini.
 * Format: CVS (Comma Separated Values)
 * Arunca exceptie daca nu se poate crea fisierul
 */
void exportToCVS(const std::string &fName, const std::vector<Car>& cars);

/*
 * Scrie in fisierul fName lista de masini.
 * Format: HTML
 * Arunca exceptie daca nu se poate crea fisierul
 */
void exportToHTML(const std::string& fName, const std::vector<Car>& cars);
