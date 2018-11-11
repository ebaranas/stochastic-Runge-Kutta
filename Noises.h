//
// Noises.h
//  optomechanics
//
//  Created by Erika Aranas on 08/08/2017.
//  Copyright © 2017 UCLUCL. All rights reserved.
//
#ifndef NOISES_H
#define NOISES_H
class Noises
{
public:
    enum class Noise_Type : unsigned int
    {
        REAL,
        IMAGINARY
    };
    
    static double compute_noise(double bath_no,
                                double random_variable, const Noise_Type type);
};

#endif