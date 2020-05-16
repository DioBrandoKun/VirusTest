// Covid-20.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <set>
#include <list>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <fstream>
using namespace std;
const short int Rand_virus = 10 - 1;
const short int comm = 5;
const short int SizeClast = 100;
const long int popul = 1000000;
template<class T,class B> 
void move(T* buff, B move, B len)//просто двигаем массив на Move 
{
	buff[move] = buff[len - 1];
	buff[len - 1] = -1;	
}
void Ilness(std::list<long int>** People, long int Ill_Pe, int Rand = Rand_virus, int days = 0, ostream& streamOut=cout);
void Ilness_Next(std::list<long int>** People, std::set<long int>* Ill, std::list<long int>* Ill_Next=NULL, int Rand = Rand_virus,int days = 1, ostream& streamOut=cout);
int main()
{
	srand(time(NULL));
	std::list<long int>**  Populat = new std::list<long int>*[popul];
	long int Pozition = 0;
	for(long int i=0;i<popul;i++)
	{
		Populat[i] = new std::list<long int>();
	}
	int circles = popul / SizeClast;
	for (int k = 0; k < circles; k++)
	{
		for (int i = 0; i < SizeClast; i++)
		{
			int Change = 0;
			long int Right_i = Pozition + i;
			if (k < circles - 2)
			{
				if (rand() % 10 < 10)
				{
					if (rand() % 10 < 8)
					{
						Populat[Right_i]->push_back(Right_i + 1);
						Populat[Right_i + 1]->push_back(Right_i);
						Change = 1;
					}
					else
					{
						long int place_up = Right_i + rand() % (popul - Right_i - 100)+100;

						long int place_low;
						if (Right_i > 100)
							place_low = rand() % (Right_i - SizeClast);
						else place_low = -1;
						long int place;
						if (place_up > popul)
							place_up -= 100000;
						if (place_low < 0) place_low = place_up;
						if (rand() % 2)
							place = place_up;
						else place = place_low;
						Populat[Right_i]->push_back(place);
						Populat[place]->push_back(Right_i);
					}
				}
			}
			else
				{
				if (rand() % 10 < 3)
					{
					long int place = rand() % (Right_i-100);
					Populat[Right_i]->push_back(place);
					Populat[place]->push_back(Right_i);
					}
				else if (i < SizeClast - 10)
					{
						Populat[Right_i]->push_back(Right_i + 1);
						Populat[Right_i + 1]->push_back(Right_i);
						Change = 1;
					}
				}
			int RandChance = comm - int(Populat[Right_i]->size())-2;
			for (int j = i + 1+Change; j < SizeClast; j++)
			{
				int Random = rand() % SizeClast;
				if (Random <= RandChance)
				{
					long int Right_i = Pozition + i;
					long int Right_j = Pozition + j;
					Populat[Right_i]->push_back(Right_j);
					Populat[Right_j]->push_back(Right_i);
				}
			}
			if (Populat[Right_i]->size() == 0)
			{
					Populat[Right_i]->push_back(Right_i + 1);
					Populat[Right_i + 1]->push_back(Right_i);
			}
		}
		Pozition += 100;
	}
	for (long int i = 999900; i < 1000000; i++)
	{
		std::cout << i << "=";
		for (std::list<long int>::iterator p = Populat[i]->begin(); p != Populat[i]->end(); p++)
		{
			std::cout << *p << " ";
		}
		std::cout << std::endl;
	}
	ofstream file2;
	file2.open("Virus.txt", ios::trunc);
	Ilness(Populat, rand()% popul, Rand_virus,0, file2);
	file2.close();
	system("\"C:\\Program Files (x86)\\Microsoft Visual Studio\\Shared\\Python36_64\\python.exe\" Graph.py");
    std::cout << "Hello World!\n"; 
}
void Ilness(std::list<long int>** People, long int Ill_Pe, int Rand, int days, ostream& streamOut)
{
	days++;
	set<long int>* Ill_all = new set<long int>();
	Ill_all->insert(Ill_Pe);
	std::list<long int>* Ill_Next = new list<long int>();
	for (std::list<long int>::iterator p = People[Ill_Pe]->begin(); p != People[Ill_Pe]->end(); p++)
		if (rand() % 100 <= Rand)
		{
			Ill_all->insert(*p);
			Ill_Next->push_back(*p);
		}
	streamOut << days << " " << Ill_all->size() <<std::endl;
	if(Ill_all->size()>0) Ilness_Next(People, Ill_all, Ill_Next, Rand_virus, days, streamOut);
}
void Ilness_Next(std::list<long int>** People, std::set<long int>* Ill_all, std::list<long int>* Ill_Next, int Rand,int days, ostream& streamOut)
{
	days++;
	list<long int>* Ill_New = new list<long int>();
	for (std::list<long int>::iterator Illp = Ill_Next->begin(); Illp != Ill_Next->end(); Illp++)
	{
		for (std::list<long int>::iterator p = People[*Illp]->begin(); p != People[*Illp]->end(); p++)
			if ((rand() % 100 <= Rand)&&(Ill_all->count(*p)==0))
			{
				Ill_New->push_back(*p);
				Ill_all ->insert(*p);
			}
	}
	streamOut << days << " " << Ill_New->size() << std::endl;
	delete(Ill_Next);
	Ill_Next = Ill_New;
	if (days > 100) return;
	else if(Ill_New->size()>0) Ilness_Next(People, Ill_all, Ill_New, Rand, days, streamOut);
	else cout << Ill_all->size();
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
