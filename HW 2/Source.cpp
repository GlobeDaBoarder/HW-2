#include <iostream>
#include <Windows.h>
#include <fstream>
#include <iomanip>
#include <cwchar>
#pragma warning(disable : 4996)
#include <string>

void setFontS(int s)
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = s;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void ERR_LOG()
{
	std::cout << "WRONG INPUT" << std::endl;
}

void printFile(std::ifstream& in)
{
	in.clear();
	in.seekg(0);
	std::cout << in.rdbuf();
	std::cout << std::endl;
	in.clear();
	in.seekg(0);
}

void intro()
{
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	setFontS(16);

	std::ifstream title("./ui/title.txt");
	printFile(title);
	title.close();

	char in;
	while (true)
	{
		std::cin >> in;
		if (in == 'S' || in == 's')
			return; 
		if (in == 'Q' || in == 'q')
			exit(0);
		
	}
	ERR_LOG();
}

std::ifstream HeroSelect()
{
	system("cls");
	std::ifstream select("./ui/select.txt");
	printFile(select);
	select.close();

	char in;
	std::ifstream hero;
	while (true)
	{
		std::cin >> in;
		switch (in)
		{
		case 'p':
			hero = std::ifstream ("./heroes/pog.txt");
			return hero;
		case 'b':
			hero = std::ifstream("./heroes/big.txt");
			return hero;
		case 'q':
			hero = std::ifstream("./heroes/dog.txt");
			return hero;
		default:
			ERR_LOG();
		}
	}

}

std::ifstream selectAttack()
{
	std::ifstream stats("./ui/combos.txt");
	printFile(stats);

	std::ifstream attack;
	char in;
	while (true)
	{
		std::cin >> in;
		switch (in)
		{
		case 'b':
			attack = std::ifstream("./attacks/mlg.txt");
			return attack;
		case 'i':
			attack = std::ifstream("./attacks/triangle.txt");
			return attack;
		case 's':
			attack = std::ifstream("./attacks/spoon.txt");
			return attack;
		default:
			ERR_LOG();
		}
	}
}

void Start(std::ifstream& hero)
{
	setFontS(5);
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_WINDOWED_MODE, 0);
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);

	std::ifstream attack(selectAttack());
	system("cls");

	std::ifstream heart("./ui/heart.txt");
	std::string temp;
	int n1 = 5;
	int n2 = 5;
	while (std::getline(heart, temp))
	{
		for (int i = 0; i < n1; ++i)
		{
			std::cout << temp;
		}

		std::cout << std::setw(365 - (50 * n1));
		for (int i = 0; i < n2; ++i)
		{
			std::cout << temp;
		}
		std::cout << std::endl;

	}

	std::ifstream shrek("./heroes/shrek.txt");

	std::string hero_temp;
	std::string at1_temp;
	//std::string at2_temp;
	std::string shrek_temp;

	while (std::getline(hero, hero_temp))
	{
		std::getline(attack, at1_temp);
		//std::getline(attack, at2_temp);
		std::getline(shrek, shrek_temp);

		std::cout << hero_temp << at1_temp << at1_temp << shrek_temp << std::endl;

	}
}

int main()
{
	//into 

	intro();

	//hero select 

	std::ifstream hero =  HeroSelect();
	
	system("cls");
	printFile(hero);

	system("pause");
	system("cls");
	

	
	// game start 

	Start(hero);

	
	
	
}
