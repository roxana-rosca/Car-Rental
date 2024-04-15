#include "VectorDinamicTemplate.h"


void testVectorDinamic(){
    VectorDinamic<int> v;
    v.add(1);
    v.add(2);
    v.add(3);

    int i=1;
    for(auto x:v){
        assert(i==x);
        i++;
    }

    i=1;
    IteratorVector<int>it{v};
    while(it != v.end()){
        assert((*it) == i);
        i++;
        ++it;
    }

    i=1;
    IteratorVector<int> it2{v};
    while(it2.valid())
    {
        assert(it2.element() == i);
        i++;
        it2.next();
    }

    v.erase(0);
    assert(v.size() == 2);
}

void testAssignmentOperator() {
    VectorDinamic<int> v1;
    VectorDinamic<int> v2;

    v1.add(1);
    v1.add(2);

    v2 = v2;
    v2 = v1;
    assert(v2.size() == 2);

    v1.add(3);
    v1.add(4);
    v1.add(5);
    v1.add(6);
    v1.add(7);
    assert(v1.size() == 7);
}
