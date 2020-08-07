#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include"text.h"
using namespace std;

text::text() {
	ifstream inFile("./text/default_code.txt");
	text::default_code;
	text::startDate;
	text::endDate;
	if (!inFile.is_open()) {
		exit(1);
	}
	getline(inFile, default_code);
	getline(inFile, startDate);
	getline(inFile, endDate);

	inFile.close();

	text::inFile.open("./text/target_code.txt");
	text::outFile.open("./text/corr_result.txt");
	//cout << default_code;
	//cout << startDate;
	//cout << endDate;
}
void text::read_text() {
	text::read_str = "";
	
	if (!text::inFile.is_open()) {
		exit(1);
	}
	getline(text::inFile, text::read_str);
	//inFile.close();
}
void text::write_text( string target_code, double corr ) {
	string str = target_code+";"+ to_string(corr);
	if (!text::outFile.is_open()) {
		exit(1);
	}
	text::outFile << str << endl;
	
}
void text::closefile() {
	text::inFile.close();
	text::outFile.close();
}

