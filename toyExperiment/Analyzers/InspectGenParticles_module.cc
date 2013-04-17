//
//  Look at the contents of the GenParticleCollection; make both printout and histograms.
//

#include "toyExperiment/MCDataProducts/GenParticleCollection.h"

#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Services/Optional/TFileService.h"

#include "TH1F.h"
#include "TNtuple.h"

#include "CLHEP/Units/SystemOfUnits.h"

#include <iostream>
#include <string>

namespace tex {

  class InspectGenParticles : public art::EDAnalyzer {

  public:

    explicit InspectGenParticles(fhicl::ParameterSet const& pset);

    void beginJob();
    void analyze(const art::Event& event);

  private:

    std::string _gensModuleLabel;
    int         _maxPrint;

    art::ServiceHandle<art::TFileService> _tfs;

    TH1F* _hNGens;
    TH1F* _hpPhi;
    TH1F* _hpKplus;
    TH1F* _hpKminus;
    TH1F* _hpOther;

    TH1F* _hczPhi;
    TH1F* _hczKplus;
    TH1F* _hczKminus;
    TH1F* _hczOther;

    TH1F* _hAngle;
    TH1F* _hMassCheck;

    TNtuple* _nt;

    int _printCount;
  };

}

tex::InspectGenParticles::InspectGenParticles(fhicl::ParameterSet const& pset):
  _gensModuleLabel( pset.get<std::string>("gensModuleLabel") ),
  _maxPrint( pset.get<int>("maxPrint",0) ),
  _tfs( art::ServiceHandle<art::TFileService>() ),
  _printCount(0){
}

void tex::InspectGenParticles::beginJob(){
  _hNGens   = _tfs->make<TH1F>( "nGens",   "Number of generated particles",        20, 0.,   20. );
  _hpPhi    = _tfs->make<TH1F>( "pPhi",    "Momentum of generated Phi; [MeV]",    100, 0., 2000. );
  _hpKplus  = _tfs->make<TH1F>( "pKplus",  "Momentum of decay K+; [MeV]",         100, 0., 2000. );
  _hpKminus = _tfs->make<TH1F>( "pKminus", "Momentum of decay K-; [MeV]",         100, 0., 2000. );
  _hpOther  = _tfs->make<TH1F>( "pKOther", "Momentum of other particles; [MeV]",  100, 0., 2000. );

  _hczPhi    = _tfs->make<TH1F>( "czPhi",    "cos(theta) of generated Phi; [MeV]",    100, -1., 1. );
  _hczKplus  = _tfs->make<TH1F>( "czKplus",  "cos(theta) of decay K+; [MeV]",         100, -1., 1. );
  _hczKminus = _tfs->make<TH1F>( "czKminus", "cos(theta) of decay K-; [MeV]",         100, -1., 1. );
  _hczOther  = _tfs->make<TH1F>( "czKOther", "cos(theta) of other particles; [MeV]",  100, -1., 1. );

  _hAngle     = _tfs->make<TH1F>( "Angle", "Openning angle between K+ K-; [degrees]",  100,    0.,  180. );
  _hMassCheck = _tfs->make<TH1F>( "MassCheck", "Mass of K+ K- pair; [MeV]",             40, 1000., 1040. );

  _nt = _tfs->make<TNtuple>( "nt", "Phi Decay Information", "p0:p1:p2" );
}

void tex::InspectGenParticles::analyze(const art::Event& event){

  // Get the generated particles from the event.
  art::Handle<GenParticleCollection> gensHandle;
  event.getByLabel( _gensModuleLabel, gensHandle);
  GenParticleCollection const& gens(*gensHandle);

  // Printout, if required.
  bool doPrint = ( ++_printCount < _maxPrint );
  if ( doPrint ) {
    std::cout << "\nNumber of GenParticles in event "
              << event.id().event() << " is: "
              << gens.size()
              << std::endl;
  }

  _hNGens->Fill(gens.size());

  // Loop over all of the generated particles.
  for ( auto const& gen:gens ){

    if ( doPrint ) {
      std::cout << gen << std::endl;
    }

    double p  = gen.momentum().vect().mag();
    double cz = gen.momentum().vect().cosTheta();

    if ( gen.pdgId() == PDGCode::phi ){
      _hpPhi->Fill( p );
      _hczPhi->Fill( cz );

    } else if ( gen.pdgId() == PDGCode::K_plus ){
      _hpKplus->Fill( p );
      _hczKplus->Fill( cz );

    } else if ( gen.pdgId() == PDGCode::K_minus ){
      _hpKminus->Fill( p );
      _hczKminus->Fill( cz );

    } else {
      _hpOther->Fill( p );
      _hczOther->Fill( cz );
    }
  }

  if ( gens.size() > 2 ) {
    CLHEP::Hep3Vector const& p1 = gens.at(1).momentum().vect();
    CLHEP::Hep3Vector const& p2 = gens.at(2).momentum().vect();

    double angle = p1.angle(p2)/CLHEP::degree;
    _hAngle->Fill(angle);

    float ntData[3];
    ntData[0] = gens.at(0).momentum().vect().mag();
    ntData[1] = gens.at(1).momentum().vect().mag();
    ntData[2] = gens.at(2).momentum().vect().mag();

    _nt->Fill(ntData);

    CLHEP::HepLorentzVector psum = gens.at(1).momentum() + gens.at(2).momentum();
    _hMassCheck->Fill( psum.mag() );

  }

}

DEFINE_ART_MODULE(tex::InspectGenParticles)
