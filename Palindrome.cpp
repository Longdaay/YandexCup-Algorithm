#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Palindrome {
public:
	Palindrome();
	void findPd();
	string getPalindrome() { return palindrome; }
private:
	string inptStr;
	string palindrome;
};

Palindrome::Palindrome()					// конструктор
{										   //
	ifstream in;						  //
	in.open("input.txt");				 //
	getline(in, inptStr);				//
	in.close();						   //
}								      //

bool isMinimumPd(string& tempPd, string& palindrome) {	// проверка найденного палиндрома - TRUE - найденный необходимо записать в пд. FALSE - пд меньше лексиграфически найденного
	if (palindrome.empty())							   // если палиндром пустой записываем туда найденный
		return true;								  //
	if (tempPd.size() > palindrome.size())		     // если найденный больше текущего - выходим
		return false;								//
	if (tempPd.size() == palindrome.size())		   // если равны по размеру - лексиграфически малый
		if (tempPd < palindrome)				  //
			return true;					     //
		else									//
			return false;					   //
	else									  // если найденный меньше текущего - записываем и ищем дальше
		return true;						 //
}

void Palindrome::findPd() {

	string tempPd; /// строка, в которой будет временно найденный пд

	for (int i = 1; i < inptStr.size(); i++) { // идем по каждому циклу в строке, сразу переходим на второй символ

		tempPd.clear();	// очищаем временный пд

		if (inptStr[i - 1] == inptStr[i]) {				// проверка смежного левого
			tempPd = inptStr.substr(i - 1, 2);
			if (isMinimumPd(tempPd, palindrome))	  //
				palindrome = tempPd;				 //
			continue;								//
		}

		if (inptStr[i + 1] == inptStr[i]) {				// проверка смежного правого
			tempPd = inptStr.substr(i, 2);
			if (isMinimumPd(tempPd, palindrome))	  //
				palindrome = tempPd;				 //
			continue;								//
		}

		if (inptStr[i - 1] == inptStr[i + 1]) {			// проверка левых и правых
			tempPd = inptStr.substr(i - 1, 3);
			if (isMinimumPd(tempPd, palindrome))	  //
				palindrome = tempPd;				 //
			continue;								//
		}

	}
}

int main() {											// основной цикл
	Palindrome pd;									   // объявляем класс
	pd.findPd();									  // поиск
	if (!pd.getPalindrome().empty())				 // выводим полученный пд или -1
		cout << pd.getPalindrome() << endl;			//
	else										   //
		cout << "-1\n";							  //
	return 0;									 //
}