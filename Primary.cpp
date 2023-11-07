//---------------------------------------------------------------------------------------------//

#include <vcl.h>

#include <iostream> // something
#include <fstream>  //          probably
#include <string>	// omg

#pragma hdrstop

#include "Primary.h"

//---------------------------------------------------------------------------------------------//

#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

Word Year, Month, Day, Hours, Minutes, Seconds, MSeconds;

//---------------------------------------------------------------------------------------------//

__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	DateTimePicker1->Time = Now(); DateTimePicker1->Date = Now(); // set up time & date
	DecodeDate(DateTimePicker1->Date, Year, Month, Day);
	DecodeTime(DateTimePicker1->Time, Hours, Minutes, Seconds, MSeconds);
	Memo1->Lines->Add(">>> M00N");
	Memo1->Lines->Add("");
};

//---------------------------------------------------------------------------------------------//

void __fastcall TForm1::DateTimePicker1Change(TObject *Sender)
{
	DecodeDate(DateTimePicker1->Date, Year, Month, Day);
	DecodeTime(DateTimePicker1->Time, Hours, Minutes, Seconds, MSeconds);

	if (CheckBox1->Checked == True)
	{
		Memo1->Lines->Add("> Year: " + IntToStr(Year) + " Month: " + IntToStr(Month) + " Day: " + IntToStr(Day));
		Memo1->Lines->Add("> Hours: " + IntToStr(Hours) + " Minutes: " + IntToStr(Minutes) + " Seconds: " + IntToStr(Seconds));
	};
};

//---------------------------------------------------------------------------------------------//

double get_PI()
{
	double pi;
	__asm
	{
		fldpi
		fstp pi
	}
	return pi;
};

//---------------------------------------------------------------------------------------------//

bool IsLeap(int year)
{
	return (year%400==0)||((year%4==0)&&(year%100!=0));
};

//---------------------------------------------------------------------------------------------//

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	Word dtYear, dtMonth, dtDay, dtHour, dtMin, dtSec, dtMSec; TDateTime dtPresent = Now();
	DecodeDate(dtPresent, dtYear, dtMonth, dtDay);
	DecodeTime(dtPresent, dtHour, dtMin, dtSec, dtMSec);
	UnicodeString uLine01 = "Program Start In : " + IntToStr(dtYear) + "/" + IntToStr(dtMonth) + "/" + IntToStr(dtDay) + " " + IntToStr(dtHour) + ":" + IntToStr(dtMin) + ":" + IntToStr(dtSec) + ":" + IntToStr(dtMSec) + "\n\n";
	std::string fstr01(AnsiString(uLine01).c_str());
	DecodeDate(DateTimePicker1->Date, Year, Month, Day);
	DecodeTime(DateTimePicker1->Time, Hours, Minutes, Seconds, MSeconds);
	UnicodeString uLine02 = "Calculations for : " + IntToStr(Year) + "/" + IntToStr(Month) + "/" + IntToStr(Day) + " " + IntToStr(Hours) + ":" + IntToStr(Minutes) + ":" + IntToStr(Seconds) + "\n\n"; //":" + IntToStr(MSeconds) + "\n\n";
	std::string fstr02(AnsiString(uLine02).c_str());

	String dirname = "result";
	if (CreateDirectory(dirname.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
	{
		//
	}
	else
	{
		ShowMessage("Failed to create directory 'result' in a program folder. Please create in manually, or you will not see a log-file.");
	};

	String fname = ("result\\M00N_" + IntToStr(Year) + "-" + IntToStr(Month) + "-" + IntToStr(Day) + "_" + IntToStr(Hours) + "-" + IntToStr(Minutes) + "-" + IntToStr(Seconds) + ".log");
	ofstream myfile;
	myfile.open(fname.c_str()); //filename with calculations date
	//myfile << fstr01; // Date Start
	myfile << fstr02; // Date Calc

//---------------------------------------------------------------------------------------------//

	//Memo1->Lines->Add(""); Memo1->Lines->Add(">> Trying...");

//---------------------------------------------------------------------------------------------//

	double e, q, d, f, m, l, pi, r, t, sm, pl, ps, S0;
	double fi = 54.8206; //grades //54.823

	float YrCr[3333];
	YrCr[2000] = 63.8; YrCr[2001] = 64.0; YrCr[2002] = 64.3;
	YrCr[2003] = 64.5; YrCr[2004] = 64.6; YrCr[2005] = 64.7;
	YrCr[2006] = 64.8; YrCr[2007] = 65.2; YrCr[2008] = 65.5;
	YrCr[2009] = 65.8; YrCr[2010] = 66.0; YrCr[2011] = 66.3;
	YrCr[2012] = 66.6; YrCr[2013] = 66.9; YrCr[2014] = 67.3;
	YrCr[2015] = 67.6; YrCr[2016] = 68.1; YrCr[2017] = 68.6;
	YrCr[2018] = 69.1; YrCr[2019] = 70.0; YrCr[2020] = 70.0;

	int month[11];
	month[0]=31; month[1]=28; month[2]=31; month[3]=30; month[4]=31; month[5]=30;
	month[6]=31; month[7]=31; month[8]=30; month[9]=31; month[10]=30; month[11]=31;

//---------------------------------------------------------------------------------------------//

	int w = 24; int th = Hours; double tm = Minutes; double ts = Seconds;
	if (CheckBox1->Checked == True) { Memo1->Lines->Add("> Time : " + IntToStr(th) + ":" + FloatToStr(tm) + ":" + FloatToStr(ts)); };

	double L = 2.5085527777777777777777777777778; //2.50925; //2 + 30/60 + 30.79/3600
	if (CheckBox1->Checked == True) { Memo1->Lines->Add("> L    : " + FloatToStr(L)); };

	double ftm = tm / 60;   if (CheckBox1->Checked == True) { Memo1->Lines->Add("> ftm  : " + FloatToStr(ftm)); };
	double fts = ts / 3600; if (CheckBox1->Checked == True) { Memo1->Lines->Add("> fts  : " + FloatToStr(fts)); };

	double tt = th + ftm + fts;
	if (CheckBox1->Checked == True) { Memo1->Lines->Add("> tt   : " + FloatToStr(tt)); };

	if (Year > 2020)
	{
		YrCr[Year] = (63.8 + 0.31 * (Year - 2000));
	};

	double itt;
	itt = tt - 3;
	if (itt < 0)
	{
		itt = itt + 24;
		Day = Day - 1;
		if (Day == 0)
		{
			Month = Month - 1;
			if (Month == 0)
			{
				Year = Year - 1;
				Month = 12;
			};
			float vv = (Year / 4) * 4;
			if (Year == vv) { month[1] = 29; }
			Day = month[Month - 1];
		};
	};

	double x = -1 + ((2 * itt)) / w;
	if (CheckBox1->Checked == True) { Memo1->Lines->Add("> x    : " + FloatToStr(x)); };

//---------------------------------------------------------------------------------------------//

	double PI = get_PI(); r = 1296000; double iday = Day; double im = Month; double iyear = Year;

	// Calculate iday

	if (im != 1)
	{
	  if (IsLeap(iyear)) { month[1] = 29; };

	  for (int i = 0; i < im - 1; i++)
	  {
		iday = iday + month[i];
	  };

	} else iday = Day;

	if (CheckBox1->Checked == True) { Memo1->Lines->Add("> iday : " + FloatToStr(iday)); };

	// Calculate mean sidereal time

	iyear = Year - 1900;
	iday = (iday - 1 + int((iyear - 1) / 4));
	t = iday + iyear * 365;
	t = (t + 0.5) / 36525;
	t = t - 1;

	sm = 24110.54841 + (8640184.812866 * t) + (0.093 * t * t);

	// Calculate long- and short-period nutation

	pi = PI / 180 / 3600;

	e = pi * (84381.448 - 46.8150 * t - 0.00059 * t * t + 0.001813 * t * t * t);

	q = pi * ( 450160.280 -    5 * r * t - 482890.539 *t + 7.455 * t * t + 0.008 * t * t * t);
	d = pi * (1072261.307 + 1236 * r * t +1105601.328 *t - 6.891 * t * t + 0.019 * t * t * t);
	f = pi * ( 335778.877 + 1342 * r * t + 295263.137 *t -13.257 * t * t + 0.011 * t * t * t);
	m = pi * (1287099.804 +   99 * r * t +1292581.224 *t - 0.577 * t * t - 0.012 * t * t * t);
	l = pi * ( 485866.733 + 1325 * r * t + 715922.633 *t +31.310 * t * t + 0.064 * t * t * t);

	pl=  -(17.1996 + 0.01742 *t)*sin(q);
	pl=pl+( 0.2062 + 0.00002 *t)*sin(2*q);
	pl=pl+  0.0046              *sin(q+2*f-2*l);
	pl=pl+  0.0011              *sin(2*(l-f));
	pl=pl-  0.0003              *sin(2*(q+f-l));
	pl=pl-  0.0003              *sin(l-m-d);
	pl=pl-  0.0002              *sin(q-2*d+2*f-2*m);
	pl=pl+  0.0001              *sin(q-2*f+2*l);
	pl=pl-( 1.3187 + 0.00016 *t)*sin(2*(q-d+f));
	pl=pl+( 0.1426 - 0.00034 *t)*sin(m);
	pl=pl-( 0.0517 - 0.00012 *t)*sin(2*q-2*d+2*f+m);
	pl=pl+( 0.0217 - 0.00005 *t)*sin(2*q-2*d+2*f-m);
	pl=pl+( 0.0129 + 0.00001 *t)*sin(q-2*d+2*f);
	pl=pl+  0.0048              *sin(2*(l-d));
	pl=pl-  0.0022              *sin(2*(f-d));
	pl=pl+( 0.0017 - 0.00001 *t)*sin(2*m);
	pl=pl-  0.0015              *sin(q+m);
	pl=pl-( 0.0016 - 0.00001 *t)*sin(2*(q-d+f+m));
	pl=pl-  0.0012              *sin(q-m);
	pl=pl-  0.0006              *sin(q+2*d-2*l);
	pl=pl-  0.0005              *sin(q-2*d+2*f-m);
	pl=pl+  0.0004              *sin(q-2*d+2*l);
	pl=pl+  0.0004              *sin(q-2*d+2*f+m);
	pl=pl-  0.0004              *sin(l-d);
	pl=pl+  0.0001              *sin(2*l+m-2*d);
	pl=pl+  0.0001              *sin(q+2.*d-2*f);
	pl=pl-  0.0001              *sin(2*d-2.*f+m);
	pl=pl+  0.0001              *sin(2*q+m);
	pl=pl+  0.0001              *sin(q+d-l);
	pl=pl-  0.0001              *sin(m+2*f-2*d);

	ps=  -( 0.2274 + 0.00002 *t)*sin(2*(q+f));
	ps=ps+( 0.0712 + 0.00001 *t)*sin(l);
	ps=ps-( 0.0386 + 0.00004 *t)*sin(q+2*f);
	ps=ps-  0.0301              *sin(2*q+2*f+l);
	ps=ps-  0.0158              *sin(l-2*d);
	ps=ps+  0.0123              *sin(2*q+2*f-l);
	ps=ps+  0.0063              *sin(2*d);
	ps=ps+( 0.0063 + 0.00001 *t)*sin(q+l);
	ps=ps-( 0.0058 + 0.00001 *t)*sin(q-l);
	ps=ps-  0.0059              *sin(2*q+2*d+2*f-l);
	ps=ps-  0.0051              *sin(q+2*f+l);
	ps=ps-  0.0038              *sin(2*(q+d+f));
	ps=ps+  0.0029              *sin(2*l);
	ps=ps+  0.0029              *sin(2*q-2*d+2*f+l);
	ps=ps-  0.0031              *sin(2*(q+f+l));
	ps=ps+  0.0026              *sin(2*f);
	ps=ps+  0.0021              *sin(q+2*f-l);
	ps=ps+  0.0016              *sin(q+2*d-l);
	ps=ps-  0.0013              *sin(q-2*d+l);
	ps=ps-  0.0010              *sin(q+2*d+2*f-l);
	ps=ps-  0.0007              *sin(l+m-2*d);
	ps=ps+  0.0007              *sin(2*q+2*f+m);
	ps=ps-  0.0007              *sin(2*q+2*f-m);
	ps=ps-  0.0008              *sin(2*q+2*d+2*f+l);
	ps=ps+  0.0006              *sin(2*d+l);
	ps=ps+  0.0006              *sin(2*(q-d+f+l));
	ps=ps-  0.0006              *sin(q+2*d);
	ps=ps-  0.0007              *sin(q+2*d+2*f);
	ps=ps+  0.0006              *sin(q-2*d+2*f+l);
	ps=ps-  0.0005              *sin(q-2*d);
	ps=ps+  0.0005              *sin(l-m);
	ps=ps-  0.0005              *sin(q+2*f+2*l);
	ps=ps-  0.0004              *sin(m-2*d);
	ps=ps+  0.0004              *sin(l-2*f);
	ps=ps-  0.0004              *sin(d);
	ps=ps-  0.0003              *sin(l+m);
	ps=ps+  0.0003              *sin(l+2*f);
	ps=ps-  0.0003              *sin(2*q+2*f-m+l);
	ps=ps-  0.0003              *sin(2*q+2*d+2*f-m-l);
	ps=ps-  0.0002              *sin(q-2*l);
	ps=ps-  0.0003              *sin(2*q+2*f+3*l);
	ps=ps-  0.0003              *sin(2*q+2*d+2*f-m);
	ps=ps+  0.0002              *sin(2*q+2*f+m+l);
	ps=ps-  0.0002              *sin(q-2*d+2*f-l);
	ps=ps+  0.0002              *sin(q+2*l);
	ps=ps-  0.0002              *sin(2*q+l);
	ps=ps+  0.0002              *sin(3*l);
	ps=ps+  0.0002              *sin(2*q+d+2*f);
	ps=ps+  0.0001              *sin(2*q-l);
	ps=ps-  0.0001              *sin(m-4*d);
	ps=ps+  0.0001              *sin(2*(q+d+f-l));
	ps=ps-  0.0002              *sin(2*q+4*d+2*f-l);
	ps=ps-  0.0001              *sin(2*l-4*d);
	ps=ps+  0.0001              *sin(2*q-2*d+2*f+m+l);
	ps=ps-  0.0001              *sin(q+2.*d+2*f+l);
	ps=ps-  0.0001              *sin(2*q+4*d+2*f-2*l);
	ps=ps+  0.0001              *sin(2*q+4*f-l);
	ps=ps+  0.0001              *sin(l-m-2*d);
	ps=ps+  0.0001              *sin(q-2*d+2*f+2*l);
	ps=ps-  0.0001              *sin(2*(q+d+f+l));
	ps=ps-  0.0001              *sin(q+2*d+l);
	ps=ps+  0.0001              *sin(2*q-2*d+4*f);
	ps=ps+  0.0001              *sin(2*q-2*d+2*f+3*l);
	ps=ps-  0.0001              *sin(l+2*f-2*d);
	ps=ps+  0.0001              *sin(q+2*f+m);
	ps=ps+  0.0001              *sin(q+2*d-m-l);
	ps=ps-  0.0001              *sin(q-2*f);
	ps=ps-  0.0001              *sin(2*q-d+2*f);
	ps=ps-  0.0001              *sin(2*d+m);
	ps=ps-  0.0001              *sin(l-2*f-2*d);
	ps=ps-  0.0001              *sin(q+2*f-m);
	ps=ps-  0.0001              *sin(q-2*d+m+l);
	ps=ps-  0.0001              *sin(l-2*f+2*d);
	ps=ps+  0.0001              *sin(2*(l+d));
	ps=ps-  0.0001              *sin(2*q+4*d+2*f);
	ps=ps+  0.0001              *sin(d+m);

	// Calculate true sidereal time

	S0 = sm + ((pl + ps) / 15) * cos(e);

	while (S0 > 86400) { S0 = S0 - 86400; };
	while (S0 < 0    ) { S0 = S0 + 86400; };

	Memo1->Lines->Add("> S0   : " + FloatToStr(S0));

	int ih = int(S0 / 3600);
	int min = int((S0 - ih * 3600) / 60);
	int sec = int(S0 - ih * 3600 - min * 60);

	Memo1->Lines->Add("> time : " + IntToStr(ih) + ":" + IntToStr(min) + ":" + IntToStr(sec));

	if (CheckBox1->Checked == True)
	{
		Memo1->Lines->Add("");
		Memo1->Lines->Add("> Pi : " + FloatToStr(PI));
		Memo1->Lines->Add("> pi : " + FloatToStr(pi));
		Memo1->Lines->Add("> e  : " + FloatToStr(e));
		Memo1->Lines->Add("> q  : " + FloatToStr(q));
		Memo1->Lines->Add("> d  : " + FloatToStr(d));
		Memo1->Lines->Add("> f  : " + FloatToStr(f));
		Memo1->Lines->Add("> m  : " + FloatToStr(m));
		Memo1->Lines->Add("> l  : " + FloatToStr(l));
		Memo1->Lines->Add("> pl : " + FloatToStr(pl));
		Memo1->Lines->Add("> ps : " + FloatToStr(ps));
		Memo1->Lines->Add("> sm : " + FloatToStr(sm));
		Memo1->Lines->Add("");
	};

//---------------------------------------------------------------------------------------------//

	ifstream file;
	file.open("ae_d5.txt");

	double A[6], D[6], P[6], R[6];

	if (!file)
	{
		ShowMessage("Make sure 'ae_d5.txt' is in the same folder with main executable file!");
		Memo1->Lines->Add("");
		Memo1->Lines->Add(">>> Following calculations are broken because there is no file 'ae_d5.txt' containing data for polynomes :");
		Memo1->Lines->Add("");
	}
	else
	{
		UnicodeString Mn = IntToStr(Month);
		if (Mn == "1") { Mn = " 1"; };	if (Mn == "2") { Mn = " 2"; }; if (Mn == "3") { Mn = " 3"; };
		if (Mn == "4") { Mn = " 4"; };  if (Mn == "5") { Mn = " 5"; }; if (Mn == "6") { Mn = " 6"; };
		if (Mn == "7") { Mn = " 7"; }; 	if (Mn == "8") { Mn = " 8"; }; if (Mn == "9") { Mn = " 9"; };

		UnicodeString Dy = IntToStr(Day);
		if (Dy == "1") { Dy = " 1"; };	if (Dy == "2") { Dy = " 2"; }; if (Dy == "3") { Dy = " 3"; };
		if (Dy == "4") { Dy = " 4"; };  if (Dy == "5") { Dy = " 5"; }; if (Dy == "6") { Dy = " 6"; };
		if (Dy == "7") { Dy = " 7"; }; 	if (Dy == "8") { Dy = " 8"; }; if (Dy == "9") { Dy = " 9"; };

		UnicodeString unicodeLine = IntToStr(Year) + "  " + Mn + "  " + Dy;
		std::string stdLine(AnsiString(unicodeLine).c_str());
		std::string stdFile;

		char line[84];

		int cnt = 0; int arn = 0;
		bool fnd = false;

		while (!file.eof())
		{
			file.getline(line, 84);

			stdFile = line;
			size_t found = stdFile.find(stdLine);

			if (found != std::string::npos) { fnd = true; };

			if (fnd == true) { cnt++; };

			if ((fnd == true) && (cnt <= 5))
			{
				if (CheckBox1->Checked == True) { Memo1->Lines->Add("> " + IntToStr(cnt) + ": " + line); };
				if (cnt > 1)
				{
					char *pch = strtok(line, " ADPR");
					while (pch != NULL)
					{
						if (arn <= 5) { A[arn] = atof(pch); };
						if ((arn >= 6) && (arn < 12)) { D[arn-6] = atof(pch); };
						if ((arn >= 12) && (arn < 18)) { P[arn-12] = atof(pch); };
						if ((arn >= 18) && (arn <= 23)) { R[arn-18] = atof(pch); };
						arn++;
						pch = strtok (NULL, " ADPR");
					};
				};
			};
		};

		if (CheckBox1->Checked == True)
		{
			Memo1->Lines->Add("");
			for (int i = 0; i < 6; i++) { Memo1->Lines->Add("> A[" + IntToStr(i) + "] = " + FloatToStr(A[i])); };

			Memo1->Lines->Add("");
			for (int i = 0; i < 6; i++) { Memo1->Lines->Add("> D[" + IntToStr(i) + "] = " + FloatToStr(D[i])); };

			Memo1->Lines->Add("");
			for (int i = 0; i < 6; i++) { Memo1->Lines->Add("> P[" + IntToStr(i) + "] = " + FloatToStr(P[i])); };

			Memo1->Lines->Add("");
			for (int i = 0; i < 6; i++) { Memo1->Lines->Add("> R[" + IntToStr(i) + "] = " + FloatToStr(R[i])); };
			Memo1->Lines->Add("");
		};
	};

	file.close();

	double T[6];

	for (int n = 0; n <= 5; n++)
	{
		if (n == 0) { T[n] = 1; };
		if (n == 1) { T[n] = x; };
		T[n + 1] = 2 * x * T[n] - T[n - 1];
	};

	//Memo1->Lines->Add("");

	if (CheckBox1->Checked == True) { for (int i = 0; i < 6; i++) { Memo1->Lines->Add("> T[" + IntToStr(i) + "] = " + FloatToStr(T[i])); }; };

	double yA[6], yD[6], yP[6], yR[6];
	double sA = 0, sD = 0, sP = 0, sR = 0;
	double sAA, sAH, sAm, sAM, sAS, sDG, sDm, sDM, sDs, sDS;

	for (int i = 0; i <= 5; i++)
	{
		yA[i] = A[i] * T[i];
		sA = sA + yA[i];
		yD[i] = D[i] * T[i];
		sD = sD + yD[i];
		yP[i] = P[i] * T[i];
		sP = sP + yP[i];
		yR[i] = R[i] * T[i];
		sR = sR + yR[i];
	};

	sAA = sA / 15;
	sAH = int(sAA);
	sAm = (sAA - sAH) * 60;
	sAM = int(sAm);
	sAS = int((sAm - sAM) * 60);

	sDG = int(sD);
	sDm = (sD - sDG) * 60;
	sDM = int(sDm);
	sDs = (sDm - sDM) * 60;
	sDS = int(sDs);

	if (CheckBox1->Checked == True)
	{
		Memo1->Lines->Add("");
		for (int i = 0; i < 6; i++) { Memo1->Lines->Add("> yA[" + IntToStr(i) + "] = " + FloatToStr(yA[i])); };
		Memo1->Lines->Add("");
		for (int i = 0; i < 6; i++)	{ Memo1->Lines->Add("> yD[" + IntToStr(i) + "] = " + FloatToStr(yD[i])); };
		Memo1->Lines->Add("");
		for (int i = 0; i < 6; i++) { Memo1->Lines->Add("> yP[" + IntToStr(i) + "] = " + FloatToStr(yP[i])); };
		Memo1->Lines->Add("");
		for (int i = 0; i < 6; i++) { Memo1->Lines->Add("> yR[" + IntToStr(i) + "] = " + FloatToStr(yR[i])); };

		Memo1->Lines->Add("");
		Memo1->Lines->Add("> sA : " + FloatToStr(sA));
		Memo1->Lines->Add("> sD : " + FloatToStr(sD));
		Memo1->Lines->Add("> sP : " + FloatToStr(sP));
		Memo1->Lines->Add("> sR : " + FloatToStr(sR));

		Memo1->Lines->Add("> sAHMS : " + FloatToStr(sAH) + ":" + FloatToStr(sAM) + ":" + FloatToStr(sAS));
		Memo1->Lines->Add("> sDGMS : " + FloatToStr(sDG) + "°" + FloatToStr(sDM) + "'" + FloatToStr(sDS) + "''");
	};

//---------------------------------------------------------------------------------------------//
/*
	if (CheckBox2->Checked == True) // Calculate Culmination
	{
		double MC, SC, SSC, atC, ttC, xC, sAC, sDC, t0C, wC, TC[6], yAC[6], yDC[6], yPC[6], ZK, dU, dtU, hC, ttCX;
		double CS, CE, MMC, ttCH, ttCm, ttCM, ttCS, sACH, sACm, sACM, sACS, sDCG, sDCM, sDCS, sDCm, sDCs, sCP;

		MC = 0; SC = 0; SSC = 0; atC = 0; ttC = 0; xC = 0; sAC = 0; sDC = 0; t0C = 0; wC = 24;

		for (int i = 0; i <= 24000000; i++)
		{
			MMC = ttC - 3;
			xC = (-1 + ((2 * (MMC - t0C)) / wC));

			sAC = 0; sDC = 0; sCP = 0;

			for (int n = 0; n <= 5; n++)
			{
				if (n == 0) { TC[n] = 1;        };
				if (n == 1) { TC[n] = xC;       };
				TC[n+1] = 2 * xC * TC[n] - TC[n-1];

				yAC[n] = A[n] * TC[n]; //A-lpha for moment of culmination
				sAC = sAC + yAC[n];
				yDC[n] = D[n] * TC[n]; //D-elta
				sDC = sDC + yDC[n];
				yPC[n] = P[n] * TC[n]; //P-arralax
				sCP = sCP + yPC[n];
			};

			MC = ttC - 3 + L;
			MC = MC * 3600;
			SC = S0 - ((L * 3600) * 0.00273790972) + (MC * 1.00273790972); //sec
			SSC = (SC * 15) / 3600;								           //grades
			atC = SSC - sAC;

			ttC = ttC + 0.000001;

			if (i == 0)
			{
				CS = atC;
			};
			if ((fabs(atC) >= 360) || ((atC >= -0.0001) && (atC <= 0.0001)))
			{
				if (atC >=  360) { atC = atC - 360; };
				if (atC <= -360) { atC = atC + 360; };

				ttCX = ttC + (YrCr[Year] / 3600);
				ttCH = int(ttCX);
				ttCm = (ttC - ttCH) * 60;
				ttCM = int(ttCm);
				ttCS = int((ttCm - ttCM) * 60);
				Memo1->Lines->Add("");
				Memo1->Lines->Add("> Culmination : " + FloatToStr(atC));
				Memo1->Lines->Add("> sAC         : " + FloatToStr(sAC));

				sAC = sAC / 15;
				sACH = int(sAC);
				sACm = (sAC - sACH) * 60;
				sACM = int(sACm);
				sACS = int((sACm - sACM) * 60);
				Memo1->Lines->Add("> sACHMS      : " + FloatToStr(sACH) + ":" + FloatToStr(sACM) + ":" + FloatToStr(sACS));
				Memo1->Lines->Add("> sDC         : " + FloatToStr(sDC));

				sDCG = int(sDC);
				sDCm = (sDC - sDCG) * 60;
				sDCM = int(sDCm);
				sDCs = (sDCm - sDCM) * 60;
				sDCS = int(sDCs);
				Memo1->Lines->Add("> sDCGMS      : " + FloatToStr(sDCG) + "°" + FloatToStr(sDCM) + "'" + FloatToStr(sDCS) + "''");
				Memo1->Lines->Add("> ttC         : " + FloatToStr(ttC));
				Memo1->Lines->Add("> ttCHMS      : " + FloatToStr(ttCH) + ":" + FloatToStr(ttCM) + ":" + FloatToStr(ttCS));

				ZK = fi - sDC;
				hC = 90 - fi + sDC;
				ZK = ZK * (PI / 180); //rad
				dU = (1 / (15 * cos(sDC * (PI / 180))) * ((28.9 * cos(ZK)) + (1.1 * sin(ZK)) + 0.4));
				dtU = 0.99727 * dU;
				Memo1->Lines->Add("> dtU         : " + FloatToStr(dtU));

				double deC = - (sCP * ((sin(fi * (PI / 180)) * cos(sDC * (PI / 180)))) - (cos(fi * (PI / 180)) * sin(sDC * (PI / 180))));
				Memo1->Lines->Add("> deC         : " + FloatToStr(deC));
				Memo1->Lines->Add("");

				UnicodeString uLine08 = "Culmination : " + FloatToStr(atC) + "\n" + "R.A.: " + FloatToStr(sACH) + ":" + FloatToStr(sACM) + ":" + FloatToStr(sACS) + "\n" + "Dec.: " + FloatToStr(sDCG) + "°" + FloatToStr(sDCM) + "'" + FloatToStr(sDCS) + "''" + "\n" + "C-T : " + FloatToStr(ttCH) + ":" + FloatToStr(ttCM) + ":" + FloatToStr(ttCS) + "\n" + "dtU : " + FloatToStr(dtU) + "\n" + "h-C : " + FloatToStr(hC) + "\n" + "deC : " + FloatToStr(deC) + "\n\n";
				std::string fstr08(AnsiString(uLine08).c_str());
				myfile << fstr08; // Culmination
				break;
			};
			if (i == 24000000)
			{
				CE = atC;
				Memo1->Lines->Add("");
				Memo1->Lines->Add(">> No Moon Culmination :(");
				Memo1->Lines->Add(">> C-Start : " + FloatToStr(CS));
				Memo1->Lines->Add(">> C-End   : " + FloatToStr(CE));
				Memo1->Lines->Add("");
				UnicodeString uLine07 = "No Moon Culmination. C-Start : " + FloatToStr(CS) + ". C-End : " + FloatToStr(CE) + "\n\n";
				std::string fstr07(AnsiString(uLine07).c_str());
				myfile << fstr07; // sum R
			};
		};
	};
*/
//---------------------------------------------------------------------------------------------//

	double M = tt - 3 + L;
	if (CheckBox1->Checked == True) { Memo1->Lines->Add("> M    : " + FloatToStr(M)); };

	M = M * 3600;
	if (CheckBox1->Checked == True) { Memo1->Lines->Add("> M*   : " + FloatToStr(M)); };

	double S = S0 - ((L / 24) * 236.5554) + (M * 1.00273790972); //sec
	if (CheckBox1->Checked == True) { Memo1->Lines->Add("> S    : " + FloatToStr(S)); };

	double SS = (S * 15) / 3600; //grades
	if (CheckBox1->Checked == True) { Memo1->Lines->Add("> SS   : " + FloatToStr(SS)); };

	double at = SS - sA; //grades
	if (at >= 360) { at = at - 360; }; if (at <= -360) { at = at + 360; };
	if (CheckBox1->Checked == True) { Memo1->Lines->Add("> at   : " + FloatToStr(at)); };

	double atR = at * (PI / 180);
	if (CheckBox1->Checked == True) { Memo1->Lines->Add("> atR  : " + FloatToStr(atR)); };

	double fiR = fi * (PI / 180);
	if (CheckBox1->Checked == True) { Memo1->Lines->Add("> fiR  : " + FloatToStr(fiR)); };

	double sDR = sD * (PI / 180);
	if (CheckBox1->Checked == True) { Memo1->Lines->Add("> sDR  : " + FloatToStr(sDR)); };

	// Parallax coord. corr.

	double alW = - (sP * cos(fiR) * sin(atR) / cos(sDR));
	if (CheckBox1->Checked == True) { Memo1->Lines->Add("> alW  : " + FloatToStr(alW)); };
	UnicodeString uLine10 = "Parallax A : " + FloatToStr(alW) + "\n";
	std::string fstr10(AnsiString(uLine10).c_str());
	myfile << fstr10; // Parallax A

	double deW = - (sP * ((sin(fiR) * cos(sDR)) - (cos(fiR) * sin(sDR) * cos(atR))));
	if (CheckBox1->Checked == True) { Memo1->Lines->Add("> deW  : " + FloatToStr(deW)); };
	UnicodeString uLine11 = "Parallax D : " + FloatToStr(deW) + "\n\n";
	std::string fstr11(AnsiString(uLine11).c_str());
	myfile << fstr11; // Parallax D

	//sDR = sDR - (deW * (PI/180));
	if (CheckBox1->Checked == True) { Memo1->Lines->Add("> sDR- : " + FloatToStr(sDR)); };

	//atR = atR - (alW * (PI/180));
	if (CheckBox1->Checked == True) { Memo1->Lines->Add("> atR- : " + FloatToStr(atR)); };

	//

	double Z = (sin(fiR) * sin(sDR)) + (cos(fiR) * cos(sDR) * cos(atR)); //zenith distance
	Memo1->Lines->Add("> Z    : " + FloatToStr(Z));

	double h = 90 - (acos(Z) * (180 / PI));
	Memo1->Lines->Add("> h    : " + FloatToStr(h));

	double Z0 = acos(Z);
	if (CheckBox1->Checked == True) { Memo1->Lines->Add("> Z0   : " + FloatToStr(Z0)); };

	double dU;
	dU = (1 / (15 * cos(sDR * (PI / 180))) * ((28.9 * cos(Z0)) + (1.1 * sin(Z0)) + 0.4));
	if (CheckBox1->Checked == True) { Memo1->Lines->Add("> dU   : " + FloatToStr(dU)); };

	double dtU = 0.99727 * dU;
	if (CheckBox1->Checked == True) { Memo1->Lines->Add("> dtU  : " + FloatToStr(dtU)); };

	double Az1 = (cos(sDR) * sin(atR)) / sin(Z0);
	Memo1->Lines->Add("> Az1  : " + FloatToStr(Az1));

	double Az2 = (sin(fiR) * cos(sDR) * cos(atR) - cos(fiR) * sin(sDR)) / sin(Z0);
	if (CheckBox1->Checked == True) { Memo1->Lines->Add("> Az2  : " + FloatToStr(Az2)); };

	double Az;
	if ((Az1 < 0) && (Az2 > 0)) { Az = asin(Az1) * (180 / PI) + 360; };
	if ((Az1 < 0) && (Az2 < 0)) { Az = asin(Az1) * (180 / PI) + 270; };
	if ((Az1 > 0) && (Az2 > 0)) { Az = asin(Az1) * (180 / PI);       };
	if ((Az1 > 0) && (Az2 < 0)) { Az = asin(Az1) * (180 / PI) + 90;  };

	Memo1->Lines->Add(""); Memo1->Lines->Add("> Az   : " + FloatToStr(Az));

	UnicodeString uLine03 = "R.A. : " + FloatToStr(sAH) + ":" + FloatToStr(sAM) + ":" + FloatToStr(sAS) + "\n";
	std::string fstr03(AnsiString(uLine03).c_str());
	myfile << fstr03; // sum Alpha
	UnicodeString uLine04 = "Dec. : " + FloatToStr(sDG) + "°" + FloatToStr(sDM) + "'" + FloatToStr(sDS) + "''" + "\n";
	std::string fstr04(AnsiString(uLine04).c_str());
	myfile << fstr04; // sum Delta
	UnicodeString uLine05 = "Prl. : " + FloatToStr(sP) + "\n";
	std::string fstr05(AnsiString(uLine05).c_str());
	myfile << fstr05; // sum P
	UnicodeString uLine06 = "R    : " + FloatToStr(sR) + "\n\n";
	std::string fstr06(AnsiString(uLine06).c_str());
	myfile << fstr06; // sum R
	UnicodeString uLine12 = "H : " + FloatToStr(h) + "\n";
	std::string fstr12(AnsiString(uLine12).c_str());
	myfile << fstr12; // h
	UnicodeString uLine13 = "A : " + FloatToStr(Az) + "\n\n";
	std::string fstr13(AnsiString(uLine13).c_str());
	myfile << fstr13; // Z
	UnicodeString uLine14 = "dU  : " + FloatToStr(dU) + "\n";
	std::string fstr14(AnsiString(uLine14).c_str());
	myfile << fstr14; // dU
	UnicodeString uLine15 = "dtU : " + FloatToStr(dtU);
	std::string fstr15(AnsiString(uLine15).c_str());
	myfile << fstr15; // dtU

	Memo1->Lines->Add(""); Memo1->Lines->Add(">> Completed.");

	myfile.close();

	Memo1->Lines->SaveToFile("msgs.log");
};

//---------------------------------------------------------------------------------------------//

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	Application->Terminate();
};

//---------------------------------------------------------------------------------------------//

