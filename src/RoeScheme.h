// =============================================================================
//                                  ROE SCHEME
//
// The purpose of this class is to implement the different equation related to
// the Roe scheme.
//
// =============================================================================
#pragma once
#include "Results.h"
#include "Metrics.h"

class RoeScheme {
  public:
    // Constructor
    RoeScheme(int &, int &, int &, int &, Metrics &, Results &);

    // Vectors/Arrays
    std::vector<double> Fluxes;

    // Variables

    // Functions
    void RoeAvgs();
    void CalcFluxes();
    std::vector<double> CalcSideFluxes(int &iElem);
    std::vector<double> CalcARoe();

  private:
    // Variables
    double rhoTilde;
    double uTilde;
    double vTilde;
    double HTilde;
    double VTilde;
    double qTildeSq;
    double cTilde;

    // Vectors/Arrays

    // Functions


}
