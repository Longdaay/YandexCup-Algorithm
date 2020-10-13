//utf-8
/*������ �. ��������� ����.
* ������� ������:
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>
#include <map>

#define MAXWEIGHTVALUE 10000

using namespace std;
int max_depth = 0;

class Topology {
public:
    Topology();
    void setComputersConnectionsMatrix();
    void checkAllComputers();
    int Dijkstra(int begin_index, int trigger);
    void checkAllpairStorage(vector<vector<int>>& potentionalStorage);
    void findPotentionalComputerStorage(vector<vector<int>>& lits_computerDepth);
private:
    int total_computers;
    vector <vector<int>> computersConnectionsMatrix;
};

Topology::Topology() {       // �����������
    setComputersConnectionsMatrix();  //
}
void Topology::setComputersConnectionsMatrix() {
    /*
    * ������ ��������� �� ���������� ����� � ���������, ��� �������� ������� ���������
    * ������� ����������� ���������� �����������, � ������ ������������ ��������� ����� ���� �����������.
    * ���������� ������ ������������ ����������� ����������� - 1. �� ����������� ������������ ������ (�.�. 1 1 � ��.) 
    * �������� ��������� ������ ���� � ��������� �� 1 �� ���������� �����������.
    * ��������� ���� ��������� �������� ���:
    * 3
    * 1 2
    * 2 3
    */
    ifstream in; // ��������� ����� ��� ���������� ������
    vector<int> CompConnection; // ������ ��� ������ ����������
    int temp, iterator = 0;
    char t;
    
    in.open("input.txt"); // �������� ����
    in >> total_computers; // �������� ���������� �����

    computersConnectionsMatrix.resize(total_computers);// ��������� ������� ��������� �����
    for (int i = 0; i < total_computers; i++)//
        computersConnectionsMatrix[i].resize(total_computers);//

    /*
    * ������ �� ����� ���������� ��������� �������: ����������� ������ �������� (���������� �����������)
    * ������ ����������� ��������� ������ ������. ����� ���������������� ����. ���� ��������� ������ �� ����� ����� �������� ������, ���������� ��������� �� ����� ����������.
    * � ����� ������������� ����������� �������� �� ����� ����� .....
    */
    while (iterator < total_computers - 1) {                                    // ���� �� ����� �� ��������� ����������
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
        computersConnectionsMatrix[first][second] = 1;           // ��������� ������� ���������
        computersConnectionsMatrix[second][first] = 1;          //

        iterator++;                                     // �������� � ���������
        CompConnection.clear();                                       //
    }                                              //
    in.close();                                   //
}


int Topology::Dijkstra(int begin_index, int trigger) {
    /*
    * �������� ��������.
    */
    vector <int> countSteps_computerToAll;                                                                             // ������ ���������� �� ���� ����� �� �������� ���������� ����
    countSteps_computerToAll.resize(computersConnectionsMatrix.size());                                                                           //
    vector <int> computers_visited;                                                                                // ������ ���������� �����
    computers_visited.resize(computersConnectionsMatrix.size());                                                                         //
    int temp, minValueIndex, minWeightToComputer;                                                                     //
    int i = 1;//



                                                                                               // ������������� ����� � ����������
    for (int i = 0; i < computersConnectionsMatrix.size(); i++) {                                                    //
        countSteps_computerToAll[i] = MAXWEIGHTVALUE;                                                                        //
        computers_visited[i] = 1;                                                                           //
    }
    countSteps_computerToAll[begin_index] = 0;                                                                   //
    computers_visited[trigger] = 0;



    // ��� ���������
    do {                                                                                //
        minValueIndex = MAXWEIGHTVALUE;                                                              //
        minWeightToComputer = MAXWEIGHTVALUE;                                                                  //
        for (int i = 0; i < computersConnectionsMatrix.size(); i++) {                                       // ���� ������� ��� �� ������ � ��� ������ min
            if ((computers_visited[i] == 1) && (countSteps_computerToAll[i] < minWeightToComputer)) {                                      // ��������������� ��������
                minWeightToComputer = countSteps_computerToAll[i];                                                        //
                minValueIndex = i;                                                     //
            }
        }
        // ��������� ��������� ����������� ���
       // � �������� ���� �������
      // � ���������� � ������� ����������� ����� �������
        if (minValueIndex != MAXWEIGHTVALUE) {                                            //
            for (int i = 0; i < computersConnectionsMatrix.size(); i++) {                         //
                if (i == trigger)
                    continue;
                if (computersConnectionsMatrix[minValueIndex][i] > 0) {                  //
                    temp = minWeightToComputer + computersConnectionsMatrix[minValueIndex][i];          //
                    if (temp < countSteps_computerToAll[i])                                    //
                        countSteps_computerToAll[i] = temp;                                   //
                }
                //
            }                                                        //
            computers_visited[minValueIndex] = 0;                                        //
        }                                                          //
    } while (minValueIndex < MAXWEIGHTVALUE);                                   //

    sort(countSteps_computerToAll.begin(), countSteps_computerToAll.begin() + countSteps_computerToAll.size());
    while (countSteps_computerToAll[countSteps_computerToAll.size() - i] == MAXWEIGHTVALUE) {
        i++;
    }
    return countSteps_computerToAll[countSteps_computerToAll.size() - i];
    //
}

void Matrixrecursion(int currentComp, vector<vector<int>>& MainMatrix, vector<int>& computers_visited, int depth) {
    /*
    * ����������� ������� ������ ������� ����� �� ��������� �����. ������� ������� ������ ������� � ������� ������ ������� ���������
    * � ��������� ���� �� ����� � ��������� �����������. ���� ����� ����� ���� ����������� ��� �� ���� ��������� �� ����� �������.
    * ���� ���, �� �������� ���� ��������� ��� ���������� � ��������� ����������� ������� ������ � ����� ������� � ������� ������������� �� 1.
    * ����� ���� �������� ������ �� ���������.
    * ����� ���� ��� ���� ������ ��� �������� � ������, ������������ ����������� ���������� ������� � �������. ���� ������� ������, �� ������������ �������
    * ������������� �������.
    */
    for (int j = 0; j < MainMatrix.size(); j++) { // ���� ������ �� ���� ��������� � ������
        if (MainMatrix[currentComp][j] == 1) { // �������� ������� ����� �� ������ �����������
            if (!computers_visited[j]) { // �������� ��� �� ��� ��������� �������
                computers_visited[j] = 1; // �������� ��������� ����������
                Matrixrecursion(j, MainMatrix, computers_visited, depth + 1); // ��������� �������� � ����� ������� � � ����������� ��������� �������
            }
        }
    }
    max_depth < depth ? max_depth = depth : max_depth; // �������� ������������ � �������
}

void printMatrix(const vector<vector<int>>& matrix) {
    /*
    * ������� ��������� ������ � ��������� ����:
    * 1    1
    * 1    2
    */
    for (auto& token : matrix) {
        for (auto& element : token) {
            cout << element << " \t";
        }
        cout << endl;
    }
}

void Topology::findPotentionalComputerStorage(vector<vector<int>>& lits_computerDepth) {
    /*
    * ����� ������������� �����������-��������. ��� ����� ��������� ������, ������� ����� ������� ������� � ������ ����� �����������.
    * ����� ���������� �������� (�������), ������� ����� ���������� ������� ������������� �������� ������� ����������� ������������ �������� ��� ���������.
    * � �������, ���� �������� ������ 4, 5, 5, 6, 7, 8, � ������� ����� 2, �� ����� ������� ���������� � �������� 4, 5, 5.
    * ���� ������� ����� ����� 3, �� ����� ������� ���������� 4, 5, 5, 6.
    * ����� ��������� ������ ������������� �������� ������������ � ������� �������� ��� ���� �������� ��� ������ ����������� ������������ ����
    */
    vector<vector<int>> potentialStorageList; // ������ ������������� ����������� �������� (������� -> ���������)
    int i = 0;
    int offset = 0; // �������
    while (offset != 3 && i < lits_computerDepth.size() - 1) { // ���� �� ��������� �� ����� ������ ��� �� �������� ��������
        potentialStorageList.push_back(lits_computerDepth[i]); // ��������� � ������ ������������� ���������-���������
        if (lits_computerDepth[i][0] != lits_computerDepth[i + 1][0]) // ���� ��������� ������� �� ����� ����� �������� 
            offset++; // �� ���������� � �������� ���
        i++;
    }
    //cout << "Potential Storage:\n";
    //printMatrix(potentialStorage);
    checkAllpairStorage(potentialStorageList);
}

void Topology::checkAllComputers() {
    /*
    * �������� ��� ����������� ����� �� �� �������. ��� ����� ��������� ������, ������� ����� ������� ������� � ������ ���� �����������,
    * � ����� ���������� ������, ������������ ���������� �����������, � ������� ����� ����� ������ �������� ������������ ���������� ���������.
    * ���������������� ���� �� ���������� �����������, � ������� ��������� ������ ���������� �����������, ������ �������� ���������� ��� �����������.
    * ����� ����������� ����������� ������� ������ ������� �� ����� ���������� � ������� ��������� ������� 0. ����� � ������ ������� - ��������� ������������
    * ���������� �������� � ����� ����������.
    * ����� ������� ���� ����������� ������ ����������� �� ����������� ������� � ������������ � ������ ���������� ������������� �����������-��������
    */
    vector<vector<int>> lits_DepthComputer; // ������, ������� ����� ������� ������� � ������ ���� �����������
    vector<int> compsVisited(computersConnectionsMatrix.size(), 0); // ������ ���������� �����������

    for (int i = 0; i < total_computers; i++) { // ���� �� ���� �����������
        compsVisited.clear(); // ������� ������ ���������� �����������
        compsVisited.resize(computersConnectionsMatrix.size()); // ���������� ������ �� ���������� �����������
        compsVisited[i] = true; // �������� ������� ��������� ����������
        Matrixrecursion(i, computersConnectionsMatrix, compsVisited, 0); // ����������� ������� ������ ������� �� �������� ����������
        lits_DepthComputer.push_back({ max_depth, i }); // ���������� �������� ������� � ����� ����������
        max_depth = 0; // �������� �������� ������� ��� ���������� ���������
    }
    sort(lits_DepthComputer.begin(), lits_DepthComputer.begin() + lits_DepthComputer.size()); // ��������� � ������� ����������� �������� ������
    //cout << "Lambda \tComps\n";
    //printMatrix(compsLambda);
    findPotentionalComputerStorage(lits_DepthComputer); // ������� ���������� ������������� �����������-��������
}

bool checkPairCompsInList(const vector<vector<int>>& pairList, vector<int> potentionalPair) {
    /*
    * �������� ���� ����������� �� ������������ � ������ ���. ����������� ������ �� ������� �������� ����, � ������ ����� �� ������� �������� ����
    * ���� ������� - true, ���� �� ������� ���� - false
    */
    for (int i = 0; i < pairList.size(); i++) {
        if (pairList[i][0] == potentionalPair[0])
            if (pairList[i][1] == potentionalPair[1])
                return true;
    }
    return false;
}

void Topology::checkAllpairStorage(vector<vector<int>>& potentionalStorage) {
    /*
    * �������� ���� ��� ������������� �������� �� ����������� ������������ ����. ������ ����������� � ���������: ������� ���� ��������������� ��� �������� � ��������� �� ������������ ������������.
    * ������ ���� �������� � ��� �������� � ������� � ����� ������������ ����� �������. ��� � ����� ���� ����������, ��� �������� ������� ����� ����������� ���������.  
    * ��� ����� ���������� ������� ������, � ������� ����� ������������ ���� �����������. ���������������� ���� � ��������� ���� ��� �������� ��� ���������. ���� �������� ������� �� ���������, �� ���� ���������
    * �� ����� ��������. � ���������� ������������ ������ ����������� � ����������� ���� �� ������������ � ������ ���. �������� ����������� � ������ ������� - ��������� �� ������: true - ���� ����� ����, false - ���� ����� ���.
    * ���� ������� ���� ��� ��� � ������ ���, �� ��������� �� � ���� ����������� : (1����, 2����) � (2����, 1����). ����� ����������� ������������ ��� ������� �� ����������� � ������� ��������� �������� � ��������� �� ��������.
    * ������ �� ���� ���� ���������� ������������� ���������� ������������ � ������������ ��� ������� ���: ������������ : ���� ��������. ����� ���������� ��������� ���� ���������.
    * 
    * ����� ������� �� ���� ����� �������� � ������ �� � �������, ���������� ��������������� ���� � ��������� ��������������� ��� ���� �����������.
    */
    vector<vector<int>> pairList; // ������ ��� ����������� - ��������
    map<int, pair <int, int>> map_reability_to_pair_computers; // ������� ������������ ��� ����������� (������������ : ���� ��������)
    map <int, pair<int, int>> ::iterator it; // �������� �� �������
    int reabilityValueFirstComputer, reabilityValueSecondComputer; // ���������� ��� ������ ������������ 
    int firstPotentialStorage, secondPotentialStorage; // ���������� ��� ������ ������� �����������

    for (int i = 0; i < potentionalStorage.size(); i++) { 
        for (int j = 0; j < potentionalStorage.size(); j++) {
            if (i == j) // ���� ���������� - ��������� �� ��������� ��������
                continue;
            firstPotentialStorage = potentionalStorage[i][1]; // ���������� ������ ���������
            secondPotentialStorage = potentionalStorage[j][1]; // ���������� ������ ���������
            if (!checkPairCompsInList(pairList, { firstPotentialStorage, secondPotentialStorage })) { // ���� ����� ���� ���, �� ���������� �� � ������ ���
                pairList.push_back({ firstPotentialStorage , secondPotentialStorage }); // ���������� ���� 1,2
                pairList.push_back({ secondPotentialStorage , firstPotentialStorage }); // ���������� ���� 2,1
                reabilityValueFirstComputer = Dijkstra(firstPotentialStorage, secondPotentialStorage); // ������������ ������� ����������
                reabilityValueSecondComputer = Dijkstra(secondPotentialStorage, firstPotentialStorage); // ������������ ������� ���������� 
                map_reability_to_pair_computers[max(reabilityValueFirstComputer, reabilityValueSecondComputer)] = { firstPotentialStorage , secondPotentialStorage }; // ���������� � ������� ������������ �� �������� ������������ ��� ���� � ��� ���� ��������
            }

        }
    }
    it = map_reability_to_pair_computers.begin(); // ������ ��������� ����������� ������� �������
    cout << (*it).second.first + 1 << " " << (*it).second.second + 1; // ������� ���� ����������� 
}

int main() {
    setlocale(0, "");
    Topology tp;
    tp.checkAllComputers();
    return 0;
}