#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

class ShootingRange {
public:
	ShootingRange();
	void setForms();
	bool isLineThoughtCenters();
private:
	vector<vector<double>>Forms;
	int formsCount;
};

ShootingRange::ShootingRange() {
	setForms();
}

void ShootingRange::setForms() {
	ifstream in;
	in.open("input.txt");
	vector<double> UserForm;
	int temp;
	char t;
	int iter = 0;
	in >> formsCount;
	while (iter < formsCount) {
		UserForm.clear();
		in >> temp;
		UserForm.push_back(temp);
		in.get(t);
		while (t != '\n') {
			if (!in.eof()) {
				in >> temp;
				UserForm.push_back(temp);
				in.get(t);
			}
			else
				t = '\n';
		}
		Forms.push_back(UserForm);
		iter++;
	}
	in.close();
}

bool ShootingRange::isLineThoughtCenters() {
	vector <double> tempCenter;
	vector < vector<double>> tempCenters;
	double x1, x2, y1, y2;
	double first, second, third, fourth;
	for (auto& token : Forms) {
		tempCenter.clear();
		switch (int(token[0])) {
		case 0:
			tempCenter.push_back(token[2]);
			tempCenter.push_back(token[3]);
			tempCenters.push_back(tempCenter);
			break;
		case 1:
			tempCenter.push_back((token[1] + token[5]) / 2.0);
			tempCenter.push_back((token[2] + token[6]) / 2.0);
			tempCenters.push_back(tempCenter);
			break;
		default:
			break;
		}
	}

	sort(tempCenters.begin(), tempCenters.begin() + tempCenters.size());
	if (tempCenters.size() == 1)
		return true;
	tempCenter = tempCenters[0];
	x1 = tempCenter[0];
	y1 = tempCenter[1];
	tempCenter = tempCenters[tempCenters.size() - 1];
	x2 = tempCenter[0];
	y2 = tempCenter[1];
	for (auto& token : tempCenters) {
		token[0] - x1 == 0 ? first = 1 : first = token[0] - x1;
		x2 - x1 == 0 ? second = 1 : second = x2 - x1;
		token[1] - y1 == 0 ? third = 1 : third = token[1] - y1;
		y2 - y1 == 0 ? fourth = 1 : fourth = y2 - y1;
		if ((first) / (second) != (third) / (fourth))
			return false;
	}
	return true;
}

int main() {
	ShootingRange sr;
	if (sr.isLineThoughtCenters())
		cout << "Yes\n";
	else
		cout << "No\n";
	return 0;
}