#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
//komentarzyk
using namespace std;

void help()
{
	cout << endl << "Dzialanie przelacznikow" << endl << endl << "\t" << "-i Pliki wejsciowe" << endl << "\t" << "-o Plik wyjsciowy" << endl << "\t" << "-h pomoc" << endl;
	cout << endl << "\t" << "Pliki powininny zawierac liczby naturalne, kazda w osobnej linii zapisane w pliku tekstowym" << endl;
}


bool string_is_ok(string napis)
{
	if (napis.length() == 0)
		return false;
	for (int i = 0; i < napis.length(); i++)
		if ((napis[i]<'0') || (napis[i]>'9'))
			return false;
	return true;
}

void sort(const string &sciezka1, const string &sciezka2, const string &sciezka3) // funkcja sortuj¹ca pliki zadane w zmiennych sciezka 1, sciezka 2 oraz wypisujaca je do pliku o nazwie sciezka3
{
	short int error_count = 0;
	ifstream we1;
	ifstream we2;
	ofstream wy;
	string napis1;
	string napis2;
	int o1;
	int o2;
	we1.open(sciezka1);
	we2.open(sciezka2);
	if ((we1.good()) && (we2.good()))
	{
		wy.open(sciezka3);
		getline(we1, napis1);
		getline(we2, napis2);
		if (string_is_ok(napis1))
			o1 = atoi(napis1.c_str());
		else
		{
			while (!string_is_ok(napis1))
			{
				error_count++;
				if (error_count == 1)
					cout << "Sprawdz format danych!" << endl << endl;
				getline(we1, napis1);
				if (string_is_ok(napis1))
				{
					o1 = atoi(napis1.c_str());
					wy << o1 << endl;
				}
			}
		}
		if (string_is_ok(napis2))
			o2 = atoi(napis2.c_str());
		else
		{
			while (!string_is_ok(napis2))
			{
				error_count++;
				if (error_count == 1)
					cout << "Sprawdz format danych!" << endl << endl;
				getline(we2, napis2);
				if (string_is_ok(napis2))
				{
					o2 = atoi(napis2.c_str());
					wy << o2 << endl;
				}
			}
		}
		if (o1 <= o2)
			wy << o1 << endl;
		else
			wy << o2 << endl;
		while ((!we1.eof()) || (!we2.eof()))
		{
			if ((!we1.eof()) && (!we2.eof()))
			{
				if (o1 <= o2)
				{
					getline(we1, napis1);
					if (string_is_ok(napis1))
					{
						o1 = atoi(napis1.c_str());
						wy << o1 << endl;
					}
					else
					{
						getline(we1, napis1);
						if (string_is_ok(napis1))
						{
							o1 = atoi(napis1.c_str());
							wy << o1 << endl;
						}
					}
				}
				else
				{
					getline(we2, napis2);
					if (string_is_ok(napis2))
					{
						o2 = atoi(napis2.c_str());
						wy << o2 << endl;
					}

					else
					{
						getline(we2, napis2);
						if (string_is_ok(napis2))
						{
							o2 = atoi(napis2.c_str());
							wy << o2 << endl;
						}
					}

				}
			}
			else
			{
				if (!we2.eof())
				{
					getline(we2, napis2);
					o2 = atoi(napis2.c_str());
					wy << o2 << endl;
				}
				if (!we1.eof())
				{
					getline(we1, napis1);
					o2 = atoi(napis1.c_str());
					wy << o1 << endl;
				}
			}

		}
		std::cout << "Operacja wykonana pomyslnie!" << endl;
		wy.close();
	}
	else
	{
		if (!we1.good())
			std::cout << "Nie udalo sie otworzyc pliku " << sciezka1 << endl;
		if (!we2.good())
			std::cout << "Nie udalo sie otworzyc pliku " << sciezka2 << endl;
	}
	we1.close();
	we2.close();
}

int main(int argc, char * argv[])
{
	string input1;
	string input2;
	string output;
	if (argc > 2)
	{
		for (int nArg = 1; nArg < argc; nArg++)
		{
			short int counter = 0;
			string arg = argv[nArg];
			if (arg == "-h")
			{
				help();
				return 0;
			}
			if ((arg == "-o") && (nArg + 2 <= argc))
			{
				string tmp = argv[nArg + 1];
				if (tmp == "-i")
				{
					help();
					return 0;
				}
				output = argv[nArg + 1];
				nArg++;
				counter++;
			}
			else
				if ((arg == "-i") && (nArg + 3 <= argc))
				{
					string tmp = argv[nArg + 1];
					if (tmp == "-o")
					{
						help();
						return 0;
					}
					tmp = argv[nArg + 2];
					if (tmp == "-o")
					{
						help();
						return 0;
					}
					input1 = argv[nArg + 1];
					input2 = argv[nArg + 2];
					nArg += 2;
					counter++;
				}
				else
					if (counter != 2)
					{
						help();
						return -1;
					}
		}
	}
	else
	{
		help();
		return 0;
	}
	cout << endl;
	sort(input1, input2, output);
	return 0;
}