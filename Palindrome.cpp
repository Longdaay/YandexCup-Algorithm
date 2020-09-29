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

Palindrome::Palindrome()					// �����������
{										   //
	ifstream in;						  //
	in.open("input.txt");				 //
	getline(in, inptStr);				//
	in.close();						   //
}								      //

bool isMinimumPd(string& tempPd, string& palindrome) {	// �������� ���������� ���������� - TRUE - ��������� ���������� �������� � ��. FALSE - �� ������ ��������������� ����������
	if (palindrome.empty())							   // ���� ��������� ������ ���������� ���� ���������
		return true;								  //
	if (tempPd.size() > palindrome.size())		     // ���� ��������� ������ �������� - �������
		return false;								//
	if (tempPd.size() == palindrome.size())		   // ���� ����� �� ������� - ��������������� �����
		if (tempPd < palindrome)				  //
			return true;					     //
		else									//
			return false;					   //
	else									  // ���� ��������� ������ �������� - ���������� � ���� ������
		return true;						 //
}

void Palindrome::findPd() {

	string tempPd; /// ������, � ������� ����� �������� ��������� ��

	for (int i = 1; i < inptStr.size(); i++) { // ���� �� ������� ����� � ������, ����� ��������� �� ������ ������

		tempPd.clear();	// ������� ��������� ��

		if (inptStr[i - 1] == inptStr[i]) {				// �������� �������� ������
			tempPd = inptStr.substr(i - 1, 2);
			if (isMinimumPd(tempPd, palindrome))	  //
				palindrome = tempPd;				 //
			continue;								//
		}

		if (inptStr[i + 1] == inptStr[i]) {				// �������� �������� �������
			tempPd = inptStr.substr(i, 2);
			if (isMinimumPd(tempPd, palindrome))	  //
				palindrome = tempPd;				 //
			continue;								//
		}

		if (inptStr[i - 1] == inptStr[i + 1]) {			// �������� ����� � ������
			tempPd = inptStr.substr(i - 1, 3);
			if (isMinimumPd(tempPd, palindrome))	  //
				palindrome = tempPd;				 //
			continue;								//
		}

	}
}

int main() {											// �������� ����
	Palindrome pd;									   // ��������� �����
	pd.findPd();									  // �����
	if (!pd.getPalindrome().empty())				 // ������� ���������� �� ��� -1
		cout << pd.getPalindrome() << endl;			//
	else										   //
		cout << "-1\n";							  //
	return 0;									 //
}