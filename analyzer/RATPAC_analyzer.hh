#ifndef ANALYZER_h
#define ANALYZER_h

#include <TFile.h>
#include <TH1.h>
#include <TF1.h>
#include <TH2.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TBranch.h>
#include <TLeaf.h>
#include <TF2.h>
#include <TRegexp.h>
#include <TPRegexp.h>
#include <TMath.h>
#include <TLeaf.h>
#include <Rtypes.h>
#include <TROOT.h>
#include <TRandom3.h>
#include <TPad.h>
#include <TVector3.h>
#include <TString.h>
#include <TObject.h>
#include <TChain.h>
#include <THStack.h>
#include <TPad.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TText.h>
#include <TLine.h>
#include <TLegendEntry.h>
#include <TVectorF.h>
#include <TKey.h>
#include <TSpectrum.h>
#include <TVirtualFFT.h>
#include <TMultiGraph.h>

#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <deque>
#include <map>
#include <utility>

// Header file for the classes stored in the TTree if any.
 #include <RAT/DS/Root.hh>
 #include <RAT/DS/MC.hh>
 #include <RAT/DS/Calib.hh>
 #include <RAT/DS/EV.hh>
 #include <RAT/DS/PMT.hh>
 #include <RAT/DSReader.hh>
 #include <RAT/TrackNav.hh>
 #include <RAT/TrackCursor.hh>
 #include <RAT/TrackNode.hh>
 

class Evt {
public:
  ~Evt() {}
  Evt():n(0LL),trig(0.),card(0),chan(0.),pmtid(0.),posx(0.),posy(0.),posz(0.),time(0.),charge(0.), ampli(0.), width(0.),evttime(0.),pulse(0.),boolword(0.) {}
  Evt(Long64_t _n, Int_t _trig, Int_t _card, Int_t _chan, Int_t _pmtid, Int_t _posx, Int_t _posy, Int_t _posz, Int_t _time, Float_t _charge, Float_t _ampli, Float_t _width, Float_t _evttime, std::vector<Float_t> _pulse, std::vector<Bool_t> _boolword):
  n(_n),trig(_trig),card(_card),chan(_chan),pmtid(_pmtid),posx(_posx),posy(_posy),posz(_posz),time(_time),charge(_charge),ampli(_ampli),width(_width),evttime(_evttime),pulse(_pulse),boolword(_boolword) {}
  Evt(const Evt& evt): n(evt.n),trig(evt.trig),card(evt.card),chan(evt.chan),pmtid(evt.pmtid),posx(evt.posx),posy(evt.posy),posz(evt.posz),time(evt.time),charge(evt.charge),ampli(evt.ampli),width(evt.width),evttime(evt.evttime),pulse(evt.pulse),boolword(evt.boolword) {}
  Evt& operator=(const Evt& evt) {
    n = evt.n;
    trig = evt.trig;
    card = evt.card;
    chan = evt.chan;
    pmtid = evt.pmtid;
    posx = evt.posx;
    posy = evt.posy;
    posz = evt.posz;
    time = evt.time;
    charge = evt.charge;
    ampli = evt.ampli;
    width = evt.width;
    evttime = evt.evttime;
    pulse = evt.pulse;
    boolword = evt.boolword;
    return *this;
  }
  Bool_t operator==(const Evt& evt) const {
    if ( n == evt.n
      && trig == evt.trig
      && card == evt.card
      && chan == evt.chan
      && pmtid == evt.pmtid
      && posx == evt.posx
      && posy == evt.posy
      && posz == evt.posz
      && time == evt.time
      && charge == evt.charge
      && ampli == evt.ampli
      && width == evt.width
      && evttime == evt.evttime
      && pulse == evt.pulse
      && boolword == evt.boolword
    ) { return true; }
    return false;
  }
  void Dump() const {
    std::cout << "event "<<n<<" card="<<card<<" chan="<<chan<<" pmtid="<<pmtid<<" posx="<<posx<<" posy="<<posy<<" posz="<<posz<< std::endl;
  }
  
  Long64_t n;
  Int_t trig;
  Int_t  card;
  Int_t  chan;
  Int_t  pmtid;
  Int_t  posx;
  Int_t  posz;
  Int_t  posy;
  Int_t time;
  Float_t charge;
  Float_t ampli;
  Float_t width;
  Float_t evttime;
  std::vector<Float_t> pulse;
  std::vector<Bool_t> boolword;
};

class Analyzer {
public:
  Analyzer(std::vector<TString> InFiles, const TString jobtype, const TString outputdir);
  virtual 	~Analyzer();
  void		Initialization();
  void		Finalize();
  void		Loop();
  
private:
    
  // Internal function
  Bool_t 	SetSaveFile();
  
  // time infos
  std::clock_t start;
  double duration;
  
  Bool_t debug;
  
  TFile *f_input, *f_output, *file;
  TString save, log;
  std::ofstream f_output_txt;
  
  // arguments
  std::vector<TString> InputFiles;
  std::vector<TString>::iterator itIF;
  TString output_dir;
  
  // job booleans
  TString job;
  Bool_t job_simu, job_run1, job_run2;
  
  // PMT number for run 1 and 2
  const static Int_t NbPMT_run1 = 61;
  const static Int_t NbPMT_run2 = 200;
  
  // booleans and counters
  Bool_t is_nGd, is_nH;
  Int_t Nneutrons;
  
  // Capture infos
  TString nucl_cap_pdg_code;
//   TRegexp pdg_nucl, pdg_gd, pdg_h;
  Int_t Ncaptures, Ncaptures_h, Ncaptures_gd;
  
  // PMT infos histos
  TH1F *hPMTx, *hPMTy, *hPMTz, *hPMTID,*hPMTcard,*hPMTchannel;
  // Charge and amplitude histos
  TH1F *hCharge, *hCharge_tot;
  TH1F *hCharge_perPMT_run1[NbPMT_run1];
  TH1F *hCharge_perPMT_run2[NbPMT_run2];
  TH1F *hNumPE;
  TH1F *hNHit; // number of photons hits 
  TH2F *hCharge_XZ;
  
  // Time and distance histos
  TH1F *hTrackDuration;
  TH1F *hTrackDuration_nGd;
  TH1F *hTrackDuration_nH;
  TH1F *hTrackLength;
  TH1F *hTrackLength_nGd;
  TH1F *hTrackLength_nH;
  
  // Dep. energy histos
  TH1F *hScintEdep;
  TH1F *hScintEdepQuen;
  TH1F *hScintEdep_x, *hScintEdep_y, *hScintEdep_z; // scintillation energy deposition
  TH1F *hEdep_x, *hEdep_y, *hEdep_z; // regular energy deposition
  
  // Variables
  Double_t init_time, fin_time;
  Double_t disp,deltat;
  Double_t charge_tot;
  Int_t Nhit;
  
  // Arrays
  int pmt_x_array_run1[NbPMT_run1];
  int pmt_x_array_run2[NbPMT_run2];
  int pmt_z_array_run1[NbPMT_run1];
  int pmt_z_array_run2[NbPMT_run2];
  int pmt_card_array_run1[NbPMT_run1];
  int pmt_card_array_run2[NbPMT_run2];
  int pmt_channel_array_run1[NbPMT_run1];
  int pmt_channel_array_run2[NbPMT_run2];
  std::vector<int> broken_pmt_vec; // in terms of pmtid (starting at 1)
  
  // TTrees, TChains and all that ROOT stuff
  TTree *nutri;
  TChain *chain;
  
  // Fixed size dimensions of array or collections stored in the TTree if any.
   static const Int_t kMaxprocResult = 4;
   static const Int_t kMaxmc = 1;
   static const Int_t kMaxcalib = 1;
   static const Int_t kMaxev = 1;
  
   RAT::DSReader *dsReader;
   RAT::DS::Root   *ds;
   
   RAT::TrackNav *nav;
   RAT::TrackCursor *cursor;
   RAT::TrackNode* node;
   
   // TVectors
   TVector3 init_pos;
   TVector3 fin_pos;
   
//    UInt_t          fUniqueID;
//    UInt_t          fBits;
//    Int_t           runID;
//    std::string         ratVersion;
//    Int_t           procResult_;
//    std::string          procResult_first[kMaxprocResult];
//    Int_t           procResult_second[kMaxprocResult];   //[procResult_]
//    Int_t           mc_;
//    UInt_t          mc_fUniqueID[kMaxmc];   //[mc_]
//    UInt_t          mc_fBits[kMaxmc];   //[mc_]
//    Int_t           mc_id[kMaxmc];   //[mc_]
//    Int_t           mc_numPE[kMaxmc];   //[mc_]
//    Int_t           mc_numDarkHits[kMaxmc];   //[mc_]
//    Int_t           mc_utc_fSec[kMaxmc];   //[mc_]
//    Int_t           mc_utc_fNanoSec[kMaxmc];   //[mc_]
//  std::vector<RAT::DS::MCSummary> mc_summary[kMaxmc];
//    std::vector<RAT::DS::MCParticle> mc_particle[kMaxmc];
//    std::vector<RAT::DS::MCParticle> mc_parent[kMaxmc];
//    std::vector<RAT::DS::MCTrack> mc_track[kMaxmc];
//    std::vector<RAT::DS::MCPMT>   mc_pmt[kMaxmc];
//    Int_t           calib_;
//    UInt_t          calib_fUniqueID[kMaxcalib];   //[calib_]
//    UInt_t          calib_fBits[kMaxcalib];   //[calib_]
//    Int_t           calib_id[kMaxcalib];   //[calib_]
//    Int_t           calib_mode[kMaxcalib];   //[calib_]
//    Float_t         calib_intensity[kMaxcalib];   //[calib_]
//    std::string          calib_name[kMaxcalib];
//    Int_t           calib_utc_fSec[kMaxcalib];   //[calib_]
//    Int_t           calib_utc_fNanoSec[kMaxcalib];   //[calib_]
//    UInt_t          calib_pos_fUniqueID[kMaxcalib];   //[calib_]
//    UInt_t          calib_pos_fBits[kMaxcalib];   //[calib_]
//    Double_t        calib_pos_fX[kMaxcalib];   //[calib_]
//    Double_t        calib_pos_fY[kMaxcalib];   //[calib_]
//    Double_t        calib_pos_fZ[kMaxcalib];   //[calib_]
//    Int_t           ev_;
//    UInt_t          ev_fUniqueID[kMaxev];   //[ev_]
//    UInt_t          ev_fBits[kMaxev];   //[ev_]
//    Int_t           ev_id[kMaxev];   //[ev_]
//    Float_t         ev_qTotal[kMaxev];   //[ev_]
//    Float_t         ev_calibratedTriggerTime[kMaxev];   //[ev_]
//    Float_t         ev_deltat[kMaxev];   //[ev_]
//    Int_t           ev_utc_fSec[kMaxev];   //[ev_]
//    Int_t           ev_utc_fNanoSec[kMaxev];   //[ev_]
//    std::vector<RAT::DS::PMT>     ev_pmt[kMaxev];
// //  std::vector<Centroid> ev_centroid[kMaxev];
// //  std::vector<PathFit> ev_pathfit[kMaxev];
//    std::vector<double>  user;

//    // List of branches
//    TBranch        *b_ds_fUniqueID;   //!
//    TBranch        *b_ds_fBits;   //!
//    TBranch        *b_ds_runID;   //!
//    TBranch        *b_ds_ratVersion;   //!
//    TBranch        *b_ds_procResult_;   //!
//    TBranch        *b_procResult_first;   //!
//    TBranch        *b_procResult_second;   //!
//    TBranch        *b_ds_mc_;   //!
//    TBranch        *b_mc_fUniqueID;   //!
//    TBranch        *b_mc_fBits;   //!
//    TBranch        *b_mc_id;   //!
//    TBranch        *b_mc_numPE;   //!
//    TBranch        *b_mc_numDarkHits;   //!
//    TBranch        *b_mc_utc_fSec;   //!
//    TBranch        *b_mc_utc_fNanoSec;   //!
//    TBranch        *b_mc_particle;   //!
//    TBranch        *b_mc_parent;   //!
//    TBranch        *b_mc_track;   //!
//    TBranch        *b_mc_pmt;   //!
//    TBranch        *b_ds_calib_;   //!
//    TBranch        *b_calib_fUniqueID;   //!
//    TBranch        *b_calib_fBits;   //!
//    TBranch        *b_calib_id;   //!
//    TBranch        *b_calib_mode;   //!
//    TBranch        *b_calib_intensity;   //!
//    TBranch        *b_calib_name;   //!
//    TBranch        *b_calib_utc_fSec;   //!
//    TBranch        *b_calib_utc_fNanoSec;   //!
//    TBranch        *b_calib_pos_fUniqueID;   //!
//    TBranch        *b_calib_pos_fBits;   //!
//    TBranch        *b_calib_pos_fX;   //!
//    TBranch        *b_calib_pos_fY;   //!
//    TBranch        *b_calib_pos_fZ;   //!
//    TBranch        *b_ds_ev_;   //!
//    TBranch        *b_ev_fUniqueID;   //!
//    TBranch        *b_ev_fBits;   //!
//    TBranch        *b_ev_id;   //!
//    TBranch        *b_ev_qTotal;   //!
//    TBranch        *b_ev_calibratedTriggerTime;   //!
//    TBranch        *b_ev_deltat;   //!
//    TBranch        *b_ev_utc_fSec;   //!
//    TBranch        *b_ev_utc_fNanoSec;   //!
//    TBranch        *b_ev_pmt;   //!
//    TBranch        *b_ds_user;   //!
  
  ULong64_t entry;
  ULong64_t NbEntries;
  
  Evt CurrentPulse;
  std::deque<Evt> CurrentEvt;
  std::deque< std::deque<Evt> > FourEvt;
  
  TCanvas *c1, *c2, *c3, *c4, *c5, *c6;
  
  private: // no copy allowed
    Analyzer(const Analyzer &){}
    
};

#endif