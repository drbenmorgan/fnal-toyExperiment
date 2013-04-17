//
// Inspect the MC truth about the intersections between tracks and detector shells.
//

#include "toyExperiment/MCDataProducts/IntersectionCollection.h"

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Services/Optional/TFileService.h"

#include "TH1F.h"
#include "TNtuple.h"

#include "CLHEP/Units/SystemOfUnits.h"

#include <iostream>

namespace tex {

  class InspectIntersections : public art::EDAnalyzer {

  public:

    explicit InspectIntersections(fhicl::ParameterSet const& pset);

    void beginJob();
    void analyze(const art::Event& event);

  private:

    std::string _simModuleLabel;
    int         _maxPrint;

    art::ServiceHandle<art::TFileService> _tfs;

    TH1F* _hNHits;

    TNtuple* _nt;

    int _printCount;
  };

}

tex::InspectIntersections::InspectIntersections(fhicl::ParameterSet const& pset):
  _simModuleLabel( pset.get<std::string>("simModuleLabel") ),
  _maxPrint( pset.get<int>("maxPrint",0) ),
  _tfs( art::ServiceHandle<art::TFileService>() ),
  _printCount(0){
}

void tex::InspectIntersections::beginJob(){
  _hNHits = _tfs->make<TH1F>( "NHits", "Number of intersections per event", 80, 0., 80 );
  _nt = _tfs->make<TNtuple>( "nt", "Intersections of tracks with shells", "evt:trk:x:y:z" );

}

void tex::InspectIntersections::analyze(const art::Event& event){

  // Fixme: add the other container
  art::Handle<IntersectionCollection> hitsHandle;
  event.getByLabel( _simModuleLabel, "outer",hitsHandle);
  IntersectionCollection const& hits(*hitsHandle);

  _hNHits->Fill( hits.size() );

  bool doPrint( _printCount++ < _maxPrint );
  if ( doPrint ){
    std::cout << "\nHit Summary for Event: " << event.id() << std::endl;
  }

  float ntData[5];
  int n(0);
  for ( auto const& hit: hits ){
    ntData[0] = event.id().event();
    ntData[1] = hit.genTrack().key();
    ntData[2] = hit.position().x();
    ntData[3] = hit.position().y();
    ntData[4] = hit.position().z();
    _nt->Fill( ntData );

    if ( doPrint ){
      std::cout << "Hit: "
                << n++ << " "
                << hit.genTrack().key()   << " "
                << hit.shell() << " "
                << hit.position()
                << std::endl;
    }
  }

}

DEFINE_ART_MODULE(tex::InspectIntersections)
