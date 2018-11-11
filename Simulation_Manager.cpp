//
//  Simulation_Manager.cpp
//  optomechanics
//
//  Created by Erika Aranas on 15/08/2017.
//  Copyright © 2017 UCLUCL. All rights reserved.
//

#include "Simulation_Manager.h"

#include <fstream>
#include <iostream>
#include "Noises.h"
#include "Runge_Kutta.h"
#include "Utils.h"
#include "FFT.h"

Simulation_Manager::Simulation_Manager()
{
    // We reserve the ammount of values we need to avoid resizing at runtime
    test_vector = vector<complex<double>>(sample_size);
    aRe_vector = vector<complex<double>>(sample_size);
    aIm_vector = vector<complex<double>>(sample_size);
    bRe_vector = vector<complex<double>>(sample_size);
    bIm_vector = vector<complex<double>>(sample_size);
    aRe_out_vector = vector<complex<double>>(sample_size);
    aIm_out_vector = vector<complex<double>>(sample_size);

    working_vector_fft = vector<complex<double>>(sample_size, 0);
    fft_vector.resize(realisations, vector<complex<double>>(sample_size));
}

Simulation_Manager::~Simulation_Manager()
{
}

void Simulation_Manager::simulate(const Vector_Type vType)
{
    output_vector& working_vector = get_working_vector(vType);
    
    FFT* fft = new FFT(nfft);
    
    double aRe;
    double aIm;
    double bRe;
    double bIm;
    double aRe_out;
    double aIm_out;
    double aRe_in;
    double aIm_in;
    double bRe_in;
    double bIm_in;
    double t;
    
    for ( int r = 0; r < realisations; r++ )
    {
        t = 0.;
        aRe = 0.0;
        aIm = 0.0;
        bRe = 0.0;
        bIm = 0.0;
        aRe_out = 0.0;
        aIm_out = 0.0;
        aRe_in = 0.0;
        aIm_in = 0.0;
        bRe_in = 0.0;
        bIm_in = 0.0;
        
        
        for ( int s = 0; s < sample_size; s++ )
        {
            /*
            for ( int p = 0; p < subintervals_propagate; p++)
            {
                // update dynamical variables
                aRe_in = Noises::compute_noise(photon_bath_no, aRe, Noises::Noise_Type::REAL);
                aIm_in = Noises::compute_noise(photon_bath_no, aRe, Noises::Noise_Type::IMAGINARY);
                bRe_in = Noises::compute_noise(phonon_bath_no, bRe, Noises::Noise_Type::REAL);
                bIm_in = Noises::compute_noise(phonon_bath_no, bIm, Noises::Noise_Type::IMAGINARY);
                
                aRe += Runge_Kutta::update(t, aRe, aIm, bRe, bIm, Runge_Kutta::aRe_dynamics) + root_kap * aRe_in;
                
                aIm += Runge_Kutta::update(t, aRe, aIm, bRe, bIm, Runge_Kutta::aIm_dynamics) + root_kap * aIm_in;
                
                bRe += Runge_Kutta::update(t, aRe, aIm, bRe, bIm, Runge_Kutta::bRe_dynamics) + root_gam * bRe_in;
                
                bIm += Runge_Kutta::update(t, aRe, aIm, bRe, bIm, Runge_Kutta::bIm_dynamics) + root_gam * bIm_in;
             
                aRe_out = aRe_in/root_step_size - root_kap * aRe;

                // increment time
                t = t + step_size;
            }
             // only record values after propagating through subintervals
            aRe_vector[s] = aRe;
            aIm_vector[s] = aIm;
            bRe_vector[s] = bRe;
            bIm_vector[s] = bIm;
            aRe_out_vector[s] = aRe_out;
            aIm_out_vector[s] = aIm_out;
            */
            
            
        
            // try bigger kicks
            for ( int p = 0; p < subintervals_propagate; p++)
            {
                // update dynamical variables
                aRe += Runge_Kutta::update(t, aRe, aIm, bRe, bIm, Runge_Kutta::aRe_dynamics);
                
                aIm += Runge_Kutta::update(t, aRe, aIm, bRe, bIm, Runge_Kutta::aIm_dynamics);
                bRe += Runge_Kutta::update(t, aRe, aIm, bRe, bIm, Runge_Kutta::bRe_dynamics);
                
                bIm += Runge_Kutta::update(t, aRe, aIm, bRe, bIm, Runge_Kutta::bIm_dynamics);
                
                // increment time
                t = t + step_size;
            }
             
            aRe_in = Noises::compute_noise(photon_bath_no, aRe, Noises::Noise_Type::REAL);
            aIm_in = Noises::compute_noise(photon_bath_no, aRe, Noises::Noise_Type::IMAGINARY);
            bRe_in = Noises::compute_noise(phonon_bath_no, bRe, Noises::Noise_Type::REAL);
            bIm_in = Noises::compute_noise(phonon_bath_no, bIm, Noises::Noise_Type::IMAGINARY);
            
            // update dynamical variables with noise
            aRe += root_kap * aRe_in;
            aIm += root_kap * aIm_in;
            bRe += root_gam * bRe_in;
            bIm += root_gam * bIm_in;
            
            //below when using npropagate = 1
            aRe_out_vector[s] = aRe_in/step_size - root_kap * aRe;
            
            // only record values after propagating through subintervals
            aRe_vector[s] = aRe;
            //aIm_vector[s] = aIm;
            //bRe_vector[s] = bRe;
            //bIm_vector[s] = bIm;
            
            // increment time
            t = t + step_size;
             
            //test_vector[s] = complex<double>(cos(om0 * t) * exp(gam/2 * t), 0.);
            
        }
        // padding
        /*
        for ( int s = sample_size; s < 2. * sample_size; s++ )
        {
            working_vector[s] = (0.,0.);
            t = t + step_size;
        }
        */

        fft->fourier_transform(working_vector, working_vector_fft);
        fft_vector[r] = working_vector_fft;
        
        //uncomment to see time traces
        //fft_vector[r] = aRe_out_vector;
        
    }
    
    delete fft;
}

void Simulation_Manager::print_to_file()
{
    // create output file
    ofstream myfile;
    myfile.open ("/Users/erikaaranas/testdata.dat");
    
    double w = -0.5/t_step;
    double t = -0.5 * t_step;
    complex<double> result = 0;
    double ans = 0;
    
    // rearrange fft
    for ( int s = 0.5 * sample_size; s < sample_size; s++ )
    {
        for ( int r = 0; r < realisations; r++ )
        {
            result = result + fft_vector[r][s];
        }
        
        result = result * conj(result);
        ans = result.real()/normalisation;
        //uncomment below to see time traces
        //ans = result.real();
        // print output
        cout << w << " " << ans << "\n";
        //myfile << t << " " << aRe_out_vector[s].real() << "\n";
        myfile << w << " " <<  ans << "\n";
        w = w + w_step;
        t = t + t_step;
        result = 0;

    }
    
    for ( int s = 0; s < 0.5 * sample_size; s++ )
    {
        for ( int r = 0; r < realisations; r++ )
        {
            result = result + fft_vector[r][s];
        }
        
        result = result * conj(result);
        ans = result.real()/normalisation;
        //uncomment below to see time traces
        //ans = result.real();
        // print output
        cout << w << " " << ans << "\n";
        //cout << t << " " << test_vector[s].real() << "\n";
        //cout << t << " " << aRe_vector[s].real() << "\n";
        myfile << w << " " <<  ans << "\n";
        w = w + w_step;
        //t = t + t_step;
        result = 0;
    }
    
    
    myfile.close();
    
}

Simulation_Manager::output_vector& Simulation_Manager::get_working_vector(const Vector_Type vType)
{
    switch (vType) {
        case Vector_Type::aRe:
            return aRe_vector;
        case Vector_Type::aIm:
            return aIm_vector;
        case Vector_Type::bRe:
            return bRe_vector;
        case Vector_Type::bIm:
            return bIm_vector;
        case Vector_Type::aRe_out:
            return aRe_out_vector;
        case Vector_Type::aIm_out:
            return aIm_out_vector;
        case Vector_Type::test:
            return test_vector;

    }
}

