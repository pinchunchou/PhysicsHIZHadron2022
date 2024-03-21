#include <iostream>
#include <vector>

#include "TTree.h"
#include "TFile.h"

#define JETCOUNTMAX 500
#define GENCOUNTMAX 250
#define VERTEXCOUNTMAX 200
#define TRACKCOUNTMAX 10000
#define PLANEMAX 200
#define MUMAX 50

class HiEventTreeMessenger;
class GGTreeMessenger;
class RhoTreeMessenger;
class SkimTreeMessenger;
class JetTreeMessenger;
class GenParticleTreeMessenger;
class PFTreeMessenger;
class TriggerTreeMessenger;
class TriggerObjectTreeMessenger;
class TrackTreeMessenger;
class MuTreeMessenger;
class PbPbTrackTreeMessenger;
class ZHadronMessenger;

class HiEventTreeMessenger
{
public:
   TTree *Tree;
   float hiHF;
   int hiBin;
   unsigned int Run;
   unsigned long long Event;
   unsigned int Lumi;
   float vx;
   float vy;
   float vz;
   float weight;
   std::vector<int> *npus;
   std::vector<float> *tnpus;
   float hiHFplus;
   float hiHFminus;
   float hiHFplusEta4;
   float hiHFminusEta4;
   int hiNevtPlane;
   float hiEvtPlanes[PLANEMAX];
public:
   HiEventTreeMessenger(TFile &File);
   HiEventTreeMessenger(TFile *File);
   HiEventTreeMessenger(TTree *HiEventTree);
   bool Initialize(TTree *HiEventTree);
   bool Initialize();
   bool GetEntry(int iEntry);
   int GetEntries();
};

class GGTreeMessenger
{
public:
   TTree *Tree;
   int NPUInfo;
   std::vector<int> *PUCount;
   std::vector<int> *PUBX;
   std::vector<float> *PUTrue;
   int PFJetCount;
   std::vector<float> *PFJetPT;
   std::vector<float> *PFJetEta;
   std::vector<float> *PFJetPhi;
   int CaloJetCount;
   std::vector<float> *CaloJetPT;
   std::vector<float> *CaloJetEta;
   std::vector<float> *CaloJetPhi;
   int GenJetCount;
   std::vector<float> *GenJetPT;
   std::vector<float> *GenJetEta;
   std::vector<float> *GenJetPhi;
public:
   GGTreeMessenger(TFile &File, std::string TreeName = "ggHiNtuplizer/EventTree");
   GGTreeMessenger(TFile *File, std::string TreeName = "ggHiNtuplizer/EventTree");
   GGTreeMessenger(TTree *EventTree);
   bool Initialize(TTree *EventTree);
   bool Initialize();
   bool GetEntry(int iEntry);
};

class RhoTreeMessenger
{
public:
   TTree *Tree;
   std::vector<double> *EtaMin;
   std::vector<double> *EtaMax;
   std::vector<double> *Rho;
   std::vector<double> *RhoM;
public:
   RhoTreeMessenger(TFile &File, std::string TreeName = "hiFJRhoAnalyzer/t");
   RhoTreeMessenger(TFile *File, std::string TreeName = "hiFJRhoAnalyzer/t");
   RhoTreeMessenger(TTree *RhoTree);
   bool Initialize(TTree *RhoTree);
   bool Initialize();
   bool GetEntry(int iEntry);
};

class SkimTreeMessenger
{
public:
   TTree *Tree;
   int HBHENoise;
   int HBHENoiseRun2Loose;
   int PVFilter;
   int ClusterCompatibilityFilter;
   int BeamScrapingFilter;
   int HFCoincidenceFilter;
   int HFCoincidenceFilter2Th4;
   int CollisionEventSelection;
public:
   SkimTreeMessenger(TFile &File);
   SkimTreeMessenger(TFile *File);
   SkimTreeMessenger(TTree *SkimTree);
   bool Initialize(TTree *SkimTree);
   bool Initialize();
   bool GetEntry(int iEntry);
   bool PassBasicFilter();
   bool PassBasicFilterLoose();
};

class JetTreeMessenger
{
public:
   TTree *Tree;
   float PTHat;
   int JetCount;
   float JetRawPT[JETCOUNTMAX];
   float JetPT[JETCOUNTMAX];
   float JetEta[JETCOUNTMAX];
   float JetY[JETCOUNTMAX];
   float JetPhi[JETCOUNTMAX];
   float JetPU[JETCOUNTMAX];
   float JetM[JETCOUNTMAX];
   float JetTau1[JETCOUNTMAX];
   float JetTau2[JETCOUNTMAX];
   float JetTau3[JETCOUNTMAX];
   float JetArea[JETCOUNTMAX];
   float JetCSVV1[JETCOUNTMAX];
   float JetCSVV2[JETCOUNTMAX];
   float JetCSVV1N[JETCOUNTMAX];
   float JetCSVV2N[JETCOUNTMAX];
   float JetCSVV1P[JETCOUNTMAX];
   float JetCSVV2P[JETCOUNTMAX];
   std::vector<std::vector<float> > *JetSubJetPT;
   std::vector<std::vector<float> > *JetSubJetEta;
   std::vector<std::vector<float> > *JetSubJetPhi;
   std::vector<std::vector<float> > *JetSubJetM;
   float JetSym[JETCOUNTMAX];
   int JetDroppedBranches[JETCOUNTMAX];
   float RefPT[JETCOUNTMAX];
   float RefEta[JETCOUNTMAX];
   float RefY[JETCOUNTMAX];
   float RefPhi[JETCOUNTMAX];
   float RefM[JETCOUNTMAX];
   float RefArea[JETCOUNTMAX];
   float RefGPT[JETCOUNTMAX];
   float RefGEta[JETCOUNTMAX];
   float RefGPhi[JETCOUNTMAX];
   float RefGM[JETCOUNTMAX];
   float RefPartonPT[JETCOUNTMAX];
   int RefPartonFlavor[JETCOUNTMAX];
   int RefPartonFlavorForB[JETCOUNTMAX];
   std::vector<std::vector<float> > *RefGSubJetPT;
   std::vector<std::vector<float> > *RefGSubJetEta;
   std::vector<std::vector<float> > *RefGSubJetPhi;
   std::vector<std::vector<float> > *RefGSubJetM;
   int GenCount;
   int GenMatchIndex[JETCOUNTMAX];
   float GenPT[JETCOUNTMAX];
   float GenEta[JETCOUNTMAX];
   float GenY[JETCOUNTMAX];
   float GenPhi[JETCOUNTMAX];
   float GenM[JETCOUNTMAX];
   float HcalSum[JETCOUNTMAX];
   float EcalSum[JETCOUNTMAX];
   float JetPFCHF[JETCOUNTMAX];
   float JetPFNHF[JETCOUNTMAX];
   float JetPFCEF[JETCOUNTMAX];
   float JetPFNEF[JETCOUNTMAX];
   float JetPFMUF[JETCOUNTMAX];
   int JetPFCHM[JETCOUNTMAX];
   int JetPFNHM[JETCOUNTMAX];
   int JetPFCEM[JETCOUNTMAX];
   int JetPFNEM[JETCOUNTMAX];
   int JetPFMUM[JETCOUNTMAX];
public:
   JetTreeMessenger(TFile &File, std::string TreeName = "akCs4PFJetAnalyzer/t");
   JetTreeMessenger(TFile *File, std::string TreeName = "akCs4PFJetAnalyzer/t");
   JetTreeMessenger(TTree *JetTree);
   bool Initialize(TTree *JetTree);
   bool Initialize();
   bool GetEntry(int iEntry);
};

class GenParticleTreeMessenger
{
public:
   TTree *Tree;
   float NPart;
   float NColl;
   float NHard;
   float Phi0;
   int Mult;
   std::vector<float> *PT;
   std::vector<float> *Eta;
   std::vector<float> *Phi;
   std::vector<int> *ID;
   std::vector<int> *Charge;
   std::vector<int> *DaughterCount;
   std::vector<int> *SubEvent;
public:
   GenParticleTreeMessenger(TFile &File);
   GenParticleTreeMessenger(TFile *File);
   GenParticleTreeMessenger(TTree *GenParticleTree);
   bool Initialize(TTree *GenParticleTree);
   bool Initialize();
   bool GetEntry(int iEntry);
};

class PFTreeMessenger
{
public:
   TTree *Tree;
   std::vector<int> *ID;
   std::vector<float> *PT;
   std::vector<float> *E;
   std::vector<float> *Eta;
   std::vector<float> *Phi;
   std::vector<float> *M;
public:
   PFTreeMessenger(TFile &File, std::string TreeName = "pfcandAnalyzer/pfTree");
   PFTreeMessenger(TFile *File, std::string TreeName = "pfcandAnalyzer/pfTree");
   bool Initialize(TFile &File, std::string TreeName = "pfcandAnalyzer/pfTree");
   bool Initialize(TFile *File, std::string TreeName = "pfcandAnalyzer/pfTree");
   PFTreeMessenger(TTree *PFTree);
   bool Initialize(TTree *PFTree);
   bool Initialize();
   bool GetEntry(int iEntry);
};

class TriggerTreeMessenger
{
public:
   TTree *Tree;
   int Run;
   unsigned long long Event;
   int Lumi;
   std::vector<std::string> Name;
   std::vector<int> Decision;
   std::vector<int> Prescale;
   std::vector<bool> Exist;
   std::vector<bool> PrescaleExist;
public:
   TriggerTreeMessenger(TFile &File, std::string TreeName = "hltanalysis/HltTree");
   TriggerTreeMessenger(TFile *File, std::string TreeName = "hltanalysis/HltTree");
   TriggerTreeMessenger(TTree *TriggerTree);
   bool Initialize(TTree *TriggerTree);
   bool Initialize();
   bool GetEntry(int iEntry);
   void FillTriggerNames();
   int FindIndex(std::string Trigger);
   int CheckTrigger(std::string Trigger);
   int CheckTriggerStartWith(std::string Trigger);
   int CheckTrigger(int Index);
   int GetPrescale(std::string Trigger);
   int GetPrescaleStartWith(std::string Trigger);
   int GetPrescale(int Index);
};

class TriggerObjectTreeMessenger
{
public:
   TTree *Tree;
   std::vector<double> *ID;
   std::vector<double> *PT;
   std::vector<double> *Eta;
   std::vector<double> *Phi;
   std::vector<double> *Mass;
public:
   TriggerObjectTreeMessenger(TFile &File, std::string TreeName = "hltobjects/HLT_HIPuAK4CaloJet60_Eta5p1_v");
   TriggerObjectTreeMessenger(TFile *File, std::string TreeName = "hltobjects/HLT_HIPuAK4CaloJet60_Eta5p1_v");
   TriggerObjectTreeMessenger(TTree *TriggerTree);
   bool Initialize(TTree *TriggerTree);
   bool Initialize();
   bool GetEntry(int iEntry);
};

class TrackTreeMessenger
{
public:
   TTree *Tree;
   int nVtx;
   int nTrkVtx[VERTEXCOUNTMAX];
   float normChi2Vtx[VERTEXCOUNTMAX];
   float sumPtVtx[VERTEXCOUNTMAX];
   float xVtx[VERTEXCOUNTMAX];
   float yVtx[VERTEXCOUNTMAX];
   float zVtx[VERTEXCOUNTMAX];
   float xVtxErr[VERTEXCOUNTMAX];
   float yVtxErr[VERTEXCOUNTMAX];
   float zVtxErr[VERTEXCOUNTMAX];
   float vtxDist2D[VERTEXCOUNTMAX];
   float vtxDist2DErr[VERTEXCOUNTMAX];
   float vtxDist2DSig[VERTEXCOUNTMAX];
   float vtxDist3D[VERTEXCOUNTMAX];
   float vtxDist3DErr[VERTEXCOUNTMAX];
   float vtxDist3DSig[VERTEXCOUNTMAX];
   int nTrk;
   float trkPt[TRACKCOUNTMAX];
   float trkPtError[TRACKCOUNTMAX];
   short trkNHit[TRACKCOUNTMAX];
   short trkNlayer[TRACKCOUNTMAX];
   float trkEta[TRACKCOUNTMAX];
   float trkPhi[TRACKCOUNTMAX];
   int trkCharge[TRACKCOUNTMAX];
   short trkNVtx[TRACKCOUNTMAX];
   int nTrkTimesnVtx;
   bool trkAssocVtx[TRACKCOUNTMAX];
   float trkDxyOverDxyError[TRACKCOUNTMAX];
   float trkDzOverDzError[TRACKCOUNTMAX];
   bool highPurity[TRACKCOUNTMAX];
   bool tight[TRACKCOUNTMAX];
   bool loose[TRACKCOUNTMAX];
   float trkChi2[TRACKCOUNTMAX];
   short trkNdof[TRACKCOUNTMAX];
   float trkDxy1[TRACKCOUNTMAX];
   float trkDxyError1[TRACKCOUNTMAX];
   float trkDz1[TRACKCOUNTMAX];
   float trkDzError1[TRACKCOUNTMAX];
   bool trkFake[TRACKCOUNTMAX];
   short trkAlgo[TRACKCOUNTMAX];
   short trkOriginalAlgo[TRACKCOUNTMAX];
public:
   TrackTreeMessenger(TFile &File, std::string TreeName = "ppTrack/trackTree");
   TrackTreeMessenger(TFile *File, std::string TreeName = "ppTrack/trackTree");
   TrackTreeMessenger(TTree *TrackTree);
   bool Initialize(TTree *TrackTree);
   bool Initialize();
   bool GetEntry(int iEntry);
   int GetBestVertexIndex();
   bool PassZHadron2022Cut(int index);
   bool PassZHadron2022CutLoose(int index);
   bool PassZHadron2022CutTight(int index);
};

class MuTreeMessenger
{
public:
   TTree *Tree;
   int Run;
   int Event;
   int Lumi;
   float Vx;
   float Vy;
   float Vz;
   int NGen;
   int GenPID[GENCOUNTMAX];
   int GenMom[GENCOUNTMAX];
   int GenStatus[GENCOUNTMAX];
   float GenP[GENCOUNTMAX];
   float GenPT[GENCOUNTMAX];
   float GenEta[GENCOUNTMAX];
   float GenPhi[GENCOUNTMAX];
   int NGlb;
   int GlbCharge[MUMAX];
   float GlbP[MUMAX];
   float GlbPT[MUMAX];
   float GlbEta[MUMAX];
   float GlbPhi[MUMAX];
   float GlbDxy[MUMAX];
   float GlbDz[MUMAX];
   int GlbNValMuHits[MUMAX];
   int GlbNValTrkHits[MUMAX];
   int GlbNValPixHits[MUMAX];
   int GlbTrkLayerWMeas[MUMAX];
   int GlbNMatchedStations[MUMAX];
   int GlbNTrkFound[MUMAX];
   float GlbGlbChi2NDof[MUMAX];
   float GlbTrkChi2NDof[MUMAX];
   int GlbPixLayerWMeas[MUMAX];
   float GlbTrkDxy[MUMAX];
   float GlbTrkDz[MUMAX];
   int NSta;
   int StaCharge[MUMAX];
   float StaP[MUMAX];
   float StaPT[MUMAX];
   float StaEta[MUMAX];
   float StaPhi[MUMAX];
   float StaDxy[MUMAX];
   float StaDz[MUMAX];
   int GlbIsArbitrated[MUMAX];
   int NDi;
   float DiVProb[MUMAX];
   float DiMass[MUMAX];
   float DiE[MUMAX];
   float DiPT[MUMAX];
   float DiPT1[MUMAX];
   float DiPT2[MUMAX];
   float DiEta[MUMAX];
   float DiEta1[MUMAX];
   float DiEta2[MUMAX];
   float DiRapidity[MUMAX];
   float DiPhi[MUMAX];
   float DiPhi1[MUMAX];
   float DiPhi2[MUMAX];
   int DiCharge[MUMAX];
   int DiCharge1[MUMAX];
   int DiCharge2[MUMAX];
   int DiIsArb1[MUMAX];
   int DiIsArb2[MUMAX];
   int DiNTrkHit1[MUMAX];
   int DiNTrkHit2[MUMAX];
   int DiNMuHit1[MUMAX];
   int DiNMuHit2[MUMAX];
   int DiNTrkLayers1[MUMAX];
   int DiNTrkLayers2[MUMAX];
   int DiNPixHit1[MUMAX];
   int DiNPixHit2[MUMAX];
   int DiNMatchedStations1[MUMAX];
   int DiNMatchedStations2[MUMAX];
   float DiTrkChi21[MUMAX];
   float DiTrkChi22[MUMAX];
   float DiGlbChi21[MUMAX];
   float DiGlbChi22[MUMAX];
   float DiDxy1[MUMAX];
   float DiDxy2[MUMAX];
   float DiDz1[MUMAX];
   float DiDz2[MUMAX];
public:
   MuTreeMessenger(TFile &File, std::string TreeName = "hltMuTree/HLTMuTree");
   MuTreeMessenger(TFile *File, std::string TreeName = "hltMuTree/HLTMuTree");
   MuTreeMessenger(TTree *MuTree);
   bool Initialize(TTree *MuTree);
   bool Initialize();
   bool GetEntry(int iEntry);
   bool DimuonPassTightCut(int index);
};

class PbPbTrackTreeMessenger
{
public:
   TTree *Tree;
   int Run;
   int Event;
   int Lumi;
   std::vector<float> *VX;
   std::vector<float> *VY;
   std::vector<float> *VZ;
   std::vector<float> *VXError;
   std::vector<float> *VYError;
   std::vector<float> *VZError;
   std::vector<float> *VChi2;
   std::vector<float> *VNDof;
   std::vector<bool>  *VIsFake;
   std::vector<int>   *VNTracks;
   std::vector<float> *VPTSum;
   std::vector<float> *TrackPT;
   std::vector<float> *TrackPTError;
   std::vector<float> *TrackEta;
   std::vector<float> *TrackPhi;
   std::vector<char>  *TrackCharge;
   std::vector<int>   *TrackPDGID;
   std::vector<char>  *TrackNHits;
   std::vector<char>  *TrackNPixHits;
   std::vector<char>  *TrackNLayers;
   std::vector<float> *TrackNormChi2;
   std::vector<bool>  *TrackHighPurity;
   std::vector<float> *PFEnergy;
   std::vector<float> *PFEcal;
   std::vector<float> *PFHcal;
   std::vector<int>   *TrackAssociatedVertexIndex;
   std::vector<int>   *TrackAssociatedVertexQuality;
   std::vector<float> *TrackAssociatedVertexDz;
   std::vector<float> *TrackAssociatedVertexDzError;
   std::vector<float> *TrackAssociatedVertexDxy;
   std::vector<float> *TrackAssociatedVertexDxyError;
   std::vector<int>   *TrackFirstVertexQuality;
   std::vector<float> *TrackFirstVertexDz;
   std::vector<float> *TrackFirstVertexDzError;
   std::vector<float> *TrackFirstVertexDxy;
   std::vector<float> *TrackFirstVertexDxyError;
public:
   PbPbTrackTreeMessenger(TFile &File, std::string TreeName = "PbPbTracks/trackTree");
   PbPbTrackTreeMessenger(TFile *File, std::string TreeName = "PbPbTracks/trackTree");
   PbPbTrackTreeMessenger(TTree *PbPbTrackTree);
   bool Initialize(TTree *PbPbTrackTree);
   bool Initialize();
   bool GetEntry(int iEntry);
   bool PassZHadron2022Cut(int index);
   bool PassZHadron2022CutNoVZ(int index);
   bool PassZHadron2022CutLoose(int index);
   bool PassZHadron2022CutTight(int index);
};

class ZHadronMessenger
{
public:
   TTree *Tree;
   int Run;
   long long Event;
   int Lumi;
   
   int hiBin;
   int hiBinUp;
   int hiBinDown;
   float hiHF;

   float SignalHF;
   float BackgroundHF;
   float SignalVZ;

   float NCollWeight;
   float ZWeight;
   float VZWeight;
   float ExtraZWeight[12];

   int NVertex;
   float VX, VY, VZ, VXError, VYError, VZError;
   int NPU;
   
   std::vector<double> *zMass;
   std::vector<double> *zEta;
   std::vector<double> *zPhi;
   std::vector<double> *zPt;
   std::vector<double> *genZMass;
   std::vector<double> *genZEta;
   std::vector<double> *genZPhi;
   std::vector<double> *genZPt;
   std::vector<double> *trackPt;
   std::vector<double> *trackDeta;
   std::vector<double> *trackDphi;
   std::vector<double> *TrackPDGID;
   std::vector<double> *trackEta;
   std::vector<double> *trackPhi;
   std::vector<bool> *trackMuTagged;
   std::vector<double> *trackMuDR;
   std::vector<double> *trackWeight;
   std::vector<double> *trackResidualWeight;
   std::vector<int> *trackCharge;
   std::vector<int> *subevent;
   
   std::vector<double> *jetPt;
   std::vector<double> *jetDeta;
   std::vector<double> *jetDphi;
   std::vector<double> *jetRefPt;
   std::vector<double> *jetRefDeta;
   std::vector<double> *jetRefDphi;
   std::vector<bool> *jetMuTagged;
   
   std::vector<double> *genJetPt;
   std::vector<double> *genJetEta;
   std::vector<double> *genJetPhi;

   double maxOppositeDEta;
   double maxOppositeDPhi;
   double maxDEta;
   double maxDPhi;
   double maxOppositeWTADEta;
   double maxOppositeWTADPhi;
   double maxMoreOppositeWTADEta;
   double maxMoreOppositeWTADPhi;
   double maxOppositeCSWTADEta;
   double maxOppositeCSWTADPhi;
   double maxOppositeChargedWTADEta;
   double maxOppositeChargedWTADPhi;
   double maxMoreOppositeChargedWTADEta;
   double maxMoreOppositeChargedWTADPhi;
   double maxOppositeHardChargedWTADEta;
   double maxOppositeHardChargedWTADPhi;

   double maxOppositeJet12Pt;
   double maxOppositeJet12DEta;
   double maxOppositeJet12DPhi;
   double maxOppositeJet34Pt;
   double maxOppositeJet34DEta;
   double maxOppositeJet34DPhi;
   double maxOppositeJet56Pt;
   double maxOppositeJet56DEta;
   double maxOppositeJet56DPhi;
   double maxOppositeJet78Pt;
   double maxOppositeJet78DEta;
   double maxOppositeJet78DPhi;

   std::vector<double> *muEta1;
   std::vector<double> *muEta2;
   std::vector<double> *muPhi1;
   std::vector<double> *muPhi2;
   std::vector<double> *muPt1;
   std::vector<double> *muPt2;

   std::vector<double> *muDeta;
   std::vector<double> *muDphi;
   std::vector<double> *muDR;
   std::vector<double> *muDphiS;

   std::vector<double> *genMuPt1;
   std::vector<double> *genMuPt2;
   std::vector<double> *genMuEta1;
   std::vector<double> *genMuEta2;
   std::vector<double> *genMuPhi1;
   std::vector<double> *genMuPhi2;

   std::vector<double> *genMuDeta;
   std::vector<double> *genMuDphi;
   std::vector<double> *genMuDR;
   std::vector<double> *genMuDphiS;

private:
   bool WriteMode;
   bool Initialized;

public:   
   ZHadronMessenger(TFile &File, std::string TreeName = "tree");
   ZHadronMessenger(TFile *File, std::string TreeName = "tree");
   ZHadronMessenger(TTree *ZHadronTree = nullptr);
   ~ZHadronMessenger();
   bool Initialize(TTree *ZHadronTree);
   bool Initialize();
   int GetEntries();
   bool GetEntry(int iEntry);
   bool SetBranch(TTree *T);
   void Clear();
   void CopyNonTrack(ZHadronMessenger &M);
   bool FillEntry();
};

