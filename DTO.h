#pragma once
#include <iostream>
#include <utility>
#include <cstring>

using namespace std;

class DTO {
private:
    string model;
    int count{};

public:

    DTO()=default;

    // Constructor
    explicit DTO(string m)
    {
        model=std::move(m);
        count=1;
    }

    [[nodiscard]] int get_count() const;

    void inc_count();
};
