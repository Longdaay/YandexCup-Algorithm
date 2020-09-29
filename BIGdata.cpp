#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;

class BigData {
public:
	BigData();
	vector < int> getVecFile(ifstream& in);
	void fillSpeadsheet();
	void findMaxSumm(int i_offset, int j_offset, unsigned long long int curr_summ);
	unsigned long long int getSumm() { return summ; }
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

void BigData::findMaxSumm(int i_offset, int j_offset, unsigned long long int curr_summ) { // поиск максимальной суммы. Рекурсивная функция. i_offset - номер строки,
																						 // j_offset - номер столбца, curr_summ - текущая сумма по пройденному пути
	if (i_offset == a_vec.size())														// если номер строки достиг края, то этот путь закончен, возвращаемся
		return;																		   //
	if (j_offset == b_vec.size())													  // если номер столбца достиг края, то этот путь закончен, возвращаемся
		return;																	     //
	curr_summ += spreadsheet[i_offset][j_offset];									// добавляем к текущей сумме пройденного пути значение элемента i-строки j-столбца
	curr_summ > summ ? summ = curr_summ : summ;									   // тренарный оператор. Если текущая сумма пройденного пути больше суммы максимально найденной - присваиваем максимальной текущуюю. Иначе - ничего не делаем 
	findMaxSumm(i_offset + 1, j_offset, curr_summ);							      // идем снова по функции, опустившись вниз (i + 1)
	findMaxSumm(i_offset, j_offset + 1, curr_summ);								 // идем снова по функции, пройдя вправо (j + 1)
}
int main() {
	BigData bd;						// экземпляр класса
	bd.findMaxSumm(0, 0, 0);	   // вызываем поиск максимальной суммы, задав начальную позицию 0,0, и текущую сумму 0
	cout << bd.getSumm();		  // выводим сумму
	return 0;
}