#include <iostream>

#include "NbtTag.h"
using namespace std;

int main(int argc, char* argv[]) {
    NumericalNbtTag<int> tag(INT, "Test Tag", 4);
    NumericalNbtTag<int> tag2(INT, "Test Tag", 5);
    EndNbtTag tag3(END);
    std::vector<NbtTag *> vec;
    vec.push_back(&tag);
    vec.push_back(&tag2);
    vec.push_back(&tag3);
    NestedNbtTag nested(COMPOUND, "Compound", vec);
    cout << nested.to_string();
}

