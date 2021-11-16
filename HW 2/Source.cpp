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

std::ifstream HeroSelect(std::ifstream& scene)
{
	system("cls");
	std::ifstream select("./ui/select.txt");
	printFile(select);

	char in;
	std::ifstream hero;
	while (true)
	{
		std::cin >> in;
		switch (in)
		{
		case 'p':
			hero = std::ifstream ("./heroes/pog.txt");
			scene = std::ifstream("./heroes/pog_and_shrek.txt");
			return hero;
		case 'b':
			hero = std::ifstream("./heroes/big.txt");
			scene = std::ifstream("./heroes/chungus_and_shrek.txt");
			return hero;
		case 'q':
			hero = std::ifstream("./heroes/dog.txt");
			scene = std::ifstream("./heroes/dog_and_shrek.txt");
			return hero;
		default:
			ERR_LOG();
		}
	}
}

void Start()
{
	char in;
	std::cin >> in;
	
}

int main()
{
	//into 

	intro();

	//hero select 

	std::ifstream scene;
	std::ifstream hero =  HeroSelect(scene);
	
	system("cls");
	printFile(hero);

	system("pause");
	system("cls");
	

	
	// game start 

	//Start()

	setFontS(5);
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_WINDOWED_MODE, 0);
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);

	//std::cout << std::setw(634) << std::setfill('=') << ' ';

	std::ifstream heart("./ui/heart.txt");
	std::string temp;
	int n1 = 5;
	int n2 = 5;
	while (std::getline(heart, temp))
	{
		for (int i = 0; i < n1; ++i)
		{
			std::cout << temp ;
		}

		std::cout << std::setw(365 - (50*n1));
		for (int i = 0; i < n2; ++i)
		{
			std::cout << temp;
		}
		std::cout << std::endl;
		
	}

	std::ifstream hero2("./heroes/dog.txt");
	std::ifstream at1("./attacks/spoon.txt");
	std::ifstream at2("./attacks/triangle.txt");

	/*printFile(hero2);
	printFile(at1);
	printFile(at2);*/

	std::string temp1;
	std::string temp2;
	std::string temp3;
	std::string temp4;

	while (std::getline(hero, temp1))
	{
		std::getline(hero2, temp2);
		std::getline(at1, temp3);
		std::getline(at2, temp4);

		std::cout << temp1 << temp1 << temp3 << temp4 << std::endl;

	}
	//printFile(scene);
	
	
}
