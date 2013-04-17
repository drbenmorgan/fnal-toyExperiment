//
// A mockup of a very minimal Particle Data Table class.
//
// HEPPDT uses the wrong set of units for use in the art workbook'
// there is no way to simultaneously get the correct mass and
// time units.  So the art workbook uses this class.
//

#include "toyExperiment/Conditions/PDT.h"

#include "cetlib/exception.h"

#include <iostream>

tex::PDT::PDT():_pdt(){

  // Normally this would be loaded from a data base; but this is a toy example.
  double mpi (  139.57018);
  double mka (  493.677  );
  double mphi( 1019.455  );

  _pdt[PDGCode::pi_plus]  = ParticleInfo(PDGCode::pi_plus,  mpi,  1., "pi+");
  _pdt[PDGCode::pi_minus] = ParticleInfo(PDGCode::pi_minus, mpi, -1., "pi-");
  _pdt[PDGCode::K_plus]   = ParticleInfo(PDGCode::K_plus,   mka,  1., "K+");
  _pdt[PDGCode::K_minus]  = ParticleInfo(PDGCode::K_minus,  mka, -1., "K-");
  _pdt[PDGCode::phi]      = ParticleInfo(PDGCode::phi,      mphi, 0., "phi");

}

void
tex::PDT::print( std::ostream& ) const{
  for ( map_type::const_iterator i=_pdt.begin();
        i  != _pdt.end(); ++i ){
    std::cout << i->second << std::endl;
  }
}

/*
double
tex::PDT::mass( PDGCode::type id ) const{
  return getById(id).mass();
}

std::string const&
tex::PDT::name( PDGCode::type id) const{
  return getById(id).name();
}
*/

tex::ParticleInfo const&
tex::PDT::getById( PDGCode::type id) const{
  map_type::const_iterator i = _pdt.find(id);
  if ( i == _pdt.end() ){
    throw cet::exception("PDT")
      << "Unrecognized pdg id code: " << id << "\n";
  }
  return i->second;
}
