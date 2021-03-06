#include "DataFormats/HeavyIonEvent/interface/Centrality.h"
#include "DataFormats/HeavyIonEvent/interface/EvtPlane.h"
#include "DataFormats/HeavyIonEvent/interface/HeavyIon.h"
#include "DataFormats/HeavyIonEvent/interface/VoronoiBackground.h"
#include "DataFormats/Common/interface/Wrapper.h"

namespace { 
  struct dictionary {

    reco::EvtPlane dummy1;
    edm::Wrapper<reco::EvtPlane> dummy2;

    reco::Centrality dummy3;
    edm::Wrapper<reco::Centrality> dummy4;

     reco::CentralityCollection ccol;
     edm::Wrapper<reco::CentralityCollection> wccol;

     reco::EvtPlaneCollection evcol;
     edm::Wrapper<reco::EvtPlaneCollection> wevcol;

     reco::VoronoiBackground vor;
     edm::Wrapper<reco::VoronoiBackground> wvor;

     reco::VoronoiMap pfvorvmap;
     edm::Wrapper<reco::VoronoiMap> pfwvorvmap;

     std::vector<reco::VoronoiBackground> vecvor;
     edm::Wrapper<std::vector<reco::VoronoiBackground> > vecwvor;

     edm::Wrapper<pat::HeavyIon >              w_v_p_hi;

  };
}


