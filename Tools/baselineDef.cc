// ===========================================================================
// 
//       Filename:  baselineDef.cc
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/30/2015 15:43:56
//       Compiler:  g++ -std=c++11
// 
//         Author:  Zhenbin Wu (benwu)
//          Email:  zhenbin.wu@gmail.com
//        Company:  UIC, CMS@LPC, CDF@FNAL
// 
// ===========================================================================

#include "baselineDef.h"

void BaselineVessel::passBaseline(NTupleReader &tr)
{
  bool debug = false;
  bool doIsoTrksVeto = true;
  bool doMuonVeto = true;
  bool doEleVeto = true;
  bool incZEROtop = false;
  bool doMET = true;
  bool dodPhis = true;

  bool passBaseline = true;
  bool passBaselineNoTagMT2 = true;
  bool passBaselineNoTag = true;

  int bToFake = 1;
  muonsFlagIDLabel = "muonsFlagMedium";

  try
  {
    const double &temp  = tr.getVar<double>("genHT");
  }
  catch (std::string var)
  {
    if(tr.IsFirstEvent()) 
    {
      printf("NTupleReader::getTupleObj(const std::string var):  Variable not found: \"%s\"!!!\n", var.c_str());
      printf("Running with PHYS14 Config\n");
    }
    muonsFlagIDLabel = "";
  }
  std::string elesFlagIDLabel = "";

  if( spec.compare("noIsoTrksVeto") == 0)
  {
    doIsoTrksVeto = false;
  }
  else if( spec.compare("incZEROtop") == 0)
  {
    incZEROtop = true;
  }
  else if( spec.compare("hadtau") == 0)
  {
    doMuonVeto = false;
    doIsoTrksVeto = false;
    METLabel = "met_hadtau";
    METPhiLabel = "metphi_hadtau";
    jetVecLabel = "jetsLVec_hadtau";
    CSVVecLabel = "recoJetsBtag_0_hadtau";
  }
  else if( spec.compare("lostlept") == 0)
  {
    doMuonVeto = false;
    doEleVeto = false; 
    doIsoTrksVeto = false;
  }
  else if(spec.compare("Zinv") == 0) 
  {
    jetVecLabel = "cleanJetpt30ArrVec";//"jetsLVec";//"prodJetsNoMu_jetsLVec";
    CSVVecLabel = "cleanJetpt30ArrBTag";//"recoJetsBtag_0";
    METLabel    = "cleanMetPt";
    METPhiLabel = "cleanMetPhi";
    doMuonVeto  = false;
    doIsoTrksVeto = false;
  }
  else if(spec.compare("Zinv1b") == 0) 
  {
    jetVecLabel = "cleanJetpt30ArrVec";//"jetsLVec";//"prodJetsNoMu_jetsLVec";
    CSVVecLabel = "cleanJetpt30ArrBTag1fake";//"recoJetsBtag_0";
    METLabel    = "cleanMetPt";
    METPhiLabel = "cleanMetPhi";
    doMuonVeto  = false;
    doIsoTrksVeto = false;
    bToFake = 1;
  }
  else if(spec.compare("Zinv2b") == 0) 
  {
    jetVecLabel = "cleanJetpt30ArrVec";//"jetsLVec";//"prodJetsNoMu_jetsLVec";
    CSVVecLabel = "cleanJetpt30ArrBTag2fake";//"recoJetsBtag_0";
    METLabel    = "cleanMetPt";
    METPhiLabel = "cleanMetPhi";
    doMuonVeto  = false;
    doIsoTrksVeto = false;
    bToFake = 1;
  }
  else if(spec.compare("Zinv3b") == 0) 
  {
    jetVecLabel = "cleanJetpt30ArrVec";//"jetsLVec";//"prodJetsNoMu_jetsLVec";
    CSVVecLabel = "cleanJetpt30ArrBTag3fake";//"recoJetsBtag_0";
    METLabel    = "cleanMetPt";
    METPhiLabel = "cleanMetPhi";
    doMuonVeto  = false;
    doIsoTrksVeto = false;
    bToFake = 1;
  }
  else if(spec.compare("QCD") == 0)
  {
    doMET = false;
    dodPhis = false;
  }

  // Form TLorentzVector of MET
  TLorentzVector metLVec; metLVec.SetPtEtaPhiM(tr.getVar<double>(METLabel), 0, tr.getVar<double>(METPhiLabel), 0);

  // Calculate number of leptons
  const std::vector<int> & muonsFlagIDVec = muonsFlagIDLabel.empty()? std::vector<int>(tr.getVec<double>("muonsMiniIso").size(), 1):tr.getVec<int>(muonsFlagIDLabel.c_str()); // We have muonsFlagTight as well, but currently use medium ID
  const std::vector<int> & elesFlagIDVec = elesFlagIDLabel.empty()? std::vector<int>(tr.getVec<double>("elesMiniIso").size(), 1):tr.getVec<int>(elesFlagIDLabel.c_str()); // Fake electrons since we don't have different ID for electrons now, but maybe later
  int nMuons = AnaFunctions::countMuons(tr.getVec<TLorentzVector>("muonsLVec"), tr.getVec<double>("muonsMiniIso"), tr.getVec<double>("muonsMtw"), muonsFlagIDVec, AnaConsts::muonsMiniIsoArr);
  int nElectrons = AnaFunctions::countElectrons(tr.getVec<TLorentzVector>("elesLVec"), tr.getVec<double>("elesMiniIso"), tr.getVec<double>("elesMtw"), tr.getVec<unsigned int>("elesisEB"), elesFlagIDVec, AnaConsts::elesMiniIsoArr);
  int nIsoTrks = AnaFunctions::countIsoTrks(tr.getVec<TLorentzVector>("loose_isoTrksLVec"), tr.getVec<double>("loose_isoTrks_iso"), tr.getVec<double>("loose_isoTrks_mtw"), tr.getVec<int>("loose_isoTrks_pdgId"));

  // Calculate number of jets and b-tagged jets
  int cntCSVS = AnaFunctions::countCSVS(tr.getVec<TLorentzVector>(jetVecLabel), tr.getVec<double>(CSVVecLabel), AnaConsts::cutCSVS, AnaConsts::bTagArr);
  int cntNJetsPt50Eta24 = AnaFunctions::countJets(tr.getVec<TLorentzVector>(jetVecLabel), AnaConsts::pt50Eta24Arr);
  int cntNJetsPt30Eta24 = AnaFunctions::countJets(tr.getVec<TLorentzVector>(jetVecLabel), AnaConsts::pt30Eta24Arr);
  int cntNJetsPt30      = AnaFunctions::countJets(tr.getVec<TLorentzVector>(jetVecLabel), AnaConsts::pt30Arr);

  // Calculate deltaPhi
  std::vector<double> * dPhiVec = new std::vector<double>();
  (*dPhiVec) = AnaFunctions::calcDPhi(tr.getVec<TLorentzVector>(jetVecLabel), metLVec.Phi(), 3, AnaConsts::dphiArr);

  // Prepare jets and b-tag working points for top tagger
  std::vector<TLorentzVector> *jetsLVec_forTagger = new std::vector<TLorentzVector>(); std::vector<double> *recoJetsBtag_forTagger = new std::vector<double>();
  AnaFunctions::prepareJetsForTagger(tr.getVec<TLorentzVector>(jetVecLabel), tr.getVec<double>(CSVVecLabel), (*jetsLVec_forTagger), (*recoJetsBtag_forTagger));
  if( debug ) std::cout<<"\njetsLVec_forTagger->size : "<<jetsLVec_forTagger->size()<<"  recoJetsBtag_forTagger->size : "<<recoJetsBtag_forTagger->size()<<"  passBaseline : "<<passBaseline<<std::endl;

  // Pass lepton veto?
  bool passMuonVeto = (nMuons == AnaConsts::nMuonsSel), passEleVeto = (nElectrons == AnaConsts::nElectronsSel), passIsoTrkVeto = (nIsoTrks == AnaConsts::nIsoTrksSel);
  bool passLeptVeto = passMuonVeto && passEleVeto && passIsoTrkVeto;
  if( doMuonVeto && !passMuonVeto ){ passBaseline = false; passBaselineNoTagMT2 = false; passBaselineNoTag = false; }
  if( doEleVeto && !passEleVeto ){ passBaseline = false; passBaselineNoTagMT2 = false; passBaselineNoTag = false; }
  // Isolated track veto is disabled for now
  if( doIsoTrksVeto && !passIsoTrkVeto ){ passBaseline = false; passBaselineNoTagMT2 = false; passBaselineNoTag = false; }

  if( debug ) std::cout<<"nMuons : "<<nMuons<<"  nElectrons : "<<nElectrons<<"  nIsoTrks : "<<nIsoTrks<<"  passBaseline : "<<passBaseline<<std::endl;

  // Pass number of jets?
  bool passnJets = true;
  if( cntNJetsPt50Eta24 < AnaConsts::nJetsSelPt50Eta24 ){ passBaseline = false; passBaselineNoTagMT2 = false; passBaselineNoTag = false; passnJets = false; }
  if( cntNJetsPt30Eta24 < AnaConsts::nJetsSelPt30Eta24 ){ passBaseline = false; passBaselineNoTagMT2 = false; passBaselineNoTag = false; passnJets = false; }
  if( debug ) std::cout<<"cntNJetsPt50Eta24 : "<<cntNJetsPt50Eta24<<"  cntNJetsPt30Eta24 : "<<cntNJetsPt30Eta24<<"  cntNJetsPt30 : "<<cntNJetsPt30<<"  passBaseline : "<<passBaseline<<std::endl;

  // Pass deltaPhi?
  bool passdPhis = (dPhiVec->at(0) >= AnaConsts::dPhi0_CUT && dPhiVec->at(1) >= AnaConsts::dPhi1_CUT && dPhiVec->at(2) >= AnaConsts::dPhi2_CUT);
  if( dodPhis && !passdPhis ){ passBaseline = false; passBaselineNoTagMT2 = false; passBaselineNoTag = false; }
  if( debug ) std::cout<<"dPhi0 : "<<dPhiVec->at(0)<<"  dPhi1 : "<<dPhiVec->at(1)<<"  dPhi2 : "<<dPhiVec->at(2)<<"  passBaseline : "<<passBaseline<<std::endl;

  // Pass number of b-tagged jets?
  bool passBJets = true;
  if( !( (AnaConsts::low_nJetsSelBtagged == -1 || cntCSVS >= AnaConsts::low_nJetsSelBtagged) && (AnaConsts::high_nJetsSelBtagged == -1 || cntCSVS < AnaConsts::high_nJetsSelBtagged ) ) ){ passBaseline = false; passBJets = false; }
  if( debug ) std::cout<<"cntCSVS : "<<cntCSVS<<"  passBaseline : "<<passBaseline<<std::endl;

  // Pass the baseline MET requirement?
  bool passMET = (metLVec.Pt() >= AnaConsts::defaultMETcut);
  if( doMET && !passMET ){ passBaseline = false; passBaselineNoTagMT2 = false; passBaselineNoTag = false; }
  if( debug ) std::cout<<"met : "<<tr.getVar<double>("met")<<"  defaultMETcut : "<<AnaConsts::defaultMETcut<<"  passBaseline : "<<passBaseline<<std::endl;

  // Pass the HT cut for trigger?
  double HT = AnaFunctions::calcHT(tr.getVec<TLorentzVector>(jetVecLabel), AnaConsts::pt30Eta24Arr);
  bool passHT = true;
  if( HT < AnaConsts::defaultHTcut ){ passHT = false; passBaseline = false; passBaselineNoTagMT2 = false; passBaselineNoTag = false; }
  if( debug ) std::cout<<"HT : "<<HT<<"  defaultHTcut : "<<AnaConsts::defaultHTcut<<"  passHT : "<<passHT<<"  passBaseline : "<<passBaseline<<std::endl;

  // Calculate top tagger related variables. 
  // Note that to save speed, only do the calculation after previous base line requirements.
  int nTopCandSortedCnt = -1;

  if( passnJets && cntNJetsPt30 >= AnaConsts::nJetsSel ){
    type3Ptr->setCSVToFake(bToFake);
    type3Ptr->processEvent((*jetsLVec_forTagger), (*recoJetsBtag_forTagger), metLVec);
    nTopCandSortedCnt = type3Ptr->nTopCandSortedCnt;
  }

  // Pass the baseline MT2 requirement?
  bool passMT2 = true;
  if( type3Ptr->best_had_brJet_MT2 < AnaConsts::defaultMT2cut ){ passBaseline = false; passBaselineNoTag = false; passMT2 = false; }
  if( debug ) std::cout<<"MT2 : "<<type3Ptr->best_had_brJet_MT2<<"  defaultMT2cut : "<<AnaConsts::defaultMT2cut<<"  passBaseline : "<<passBaseline<<std::endl;

  // Pass top tagger requirement?
  bool passTagger = type3Ptr->passNewTaggerReq() && (incZEROtop || nTopCandSortedCnt >= AnaConsts::low_nTopCandSortedSel);

  if( !passTagger ) passBaseline = false;

  bool passNoiseEventFilter = true;
  if( !passNoiseEventFilterFunc(tr) ) { passNoiseEventFilter = false; passBaseline = false; passBaselineNoTagMT2 = false; passBaselineNoTag = false; }
  if( debug ) std::cout<<"passNoiseEventFilterFunc : "<<passNoiseEventFilterFunc(tr)<<"  passBaseline : "<<passBaseline<<std::endl;

  // Register all the calculated variables
  tr.registerDerivedVar("nMuons_Base" + spec, nMuons);
  tr.registerDerivedVar("nElectrons_Base" + spec, nElectrons);
  tr.registerDerivedVar("nIsoTrks_Base" + spec, nIsoTrks);
  //tr.registerDerivedVar("nMuons_CUT" + spec, nMuons);
  //tr.registerDerivedVar("nElectrons_CUT" + spec, nElectrons);
  //tr.registerDerivedVar("nIsoTrks_CUT" + spec, nIsoTrks);


  tr.registerDerivedVar("cntNJetsPt50Eta24" + spec, cntNJetsPt50Eta24);
  tr.registerDerivedVar("cntNJetsPt30Eta24" + spec, cntNJetsPt30Eta24);

  tr.registerDerivedVec("dPhiVec" + spec, dPhiVec);

  tr.registerDerivedVar("cntCSVS" + spec, cntCSVS);

  tr.registerDerivedVec("jetsLVec_forTagger" + spec, jetsLVec_forTagger);
  tr.registerDerivedVec("recoJetsBtag_forTagger" + spec, recoJetsBtag_forTagger);

  tr.registerDerivedVar("cntNJetsPt30" + spec, cntNJetsPt30);

  tr.registerDerivedVar("passLeptVeto" + spec, passLeptVeto);
  tr.registerDerivedVar("passMuonVeto" + spec, passMuonVeto);
  tr.registerDerivedVar("passEleVeto" + spec, passEleVeto);
  tr.registerDerivedVar("passIsoTrkVeto" + spec, passIsoTrkVeto);
  tr.registerDerivedVar("passnJets" + spec, passnJets);
  tr.registerDerivedVar("passdPhis" + spec, passdPhis);
  tr.registerDerivedVar("passBJets" + spec, passBJets);
  tr.registerDerivedVar("passMET" + spec, passMET);
  tr.registerDerivedVar("passMT2" + spec, passMT2);
  tr.registerDerivedVar("passHT" + spec, passHT);
  tr.registerDerivedVar("passTagger" + spec, passTagger);
  tr.registerDerivedVar("passNoiseEventFilter" + spec, passNoiseEventFilter);
  tr.registerDerivedVar("passBaseline" + spec, passBaseline);
  tr.registerDerivedVar("passBaselineNoTagMT2" + spec, passBaselineNoTagMT2);
  tr.registerDerivedVar("passBaselineNoTag" + spec, passBaselineNoTag);

  tr.registerDerivedVar("nTopCandSortedCnt" + spec, nTopCandSortedCnt);

  tr.registerDerivedVar("best_lept_brJet_MT" + spec,    type3Ptr->best_lept_brJet_MT);
  tr.registerDerivedVar("best_had_brJet_MT" + spec,     type3Ptr->best_had_brJet_MT);
  tr.registerDerivedVar("best_had_brJet_mTcomb" + spec, type3Ptr->best_had_brJet_mTcomb);
  tr.registerDerivedVar("best_had_brJet_MT2" + spec,    type3Ptr->best_had_brJet_MT2);

  tr.registerDerivedVar("HT" + spec, HT);

  if( debug ) std::cout<<"passBaseline : "<<passBaseline<<"  passBaseline : "<<passBaseline<<std::endl;
} 

void BaselineVessel::prepareTopTagger(){
  //if( !type3Ptr ) type3Ptr = new topTagger::type3TopTagger();
  type3Ptr = new topTagger::type3TopTagger();
  type3Ptr->setnJetsSel(AnaConsts::nJetsSel);
  type3Ptr->setCSVS(AnaConsts::cutCSVS);
}

bool BaselineVessel::GetnTops(NTupleReader *tr) const
{
  int nTops = tr->getVar<int>("nTopCandSortedCnt" + spec);
  std::vector<TLorentzVector> *vTops = new std::vector<TLorentzVector>();
  std::map<int, std::vector<TLorentzVector> > *vTopJets = new std::map<int, std::vector<TLorentzVector> >();

  for(int it=0; it<nTops; it++)
  {
    TLorentzVector topLVec = type3Ptr->buildLVec(tr->getVec<TLorentzVector>("jetsLVec_forTagger" + spec), 
        type3Ptr->finalCombfatJets[type3Ptr->ori_pickedTopCandSortedVec[it]]);
    vTops->push_back(topLVec);

    std::vector<TLorentzVector> temp;
    std::vector<int> indexCombVec = type3Ptr->finalCombfatJets[type3Ptr->ori_pickedTopCandSortedVec[it]];
    for (size_t k = 0; k < indexCombVec.size(); ++k)
    {
      temp.push_back( (tr->getVec<TLorentzVector>("jetsLVec_forTagger"+spec)).at(indexCombVec.at(k)));
    }
    vTopJets->insert(std::make_pair(it, temp));
  }

  tr->registerDerivedVec("vTops"+spec, vTops);
  tr->registerDerivedVec("mTopJets"+spec, vTopJets);

  return true;
}       // -----  end of function VarPerEvent::GetnTops  -----


bool BaselineVessel::passNoiseEventFilterFunc(NTupleReader &tr){
  try
  {
    int jetIDFilter = tr.getVar<int>("prodJetIDEventFilter");
    int beamHaloFilter = tr.getVar<int>("CSCTightHaloFilter");
    int ecalTPFilter = tr.getVar<int>("EcalDeadCellTriggerPrimitiveFilter");
    bool hbheNoiseFilter = tr.getVar<bool>("HBHENoiseFilter");
    int vtxSize = tr.getVar<int>("vtxSize");

    //return (vtxSize>=1) && beamHaloFilter && ecalTPFilter && hbheNoiseFilter && jetIDFilter;
    return (vtxSize>=1) && beamHaloFilter && ecalTPFilter && hbheNoiseFilter;
  }
  catch (std::string var)
  {
    if(tr.IsFirstEvent()) 
    {
      printf("NTupleReader::getTupleObj(const std::string var):  Variable not found: \"%s\"!!!\n", var.c_str());
      printf("Running with PHYS14 Config\n");
    }
  }
  return true;
}


void stopFunctions::CleanJets::setMuonIso(const std::string muIsoFlag) 
{
  if(muIsoFlag.compare("mini") == 0)
  {
    muIsoStr_ = "muonsMiniIso";
    muIsoReq_ = AnaConsts::muonsMiniIsoArr;
  }
  else if(muIsoFlag.compare("rel") == 0)
  {
    muIsoStr_ = "muonsRelIso";
    muIsoReq_ = AnaConsts::muonsArr;
  }
  else
  {
    std::cout << "cleanJets(...):  muon iso mode not recognized!!!  Using \"rel iso\" settings." << std::endl;
    muIsoStr_ = "muonsRelIso";
    muIsoReq_ = AnaConsts::muonsArr;
  }
}

void stopFunctions::CleanJets::setElecIso(const std::string elecIsoFlag)
{
  if(elecIsoFlag.compare("mini") == 0)
  {
    //                std::cout << "cleanJets(...):  electron mini iso mode not implemented yet!!! Using \"rel iso\" settings." << std::endl;
    elecIsoStr_ = "elesMiniIso";
    elecIsoReq_ = AnaConsts::elesMiniIsoArr;
    //                elecIsoStr_ = "elesRelIso";
    //                elecIsoReq_ = AnaConsts::elesArr;
  }
  else if(elecIsoFlag.compare("rel") == 0)
  {
    elecIsoStr_ = "elesRelIso";
    elecIsoReq_ = AnaConsts::elesArr;
  }
  else
  {
    std::cout << "cleanJets(...):  muon iso mode not recognized!!!  Using \"rel iso\" settings." << std::endl;
    elecIsoStr_ = "elesRelIso";
    elecIsoReq_ = AnaConsts::elesArr;
  }
}

void stopFunctions::CleanJets::setJetCollection(std::string jetVecLabel)
{
  jetVecLabel_ = jetVecLabel;
}

void stopFunctions::CleanJets::setBTagCollection(std::string bTagLabel)
{
  bTagLabel_ = bTagLabel;
}

void stopFunctions::CleanJets::setMuonsFlagID(std::string muonsFlagIDLabel)
{
  muonsFlagIDLabel_ = muonsFlagIDLabel;
}

void stopFunctions::CleanJets::setElesFlagID(std::string elesFlagIDLabel)
{
  elesFlagIDLabel_ = elesFlagIDLabel;
}

void stopFunctions::CleanJets::setEnergyFractionCollections(std::string chargedEMfrac, std::string neutralEMfrac, std::string chargedHadfrac)
{
  chargedEMFracLabel_ = chargedEMfrac;
  neutralEMFracLabel_ = neutralEMfrac;
  chargedHadFracLabel_ = chargedHadfrac;
}

void stopFunctions::CleanJets::setForceDr(bool forceDr)
{
  forceDr_ = forceDr;
}

void stopFunctions::CleanJets::setDisable(bool disable)
{
  disable_ = disable;
}

void stopFunctions::CleanJets::setRemove(bool remove)
{
  remove_ = remove;
}

void stopFunctions::CleanJets::setElecPtThresh(double minPt)
{
  elecPtThresh_ = minPt;
}

void stopFunctions::CleanJets::setMuonPtThresh(double minPt)
{
  muonPtThresh_ = minPt;
}

void stopFunctions::CleanJets::setPhotoCleanThresh(double photoCleanThresh)
{
  photoCleanThresh_ = photoCleanThresh;
}

int stopFunctions::CleanJets::cleanLeptonFromJet(const TLorentzVector& lep, const int& lepMatchedJetIdx, const std::vector<TLorentzVector>& jetsLVec, std::vector<bool>& keepJet, const std::vector<double>& neutralEmEnergyFrac, std::vector<TLorentzVector>* cleanJetVec, const double& jldRMax, const double photoCleanThresh)
{
  int match = lepMatchedJetIdx;
  if(match < 0)
  {
    //If muon matching to PF candidate has failed, use dR matching as fallback
    match = AnaFunctions::jetLepdRMatch(lep, jetsLVec, jldRMax);
  }

  if(match >= 0)
  {
    if(remove_ || (photoCleanThresh > 0.0 && neutralEmEnergyFrac[match] > photoCleanThresh) )
    {
      keepJet[match] = false;
    }
    else
    {
      (*cleanJetVec)[match] -= lep;
    }
  }

  return match;
}

void stopFunctions::CleanJets::internalCleanJets(NTupleReader& tr)
{
  const std::vector<TLorentzVector>& jetsLVec         = tr.getVec<TLorentzVector>(jetVecLabel_);
  const std::vector<TLorentzVector>& elesLVec         = tr.getVec<TLorentzVector>("elesLVec");
  const std::vector<TLorentzVector>& muonsLVec        = tr.getVec<TLorentzVector>("muonsLVec");
  const std::vector<double>&         elesIso          = tr.getVec<double>(elecIsoStr_);
  const std::vector<double>&         muonsIso         = tr.getVec<double>(muIsoStr_);
  const std::vector<int>&            muonsFlagIDVec   = muonsFlagIDLabel_.empty()? std::vector<int>(muonsIso.size(), 1):tr.getVec<int>(muonsFlagIDLabel_.c_str());
  const std::vector<int>&            elesFlagIDVec    = elesFlagIDLabel_.empty()? std::vector<int>(elesIso.size(), 1):tr.getVec<int>(elesFlagIDLabel_.c_str());
  const std::vector<double>&         recoJetsBtag_0   = tr.getVec<double>(bTagLabel_);
  const std::vector<double>& chargedHadronEnergyFrac  = tr.getVec<double>(chargedHadFracLabel_);
  const std::vector<double>&     neutralEmEnergyFrac  = tr.getVec<double>(neutralEMFracLabel_);
  const std::vector<double>&     chargedEmEnergyFrac  = tr.getVec<double>(chargedEMFracLabel_);
  const std::vector<int>&            muMatchedJetIdx  = tr.getVec<int>("muMatchedJetIdx");
  const std::vector<int>&            eleMatchedJetIdx = tr.getVec<int>("eleMatchedJetIdx");
  const std::vector<unsigned int>&   elesisEB         = tr.getVec<unsigned int>("elesisEB");

  const unsigned int& run   = tr.getVar<unsigned int>("run");
  const unsigned int& lumi  = tr.getVar<unsigned int>("lumi");
  const unsigned int& event = tr.getVar<unsigned int>("event");

  if(elesLVec.size() != elesIso.size() 
      || elesLVec.size() != eleMatchedJetIdx.size()
      || elesLVec.size() != elesisEB.size()
      || muonsLVec.size() != muonsIso.size()
      || muonsLVec.size() != muMatchedJetIdx.size()
      || jetsLVec.size() != recoJetsBtag_0.size()
      || jetsLVec.size() != chargedHadronEnergyFrac.size()
      || jetsLVec.size() != neutralEmEnergyFrac.size()
      || jetsLVec.size() != chargedEmEnergyFrac.size())
  {
    std::cout << "MISMATCH IN VECTOR SIZE!!!!! Aborting jet cleaning algorithm!!!!!!" << std::endl;
    return;
  }

  std::vector<TLorentzVector>* cleanJetVec        = new std::vector<TLorentzVector>(jetsLVec);
  std::vector<double>* cleanJetBTag               = new std::vector<double>(recoJetsBtag_0);
  std::vector<TLorentzVector>* cleanJetpt30ArrVec = new std::vector<TLorentzVector>();
  std::vector<double>* cleanJetpt30ArrBTag        = new std::vector<double>;
  std::vector<double>* cleanChargedHadEFrac       = new std::vector<double>(chargedHadronEnergyFrac);
  std::vector<double>* cleanNeutralEMEFrac        = new std::vector<double>(neutralEmEnergyFrac);
  std::vector<double>* cleanChargedEMEFrac        = new std::vector<double>(chargedEmEnergyFrac);

  std::vector<TLorentzVector>* removedJetVec      = new std::vector<TLorentzVector>();
  std::vector<double>* removedChargedHadEFrac     = new std::vector<double>();
  std::vector<double>* removedNeutralEMEFrac      = new std::vector<double>();
  std::vector<double>* removedChargedEMEFrac      = new std::vector<double>();

  std::vector<int>* rejectJetIdx_formuVec = new std::vector<int>();
  std::vector<int>* rejectJetIdx_foreleVec = new std::vector<int>();

  const double jldRMax = 0.15;

  const double HT_jetPtMin = 50;
  const double HT_jetEtaMax = 2.4;
  const double MHT_jetPtMin = 30.0;

  double HT = 0.0, HTNoIso = 0.0;
  TLorentzVector MHT;

  std::vector<bool> keepJetPFCandMatch(jetsLVec.size(), true);

  if(!disable_)
  {
    for(int iM = 0; iM < muonsLVec.size() && iM < muonsIso.size() && iM < muMatchedJetIdx.size(); ++iM)
    {
      if(!AnaFunctions::passMuon(muonsLVec[iM], muonsIso[iM], 0.0, muonsFlagIDVec[iM], muIsoReq_) && muonsLVec[iM].Pt() > muonPtThresh_) 
      {
        rejectJetIdx_formuVec->push_back(-1);
        continue;
      }

      int match = -1;
      if(forceDr_) match = cleanLeptonFromJet(muonsLVec[iM],                  -1, jetsLVec, keepJetPFCandMatch, neutralEmEnergyFrac, cleanJetVec, jldRMax, photoCleanThresh_);
      else         match = cleanLeptonFromJet(muonsLVec[iM], muMatchedJetIdx[iM], jetsLVec, keepJetPFCandMatch, neutralEmEnergyFrac, cleanJetVec, jldRMax, photoCleanThresh_);

      if( match >= 0 ) rejectJetIdx_formuVec->push_back(match);
      else rejectJetIdx_formuVec->push_back(-1);
    }

    for(int iE = 0; iE < elesLVec.size() && iE < elesIso.size() && iE < eleMatchedJetIdx.size(); ++iE)
    {
      if(!AnaFunctions::passElectron(elesLVec[iE], elesIso[iE], 0.0, elesisEB[iE], elesFlagIDVec[iE], elecIsoReq_) && elesLVec[iE].Pt() > elecPtThresh_) 
      {
        rejectJetIdx_foreleVec->push_back(-1);
        continue;
      }

      int match = -1;
      if(forceDr_) match = cleanLeptonFromJet(elesLVec[iE],                   -1, jetsLVec, keepJetPFCandMatch, neutralEmEnergyFrac, cleanJetVec, jldRMax);
      else         match = cleanLeptonFromJet(elesLVec[iE], eleMatchedJetIdx[iE], jetsLVec, keepJetPFCandMatch, neutralEmEnergyFrac, cleanJetVec, jldRMax);

      if( match >= 0 ) rejectJetIdx_foreleVec->push_back(match);
      else rejectJetIdx_foreleVec->push_back(-1);
    }
  }

  int jetsKept = 0;
  auto iJet = cleanJetVec->begin();
  auto iOrigJet = jetsLVec.begin();
  auto iBTag = cleanJetBTag->begin();
  auto iKeep = keepJetPFCandMatch.begin();
  auto iCHF = cleanChargedHadEFrac->begin();
  auto iNEMF = cleanNeutralEMEFrac->begin();
  auto iCEMF = cleanChargedEMEFrac->begin();
  const bool& passMuZinvSel = tr.getVar<bool>("passMuZinvSel");
  for(; iJet != cleanJetVec->end() && iBTag != cleanJetBTag->end() && iKeep != keepJetPFCandMatch.end() && iOrigJet != jetsLVec.end(); ++iKeep, ++iOrigJet)
  {
    if(!(*iKeep))
    {
      removedJetVec->push_back(*iOrigJet);
      removedChargedHadEFrac->push_back(*iCHF);
      removedNeutralEMEFrac->push_back(*iNEMF);
      removedChargedEMEFrac->push_back(*iCEMF);
      iJet = cleanJetVec->erase(iJet);
      iBTag = cleanJetBTag->erase(iBTag);
      iCHF = cleanChargedHadEFrac->erase(iCHF);
      iNEMF = cleanNeutralEMEFrac->erase(iNEMF);
      iCEMF = cleanChargedEMEFrac->erase(iCEMF);
      continue;
    }

    ++jetsKept;
    if(AnaFunctions::jetPassCuts(*iJet, AnaConsts::pt30Arr))
    {
      cleanJetpt30ArrVec->push_back(*iJet);
      cleanJetpt30ArrBTag->push_back(*iBTag);
    }
    if(iJet->Pt() > HT_jetPtMin && fabs(iJet->Eta()) < HT_jetEtaMax) HT += iJet->Pt();
    if(iJet->Pt() > MHT_jetPtMin) MHT += *iJet;

    ++iJet;
    ++iBTag;
    ++iCHF;
    ++iNEMF;
    ++iCEMF;
  }

  tr.registerDerivedVar("nJetsRemoved", static_cast<int>(jetsLVec.size() - jetsKept));
  tr.registerDerivedVar("cleanHt", HT);
  tr.registerDerivedVar("cleanMHt", MHT.Pt());
  tr.registerDerivedVar("cleanMHtPhi", MHT.Phi());
  tr.registerDerivedVec("removedJetVec", removedJetVec);
  tr.registerDerivedVec("cleanJetVec", cleanJetVec);
  tr.registerDerivedVec("cleanJetBTag", cleanJetBTag);
  tr.registerDerivedVec("cleanJetpt30ArrVec", cleanJetpt30ArrVec);
  tr.registerDerivedVec("cleanJetpt30ArrBTag", cleanJetpt30ArrBTag);
  tr.registerDerivedVec("cleanChargedHadEFrac", cleanChargedHadEFrac);
  tr.registerDerivedVec("cleanNeutralEMEFrac", cleanNeutralEMEFrac);
  tr.registerDerivedVec("cleanChargedEMEFrac", cleanChargedEMEFrac);
  tr.registerDerivedVec("removedChargedHadEFrac", removedChargedHadEFrac);
  tr.registerDerivedVec("removedNeutralEMEFrac",  removedNeutralEMEFrac);
  tr.registerDerivedVec("removedChargedEMEFrac",  removedChargedEMEFrac);
  tr.registerDerivedVec("rejectJetIdx_formuVec", rejectJetIdx_formuVec);
  tr.registerDerivedVec("rejectJetIdx_foreleVec", rejectJetIdx_foreleVec);
}
