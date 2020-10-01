#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <set>

using namespace std;

class BigData {
public:
	BigData();
	vector < int> getVecFile(ifstream& in);
	void fillSpeadsheet();
	unsigned long long int getSumm() { return summ; }
	void findmax();
	bool checkForEqual();
private:
	vector< int> a_vec;										// 1 ������
	vector< int> b_vec;									   // 2 ������
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
}

unsigned long long int summ_elem(vector<unsigned long long int>& vec) { // ������������ ���� �����/��������
	unsigned long long int summ = 0;								   //
	for (auto& token : vec)											  //
		summ += token;												 //
	return summ;													// ���������� ���������� �����
}

int maximum(vector<int>& vec) {					// ����� ������������� ����� � ������� �����/��������. ���������� ��� ������
	int max = vec[0];												  // ������ ��������� - ������ ��������
	int iter = 0;												 // ���������� ��� ������ ������� ���������
	for (int i = 0; i < vec.size(); i++) {					    //	
		if (vec[i] > max) {									   // ���� ����� ������ ���
			iter = i;										  // ���������� ��� ������
			max = vec[i];								     // ���������� ��� ����� � ���
		}												    //
	}													   //
	return iter;										  // ���������� ������
}

vector<int> getIndexMaxValues(vector<int>& vec, int& index) {//
	int maxValueVec = vec[index];
	vector<int> vecIndexMaxValues;
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] == maxValueVec)
			vecIndexMaxValues.push_back(i);
	}
	return vecIndexMaxValues;
}

bool BigData::checkForEqual() {
	set<int> setEqualRow;
	set<int> setEqualColumn;
	for (auto& token : a_vec)
		setEqualRow.insert(token);
	for (auto& token : b_vec)
		setEqualColumn.insert(token);
	if (setEqualRow.size() == 1 && setEqualColumn.size() == 1)
		return true;
	else
		return false;
}

void BigData::findmax() {																								     // ����� ������������ �����
	int StopColumn, StopRow;																									    // ���������� "�����/��������-�������������"
	vector<int> vecIndexStopRow;//
	int i = 0;																											   // ������
	int j = 0;																											  // �������
	StopColumn = maximum(b_vec);																						 // ����� ������� ��� ������
	StopRow = maximum(a_vec);																						    // ����� ������� ��� ������
	vecIndexStopRow = getIndexMaxValues(a_vec, StopRow);//
	
	if (checkForEqual()) {																			// �������� ������� �� ������ ��������� ���� ����� ���� ��������� �������� �� ���������� ����� �������� ����� �������� 
		summ = spreadsheet[0][0] * ((a_vec.size() + b_vec.size()) - 1);					   // ����������� ����� �� �������
		return;																					  // �������
	}																							 //
	unsigned long long int curr_summ = 0;
	for (int step = 0; step < vecIndexStopRow.size(); step++) {
		StopRow = vecIndexStopRow[step];
		while (i != StopRow) {
			curr_summ += spreadsheet[i][j];
			i++;
		}
		while (j != StopColumn) {
			curr_summ += spreadsheet[i][j];
			j++;
		}
	}
	if (StopColumn == j && StopRow == i) {
		while (j != b_vec.size()) {
			curr_summ += spreadsheet[i][j];
			j++;
		}
		j--;
		i++;
		while (i != a_vec.size()) {
			curr_summ += spreadsheet[i][j];
			i++;
		}
		summ = curr_summ;
		return;
	}
}

int main() {
	BigData bd;						// ��������� ������
	bd.findmax();				   // ����� �������������
	cout << bd.getSumm();		  // ������� �����
	return 0;
}


