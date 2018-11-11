//
//  FFT.h
//  optomechanics
//
//  Created by Erika Aranas on 22/08/2017.
//  Copyright © 2017 UCLUCL. All rights reserved.
//

#ifndef FFT_h
#define FFT_h

#include <stdio.h>
#include <vector>
#include <complex>
#include "kiss_fft.h"
#include "Utils.h"

using namespace std;

class FFT
{
public:
    //Constructor & Destructor
    FFT(const int nfft);
    ~FFT();
    typedef vector<complex<double>> complex_vector;
    
    //Methods
    void fourier_transform(const complex_vector &input_signal, complex_vector &output_spectrum);
    
private:
    //Member Variables
    double t = 0;
    double w = 0;
    
    kiss_fft_cfg fwd;
};


#endif /* FFT_h */
