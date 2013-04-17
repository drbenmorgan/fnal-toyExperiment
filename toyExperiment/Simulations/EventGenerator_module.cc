//
//  Generate a very simple event; add it to the event as a data product of type GenParticleCollection.
//

#include "toyExperiment/Conditions/Conditions.h"
#include "toyExperiment/MCDataProducts/GenParticleCollection.h"
#include "toyExperiment/Utilities/Decay2Body.h"
#include "toyExperiment/Utilities/RandomUnitSphere.h"

#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"

#include "CLHEP/Random/RandFlat.h"

#include <iostream>
#include <cmath>
#include <memory>

namespace tex {

  class EventGenerator : public art::EDProducer {

  public:

    explicit EventGenerator( fhicl::ParameterSet const& pset );
    void produce( art::Event& event );

  private:

    // Particle data table.
    PDT const& _pdt;

    // Configuration information.
    int    _seed;
    double _pmin;
    double _pmax;

    // Particle masses.
    double _mpi;
    double _mka;
    double _mphi;

    // Random number engines and distributions.
    art::RandomNumberGenerator::base_engine_t & _engine;
    CLHEP::RandFlat                             _flat;
    RandomUnitSphere                            _unitSphere;

  };

}

tex::EventGenerator::EventGenerator( fhicl::ParameterSet const& pset ):
  _pdt(( art::ServiceHandle<Conditions>()->pdt())),

  _seed( pset.get<int>("seed")),
  _pmin( pset.get<double>("pmin",500.)),
  _pmax( pset.get<double>("pmax",1500.)),

  _mpi(  _pdt.getById( PDGCode::pi_plus).mass() ),
  _mka(  _pdt.getById( PDGCode::K_plus).mass() ),
  _mphi( _pdt.getById( PDGCode::phi).mass() ),

  _engine(      createEngine(_seed)),
  _flat(       _engine),
  _unitSphere( _engine)
{
  produces<GenParticleCollection>();
}

void tex::EventGenerator::produce( art::Event& event ){

  // Create an empty output data product
  std::unique_ptr<GenParticleCollection> gens(new GenParticleCollection());
  gens->reserve(3);

  // Product Id of the data product to be created; needed for persistent pointers.
  art::ProductID gensID(getProductID<GenParticleCollection>(event));

  // All particles will be produced at the origin.
  static CLHEP::Hep3Vector origin(0.,0.,0);

  // Generate the 4 momentum of a phi, ignoring its natural width.
  double p              = _flat.fire( _pmin, _pmax);
  CLHEP::Hep3Vector mom = _unitSphere.fire(p);
  double e              = std::sqrt ( _mphi*_mphi + p*p );
  CLHEP::HepLorentzVector lmom( mom, e);

  // The particles will be added to the collection in given order; these are indicies into the collection
  int idxPhi(0);
  int idxKplus(1);
  int idxKminus(2);

  // Put the phi into the output collection; it is a primary particle that has no parent.
  gens->push_back ( GenParticle( PDGCode::phi, art::Ptr<GenParticle>(), origin, lmom, GenParticle::decayed));

  // Particles 1 and 2, have a parent, it is particle 0;
  art::Ptr<GenParticle> parent( gensID, idxPhi, event.productGetter(gensID));

  // Decay the phi and add its decay products to the output collection.
  Decay2Body decay( lmom, _mka, _mka, _unitSphere );
  gens->push_back ( GenParticle( PDGCode::K_plus,  parent, origin, decay.p1(), GenParticle::alive));
  gens->push_back ( GenParticle( PDGCode::K_minus, parent, origin, decay.p2(), GenParticle::alive));

  // Tell particle 0 about its children.
  gens->at(0).addChild( art::Ptr<GenParticle>( gensID, idxKplus,  event.productGetter(gensID)) );
  gens->at(0).addChild( art::Ptr<GenParticle>( gensID, idxKminus, event.productGetter(gensID)) );

  // Put the output collection into the event.
  event.put(std::move(gens));
}

DEFINE_ART_MODULE(tex::EventGenerator)
