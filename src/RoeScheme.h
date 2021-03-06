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
    RoeScheme(int faceIIn, Metrics &, Results &, Mesh &);
    ~RoeScheme();

    // Vectors/Arrays
    std::vector<double> Fluxes;
    std::vector<double> ARoe;

    // Variables
    int elem1;
    int elem2;
    int faceI;
    int currElem;
    Metrics &metrics;
    Results &SimResults;
    Mesh &mesh;
    int faceIIn;

    // Functions
    void RoeAvgs();
    void CalcFluxes();
    std::vector<double> CalcSideFluxes(int &iElem);
    void CalcARoe();
    void ComputeFluxes();

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


};
