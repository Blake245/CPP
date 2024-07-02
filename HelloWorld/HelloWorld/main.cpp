#include <iostream>

using namespace std;

void print()
{
	cout << "Hi\n";
}


namespace Blake
{
	void print()
	{
		cout << "bye\n";
	}
}

int global = 5;

class Player
{
public:
	bool getAlive()
	{
		return isAlive;
	}
	void setAlive(bool alive)
	{
		isAlive = alive;
	}

private:
	int health = 10;
	bool isAlive = true;
};


int main()
{
	bool alive = true;
	char initial = 'B';
	unsigned int score = 100; // signed = +/-
	const float decimal = 1.56f;
	double doubleDecimal = 1.56789;

	Player player1;

	//cout << player1.health << endl;
	Blake::print();
	print();
	cout << global << endl;
	cout << "Sup\n";
	cout << sizeof(int) << endl;
	cout << sizeof(short) << endl;
	cout << sizeof(long) << endl;
	cout << sizeof(float) << endl;
	cout << sizeof(double) << endl;
}

