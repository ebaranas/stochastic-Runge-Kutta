//
//  Utils.h
//  optomechanics
//
//  Created by Erika Aranas on 14/08/2017.
//  Copyright © 2017 UCLUCL. All rights reserved.
//

#ifndef UTILS_H
#define UTILS_H

#include <cmath>

// physical constants
const double root2 = sqrt(2.);
const double pi = 3.14159265359;
const double pi2 = 2. * pi;
const double root2pi = sqrt(pi2);
const double boltzmann = 1.38064852 * pow(10, -23);
const double hbar = 1.054571800 * pow(10, -34);

// experiment parameters: standard
const double mass = 7.3655686961 * pow(10, -17);
const double om0 = 2000. * pi2;
const double det = -om0;
const double kap = om0;
const double root_kap = sqrt(kap);
const double gam = 0.23; // .23 gam = 10^-4 mbar;
const double root_gam = sqrt(gam);
const double g0 = om0 / 5.;
const double phonon_bath_temperature = 300.0;
const double photon_bath_no = 1;
const double phonon_bath_no = (phonon_bath_temperature * boltzmann)/ (hbar * om0);

// experiment parameters: modulated
const double omD = 0*150. * pi2;
const double om2 = 0. * sqrt(2.) * omD;
const double g1 = 0.;

// simulation parameters
const int sample_size = 400000;
const double oscillation_period = pi2 / (2. * om0);
const double subintervals_plot = 100;
const double subintervals_propagate = 1000;
const double step_size = oscillation_period / subintervals_propagate / subintervals_plot;
//const double plot_time = oscillation_period / subintervals_plot;
const int realisations = 10;

// FFT parameters
const int nfft = sample_size;
const double t_step = step_size * subintervals_propagate; // = plot_time
const double w_step = 1.0 / (nfft * t_step);
const double nfft_inv = 1./nfft;
//const double normalisation = realisations / nfft_inv / nfft_inv * 2;
const double total_time = sample_size * t_step;
const double normalisation = realisations / nfft_inv / nfft_inv / total_time * 2;


//const double root_t_step = sqrt(t_step);
const double root_step_size = sqrt(step_size);

/*
struct Simulation_Parameters
{
    int sample_size;
    double oscillation_period;
    double subintervals_plot;
    double subintervals_propagate;
    double step_size;
    double plot_time;
    int realisations;
    int nfft;
    double t_step;
    double w_step;
    int normalisation;
};
*/
class Utils
{
public:
    //static Simulation_Parameters get_default_configuration();
    static void print_equilibrium_values();
    
    static double omM(double time);
    static double g(double time);
    static double get_phonon_number();
    static double get_cooling_rate();
};

#endif