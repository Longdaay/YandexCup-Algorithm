#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Topology {
public:
	Topology();
	void setCompsConnections();
	void printConnections();
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
		CompsConnections.push_back(CompConnection);
		iter++;
	}
	in.close();
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
	return 0;
}