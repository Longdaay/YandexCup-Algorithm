#include <iostream>
#include <vector>
#include <fstream>
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define SIZE 9
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
private:
	int countComps;
	vector <vector<int>> CompsConnections;
    vector <vector<int>> summComps;
};

Topology::Topology() {
	setCompsConnections();
}
void Topology::setCompsConnections() {
	ifstream in;
	in.open("input.txt");
	vector<int> CompConnection;
	int temp;
	char t;
	int iter = 0;
	in >> countComps;

	CompsConnections.resize(countComps);
	for (int i = 0; i < countComps; i++)
		CompsConnections[i].resize(countComps);

	while (iter < countComps - 1) {
		CompConnection.clear();
		in >> temp;
		CompConnection.push_back(temp);
		in.get(t);
		while (t != '\n') {
			if (!in.eof()) {
				in >> temp;
				CompConnection.push_back(temp);
				in.get(t);
			}
			else
				t = '\n';
		}

		int first = CompConnection[0] - 1;
		int second = CompConnection[1] - 1;
		CompsConnections[first][second] = 1;
		CompsConnections[second][first] = 1;
		
		iter++;
	}
	in.close();
}

int Topology::Dijkstra(int begin_index)
{
    int d[SIZE]; // минимальное расстояние
    int v[SIZE]; // посещенные вершины
    int temp, minindex, min;
    int summ = 0;
    //Инициализация вершин и расстояний
    for (int i = 0; i < SIZE; i++)
    {
        d[i] = 10000;
        v[i] = 1;
    }
    d[begin_index] = 0;
    // Шаг алгоритма
    do {
        minindex = 10000;
        min = 10000;
        for (int i = 0; i < SIZE; i++)
        { // Если вершину ещё не обошли и вес меньше min
            if ((v[i] == 1) && (d[i] < min))
            { // Переприсваиваем значения
                min = d[i];
                minindex = i;
            }
        }
        // Добавляем найденный минимальный вес
        // к текущему весу вершины
        // и сравниваем с текущим минимальным весом вершины
        if (minindex != 10000)
        {
            for (int i = 0; i < SIZE; i++)
            {
                if (CompsConnections[minindex][i] > 0)
                {
                    temp = min + CompsConnections[minindex][i];
                    if (temp < d[i])
                    {
                        d[i] = temp;
                    }
                }
            }
            v[minindex] = 0;
        }
    } while (minindex < 10000);
    // Вывод кратчайших расстояний до вершин
    printf("\nКратчайшие расстояния до вершин: \n");
    for (int i = 1; i < SIZE + 1; i++)
        printf("%5d ", i);
    cout << "\n------------------------------------------\n";
    for (int i = 0; i < SIZE; i++) {
        printf("%5d ", d[i]);
        summ += d[i];
    }
    return summ;
}

void Topology::checkAllComps() {
    vector<int> tempvec;
    for (int i = 0; i < countComps; i++) {
        tempvec.push_back(Dijkstra(i));
        tempvec.push_back(i);
        summComps.push_back(tempvec);
        tempvec.clear();
    }
    sort(summComps.begin(), summComps.begin() + summComps.size());

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

int main() {
	setlocale(0, "");
	Topology tp;
	tp.printConnections();
    tp.checkAllComps();
    cout << endl;
    tp.printSumms();
    cout << endl;
	return 0;
}