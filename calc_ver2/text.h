#pragma once
#include<fstream>
using namespace std;

class text {
public:
    text();
	void read_text();
	void write_text( string target_code, double corr);
	void closefile();
	string default_code;
	string startDate;
	string endDate;
	string read_str;
	ifstream inFile;
	ofstream outFile;
};