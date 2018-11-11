//
//  Dynamics.h
//  optomechanics
//
//  Created by Erika Aranas on 14/08/2017.
//  Copyright © 2017 UCLUCL. All rights reserved.
//

class Runge_Kutta
{
public:
    typedef double (*t_function)(double, double, double, double, double);
    
    static double aRe_dynamics(double time, double aRe, double aIm, double bRe, double bIm);
    
    static double aIm_dynamics(double time, double aRe, double aIm, double bRe, double bIm);
    
    static double bRe_dynamics(double time, double aRe, double aIm, double bRe, double bIm);
    
    static double bIm_dynamics(double time, double aRe, double aIm, double bRe, double bIm);
    
    static double update(double time, double aRe, double aIm, double bRe, double bIm, t_function function);
    
};
