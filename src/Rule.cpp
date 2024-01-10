//
// Created by robos on 10/01/2024.
//

#include "Rule.h"

namespace Fuzzy {


    Rule::Rule(LinguisticVariable var, MembershipFunction *antecedents[2], MembershipFunction *consequent) {
        this->var = var;
        this->antecedents[0] = antecedents[0];
        this->antecedents[1] = antecedents[1];
        this->consequent = consequent;
    }



    Rule::Rule(const Rule &other) {
        this->var = other.var;
        this->antecedents[0] = other.antecedents[0];
        this->antecedents[1] = other.antecedents[1];
        this->consequent = other.consequent;
    }

    Rule::Rule(LinguisticVariable var, std::initializer_list<MembershipFunction *> antecedents,
               MembershipFunction *consequent) {
        this->var = var;
        this->antecedents[0] = *antecedents.begin();
        this->antecedents[1] = *(antecedents.begin() + 1);
        this->consequent = consequent;
    }

    Rule::Rule() { // default constructor
        this->var = LinguisticVariable();
        this->antecedents[0] = nullptr;
        this->antecedents[1] = nullptr;
        this->consequent = nullptr;

    }


}