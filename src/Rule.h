//
// Created by robos on 10/01/2024.
//

#ifndef FUZZY_RULE_H
#define FUZZY_RULE_H

#include <initializer_list>
#include "MembershipFunction.h"

namespace Fuzzy {

    class LinguisticVariable {
    public:
        const char *name;
        double value;
    };


    class Rule {
    public:
        Rule();

// array of antecedents - max 2
        LinguisticVariable var;
        MembershipFunction* antecedents[10];  // Has to be pointer because MembershipFunction is abstract
        MembershipFunction* consequent;

        Rule(LinguisticVariable var, MembershipFunction* antecedents[2], MembershipFunction* consequent);

        // constructor with initializer list
        Rule(LinguisticVariable var, std::initializer_list<MembershipFunction*> antecedents, MembershipFunction* consequent);

        // copy constructor
        Rule(const Rule &other);
    };

} // Fuzzy

#endif //FUZZY_RULE_H
