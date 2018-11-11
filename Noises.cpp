//
//  Noises.cpp
//  optomechanics
//
//  Created by Erika Aranas on 08/08/2017.
//  Copyright © 2017 UCLUCL. All rights reserved.
//

#include "Noises.h"

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstdlib>
#include <random>
#include "Utils.h"

using namespace std;


random_device rd;
default_random_engine generator( rd() );

double Noises::compute_noise(double bath_no, double random_variable, const Noise_Type type)
{
    // unit interval random number generator
    uniform_real_distribution<double> distribution(0., 1.0);
    double r1 = distribution(generator);
    double r2 = distribution(generator);
    //cout << r1 << "/n" << r2 << endl;
    
    // compute r1 and r2 for random number generator from gaussian distribution: Box-Mulller algorithm
    double s = sqrt(2. * log(1./r1));
    double theta = pi2 * r2;
    
    double n = 0;
    if ( type == Noise_Type::REAL)
    {
        n = s * cos(theta);
    }
    else
    {
        n = s * sin(theta);
    }
   
       
    // update formula
    double sigma = sqrt(bath_no * step_size) * subintervals_propagate;
    return sigma * n;
    
}