/*Задача Е. ТОПОЛОГИЯ СЕТИ.
* Условие задачи:
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
    vector<int> Dijkstra(int begin_index);
    void checkAllpairStorage(vector<int>& potentionalStorage);
    void findPotentionalComputerStorage(vector<vector<int>>& lits_computerDepth);
    int get_total() { return total_computers; }
private:
    int total_computers;
    vector <vector<int>> computersConnectionsMatrix;
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
    vector<int> CompConnection; // вектор для одного соединения
    int temp, iterator = 0;
    char t;
    
    in.open("input.txt"); // открывем файл
    in >> total_computers; // получаем количество узлов

    computersConnectionsMatrix.resize(total_computers);// расширяем матрицу смежности узлов
    for (int i = 0; i < total_computers; i++)//
        computersConnectionsMatrix[i].resize(total_computers);//

    /*
    * запись из файла происходит следующим образом: считывается первое значение (количество компьютеров)
    * дальше считывается следующий символ строки. Затем организовывается цикл. Пока следующий символ не будет равен переносу строки, продолжаем считывать из файла соединение.
    * В цикле первоочередно проверяется достигли ли конца файла .....
    */
    while (iterator < total_computers - 1) {                                    // пока не дошли до конечного соединения
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

        int first = CompConnection[0] - 1;               // первая позиция
        int second = CompConnection[1] - 1;             // вторая позиция
        computersConnectionsMatrix[first][second] = 1;           // заполнили матрицу смежности
        computersConnectionsMatrix[second][first] = 1;          //

        iterator++;                                     // добавили к итератору
        CompConnection.clear();                                       //
    }                                              //
    in.close();                                   //
}


vector<int> Topology::Dijkstra(int begin_index) {
    /*
    * Алгоритм Дейкстры. Используется лишь часть алгоритма, а именно расчет всех путей от заданной точки ко всем точкам в графе. Алгоритм работает со взвешенными графами,
    * значения у которых неотрицательны. Дополнительное условие состоит в установке, так называемого, триггера - узла, через который пройти нельзя.
    * Алгоритм заключается в следующем: 
    *   Инициализация всех расстояний компьютера максимальным значением, кроме искомого (у искомого расстояние = 0)
    *   Поиск текущего минимального непосещенного веса компьютера и присваивание его номера и расстоянния
    *   Поиск связей этого компьютера с другими и сравнение полученного сложение путей к связному компьютеру и исходное расстояние связного компьютера
    *   Помечаем этот компьютер как посещенный и возвращаемся в цикл снова.
    *   Сортировка полученных расстояний
    *   Поиск максимального расстояния.
    */   

    vector <int> countSteps_computerToAll;// список, размерностью количества компьютеров, который хранит пути от заданной точке ко всем.
    countSteps_computerToAll.resize(computersConnectionsMatrix.size());
    vector <int> computers_visited; //Есть список посещенных компьютеров, который необходим для обработки всех компьютеров(1 - компьютер не был посещен).
    computers_visited.resize(computersConnectionsMatrix.size());
    int temp, minValueIndex, minWeightToComputer;
    int i = 1;



    // Первоначально необходимо расстояние до каждого элемента указать как максимально большое значение (в идеале бесконечность);
    // постепенно эти значения будут заменятся на корректные значения расстояний.
    for (int i = 0; i < computersConnectionsMatrix.size(); i++) {
        countSteps_computerToAll[i] = MAXWEIGHTVALUE;
        computers_visited[i] = 1;
    }
    countSteps_computerToAll[begin_index] = 0; // После этого необходимо указать расстояние у искомой точки равное 0 (т.е. мы уже в ней находимся, расстояние 0)


    /*
    * Дальше задается цикл с постусловием, в котором первом делом инициализируем максимальными значениями номер компьютера с минимальным значением, а потом и расстояние этого
    * компьютера. Далее запускаем цикл по поиску непосещенной минимальной вершины (в 1 раз это будет начальная точка - дальше зависит от весов компьютеров)
    * Если компьютер не был еще посещен и его значение расстояния меньше, чем номинальное, то мы присваиваем его номер и его расстояние соответсвующим переменным.
    * затем мы снова задаем цикл, в котором производим поиск связей этого компьютера с другими и производим сравнение полученного сложение путей к связному компьютеру и исходное расстояние связного компьютера
    * Проходим этим циклом по всем связей такого компьютера и после помечаем этот компьютер как посещенный и возвращаемся в цикл снова
    */
    do {
        minValueIndex = MAXWEIGHTVALUE; // задаем максимально возможное значение индексу
        minWeightToComputer = MAXWEIGHTVALUE; // задаем максимально возможное значение расстояние
        for (int i = 0; i < computersConnectionsMatrix.size(); i++) { // проходим циклом по всем компьютерам
            if ((computers_visited[i] == 1) && (countSteps_computerToAll[i] < minWeightToComputer)) { // если нашли непосещенный компьютер с минимальным весом, то присваиваем его номер и его расстояние соответсвующим переменным
                minWeightToComputer = countSteps_computerToAll[i]; // минимальное расстояние такого компьютера
                minValueIndex = i; // индекс такого компьютера
            }
        }

        // цикл поиска связей этого компьютера с другими
        if (minValueIndex != MAXWEIGHTVALUE) { // проверка на конец просчета всех путей (исходя из предыдущего цикла - если все вершины будут посещены, то присваиваемое значение максимально возможное не изменится)
            for (int i = 0; i < computersConnectionsMatrix.size(); i++) {
                if (computersConnectionsMatrix[minValueIndex][i] > 0) { // если есть связь с другим компьютером
                    temp = minWeightToComputer + computersConnectionsMatrix[minValueIndex][i]; // Добавляем найденный минимальный вес к текущему весу вершины
                    if (temp < countSteps_computerToAll[i]) //и сравниваем с текущим минимальным весом вершины
                        countSteps_computerToAll[i] = temp; // если меньше, то присваиваем
                }
            }
            computers_visited[minValueIndex] = 0; // помечаем компьютер как посещенный
        }
    } while (minValueIndex < MAXWEIGHTVALUE); // пока не прошли все компьютеры

    //* Сортировка полученных расстояний
    //sort(countSteps_computerToAll.begin(), countSteps_computerToAll.begin() + countSteps_computerToAll.size());

    //* Поиск максимального расстояния. Загвоздка заключается в следующем. По причине наличия триггера расстояния до компьютеров, где триггер был элементом в цепочке,
    //* равны максимально возможному значению. Поэтому необходимо организовать цикл в котором следует проверят текущий элемент с максимально возможным значением.
    //* если он равен, итератору добавляем шаг + 1. Как только мы находим значение не равное максимально возможному значению, выходим из цикла и выводим максимальный элемент.
    return countSteps_computerToAll;
}

void Matrixrecursion(int currentComp, vector<vector<int>>& MainMatrix, vector<int>& computers_visited, int depth) {
    /*
    * Рекурсивная функция поиска глубины графа из начальной точки. Функция обходит каждый элемент в текущей строке матрицы смежности
    * и проверяет есть ли связь с следующим компьютером. Если такая связь есть проверяется был ли этот компьютер до этого посещен.
    * Если нет, то помечаем этот компьютер как посещенным и запускаем рекурсивную функцию заново с новой строкой и глубина увеличивается на 1.
    * Иначе цикл движется дальше по элементам.
    * После того как цикл прошел все элементы в строке, сравнивается максимально полученная глубина с текущей. Если текущая больше, то максимальной глубине
    * присваивается текущая.
    */
    for (int j = 0; j < MainMatrix.size(); j++) { // идем циклом по всем элементам в строке
        if (MainMatrix[currentComp][j] == 1) { // проверка наличия свзяи со другим компьютером
            if (!computers_visited[j]) { // проверка был ли это компьютер посещен
                computers_visited[j] = 1; // помечаем компьютер посещенным
                Matrixrecursion(j, MainMatrix, computers_visited, depth + 1); // запускаем рекурсию с новой строкой и с увеличенным значением глубины
            }
        }
    }
    max_depth < depth ? max_depth = depth : max_depth; // проверка максимальной и текущей
}

void Topology::findPotentionalComputerStorage(vector<vector<int>>& lits_computerDepth) {
    /*
    * поиск потенциальных компьютеров-хранилиш. Для этого создается список, который будет хранить глубины и номера таких компьютеров.
    * Также необходимо значение (триггер), которое будет определять сколько неповторяющих значений глубины компьютеров потенциально подходят как хранилища.
    * К примеру, если значения глубин 4, 5, 5, 6, 7, 8, а триггер равен 2, то будут выбраны компьютеры с глубиной 4, 5, 5.
    * Если триггер будет равен 3, то будут выбраны компьютеры 4, 5, 5, 6.
    * После получения списка потенциальных хранилищ отправляемся в функцию проверки пар этих хранилищ для поиска минимальной ненадежности сети
    */
    vector<int> potentialStorageList; // список потенциальных компьютеров хранилищ (глубина -> компьютер)
    int i = 0;
    int offset = 0; // триггер
    while (offset != 3 && i < lits_computerDepth.size() - 1) { // пока не добрались до конца списка или не достигли триггера
        potentialStorageList.push_back(lits_computerDepth[i][1]); // добавляем в список потенциальный компьютер-хранилище
        if (lits_computerDepth[i][0] != lits_computerDepth[i + 1][0]) // если следующий элемент не будет равен текущему 
            offset++; // то прибавляем к триггеру шаг
        i++;
    }
    //cout << "Potential Storage:\n";
    //printMatrix(potentialStorage);
    checkAllpairStorage(potentialStorageList);
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
    vector<vector<int>> lits_DepthComputer; // массив, который будет хранить глубины и номера этих компьютеров
    vector<int> compsVisited(computersConnectionsMatrix.size(), 0); // массив посещенных компьютеров

    for (int i = 0; i < total_computers; i++) { // цикл по всем компьютерам
        compsVisited.clear(); // очистка списка посещенных компьютеров
        compsVisited.resize(computersConnectionsMatrix.size()); // расширение списка до количества компьютеров
        compsVisited[i] = true; // помечаем текущий компьютер посещенным
        Matrixrecursion(i, computersConnectionsMatrix, compsVisited, 0); // рекурсивная функция поиска глубины от текущего компьютера
        lits_DepthComputer.push_back({ max_depth, i }); // записываем значение глубины и номер компьютера
        max_depth = 0; // обнуляем значение глубины для дальнейших просчетов
    }
    sort(lits_DepthComputer.begin(), lits_DepthComputer.begin() + lits_DepthComputer.size()); // сортируем в порядке возрастания элементы списка
    //cout << "Lambda \tComps\n";
    //printMatrix(compsLambda);
    findPotentionalComputerStorage(lits_DepthComputer); // функция нахождения потенциальных компьютеров-хранилищ
}

bool checkPairCompsInList(const vector<vector<int>>& pairList, vector<int> potentionalPair) {
    /*
    * проверка пары компьютеров на уникальность в списке пар. Прогоняется массив по первому элементу пары, а дальше поиск по второму элементу пары
    * если найдена - true, если не найдена пара - false
    */
    for (int i = 0; i < pairList.size(); i++) {
        if (pairList[i][0] == potentionalPair[0])
            if (pairList[i][1] == potentionalPair[1])
                return true;
    }
    return false;
}

void Topology::checkAllpairStorage(vector<int>& potentionalStorage) {
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
    vector<vector<int>> pairList; // список пар компьютеров - хранилищ
    map<int, pair <int, int>> map_reability_to_pair_computers; // словарь ненадежности пар компьютеров (ненадежность : пара хранилищ)
    map <int, pair<int, int>> ::iterator it; // итератор по словарю
    vector<int> reabilityValueFirstComputer, reabilityValueSecondComputer; // переменные для записи ненадежности 
    int firstPotentialStorage, secondPotentialStorage; // переменные для записи номеров компьютеров
    vector<int> best_reliability_list;

    for (int i = 0; i < potentionalStorage.size(); i++) { 
        for (int j = 0; j < potentionalStorage.size(); j++) {
            if (i == j) // если одинаковые - переходим на следующую итерацию
                continue;
            firstPotentialStorage = potentionalStorage[i]; // записываем первый компьютер
            secondPotentialStorage = potentionalStorage[j]; // записываем второй компьютер
            if (!checkPairCompsInList(pairList, { firstPotentialStorage, secondPotentialStorage })) { // если такой пары нет, то записываем ее в список пар
                pairList.push_back({ firstPotentialStorage , secondPotentialStorage }); // записываем пару 1,2
                pairList.push_back({ secondPotentialStorage , firstPotentialStorage }); // записываем пару 2,1
                reabilityValueFirstComputer = Dijkstra(firstPotentialStorage); // ненадежность первого компьютера
                reabilityValueSecondComputer = Dijkstra(secondPotentialStorage); // ненадежность второго компьютера 
                best_reliability_list.clear();
                for (int i = 0; i < reabilityValueFirstComputer.size(); i++) {
                    if (reabilityValueFirstComputer[i] < reabilityValueSecondComputer[i])
                        best_reliability_list.push_back(reabilityValueFirstComputer[i]);
                    else
                        best_reliability_list.push_back(reabilityValueSecondComputer[i]);
                }
                sort(best_reliability_list.begin(), best_reliability_list.begin() + best_reliability_list.size());
                map_reability_to_pair_computers[best_reliability_list[best_reliability_list.size() - 1]] = { firstPotentialStorage , secondPotentialStorage }; // записываем в словарь максимальное из значений ненадежности как ключ и его пару хранилищ
            }

        }
    }
    it = map_reability_to_pair_computers.begin(); // задаем итератору минимальный элемент словаря
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