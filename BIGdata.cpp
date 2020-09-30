#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;

class BigData {
public:
	BigData();
	vector < int> getVecFile(ifstream& in);
	void fillSpeadsheet();
	void findMaxSumm(int i_offset, int j_offset, unsigned long long int curr_summ);
	unsigned long long int getSumm() { return summ; }
	void fillsumms();
	void findmax();
private:
	vector< int> a_vec;										// 1 ������
	vector< int> b_vec;									   // 2 ������
	vector <unsigned long long int> summ_row;
	vector <unsigned long long int> summ_col;
	vector<vector<unsigned long long int>> spreadsheet;	  // ������� 
	unsigned long long int summ = 0;					 // ������������ ��������� �����
};

BigData::BigData() {					// �����������
	ifstream in;					   // ��������� ����� ��� �����
	int sizeA, sizeB;				  // ���������� ��� �������� ������� � ������ 
	in.open("input.txt");			 // ��������� ����
	in >> sizeA;					// ������� ������ 1�� �������
	in >> sizeB;				   // ������� ������ 2�� �������
	a_vec = getVecFile(in);		  // �������� �� ����� 1 ������
	b_vec = getVecFile(in);		 // �������� �� ����� 2 ������
	in.close();					// ����� ���������
	fillSpeadsheet();		   // ��������� ������� ����� ���������
}

vector <int> BigData::getVecFile(ifstream& in) {	// �������� �� ����� ������ ����� (�� ���� ��������� ����� � �����) �� ����� ������ ������ ����� �� �����
	vector< int> vec;							   // ������ � ������� ������� ���� �����
	int temp;									  // ���������� ���� ����� ������������ ����� �� �����
	char t;										 // ���������� ����������	
	in >> temp;									// �������� ������ �����
	vec.push_back(temp);					   // ���������� ���
	in.get(t);							   	  // ��������� ��������� ������ � �����
	while (t != '\n') {					 	 // ���� ��� ���������� �� ������� ������ ����� ������ ���������� ���������� ����� � ������
		if (!in.eof()) {					// ���� �� �������� ����� ����� - ����������, ����� - ������� ����������� ����� ������
			in >> temp;				 	   //
			vec.push_back(temp);		  //
			in.get(t);					 //
		}								//
		else					  	   //
			t = '\n';	 			  //
	}								 //
	return vec;						//���������� ������
}



void BigData::fillSpeadsheet() {											// ��������� �������
	spreadsheet.resize(a_vec.size());									   // ��������� ������ ������� �� ����������� 1�� ������� 
	for (int i = 0; i < a_vec.size(); i++) {							  // �������� ������ �� �������
		spreadsheet[i].resize(b_vec.size());							 // ��������� ������� ������� �� ����������� 2�� �������
		for (int j = 0; j < b_vec.size(); j++) {						// �������� ������ �� ��������
			spreadsheet[i][j] = a_vec[i] * pow(10,9) + b_vec[j];	   // ��������� ������� ������� ��������� �� ������� (pow - ���������� � ������� (10 - �����, 9 - �������))
		}															  //
	}																 //
	fillsumms();
}

unsigned long long int summ_elem(vector<unsigned long long int>& vec) { // ������������ ���� �����/��������
	unsigned long long int summ = 0;								   //
	for (auto& token : vec)											  //
		summ += token;												 //
	return summ;													// ���������� ���������� �����
}

void BigData::fillsumms() {													// ��������� ����� �� �������/��������
	summ_col.resize(b_vec.size());										   // �������� ������ �������
	summ_row.resize(a_vec.size());										  // �������� ������ �������
	for (int i = 0; i < a_vec.size(); i++) {							 // ��������� ������ ���� �����
		for (int j = 0; j < b_vec.size(); j++)							//
			summ_row[i] += spreadsheet[i][j];						   //
	}																  //
	for (int j = 0; j < b_vec.size(); j++) {						 // ��������� ������ ���� ��������
		for (int i = 0; i < a_vec.size(); i++)					    //
			summ_col[j] += spreadsheet[i][j];					   //
	}														      //
}

int maximum(vector<unsigned long long int>& vec) {					// ����� ������������� ����� � ������� �����/��������. ���������� ��� ������
	unsigned long long int max;									   // ���������� ��� ���������
	max = vec[0];												  // ������ ��������� - ������ ��������
	int iter = 0;												 // ���������� ��� ������ ������� ���������
	for (int i = 0; i < vec.size(); i++) {					    //	
		if (vec[i] > max) {									   // ���� ����� ������ ���
			iter = i;										  // ���������� ��� ������
			max = vec[i];								     // ���������� ��� ����� � ���
		}												    //
	}													   //
	return iter;										  // ���������� ������
}

void BigData::findmax() {																								     // ����� ������������ �����
	int Scollumn, Srow;																									    // ���������� "�����/��������-�������������"
	int i = 0;																											   // ������
	int j = 0;																											  // �������
	Scollumn = maximum(summ_col);																						 // ����� ������� ��� ������
	Srow = maximum(summ_row);																						    // ����� ������� ��� ������
	if ((summ_elem(summ_row) + summ_elem(summ_col)) / (2 * (summ_col.size() * summ_row.size())) == spreadsheet[0][0]) {// �������� ������� �� ������ ��������� ���� ����� ���� ��������� �������� �� ���������� ����� �������� ����� �������� 
		summ = spreadsheet[0][0] * ((summ_col.size() + summ_row.size()) - 1);										  // ����������� ����� �� �������
		return;																										 // �������
	}																											    //
	unsigned long long int curr_summ = 0;
	if (Scollumn == 0 && Srow == 0) {
		while (j != b_vec.size()) {
			summ += spreadsheet[i][j];
			j++;
		}
		j--;
		i++;
		while (i != a_vec.size()) {
			summ += spreadsheet[i][j];
			i++;
		}
		return;
	}
																											  // ���� �� ������������� ����
	while (i != Srow) {																					  	 // ���� �� ����� �� ������������ ������
		curr_summ += spreadsheet[i][j];																	    // ��������� � ������� ����� �������
		i++;																							   // ���� ���� ������
	}																									  //
	while (j != Scollumn) {																				 // ���� �� ������������� ������
		curr_summ += spreadsheet[i][j];																    // ��������� � ������� ����� �������
		j++;																						   // ���� ������ ������
	}																							      //
	findMaxSumm(i, j, curr_summ);																	 // ����� ���� ��������, ���� �� �� ����� �� �����, ���������� ������� � ���
}

void BigData::findMaxSumm(int i_offset, int j_offset, unsigned long long int curr_summ) { // ����� ������������ �����. ����������� �������. i_offset - ����� ������,
																						 // j_offset - ����� �������, curr_summ - ������� ����� �� ����������� ����
	if (i_offset == a_vec.size())														// ���� ����� ������ ������ ����, �� ���� ���� ��������, ������������
		return;																		   //
	if (j_offset == b_vec.size())													  // ���� ����� ������� ������ ����, �� ���� ���� ��������, ������������
		return;																	     //
	curr_summ += spreadsheet[i_offset][j_offset];									// ��������� � ������� ����� ����������� ���� �������� �������� i-������ j-�������
	curr_summ > summ ? summ = curr_summ : summ;									   // ��������� ��������. ���� ������� ����� ����������� ���� ������ ����� ����������� ��������� - ����������� ������������ ��������. ����� - ������ �� ������ 
	findMaxSumm(i_offset + 1, j_offset, curr_summ);							      // ���� ����� �� �������, ����������� ���� (i + 1)
	findMaxSumm(i_offset, j_offset + 1, curr_summ);								 // ���� ����� �� �������, ������ ������ (j + 1)
}
int main() {
	BigData bd;						// ��������� ������
	bd.findmax();				   // ����� �������������
	cout << bd.getSumm();		  // ������� �����
	return 0;
}


