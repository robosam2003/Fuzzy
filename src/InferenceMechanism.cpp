//
// Created by robos on 10/01/2024.
//

#include "InferenceMechanism.h"
#include <iostream>

namespace Fuzzy {
    InferenceMechanism::InferenceMechanism(Rule *rules, int num_inputs, int num_rules) {
        this->rules = rules;
        this->num_inputs = num_inputs; // up to 2
        this->num_rules = num_rules;
        std::cout << "num_rules: " << num_rules << std::endl;
    }

    float InferenceMechanism::infer(float *inputs) {
        // Determine which rules are on
        int num_rules_on = 0;
        Rule *rules_on = new Rule[num_rules];
        std::cout << "num_rules: " << num_rules << std::endl;
        for (int i = 0; i < num_rules; i++) {
            // Check if the rule is on
            bool rule_on = false;
            bool other_rule_on = false;
            for (int j = 0; j < num_inputs; j++) {
                // Check if the antecedent is on
                float mu = rules[i].antecedents[j]->mu(inputs[j]);
                if ((mu != 0) and not other_rule_on) {
                    other_rule_on = true;
                    continue;
                }
                if (mu != 0 and other_rule_on) {
                    rule_on = true;
                    rules_on[num_rules_on] = rules[i];
                    num_rules_on++;
                }
//                std::cout << "Rule:" << i+1 << ": mu= " << mu << std::endl;
            }
        }
        std::cout << "num_rules_on: " << num_rules_on << std::endl;

        // Determine the output of each rule
        float mu_premises[num_rules_on];
        for (int i = 0; i < num_rules_on; i++) {
            // use product for and
            float mu = 1;
            for (int j = 0; j < num_inputs; j++) {
                mu *= rules_on[i].antecedents[j]->mu(inputs[j]);
            }
            mu_premises[i] = mu;
        }
        for (int i = 0; i < num_rules_on; i++) {
            std::cout << mu_premises[i] << ", ";
        }
        std::cout << std::endl;

        // Determine the output of the system by defuzzifying the output of each rule using COG defuzzification
        // assume the membership functions are all TriMFs for now
        // The defuzzification method is the Center of Gravity (COG) method

        // Determine the range of the output
        float min_output = 0;
        float max_output = 0;
        for (int i = 0; i < num_rules_on; i++) {
            if (rules_on[i].consequent->a < min_output) {
                min_output = rules_on[i].consequent->a;
            }
            if (rules_on[i].consequent->c > max_output) {
                max_output = rules_on[i].consequent->c;
            }
        }
        std::cout << "min_output: " << min_output << std::endl;
        std::cout << "max_output: " << max_output << std::endl;

        // Determine the step size
        float step_size = 0.001;
        int num_steps = int((max_output - min_output) / step_size);
        std::cout << "num_steps: " << num_steps << std::endl;

        float sum_mu = 0;
        float sum_mu_x = 0;
        for (int i = 0; i < num_steps; i++) {
            // The output is a fuzz set with several MFs making it up - the overall MF is the union of all the MFs (use max)
            float max_mu = 0;
            for (int j = 0; j < num_rules_on; j++) {
                float mu = std::min(mu_premises[j], rules_on[j].consequent->mu(min_output + i * step_size)); // use product for and
                if (mu > max_mu) {
                    max_mu = mu;
                }
            }
            sum_mu += max_mu;
            sum_mu_x += max_mu * (min_output + i * step_size);
        }
        std::cout << "sum_mu: " << sum_mu << std::endl;
        std::cout << "sum_mu_x: " << sum_mu_x << std::endl;
        float output = sum_mu_x / sum_mu;
        std::cout << "output: " << output << std::endl;
        return output;
    }
} // Fuzzy