#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <set>

using namespace std;

class BigData {
public:
	BigData();
	vector < int> getVecFile(ifstream& in);
	void fillSpeadsheet();
	unsigned long long int getSumm() { return summ; }
	void findmax();
	bool checkForEqual();
private:
	vector< int> a_vec;										// 1 массив
	vector< int> b_vec;									   // 2 массив
	vector<vector<unsigned long long int>> spreadsheet;	  // матрица 
	unsigned long long int summ = 0;					 // максимальная найденная сумма
};

BigData::BigData() {					// конструктор
	ifstream in;					   // объявляем поток для файла
	int sizeA, sizeB;				  // переменные для размеров столбца и строки 
	in.open("input.txt");			 // открываем файл
	in >> sizeA;					// получем размер 1го массива
	in >> sizeB;				   // получем размер 2го массива
	a_vec = getVecFile(in);		  // получаем из файла 1 массив
	b_vec = getVecFile(in);		 // получаем из файла 2 массив
	in.close();					// поток закрываем
	fillSpeadsheet();		   // заполняем матрицу этими массивами
}

vector <int> BigData::getVecFile(ifstream& in) {	// получаем из файла массив чисел (на вход принимаем поток с файла) на выход отдаем массив чисел из файла
	vector< int> vec;							   // массив в который запишем наши числа
	int temp;									  // переменная куда будут записываться числа из файла
	char t;										 // символьная переменная	
	in >> temp;									// получаем первое число
	vec.push_back(temp);					   // записываем его
	in.get(t);							   	  // считываем следующий символ в файле
	while (t != '\n') {					 	 // пока эта переменная не получит символ конца строки продолжаем записывать числа в массив
		if (!in.eof()) {					// если не достигли конца файла - записываем, иначе - символу присваиваем конец строки
			in >> temp;				 	   //
			vec.push_back(temp);		  //
			in.get(t);					 //
		}								//
		else					  	   //
			t = '\n';	 			  //
	}								 //
	return vec;						//возвращаем массив
}

void BigData::fillSpeadsheet() {											// заполняем матрицу
	spreadsheet.resize(a_vec.size());									   // расширяем строки таблицы на размерность 1го массива 
	for (int i = 0; i < a_vec.size(); i++) {							  // проходим циклом по строкам
		spreadsheet[i].resize(b_vec.size());							 // расширяем столбцы таблицы на размерность 2го массива
		for (int j = 0; j < b_vec.size(); j++) {						// проходим циклом по столбцам
			spreadsheet[i][j] = a_vec[i] * pow(10,9) + b_vec[j];	   // заполняем элемент матрицы значением по формуле (pow - возведение в степень (10 - число, 9 - степень))
		}															  //
	}																 //
}

unsigned long long int summ_elem(vector<unsigned long long int>& vec) { // суммирование сумм строк/столбцов
	unsigned long long int summ = 0;								   //
	for (auto& token : vec)											  //
		summ += token;												 //
	return summ;													// возвращаем полученную сумму
}

int maximum(vector<int>& vec) {					// поиск максимального числа в массиве строк/столбцов. Возвращаем его индекс
	int max = vec[0];												  // задаем максимуму - первое значение
	int iter = 0;												 // переменная для вывода индекса максимума
	for (int i = 0; i < vec.size(); i++) {					    //	
		if (vec[i] > max) {									   // если текущ больше мах
			iter = i;										  // записываем его индекс
			max = vec[i];								     // записываем это число в мах
		}												    //
	}													   //
	return iter;										  // возвращаем индекс
}

vector<int> getIndexMaxValues(vector<int>& vec, int& index) {//
	int maxValueVec = vec[index];
	vector<int> vecIndexMaxValues;
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] == maxValueVec)
			vecIndexMaxValues.push_back(i);
	}
	return vecIndexMaxValues;
}

bool BigData::checkForEqual() {
	set<int> setEqualRow;
	set<int> setEqualColumn;
	for (auto& token : a_vec)
		setEqualRow.insert(token);
	for (auto& token : b_vec)
		setEqualColumn.insert(token);
	if (setEqualRow.size() == 1 && setEqualColumn.size() == 1)
		return true;
	else
		return false;
}

void BigData::findmax() {																								     // поиск максимальной суммы
	int StopColumn, StopRow;																									    // переменные "строк/столбцов-ограничителей"
	vector<int> vecIndexStopRow;//
	int i = 0;																											   // строка
	int j = 0;																											  // столбец
	StopColumn = maximum(b_vec);																						 // поиск индекса для стобца
	StopRow = maximum(a_vec);																						    // поиск индекса для строки
	vecIndexStopRow = getIndexMaxValues(a_vec, StopRow);//
	
	if (checkForEqual()) {																			// проверка таблицы из равных элементов если сумма всех элементов деленная на количество строк столбцов равна элементу 
		summ = spreadsheet[0][0] * ((a_vec.size() + b_vec.size()) - 1);					   // присваиваем сумму по формуле
		return;																					  // выходим
	}																							 //
	unsigned long long int curr_summ = 0;
	for (int step = 0; step < vecIndexStopRow.size(); step++) {
		StopRow = vecIndexStopRow[step];
		while (i != StopRow) {
			curr_summ += spreadsheet[i][j];
			i++;
		}
		while (j != StopColumn) {
			curr_summ += spreadsheet[i][j];
			j++;
		}
	}
	if (StopColumn == j && StopRow == i) {
		while (j != b_vec.size()) {
			curr_summ += spreadsheet[i][j];
			j++;
		}
		j--;
		i++;
		while (i != a_vec.size()) {
			curr_summ += spreadsheet[i][j];
			i++;
		}
		summ = curr_summ;
		return;
	}
}

int main() {
	BigData bd;						// экземпляр класса
	bd.findmax();				   // поиск максимального
	cout << bd.getSumm();		  // выводим сумму
	return 0;
}


