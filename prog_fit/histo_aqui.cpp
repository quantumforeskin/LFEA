#include <iostream>
#include "TH2.h"
#include "TGraph.h"
#include "TMath.h"
#include "TCanvas.h"

using namespace std;

void histo_aqui()
{

  //SINOGRAMA
  
  TCanvas c;
  //c = new TCanvas("c","c",700,700);
  
  int phi[24] = {0,15,30,45,60,75,90,105,120,135,150,165,180,195,210,225,240,255,270,285,300,315,330,345};
  int the[13] = {-30,-25,-20,-15,-10,-5,0,5,10,15,20,25,30};
  //int the[14] = {-32.5,-27.5,-22.5,-17.5,-12.5,-7.5,-2.5,2.5,7.5,12.5,17.5,22.5,27.5,32.5}

  
  //int val[312] = {1,1,2,1,1,0,4,1,0,5,2,1,2,2,0,2,1,1,0,1,1,2,0,0,0 ,0 ,0 ,0 ,10,14,14,12,0 ,3 ,0 ,1 ,2 ,1 ,2 ,1 ,1 ,4 ,1 ,0 ,0 ,0 ,1 ,1 ,0  ,1  ,3  ,22 ,32  ,34 ,35 ,43 ,29 ,7  ,0  ,5  ,1  ,2  ,1  ,1  ,2  ,0  ,1  ,2  ,1  ,2  ,1  ,0  ,1 ,8 ,30 ,38,39 ,35,35,46,50,64,49 ,49,47,34,29,14,7 ,3 ,1 ,1 ,2 ,0 ,0 ,2 ,9  ,33 ,43,39 ,22 ,29 ,66 ,101,162,182,154  ,153,151,182,148,115,63 ,38 ,24 ,6  ,2  ,3  ,0  ,3  ,30 ,6  ,40,71 ,87,130,205,239,244,251,258 ,283,246,226,242,248,176,163,113,92 ,31 ,19 ,12 ,29 ,141,133,160,194,206,248,239,170,162,100,108,137,149,132,177,175,218,259,236,192,169,137,115,129,217,250,270 ,193,191 ,118,109,46 ,38 ,6  ,12,30 ,37 ,51 ,39 ,60 ,98 ,151,205,217,265,259,224,268,187,131,130 ,67 ,50 ,8  ,4  ,1  ,4  ,3  ,3,12 ,34 ,46 ,28 ,15 ,16 ,33 ,78 ,114,179,157,138,167,44,30,6,3 ,3,4 ,1 ,2 ,6 ,1 ,1,2 ,12,26,45,34,41,34,34,49,43,43,43,51,1 ,0 ,4 ,0 ,3,2 ,1 ,2 ,1 ,0 ,2 ,2 ,1 ,5 ,24,34,34,41,30,21,3 ,3 ,5 ,2 ,2 ,2 ,0 ,1 ,0,1 ,3 ,1 ,3 ,2 ,0 ,3 ,1 ,1 ,5 ,13,11,17,12,1 ,3 ,3 ,3 ,3 ,3,3,1,0,1,1,0,0,1,2,0,1,0,0,0,1,1,0,1,1,0,2,2,2};

  double val[312] = {0.000,0.020,0.020,0.020,0.020,0.020,0.040,0.000,0.020,0.020,0.200,0.040,0.120,0.060,0.260,0.060,0.025,0.025,0.050,0.033,0.033,0.033,0.033,0.000,0.020,0.000,0.000,0.020,0.020,0.080,0.080,0.080,0.040,0.080,0.180,1.240,2.320,0.180,2.380,1.080,0.075,0.075,0.075,0.000,0.033,0.033,0.000,0.033,0.040,0.020,0.040,0.060,0.160,0.300,0.420,0.400,0.480,1.040,3.400,5.200,6.980,6.660,6.120,4.780,1.825,0.150,0.100,0.033,0.100,0.067,0.033,0.100,0.000,0.060,0.100,0.480,1.020,0.780,0.940,1.180,2.840,4.900,7.760,8.080,6.420,6.000,7.240,7.760,5.600,2.400,0.200,0.033,0.000,0.033,0.000,0.033,0.020,0.320,0.780,1.140,1.360,1.160,1.420,3.440,6.700,7.060,5.780,3.020,2.520,2.220,3.240,5.640,7.925,5.700,2.300,0.100,0.033,0.033,0.000,0.167,0.520,0.940,1.380,0.940,0.820,1.040,3.600,7.340,5.920,3.020,1.820,1.380,1.300,0.640,0.540,1.720,5.325,8.625,6.150,1.400,0.067,0.067,0.033,0.333,1.140,1.240,0.560,0.240,1.400,4.400,7.500,0.580,1.240,0.300,0.660,1.140,1.260,0.980,0.900,0.420,1.225,1.425,8.050,5.500,1.333,0.233,0.700,0.900,1.080,0.300,0.520,2.240,5.640,7.500,3.180,0.460,0.200,0.060,0.040,1.080,0.900,1.440,1.220,1.020,0.675,1.550,5.450,6.967,4.967,2.400,2.033,1.300,2.180,2.580,4.640,7.000,6.940,2.780,0.180,0.100,0.080,0.080,0.040,0.480,0.180,0.740,1.160,1.340,1.175,0.850,2.475,6.767,6.700,6.400,5.167,2.800,6.720,7.260,7.560,5.380,2.040,0.080,0.100,0.020,0.020,0.020,0.080,0.040,0.020,0.120,0.420,0.800,1.275,0.850,1.500,2.367,5.733,7.567,7.733,5.933,7.820,6.300,4.000,0.940,0.020,0.060,0.020,0.020,0.020,0.000,0.040,0.020,0.020,0.020,0.080,0.160,0.275,0.425,0.425,0.233,1.700,4.900,5.967,8.200,3.300,1.540,0.180,0.060,0.020,0.060,0.000,0.000,0.020,0.060,0.020,0.000,0.020,0.000,0.020,0.080,0.075,0.125,0.125,0.100,0.100,0.533,2.300,3.133,0.240,0.060,0.080,0.040,0.000,0.040,0.020,0.020,0.000,0.020,0.000,0.000,0.000,0.020,0.020,0.040,0.100,0.050,0.025,0.033,0.033,0.100,0.167,0.300};

  
 TH2D *hist = new TH2D("Sinograma","",13,-32.5,32.5,24,-7.5,352.5);
  
  int k = 0;
  
  for (int i=0; i<13; i++)
  {
    for (int j=0; j<24;j++)
    {

      if(val[k]<=0)
	val[k]=0.1;
      hist->Fill(the[i],phi[j],val[k]);
      k++;
    }
  }

  hist->GetXaxis()->SetTitle("#theta [^{o}]");
  hist->GetYaxis()->SetTitle("#phi [^{o}]");
  hist->GetYaxis()->SetTitleOffset(1);
  //hist->GetZaxis()->SetTitleOffset(2);

  
    const Int_t NRGBs = 5;
    const Int_t NCont = 500;

    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    Double_t black[NRGBs]  = { 0.00, 0.00, 0.00, 0.00, 0.00 };
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue,NCont);
    gStyle->SetNumberContours(NCont);
  

    //Fonte forte
    TF1 *f = new TF1("a","180/TMath::Pi()*TMath::ACos(2.7297*TMath::Tan(x*TMath::Pi()/180))",-20.32,20.32);
    TF1 *f2 = new TF1("b","360-180/TMath::Pi()*TMath::ACos(2.7297*TMath::Tan(x*TMath::Pi()/180))",-20.32,20.32);
    f->SetLineColor(1);
    f2->SetLineColor(1);

    //Fonte fraca
    double limit = 13.863;
    TF1 *ff = new TF1("aa","-90+180/TMath::Pi()*TMath::ACos(4.0945*TMath::Tan(x*TMath::Pi()/180))",-limit,limit);
    TF1 *ff2 = new TF1("bb","360-90+180/TMath::Pi()*TMath::ACos(4.0945*TMath::Tan(x*TMath::Pi()/180))",-limit,limit);
    TF1 *ff3 = new TF1("bb","360-90-180/TMath::Pi()*TMath::ACos(4.0945*TMath::Tan(x*TMath::Pi()/180))",-limit,limit);
    f->SetLineColor(1);
    f2->SetLineColor(1);


  gStyle->SetOptStat(0); //tirar a tabela de estatisticas
  hist->Draw("colz");
  f->Draw("SAME");
  f2->Draw("SAME");
  ff->Draw("SAME");
  ff2->Draw("SAME");
  ff3->Draw("SAME");
  //hist->Draw("");
  c.Print("sinograma.png");
  
  



















  
  
  
  
  //RECONSTRUCAO
  /*
  //c = new TCanvas("c","c",600,700);
  TCanvas c;

  int X[15] = {-35,-30,-25,-20,-15,-10,-5,0,5,10,15,20,25,30,35};
  int Y[15] = {-35,-30,-25,-20,-15,-10,-5,0,5,10,15,20,25,30,35};

  //Reconstrucao
  double val[225] = {-0.00520940667919827,-0.0709903373261967,-0.0192021681368049,0.0459732184123753,-0.00188209035763080,-0.0190574410109047,-0.00994424174645489,0.00600106786774594,0.0339256519981210,-0.0166314126427618,-0.0307337444399340,0.0409538239315658,0.0463509679218066,0.0785027128925708,-0.000549095334295209,0.0858289719581794,0.0498363146745085,-0.0347504201931969,-0.0274684256061477,0.0401947585791377,-0.00685009330213803,-0.00806063081602896,0.0710504736151663,0.0138128225223246,-0.0341392431872331,0.0153204463207313,0.0132174165248511,0.0294944383569303,0.0393882660691333,0.0560559402431964,0.00658024321511153,0.0390109031903350,0.0487347582220051,0.0127642370447331,-0.0219678635255750,-0.0128546230764779,0.0114499951687109,0.0228518317089330,0.0135053409067943,-0.0243320134794449,0.0421953662196946,-0.0262312189584713,0.00536127689310415,0.0243997024966558,0.0277576195690852,-0.100685900662467,-0.0539066132094292,0.0154023515633108,0.00730171369427641,0.0553027647113870,0.0104639531439373,0.00555342379769692,0.00397914718035521,0.00602574561320953,0.00221654148702547,0.0696945428585631,0.0105814695486826,0.0239234351464344,-0.0127292712310891,-0.00965873198125207,0.172751296025664,0.0717239847935501,-0.0228696285811282,-0.0171630384477138,-0.0219065125933504,-0.00629989937722555,0.0524452050212712,0.0284454334978929,0.00760550794965709,0.0465557999950586,0.0730493000353285,0.111447003099075,0.0151469453123442,-0.0587657783386551,-0.00219920329215897,-0.134528295356626,-0.0561003344784182,0.0270942038923818,0.0927134457621534,0.0830151415843351,0.0382788865109664,0.0236796016846249,-0.0491432349463673,0.0583175225513930,0.131600178914415,0.472369685765033,0.554133675572123,0.142209423174551,-0.0997554011377425,-0.150886760340849,-0.0293083552295649,-0.0542834518663871,-0.0930924628587310,-0.132731899072286,-0.0957197296842600,-0.0453509963800301,0.0519161342407039,0.153953887218686,0.117827671917248,0.510047035175596,1.43327964034555,1.49282400653035,0.390298454477733,0.0597333264813060,0.0506078947336077,0.154980712518251,0.154178649658435,0.136086564821834,0.122457787629549,0.0773728064745736,0.0304023305473177,-0.0269511704945112,-0.204367601034364,-0.00687546817418004,0.811421265683825,2.26338833123813,2.55642825879035,1.08126270768637,0.316891556498562,0.134764601643456,-0.0767606602227425,-0.0887142785469381,-0.0940283396621366,-0.102555536907785,-0.0995538428096898,-0.0523679635359294,0.0776980858390827,0.199960780829425,0.0941995421633696,0.343631286007208,1.24130919579834,1.47352796973766,0.573860005020020,0.0963073405697264,0.0969567070991464,-0.112711750544477,-0.0639290632954773,-0.0228017737614741,0.0108871194576194,0.0346320411946836,0.0748776511473800,0.218087043256180,0.264251291999909,0.252635075908959,0.144725927538097,0.424281012783804,0.529275781318427,0.161798490493478,-0.115501479168563,-0.0975735150342475,0.124615172919373,0.0552628094379013,0.00596031520774881,0.0203345529451148,0.00279162253051885,0.0445816168663150,0.206856563162534,0.350977197788402,0.253923887523900,0.117296138203207,0.0532153851264903,0.105040318140697,0.0619302528443446,-0.0961925127160612,0.0874955221810868,-0.0623461711433342,-0.0214402333838552,0.0256722505811896,-0.0523594510072805,-0.0368781828083298,-0.0185625622577352,0.0743060913453821,0.177894671319753,0.151384677158234,0.0465291865834274,0.0333461329679331,0.0397127140742411,-0.0129091184511499,-0.0855635151906833,0.00911351466532341,-0.00121514571761029,0.00873920295626994,-0.0315804473923499,-0.0520283614769460,-0.00510955507222760,0.0207807876039525,0.0118284049241806,0.0662355226443711,0.0517413534323803,-0.0102648291877522,0.0707205899242250,0.0286966930352225,-0.0412586999650648,-0.0255227456663609,0.00343812348061685,0.0419493313622007,-0.00486211095526946,-0.0449383707311174,-0.00564803442711459,0.0459998560611763,-0.0214859361182629,0.0279181291259097,0.0673813768813141,-0.0174018344010201,-0.0280867718308667,0.0584001644767248,0.0710835766733431,0.00302168982779183,0.0187863377307812,-0.00402802448468536,-0.0115722813972465,-0.0367263622024727,-0.0215665455253067,0.0468668370555382,-0.0105263613129995,0.000437330613542668,0.0390509041840031,-0.0406153729084183,0.0213758110998609,-0.00381441135139487,0.0187220014652449,0.0628227617394062,0.0130219551453507,0.0978172397309866,-0.0677330465286598};
 

  TH2D *hist = new TH2D("Reconstrucao","",15,-37.5,37.5,15,-37.5,37.5);
  
  int k = 0;
  
  for (int i=0; i<15; i++)
  {
    for (int j=0; j<15;j++)
    {
      //if(val[k]<0.1)
      //val[k]=0.01;
      hist->Fill(X[j],Y[i],val[k]);
      //hist->SetBinContent(X[j],Y[i],val[k]);
      k++;
    }
  }

  //hist->GetZaxis()->SetRangeUser(-0.05, 3); // ... set the range ...
  
  //hist->GetXaxis()->SetTitle("X [^{o}]");
  //hist->GetYaxis()->SetTitle("Y [^{o}]");

  
  
    const Int_t NRGBs = 5;
    const Int_t NCont = 50;

    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    Double_t black[NRGBs]  = { 0.00, 0.00, 0.00, 0.00, 0.00 };
    //TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue,NCont);
    TColor::CreateGradientColorTable(NRGBs, stops, red, green,black,NCont);
    gStyle->SetNumberContours(NCont);
  

  hist->GetXaxis()->SetTitle("X");
  hist->GetYaxis()->SetTitle("Y");
  hist->GetZaxis()->SetTitle("Z");


  //hist->Draw("sph");
  gStyle->SetOptStat(0);
  gStyle->SetPadTickY(2);
  //hist->Draw("COLZ"); //normal
  hist->Draw("contz"); //countour
  //hist->Draw("SURF2Z"); //3D
  c.Print("recons_cont.png");
  
  
  */
  
}
