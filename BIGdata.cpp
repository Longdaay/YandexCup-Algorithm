#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <ctime>//
#include <chrono>//

using namespace std;
unsigned long long int max_value = 9 * pow(10, 9) + 9;


class BigData {
public:
	BigData();
	BigData(char name);
	vector < int> getVecFile( int& size, ifstream& in);
	vector<int> getVec(int& Size);
	void fillSpeadsheet();
	void findMaxSumm(int i_offset, int j_offset, unsigned long long int curr_summ);
	void findMaxSummopt(int i_offset, int j_offset, unsigned long long int curr_summ);
	unsigned long long int getSumm() { return summ; }
	void setsumm(unsigned long long int summ) { this->summ = summ; }
private:
	vector< int> a_vec;
	vector< int> b_vec;
	vector<vector<unsigned long long int>> spreadsheet;
	unsigned long long int summ = 0;
};

BigData::BigData() {
	ifstream in;
	 int sizeA, sizeB;
	in.open("input.txt");
	in >> sizeA;
	in >> sizeB;
	a_vec = getVecFile(sizeA, in);
	b_vec = getVecFile(sizeB, in);
	in.close();
	fillSpeadsheet();
}

BigData::BigData(char name) {
	int sizeA, sizeB;
	cin >> sizeA;
	cin >> sizeB;
	a_vec = getVec(sizeA);
	b_vec = getVec(sizeB);
	fillSpeadsheet();
}

vector<int>BigData::getVec(int& Size) {//
	vector<int> vec;
	for (int i = 0; i < Size; i++) {
		vec.push_back(rand() % 10);
	}
	return vec;
}

vector < int> BigData::getVecFile(int& size, ifstream& in) {
	vector< int> vec;
	int temp;
	char t;
	vec.clear();
	in >> temp;
	vec.push_back(temp);
	in.get(t);
	while (t != '\n') {
		if (!in.eof()) {
			in >> temp;
			vec.push_back(temp);
			in.get(t);
		}
		else
			t = '\n';
	}
	return vec;
}

void BigData::fillSpeadsheet() {
	spreadsheet.resize(a_vec.size());
	for (int i = 0; i < a_vec.size(); i++) {
		spreadsheet[i].resize(b_vec.size());
		for (int j = 0; j < b_vec.size(); j++) {
			spreadsheet[i][j] = a_vec[i] * pow(10,9) + b_vec[j];
		}
	}
}

void BigData::findMaxSumm(int i_offset, int j_offset, unsigned long long int curr_summ) {
	
	if (i_offset == a_vec.size())
		return;
	if (j_offset == b_vec.size())
		return;
	
	/*int max_steps = a_vec.size() + b_vec.size() - 2;
	int current_steps = i_offset + j_offset - 2;
	int steps_left = max_steps - current_steps;
	if (curr_summ + (steps_left * max_value) < summ)
		return;*/
	curr_summ += spreadsheet[i_offset][j_offset];
	curr_summ > summ ? summ = curr_summ : summ;
	findMaxSumm(i_offset + 1, j_offset, curr_summ);
	findMaxSumm(i_offset, j_offset + 1, curr_summ);
}

void BigData::findMaxSummopt(int i_offset, int j_offset, unsigned long long int curr_summ) {

	if (i_offset == a_vec.size())
		return;
	if (j_offset == b_vec.size())
		return;

	int max_steps = a_vec.size() + b_vec.size() - 2;
	int current_steps = i_offset + j_offset - 2;
	int steps_left = max_steps - current_steps;
	if (curr_summ + (steps_left * max_value) < summ)
		return;
	curr_summ += spreadsheet[i_offset][j_offset];
	curr_summ > summ ? summ = curr_summ : summ;
	findMaxSummopt(i_offset + 1, j_offset, curr_summ);
	findMaxSummopt(i_offset, j_offset + 1, curr_summ);
}

int main() {
	chrono::steady_clock sc;
	srand(time(0));//
	BigData bd(' ');//
	auto start = sc.now();     // устанавливаем начало отсчета времени события
	bd.findMaxSumm(0, 0, 0);
	auto end = sc.now();       // устанавливаем конец отсчета времени события
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // высчитываем время, затраченное на событи
	cout << bd.getSumm();
	cout << "\nTime: " << time_span.count() << " second" << endl << endl;

	bd.setsumm(0);
	auto start1 = sc.now();     // устанавливаем начало отсчета времени события
	bd.findMaxSumm(0, 0, 0);
	auto end1 = sc.now();       // устанавливаем конец отсчета времени события
	auto time_span1 = static_cast<chrono::duration<double>>(end1 - start1);   // высчитываем время, затраченное на событи
	cout << bd.getSumm();
	cout << "\nTime optimization: " << time_span1.count() << " second" << endl << endl;
	return 0;
}
/*
void BigData::printSheet() {
	for (auto& token : spreadsheet) {
		for (auto& elem : token) {
			cout << elem << " ";
		}
		cout << endl;
	}
}

void BigData::printVec(vector< int> vec) {
	for (auto& token : vec)
		cout << token << " ";
	cout << endl;
}
void BigData::findMaxSumm(int i_offset, int j_offset, unsigned long long int curr_summ) {
	if (i_offset == a_vec.size())
		return;
	if (j_offset == b_vec.size())
		return;
	curr_summ += spreadsheet[i_offset][j_offset];
	curr_summ > summ ? summ = curr_summ : summ;
	findMaxSumm(i_offset + 1, j_offset, curr_summ);
	findMaxSumm(i_offset, j_offset + 1, curr_summ);
}
*/