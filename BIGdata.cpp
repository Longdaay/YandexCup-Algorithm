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
	long long int getSumm() { return summ; }
	void findmax();
	bool checkForEqual();
private:
	vector< int> a_vec;						  // 1 массив
	vector< int> b_vec;						 // 2 массив
	int a_vecSize;
	int b_vecSize;
	long long summ = 0;					  // максимальная найденная сумма
};

BigData::BigData() {				   // конструктор
	ifstream in;					  // объявляем поток для файла 
	in.open("input.txt");			 // открываем файл
	in >> a_vecSize;				// получем размер 1го массива
	in >> b_vecSize;			   // получем размер 2го массива
	a_vec = getVecFile(in);		  // получаем из файла 1 массив
	b_vec = getVecFile(in);		 // получаем из файла 2 массив
	in.close();					// поток закрываем
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

int maximum(vector<int>& vec) {								// поиск максимального числа в массиве строк/столбцов. Возвращаем его индекс
	int max = vec[0];									   // задаем максимуму - первое значение
	int iter = 0;									 	  // переменная для вывода индекса максимума
	for (int i = 0; i < vec.size(); i++) {				 //	
		if (vec[i] > max) {								// если текущ больше мах
			iter = i;								   // записываем его индекс
			max = vec[i];							  // записываем это число в мах
		}											 //
	}												//
	return iter;								   // возвращаем индекс
}

vector<int> getIndexMaxValues(vector<int>& vec, int& index) {   // массив индексов максимальных значений
	int maxValueVec = vec[index];							   // присваиваем мах максимальное значение
	vector<int> vecIndexMaxValues;							  //
	for (int i = 0; i < vec.size(); i++) {					 // проходим по массиву и ищем максимальные значения 
		if (vec[i] == maxValueVec)							//
			vecIndexMaxValues.push_back(i);				   // добавляем в массив
	}													  //
	return vecIndexMaxValues;							 // возвращаем массив
}

bool BigData::checkForEqual() {										   // проверка значений на одинаковость
	set<int> setEqualRow;											  // массив по строкам
	set<int> setEqualColumn;										 // массив по столбцам
	for (auto& token : a_vec)									    // проходим по массиву значений строк
		setEqualRow.insert(token);								   // пытаемся добавить элемент
	for (auto& token : b_vec)									  // проходим по массиву значений строк
		setEqualColumn.insert(token);							 // пытаемся добавить элемент
	if (setEqualRow.size() == 1 && setEqualColumn.size() == 1)	// если размеры массивов = 1, то все значения в массивах одинковы
		return true;
	else
		return false;
}

void BigData::findmax() {																						// поиск максимальной суммы
	int StopColumn, StopRow;																				   // переменные "строк/столбцов-ограничителей"
	vector<int> vecIndexStopRow;																			  //
	int i = 0;																								 // строка
	int j = 0;																								// столбец
	StopColumn = maximum(b_vec);																		   // поиск индекса для стобца
	StopRow = maximum(a_vec);																			  // поиск индекса для строки
	vecIndexStopRow = getIndexMaxValues(a_vec, StopRow);												 // заполняем массив индексов максимальных значений
	if (checkForEqual()) {																				// если все значения равны
		summ = (a_vec[i] * pow(10, 9) + b_vec[j]) * ((a_vec.size() + b_vec.size()) - 1);			   // вычисляем по формуле
		return;																						  // выходим
	}																								 //
	for (int step = 0; step < vecIndexStopRow.size(); step++) {										// идем по циклу строк, присваивая ограничителям строк индексы максимальных значений
		StopRow = vecIndexStopRow[step];														   // присваиваем очередной индекс
		while (i != StopRow) {																	  // пока не дошли до ограничителя строки
			summ += a_vec[i] * pow(10, 9) + b_vec[j];											 // добавляем к сумме новое значение
			i++;																				//
		}																					   //
		while (j != StopColumn) {															  // пока не дошли до ограничителя столбца
			summ += a_vec[i] * pow(10, 9) + b_vec[j];									 	 // добавляем к сумме новое значение
			j++;																			//
		}																				   //
	}
	vecIndexStopRow.clear();
	if (StopColumn == j && StopRow == i) {												// если стоим на ограничителях, то необходимо идти до конца строки и до конца столбца. Это максимальный путь
		while (j != b_vecSize) {													   // пока не дошли до последнего столбца
			summ += a_vec[i] * pow(10, 9) + b_vec[j];								  // добавляем к сумме новое значение
			j++;																	 //
		}
		j--;																	   //
		i++;																	  //
		while (i != a_vecSize) {												 // пока не дошли до последнй строки
			summ += a_vec[i] * pow(10, 9) + b_vec[j];							// добавляем к сумме новое значение
			i++;															   //
		}																	  //
		return;
	}
}

int main() {
	BigData bd;						// экземпляр класса
	bd.findmax();				   // поиск максимального
	cout << bd.getSumm();		  // выводим сумму
	return 0;
}


