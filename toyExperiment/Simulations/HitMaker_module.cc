//
// Starting from the MC truth information, produce data-like hits.
// Produce an art Assns to connect the data-like hits and their MCTruth.
//

#include "toyExperiment/Conditions/Conditions.h"
#include "toyExperiment/Geometry/Geometry.h"
#include "toyExperiment/MCDataProducts/IntersectionCollection.h"
#include "toyExperiment/MCDataProducts/TrkHitMatch.h"
#include "toyExperiment/RecoDataProducts/TrkHitCollection.h"

#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"

#include "CLHEP/Random/RandGaussQ.h"
#include "CLHEP/Random/RandFlat.h"

#include <iostream>
#include <cmath>

namespace tex {

  class HitMaker : public art::EDProducer {

  public:

    explicit HitMaker( fhicl::ParameterSet const& pset );

    void produce  ( art::Event& event );

  private:

    // Label of the module that made the Intersection objects.
    std::string _simsModuleLabel;

    // Seed for the random number engine
    int _seed;

    // Which instance names of the input product should we do?
    std::vector<std::string> _instanceNames;

    // Handle to the geometry and conditions services; handles are defined at
    // c'tor-time but the contents of the underlying objects may change on
    // run and subrun boundaries.
    art::ServiceHandle<Geometry>   _geom;
    art::ServiceHandle<Conditions> _conditions;

    // The random number engine that will be used by this data product.
    art::RandomNumberGenerator::base_engine_t & _engine;

    // Random number distributions.
    CLHEP::RandFlat   _flat;
    CLHEP::RandGaussQ _gauss;

  };

}

tex::HitMaker::HitMaker( fhicl::ParameterSet const& pset ):
  _simsModuleLabel(pset.get<std::string>("inputModuleLabel")),
  _seed(pset.get<int>("seed")),
  _instanceNames(pset.get<std::vector<std::string>>("instanceNames")),
  _geom(art::ServiceHandle<Geometry>()),
  _engine(createEngine(_seed)),
  _flat(_engine),
  _gauss(_engine){

  produces<TrkHitCollection>();
  produces<TrkHitMatch>();
}

void tex::HitMaker::produce( art::Event& event ){

  // Fetch input data products and count the total size.
  int nHitMax(0);
  std::vector<art::Handle<IntersectionCollection>> handles;
  handles.reserve(_instanceNames.size());
  for ( auto const& instance : _instanceNames ) {
    art::Handle<IntersectionCollection> handle;
    event.getByLabel(_simsModuleLabel, instance, handle);
    handles.emplace_back( handle );
    nHitMax += handle->size();
  }

  // Create empty output data products; reserve maximum possible size.
  std::unique_ptr<TrkHitCollection> hits(new TrkHitCollection );
  std::unique_ptr<TrkHitMatch> matches(new TrkHitMatch());
  hits->reserve(nHitMax);

  // Product ID of the Assns product to be created.
  art::ProductID trkHitID(getProductID<TrkHitCollection>(event));

  // Access geometry information.
  Tracker const& tracker( _geom->tracker() ) ;

  for ( auto const& handle : handles ){

    for ( auto const& truth: *handle ){

      CLHEP::Hep3Vector const& pos = truth.position();
      Shell const& shell           =  tracker.shell( truth.shell() );
      ShellConditions const& cond  = _conditions->shellConditions( truth.shell() );

      // Apply efficiency.
      if ( _flat.fire() > cond.efficiency() ) continue;

      // Apply resolution smearing
      double z   = pos.z()   + _gauss.fire()*cond.sigmaZ();
      double phi = pos.phi() + _gauss.fire()*cond.sigmaPhi();
      hits->emplace_back( shell.id(), z, phi, cond.sigmaZ(), cond.sigmaPhi() );

      // Record connection betwween the hit and its truth information.
      art::Ptr<Intersection> ptruth( handle, &truth-&handle->front() );
      art::Ptr<TrkHit>      phit  ( trkHitID, hits->size()-1, event.productGetter(trkHitID) );
      matches->addSingle( phit, ptruth );

    }
  }

  // Add output data products to the event.
  event.put( std::move(hits) );
  event.put( std::move(matches) );

}

DEFINE_ART_MODULE(tex::HitMaker)
