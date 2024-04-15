#include "DTO.h"

#include <utility>

int DTO::get_count() const {
    return this->count;
}

void DTO::inc_count() {
    this->count++;
}