#include <iostream>
#include <Windows.h>
#include <fstream>
#include <iomanip>
#include <cwchar>
#pragma warning(disable : 4996)
#include <string>
#include <queue>

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
	std::string temp;
	while (std::getline(in, temp))
	{
		std::cout << temp << std::endl;
	}
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

std::ifstream selectAttack(std::queue<char>& moves)
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
			moves.push('b');
			attack = std::ifstream("./attacks/mlg.txt");
			return attack;
		case 'i':
			moves.push('i');
			attack = std::ifstream("./attacks/triangle.txt");
			return attack;
		case 's':
			moves.push('s');
			attack = std::ifstream("./attacks/spoon.txt");
			return attack;
		case 'q':
			exit(0);
		default:
			ERR_LOG();
		}
	}
}

std::ifstream Randomize(std::queue<char>& sh_moves)
{
	std::ifstream temp("./attacks/triangle.txt");
	sh_moves.push('i');
	return temp;
}

void checkCombos(std::queue<char>& moves, int& n, int& n_en, bool isShreck = 0)
{
	if (moves.size() > 4)
	{
		moves.pop();
	}
	if (moves.size() < 3)
	{
		return;
	}

	
	std::queue<char> copy = moves;
	std::string combo4 = "";
	for (int i = 0; i < moves.size(); ++i)
	{
		combo4 += copy.front();
		copy.pop();
	}

	copy = moves;
	if (copy.size() == 4)
		copy.pop();
	
	std::string combo3 = "";
	for (int i = 0; i < 3; ++i)
	{
		combo3 += copy.front();
		copy.pop();
	}

	std::ifstream who;
	if (isShreck)
	{
		who.open("./combos/shrek.txt");
	}
	else
	{
		who.open("./combos/you.txt");
	}

	std::ifstream temp;
	if (combo3 == "sss" )
	{
		n_en--;
		temp.open("./combos/spoon.txt");
		printFile(who);
		printFile(temp);
	}
	else if (combo3 == "bbb")
	{
		n_en--;
		temp.open("./combos/coma.txt");
		printFile(who);
		printFile(temp);
	}
	else if (combo3 == "iii")
	{
		n++;
		temp.open("./combos/potion.txt");
		printFile(who);
		printFile(temp);
	}
}

bool Start(std::ifstream& hero)
{
	setFontS(5);
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_WINDOWED_MODE, 0);
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);

	std::queue<char> moves;
	std::queue<char> sh_moves;
	int n1 = 6;
	int n2 = 6;
	std::ifstream heart("./ui/heart.txt");
	std::ifstream shrek("./heroes/shrek.txt");

	while (n1 > 0 && n2 > 0)
	{
		system("cls");
		std::ifstream attack(selectAttack(moves));
		std::ifstream sh_attack(Randomize(sh_moves));
		system("cls");

		checkCombos(sh_moves, n2, n1, true);
		checkCombos(moves,n1,  n2);

		
		std::string temp;


		//calculating hp
		std::ifstream result;

		if (moves.back() == sh_moves.back())
		{
			result.open("./ui/draw.txt");
		}
		else if ((moves.back() == 'b' && sh_moves.back() == 'i') || (moves.back() == 'i' && sh_moves.back() == 's') || (moves.back() == 's' && sh_moves.back() == 'b'))
		{
			n2--;
			result.open("./ui/win.txt");
		}
		else
		{
			n1--;
			result.open("./ui/loose.txt");
		}

		//printing hearts

		heart.clear();
		heart.seekg(0);

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

		//printing fight

		std::string hero_temp;
		std::string at1_temp;
		std::string at2_temp;
		std::string shrek_temp;

		hero.clear();
		hero.seekg(0);
		attack.clear();
		attack.seekg(0);
		sh_attack.clear();
		sh_attack.seekg(0);
		shrek.clear();
		shrek.seekg(0);

		while (std::getline(hero, hero_temp))
		{
			std::getline(attack, at1_temp);
			std::getline(sh_attack, at2_temp);
			std::getline(shrek, shrek_temp);

			std::cout << hero_temp << at1_temp << at2_temp << shrek_temp << std::endl;

		}

		//printing result

		printFile(result);

		system("pause");
	}

	system("cls");

	setFontS(16);
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_WINDOWED_MODE, 0);
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);

	if (n2 <= 0)
		return true;
	return false;
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

	std::ifstream final_res;
	if (Start(hero))
	{
		final_res.open("./ui/final_win.txt");
		printFile(final_res);
	}
	else
	{
		final_res.open("./ui/final_loose.txt");
		printFile(final_res);
	}

	
	
	
}
