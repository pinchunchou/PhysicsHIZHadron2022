#include <algorithm>
#include <iostream>
#include <vector>

#include "TFile.h"
#include "TTree.h"

#include "Messenger.h"

namespace EmptyVectors
{
   std::vector<double> EmptyVectorDouble;
   std::vector<float> EmptyVectorFloat;
   std::vector<int> EmptyVectorInt;
   std::vector<std::vector<float> > EmptyVectorVectorFloat;
}

HiEventTreeMessenger::HiEventTreeMessenger(TFile &File)
{
   Tree = (TTree *)File.Get("hiEvtAnalyzer/HiTree");
   Initialize();
}

HiEventTreeMessenger::HiEventTreeMessenger(TFile *File)
{
   if(File != nullptr)
      Tree = (TTree *)File->Get("hiEvtAnalyzer/HiTree");
   else
      Tree = nullptr;
   Initialize();
}

HiEventTreeMessenger::HiEventTreeMessenger(TTree *HiEventTree)
{
   Initialize(HiEventTree);
}
   
bool HiEventTreeMessenger::Initialize(TTree *HiEventTree)
{
   Tree = HiEventTree;
   return Initialize();
}

bool HiEventTreeMessenger::Initialize()
{
   if(Tree == nullptr)
      return false;

   if(Tree->GetBranch("hiHF"))  Tree->SetBranchAddress("hiHF", &hiHF);
   else                         hiHF = 0;
   if(Tree->GetBranch("hiBin")) Tree->SetBranchAddress("hiBin", &hiBin);
   else                         hiBin = 0;
   if(Tree->GetBranch("run"))   Tree->SetBranchAddress("run", &Run);
   else                         Run = 1;
   if(Tree->GetBranch("evt"))   Tree->SetBranchAddress("evt", &Event);
   else                         Event = 1;
   if(Tree->GetBranch("lumi"))  Tree->SetBranchAddress("lumi", &Lumi);
   else                         Lumi = 1;
   if(Tree->GetBranch("weight"))  Tree->SetBranchAddress("weight", &weight);
   else                         weight = 1;
   if(Tree->GetBranch("hiHFplus"))  Tree->SetBranchAddress("hiHFplus", &hiHFplus);
   else                         hiHFplus = 0;
   if(Tree->GetBranch("hiHFminus"))  Tree->SetBranchAddress("hiHFminus", &hiHFminus);
   else                         hiHFminus = 0;
   if(Tree->GetBranch("hiHFplusEta4"))  Tree->SetBranchAddress("hiHFplusEta4", &hiHFplusEta4);
   else                         hiHFplusEta4 = 0;
   if(Tree->GetBranch("hiHFminusEta4"))  Tree->SetBranchAddress("hiHFminusEta4", &hiHFminusEta4);
   else                         hiHFminusEta4 = 0;
   if(Tree->GetBranch("hiNevtPlane"))   Tree->SetBranchAddress("hiNevtPlane", &hiNevtPlane);
   else                         hiNevtPlane = 0;
   if(Tree->GetBranch("hiEvtPlanes"))   Tree->SetBranchAddress("hiEvtPlanes", &hiEvtPlanes);
   
   return true;
}

bool HiEventTreeMessenger::GetEntry(int iEntry)
{
   if(Tree == nullptr)
      return false;

   Tree->GetEntry(iEntry);
   return true;
}
   
int HiEventTreeMessenger::GetEntries()
{
   if(Tree == nullptr)
      return 0;

   return Tree->GetEntries();
}

GGTreeMessenger::GGTreeMessenger(TFile &File, std::string TreeName)
{
   Tree = (TTree *)File.Get(TreeName.c_str());
   Initialize();
}

GGTreeMessenger::GGTreeMessenger(TFile *File, std::string TreeName)
{
   if(File != nullptr)
      Tree = (TTree *)File->Get(TreeName.c_str());
   else
      Tree = nullptr;
   Initialize();
}

GGTreeMessenger::GGTreeMessenger(TTree *EventTree)
{
   Tree = EventTree;
   Initialize();
}

bool GGTreeMessenger::Initialize(TTree *EventTree)
{
   Tree = EventTree;
   return Initialize();
}

bool GGTreeMessenger::Initialize()
{
   if(Tree == nullptr)
      return false;

   PUCount = nullptr;
   PUBX = nullptr;
   PUTrue = nullptr;

   if(Tree->GetBranch("nPUInfo"))   Tree->SetBranchAddress("nPUInfo", &NPUInfo);
   else                             NPUInfo = 0;
   if(Tree->GetBranch("nPU"))       Tree->SetBranchAddress("nPU", &PUCount);
   else                             PUCount = &EmptyVectors::EmptyVectorInt;
   if(Tree->GetBranch("puBX"))      Tree->SetBranchAddress("puBX", &PUBX);
   else                             PUBX = &EmptyVectors::EmptyVectorInt;
   if(Tree->GetBranch("puTrue"))    Tree->SetBranchAddress("puTrue", &PUTrue);
   else                             PUTrue = &EmptyVectors::EmptyVectorFloat;
   
   PFJetPT = nullptr;
   PFJetEta = nullptr;
   PFJetPhi = nullptr;
   CaloJetPT = nullptr;
   CaloJetEta = nullptr;
   CaloJetPhi = nullptr;
   GenJetPT = nullptr;
   GenJetEta = nullptr;
   GenJetPhi = nullptr;

   if(Tree->GetBranch("nPFJt"))         Tree->SetBranchAddress("nPFJt", &PFJetCount);
   else                                 PFJetCount = 0;
   if(Tree->GetBranch("pfJtPt"))        Tree->SetBranchAddress("pfJtPt", &PFJetPT);
   else                                 PFJetPT = &EmptyVectors::EmptyVectorFloat;
   if(Tree->GetBranch("pfJtEta"))       Tree->SetBranchAddress("pfJtEta", &PFJetEta);
   else                                 PFJetEta = &EmptyVectors::EmptyVectorFloat;
   if(Tree->GetBranch("pfJtPhi"))       Tree->SetBranchAddress("pfJtPhi", &PFJetPhi);
   else                                 PFJetPhi = &EmptyVectors::EmptyVectorFloat;
   if(Tree->GetBranch("nCaloJt"))       Tree->SetBranchAddress("nCaloJt", &CaloJetCount);
   else                                 CaloJetCount = 0;
   if(Tree->GetBranch("caloJtPt"))      Tree->SetBranchAddress("caloJtPt", &CaloJetPT);
   else                                 CaloJetPT = &EmptyVectors::EmptyVectorFloat;
   if(Tree->GetBranch("caloJtEta"))     Tree->SetBranchAddress("caloJtEta", &CaloJetEta);
   else                                 CaloJetEta = &EmptyVectors::EmptyVectorFloat;
   if(Tree->GetBranch("caloJtPhi"))     Tree->SetBranchAddress("caloJtPhi", &CaloJetPhi);
   else                                 CaloJetPhi = &EmptyVectors::EmptyVectorFloat;
   if(Tree->GetBranch("nGenJt"))        Tree->SetBranchAddress("nGenJt", &GenJetCount);
   else                                 GenJetCount = 0;
   if(Tree->GetBranch("genJtPt"))       Tree->SetBranchAddress("genJtPt", &GenJetPT);
   else                                 GenJetPT = &EmptyVectors::EmptyVectorFloat;
   if(Tree->GetBranch("genJtEta"))      Tree->SetBranchAddress("genJtEta", &GenJetEta);
   else                                 GenJetEta = &EmptyVectors::EmptyVectorFloat;
   if(Tree->GetBranch("genJtPhi"))      Tree->SetBranchAddress("genJtPhi", &GenJetPhi);
   else                                 GenJetPhi = &EmptyVectors::EmptyVectorFloat;

   return true;
}

bool GGTreeMessenger::GetEntry(int iEntry)
{
   if(Tree == nullptr)
      return false;

   Tree->GetEntry(iEntry);
   return true;
}

RhoTreeMessenger::RhoTreeMessenger(TFile &File, std::string TreeName)
{
   Tree = (TTree *)File.Get(TreeName.c_str());
   Initialize();
}

RhoTreeMessenger::RhoTreeMessenger(TFile *File, std::string TreeName)
{
   if(File != nullptr)
      Tree = (TTree *)File->Get(TreeName.c_str());
   else
      Tree = nullptr;
   Initialize();
}

RhoTreeMessenger::RhoTreeMessenger(TTree *RhoTree)
{
   Initialize(RhoTree);
}
   
bool RhoTreeMessenger::Initialize(TTree *RhoTree)
{
   Tree = RhoTree;
   return Initialize();
}

bool RhoTreeMessenger::Initialize()
{
   if(Tree == nullptr)
      return false;

   EtaMin = nullptr;
   EtaMax = nullptr;
   Rho = nullptr;
   RhoM = nullptr;

   if(Tree->GetBranch("etaMin")) Tree->SetBranchAddress("etaMin", &EtaMin);
   else                          EtaMin = &EmptyVectors::EmptyVectorDouble;
   if(Tree->GetBranch("etaMax")) Tree->SetBranchAddress("etaMax", &EtaMax);
   else                          EtaMax = &EmptyVectors::EmptyVectorDouble;
   if(Tree->GetBranch("rho"))    Tree->SetBranchAddress("rho", &Rho);
   else                          Rho = &EmptyVectors::EmptyVectorDouble;
   if(Tree->GetBranch("rhom"))   Tree->SetBranchAddress("rhom", &RhoM);
   else                          RhoM = &EmptyVectors::EmptyVectorDouble;

   return true;
}

bool RhoTreeMessenger::GetEntry(int iEntry)
{
   if(Tree == nullptr)
      return false;

   Tree->GetEntry(iEntry);
   return true;
}

SkimTreeMessenger::SkimTreeMessenger(TFile &File)
{
   Tree = (TTree *)File.Get("skimanalysis/HltTree");
   Initialize();
}

SkimTreeMessenger::SkimTreeMessenger(TFile *File)
{
   if(File != nullptr)
      Tree = (TTree *)File->Get("skimanalysis/HltTree");
   else
      Tree = nullptr;
   Initialize();
}

SkimTreeMessenger::SkimTreeMessenger(TTree *SkimTree)
{
   Initialize(SkimTree);
}

bool SkimTreeMessenger::Initialize(TTree *SkimTree)
{
   Tree = SkimTree;
   return Initialize();
}

bool SkimTreeMessenger::Initialize()
{
   if(Tree == nullptr)
      return false;

   if(Tree->GetBranch("HBHENoiseFilterResult"))
      Tree->SetBranchAddress("HBHENoiseFilterResult", &HBHENoise);
   else
      HBHENoise = 1;
   if(Tree->GetBranch("HBHENoiseFilterResultRun2Loose"))
      Tree->SetBranchAddress("HBHENoiseFilterResultRun2Loose", &HBHENoiseRun2Loose);
   else
      HBHENoiseRun2Loose = 1;
   if(Tree->GetBranch("pprimaryVertexFilter"))
      Tree->SetBranchAddress("pprimaryVertexFilter", &PVFilter);
   else if(Tree->GetBranch("pPAprimaryVertexFilter"))
      Tree->SetBranchAddress("pPAprimaryVertexFilter", &PVFilter);
   else
      PVFilter = 1;
   if(Tree->GetBranch("pBeamScrapingFilter"))
      Tree->SetBranchAddress("pBeamScrapingFilter", &BeamScrapingFilter);
   else
      BeamScrapingFilter = 1;
   if(Tree->GetBranch("pclusterCompatibilityFilter"))
      Tree->SetBranchAddress("pclusterCompatibilityFilter", &ClusterCompatibilityFilter);
   else
      ClusterCompatibilityFilter = 1;
   if(Tree->GetBranch("phfCoincFilter3"))
      Tree->SetBranchAddress("phfCoincFilter3", &HFCoincidenceFilter);
   else
      HFCoincidenceFilter = 1;
   if(Tree->GetBranch("phfCoincFilter2Th4"))
      Tree->SetBranchAddress("phfCoincFilter2Th4", &HFCoincidenceFilter2Th4);
   else
      HFCoincidenceFilter2Th4 = 1;
   if(Tree->GetBranch("pcollisionEventSelection"))
      Tree->SetBranchAddress("pcollisionEventSelection", &CollisionEventSelection);
   else
      CollisionEventSelection = 1;

   return true;
}

bool SkimTreeMessenger::PassBasicFilter()
{
   if(HBHENoise == 0)
      return false;
   if(HBHENoiseRun2Loose == 0)
      return false;
   if(PVFilter == 0)
      return false;
   if(ClusterCompatibilityFilter == 0)
      return false;
   if(HFCoincidenceFilter2Th4 == 0)
      return false;
   if(CollisionEventSelection == 0)
      return false;

   return true;
}

bool SkimTreeMessenger::PassBasicFilterLoose()
{
   if(HBHENoiseRun2Loose == 0)
      return false;
   if(PVFilter == 0)
      return false;
   if(ClusterCompatibilityFilter == 0)
      return false;
   if(HFCoincidenceFilter2Th4 == 0)
      return false;
   if(CollisionEventSelection == 0)
      return false;

   return true;
}

bool SkimTreeMessenger::GetEntry(int iEntry)
{
   if(Tree == nullptr)
      return false;

   Tree->GetEntry(iEntry);
   return true;
}

JetTreeMessenger::JetTreeMessenger(TFile &File, std::string TreeName)
{
   Tree = (TTree *)File.Get(TreeName.c_str());
   Initialize();
}

JetTreeMessenger::JetTreeMessenger(TFile *File, std::string TreeName)
{
   if(File != nullptr)
      Tree = (TTree *)File->Get(TreeName.c_str());
   else
      Tree = nullptr;
   Initialize();
}

JetTreeMessenger::JetTreeMessenger(TTree *JetTree)
{
   Initialize(JetTree);
}

bool JetTreeMessenger::Initialize(TTree *JetTree)
{
   Tree = JetTree;
   return Initialize();
}

bool JetTreeMessenger::Initialize()
{
   if(Tree == nullptr)
      return false;

   JetSubJetPT = nullptr;
   JetSubJetEta = nullptr;
   JetSubJetPhi = nullptr;
   JetSubJetM = nullptr;
   RefGSubJetPT = nullptr;
   RefGSubJetEta = nullptr;
   RefGSubJetPhi = nullptr;
   RefGSubJetM = nullptr;

   if(Tree->GetBranch("pthat"))   Tree->SetBranchAddress("pthat", &PTHat);

   if(Tree->GetBranch("nref"))    Tree->SetBranchAddress("nref", &JetCount);
   else                           JetCount = 0;
   if(Tree->GetBranch("rawpt"))   Tree->SetBranchAddress("rawpt", &JetRawPT);
   if(Tree->GetBranch("jtpt"))    Tree->SetBranchAddress("jtpt", &JetPT);
   if(Tree->GetBranch("jteta"))   Tree->SetBranchAddress("jteta", &JetEta);
   if(Tree->GetBranch("jty"))     Tree->SetBranchAddress("jty", &JetY);
   if(Tree->GetBranch("jtphi"))   Tree->SetBranchAddress("jtphi", &JetPhi);
   if(Tree->GetBranch("jtpu"))    Tree->SetBranchAddress("jtpu", &JetPU);
   if(Tree->GetBranch("jtm"))     Tree->SetBranchAddress("jtm", &JetM);
   if(Tree->GetBranch("jttau1"))  Tree->SetBranchAddress("jttau1", &JetTau1);
   if(Tree->GetBranch("jttau2"))  Tree->SetBranchAddress("jttau2", &JetTau2);
   if(Tree->GetBranch("jttau3"))  Tree->SetBranchAddress("jttau3", &JetTau3);
   if(Tree->GetBranch("jtarea"))  Tree->SetBranchAddress("jtarea", &JetArea);
   if(Tree->GetBranch("discr_csvV1"))  Tree->SetBranchAddress("discr_csvV1", &JetCSVV1);
   if(Tree->GetBranch("discr_csvV2"))  Tree->SetBranchAddress("discr_csvV2", &JetCSVV2);
   if(Tree->GetBranch("ndiscr_csvV1")) Tree->SetBranchAddress("ndiscr_csvV1", &JetCSVV1N);
   if(Tree->GetBranch("ndiscr_csvV2")) Tree->SetBranchAddress("ndiscr_csvV2", &JetCSVV2N);
   if(Tree->GetBranch("pdiscr_csvV1")) Tree->SetBranchAddress("pdiscr_csvV1", &JetCSVV1P);
   if(Tree->GetBranch("pdiscr_csvV2")) Tree->SetBranchAddress("pdiscr_csvV2", &JetCSVV2P);

   if(Tree->GetBranch("jtSubJetPt"))
      Tree->SetBranchAddress("jtSubJetPt", &JetSubJetPT);
   else
      JetSubJetPT = &EmptyVectors::EmptyVectorVectorFloat;
   if(Tree->GetBranch("jtSubJetEta"))
      Tree->SetBranchAddress("jtSubJetEta", &JetSubJetEta);
   else
      JetSubJetEta = &EmptyVectors::EmptyVectorVectorFloat;
   if(Tree->GetBranch("jtSubJetPhi"))
      Tree->SetBranchAddress("jtSubJetPhi", &JetSubJetPhi);
   else
      JetSubJetPhi = &EmptyVectors::EmptyVectorVectorFloat;
   if(Tree->GetBranch("jtSubJetM"))
      Tree->SetBranchAddress("jtSubJetM", &JetSubJetM);
   else
      JetSubJetM = &EmptyVectors::EmptyVectorVectorFloat;
   if(Tree->GetBranch("jtsym"))
      Tree->SetBranchAddress("jtsym", &JetSym);
   else
      for(int i = 0; i < JETCOUNTMAX; i++)
         JetSym[i] = -1;
   if(Tree->GetBranch("jtdroppedBranches"))
      Tree->SetBranchAddress("jtdroppedBranches", &JetDroppedBranches);
   else
      for(int i = 0; i < JETCOUNTMAX; i++)
         JetDroppedBranches[i] = -1;
   
   if(Tree->GetBranch("refpt"))   Tree->SetBranchAddress("refpt", &RefPT);
   if(Tree->GetBranch("refeta"))  Tree->SetBranchAddress("refeta", &RefEta);
   if(Tree->GetBranch("refy"))    Tree->SetBranchAddress("refy", &RefY);
   if(Tree->GetBranch("refphi"))  Tree->SetBranchAddress("refphi", &RefPhi);
   if(Tree->GetBranch("refm"))    Tree->SetBranchAddress("refm", &RefM);
   if(Tree->GetBranch("refarea")) Tree->SetBranchAddress("refarea", &RefArea);
   
   if(Tree->GetBranch("refptG"))  Tree->SetBranchAddress("refptG", &RefGPT);
   if(Tree->GetBranch("refetaG")) Tree->SetBranchAddress("refetaG", &RefGEta);
   if(Tree->GetBranch("refphiG")) Tree->SetBranchAddress("refphiG", &RefGPhi);
   if(Tree->GetBranch("refmG"))   Tree->SetBranchAddress("refmG", &RefGM);

   if(Tree->GetBranch("refparton_pt"))
      Tree->SetBranchAddress("refparton_pt", &RefPartonPT);
   if(Tree->GetBranch("refparton_flavor"))
      Tree->SetBranchAddress("refparton_flavor", &RefPartonFlavor);
   if(Tree->GetBranch("refparton_flavorForB"))
      Tree->SetBranchAddress("refparton_flavorForB", &RefPartonFlavorForB);
   
   if(Tree->GetBranch("refSubJetPt"))
      Tree->SetBranchAddress("refSubJetPt", &RefGSubJetPT);
   else
      RefGSubJetPT = &EmptyVectors::EmptyVectorVectorFloat;
   if(Tree->GetBranch("refSubJetEta"))
      Tree->SetBranchAddress("refSubJetEta", &RefGSubJetEta);
   else
      RefGSubJetEta = &EmptyVectors::EmptyVectorVectorFloat;
   if(Tree->GetBranch("refSubJetPhi"))
      Tree->SetBranchAddress("refSubJetPhi", &RefGSubJetPhi);
   else
      RefGSubJetPhi = &EmptyVectors::EmptyVectorVectorFloat;
   if(Tree->GetBranch("refSubJetM"))
      Tree->SetBranchAddress("refSubJetM", &RefGSubJetM);
   else
      RefGSubJetM = &EmptyVectors::EmptyVectorVectorFloat;
   
   if(Tree->GetBranch("ngen"))    Tree->SetBranchAddress("ngen", &GenCount);
   else                           GenCount = 0;
   
   if(Tree->GetBranch("genmatchindex"))
      Tree->SetBranchAddress("genmatchindex", &GenMatchIndex);
   else
      for(int i = 0; i < JETCOUNTMAX; i++)
         GenMatchIndex[i] = -1;
   if(Tree->GetBranch("genpt"))   Tree->SetBranchAddress("genpt", &GenPT);
   if(Tree->GetBranch("geneta"))  Tree->SetBranchAddress("geneta", &GenEta);
   if(Tree->GetBranch("geny"))    Tree->SetBranchAddress("geny", &GenY);
   if(Tree->GetBranch("genphi"))  Tree->SetBranchAddress("genphi", &GenPhi);
   if(Tree->GetBranch("genm"))    Tree->SetBranchAddress("genm", &GenM);

   if(Tree->GetBranch("hcalSum")) Tree->SetBranchAddress("hcalSum", &HcalSum);
   if(Tree->GetBranch("ecalSum")) Tree->SetBranchAddress("ecalSum", &EcalSum);

   if(Tree->GetBranch("jtPfCHF")) Tree->SetBranchAddress("jtPfCHF", &JetPFCHF);
   if(Tree->GetBranch("jtPfNHF")) Tree->SetBranchAddress("jtPfNHF", &JetPFNHF);
   if(Tree->GetBranch("jtPfCEF")) Tree->SetBranchAddress("jtPfCEF", &JetPFCEF);
   if(Tree->GetBranch("jtPfNEF")) Tree->SetBranchAddress("jtPfNEF", &JetPFNEF);
   if(Tree->GetBranch("jtPfMUF")) Tree->SetBranchAddress("jtPfMUF", &JetPFMUF);
   if(Tree->GetBranch("jtPfCHM")) Tree->SetBranchAddress("jtPfCHM", &JetPFCHM);
   if(Tree->GetBranch("jtPfNHM")) Tree->SetBranchAddress("jtPfNHM", &JetPFNHM);
   if(Tree->GetBranch("jtPfCEM")) Tree->SetBranchAddress("jtPfCEM", &JetPFCEM);
   if(Tree->GetBranch("jtPfNEM")) Tree->SetBranchAddress("jtPfNEM", &JetPFNEM);
   if(Tree->GetBranch("jtPfMUM")) Tree->SetBranchAddress("jtPfMUM", &JetPFMUM);

   return true;
}

bool JetTreeMessenger::GetEntry(int iEntry)
{
   if(Tree == nullptr)
      return false;

   Tree->GetEntry(iEntry);
   return true;
}

GenParticleTreeMessenger::GenParticleTreeMessenger(TFile &File)
{
   Tree = (TTree *)File.Get("HiGenParticleAna/hi");
   Initialize();
}

GenParticleTreeMessenger::GenParticleTreeMessenger(TFile *File)
{
   if(File != nullptr)
      Tree = (TTree *)File->Get("HiGenParticleAna/hi");
   else
      Tree = nullptr;
   Initialize();
}

GenParticleTreeMessenger::GenParticleTreeMessenger(TTree *GenParticleTree)
{
   Initialize(GenParticleTree);
}

bool GenParticleTreeMessenger::Initialize(TTree *GenParticleTree)
{
   Tree = GenParticleTree;
   return Initialize();
}

bool GenParticleTreeMessenger::Initialize()
{
   if(Tree == nullptr)
      return false;

   PT = nullptr;
   Eta = nullptr;
   Phi = nullptr;
   ID = nullptr;
   Charge = nullptr;
   DaughterCount = nullptr;
   SubEvent = nullptr;

   if(Tree->GetBranch("npart")) Tree->SetBranchAddress("npart", &NPart);
   else                         NPart = 0;
   if(Tree->GetBranch("ncoll")) Tree->SetBranchAddress("ncoll", &NColl);
   else                         NColl = 0;
   if(Tree->GetBranch("nhard")) Tree->SetBranchAddress("nhard", &NHard);
   else                         NHard = 0;
   if(Tree->GetBranch("phi0"))  Tree->SetBranchAddress("phi0", &Phi0);
   else                         Phi0 = 0;

   if(Tree->GetBranch("pt"))    Tree->SetBranchAddress("pt", &PT);
   else                         PT = &EmptyVectors::EmptyVectorFloat;
   if(Tree->GetBranch("eta"))   Tree->SetBranchAddress("eta", &Eta);
   else                         Eta = &EmptyVectors::EmptyVectorFloat;
   if(Tree->GetBranch("phi"))   Tree->SetBranchAddress("phi", &Phi);
   else                         Phi = &EmptyVectors::EmptyVectorFloat;
   if(Tree->GetBranch("pdg"))   Tree->SetBranchAddress("pdg", &ID);
   else                         ID = &EmptyVectors::EmptyVectorInt;
   if(Tree->GetBranch("chg")) Tree->SetBranchAddress("chg", &Charge);
   else                         Charge = &EmptyVectors::EmptyVectorInt;
   if(Tree->GetBranch("nDaughters")) Tree->SetBranchAddress("nDaughters", &DaughterCount);
   else                         DaughterCount = &EmptyVectors::EmptyVectorInt;
   if(Tree->GetBranch("sube"))  Tree->SetBranchAddress("sube", &SubEvent);
   else                         SubEvent = &EmptyVectors::EmptyVectorInt;

   return true;
}

bool GenParticleTreeMessenger::GetEntry(int iEntry)
{
   if(Tree == nullptr)
      return false;

   Tree->GetEntry(iEntry);
   return true;
}

PFTreeMessenger::PFTreeMessenger(TFile &File, std::string TreeName)
{
   Initialize(File, TreeName);
}

PFTreeMessenger::PFTreeMessenger(TFile *File, std::string TreeName)
{
   Initialize(File, TreeName);
}

PFTreeMessenger::PFTreeMessenger(TTree *PFTree)
{
   Initialize(PFTree);
}

bool PFTreeMessenger::Initialize(TFile &File, std::string TreeName)
{
   Tree = (TTree *)File.Get(TreeName.c_str());
   return Initialize();
}

bool PFTreeMessenger::Initialize(TFile *File, std::string TreeName)
{
   if(File != nullptr)
      Tree = (TTree *)File->Get(TreeName.c_str());
   else
      Tree = nullptr;
   return Initialize();
}

bool PFTreeMessenger::Initialize(TTree *PFTree)
{
   Tree = PFTree;
   return Initialize();
}

bool PFTreeMessenger::Initialize()
{
   if(Tree == nullptr)
      return false;

   ID = nullptr;
   PT = nullptr;
   E = nullptr;
   Eta = nullptr;
   Phi = nullptr;
   M = nullptr;

   if(Tree->GetBranch("pfId"))     Tree->SetBranchAddress("pfId", &ID);
   else                            ID = &EmptyVectors::EmptyVectorInt;
   if(Tree->GetBranch("pfPt"))     Tree->SetBranchAddress("pfPt", &PT);
   else                            PT = &EmptyVectors::EmptyVectorFloat;
   if(Tree->GetBranch("pfEnergy")) Tree->SetBranchAddress("pfEnergy", &E);
   else if(Tree->GetBranch("pfE")) Tree->SetBranchAddress("pfE", &E);
   else                            E = &EmptyVectors::EmptyVectorFloat;
   if(Tree->GetBranch("pfEta"))    Tree->SetBranchAddress("pfEta", &Eta);
   else                            Eta = &EmptyVectors::EmptyVectorFloat;
   if(Tree->GetBranch("pfPhi"))    Tree->SetBranchAddress("pfPhi", &Phi);
   else                            Phi = &EmptyVectors::EmptyVectorFloat;
   if(Tree->GetBranch("pfM"))      Tree->SetBranchAddress("pfM", &M);
   else                            M = &EmptyVectors::EmptyVectorFloat;

   return true;
}

bool PFTreeMessenger::GetEntry(int iEntry)
{
   if(Tree == nullptr)
      return false;

   Tree->GetEntry(iEntry);
   return true;
}

TriggerTreeMessenger::TriggerTreeMessenger(TFile &File, std::string TreeName)
{
   Tree = (TTree *)File.Get(TreeName.c_str());
   Initialize();
}

TriggerTreeMessenger::TriggerTreeMessenger(TFile *File, std::string TreeName)
{
   if(File != nullptr)
      Tree = (TTree *)File->Get(TreeName.c_str());
   else
      Tree = nullptr;
   Initialize();
}

TriggerTreeMessenger::TriggerTreeMessenger(TTree *TriggerTree)
{
   Initialize(TriggerTree);
}

bool TriggerTreeMessenger::Initialize(TTree *TriggerTree)
{
   Tree = TriggerTree;
   return Initialize();
}

bool TriggerTreeMessenger::Initialize()
{
   if(Tree == nullptr)
      return false;

   if(Tree->GetBranch("Run"))   Tree->SetBranchAddress("Run", &Run);
   else                         Run = 0;
   if(Tree->GetBranch("LumiBlock")) Tree->SetBranchAddress("LumiBlock", &Lumi);
   else                         Lumi = 0;
   if(Tree->GetBranch("Event")) Tree->SetBranchAddress("Event", &Event);
   else                         Event = 0;

   FillTriggerNames();

   for(int i = 0; i < (int)Name.size(); i++)
   {
      if(Tree->GetBranch(Name[i].c_str()))
      {
         Tree->SetBranchAddress(Name[i].c_str(), &Decision[i]);
         Exist[i] = true;
         
         if(Tree->GetBranch((Name[i] + "_Prescl").c_str()))
         {
            Tree->SetBranchAddress((Name[i] + "_Prescl").c_str(), &Prescale[i]);
            PrescaleExist[i] = true;
         }
         else
         {
            Prescale[i] = -1;
            PrescaleExist[i] = false;
         }
      }
      else
      {
         Decision[i] = false;
         Exist[i] = false;
      }
   }

   return true;
}

bool TriggerTreeMessenger::GetEntry(int iEntry)
{
   if(Tree == nullptr)
      return false;

   Tree->GetEntry(iEntry);
   return true;
}
   
void TriggerTreeMessenger::FillTriggerNames()
{
   Name.clear();
   Decision.clear();
   
   // 2018 triggers
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part0_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part1_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part2_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part3_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part4_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part5_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part6_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part7_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part8_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part9_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part10_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part11_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part12_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part13_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part14_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part15_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part16_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part17_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part18_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixBypass_part19_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part0_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part1_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part2_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part3_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part4_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part5_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part6_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part7_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part8_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part9_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part10_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part11_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part12_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part13_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part14_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part15_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part16_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part17_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part18_v1");
   Name.push_back("HLT_HIMinimumBias_SinglePixelTrack_NpixGated_part19_v1");

   // 2018 AA trigger
   Name.push_back("HLT_HIPuAK4CaloJet100Eta5p1_v1");
   Name.push_back("HLT_HIPuAK4CaloJet80Eta5p1_v1");
   Name.push_back("HLT_HIPuAK4CaloJet60Eta5p1_v1");
   Name.push_back("HLT_HIPuAK4CaloJet60Eta5p1_v1");
   Name.push_back("HLT_HIPuAK4CaloJet40Eta5p1_v1");

   // AA trigger
   Name.push_back("HLT_HIPuAK4CaloJet100_Eta5p1_v1");
   Name.push_back("HLT_HIPuAK4CaloJet80_Eta5p1_v1");
   Name.push_back("HLT_HIPuAK4CaloJet60_Eta5p1_v1");
   Name.push_back("HLT_HIPuAK4CaloJet60_Eta5p1_v1");
   Name.push_back("HLT_HIPuAK4CaloJet40_Eta5p1_v1");

   Name.push_back("HLT_PAAK4PFJet40_Eta5p1v2");
   Name.push_back("HLT_PAAK4PFJet60_Eta5p1_v2");
   Name.push_back("HLT_PAAK4PFJet80_Eta5p1_v2");

   // pp trigger
   Name.push_back("HLT_AK4PFJet80_Eta5p1_v1");
   Name.push_back("HLT_HIAK4PFJet40_v1");
   Name.push_back("HLT_HIAK4PFJet60_v1");
   Name.push_back("HLT_HIAK4PFJet80_v1");
   Name.push_back("HLT_HIAK4PFJet100_v1");
   Name.push_back("HLT_HIAK4PFJet120_v1");

   // L1 pass through
   Name.push_back("HLT_L1SingleJet8_v1_BptxAND_v1");
   Name.push_back("HLT_L1SingleJet12_v1_BptxAND_v1");
   Name.push_back("HLT_L1SingleJet16_v1");
   Name.push_back("HLT_L1SingleJet20_v1");
   Name.push_back("HLT_L1SingleJet35_v1");
   Name.push_back("HLT_L1SingleJet40_v1");
   Name.push_back("HLT_L1SingleJet44_v1");
   Name.push_back("HLT_L1SingleJet60_v1");

   // pA temporary triggers - v16
   // Name.push_back("HLT_PAAK4CaloBJetCSVv160_Eta2p1_v1");   // same in v18
   // Name.push_back("HLT_PAAK4CaloBJetCSVv260_Eta2p1_v1");   // same in v18
   Name.push_back("HLT_PAAK4PFJetCSV60_Eta2p1_v2");

   // pA temporary triggers - v22
   Name.push_back("HLT_PAAK4CaloJet60_Eta2p1_v1");
   Name.push_back("HLT_PAAK4CaloJet80_Eta2p1_v1");
   Name.push_back("HLT_PAAK4CaloJet100_Eta2p1_v1");
   Name.push_back("HLT_PAAK4CaloBJetCSVv160_Eta2p1_v1");
   Name.push_back("HLT_PAAK4CaloBJetCSVv180_Eta2p1_v1");
   Name.push_back("HLT_PAAK4CaloBJetCSVv1100_Eta2p1_v1");
   Name.push_back("HLT_PAAK4CaloBJetCSVv260_Eta2p1_v1");
   Name.push_back("HLT_PAAK4CaloBJetCSVv280_Eta2p1_v1");
   Name.push_back("HLT_PAAK4CaloBJetCSVv2100_Eta2p1_v1");
   Name.push_back("HLT_PAAK4PFJet60_Eta2p1_v1");
   Name.push_back("HLT_PAAK4PFJet80_Eta2p1_v1");
   Name.push_back("HLT_PAAK4PFJet100_Eta2p1_v1");
   Name.push_back("HLT_PAAK4PFBJetCSV60_Eta2p1_v1");
   Name.push_back("HLT_PAAK4PFBJetCSV80_Eta2p1_v1");
   Name.push_back("HLT_PAAK4PFBJetCSV100_Eta2p1_v1");

   // pA temporary triggers - v24
   Name.push_back("HLT_L1ZeroBias_BptxAND_v1");
   
   // pA temporary triggers - v27
   Name.push_back("HLT_PAAK4CaloJet40_Eta2p1_v1");
   Name.push_back("HLT_PAAK4CaloBJetCSV40_Eta2p1_v1");
   Name.push_back("HLT_PAAK4CaloBJetCSV60_Eta2p1_v1");
   Name.push_back("HLT_PAAK4CaloBJetCSV80_Eta2p1_v1");
   Name.push_back("HLT_PAAK4PFJet40_Eta2p1_v1");
   Name.push_back("HLT_PAAK4PFBJetCSV40_Eta2p1_v1");
   
   // pA temporary triggers - v31 / JCv1
   Name.push_back("HLT_PAAK4CaloBJetCSV40_CommonTracking_Eta2p1_v1");
   Name.push_back("HLT_PAAK4CaloBJetCSV60_CommonTracking_Eta2p1_v1");
   Name.push_back("HLT_PAAK4CaloBJetCSV80_CommonTracking_Eta2p1_v1");

   // Chris V14
   Name.push_back("HLT_PAAK4CaloJet40_Eta5p1_v2");
   Name.push_back("HLT_PAAK4CaloJet60_Eta5p1_v2");
   Name.push_back("HLT_PAAK4CaloJet80_Eta5p1_v2");
   Name.push_back("HLT_PAAK4CaloJet40_Eta1p9toEta5p1_v2");
   Name.push_back("HLT_PAAK4CaloJet60_Eta1p9toEta5p1_v2");
   Name.push_back("HLT_PAAK4CaloJet40_Eta2p9toEta5p1_v2");
   Name.push_back("HLT_PAAK4CaloJet40_Eta5p1_PAL3Mu3_v2");
   Name.push_back("HLT_PAAK4CaloJet40_Eta5p1_PAL3Mu5_v2");
   Name.push_back("HLT_PAAK4CaloJet60_Eta5p1_PAL3Mu3_v2");
   Name.push_back("HLT_PAAK4CaloJet60_Eta5p1_PAL3Mu5_v2");
   Name.push_back("HLT_PAAK4PFJet40_Eta5p1_v2");
   Name.push_back("HLT_PAAK4PFJet60_Eta5p1_v2");
   Name.push_back("HLT_PAAK4PFJet80_Eta5p1_v2");
   Name.push_back("HLT_PAAK4PFJet60_Eta1p9toEta5p1_v2");
   Name.push_back("HLT_PAAK4PFJet40_Eta1p9toEta5p1_v2");
   Name.push_back("HLT_PAAK4PFJet40_Eta2p9toEta5p1_v2");
   Name.push_back("HLT_PADiAK4CaloJetAve40_Eta5p1_v2");
   Name.push_back("HLT_PADiAK4CaloJetAve60_Eta5p1_v2");
   Name.push_back("HLT_PADiAK4CaloJetAve80_Eta5p1_v2");
   Name.push_back("HLT_PADiAK4PFJetAve40_Eta5p1_v2");
   Name.push_back("HLT_PADiAK4PFJetAve60_Eta5p1_v2");
   Name.push_back("HLT_PADiAK4PFJetAve80_Eta5p1_v2");
   Name.push_back("HLT_PASinglePhoton10_Eta3p1_v2");
   Name.push_back("HLT_PASinglePhoton15_Eta3p1_v2");
   Name.push_back("HLT_PASinglePhoton20_Eta3p1_v2");
   Name.push_back("HLT_PASinglePhoton30_Eta3p1_v2");
   Name.push_back("HLT_PADoublePhoton15_Eta3p1_Mass50_1000_v2");
   Name.push_back("HLT_PASinglePhoton10_Eta3p1_PAL3Mu3_v2");
   Name.push_back("HLT_PASinglePhoton10_Eta3p1_PAL3Mu5_v2");
   Name.push_back("HLT_PASinglePhoton15_Eta3p1_PAL3Mu3_v2");
   Name.push_back("HLT_PASinglePhoton15_Eta3p1_PAL3Mu5_v2");
   Name.push_back("HLT_PASinglePhoton20_Eta3p1_PAL3Mu3_v2");
   Name.push_back("HLT_PASinglePhoton20_Eta3p1_PAL3Mu5_v2");

   Name.push_back("L1_SingleJet12_BptxAND");
   
   Name.push_back("HLT_PAAK4CaloJet40_Eta5p1_v1");
   Name.push_back("HLT_PAAK4CaloJet60_Eta5p1_v1");
   Name.push_back("HLT_PAAK4CaloJet80_Eta5p1_v1");
   Name.push_back("HLT_PAAK4CaloJet100_Eta5p1_v1");
   Name.push_back("HLT_PAAK4PFJet40_Eta5p1_v1");
   Name.push_back("HLT_PAAK4PFJet60_Eta5p1_v1");
   Name.push_back("HLT_PAAK4PFJet60_Eta5p1_v3");
   Name.push_back("HLT_PAAK4PFJet80_Eta5p1_v1");
   Name.push_back("HLT_PAAK4PFJet100_Eta5p1_v1");

   Name.push_back("L1_MinimumBiasHF0_OR_BptxAND_Initial");
   Name.push_back("L1_MinimumBiasHF0_OR_BptxAND_Final");
   Name.push_back("L1_MinimumBiasHF0_OR_BptxAND");
   Name.push_back("HLT_PAL1MinimumBiasHF_AND_SinglePixelTrack_v1");
   Name.push_back("HLT_PAL1MinimumBiasHF_AND_SinglePixelTrack_v2");
   Name.push_back("HLT_PAL1MinimumBiasHF_AND_SinglePixelTrack_v3");
   Name.push_back("HLT_PAL1MinimumBiasHF_AND_SinglePixelTrack_v4");
   Name.push_back("HLT_PAL1MinimumBiasHF_AND_SinglePixelTrack_v5");

   Name.push_back("L1_SingleJet12_BptxAND_Initial");
   Name.push_back("L1_SingleJet12_BptxAND_Final");
   Name.push_back("L1_SingleJet16_BptxAND_Initial");
   Name.push_back("L1_SingleJet16_BptxAND_Final");
   Name.push_back("L1_SingleJet24_BptxAND_Initial");
   Name.push_back("L1_SingleJet24_BptxAND_Final");
   Name.push_back("L1_SingleJet36_BptxAND_Initial");
   Name.push_back("L1_SingleJet36_BptxAND_Final");
   Name.push_back("L1_SingleJet52_BptxAND_Initial");
   Name.push_back("L1_SingleJet52_BptxAND_Final");
   
   Name.push_back("L1_SingleJet12_ForEta1p5_BptxAND_Initial");
   Name.push_back("L1_SingleJet12_ForEta1p5_BptxAND_Final");
   Name.push_back("L1_SingleJet12_ForEta2p5_BptxAND_Initial");
   Name.push_back("L1_SingleJet12_ForEta2p5_BptxAND_Final");
   Name.push_back("L1_SingleJet24_ForEta1p5_BptxAND_Initial");
   Name.push_back("L1_SingleJet24_ForEta1p5_BptxAND_Final");
   Name.push_back("L1_SingleJet24_ForEta2p5_BptxAND_Initial");
   Name.push_back("L1_SingleJet24_ForEta2p5_BptxAND_Final");

   Name.push_back("HLT_PAAK4CaloJet40_Eta5p1_v3");
   Name.push_back("HLT_PAAK4CaloJet60_Eta5p1_v3");
   Name.push_back("HLT_PAAK4CaloJet80_Eta5p1_v3");
   Name.push_back("HLT_PAAK4CaloJet40_Eta1p9toEta5p1_v3");
   Name.push_back("HLT_PAAK4CaloJet60_Eta1p9toEta5p1_v3");
   Name.push_back("HLT_PAAK4CaloJet40_Eta2p9toEta5p1_v3");
   Name.push_back("HLT_PAAK4CaloJet40_Eta5p1_PAL3Mu3_v3");
   Name.push_back("HLT_PAAK4CaloJet40_Eta5p1_PAL3Mu5_v3");
   Name.push_back("HLT_PAAK4CaloJet60_Eta5p1_PAL3Mu3_v3");
   Name.push_back("HLT_PAAK4CaloJet60_Eta5p1_PAL3Mu5_v3");
   Name.push_back("HLT_PAAK4PFJet40_Eta5p1_v3");
   Name.push_back("HLT_PAAK4PFJet60_Eta5p1_v3");
   Name.push_back("HLT_PAAK4PFJet60_Eta5p1_v4");
   Name.push_back("HLT_PAAK4PFJet80_Eta5p1_v3");
   Name.push_back("HLT_PAAK4PFJet60_Eta1p9toEta5p1_v3");
   Name.push_back("HLT_PAAK4PFJet40_Eta1p9toEta5p1_v3");
   Name.push_back("HLT_PAAK4PFJet40_Eta2p9toEta5p1_v3");
   Name.push_back("HLT_PADiAK4CaloJetAve40_Eta5p1_v3");
   Name.push_back("HLT_PADiAK4CaloJetAve60_Eta5p1_v3");
   Name.push_back("HLT_PADiAK4CaloJetAve80_Eta5p1_v3");
   Name.push_back("HLT_PADiAK4PFJetAve40_Eta5p1_v3");
   Name.push_back("HLT_PADiAK4PFJetAve60_Eta5p1_v3");
   Name.push_back("HLT_PADiAK4PFJetAve80_Eta5p1_v3");
   Name.push_back("HLT_PASinglePhoton10_Eta3p1_v3");
   Name.push_back("HLT_PASinglePhoton15_Eta3p1_v3");
   Name.push_back("HLT_PASinglePhoton20_Eta3p1_v3");
   Name.push_back("HLT_PASinglePhoton30_Eta3p1_v3");
   Name.push_back("HLT_PADoublePhoton15_Eta3p1_Mass50_1000_v3");
   Name.push_back("HLT_PASinglePhoton10_Eta3p1_PAL3Mu3_v3");
   Name.push_back("HLT_PASinglePhoton10_Eta3p1_PAL3Mu5_v3");
   Name.push_back("HLT_PASinglePhoton15_Eta3p1_PAL3Mu3_v3");
   Name.push_back("HLT_PASinglePhoton15_Eta3p1_PAL3Mu5_v3");
   Name.push_back("HLT_PASinglePhoton20_Eta3p1_PAL3Mu3_v3");
   Name.push_back("HLT_PASinglePhoton20_Eta3p1_PAL3Mu5_v3");

   // PP Reference Runs - v4
   Name.push_back("HLT_AK4PFJet30_v15");
   Name.push_back("HLT_AK4PFJet50_v15");
   Name.push_back("HLT_AK4PFJet80_v15");
   Name.push_back("HLT_AK4PFJet100_v15");
   Name.push_back("HLT_AK4PFJet120_v14");

   Name.push_back("HLT_AK4CaloJet30_v10");
   Name.push_back("HLT_AK4CaloJet40_v9");
   Name.push_back("HLT_AK4CaloJet50_v9");
   Name.push_back("HLT_AK4CaloJet80_v9");
   Name.push_back("HLT_AK4CaloJet100_v9");
   Name.push_back("HLT_AK4CaloJet120_v8");

   Name.push_back("HLT_L1SingleJet16_Eta5p1_v1");
   Name.push_back("HLT_L1SingleJet20_Eta5p1_v1");
   Name.push_back("HLT_L1SingleJet28_Eta5p1_v1");
   Name.push_back("HLT_L1SingleJet40_Eta5p1_v1");
   Name.push_back("HLT_L1SingleJet60_Eta5p1_v1");

   // pp reference runs - v6
   Name.push_back("HLT_L1SingleJet20FWD");
   Name.push_back("HLT_L1SingleJet35FWD");
   Name.push_back("HLT_L1SingleJet40FWD");
   Name.push_back("HLT_L1SingleJet50FWD");
   Name.push_back("HLT_L1SingleJet60FWD");
   
   Name.push_back("HLT_AK4PFJet30FWD_v14");
   Name.push_back("HLT_AK4PFJet50FWD_v14");
   Name.push_back("HLT_AK4PFJet60FWD_v14");
   Name.push_back("HLT_AK4PFJet70FWD_v14");
   Name.push_back("HLT_AK4PFJet80FWD_v14");

   std::sort(Name.begin(), Name.end());
   std::vector<std::string>::iterator iter = std::unique(Name.begin(), Name.end());
   Name.erase(iter, Name.end());
   Decision.resize(Name.size());
   Prescale.resize(Name.size());
   Exist.resize(Name.size());
   PrescaleExist.resize(Name.size());
}

int TriggerTreeMessenger::FindIndex(std::string Trigger)
{
   std::vector<std::string>::iterator iter
      = std::lower_bound(Name.begin(), Name.end(), Trigger);

   if(iter == Name.end())
      return -1;
   if(Trigger == *iter)
      return (iter - Name.begin());
   return -1;
}

int TriggerTreeMessenger::CheckTrigger(std::string Trigger)
{
   return CheckTrigger(FindIndex(Trigger));
}
   
int TriggerTreeMessenger::CheckTriggerStartWith(std::string Trigger)
{
   bool Found = false;
   int Result = 0;

   for(int i = 0; i < (int)Name.size(); i++)
   {
      if(Exist[i] == false || Name[i].find(Trigger) != 0)
         continue;

      Found = true;
      Result = Result + CheckTrigger(i);
   }

   if(Found == true)
      return Result;
   return -1;
}
   
int TriggerTreeMessenger::CheckTrigger(int Index)
{
   if(Index < 0 || Index >= (int)Name.size())
      return -1;
   if(Exist[Index] == false)
      return -1;

   return Decision[Index];
}

int TriggerTreeMessenger::GetPrescale(std::string Trigger)
{
   return GetPrescale(FindIndex(Trigger));
}
   
int TriggerTreeMessenger::GetPrescaleStartWith(std::string Trigger)
{
   for(int i = 0; i < (int)Name.size(); i++)
   {
      if(Exist[i] == false || Name[i].find(Trigger) != 0)
         continue;
      return GetPrescale(i);
   }

   return -1;
}

int TriggerTreeMessenger::GetPrescale(int Index)
{
   if(Index < 0 || Index >= (int)Name.size())
      return -1;
   if(Exist[Index] == false)
      return -1;
   if(PrescaleExist[Index] == false)
      return 1;

   return Prescale[Index];
}

TriggerObjectTreeMessenger::TriggerObjectTreeMessenger(TFile &File, std::string TreeName)
{
   Tree = (TTree *)File.Get(TreeName.c_str());
   Initialize();
}

TriggerObjectTreeMessenger::TriggerObjectTreeMessenger(TFile *File, std::string TreeName)
{
   if(File != nullptr)
      Tree = (TTree *)File->Get(TreeName.c_str());
   else
      Tree = nullptr;
   Initialize();
}

TriggerObjectTreeMessenger::TriggerObjectTreeMessenger(TTree *TriggerTree)
{
   Initialize(TriggerTree);
}

bool TriggerObjectTreeMessenger::Initialize(TTree *TriggerTree)
{
   Tree = TriggerTree;
   return Initialize();
}

bool TriggerObjectTreeMessenger::Initialize()
{
   ID = nullptr;
   PT = nullptr;
   Eta = nullptr;
   Phi = nullptr;
   Mass = nullptr;

   if(Tree == nullptr)
      return false;

   Tree->SetBranchAddress("TriggerObjID", &ID);
   Tree->SetBranchAddress("pt", &PT);
   Tree->SetBranchAddress("eta", &Eta);
   Tree->SetBranchAddress("phi", &Phi);
   Tree->SetBranchAddress("mass", &Mass);

   return true;
}

bool TriggerObjectTreeMessenger::GetEntry(int iEntry)
{
   if(Tree == nullptr)
      return false;

   Tree->GetEntry(iEntry);

   return true;
}

TrackTreeMessenger::TrackTreeMessenger(TFile &File, std::string TreeName)
{
   Tree = (TTree *)File.Get(TreeName.c_str());
   Initialize();
}

TrackTreeMessenger::TrackTreeMessenger(TFile *File, std::string TreeName)
{
   if(File != nullptr)
      Tree = (TTree *)File->Get(TreeName.c_str());
   else
      Tree = nullptr;
   Initialize();
}

TrackTreeMessenger::TrackTreeMessenger(TTree *TrackTree)
{
   Initialize(TrackTree);
}

bool TrackTreeMessenger::Initialize(TTree *TrackTree)
{
   Tree = TrackTree;
   return Initialize();
}

bool TrackTreeMessenger::Initialize()
{
   nVtx = 0;

   if(Tree == nullptr)
      return false;

   Tree->SetBranchAddress("nVtx", &nVtx);
   Tree->SetBranchAddress("nTrkVtx", &nTrkVtx);
   Tree->SetBranchAddress("normChi2Vtx", &normChi2Vtx);
   Tree->SetBranchAddress("sumPtVtx", &sumPtVtx);
   Tree->SetBranchAddress("xVtx", &xVtx);
   Tree->SetBranchAddress("yVtx", &yVtx);
   Tree->SetBranchAddress("zVtx", &zVtx);
   Tree->SetBranchAddress("xVtxErr", &xVtxErr);
   Tree->SetBranchAddress("yVtxErr", &yVtxErr);
   Tree->SetBranchAddress("zVtxErr", &zVtxErr);
   Tree->SetBranchAddress("vtxDist2D", &vtxDist2D);
   Tree->SetBranchAddress("vtxDist2DErr", &vtxDist2DErr);
   Tree->SetBranchAddress("vtxDist2DSig", &vtxDist2DSig);
   Tree->SetBranchAddress("vtxDist3D", &vtxDist3D);
   Tree->SetBranchAddress("vtxDist3DErr", &vtxDist3DErr);
   Tree->SetBranchAddress("vtxDist3DSig", &vtxDist3DSig);

   return true;
}

bool TrackTreeMessenger::GetEntry(int iEntry)
{
   if(Tree == nullptr)
      return false;

   nVtx = 0;
   Tree->GetEntry(iEntry);

   return true;
}

int TrackTreeMessenger::GetBestVertexIndex()
{
   if(nVtx == 0)
      return -1;
   if(nVtx == 1)
      return 0;

   int BestIndex = 0;
   double BestSumPT = 0;
   for(int iV = 0; iV < nVtx; iV++)
   {
      if(BestSumPT < sumPtVtx[iV])
      {
         BestIndex = iV;
         BestSumPT = sumPtVtx[iV];
      }
   }

   return BestIndex;
}

MuTreeMessenger::MuTreeMessenger(TFile &File, std::string TreeName)
{
   Tree = (TTree *)File.Get(TreeName.c_str());
   Initialize();
}

MuTreeMessenger::MuTreeMessenger(TFile *File, std::string TreeName)
{
   if(File != nullptr)
      Tree = (TTree *)File->Get(TreeName.c_str());
   else
      Tree = nullptr;
   Initialize();
}

MuTreeMessenger::MuTreeMessenger(TTree *MuTree)
{
   Initialize(MuTree);
}
   
bool MuTreeMessenger::Initialize(TTree *MuTree)
{
   Tree = MuTree;
   return Initialize();
}

bool MuTreeMessenger::Initialize()
{
   if(Tree == nullptr)
      return false;

   Tree->SetBranchAddress("Run", &Run);
   Tree->SetBranchAddress("Event", &Event);
   Tree->SetBranchAddress("Lumi", &Lumi);
   Tree->SetBranchAddress("vx", &Vx);
   Tree->SetBranchAddress("vy", &Vy);
   Tree->SetBranchAddress("vz", &Vz);
   Tree->SetBranchAddress("Gen_nptl", &NGen);
   Tree->SetBranchAddress("Gen_pid", &GenPID);
   Tree->SetBranchAddress("Gen_mom", &GenMom);
   Tree->SetBranchAddress("Gen_status", &GenStatus);
   Tree->SetBranchAddress("Gen_p", &GenP);
   Tree->SetBranchAddress("Gen_pT", &GenPT);
   Tree->SetBranchAddress("Gen_eta", &GenEta);
   Tree->SetBranchAddress("Gen_phi", &GenPhi);
   Tree->SetBranchAddress("Glb_nptl", &NGlb);
   Tree->SetBranchAddress("Glb_charge", &GlbCharge);
   Tree->SetBranchAddress("Glb_p", &GlbP);
   Tree->SetBranchAddress("Glb_pt", &GlbPT);
   Tree->SetBranchAddress("Glb_eta", &GlbEta);
   Tree->SetBranchAddress("Glb_phi", &GlbPhi);
   Tree->SetBranchAddress("Glb_dxy", &GlbDxy);
   Tree->SetBranchAddress("Glb_dz", &GlbDz);
   Tree->SetBranchAddress("Glb_nValMuHits", &GlbNValMuHits);
   Tree->SetBranchAddress("Glb_nValTrkHits", &GlbNValTrkHits);
   Tree->SetBranchAddress("Glb_nValPixHits", &GlbNValPixHits);
   Tree->SetBranchAddress("Glb_trkLayerWMeas", &GlbTrkLayerWMeas);
   Tree->SetBranchAddress("Glb_nMatchedStations", &GlbNMatchedStations);
   Tree->SetBranchAddress("Glb_nTrkFound", &GlbNTrkFound);
   Tree->SetBranchAddress("Glb_glbChi2NDof", &GlbGlbChi2NDof);
   Tree->SetBranchAddress("Glb_trkChi2NDof", &GlbTrkChi2NDof);
   Tree->SetBranchAddress("Glb_pixLayerWMeas", &GlbPixLayerWMeas);
   Tree->SetBranchAddress("Glb_trkDxy", &GlbTrkDxy);
   Tree->SetBranchAddress("Glb_trkDz", &GlbTrkDz);
   Tree->SetBranchAddress("Sta_nptl", &NSta);
   Tree->SetBranchAddress("Sta_charge", &StaCharge);
   Tree->SetBranchAddress("Sta_p", &StaP);
   Tree->SetBranchAddress("Sta_pt", &StaPT);
   Tree->SetBranchAddress("Sta_eta", &StaEta);
   Tree->SetBranchAddress("Sta_phi", &StaPhi);
   Tree->SetBranchAddress("Sta_dxy", &StaDxy);
   Tree->SetBranchAddress("Sta_dz", &StaDz);
   Tree->SetBranchAddress("Glb_isArbitrated", &GlbIsArbitrated);
   Tree->SetBranchAddress("Di_npair", &NDi);
   Tree->SetBranchAddress("Di_vProb", &DiVProb);
   Tree->SetBranchAddress("Di_mass", &DiMass);
   Tree->SetBranchAddress("Di_e", &DiE);
   Tree->SetBranchAddress("Di_pt", &DiPT);
   Tree->SetBranchAddress("Di_pt1", &DiPT1);
   Tree->SetBranchAddress("Di_pt2", &DiPT2);
   Tree->SetBranchAddress("Di_eta", &DiEta);
   Tree->SetBranchAddress("Di_eta1", &DiEta1);
   Tree->SetBranchAddress("Di_eta2", &DiEta2);
   Tree->SetBranchAddress("Di_rapidity", &DiRapidity);
   Tree->SetBranchAddress("Di_phi", &DiPhi);
   Tree->SetBranchAddress("Di_phi1", &DiPhi1);
   Tree->SetBranchAddress("Di_phi2", &DiPhi2);
   Tree->SetBranchAddress("Di_charge", &DiCharge);
   Tree->SetBranchAddress("Di_charge1", &DiCharge1);
   Tree->SetBranchAddress("Di_charge2", &DiCharge2);
   Tree->SetBranchAddress("Di_isArb1", &DiIsArb1);
   Tree->SetBranchAddress("Di_isArb2", &DiIsArb2);
   Tree->SetBranchAddress("Di_nTrkHit1", &DiNTrkHit1);
   Tree->SetBranchAddress("Di_nTrkHit2", &DiNTrkHit2);
   Tree->SetBranchAddress("Di_nMuHit1", &DiNMuHit1);
   Tree->SetBranchAddress("Di_nMuHit2", &DiNMuHit2);
   Tree->SetBranchAddress("Di_nTrkLayers1", &DiNTrkLayers1);
   Tree->SetBranchAddress("Di_nTrkLayers2", &DiNTrkLayers2);
   Tree->SetBranchAddress("Di_nPixHit1", &DiNPixHit1);
   Tree->SetBranchAddress("Di_nPixHit2", &DiNPixHit2);
   Tree->SetBranchAddress("Di_nMatchedStations1", &DiNMatchedStations1);
   Tree->SetBranchAddress("Di_nMatchedStations2", &DiNMatchedStations2);
   Tree->SetBranchAddress("Di_trkChi2_1", &DiTrkChi21);
   Tree->SetBranchAddress("Di_trkChi2_2", &DiTrkChi22);
   Tree->SetBranchAddress("Di_glbChi2_1", &DiGlbChi21);
   Tree->SetBranchAddress("Di_glbChi2_2", &DiGlbChi22);
   Tree->SetBranchAddress("Di_dxy1", &DiDxy1);
   Tree->SetBranchAddress("Di_dxy2", &DiDxy2);
   Tree->SetBranchAddress("Di_dz1", &DiDz1);
   Tree->SetBranchAddress("Di_dz2", &DiDz2);
   
   return true;
}

bool MuTreeMessenger::GetEntry(int iEntry)
{
   if(Tree == nullptr)
      return false;

   Tree->GetEntry(iEntry);
   return true;
}

PbPbTrackTreeMessenger::PbPbTrackTreeMessenger(TFile &File, std::string TreeName)
{
   Tree = (TTree *)File.Get(TreeName.c_str());
   Initialize();
}

PbPbTrackTreeMessenger::PbPbTrackTreeMessenger(TFile *File, std::string TreeName)
{
   if(File != nullptr)
      Tree = (TTree *)File->Get(TreeName.c_str());
   else
      Tree = nullptr;
   Initialize();
}

PbPbTrackTreeMessenger::PbPbTrackTreeMessenger(TTree *PbPbTrackTree)
{
   Initialize(PbPbTrackTree);
}
   
bool PbPbTrackTreeMessenger::Initialize(TTree *PbPbTrackTree)
{
   Tree = PbPbTrackTree;
   return Initialize();
}

bool PbPbTrackTreeMessenger::Initialize()
{
   if(Tree == nullptr)
      return false;

   VX = nullptr;
   VY = nullptr;
   VZ = nullptr;
   VXError = nullptr;
   VYError = nullptr;
   VZError = nullptr;
   VChi2 = nullptr;
   VNDof = nullptr;
   VIsFake = nullptr;
   VNTracks = nullptr;
   VPTSum = nullptr;
   TrackPT = nullptr;
   TrackPTError = nullptr;
   TrackEta = nullptr;
   TrackPhi = nullptr;
   TrackCharge = nullptr;
   TrackPDFID = nullptr;
   TrackNHits = nullptr;
   TrackNPixHits = nullptr;
   TrackNLayers = nullptr;
   TrackNormChi2 = nullptr;
   TrackHighPurity = nullptr;
   TrackAssociatedVertexIndex = nullptr;
   TrackAssociatedVertexQuality = nullptr;
   TrackAssociatedVertexDz = nullptr;
   TrackAssociatedVertexDzError = nullptr;
   TrackAssociatedVertexDxy = nullptr;
   TrackAssociatedVertexDxyError = nullptr;
   TrackFirstVertexQuality = nullptr;
   TrackFirstVertexDz = nullptr;
   TrackFirstVertexDzError = nullptr;
   TrackFirstVertexDxy = nullptr;
   TrackFirstVertexDxyError = nullptr;   

   Tree->SetBranchAddress("Run", &Run);
   Tree->SetBranchAddress("Event", &Event);
   Tree->SetBranchAddress("Lumi", &Lumi);
   Tree->SetBranchAddress("VX", &VX);
   Tree->SetBranchAddress("VY", &VY);
   Tree->SetBranchAddress("VZ", &VZ);
   Tree->SetBranchAddress("VXError", &VXError);
   Tree->SetBranchAddress("VYError", &VYError);
   Tree->SetBranchAddress("VZError", &VZError);
   Tree->SetBranchAddress("VChi2", &VChi2);
   Tree->SetBranchAddress("VNDof", &VNDof);
   Tree->SetBranchAddress("VIsFake", &VIsFake);
   Tree->SetBranchAddress("VNTracks", &VNTracks);
   Tree->SetBranchAddress("VPTSum", &VPTSum);
   Tree->SetBranchAddress("TrackPT", &TrackPT);
   Tree->SetBranchAddress("TrackPTError", &TrackPTError);
   Tree->SetBranchAddress("TrackEta", &TrackEta);
   Tree->SetBranchAddress("TrackPhi", &TrackPhi);
   Tree->SetBranchAddress("TrackCharge", &TrackCharge);
   Tree->SetBranchAddress("TrackPDFID", &TrackPDFID);
   Tree->SetBranchAddress("TrackNHits", &TrackNHits);
   Tree->SetBranchAddress("TrackNPixHits", &TrackNPixHits);
   Tree->SetBranchAddress("TrackNLayers", &TrackNLayers);
   Tree->SetBranchAddress("TrackNormChi2", &TrackNormChi2);
   Tree->SetBranchAddress("TrackHighPurity", &TrackHighPurity);
   Tree->SetBranchAddress("TrackAssociatedVertexIndex", &TrackAssociatedVertexIndex);
   Tree->SetBranchAddress("TrackAssociatedVertexQuality", &TrackAssociatedVertexQuality);
   Tree->SetBranchAddress("TrackAssociatedVertexDz", &TrackAssociatedVertexDz);
   Tree->SetBranchAddress("TrackAssociatedVertexDzError", &TrackAssociatedVertexDzError);
   Tree->SetBranchAddress("TrackAssociatedVertexDxy", &TrackAssociatedVertexDxy);
   Tree->SetBranchAddress("TrackAssociatedVertexDxyError", &TrackAssociatedVertexDxyError);
   Tree->SetBranchAddress("TrackFirstVertexQuality", &TrackFirstVertexQuality);
   Tree->SetBranchAddress("TrackFirstVertexDz", &TrackFirstVertexDz);
   Tree->SetBranchAddress("TrackFirstVertexDzError", &TrackFirstVertexDzError);
   Tree->SetBranchAddress("TrackFirstVertexDxy", &TrackFirstVertexDxy);
   Tree->SetBranchAddress("TrackFirstVertexDxyError", &TrackFirstVertexDxyError);

   return true;
}

bool PbPbTrackTreeMessenger::GetEntry(int iEntry)
{
   if(Tree == nullptr)
      return false;

   Tree->GetEntry(iEntry);
   return true;
}

ZHadronMessenger::ZHadronMessenger(TFile &File, std::string TreeName)
{
   Initialized = false;
   WriteMode = false;
   
   Tree = (TTree *)File.Get(TreeName.c_str());
   Initialize();
}

ZHadronMessenger::ZHadronMessenger(TFile *File, std::string TreeName)
{
   Initialized = false;
   WriteMode = false;
   
   if(File != nullptr)
      Tree = (TTree *)File->Get(TreeName.c_str());
   else
      Tree = nullptr;
   Initialize();
}

ZHadronMessenger::ZHadronMessenger(TTree *ZHadronTree)
{
   Initialized = false;
   WriteMode = false;

   Initialize(ZHadronTree);
}
   
bool ZHadronMessenger::Initialize(TTree *ZHadronTree)
{
   Tree = ZHadronTree;
   return Initialize();
}

bool ZHadronMessenger::Initialize()
{
   if(Tree == nullptr)
      return false;

   Initialized = true;

   int Run;
   int Event;
   int Lumi;
   
   int hiBin;
   float hiHF;
   
   zMass = nullptr;
   zEta = nullptr;
   zPhi = nullptr;
   zPt = nullptr;
   genZMass = nullptr;
   genZEta = nullptr;
   genZPhi = nullptr;
   genZPt = nullptr;
   trackDphi = nullptr;
   trackPt = nullptr;
   trackDeta = nullptr;
   trackPDFId = nullptr;
   trackEta = nullptr;
   trackPhi = nullptr;

   muEta1 = nullptr;
   muEta2 = nullptr;
   muPhi1 = nullptr;
   muPhi2 = nullptr;
   muPt1 = nullptr;
   muPt2 = nullptr;

   muDeta = nullptr;
   muDphi = nullptr;
   muDR = nullptr;
   muDphiS = nullptr;

   genMuPt1 = nullptr;
   genMuPt2 = nullptr;
   genMuEta1 = nullptr;
   genMuEta2 = nullptr;
   genMuPhi1 = nullptr;
   genMuPhi2 = nullptr;

   genMuDeta = nullptr;
   genMuDphi = nullptr;
   genMuDR = nullptr;
   genMuDphiS = nullptr;

   Tree->SetBranchAddress("Run", &Run);
   Tree->SetBranchAddress("Event", &Event);
   Tree->SetBranchAddress("Lumi", &Lumi);

   Tree->SetBranchAddress("hiBin", &hiBin);
   Tree->SetBranchAddress("hiHF", &hiHF);
   
   Tree->SetBranchAddress("zMass", zMass);
   Tree->SetBranchAddress("zEta", zEta);
   Tree->SetBranchAddress("zPhi", zPhi);
   Tree->SetBranchAddress("zPt", zPt);
   Tree->SetBranchAddress("genZMass", genZMass);
   Tree->SetBranchAddress("genZEta", genZEta);
   Tree->SetBranchAddress("genZPhi", genZPhi);
   Tree->SetBranchAddress("genZPt", genZPt);
   Tree->SetBranchAddress("trackDphi", trackDphi);
   Tree->SetBranchAddress("trackPt", trackPt);
   Tree->SetBranchAddress("trackDeta", trackDeta);
   Tree->SetBranchAddress("trackPDFId", trackPDFId);
   Tree->SetBranchAddress("trackEta", trackEta);
   Tree->SetBranchAddress("trackPhi", trackPhi);

   Tree->SetBranchAddress("muEta1", muEta1);
   Tree->SetBranchAddress("muEta2", muEta2);
   Tree->SetBranchAddress("muPhi1", muPhi1);
   Tree->SetBranchAddress("muPhi2", muPhi2);
   Tree->SetBranchAddress("muPt1", muPt1);
   Tree->SetBranchAddress("muPt2", muPt2);
 
   Tree->SetBranchAddress("muDeta", muDeta);
   Tree->SetBranchAddress("muDphi", muDphi);
   Tree->SetBranchAddress("muDR", muDR);
   Tree->SetBranchAddress("muDphiS", muDphiS);
  
   Tree->SetBranchAddress("genMuPt1", genMuPt1);
   Tree->SetBranchAddress("genMuPt2", genMuPt2);
   Tree->SetBranchAddress("genMuEta1", genMuEta1);
   Tree->SetBranchAddress("genMuEta2", genMuEta2);
   Tree->SetBranchAddress("genMuPhi1", genMuPhi1);
   Tree->SetBranchAddress("genMuPhi2", genMuPhi2);
   
   Tree->SetBranchAddress("genMuDeta", genMuDeta);
   Tree->SetBranchAddress("genMuDphi", genMuDphi);
   Tree->SetBranchAddress("genMuDR", genMuDR);
   Tree->SetBranchAddress("genMuDphiS", genMuDphiS);
   
   return true;
}

bool ZHadronMessenger::GetEntry(int iEntry)
{
   if(Tree == nullptr)
      return false;

   Tree->GetEntry(iEntry);
   return true;
}

bool ZHadronMessenger::SetBranch(TTree *T)
{
   if(T == nullptr)
      return false;

   Initialized = true;
   WriteMode = true;

   zMass = new std::vector<double>();
   zEta = new std::vector<double>();
   zPhi = new std::vector<double>();
   zPt = new std::vector<double>();
   genZMass = new std::vector<double>();
   genZEta = new std::vector<double>();
   genZPhi = new std::vector<double>();
   genZPt = new std::vector<double>();
   trackDphi = new std::vector<double>();
   trackPt = new std::vector<double>();
   trackDeta = new std::vector<double>();
   trackPDFId = new std::vector<double>();
   trackEta = new std::vector<double>();
   trackPhi = new std::vector<double>();

   muEta1 = new std::vector<double>();
   muEta2 = new std::vector<double>();
   muPhi1 = new std::vector<double>();
   muPhi2 = new std::vector<double>();
   muPt1 = new std::vector<double>();
   muPt2 = new std::vector<double>();

   muDeta = new std::vector<double>();
   muDphi = new std::vector<double>();
   muDR = new std::vector<double>();
   muDphiS = new std::vector<double>();

   genMuPt1 = new std::vector<double>();
   genMuPt2 = new std::vector<double>();
   genMuEta1 = new std::vector<double>();
   genMuEta2 = new std::vector<double>();
   genMuPhi1 = new std::vector<double>();
   genMuPhi2 = new std::vector<double>();

   genMuDeta = new std::vector<double>();
   genMuDphi = new std::vector<double>();
   genMuDR = new std::vector<double>();
   genMuDphiS = new std::vector<double>();

   Tree = T;

   Tree->Branch("zMass",      &zMass);
   Tree->Branch("zEta",       &zEta);
   Tree->Branch("zPhi",       &zPhi);
   Tree->Branch("zPt",        &zPt);
   Tree->Branch("genZMass",   &genZMass);
   Tree->Branch("genZEta",    &genZEta);
   Tree->Branch("genZPhi",    &genZPhi);
   Tree->Branch("genZPt",     &genZPt);
   Tree->Branch("trackDphi",  &trackDphi);
   Tree->Branch("trackDeta",  &trackDeta);
   Tree->Branch("trackPt",    &trackPt);
   Tree->Branch("trackPDFId", &trackPDFId);
   Tree->Branch("trackPhi",   &trackPhi);
   Tree->Branch("trackEta",   &trackEta);
   Tree->Branch("hiBin",      &hiBin);
   Tree->Branch("hiHF",       &hiHF);

   Tree->Branch("muEta1",     &muEta1);
   Tree->Branch("muEta2",     &muEta2);
   Tree->Branch("muPhi1",     &muPhi1);
   Tree->Branch("muPhi2",     &muPhi2);
   Tree->Branch("muPt1",      &muPt1);
   Tree->Branch("muPt2",      &muPt2);

   Tree->Branch("genMuPt1",   &genMuPt1);
   Tree->Branch("genMuPt2",   &genMuPt2);
   Tree->Branch("genMuEta1",  &genMuEta1);
   Tree->Branch("genMuEta2",  &genMuEta2);
   Tree->Branch("genMuPhi1",  &genMuPhi1);
   Tree->Branch("genMuPhi2",  &genMuPhi2);

   Tree->Branch("muDeta",     &muDeta);
   Tree->Branch("muDphi",     &muDphi);
   Tree->Branch("muDR",       &muDR);
   Tree->Branch("muDphiS",    &muDphiS);

   Tree->Branch("genMuDeta",  &genMuDeta);
   Tree->Branch("genMuDphi",  &genMuDphi);
   Tree->Branch("genMuDR",    &genMuDR);
   Tree->Branch("genMuDphiS", &genMuDphiS);

   return true;
}
   
void ZHadronMessenger::Clear()
{
   if(Initialized == false)
      return;

   zMass->clear();
   zEta->clear();
   zPhi->clear();
   zPt->clear();
   genZMass->clear();
   genZEta->clear();
   genZPhi->clear();
   genZPt->clear();
   trackDphi->clear();
   trackPt->clear();
   trackDeta->clear();
   trackPDFId->clear();
   trackPhi->clear();
   trackEta->clear();

   muEta1->clear();
   muEta2->clear();
   muPhi1->clear();
   muPhi2->clear();
   muPt1->clear();
   muPt2->clear();

   genMuPt1->clear();
   genMuPt2->clear();
   genMuEta1->clear();
   genMuEta2->clear();
   genMuPhi1->clear();
   genMuPhi2->clear();

   muDeta->clear();
   muDphi->clear();
   muDR->clear();
   muDphiS->clear();
   genMuDeta->clear();
   genMuDphi->clear();
   genMuDR->clear();
   genMuDphiS->clear();
}

bool ZHadronMessenger::FillEntry()
{
   if(Initialized == false)
      return false;
   if(WriteMode == false)
      return false;

   if(Tree == nullptr)
      return false;

   Tree->Fill();
   Clear();

   return true;
}