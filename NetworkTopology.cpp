#include <iostream>
#include <vector>
#include <fstream>
#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>

using namespace std;

class Topology {
public:
	Topology();
	void setCompsConnections();
	void printConnections();
    int Dijkstra(int st);
    void checkAllComps();
    void printSumms();
    vector <int> findMaxCountConnections();
    void printStorage();
private:
	int countComps;
	vector <vector<int>> CompsConnections;
    vector <vector<int>> summComps;
    vector <int> CompStorage;
};

Topology::Topology() {       // �����������
	setCompsConnections();  //
}
void Topology::setCompsConnections() {                                             // �������� �� ����� ���������� �����
	ifstream in;                                                                  // �����
	in.open("input.txt");                                                        // �������� ����
	vector<int> CompConnection;                                                 // ������ ��� ������ ����������
	int temp;                                                                  // ���������� ����
	char t;                                                                   //
	int iter = 0;                                                            // ��������
	in >> countComps;                                                       // �������� ���������� �����

	CompsConnections.resize(countComps);                                  // ��������� ������� ��������� �����
	for (int i = 0; i < countComps; i++)                                 //
		CompsConnections[i].resize(countComps);                         //

	while (iter < countComps - 1) {                                    // ���� �� ����� �� ��������� ����������
		CompConnection.clear();                                       //
		in >> temp;                                                  // ��������� ������ ����
		CompConnection.push_back(temp);                             //  � ������
		in.get(t);                                                 // ��������� ������
		while (t != '\n') {                                       // ���� ������ �� ����� ������
			if (!in.eof()) {                                     // ���� �� �������� ����� �����
				in >> temp;                                     // ��������� ������ ����
				CompConnection.push_back(temp);                // � ������
				in.get(t);                                    // ��������� ������
			}
			else                                            // �����
				t = '\n';                                  // ����������� ����� ������
		}

		int first = CompConnection[0] - 1;               // ������ �������
		int second = CompConnection[1] - 1;             // ������ �������
		CompsConnections[first][second] = 1;           // ��������� ������� ���������
		CompsConnections[second][first] = 1;          //
		
		iter++;                                     // �������� � ���������
	}                                              //
	in.close();                                   //
}

int Topology::Dijkstra(int begin_index)
{
    vector <int> d;                                                                                  // ������ ���������� �� ���� ����� �� �������� ���������� ����
    d.resize(countComps);                                                                           //
    vector <int> v;                                                                                // ������ ���������� �����
    v.resize(countComps);                                                                         //
    int temp, minindex, min;                                                                     //
    int summ = 0;                                                                               //
                                                                                               // ������������� ����� � ����������
    for (int i = 0; i < countComps; i++) {                                                    //
        d[i] = 10000;                                                                        //
        v[i] = 1;                                                                           //
    }
    d[begin_index] = 0;                                                                   //
                                                                                         // ��� ���������
    do {                                                                                //
        minindex = 10000;                                                              //
        min = 10000;                                                                  //
        for (int i = 0; i < countComps; i++) {                                       // ���� ������� ��� �� ������ � ��� ������ min
            if ((v[i] == 1) && (d[i] < min)) {                                      // ��������������� ��������
                min = d[i];                                                        //
                minindex = i;                                                     //
            }
        }
                                                                               // ��������� ��������� ����������� ���
                                                                              // � �������� ���� �������
                                                                             // � ���������� � ������� ����������� ����� �������
        if (minindex != 10000) {                                            //
            for (int i = 0; i < countComps; i++) {                         //
                if (CompsConnections[minindex][i] > 0) {                  //
                    temp = min + CompsConnections[minindex][i];          //
                    if (temp < d[i])                                    //
                        d[i] = temp;                                   //
                }                                                     //
            }                                                        //
            v[minindex] = 0;                                        //
        }                                                          //
    } while (minindex < 10000);                                   //
                                                                 // ����� ���������� ���������� �� ������
 /*   printf("\n���������� ���������� �� ������: \n");
    for (int i = 1; i < countComps + 1; i++)
        printf("%5d ", i);
    cout << "\n---------------------------------\n";*/
    for (int i = 0; i < countComps; i++) {                  //
        summ += d[i];                                      //
    }                                                     //
    return summ;                                         //
}

vector<int> Topology::findMaxCountConnections() {
    vector<int> tempvec;
    vector < vector<int>> summsRows;
    int summ = 0;
    for (int i = 0; i < countComps; i++) {
        for (int j = 0; j < countComps; j++) {
            summ += CompsConnections[i][j];
        }
        tempvec.push_back(summ);
        tempvec.push_back(i);
        summsRows.push_back(tempvec);
        tempvec.clear();
        summ = 0;
    }
    sort(summsRows.begin(), summsRows.begin() + summsRows.size());
   /*for (auto& Connection : summsRows) {
        for (auto& currentComp : Connection)
            cout << currentComp << " ";
        cout << endl;
    }
    cout << endl;*/
    if (countComps == 3) {
        tempvec.push_back(summsRows[0][1]);
        tempvec.push_back(summsRows[1][1]);
        return tempvec;
    }
    while (tempvec.size() < 2) {
        summ = summsRows[summsRows.size() - 1][0];
        tempvec.push_back(summsRows[summsRows.size() - 1][1]);
        summsRows.pop_back();
        for (int i = summsRows.size() - 1; i >= 0; i--) {
            if (summ == summsRows[i][0]) {
                tempvec.push_back(summsRows[i][1]);
                summsRows.pop_back();
            }
        }
    }
    /*for (int i = 0; i < tempvec.size(); i++)
        cout << tempvec[i] << " ";
    system("pause");*/
    return tempvec;
}

void Topology::checkAllComps() {
    vector<int> tempvec;
    vector <int> CompsMaxLink;
    
    if (countComps == 3) {
        CompsMaxLink = findMaxCountConnections();
        CompStorage.push_back(CompsMaxLink[0] + 1);
        CompStorage.push_back(CompsMaxLink[1] + 1);
        return;
    }

    for (int i = 0; i < countComps; i++) {
        tempvec.push_back(Dijkstra(i));
        tempvec.push_back(i);
        summComps.push_back(tempvec);
        tempvec.clear();
    }
    sort(summComps.begin(), summComps.begin() + summComps.size());
    CompStorage.push_back(summComps[0][1] + 1);
    CompStorage.push_back(summComps[1][1] + 1);
    sort(CompStorage.begin(), CompStorage.begin() + CompStorage.size());
}

void Topology::printSumms() {
    for (auto& Connection : summComps) {
        for (auto& currentComp : Connection)
            cout << currentComp << " ";
        cout << endl;
    }
}

void Topology::printConnections() {
	for (auto& Connection : CompsConnections) {
		for (auto& currentComp : Connection)
			cout << currentComp << " ";
		cout << endl;
	}
}

void Topology::printStorage() {
    for (auto& token : CompStorage)
        cout << token << " ";
    cout << endl;
}

int main() {
	setlocale(0, "");
	Topology tp;
    tp.checkAllComps();
    tp.printStorage();
	return 0;
}