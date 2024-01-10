#include <iostream>
#include "MembershipFunction.h"
#include "Rule.h"
#include "InferenceMechanism.h"
// Library to plot the MFs
#include <cmath>

int main() {
    // MFs for an inverted pendulum
    Fuzzy::TriMF err_neglarge("err_neglarge", -3*M_PI_4, -M_PI_2, -M_PI_4, 1);
    Fuzzy::TriMF err_negsmall("err_negsmall", -M_PI_2, -M_PI_4, 0, 1);
    Fuzzy::TriMF err_zero("err_zero", -M_PI_4, 0, M_PI_4, 1);
    Fuzzy::TriMF err_possmall("err_possmall", 0, M_PI_4, M_PI_2, 1);
    Fuzzy::TriMF err_poslarge("err_poslarge", M_PI_4, M_PI_2, 3*M_PI_4, 1);

    // MFs for the change in error
    Fuzzy::TriMF derr_neglarge("derr_neglarge", -M_PI_2, -M_PI_4, -M_PI/8, 1);
    Fuzzy::TriMF derr_negsmall("derr_negsmall", -M_PI_4, -M_PI/8, 0, 1);
    Fuzzy::TriMF derr_zero("derr_zero", -M_PI/8, 0, M_PI/8, 1);
    Fuzzy::TriMF derr_possmall("derr_possmall", 0, M_PI/8, M_PI/4, 1);
    Fuzzy::TriMF derr_poslarge("derr_poslarge", M_PI/8, M_PI/4, M_PI_2, 1);

    // MFs for output force
    Fuzzy::TriMF force_neglarge("force_neglarge", -30, -20, -10, 1);
    Fuzzy::TriMF force_negsmall("force_negsmall", -20, -10, 0, 1);
    Fuzzy::TriMF force_zero("force_zero", -10, 0, 10, 1);
    Fuzzy::TriMF force_possmall("force_possmall", 0, 10, 20, 1);
    Fuzzy::TriMF force_poslarge("force_poslarge", 10, 20, 30, 1);
    std::cout << "MFs created" << std::endl;

    // Rules
    Fuzzy::LinguisticVariable err = {"err", 0};
    Fuzzy::LinguisticVariable derr = {"derr", 0};
    Fuzzy::LinguisticVariable force = {"force", 0};
    std::cout << "Linguistic variables created" << std::endl;

    Fuzzy::Rule rule1(err, {&err_neglarge, &derr_neglarge}, &force_poslarge);
    Fuzzy::Rule rule2(err, {&err_neglarge, &derr_negsmall}, &force_poslarge);
    Fuzzy::Rule rule3(err, {&err_neglarge, &derr_zero}, &force_poslarge);
    Fuzzy::Rule rule4(err, {&err_neglarge, &derr_possmall}, &force_possmall);
    Fuzzy::Rule rule5(err, {&err_neglarge, &derr_poslarge}, &force_zero);
    Fuzzy::Rule rule6(err, {&err_negsmall, &derr_neglarge}, &force_poslarge);
    Fuzzy::Rule rule7(err, {&err_negsmall, &derr_negsmall}, &force_poslarge);
    Fuzzy::Rule rule8(err, {&err_negsmall, &derr_zero}, &force_possmall);
    Fuzzy::Rule rule9(err, {&err_negsmall, &derr_possmall}, &force_zero);
    Fuzzy::Rule rule10(err, {&err_negsmall, &derr_poslarge}, &force_negsmall);
    Fuzzy::Rule rule11(err, {&err_zero, &derr_neglarge}, &force_poslarge);
    Fuzzy::Rule rule12(err, {&err_zero, &derr_negsmall}, &force_possmall);
    Fuzzy::Rule rule13(err, {&err_zero, &derr_zero}, &force_zero);
    Fuzzy::Rule rule14(err, {&err_zero, &derr_possmall}, &force_negsmall);
    Fuzzy::Rule rule15(err, {&err_zero, &derr_poslarge}, &force_neglarge);
    Fuzzy::Rule rule16(err, {&err_possmall, &derr_neglarge}, &force_possmall);
    Fuzzy::Rule rule17(err, {&err_possmall, &derr_negsmall}, &force_zero);
    Fuzzy::Rule rule18(err, {&err_possmall, &derr_zero}, &force_negsmall);
    Fuzzy::Rule rule19(err, {&err_possmall, &derr_possmall}, &force_neglarge);
    Fuzzy::Rule rule20(err, {&err_possmall, &derr_poslarge}, &force_neglarge);
    Fuzzy::Rule rule21(err, {&err_poslarge, &derr_neglarge}, &force_zero);
    Fuzzy::Rule rule22(err, {&err_poslarge, &derr_negsmall}, &force_negsmall);
    Fuzzy::Rule rule23(err, {&err_poslarge, &derr_zero}, &force_neglarge);
    Fuzzy::Rule rule24(err, {&err_poslarge, &derr_possmall}, &force_neglarge);
    Fuzzy::Rule rule25(err, {&err_poslarge, &derr_poslarge}, &force_neglarge);


    std::cout << "Rules created" << std::endl;

    Fuzzy::Rule rules[25] = {rule1, rule2, rule3, rule4, rule5, rule6, rule7, rule8, rule9, rule10,
                             rule11, rule12, rule13, rule14, rule15, rule16, rule17, rule18, rule19, rule20,
                             rule21, rule22, rule23, rule24, rule25};
    std::cout << "Rules array created" << std::endl;

    Fuzzy::InferenceMechanism inferenceMechanism(rules, 2, 25);
    std::cout << "Inference mechanism created" << std::endl;

    // infer a value
    float inputs[2] = {0, M_PI/8 - M_PI/32};
    float output = inferenceMechanism.infer(inputs);

    std::cout << "Output: " << output << std::endl;



}
