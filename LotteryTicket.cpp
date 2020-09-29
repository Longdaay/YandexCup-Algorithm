#include <iostream>
#include <set>
#include <vector>
#include <ctime>
#include <algorithm>
#define TICKETCOUNTNUMBERS 6
#define ORGCOUNTNUMBERS 10
#define CONTWINNUMBERS 3

using namespace std;
int Search_Binary(vector<int>& arr, int left, int right, int key);

class Lotery
{
public:
	Lotery();
	void setVecOrg();
	void setUserTickets();
	void checkTickets();
private:
	vector<int> vecOrgNumbers;
	int ticketCount;
	vector<vector<int>> UserTikets;
};

Lotery::Lotery() {
	setVecOrg();
	cin >> this->ticketCount;
	setUserTickets();
}

void Lotery::setVecOrg() {
	vecOrgNumbers.clear();
	int temp;
	cin >> temp;
	vecOrgNumbers.push_back(temp);
	while (cin.peek() != '\n')
	{
		cin >> temp;
		vecOrgNumbers.push_back(temp);
	}
}

void Lotery::setUserTickets() {
	vector<int> UserTicket;
	int temp;
	int iter = 0;
	while (iter < ticketCount) {
		UserTicket.clear();
		cin >> temp;
		UserTicket.push_back(temp);
		while (cin.peek() != '\n')
		{
			cin >> temp;
			UserTicket.push_back(temp);
		}
		UserTikets.push_back(UserTicket);
		iter++;
	}
}

void Lotery::checkTickets() {
	sort(vecOrgNumbers.begin(), vecOrgNumbers.begin() + vecOrgNumbers.size());
	for (auto& token : UserTikets) {
		int samenumbes = 0;
		bool stop = true;
		int i = 0;
		while (i < token.size() && stop) {
			if (samenumbes == CONTWINNUMBERS) {
				stop = false;
				break;
			}
			if (Search_Binary(vecOrgNumbers, 0, vecOrgNumbers.size() - 1, token[i]) >= 0)
				samenumbes++;
			i++;
		}
		if (samenumbes >= 3)
			cout << "Lucky\n";
		else
			cout << "Unlucky\n";
	}
}

int Search_Binary(vector<int>& arr, int left, int right, int key) {
	int midd = 0;
	while (1) {
		midd = (left + right) / 2;

		if (key < arr[midd])
			right = midd - 1;
		else if (key > arr[midd])
			left = midd + 1;
		else
			return midd;

		if (left > right)
			return -1;
	}
}

int main() {
	srand(time(0));
	Lotery lot;
	lot.checkTickets();
	return 0;
}