#include <iostream>
#include <Windows.h> // library to change font size and enter full screen
#include <fstream>
#include <iomanip>
#include <cwchar> // used to coppy current console font settings 
#pragma warning(disable : 4996) // allows to copy console information from windows
#include <string>
#include <queue>
#include <random> 
#include <chrono> // library for time
#include <thread> // library for time

void setFontS(int s) // changes console size to value s
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

void printFile(std::ifstream& in) // prints out a txt file to the console
{
	in.clear();  // resets stream, so we could print from begining of the file
	in.seekg(0); //
	std::string temp;
	while (std::getline(in, temp))
	{
		std::cout << temp << std::endl;
	}
	in.clear();
	in.seekg(0);
}

void intro() // output title + start or quit 
{
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0); // enter fullscreen 
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
	system("cls"); // clears the console
	std::ifstream select("./ui/select.txt");
	printFile(select);
	select.close();

	//switch in a loop to choose a hero we will fight with
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
			moves.push('b'); // adding attack letter to the queue of attacks
			attack = std::ifstream("./attacks/mlg.txt"); // set attack to be equal to specific file
			return attack; // return that stream with file
		case 'i':
			moves.push('i');
			attack = std::ifstream("./attacks/triangle.txt");
			return attack;
		case 's':
			moves.push('s');
			attack = std::ifstream("./attacks/spoon.txt");
			return attack;
		case 'q':
			exit(0); // end program 
		default:
			ERR_LOG();
		}
	}
}

std::ifstream Randomize(std::queue<char>& sh_moves) // bot pick randomization 
{
	// the non-bias and apparently the best "modern c++ way" to random a value that i found here
	// https://stackoverflow.com/questions/7560114/random-number-c-in-some-range/7560151
	std::random_device dev; // obtain a random number from hardware
	std::mt19937 rng(dev()); // seed the generator
	std::uniform_int_distribution<std::mt19937::result_type> dist3(1, 3); // distribution in range [1, 3]

	std::ifstream temp;
	int val = dist3(rng); // generate a random value from 1 to 3
	if (val == 1)
	{
		sh_moves.push('b');
		temp.open("./attacks/mlg.txt");
		return temp;
	}
	if (val == 2)
	{
		sh_moves.push('i');
		temp.open("./attacks/triangle.txt");
		return temp;
	}
	if (val == 3)
	{
		sh_moves.push('s');
		temp.open("./attacks/spoon.txt");
		return temp;
	}
}

void checkCombos(std::queue<char>& moves, int& n, int& n_en, bool isShreck = 0)
{
	// if queue size is bigger than 4 we pop the firt element of the queue. \
	We do that because there's no sense in keeping a queue of size more than 4, where biggest combo size is 4
	if (moves.size() > 4) 
	{
		moves.pop();
	}
	//there's no need to check for combos if the queue is less then 3 aka we only made our first or second move
	if (moves.size() < 3)
	{
		return;
	}

	
	std::queue<char> copy = moves; //  copy of the queue that we will pop and get element from 
	std::string combo4 = ""; // string for storing and recognizing combos of size 4
	for (int i = 0; i < moves.size(); ++i)
	{
		combo4 += copy.front();// adding first element of the queue
		copy.pop(); // deleting first element
	}

	copy = moves;
	if (copy.size() == 4)
		copy.pop();
	
	std::string combo3 = ""; // string for combos with size 3
	for (int i = 0; i < 3; ++i)
	{
		combo3 += copy.front();
		copy.pop();
	}


	//determening for which character to check combos
	std::ifstream who;
	if (isShreck)
	{
		who.open("./combos/shrek.txt");
	}
	else
	{
		who.open("./combos/you.txt");
	}

	//checking combos 
	std::ifstream temp;
	if (combo3 == "bss" )
	{
		n_en--;
		temp.open("./combos/spoon.txt");
		printFile(who);
		printFile(temp);
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	else if (combo3 == "bbi")
	{
		n_en--;
		temp.open("./combos/coma.txt");
		printFile(who);
		printFile(temp);
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	else if (combo3 == "isi")
	{
		n++;
		temp.open("./combos/potion.txt");
		printFile(who);
		printFile(temp);
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	else if (combo4 == "ibsb")
	{
		n_en -= 2;
		temp.open("./combos/pistol.txt");
		printFile(who);
		printFile(temp);
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

bool Start(std::ifstream& hero) // basicaly the main  game mechanics aka battle
{
	setFontS(5);
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_WINDOWED_MODE, 0);
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);

	std::queue<char> moves; // queue of moves for player
	std::queue<char> sh_moves; // queue of moves for pc
	int n1 = 6; // health variables
	int n2 = 6;
	std::ifstream heart("./ui/heart.txt"); 
	std::ifstream shrek("./heroes/shrek.txt");

	while (n1 > 0 && n2 > 0) // if hp is <= than 0 loop breaks 
	{
		system("cls");
		std::ifstream attack(selectAttack(moves)); // choose attack
		std::ifstream sh_attack(Randomize(sh_moves)); // pc random attack
		system("cls");

		checkCombos(sh_moves, n2, n1, true); // check combos for pc
		checkCombos(moves,n1,  n2);// check combos for player

		
		std::string temp;


		//calculating hp and performing the comparisons of chosen attacks
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

	//here i reenter full screen because it won't properly change the font size otherwise
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_WINDOWED_MODE, 0);
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);


	//returning who own
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
	std::ifstream is("./heroes/hero_line.txt");
	
	system("cls");
	printFile(is);
	std::this_thread::sleep_for(std::chrono::seconds(1)); // dellay of 1 second
	printFile(hero);

	system("pause");
	system("cls");

	is.close();
	
	// game start 

	std::ifstream final_res; // lose or win screen
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

	system("pause"); // waiting for player to press enter, so that program wont close imideatly \
	in the executable file
}
