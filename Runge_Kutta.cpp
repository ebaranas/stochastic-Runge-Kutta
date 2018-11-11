//
//  Runge-Kutta.cpp
//  optomechanics
//
//  Created by Erika Aranas on 14/08/2017.
//  Copyright © 2017 UCLUCL. All rights reserved.
//

#include "Utils.h"
#include "Runge_Kutta.h"


// dynamical equation
double Runge_Kutta::aRe_dynamics(double time, double aRe, double aIm, double bRe, double bIm){
    //return -det * aIm;
    return 1. * (-kap/2. * aRe - det * aIm);
}

double Runge_Kutta::aIm_dynamics(double time, double aRe, double aIm, double bRe, double bIm) {
    //return det * aRe + 2. * g(time) * bRe;
    return 1. * (det * aRe - kap/2. * aIm) + Utils::g(time) * bRe;
}

double Runge_Kutta::bRe_dynamics(double time, double aRe, double aIm, double bRe, double bIm){
    //return om0 * bIm;
    //return 0.5 * omM(time) * bIm;
    return 1. * (-gam/2. * bRe + Utils::omM(time) * bIm);
}

double Runge_Kutta::bIm_dynamics(double time, double aRe, double aIm, double bRe, double bIm) {
    //return -om0 * bRe + 2. * g(time) * aRe;
    //return 0.5 * -omM(time) * bRe + g(time) * aRe;
    return 1. * (-gam/2. * bIm - Utils::omM(time) * bRe) + Utils::g(time) * aRe;
}

// update formula
double Runge_Kutta::update(double time, double aRe, double aIm, double bRe, double bIm, t_function function)
{
    double K1 = function(time, aRe, aIm, bRe, bIm);
    
    double K2 = function(time + step_size/2., aRe + step_size/2. * K1, aIm + step_size/2. * K1,
                         bRe + step_size/2. * K1, bIm + step_size/2. * K1);
    
    double K3 = function(time + step_size/2., aRe + step_size/2. * K2, aIm + step_size/2. * K2,
                         bRe + step_size/2. * K2, bIm + step_size/2. * K2);
    
    double K4 = function(time + step_size/2., aRe + step_size * K3, aIm + step_size * K3,
                         bRe + step_size * K3, bIm + step_size * K3);
    
    return step_size/6. * (K1 + 2. * K2 + 2. * K3 + K4);
}

