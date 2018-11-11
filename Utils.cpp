//
//  Utils.cpp
//  optomechanics
//
//  Created by Erika Aranas on 15/08/2017.
//  Copyright © 2017 UCLUCL. All rights reserved.
//

#include <iostream>
#include "Utils.h"

using namespace std;

/*
Simulation_Parameters Utils::get_default_configuration()
{
    Simulation_Parameters parameters;
    
    parameters.sample_size = 10000;
    parameters.oscillation_period = pi2 / (2. * om0);
    parameters.subintervals_plot = 3;
    parameters.subintervals_propagate = 1000;
    parameters.step_size = parameters.oscillation_period / parameters.subintervals_propagate / parameters.subintervals_plot;
    parameters.plot_time = parameters.oscillation_period / parameters.subintervals_plot;
    parameters.realisations = 20.;
    
    
    parameters.nfft = parameters.sample_size;
    parameters.t_step = parameters.step_size * parameters.subintervals_propagate;
    parameters.w_step = 1.0 / (parameters.nfft * parameters.t_step);
    
    parameters.normalisation = parameters.realisations * parameters.realisations;
    return parameters;
}
*/

void Utils::print_equilibrium_values() {
    // compute zero point motion
    const double xZPF = sqrt(hbar / 2. / mass / om0);
    
    // print cooling rate and phonon number
    cout << "cooling rate: " << get_cooling_rate() << "\n";
    cout << "bath phonon number: " << phonon_bath_no << "\n";
    cout << "phonon number: " << get_phonon_number() << "\n";
    cout << "xZPF: " << xZPF << "\n";
    cout << "noise scaling term" << boltzmann * phonon_bath_temperature / mass << "\n";
    cout << "oscillation period " << oscillation_period << "\n";
    cout << "step size " << step_size << "\n";
    cout << "total time " << total_time << "\n";
    cout << "t step " << t_step << "\n";
    cout << "w step " << w_step << "\n";
    cout << "gamma " << gam << "\n";
    cout << "SD compare with xmgrace " << sqrt(gam * step_size * phonon_bath_no) * 2. * get_cooling_rate()
    << "\n";
}

double Utils::get_phonon_number()
{
    // compute phonon number
    return phonon_bath_no * gam / (gam + get_cooling_rate());
}

double Utils::get_cooling_rate()
{
    // compute cooling rate
    double cooling_rate = pow(pow(kap, 2) / 4. + pow(det + om0, 2), -1);
    cooling_rate += -pow(pow(kap, 2) / 4. + pow(det - om0, 2), -1);
    cooling_rate = cooling_rate * kap * pow(g0, 2);
    
    return cooling_rate;
}

double Utils::omM(double time){
    return om0 + 2. * om2 * cos(2. * omD * time);
}

double Utils::g(double time){
    return g0 + 2. * g1 * sin(omD * time);
}