//
// A minimal particle information class for use with the minimal
// particle data table class.
//

#include "toyExperiment/Conditions/ParticleInfo.h"

tex::ParticleInfo::ParticleInfo():
  _id(PDGCode::invalid),
  _mass(0),
  _q(0),
  _name("invalid"){
}

tex::ParticleInfo::ParticleInfo( PDGCode::type id,
                                   double        mass,
				   double        q,
                                   std::string   name):
  _id(id),
  _mass(mass),
  _q(q),
  _name(name){
}
