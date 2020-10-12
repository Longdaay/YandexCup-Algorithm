#include <iostream>
#include <vector>
#include <fstream>
#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#define MAXWEIGHTVALUE 10000
#include <set>

using namespace std;
int max_lambda = 0;

class Topology {
public:
    Topology();
    void setCompsConnections();
    void checkAllComps();
    void printStorage();
    int Dijkstra(int begin_index, int trigger);
    void checkAllpairStorage(vector<vector<int>>& potentionalStorage);
private:
    int countComps;
    vector <vector<int>> CompsConnections;
    vector <vector<int>> summComps;
    vector <int> CompStorage;
};

Topology::Topology() {       // конструктор
    setCompsConnections();  //
}
void Topology::setCompsConnections() {                                             // получаем из файла соединени€ узлов
    ifstream in;                                                                  // поток
    in.open("input.txt");                                                        // открывем файл
    vector<int> CompConnection;                                                 // вектор дл€ одного соединени€
    int temp;                                                                  // переменна€ узла
    char t;                                                                   //
    int iter = 0;                                                            // итератор
    in >> countComps;                                                       // получаем количество узлов

    CompsConnections.resize(countComps);                                  // расшир€ем матрицу смежности узлов
    for (int i = 0; i < countComps; i++)                                 //
        CompsConnections[i].resize(countComps);                         //

    while (iter < countComps - 1) {                                    // пока не дошли до конечного соединени€
        CompConnection.clear();                                       //
        in >> temp;                                                  // считываем первый узел
        CompConnection.push_back(temp);                             //  в массив
        in.get(t);                                                 // считываем символ
        while (t != '\n') {                                       // пока символ не конец строки
            if (!in.eof()) {                                     // если не достигли конца файла
                in >> temp;                                     // считываем второй узел
                CompConnection.push_back(temp);                // в массив
                in.get(t);                                    // считываем символ
            }
            else                                            // иначе
                t = '\n';                                  // присваиваем конец строки
        }

        int first = CompConnection[0] - 1;               // перва€ позици€
        int second = CompConnection[1] - 1;             // втора€ позици€
        CompsConnections[first][second] = 1;           // заполнили матрицу смежности
        CompsConnections[second][first] = 1;          //

        iter++;                                     // добавили к итератору
    }                                              //
    in.close();                                   //
}

int Topology::Dijkstra(int begin_index, int trigger)
{
    vector <int> d;                                                                                  // массив рассто€ний до всех узлов от текущего начального узла
    d.resize(CompsConnections.size());                                                                           //
    vector <int> v;                                                                                // массив посещенных узлов
    v.resize(CompsConnections.size());                                                                         //
    int temp, minindex, min;                                                                     //
    int summ = 0;
    int i = 1;//



                                                                                               // инициализаци€ узлов и рассто€ний
    for (int i = 0; i < CompsConnections.size(); i++) {                                                    //
        d[i] = MAXWEIGHTVALUE;                                                                        //
        v[i] = 1;                                                                           //
    }
    d[begin_index] = 0;                                                                   //
    v[trigger] = 0;



    // Ўаг алгоритма
    do {                                                                                //
        minindex = MAXWEIGHTVALUE;                                                              //
        min = MAXWEIGHTVALUE;                                                                  //
        for (int i = 0; i < CompsConnections.size(); i++) {                                       // ≈сли вершину ещЄ не обошли и вес меньше min
            if ((v[i] == 1) && (d[i] < min)) {                                      // ѕереприсваиваем значени€
                min = d[i];                                                        //
                minindex = i;                                                     //
            }
        }
        // ƒобавл€ем найденный минимальный вес
       // к текущему весу вершины
      // и сравниваем с текущим минимальным весом вершины
        if (minindex != MAXWEIGHTVALUE) {                                            //
            for (int i = 0; i < CompsConnections.size(); i++) {                         //
                if (i == trigger)
                    continue;
                if (CompsConnections[minindex][i] > 0) {                  //
                    temp = min + CompsConnections[minindex][i];          //
                    if (temp < d[i])                                    //
                        d[i] = temp;                                   //
                }
                //
            }                                                        //
            v[minindex] = 0;                                        //
        }                                                          //
    } while (minindex < MAXWEIGHTVALUE);                                   //




                                                                 // ¬ывод кратчайших рассто€ний до вершин
   /*cout << "\n ратчайшие рассто€ни€ от узлов до узла " << begin_index + 1 << endl;
    for (int i = 1; i < CompsConnections.size() + 1; i++)
        printf("%5d ", i);
    cout << "\n---------------------------------\n";
    for (int i = 0; i < CompsConnections.size(); i++) {                  //
        printf("%5d ", d[i]);
        summ += d[i];                                      //
    }                                                     //
    cout << "ќбща€ сумма по строке - " << summ;
    */
    sort(d.begin(), d.begin() + d.size());
    while (d[d.size() - i] == MAXWEIGHTVALUE) {
        i++;
    }
    return d[d.size() - i];
    //
}

void Matrixrecursion(int currentComp, vector<vector<int>>& MainMatrix, vector<int>& CompsVisited, int lambda) {
    for (int j = 0; j < MainMatrix.size(); j++) {
        if (MainMatrix[currentComp][j] == 1) {
            if (!CompsVisited[j]) {
                CompsVisited[j] = 1;
                Matrixrecursion(j, MainMatrix, CompsVisited, lambda + 1);
            }
        }
    }
    max_lambda < lambda ? max_lambda = lambda : max_lambda;
}

void printMatrix(const vector<vector<int>>& matrix) {
    for (auto& token : matrix) {
        for (auto& element : token) {
            cout << element << " \t";
        }
        cout << endl;
    }
}

void Topology::checkAllComps() {
    printMatrix(CompsConnections);
    system("pause");
    vector<vector<int>> compsLambda;
    vector<vector<int>> potentialStorage;
    int i = 0;
    int offset = 0;
    vector<int> compsVisited(CompsConnections.size(), 0);

    for (int i = 0; i < countComps; i++) {
        compsVisited.clear();
        compsVisited.resize(CompsConnections.size());
        compsVisited[i] = true;
        Matrixrecursion(i, CompsConnections, compsVisited, 0);
        compsLambda.push_back({ max_lambda, i });
        max_lambda = 0;
    }
    sort(compsLambda.begin(), compsLambda.begin() + compsLambda.size());
    //cout << "Lambda \tComps\n";
    //printMatrix(compsLambda);

    while (offset != 3 && i < compsLambda.size() - 1) {
        potentialStorage.push_back(compsLambda[i]);
        if (compsLambda[i][0] != compsLambda[i + 1][0])
            offset++;
        i++;
    }
    //cout << "Potential Storage:\n";
    //printMatrix(potentialStorage);
    checkAllpairStorage(potentialStorage);
}

bool checkPairCompsInList(const vector<vector<int>>& pairList, vector<int> potentionalPair) {
    for (int i = 0; i < pairList.size(); i++) {
        if (pairList[i][0] == potentionalPair[0])
            if (pairList[i][1] == potentionalPair[1])
                return true;
    }
    return false;
}

void Topology::checkAllpairStorage(vector<vector<int>>& potentionalStorage) {
    vector<vector<int>> pairList;
    vector<vector<int>> reabilityEachPairStorage;
    vector<vector<int>> pairPotentionalStorage;
    for (int i = 0; i < potentionalStorage.size(); i++) {
        for (int j = 0; j < potentionalStorage.size(); j++) {
            if (i == j)
                continue;
            if (!checkPairCompsInList(pairList, { potentionalStorage[i][1], potentionalStorage[j][1] })) {
                pairList.push_back({ potentionalStorage[i][1] , potentionalStorage[j][1] });
                pairList.push_back({ potentionalStorage[j][1] , potentionalStorage[i][1] });
                reabilityEachPairStorage.push_back({ potentionalStorage[i][1], potentionalStorage[j][1], Dijkstra(potentionalStorage[i][1], potentionalStorage[j][1]), Dijkstra(potentionalStorage[j][1], potentionalStorage[i][1]) });
            }

        }
    }
    //cout << "reabilityPair\nc1\tc2\tmin1\tmin2\t\n";
   // printMatrix(reabilityEachPairStorage);

    for (int i = 0; i < reabilityEachPairStorage.size(); i++) {
        pairPotentionalStorage.push_back({ max(reabilityEachPairStorage[i][2], reabilityEachPairStorage[i][3]), i });
    }

    sort(pairPotentionalStorage.begin(), pairPotentionalStorage.begin() + pairPotentionalStorage.size());
    //cout << "StoragePair\nmax\trow\t\n";
    /*for (int i = 0; i < reabilityEachPairStorage.size(); i++) {
        cout << pairPotentionalStorage[i][0] << " \t" << reabilityEachPairStorage[pairPotentionalStorage[i][1]][0] + 1 << " \t" << reabilityEachPairStorage[pairPotentionalStorage[i][1]][1] + 1 << " \t\n";
    }*/
    //printMatrix(pairPotentionalStorage);
    cout << reabilityEachPairStorage[pairPotentionalStorage[0][1]][0] + 1 << " " << reabilityEachPairStorage[pairPotentionalStorage[0][1]][1] + 1;
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
    //tp.printStorage();
    set<int> value;
    value.insert(3);
    value.insert(4);
    for (auto it = value.rbegin(); it != value.rend(); ++it)
        cout << *it << " ";
    auto val = value.rbegin();
    //int f = value.extract(--(value.end()));
    return 0;
}