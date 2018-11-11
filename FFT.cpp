//
//  FFT.cpp
//  optomechanics
//
//  Created by Erika Aranas on 22/08/2017.
//  Copyright © 2017 UCLUCL. All rights reserved.
//

#include "FFT.h"
#include <iostream>
#include <complex>
#include <vector>
#include <fstream>
using namespace std;

FFT::FFT(const int nfft)
{
    const int inverse_fft = 0;
    fwd = kiss_fft_alloc(nfft,inverse_fft, NULL, NULL);
}

FFT::~FFT()
{
    kiss_fft_free(fwd);
}

void FFT::fourier_transform(const FFT::complex_vector &input_signal, complex_vector &output_spectrum)
{
    kiss_fft(fwd, (kiss_fft_cpx*)&input_signal[0], (kiss_fft_cpx*)&output_spectrum[0]);
       /* output_spectrum[k] = output_spectrum[k] * conj(output_spectrum[k]);
        output_spectrum[k] = output_spectrum[k].real() * t_step * t_step;*/
}


