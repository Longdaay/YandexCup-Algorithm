/*Задача Е. ТОПОЛОГИЯ СЕТИ.
*    Ограничение времени    3 секунды
*    Ограничение памяти	    512Mb
*    Ввод	                стандартный ввод или input.txt
*    Вывод	                стандартный вывод или output.txt
* 
* Условие задачи:
* Распределённая сеть Александра состоит из n вычислительных узлов, соединённых с помощью помощью n − 1 кабелей.
* Каждый кабель соединяет ровно два различных узла, при этом любые два узла соединены кабелем напрямую, либо через цепочку промежуточных узлов.
* Александр очень переживает за сохранность данных в системе, поэтому хочет установить дополнительные жесткие диски на два компьютера-хранилища.
* Расстоянием между двумя узлами Александр называет минимальное количество соединений на цепочке от одного узла к другому. После выбора узлов для
* установки дополнительных хранилищ, для каждого узла сети Александр определяет ближайшее к нему хранилище. 
* Ненадёжностью сети он называет максимальное значение этой величины по всем узлам.
* Помогите Александру, сообщите, на какие различные компьютеры необходимо установить дополнительные жесткие диски, чтобы ненадёжность сети была минимальна.
* 
* Формат ввода:
* В первой строке входных данных записано одно целое число n(2 ≤ n ≤ 200000) — количество компьютеров в системе Александра.
* Далее в n − 1 строках записаны по два целых числа xy (1 ≤ x, y ≤ n, x ≠ y) — номера компьютеров, соединенных кабелем
* Формат вывода:
* В единственной строке выведите номера двух различных выбранных компьютеров. Если существует несколько решений, удовлетворяющих условию задачи, то выведите любое из них.
*/

/*
* Логика решения построена на наблюдениях, в которых потенциальные вершины для хранилищ имеют
* глубину(максимальное расстояние до крайних точек) больше чем у центра графа на 2
* Однако такое решение не верно
* Это практически классическая минимаксная задача размещения, только в интернете решают её для 1 центра, а мы решаем
* для двух центров(часто приводят в пример задачу как разместить центры МЧС или Скорой помощи в городе, чтобы сократить
* максимальное расстояние до каждого жителя)
* Для решения задачи ключевым является алгоритм Дейкстры для поиска самого короткого пути от целевой вершины графа к остальным
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>
#include <map>
#include <queue>

#define MAXWEIGHTVALUE 10000

struct Graph;
using namespace std;
int max_depth = 0;
vector<int> other_centres_indexes_list;

class Heap
{
    int Dist;
    int City;
public:
    Heap(int _Dist, int _y)
    {
        Dist = _Dist;
        City = _y;
    }
    int getDist() const { return Dist; }
    int getCity() const { return City; }
};

class myComparator
{
public:
    int operator() (const Heap& p1, const Heap& p2)
    {
        return p1.getDist() > p2.getDist();
    }
};

struct Graph {
public:
    int numberOfCities;
    int numberOfRoads;
    std::vector<std::vector< std::pair<int, int>>> inputData;
};

struct Distances
{
    std::vector<int> distances;
    std::vector<int> previous;
};

class Topology {
public:
    Topology();
    void setComputersConnectionsMatrix();
    void checkAllComputers();
    void checkAllpairStorage(vector<int>& potentionalStorage);
    void findPotentionalComputerStorage(vector<vector<int>>& lits_computerDepth);
    void other_centres_finder(vector <int>& centres_list, int& steps_to_new_center);
    int get_total() { return total_computers; }
private:
    int total_computers;
    vector<vector<int>> all_steps_list;
    Graph compsConnectionGraph;
};

Topology::Topology() { // конструктор
    setComputersConnectionsMatrix();
}
void Topology::setComputersConnectionsMatrix() {
    /*
    * Запись элементов из текстового файла в программу, для создания матрицы смежности
    * Сначала считывается количество компьютеров, а дальше записываются отдельные связи двух компьютеров.
    * Количество связей определяется количеством компьютеров - 1. Не допускается зацикливание связей (т.е. 1 1 и пр.) 
    * Значения элементов должны быть в диапазоне от 1 до количества компьютеров.
    * Примерный ввод элементов выглядит так:
    * 3
    * 1 2
    * 2 3
    */
    ifstream in; // открываем поток для считывания данных
    vector<int> ComputersConnection; // вектор для одного соединения
    int tempComputer, iterator = 0;
    char t;
    
    in.open("input.txt"); // открываем файл
    in >> total_computers; // получаем количество узлов
    compsConnectionGraph.numberOfCities = total_computers;
    /*
    * запись из файла происходит следующим образом: считывается первое значение (количество компьютеров)
    * дальше считывается следующий символ строки. Затем организовывается цикл. Пока следующий символ не будет равен переносу строки, продолжаем считывать из файла соединение.
    * В цикле первоочередно проверяется достигли ли конца файла. Если достигли, то присваиваем конец строки и выходим из цикла. Затем в переменные записываются значения компьютеров - 1.
    * После этого заполняется матрица смежности. 1 - обозначет, что связь между двумя компьютерами есть. Условием не оговорено, что номера компьютеров могут больше количества компьютеров.
    * Поэтому логика жестко связана на этих номерах.
    */
    compsConnectionGraph.inputData.resize(total_computers);

    for (int i = 0; i < total_computers - 1; i++) {
        int edgeStartPoint, edgeEndPoint;
        in >> edgeStartPoint >> edgeEndPoint;
        compsConnectionGraph.inputData[edgeStartPoint - 1].push_back(std::make_pair(edgeEndPoint - 1, 1));
        compsConnectionGraph.inputData[edgeEndPoint - 1].push_back(std::make_pair(edgeStartPoint - 1, 1));
    }
    in.close();
}

Distances DijkstraForward(Graph& inputGraph, int start_Point) {

    std::vector<Heap> BinaryHeap;

    Distances Result;
    Result.distances.resize(inputGraph.numberOfCities);
    Result.previous.resize(inputGraph.numberOfCities);

    for (int i = 0; i < inputGraph.numberOfCities; i++) {
        Result.distances[i] = MAXWEIGHTVALUE;
    }

    Result.distances[start_Point] = 0;

    BinaryHeap.push_back(Heap(0, start_Point));

    std::make_heap(BinaryHeap.begin(), BinaryHeap.end(), myComparator());

    while (!BinaryHeap.empty()) {

        std::pop_heap(BinaryHeap.begin(), BinaryHeap.end(), myComparator());
        Heap temp = BinaryHeap.back();
        BinaryHeap.pop_back();


        std::pair<int, int> cur;
        cur.first = temp.getDist();
        cur.second = temp.getCity();

        if (cur.first > Result.distances[cur.second]) {
            continue;
        }

        for (int i = 0; i < (int)inputGraph.inputData[cur.second].size(); ++i) {

            if (inputGraph.inputData[cur.second][i].second + Result.distances[cur.second] < Result.distances[inputGraph.inputData[cur.second][i].first]) {

                int temp = Result.distances[inputGraph.inputData[cur.second][i].first];

                Result.distances[inputGraph.inputData[cur.second][i].first] = inputGraph.inputData[cur.second][i].second + Result.distances[cur.second];
                Result.previous[inputGraph.inputData[cur.second][i].first] = cur.second;

                if (temp > Result.distances[inputGraph.inputData[cur.second][i].first]) {
                    BinaryHeap.emplace_back(Heap(Result.distances[inputGraph.inputData[cur.second][i].first], inputGraph.inputData[cur.second][i].first));
                    std::push_heap(BinaryHeap.begin(), BinaryHeap.end(), myComparator());
                }
            }
        }
    }
    return Result;
}

void Topology::other_centres_finder(vector <int>& centres_list, int& steps_to_new_center) {
    for (auto& center : centres_list) {
        int counter = 0;
        for (auto& steps_count : all_steps_list[center]) {
            if (steps_to_new_center == steps_count) {
                other_centres_indexes_list.push_back(counter);
            }
            counter++;
        }
    }
}

void Topology::findPotentionalComputerStorage(vector<vector<int>>& lits_computerDepth) {
    /*
    * поиск потенциальных компьютеров-хранилиш. Для этого создается список, который будет хранить глубины и номера таких компьютеров.
    * Также необходимо значение (триггер), которое будет определять сколько неповторяющих значений глубины компьютеров потенциально подходят как хранилища.
    * К примеру, если значения глубин 4, 5, 5, 6, 7, 8, а триггер равен 2, то будут выбраны компьютеры с глубиной 4, 5, 5.
    * Если триггер будет равен 3, то будут выбраны компьютеры 4, 5, 5, 6.
    * После получения списка потенциальных хранилищ отправляемся в функцию проверки пар этих хранилищ для поиска минимальной ненадежности сети
    */
    vector<int> centres_list;
    int distance_to_other_centres;
    vector<int> other_centres_for_indexation;

    //cout << "Potential Storage:\n";
    //printMatrix(lits_computerDepth);
    if (lits_computerDepth[0][1] != lits_computerDepth[1][1])
        centres_list.push_back(lits_computerDepth[0][1]);
    else {
        centres_list.push_back(lits_computerDepth[0][1]);
        centres_list.push_back(lits_computerDepth[1][1]);
    }

    distance_to_other_centres = lits_computerDepth[0][0] / 2;
    
    other_centres_finder(centres_list, distance_to_other_centres);
    other_centres_for_indexation = other_centres_indexes_list;
    for (int i = 0; i < other_centres_for_indexation.size(); i++) {
        for (int x = 0; x < compsConnectionGraph.inputData[other_centres_for_indexation[i]].size(); x++)
            other_centres_indexes_list.push_back(compsConnectionGraph.inputData[other_centres_for_indexation[i]][x].first);
    }
    compsConnectionGraph.inputData.clear();
    checkAllpairStorage(other_centres_indexes_list);
}

int maximum(vector<int>& value_list) {
    int maximumValue_in_list = value_list[0];// задаем максимуму - первое значение
    int iterator = 0;// переменная для вывода индекса максимума
    for (int i = 0; i < value_list.size(); i++) {//	
        if (value_list[i] > maximumValue_in_list) {// если текущ больше мах
            maximumValue_in_list = value_list[i];// записываем это число в мах
        }
    }
    return maximumValue_in_list;
}

void Topology::checkAllComputers() {
    /*
    * проверка все компьютеров графа на их глубину. Для этого создается массив, который будет хранить глубины и номера этих компьютеров,
    * а также одномерный массив, размерностью количества компьютеров, в который будет после каждой итерации записываться посещенный компьютер.
    * Организовывается цикл по количеству компьютеров, в котором очищается массив посещенных компьютеров, запись текущего компьютера как посещенного.
    * Затем запускается рекурсивная функция поиска глубины от этого компьютера и текущем значением глубины 0. После в массив глубина - компьютер записывается
    * полученное значение и номер компьютера.
    * После прохода всех компьютеров массив сортируется по возрастанию глубины и отправляется в функию нахождения потенциальных компьютеров-хранилищ
    */
    vector<vector<int>> depthValueComputer_list; // массив, который будет хранить глубины и номера этих компьютеров
    vector<int> steps_from_computer_to_other_computers;
    int max_steps = 200001;
    int counter = 0;
    for (int i = 0; i < total_computers; i++) { // цикл по всем компьютерам
        steps_from_computer_to_other_computers = DijkstraForward(compsConnectionGraph, i).distances;
        all_steps_list.push_back(steps_from_computer_to_other_computers);
    }
    for (auto steps_list : all_steps_list) {
        int maximumValue = maximum(steps_list);
        if (maximum(steps_list) <= max_steps) {
            max_steps = maximumValue;
            depthValueComputer_list.push_back({ max_steps, counter });
        }
        counter++;
    }

    sort(depthValueComputer_list.begin(), depthValueComputer_list.begin() + depthValueComputer_list.size()); // сортируем в порядке возрастания элементы списка
    findPotentionalComputerStorage(depthValueComputer_list); // функция нахождения потенциальных компьютеров-хранилищ
}

void Topology::checkAllpairStorage(vector<int>& potentialStorage) {
    /*
    * проверка всех пар потенциальных хранилищ на минимальную ненадежность сети. Логика заключается в следующем: перебор всех неповторяющихся пар хранилищ и получение их максимальной ненадежности.
    * запись этих значений и пар хранилищ в словарь и выбор минимального ключа словаря. Это и будет пара компьютеры, где наиболее выгодно можно расположить хранилища.  
    * Для этого необходимо создать список, в котором будут записываться пары компьютеров. Организовывается цикл и вложенный цикл для перебора пар элементов. Если элементы совпали по значениям, то цикл переходит
    * на новую итерацию. В переменные записываются номера компьютеров и проверяется пара на уникальность в списке пар. Проверка реализована в другой функции - результат ее работы: true - пара такая есть, false - пары такой нет.
    * Если текущей пары еще нет в списке пар, то добавляем ее в двух комбинациях : (1элем, 2элем) и (2элем, 1элем). После расчитываем ненадежность для каждого из компьютеров с помощью Алгоритма Дейкстры с триггером на партнера.
    * Дальше из этих двух полученных ненадежностей выбирается максимальная и записывается как словарь как: ненадежность : пара хранилищ. Далее выбирается следующая пара храниилищ.
    * 
    * После прохода по всем парам хранилищ и запись их в словарь, выбирается минимальмальный ключ и выводится соответствующая ему пара компьютеров.
    */
    map<int, pair <int, int>> map_reliability_to_pair_computers; // словарь ненадежности пар компьютеров (ненадежность : пара хранилищ)
    map <int, pair<int, int>> ::iterator it; // итератор по словарю
    vector<int> reliabilityValueFirstComputer, reliabilityValueSecondComputer; // переменные для записи ненадежности 
    int firstPotentialStorage, secondPotentialStorage; // переменные для записи номеров компьютеров
    vector<int> best_reliability_list;

    for (int i = 0; i < potentialStorage.size(); i++) {
        for (int j = 0; j < potentialStorage.size(); j++) {
            if (i == j) // если одинаковые - переходим на следующую итерацию
                continue;
            firstPotentialStorage = potentialStorage[i]; // записываем первый компьютер
            secondPotentialStorage = potentialStorage[j]; // записываем второй компьютер
            reliabilityValueFirstComputer = all_steps_list[firstPotentialStorage]; // ненадежность первого компьютера
            reliabilityValueSecondComputer = all_steps_list[secondPotentialStorage]; // ненадежность второго компьютера 
            best_reliability_list.clear();
            for (int i = 0; i < reliabilityValueFirstComputer.size(); i++) {
                if (reliabilityValueFirstComputer[i] < reliabilityValueSecondComputer[i])
                    best_reliability_list.push_back(reliabilityValueFirstComputer[i]);
                else
                    best_reliability_list.push_back(reliabilityValueSecondComputer[i]);
            }
            sort(best_reliability_list.begin(), best_reliability_list.begin() + best_reliability_list.size());
            map_reliability_to_pair_computers[best_reliability_list[best_reliability_list.size() - 1]] = { firstPotentialStorage , secondPotentialStorage }; // записываем в словарь максимальное из значений ненадежности как ключ и его пару хранилищ


        }
    }
    it = map_reliability_to_pair_computers.begin(); // задаем итератору минимальный элемент словаря
    cout << (*it).second.first + 1 << " " << (*it).second.second + 1; // выводим пару компьютеров 
}

int main() {
    setlocale(0, "");
    Topology tp;
    if (tp.get_total() == 2)
        cout << 1 << " " << 2;
    else
        tp.checkAllComputers();
    return 0;
}