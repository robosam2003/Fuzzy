//
// Created by robos on 10/01/2024.
//

#ifndef FUZZY_INFERENCEMECHANISM_H
#define FUZZY_INFERENCEMECHANISM_H

#include "Rule.h"

namespace Fuzzy {

    class InferenceMechanism {
        // This is the class that will be used to infer the output of the system and defuzzify it
    public:
        // array of rules
        Rule* rules;
        int num_inputs;
        int num_rules;

        explicit InferenceMechanism(Rule* rules, int num_inputs, int num_rules);

        float infer(float inputs[]);

        virtual ~InferenceMechanism() = default;



    };

} // Fuzzy

#endif //FUZZY_INFERENCEMECHANISM_H
