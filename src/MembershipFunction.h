//
// Created by robos on 10/01/2024.
//

#ifndef FUZZY_MEMBERSHIPFUNCTION_H
#define FUZZY_MEMBERSHIPFUNCTION_H

namespace Fuzzy {

class MembershipFunction {
public:
    // Name as a string
    const char* name;
    float peak;
    float a, b, c;
    float middle;
    float width;

    [[maybe_unused]] virtual float mu(float x) = 0;

    virtual ~MembershipFunction() = default;
};

class TriMF : public MembershipFunction {
public:

    TriMF(const char* name, float a, float b, float c, float peak);
    TriMF(const char* name, float middle, float width, float peak);

    // copy constructor
    TriMF(const TriMF &other);

    // assignment operator
    TriMF &operator=(const TriMF &other);


    // to string method
    const char* toString();


    float mu(float x) override;
};



} // Fuzzy

#endif //FUZZY_MEMBERSHIPFUNCTION_H
