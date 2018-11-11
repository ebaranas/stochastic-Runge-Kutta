//
//  main.cpp
//  optomechanics
//
//  Created by Erika Aranas on 04/08/2017.
//  Copyright © 2017 UCLUCL. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include "Utils.h"
#include "Simulation_Manager.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    Simulation_Manager* sm = new Simulation_Manager();
    
    // begin clock
    clock_t t1,t2;
    t1 = clock();
    
    //run simulation
    sm->simulate(Simulation_Manager::Vector_Type::aRe_out);
    sm->print_to_file();
    
    // compute equilibrium values
    Utils::print_equilibrium_values();
    
    // compute runtime
    t2=clock();
    float diff ((float)t2-(float)t1);
    cout << "runtime: " << diff/CLOCKS_PER_SEC << endl;
    
    return 0;
}