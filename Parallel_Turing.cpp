// Lygiagret.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;

struct Turing
{
	int DabartineBusena;
	char DabartinisElementas;
	char NaujasElementas;
	char Kryptis;
	int NaujiBusena;
};

Turing Machine[4][1000];

int main()
{
	int JuostuKiekis(4), position[4], VeikianciuMasinuKiekis(4), kiekis(0), DabarVeikianti(0);
	int busena[4]={0, 0, 0, 0}, poz, number, kartai(0), sustojo[4]={0, 1, 2, 3};
	ifstream Duomenys;
	string juosta[4], reader, failoVardas;

	//Duomenu nuskaitimas ir irasymas
	for (int i = 0; i<4;i++)
	{
		kiekis = 0;
		if (i == 0)failoVardas = "1.txt";
		else if (i == 1)failoVardas = "2.txt";
		else if (i == 2)failoVardas = "3.txt";
		else if (i == 3)failoVardas = "4.txt";
		Duomenys.open(failoVardas);
		Duomenys >> position[i] >> juosta[i];
		while (!Duomenys.eof())
		{
			if (Duomenys.fail())
			{
				Machine[i][kiekis-1].NaujiBusena = -1;
				Duomenys.clear();
				Duomenys >> reader;
			}
			Duomenys >> Machine[i][kiekis].DabartineBusena >> Machine[i][kiekis].DabartinisElementas
				>> Machine[i][kiekis].NaujasElementas >> Machine[i][kiekis].Kryptis >> Machine[i][kiekis].NaujiBusena;
			kiekis++;
		}
		Duomenys.close();
	}

	//Darbas su duomenimis
	while(true)
	{ 
	//Pereimas prie kitos juostos
		if (kartai >= 4)
		{
			Sleep(50);
			system("cls");
			kartai = 0;
		}
		if (DabarVeikianti>3) DabarVeikianti = 0;
		
	//Tikriname kuri juosta sustojo
		for (int i = 0; i < 4; i++)
			if (sustojo[i] == -1)
				if (DabarVeikianti == i)
				{
					cout<<endl<<endl;
					cout<<juosta[i]<<endl;
					kartai++;
					DabarVeikianti++;
				}

		number = DabarVeikianti;
		poz = position[number];

	//Taisykles ir galvute
		if (juosta[number][poz-1] == Machine[number][kiekis].DabartinisElementas 
			&& Machine[number][kiekis].DabartineBusena == busena[number])
		{
			cout<<endl;
			juosta[number][poz - 1] = Machine[number][kiekis].NaujasElementas;
			busena[number] = Machine[number][kiekis].NaujiBusena;
			if (Machine[number][kiekis].Kryptis == 'R') position[number]++;
			else position[number]--;
			poz = position[number];

			kiekis = 0;
			//piesiam galvute
			for (int i = 0; i < poz; i++)
			{
				if (i == (poz - 1)) cout << "-";
				else cout << " ";
			}
			cout << endl;
			cout << juosta[number] << endl;
			kartai++;
			//Dirbam su sekancia juosta
			DabarVeikianti++;
		}
		else kiekis ++;

	//Tikrinimas
		if (position[number] > juosta[number].length() || position[number]< 1 || busena[number]<0)
		{
			sustojo[number] = -1;
			VeikianciuMasinuKiekis--;
		}

	//Jei nebeliko veikianciu masinu
		if(VeikianciuMasinuKiekis == 0) break;
		if (GetAsyncKeyState(VK_SPACE)) break;
	}
	system("cls");
	for(int i = 0; i < 4; i++) cout<<endl<<juosta[i]<<endl<<endl;
	cout << "END" << endl;
	cin.get();
}

