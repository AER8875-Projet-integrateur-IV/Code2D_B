/*#include "RoeScheme.h"

// Constructor
RoeScheme::RoeScheme(int elem1, int elem2, int faceI, int currElem, Metrics &metrics, Results &SimResults){
  //: elem1(elem1In), elem2(elem2In), faceI(faceIIn), currElem(currElemIn), metrics(metricsIn), SimResults(SimResultsIn)
}

RoeScheme::~RoeScheme(){}

 void RoeScheme::RoeAvgs(){

   // Calculate rho
   double rhoL = SimResults.rho[elem1];
   double rhoR = SimResults.rho[elem2];
   rhoTilde = std::sqrt(rhoL-rhoR);

   // Calculate u
   double uL = SimResults.u[elem1];
   double uR = SimResults.u[elem2];
   uTilde = (uL*std::sqrt(rhoL)+uR*std::sqrt(rhoR))/(std::sqrt(rhoL)+std::sqrt(rhoR));

   // Calculate v
   double vL = SimResults.v[elem1];
   double vR = SimResults.v[elem2];
   vTilde = (vL*std::sqrt(rhoL)+vR*std::sqrt(rhoR))/(std::sqrt(rhoL)+std::sqrt(rhoR));

   // Calculate H
   double HL = SimResults.H[elem1];
   double HR = SimResults.H[elem2];
   HTilde = (HL*std::sqrt(rhoL)+HR*std::sqrt(rhoR))/(std::sqrt(rhoL)+std::sqrt(rhoR));

   // Calculate V
   double nx = metrics[currElem][faceI][0];
   double ny = metrics[currElem][faceI][1];
   VTilde = uTilde*nx+vTilde*ny;

   // Calculate q sqaured
   qTildeSq = uTilde*uTilde+vTilde*vTilde;

   // Calculate c
   double gamma = SimResults.gamma;
   cTilde = std::sqrt((gamma-1)*(HTilde-qTildeSq/2));

 }

 // Function to calculate F_L and F_R
 std::vector<double> RoeScheme::CalcSideFluxes(int &iElem){
   std::vector<double> SideFlux;
   SideFlux.resize(4);
   SideFlux[0] = SimResults.rho[iElem]*SimResults.V[iElem];
   SideFlux[1] = SimResults.rho[iElem]*SimResults.u[iElem]*SimResults.V[iElem]+metrics[iElem][faceI].x*SimResults.p[iElem];
   SideFlux[2] = SimResults.rho[iElem]*SimResults.v[iElem]*SimResults.V[iElem]+metrics[iElem][faceI].y*SimResults.p[iElem];
   SideFlux[3] = SimResults.rho[iElem]*SimResults.H[iElem]*SimResults.V[iElem];
   return SideFlux;
 }

 std::vector<double> RoeScheme::CalcARoe(){
   double nx = metrics[currElem][faceI][0];
   double ny = metrics[currElem][faceI][1];

   std::vector<double> ARoe;
   ARoe.resize(4);

   std::vector<double> deltaF1;
   deltaF1.resize(4);

   double deltaP = SimResults.p[elem2]-SimResults.p[elem1];
   double deltaV = SimResults.V[elem2]-SimResults.V[elem1];
   double deltarho = SimResults.rho[elem2]-SimResults.rho[elem1];
   double deltau = SimResults.u[elem2]-SimResults.u[elem1];
   double deltav = SimResults.v[elem2]-SimResults.v[elem1];

   // Calculate delta F1
   double deltaMult1 = std::abs(VTilde-cTilde)*(deltaP-rhoTilde*cTilde*deltaV)/(2*cTilde*cTilde);
   std::vector<double> deltaF1{deltaMult1*1,
                              deltaMult1*(uTilde-cTilde*nx),
                              deltaMult1*(vTilde-cTilde*ny),
                              deltaMult1*(HTilde-cTilde*VTilde)};

   // Calculate delta F234
   double deltaMult234 = deltarho-deltaP/(cTilde*cTilde);
   std::vector<double> deltaF234{std::abs(VTilde)*deltaMult234*1+rhoTilde*0,
                              std::abs(VTilde)*deltaMult234*uTilde+rhoTilde*(deltau-deltaV*nx),
                              std::abs(VTilde)*deltaMult234*vTilde+rhoTilde*(deltav-deltaV*ny),
                              std::abs(VTilde)*deltaMult234*qTildeSq/2+rhoTilde*(uTilde*deltau+vTilde*deltav-VTilde*deltaV)};

    double deltaMult5 = std::abs(VTilde+cTilde)*(deltaP+rhoTilde*cTilde*deltaV)/(2*cTilde);
    std::vector<double> deltaF5{deltaMult5*1,
                               deltaMult5*(uTilde+cTilde*nx),
                               deltaMult5*(vTilde+cTilde*ny),
                               deltaMult5*(HTilde+cTilde*VTilde)};

   for (int i = 0; i< ARoe.length(); i++){
     ARoe[i] = deltaF1[i]+deltaF234[i]+deltaF5[i];
   }
   return ARoe;
 }

 void RoeScheme::CalcFluxes(){
   Fluxes.resize(4);
   std::vector<double> FluxL = CalcSideFluxes(elem1);
   std::vector<double> FluxR = CalcSideFluxes(elem2);
   for (int i = 0; i<Fluxes.length(); i++){
     Fluxes[i] = 0.5*(FluxR[i]+FluxL[i]-ARoe[i]);
   }
 }*/


 // HARTEN'S CONDITION STILL MISSING
