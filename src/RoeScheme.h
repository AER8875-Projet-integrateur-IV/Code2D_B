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
    RoeScheme(int elem1In, int elem2In, int faceIIn, int currElemIn, Metrics &, Results &);
    ~RoeScheme();

    // Vectors/Arrays
    std::vector<double> Fluxes;

    // Variables
    int elem1;
    int elem2;
    int faceI;
    int currElem;
    Metrics metrics;
    Results SimResults;

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

    Metrics &metricsIn;
    Results &SimResultsIn;

    // Vectors/Arrays

    // Functions


};