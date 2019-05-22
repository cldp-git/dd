#include "avivh.h"  



int main(int argc,char* argv[]){
TApplication* rootapp= new TApplication("why",&argc,argv);
 TH1F *h = new TH1F("h","All cuts",60,5050,5650);


TFile *f = new TFile("/MIT/h/dd.root");
  TTree *t = (TTree*)f->Get("DecayTree");
 TLorentzVector p1, p2, pd, pk, pb, plam,pk2,p5,p6,pd2,plam2;
particle B,D1,D2,k1,k2,pi1,pi2,pi3,pi4;
///////////////
/////////////// BDT cuts, B_mm
  float mDs1,mDs2,pidk1,pidk2,bdt1,bdt5,ml1,ml2,ipchi2,lab1fdchi,lab5fdchi;
  t->SetBranchAddress("lab0_DTF_B02DD_M",&B.m);
  t->SetBranchAddress("lab1_DFromBBDT",&bdt1);
  t->SetBranchAddress("lab5_DFromBBDT",&bdt5);
   t->SetBranchAddress("lab1_MM",&D1.m);
  t->SetBranchAddress("lab0_IPCHI2_OWNPV",&ipchi2);
  t->SetBranchAddress("lab1_TAU",&D1.tau);
  t->SetBranchAddress("lab5_TAU",&D2.tau);
  t->SetBranchAddress("lab1_FDCHI2_ORIVX",&lab1fdchi);
  t->SetBranchAddress("lab5_FDCHI2_ORIVX",&lab5fdchi);
  
/////////////// Three Momentum, pion/kaon mass
  t->SetBranchAddress("lab2_PX",&pi1.p[1]);
  t->SetBranchAddress("lab2_PY",&pi1.p[2]);
  t->SetBranchAddress("lab2_PZ",&pi1.p[3]);
  t->SetBranchAddress("lab3_PX",&pi2.p[1]);
  t->SetBranchAddress("lab3_PY",&pi2.p[2]);
  t->SetBranchAddress("lab3_PZ",&pi2.p[3]);
  t->SetBranchAddress("lab4_PX",&k1.p[1]);
  t->SetBranchAddress("lab4_PY",&k1.p[2]);
  t->SetBranchAddress("lab4_PZ",&k1.p[3]);
  t->SetBranchAddress("lab2_M",&pi1.m);
  t->SetBranchAddress("lab3_M",&pi2.m);
  t->SetBranchAddress("lab4_M",&k1.m);

 t->SetBranchAddress("lab3_PIDK",&pidk1);
  
///////////////
///////////////

   t->SetBranchAddress("lab5_MM",&D2.m);
  
/////////////// Three Momentum, pion/kaon mass
  t->SetBranchAddress("lab6_PX",&pi3.p[1]);
  t->SetBranchAddress("lab6_PY",&pi3.p[2]);
  t->SetBranchAddress("lab6_PZ",&pi3.p[3]);
  t->SetBranchAddress("lab7_PX",&pi4.p[1]);
  t->SetBranchAddress("lab7_PY",&pi4.p[2]);
  t->SetBranchAddress("lab7_PZ",&pi4.p[3]);
  t->SetBranchAddress("lab8_PX",&k2.p[1]);
  t->SetBranchAddress("lab8_PY",&k2.p[2]);
  t->SetBranchAddress("lab8_PZ",&k2.p[3]);
  t->SetBranchAddress("lab6_M",&pi3.m);
  t->SetBranchAddress("lab7_M",&pi4.m);
  t->SetBranchAddress("lab8_M",&k2.m);

 t->SetBranchAddress("lab7_PIDK",&pidk2);
///////////////
///////////////


int n = (int)t->GetEntries();
//int n=2000;
for(int e = 0; e < n; e++){
t->GetEntry(e);

//vk1=lorentzp4(k1);
//vpi1=lorentzp4(pi1);
//vpi2=lorentzp4(pi2);




///////////////////////////


///////////////////////////

bool bdtipchicut = bdt1*bdt5>0.67 && ipchi2 < 16;
bool dcut = fabs(D1.m-1869) < 25 && fabs(D2.m-1869) < 25;
bool taucut = D1.tau > 0 && D2.tau>0;
bool fdchicut = lab1fdchi > 2 && lab5fdchi > 2;
bool prelimcut = bdtipchicut && dcut && taucut && fdchicut;
if(prelimcut){
mDs1=swapPIDM(pi2,pi1,k1,MK);

ml1=swapPIDM(pi2,pi1,k1,MP);

mDs2=swapPIDM(pi4,pi3,k2,MK);

ml2=swapPIDM(pi4,pi3,k2,MP);

bool Ds1cut = fabs(mDs1-1968) > 25 || (fabs(mDs1-1968) < 25 && pidk1<-10);
bool Ds2cut = fabs(mDs2-1968) > 25 || (fabs(mDs2-1968) < 25 && pidk2<-10);
bool Dscut = Ds1cut && Ds2cut;
bool lambdacut = fabs(ml1-2286) > 25 && fabs(ml2-2286) > 25;

bool masscuts = Dscut && lambdacut;

if (masscuts){ cout<<"YOU ROCK"<<endl;
 h->Fill(B.m);}

}

  }

////////////////////
/*
TCanvas *canvas= new TCanvas("canvas","Canvas");
canvas->cd(1);

h->SetMinimum(0);
h->Draw();
 h->GetXaxis()->SetTitle("Mass (MeV)");

gSystem->Load("libRooFit") ;
using namespace RooFit ;

RooRealVar m("m","m",5200,5400);
RooRealVar m0("m0","m0",5279);
RooRealVar n1("n1","n1",5200,5400);
RooRealVar a("a","alpha",10);
RooRealVar s("s","sigma",50);
RooDataHist data("h","my data",m,h);

RooCBShape g("g","crystalball",m,m0,s,a,n1);
g.fitTo(data);
RooPlot* frame=m.frame() ;
data.plotOn(frame);
g.plotOn(frame);
g.paramOn(frame,data);
frame->Draw();
*/
return 0;
}

