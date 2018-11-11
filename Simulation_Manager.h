//
//  Simulation_Manager.h
//  optomechanics
//
//  Created by Erika Aranas on 15/08/2017.
//  Copyright © 2017 UCLUCL. All rights reserved.
//

#ifndef Simulation_Manager_h
#define Simulation_Manager_h

#include <stdio.h>
#include <vector>
#include <complex>

using namespace std;

class Simulation_Manager
{
public:
    enum class Vector_Type : unsigned int
    {
        test,
        aRe,
        aIm,
        bRe,
        bIm,
        aRe_out,
        aIm_out,
    };
    
    //Constructor & Destructor
    Simulation_Manager();
    ~Simulation_Manager();
    
    //Types
    typedef vector<complex<double>> output_vector;
    typedef vector<output_vector> output_matrix;
    output_vector& get_working_vector(const Vector_Type vType);
    
    //Methods
    void simulate(const Vector_Type vType);
    void print_to_file();
    
private:

    //Member Variables
    output_vector test_vector;
    output_vector aRe_vector;
    output_vector aIm_vector;
    output_vector bRe_vector;
    output_vector bIm_vector;
    output_vector aRe_out_vector;
    output_vector aIm_out_vector;
    output_vector working_vector_fft;
    output_matrix fft_vector;

};

#endif /* Simulation_Manager_h */
