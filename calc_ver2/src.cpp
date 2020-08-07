#include<iostream>
#include<string>
#include<cmath>
#include"DB.h"
#include"text.h"
using namespace std;

int main() {
	double multiplyXYSigma = 0;
	double xSigma = 0;
	double ySigma = 0;
	double xPowSigma=0;
	double yPowSigma =0;
	double numerator = 1; // 분자
	double divide = 1; //분모
	double corr = 0;		//결과

	double min;
	double max;

	int default_cnt = 0;
	int target_cnt = 0;
	int i = 0;
	int index = 0;
	DB calDB;
	text caltext;
	string target_code = "";

	cout << "start calc corr" << endl;

	default_cnt = calDB.get_dataCount(caltext.default_code, caltext.startDate, caltext.endDate);
	double* default_data = new double[default_cnt];
	calDB.req_data(caltext.default_code, caltext.startDate, caltext.endDate);

	for (i = 0; calDB.get_data() != NULL; i++) {
		default_data[i] = (double)atoi(calDB.sql_row[0]);
		if (i == 0) {
			max = default_data[0];
			min = default_data[0];
		}
		else {
			default_data[i] > max ? max = default_data[i] : 0;
			default_data[i] < min ? min = default_data[i] : 0;
		}
	}
	
	for (i = 0; i < default_cnt; i++) { // 정규화
		default_data[i] = ((default_data[i] - min) / (max - min));
	}

	for (i = 0; i < calDB.code_cnt; i++) {
		caltext.read_text();
		target_code = caltext.read_str;
		target_cnt = calDB.get_dataCount(target_code, caltext.startDate, caltext.endDate);

		if (target_cnt == default_cnt) {
			//cout << target_code << " " << target_cnt << endl;
			double* target_data = new double[target_cnt];
			calDB.req_data(target_code, caltext.startDate, caltext.endDate);

			for (index = 0; calDB.get_data() != NULL; index++) {
				target_data[index] = (double)atoi(calDB.sql_row[0]);
				if (index == 0) {
					max = target_data[0];
					min = target_data[0];
				}
				else {
					target_data[index] > max ? max = target_data[index] : 0;
					target_data[index] < min ? min = target_data[index] : 0;
				}
			}
			multiplyXYSigma = 0;
			xSigma = 0;
			ySigma = 0;
			xPowSigma = 0;
			yPowSigma = 0;
			for (index = 0; index < target_cnt; index++) { // 정규화
				target_data[index] = ((target_data[index] - min) / (max - min));

				multiplyXYSigma += default_data[index] * target_data[index];
				xSigma += default_data[index];
				ySigma += target_data[index];
				xPowSigma += default_data[index] * default_data[index];
				yPowSigma += target_data[index] * target_data[index];

				//cout << target_code <<"  "<< multiplyXYSigma << endl;
			}
			divide = sqrt(((default_cnt * xPowSigma) - (xSigma * xSigma)) * ((target_cnt * yPowSigma) - (ySigma * ySigma)));
			numerator = (default_cnt * multiplyXYSigma) - (xSigma * ySigma);
			corr = numerator / divide;
			if (isnan(corr)) { corr = 0; }
			delete[] target_data;
		}
		else {
			corr = 0;
		}
		if (corr > 0.7) {
			//printf("%s %lf\n", target_code.c_str(), corr);
			caltext.write_text(target_code, corr);
		}

		cout << (i+1) << "/"<< calDB.code_cnt <<endl;

	}

	cout << "finish calc corr" << endl;

	delete[] default_data;
	caltext.closefile();
	calDB.close();
	system("pause");

	return 0;
}