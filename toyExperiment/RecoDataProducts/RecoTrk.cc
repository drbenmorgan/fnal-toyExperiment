//
// A crude reconstructed track class in cartesian representation.
//

#include "toyExperiment/RecoDataProducts/RecoTrk.h"
#include "CLHEP/Matrix/Vector.h"

tex::RecoTrk::RecoTrk():
  _momentum(),
  _momCov(dimension){
}

tex::RecoTrk::RecoTrk( CLHEP::HepLorentzVector const& momentum,
                         CLHEP::HepSymMatrix     const& momCov ):
  _momentum(momentum),
  _momCov(momCov){
}

tex::RecoTrk const& tex::RecoTrk::operator+=( RecoTrk const& rhs){
  _momentum += rhs._momentum;
  _momCov   += rhs._momCov;
  return *this;
}

double tex::RecoTrk::sigmaMass() const{

  double m = _momentum.mag();

  // Derivatives of the mass wrt the 4-vector components.
  double dm[dimension];
  dm[ipx] = - _momentum.x()/m;
  dm[ipy] = - _momentum.y()/m;
  dm[ipz] = - _momentum.z()/m;
  dm[ie ] =   _momentum.e()/m;

  // Alias for typographic convenience.
  CLHEP::HepSymMatrix const& v(_momCov);

  // Error squared on the mass.
  double vm = dm[ipx]*dm[ipx]*v[ipx][ipx] +
              dm[ipy]*dm[ipy]*v[ipy][ipy] +
              dm[ipz]*dm[ipz]*v[ipz][ipz] +
              dm[ie ]*dm[ie ]*v[ie ][ie ] +
    2.* (  dm[ipx]*dm[ipy]*v[ipx][ipy] +
              dm[ipx]*dm[ipz]*v[ipx][ipz] +
              dm[ipx]*dm[ie ]*v[ipx][ie ] +
              dm[ipy]*dm[ipz]*v[ipy][ipz] +
              dm[ipy]*dm[ie ]*v[ipy][ie ] +
              dm[ipz]*dm[ie ]*v[ipz][ie ]
           );

  double sigma = ( vm > 0. ) ? sqrt(vm) : 0.;

  return sigma;
}

double tex::RecoTrk::sigmaP() const{

  double p = _momentum.vect().mag();

  // Derivatives of the mass wrt the 4-vector components.
  double d[3];
  d[ipx] = _momentum.x()/p;
  d[ipy] = _momentum.y()/p;
  d[ipz] = _momentum.z()/p;

  // Alias for typographic convenience.
  CLHEP::HepSymMatrix const& v(_momCov);

  // Error squared on the momentum.
  double vp = d[ipx]*d[ipx]*v[ipx][ipx] +
              d[ipy]*d[ipy]*v[ipy][ipy] +
              d[ipz]*d[ipz]*v[ipz][ipz] +
    2.* (  d[ipx]*d[ipy]*v[ipx][ipy] +
              d[ipx]*d[ipz]*v[ipx][ipz] +
              d[ipy]*d[ipz]*v[ipy][ipz]
           );

  double sigma = ( vp > 0. ) ? sqrt(vp) : 0.;

  return sigma;
}

std::ostream& tex::operator<<(std::ostream& ost,
                                const RecoTrk& recoTrk ){
  ost << "( "
      << recoTrk.momentum()    << ", "
      << recoTrk.momentumCov() << " )";
  return ost;
}
