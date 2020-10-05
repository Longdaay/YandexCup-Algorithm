#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Topology {
public:
	Topology();
	void setCompsConnections();
	void printConnections();
    void Dijkstra(int st);
private:
	int countComps;
	vector <vector<int>> CompsConnections;
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
	while (iter < countComps - 1) {
		CompsConnections[iter].resize(countComps);
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
		CompsConnections[CompConnection[0] - 1][CompConnection[1] - 1] = 1;
		CompsConnections[CompConnection[1] - 1][CompConnection[0] - 1] = 1;
		
		iter++;
	}
	in.close();
}

void Topology::Dijkstra(int st)
{
    vector<bool> visited;
	visited.resize(countComps);
    vector<int> D;
	D.resize(countComps);
    for (int i = 0; i < countComps; i++)
    {
        D[i] = CompsConnections[st][i];
        visited[i] = false;
    }
    D[st] = 0;
    int index = 0, u = 0;
    for (int i = 0; i < countComps; i++)
    {
        int min = INT_MAX;
        for (int j = 0; j < countComps; j++)
        {
            if (!visited[j] && D[j] < min)
            {
                min = D[j];
                index = j;
            }
        }
        u = index;
        visited[u] = true;
        for (int j = 0; j < countComps; j++)
        {
            if (!visited[j] && CompsConnections[u][j] != INT_MAX && D[u] != INT_MAX && (D[u] + CompsConnections[u][j] < D[j]))
            {
                D[j] = D[u] + CompsConnections[u][j];
            }
        }
    }
    cout << "Стоимость пути из начальной вершины до остальных(Алгоритм Дейкстры):\t\n";
    for (int i = 0; i < countComps; i++)
    {
        if (D[i] != INT_MAX)
            cout << st << " -> " << i << " = " << D[i] << endl;
        else
            cout << st << " -> " << i << " = " << "маршрут недоступен" << endl;
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
	Topology tp;
	tp.printConnections();
	cout << endl;
	//tp.Dijkstra(0);
	return 0;
}