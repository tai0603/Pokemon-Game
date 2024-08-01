#include "rlutil.h"
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <time.h>
#include "pokemons.h"
using namespace std;

//Object
#define MAPHEIGHT 31
#define MAPWIDTH 92
#define SPACE ' '
#define WALL '*'
#define GRASS ';'
#define TREE '!'
#define POOL '~'
#define BUILDING_1 '1'
#define BUILDING_2 '2'
#define BUILDING_3 '3'
#define BUILDING_4 '4'
#define BUILDING_5 '5'
#define BUILDING_6 '6'
#define BUILDING_7 '7'
#define BUILDING_8 '8'
#define BUILDING_9 '9'
#define BUILDING_A 'A'
#define BUILDING_B 'B'
#define BUILDING_C 'C'
#define BUILDING_D 'D'
#define BUILDING_ENTRY '#'

//Global
int x = 5, y = 5;
int WIN = 0, POKEMON = 0;
char map[MAPHEIGHT][MAPWIDTH];
int *counterPokemon = new int[10]();
int *catchPok = new int[2]();
vector<Pokemon> Pokemons;

//Pokemons(32)
Bulbasaur bulbasaur;
Ivysaur ivysaur;
Venusaur venusaur;
Charmander charmander;
Charmeleon charmeleon;
Charizard charizard;
Squirtle squirtle;
Wartortle wartortle;
Blastoise blastoise;
Caterpie caterpie;
Metapod metapod;
Butterfree butterfree;
Weedle weedle;
Kakuna kakuna;
Beedrill beedrill;
Pidgey pidgey;
Pidgeotto pidgeotto;
Pidgeot pidgeot;
Rattata rattata;
Raticate raticate;
Spearow spearow;
Fearow fearow;
Ekans ekans;
Arbok arbok;
Pikachu pikachu;
Raichu raichu;
Sandshrew sandshrew;
Sandslash sandslash;
Nidoran_Female nidoran_Female;
Nidorina nidorina;
Nidoqueen nidoqueen;
Nidoran_Male nidoran_Male;

//NPC(13)
NPC NPC_1("NPC_1");
NPC NPC_2("NPC_2");
NPC NPC_3("NPC_3");
NPC NPC_4("NPC_4");
NPC NPC_5("NPC_5");
NPC NPC_6("NPC_6");
NPC NPC_7("NPC_7");
NPC NPC_8("NPC_8");
NPC NPC_9("NPC_9");
NPC NPC_A("NPC_A");
NPC NPC_B("NPC_B");
NPC NPC_C("NPC_C");
NPC NPC_D("NPC_D");

//function
void genPokemons();
void genNPC();
void genMap();
void drawMap();
void wildPokemon(Player<Pokemon> &player);
void battle(Player<Pokemon> &player, NPC &npc);
void drawRec(int height, int width);

int main()
{
	system("chcp 437>null"); //電腦page code是Big-5所以跑不出有顏色的圖，改page code

	genPokemons(); //生成pokemon的列表
	genNPC(); //生成NPC

	{	rlutil::hidecursor();
		rlutil::cls();
		cout << "Welcome to Term Project" << endl;
		cout << "Hit Enter to continue to continue.." << endl;
		while (true)
		{
			if (kbhit())
			{
				int k = rlutil::getkey();
				if (k == rlutil::KEY_ENTER)
					break;
			}
		}
	}

	rlutil::cls();
	cout << "Build your own character" << endl;
	cout << "Name: ";
	string name;
	cin >> name;

	rlutil::hidecursor(); //設定腳色性別
	rlutil::cls();
	const char *gender[2] = { "Boy", "Girl"};
	string select_gender;
	cout << "Choose your gender" << endl;
	cout << "( " << gender[0] << " / " << gender[1] << " )";
	bool selected = false;
	while (true)
	{
		if (kbhit())
		{
			rlutil::cls();
			rlutil::setBackgroundColor(0);
			cout << "Choose your gender" << endl;
			cout << "( " << gender[0] << " / " << gender[1] << " )";

			int k = rlutil::getkey();
			if (k == 'a')
			{
				gotoxy(3, 2);
				rlutil::setBackgroundColor(15);
				rlutil::setColor(0);
				cout << gender[0];
				select_gender = gender[0];
				selected = true;
			}
			else if (k == 'd')
			{
				gotoxy(9, 2);
				rlutil::setBackgroundColor(15);
				rlutil::setColor(0);
				cout << gender[1];
				select_gender = gender[1];
				selected = true;
			}
			else if (k == rlutil::KEY_ENTER && selected == true)
				break;
			else
				selected = false;
		}
		rlutil::resetColor();
	}
	rlutil::hidecursor();
	rlutil::cls();
	cout << "Hit Enter to continue to start the game.." << endl;
	Player<Pokemon> p1(name, select_gender);

	p1.setPokemon(new Arbok, new Charizard, new Charizard);

	POKEMON = p1.getPokeNum();

	while (true)
	{
		if (kbhit())
		{
			int k = rlutil::getkey();
			if (k == rlutil::KEY_ENTER)
				break;
		}
	}

	srand((unsigned)time(NULL));
	counterPokemon[rand() % 10] = 1;
	catchPok[rand() % 2] = 1;

	rlutil::saveDefaultColor();
	genMap();
	drawMap();
	while (true) //移動
	{
		if (kbhit()) 
		{
			char k = rlutil::getkey();

			int oldx = x, oldy = y;
			if (k == 'a')
			{ 
				x--;
			}
			else if (k == 'd') 
			{ 
				x++;
			}
			else if (k == 'w') 
			{ 
				y--;
			}
			else if (k == 's') 
			{ 
				y++; 
			}
			else if (k == rlutil::KEY_ESCAPE) 
				break;
			if (map[y][x] == WALL || map[y][x] == TREE || map[y][x] == BUILDING_1 || map[y][x] == BUILDING_2 || map[y][x] == BUILDING_3 || map[y][x] == BUILDING_4 || map[y][x] == BUILDING_5 || map[y][x] == BUILDING_6 || map[y][x] == BUILDING_7 || map[y][x] == BUILDING_8 || map[y][x] == BUILDING_9 || map[y][x] == BUILDING_A || map[y][x] == BUILDING_B || map[y][x] == BUILDING_C || map[y][x] == BUILDING_D)
			{ 
				x = oldx; 
				y = oldy;
			}
			drawMap();

			if (counterPokemon[rand() % 10] == 1 && map[y][x] != BUILDING_ENTRY) //遇到pokemon進入抓寵模式
			{
				wildPokemon(p1);
				drawMap();
			}

			if (map[y][x] == BUILDING_ENTRY) //進入大樓入口和NPC對打
			{
				if (map[y - 1][x] == BUILDING_1 || map[y + 1][x] == BUILDING_1 || map[y][x - 1] == BUILDING_1 || map[y][x + 1] == BUILDING_1)
					battle(p1, NPC_1);
				else if (map[y - 1][x] == BUILDING_2 || map[y + 1][x] == BUILDING_2 || map[y][x - 1] == BUILDING_2 || map[y][x + 1] == BUILDING_2)
					battle(p1, NPC_2);
				else if (map[y - 1][x] == BUILDING_3 || map[y + 1][x] == BUILDING_3 || map[y][x - 1] == BUILDING_3 || map[y][x + 1] == BUILDING_3)
					battle(p1, NPC_3);
				else if (map[y - 1][x] == BUILDING_4 || map[y + 1][x] == BUILDING_4 || map[y][x - 1] == BUILDING_4 || map[y][x + 1] == BUILDING_4)
					battle(p1, NPC_4);
				else if (map[y - 1][x] == BUILDING_5 || map[y + 1][x] == BUILDING_5 || map[y][x - 1] == BUILDING_5 || map[y][x + 1] == BUILDING_5)
					battle(p1, NPC_5);
				else if (map[y - 1][x] == BUILDING_6 || map[y + 1][x] == BUILDING_6 || map[y][x - 1] == BUILDING_6 || map[y][x + 1] == BUILDING_6)
					battle(p1, NPC_6);
				else if (map[y - 1][x] == BUILDING_7 || map[y + 1][x] == BUILDING_7 || map[y][x - 1] == BUILDING_7 || map[y][x + 1] == BUILDING_7)
					battle(p1, NPC_7);
				else if (map[y - 1][x] == BUILDING_8 || map[y + 1][x] == BUILDING_8 || map[y][x - 1] == BUILDING_8 || map[y][x + 1] == BUILDING_8)
					battle(p1, NPC_8);
				else if (map[y - 1][x] == BUILDING_9 || map[y + 1][x] == BUILDING_9 || map[y][x - 1] == BUILDING_9 || map[y][x + 1] == BUILDING_9)
					battle(p1, NPC_9);
				else if (map[y - 1][x] == BUILDING_A || map[y + 1][x] == BUILDING_A || map[y][x - 1] == BUILDING_A || map[y][x + 1] == BUILDING_A)
					battle(p1, NPC_A);
				else if (map[y - 1][x] == BUILDING_B || map[y + 1][x] == BUILDING_B || map[y][x - 1] == BUILDING_B || map[y][x + 1] == BUILDING_B)
					battle(p1, NPC_B);
				else if (map[y - 1][x] == BUILDING_C || map[y + 1][x] == BUILDING_C || map[y][x - 1] == BUILDING_C || map[y][x + 1] == BUILDING_C)
					battle(p1, NPC_C);
				else if (map[y - 1][x] == BUILDING_D || map[y + 1][x] == BUILDING_D || map[y][x - 1] == BUILDING_D || map[y][x + 1] == BUILDING_D)
					battle(p1, NPC_D);

				drawMap();
			}

			if (WIN == 7) //打敗7個NPC結束
			{
				rlutil::hidecursor();
				rlutil::cls();
				cout << "Hit Enter to continue to start the game.." << endl;
				while (true)
				{
					if (kbhit())
					{
						int k = rlutil::getkey();
						if (k == rlutil::KEY_ENTER)
							break;
					}
				}
			}
		}
	}

	rlutil::cls();
	rlutil::resetColor();
	rlutil::showcursor();

	system("pause");
	//return 0;
}

void genMap() //把地圖存入陣列
{
	ifstream yzumap("yzumap.txt");
	string inputLine;
	int height = 0;
	while (getline(yzumap, inputLine))
	{
		for (int s = 0; s < inputLine.size(); s++)
			map[height][s] = inputLine[s];

		height++;
	}
}

void drawMap()  //輸出地圖陣列
{
	rlutil::hidecursor();
	rlutil::cls();
	rlutil::locate(1, MAPHEIGHT + 3);
	cout << "Scoreboard" << endl;
	cout << "==============" << endl;
	rlutil::setColor(14);
	cout << "Win: " << WIN << endl;
	cout << "Pokemon: " << POKEMON << endl;
	rlutil::locate(1, 1);
	for (int i = 0; i < MAPHEIGHT; i++) 
	{
		for (int j = 0; j < MAPWIDTH; j++)
		{
			if (map[i][j] == SPACE)
				cout << " ";
			else if (map[i][j] == WALL)
			{
				rlutil::setColor(15);
				cout << "*";
			}
			else if (map[i][j] == GRASS)
			{
				rlutil::setColor(2);
				cout << ";";
			}
			else if (map[i][j] == TREE)
			{
				rlutil::setColor(6);
				cout << "!";
			}
			else if (map[i][j] == POOL)
			{
				rlutil::setColor(1);
				cout << "~";
			}
			else if (map[i][j] == BUILDING_ENTRY)
			{
				rlutil::setColor(14);
				cout << "#";
			}
			else
			{
				rlutil::setColor(15);
				cout << map[i][j];
			}
		}
		cout << endl;
	}
	rlutil::locate(x + 1, y + 1);
	rlutil::setColor(4);
	cout << "@";
	fflush(stdout);
	rlutil::resetColor();
}

void wildPokemon(Player<Pokemon> &player)
{
	rlutil::hidecursor();
	rlutil::cls();
	rlutil::locate(1, 1);

	int *pokemons = new int[32]();
	int whichPokemon;
	if (map[y][x] == GRASS)
	{
		whichPokemon = rand() % 56;
		if (whichPokemon % 32 >= 0 && whichPokemon % 32 <= 7)
			whichPokemon = 0;
		else if(whichPokemon % 32 >= 8 && whichPokemon % 32 <= 15)
			whichPokemon = 1;
		else if (whichPokemon % 32 >= 16 && whichPokemon % 32 <= 23)
			whichPokemon = 2;
	}
	else if (map[y][x] == POOL)
	{
		whichPokemon = rand() % 56;
		if (whichPokemon % 32 >= 0 && whichPokemon % 32 <= 7)
			whichPokemon = 6;
		else if (whichPokemon % 32 >= 8 && whichPokemon % 32 <= 15)
			whichPokemon = 7;
		else if (whichPokemon % 32 >= 16 && whichPokemon % 32 <= 23)
			whichPokemon = 8;
	}
	else
		whichPokemon = rand() % 32;

	drawRec(50, 80);
	string file_path = Pokemons[whichPokemon].getIcon();
	ifstream icon(file_path);
	string inputStr;
	int pos = 2;
	while (getline(icon, inputStr))
	{
		rlutil::locate(2, pos);
		cout << inputStr << endl;
		pos++;
	}
	icon.close();
	inputStr.clear();
	pos = 2;
	Pokemons[whichPokemon].showPokemon(61, 5);
	player.showMyPokemons(13, 25);
	gotoxy(20, 35);
	cout << "Catch" << endl;
	gotoxy(20, 36);
	cout << "Exit" << endl;
	char k_Catch = '\0';
	char k_Exit = '\0';
	bool Catch = false;
	while (true)
	{
		if (kbhit())
		{
			if (Catch == false)
			{
				rlutil::cls();
				rlutil::setBackgroundColor(0);
				drawRec(50, 80);
				ifstream icon(file_path);
				while (getline(icon, inputStr))
				{
					rlutil::locate(2, pos);
					cout << inputStr << endl;
					pos++;
				}
				icon.close();
				inputStr.clear();
				pos = 2;
				Pokemons[whichPokemon].showPokemon(61, 5);
				player.showMyPokemons(13, 25);
				gotoxy(20, 35);
				cout << "Catch" << endl;
				gotoxy(20, 36);
				cout << "Exit" << endl;
			}

			int k = rlutil::getkey();
			if (k == 'w')
			{
				if (Catch == false)
				{
					k_Catch = 'w';
					k_Exit = '\0';
					gotoxy(20, 35);
					rlutil::setBackgroundColor(15);
					rlutil::setColor(0);
					cout << "Catch";
				}			
			}
			else if (k == 's')
			{
				k_Catch = '\0';
				k_Exit = 's';
				gotoxy(20, 36);
				rlutil::setBackgroundColor(15);
				rlutil::setColor(0);
				cout << "Exit";
			}
			else if (k == rlutil::KEY_ENTER)
			{
				if (k_Exit == 's')
					break;
				else if (k_Catch == 'w')
				{
					rlutil::cls();
					rlutil::setBackgroundColor(0);

					if (catchPok[rand() % 2] == 1)
					{
						if (whichPokemon == 0)
							player.catchPokemon(new Bulbasaur);
						else if (whichPokemon == 1)
							player.catchPokemon(new Ivysaur);
						else if (whichPokemon == 2)
							player.catchPokemon(new Venusaur);
						else if (whichPokemon == 3)
							player.catchPokemon(new Charmander);
						else if (whichPokemon == 4)
							player.catchPokemon(new Charmeleon);
						else if (whichPokemon == 5)
							player.catchPokemon(new Charizard);
						else if (whichPokemon == 6)
							player.catchPokemon(new Squirtle);
						else if (whichPokemon == 7)
							player.catchPokemon(new Wartortle);
						else if (whichPokemon == 8)
							player.catchPokemon(new Blastoise);
						else if (whichPokemon == 9)
							player.catchPokemon(new Caterpie);
						else if (whichPokemon == 10)
							player.catchPokemon(new Metapod);
						else if (whichPokemon == 11)
							player.catchPokemon(new Butterfree);
						else if (whichPokemon == 12)
							player.catchPokemon(new Weedle);
						else if (whichPokemon == 13)
							player.catchPokemon(new Kakuna);
						else if (whichPokemon == 14)
							player.catchPokemon(new Beedrill);
						else if (whichPokemon == 15)
							player.catchPokemon(new Pidgey);
						else if (whichPokemon == 16)
							player.catchPokemon(new Pidgeotto);
						else if (whichPokemon == 17)
							player.catchPokemon(new Pidgeot);
						else if (whichPokemon == 18)
							player.catchPokemon(new Rattata);
						else if (whichPokemon == 19)
							player.catchPokemon(new Raticate);
						else if (whichPokemon == 20)
							player.catchPokemon(new Spearow);
						else if (whichPokemon == 21)
							player.catchPokemon(new Fearow);
						else if (whichPokemon == 22)
							player.catchPokemon(new Ekans);
						else if (whichPokemon == 23)
							player.catchPokemon(new Arbok);
						else if (whichPokemon == 24)
							player.catchPokemon(new Pikachu);
						else if (whichPokemon == 25)
							player.catchPokemon(new Raichu);
						else if (whichPokemon == 26)
							player.catchPokemon(new Sandshrew);
						else if (whichPokemon == 27)
							player.catchPokemon(new Sandslash);
						else if (whichPokemon == 28)
							player.catchPokemon(new Nidoran_Female);
						else if (whichPokemon == 29)
							player.catchPokemon(new Nidorina);
						else if (whichPokemon == 30)
							player.catchPokemon(new Nidoqueen);
						else if (whichPokemon == 31)
							player.catchPokemon(new Nidoran_Male);

						/*drawRec();
						Pokemons[whichPokemon].showPokemon(31, 2);
						gotoxy(13, 10);
						player.showMyPokemons(13, 10);
						gotoxy(13, 17);
						cout << "You get a " << Pokemons[whichPokemon].getName();*/
						POKEMON++;

						if (POKEMON == 4)
						{
							rlutil::cls();
							rlutil::locate(1, 1);
							cout << "You get a " << Pokemons[whichPokemon].getName();
							cout << "But you already got three Pokemons, choose one to be abandoned..";
							player.showMyPokemons(1, 3);
							while (true)
							{
								if (kbhit())
								{
									int k = rlutil::getkey();
									if (k == '1')
									{
										player.dropPokemon(1);
										POKEMON--;
										break;
									}
									else if (k == '2')
									{
										player.dropPokemon(2);
										POKEMON--;
										break;
									}
									else if (k == '3')
									{
										player.dropPokemon(3);
										POKEMON--;
										break;
									}
									else if (k == '4')
									{
										player.dropPokemon(3);
										POKEMON--;
										break;
									}
								}
							}

							rlutil::cls();
							rlutil::setBackgroundColor(0);
							drawRec(50, 80);
							ifstream icon(file_path);
							while (getline(icon, inputStr))
							{
								rlutil::locate(2, pos);
								cout << inputStr << endl;
								pos++;
							}
							icon.close();
							inputStr.clear();
							pos = 2;
							Pokemons[whichPokemon].showPokemon(61, 5);
							player.showMyPokemons(13, 25);
							gotoxy(10, 35);
							cout << "You abandoned a Pokemon";
						}
						else if (POKEMON <= 3)
						{
							drawRec(50, 80);
							ifstream icon(file_path);
							while (getline(icon, inputStr))
							{
								rlutil::locate(2, pos);
								cout << inputStr << endl;
								pos++;
							}
							icon.close();
							inputStr.clear();
							pos = 2;
							Pokemons[whichPokemon].showPokemon(61, 5);
							player.showMyPokemons(13, 25);
							gotoxy(13, 35);
							cout << "You get a " << Pokemons[whichPokemon].getName();
						}

					}
					else
					{
						drawRec(50, 80);
						ifstream icon(file_path);
						while (getline(icon, inputStr))
						{
							rlutil::locate(2, pos);
							cout << inputStr << endl;
							pos++;
						}
						icon.close();
						inputStr.clear();
						pos = 2;
						Pokemons[whichPokemon].showPokemon(61, 5);
						player.showMyPokemons(13, 25);
						gotoxy(10, 35);
						cout << "Sorry, you miss a " << Pokemons[whichPokemon].getName();
					}

					k_Catch = '\0';
					Catch = true;

					rlutil::setBackgroundColor(15);
					rlutil::setColor(0);
					gotoxy(20, 36);
					cout << "Exit" << endl;
					k_Exit = 's';
				}
			}
			else
			{
				if (Catch == false)
				{
					k_Catch = '\0';
					k_Exit = '\0';
				}
			}
		}

		rlutil::resetColor();
	}
	rlutil::resetColor();
}

void battle(Player<Pokemon> &player, NPC &npc)
{
	rlutil::hidecursor();
	rlutil::cls();
	rlutil::locate(1, 1);

	//drawRec(70, 200);

	string NPC_Pokemon = npc.getCurrentPokemon()->getIcon();
	ifstream NPC_icon(NPC_Pokemon);
	string NPC_str;
	int NPC_pos = 2;
	while (getline(NPC_icon, NPC_str))
	{
		rlutil::locate(2, NPC_pos);
		cout << NPC_str << endl;
		NPC_pos++;
	}
	NPC_icon.close();
	NPC_str.clear();
	rlutil::locate(2, NPC_pos + 1);
	npc.getCurrentPokemon()->showStats();
	npc.getCurrentPokemon()->showPokemon(2, NPC_pos + 3);
	npc.showMyPokemons(2, NPC_pos + 10);
	NPC_pos = 2;

	string Player_Pokemon = player.getCurrentPokemon()->getIcon();
	ifstream Player_icon(Player_Pokemon);
	string Player_str;
	int Player_pos = 2;
	while (getline(Player_icon, Player_str))
	{
		rlutil::locate(60, Player_pos);
		cout << Player_str << endl;
		Player_pos++;
	}
	Player_icon.close();
	Player_str.clear();
	rlutil::locate(60, Player_pos + 1);
	player.getCurrentPokemon()->showStats();
	player.getCurrentPokemon()->showPokemon(60, Player_pos + 3);
	player.showMyPokemons(60, Player_pos + 10);
	Player_pos = 2;

	int round = 0;
	bool battle = false;
	bool end = false;
	char k_Battle = '\0';
	char k_Exit = '\0';
	rlutil::locate(45, 50);
	cout << "Battle";
	rlutil::locate(45, 51);
	cout << "Exit";

	while (true)
	{
		if (kbhit())
		{
			if (battle == false)
			{
				rlutil::cls();
				rlutil::setBackgroundColor(0);

				string NPC_Pokemon = npc.getCurrentPokemon()->getIcon();
				ifstream NPC_icon(NPC_Pokemon);
				while (getline(NPC_icon, NPC_str))
				{
					rlutil::locate(2, NPC_pos);
					cout << NPC_str << endl;
					NPC_pos++;
				}
				NPC_icon.close();
				NPC_str.clear();
				rlutil::locate(2, NPC_pos + 1);
				npc.getCurrentPokemon()->showStats();
				npc.getCurrentPokemon()->showPokemon(2, NPC_pos + 3);
				npc.showMyPokemons(2, NPC_pos + 10);
				NPC_pos = 2;

				string Player_Pokemon = player.getCurrentPokemon()->getIcon();
				ifstream Player_icon(Player_Pokemon);
				while (getline(Player_icon, Player_str))
				{
					rlutil::locate(60, Player_pos);
					cout << Player_str << endl;
					Player_pos++;
				}
				Player_icon.close();
				Player_str.clear();
				rlutil::locate(60, Player_pos + 1);
				player.getCurrentPokemon()->showStats();
				player.getCurrentPokemon()->showPokemon(60, Player_pos + 3);
				player.showMyPokemons(60, Player_pos + 10);
				Player_pos = 2;

				rlutil::locate(45, 50);
				cout << "Battle";
				rlutil::locate(45, 51);
				cout << "Exit";
			}

			int k = rlutil::getkey();
			if (k == 'w')
			{
				if (battle == false)
				{
					k_Battle = 'w';
					k_Exit = '\0';
					gotoxy(45, 50);
					rlutil::setBackgroundColor(15);
					rlutil::setColor(0);
					cout << "Battle";
				}
				else if (end == false)
				{
					k_Exit = '\0';
					gotoxy(45, 51);
					cout << "Exit";
				}
			}
			else if (k == 's')
			{
				k_Battle = '\0';
				k_Exit = 's';
				gotoxy(45, 51);
				rlutil::setBackgroundColor(15);
				rlutil::setColor(0);
				cout << "Exit";
			}
			else if (k == rlutil::KEY_ENTER)
			{
				if (k_Exit == 's')
					break;
				else if (k_Battle == 'w')
				{
					battle = true;
					round++;

					rlutil::cls();
					rlutil::setBackgroundColor(0);

					if (player.getCurrentPokemon()->getSpeed() >= npc.getCurrentPokemon()->getSpeed())
					{
						rlutil::locate(30, 42);
						player.getCurrentPokemon()->attack(*npc.getCurrentPokemon());
						if (player.getCurrentPokemon()->getAbility() == 1 || player.getCurrentPokemon()->getAbility() == 2 || player.getCurrentPokemon()->getAbility() == 5 || player.getCurrentPokemon()->getAbility() == 7 || player.getCurrentPokemon()->getAbility() == 8 || player.getCurrentPokemon()->getAbility() == 9 || player.getCurrentPokemon()->getAbility() == 11 || player.getCurrentPokemon()->getAbility() == 12)
						{
							rlutil::locate(30, 43);
							player.getCurrentPokemon()->ability(*npc.getCurrentPokemon());

							if (npc.getCurrentPokemon()->getAbility() == 3 || npc.getCurrentPokemon()->getAbility() == 4 || npc.getCurrentPokemon()->getAbility() == 6 || npc.getCurrentPokemon()->getAbility() == 10)
							{
								rlutil::locate(30, 44);
								npc.getCurrentPokemon()->ability(*player.getCurrentPokemon());
							}
						}

						rlutil::locate(30, 46);
						npc.getCurrentPokemon()->attack(*player.getCurrentPokemon());
						if (npc.getCurrentPokemon()->getAbility() == 1 || npc.getCurrentPokemon()->getAbility() == 2 || npc.getCurrentPokemon()->getAbility() == 5 || npc.getCurrentPokemon()->getAbility() == 7 || npc.getCurrentPokemon()->getAbility() == 8 || npc.getCurrentPokemon()->getAbility() == 9 || npc.getCurrentPokemon()->getAbility() == 11 || npc.getCurrentPokemon()->getAbility() == 12)
						{
							rlutil::locate(30, 47);
							npc.getCurrentPokemon()->ability(*player.getCurrentPokemon());

							if (player.getCurrentPokemon()->getAbility() == 3 || player.getCurrentPokemon()->getAbility() == 4 || player.getCurrentPokemon()->getAbility() == 6 || player.getCurrentPokemon()->getAbility() == 10)
							{
								rlutil::locate(30, 48);
								player.getCurrentPokemon()->ability(*npc.getCurrentPokemon());
							}
						}
					}
					else
					{
						rlutil::locate(30, 42);
						npc.getCurrentPokemon()->attack(*player.getCurrentPokemon());
						if (npc.getCurrentPokemon()->getAbility() == 1 || npc.getCurrentPokemon()->getAbility() == 2 || npc.getCurrentPokemon()->getAbility() == 5 || npc.getCurrentPokemon()->getAbility() == 7 || npc.getCurrentPokemon()->getAbility() == 8 || npc.getCurrentPokemon()->getAbility() == 9 || npc.getCurrentPokemon()->getAbility() == 11 || npc.getCurrentPokemon()->getAbility() == 12)
						{
							rlutil::locate(30, 43);
							npc.getCurrentPokemon()->ability(*npc.getCurrentPokemon());

							if (player.getCurrentPokemon()->getAbility() == 3 || player.getCurrentPokemon()->getAbility() == 4 || player.getCurrentPokemon()->getAbility() == 6 || player.getCurrentPokemon()->getAbility() == 10)
							{
								rlutil::locate(30, 44);
								player.getCurrentPokemon()->ability(*npc.getCurrentPokemon());
							}
						}

						rlutil::locate(30, 46);
						player.getCurrentPokemon()->attack(*npc.getCurrentPokemon());
						if (player.getCurrentPokemon()->getAbility() == 1 || player.getCurrentPokemon()->getAbility() == 2 || player.getCurrentPokemon()->getAbility() == 5 || player.getCurrentPokemon()->getAbility() == 7 || player.getCurrentPokemon()->getAbility() == 8 || player.getCurrentPokemon()->getAbility() == 9 || player.getCurrentPokemon()->getAbility() == 11 || player.getCurrentPokemon()->getAbility() == 12)
						{
							rlutil::locate(30, 47);
							player.getCurrentPokemon()->ability(*npc.getCurrentPokemon());

							if (npc.getCurrentPokemon()->getAbility() == 3 || npc.getCurrentPokemon()->getAbility() == 4 || npc.getCurrentPokemon()->getAbility() == 6 || npc.getCurrentPokemon()->getAbility() == 10)
							{
								rlutil::locate(30, 48);
								npc.getCurrentPokemon()->ability(*player.getCurrentPokemon());
							}
						}
					}

					string NPC_Pokemon = npc.getCurrentPokemon()->getIcon();
					ifstream NPC_icon(NPC_Pokemon);
					while (getline(NPC_icon, NPC_str))
					{
						rlutil::locate(2, NPC_pos);
						cout << NPC_str << endl;
						NPC_pos++;
					}
					NPC_icon.close();
					NPC_str.clear();
					rlutil::locate(2, NPC_pos + 1);
					npc.getCurrentPokemon()->showStats();
					npc.getCurrentPokemon()->showPokemon(2, NPC_pos + 3);
					npc.showMyPokemons(2, NPC_pos + 10);
					NPC_pos = 2;

					string Player_Pokemon = player.getCurrentPokemon()->getIcon();
					ifstream Player_icon(Player_Pokemon);
					while (getline(Player_icon, Player_str))
					{
						rlutil::locate(60, Player_pos);
						cout << Player_str << endl;
						Player_pos++;
					}
					Player_icon.close();
					Player_str.clear();
					rlutil::locate(60, Player_pos + 1);
					player.getCurrentPokemon()->showStats();
					player.getCurrentPokemon()->showPokemon(60, Player_pos + 3);
					player.showMyPokemons(60, Player_pos + 10);
					Player_pos = 2;

					rlutil::locate(45, 40);
					cout << "Round " << round;
					rlutil::locate(35, 50);
					cout << "Press Space to next round";
					rlutil::locate(45, 51);
					cout << "Exit";
				}
			}
			else if (k == rlutil::KEY_SPACE && end == false)
			{
				if (battle == true)
				{
					round++;

					rlutil::cls();
					rlutil::setBackgroundColor(0);

					if (player.getCurrentPokemon()->getSpeed() >= npc.getCurrentPokemon()->getSpeed())
					{
						rlutil::locate(30, 42);
						player.getCurrentPokemon()->attack(*npc.getCurrentPokemon());
						if (npc.getCurrentPokemon() != NULL)
						{
							if (player.getCurrentPokemon()->getAbility() == 1 || player.getCurrentPokemon()->getAbility() == 2 || player.getCurrentPokemon()->getAbility() == 5 || player.getCurrentPokemon()->getAbility() == 7 || player.getCurrentPokemon()->getAbility() == 8 || player.getCurrentPokemon()->getAbility() == 9 || player.getCurrentPokemon()->getAbility() == 11 || player.getCurrentPokemon()->getAbility() == 12)
							{
								rlutil::locate(30, 43);
								player.getCurrentPokemon()->ability(*npc.getCurrentPokemon());

								if (npc.getCurrentPokemon()->getAbility() == 3 || npc.getCurrentPokemon()->getAbility() == 4 || npc.getCurrentPokemon()->getAbility() == 6 || npc.getCurrentPokemon()->getAbility() == 10)
								{
									rlutil::locate(30, 44);
									npc.getCurrentPokemon()->ability(*player.getCurrentPokemon());
								}
							}
						}

						if (npc.getCurrentPokemon() == NULL)
						{
							end = true;
							rlutil::locate(42, 50);
							cout << "You Win!!";
							WIN++;
						}
						else
						{
							rlutil::locate(30, 46);
							npc.getCurrentPokemon()->attack(*player.getCurrentPokemon());
							if (player.getCurrentPokemon() != NULL)
							{
								if (npc.getCurrentPokemon()->getAbility() == 1 || npc.getCurrentPokemon()->getAbility() == 2 || npc.getCurrentPokemon()->getAbility() == 5 || npc.getCurrentPokemon()->getAbility() == 7 || npc.getCurrentPokemon()->getAbility() == 8 || npc.getCurrentPokemon()->getAbility() == 9 || npc.getCurrentPokemon()->getAbility() == 11 || npc.getCurrentPokemon()->getAbility() == 12)
								{
									rlutil::locate(30, 47);
									npc.getCurrentPokemon()->ability(*player.getCurrentPokemon());

									if (player.getCurrentPokemon()->getAbility() == 3 || player.getCurrentPokemon()->getAbility() == 4 || player.getCurrentPokemon()->getAbility() == 6 || player.getCurrentPokemon()->getAbility() == 10)
									{
										rlutil::locate(30, 48);
										player.getCurrentPokemon()->ability(*npc.getCurrentPokemon());
									}
								}
							}

							if (player.getCurrentPokemon() == NULL)
							{
								end = true;
								rlutil::locate(42, 50);
								cout << "You Lose..";
							}
						}
					}
					else
					{
						rlutil::locate(30, 42);
						npc.getCurrentPokemon()->attack(*player.getCurrentPokemon());
						if (player.getCurrentPokemon() != NULL)
						{
							if (npc.getCurrentPokemon()->getAbility() == 1 || npc.getCurrentPokemon()->getAbility() == 2 || npc.getCurrentPokemon()->getAbility() == 5 || npc.getCurrentPokemon()->getAbility() == 7 || npc.getCurrentPokemon()->getAbility() == 8 || npc.getCurrentPokemon()->getAbility() == 9 || npc.getCurrentPokemon()->getAbility() == 11 || npc.getCurrentPokemon()->getAbility() == 12)
							{
								rlutil::locate(30, 43);
								npc.getCurrentPokemon()->ability(*npc.getCurrentPokemon());

								if (player.getCurrentPokemon()->getAbility() == 3 || player.getCurrentPokemon()->getAbility() == 4 || player.getCurrentPokemon()->getAbility() == 6 || player.getCurrentPokemon()->getAbility() == 10)
								{
									rlutil::locate(30, 44);
									player.getCurrentPokemon()->ability(*npc.getCurrentPokemon());
								}
							}
						}

						if (player.getCurrentPokemon() == NULL)
						{
							end = true;
							rlutil::locate(42, 50);
							cout << "You Lose..";
						}
						else
						{
							rlutil::locate(30, 46);
							player.getCurrentPokemon()->attack(*npc.getCurrentPokemon());
							if (npc.getCurrentPokemon() != NULL)
							{
								if (player.getCurrentPokemon()->getAbility() == 1 || player.getCurrentPokemon()->getAbility() == 2 || player.getCurrentPokemon()->getAbility() == 5 || player.getCurrentPokemon()->getAbility() == 7 || player.getCurrentPokemon()->getAbility() == 8 || player.getCurrentPokemon()->getAbility() == 9 || player.getCurrentPokemon()->getAbility() == 11 || player.getCurrentPokemon()->getAbility() == 12)
								{
									rlutil::locate(30, 47);
									player.getCurrentPokemon()->ability(*npc.getCurrentPokemon());

									if (npc.getCurrentPokemon()->getAbility() == 3 || npc.getCurrentPokemon()->getAbility() == 4 || npc.getCurrentPokemon()->getAbility() == 6 || npc.getCurrentPokemon()->getAbility() == 10)
									{
										rlutil::locate(30, 48);
										npc.getCurrentPokemon()->ability(*player.getCurrentPokemon());
									}
								}
							}

							if (npc.getCurrentPokemon() == NULL)
							{
								end = true;
								rlutil::locate(42, 50);
								cout << "You Win!!";
								WIN++;
							}
						}
					}

					if (npc.getCurrentPokemon() != NULL)
					{
						string NPC_Pokemon = npc.getCurrentPokemon()->getIcon();
						ifstream NPC_icon(NPC_Pokemon);
						while (getline(NPC_icon, NPC_str))
						{
							rlutil::locate(2, NPC_pos);
							cout << NPC_str << endl;
							NPC_pos++;
						}
						NPC_icon.close();
						NPC_str.clear();
						rlutil::locate(2, NPC_pos + 1);
						npc.getCurrentPokemon()->showStats();
						npc.getCurrentPokemon()->showPokemon(2, NPC_pos + 3);
						npc.showMyPokemons(2, NPC_pos + 10);
						NPC_pos = 2;
					}
					else
						npc.showMyPokemons(2, 36);

					if (player.getCurrentPokemon() != NULL)
					{
						string Player_Pokemon = player.getCurrentPokemon()->getIcon();
						ifstream Player_icon(Player_Pokemon);
						while (getline(Player_icon, Player_str))
						{
							rlutil::locate(60, Player_pos);
							cout << Player_str << endl;
							Player_pos++;
						}
						Player_icon.close();
						Player_str.clear();
						rlutil::locate(60, Player_pos + 1);
						player.getCurrentPokemon()->showStats();
						player.getCurrentPokemon()->showPokemon(60, Player_pos + 3);
						player.showMyPokemons(60, Player_pos + 10);
						Player_pos = 2;
					}
					else
						player.showMyPokemons(60, 36);

					if (end == false)
					{
						rlutil::locate(45, 40);
						cout << "Round " << round;
						rlutil::locate(35, 50);
						cout << "Press Space to next round";
						rlutil::locate(45, 51);
						cout << "Exit";
					}
					else
					{
						k_Battle = '\0';
						k_Exit = 's';
						rlutil::locate(45, 51);
						rlutil::setBackgroundColor(15);
						rlutil::setColor(0);
						cout << "Exit";
						npc.recoverPokemon();
						player.recoverPokemon();
					}
					
				}
			}
			else
			{
				if (end == false)
				{
					k_Battle = '\0';
					k_Exit = '\0';
				}
			}
		}
		rlutil::resetColor();
	}
	rlutil::resetColor();
}

void drawRec(int height, int width)
{
	cout << "-";
	for (int i = 0; i < width - 2; i++)
		cout << "-";
	cout << "-\n";

	for (int i = 0; i < height - 2; i++)
	{
		cout << "|";
		for (int j = 0; j < width - 2; j++)
			cout << " ";
		cout << "|\n";
	}

	cout << "-";
	for (int i = 0; i < width - 2; i++)
		cout << "-";
	cout << "-\n";
}

void genPokemons()
{
	Pokemons.push_back(bulbasaur);
	Pokemons.push_back(ivysaur);
	Pokemons.push_back(venusaur);
	Pokemons.push_back(charmander);
	Pokemons.push_back(charmeleon);
	Pokemons.push_back(charizard);
	Pokemons.push_back(squirtle);
	Pokemons.push_back(wartortle);
	Pokemons.push_back(blastoise);
	Pokemons.push_back(caterpie);
	Pokemons.push_back(metapod);
	Pokemons.push_back(butterfree);
	Pokemons.push_back(weedle);
	Pokemons.push_back(kakuna);
	Pokemons.push_back(beedrill);
	Pokemons.push_back(pidgey);
	Pokemons.push_back(pidgeotto);
	Pokemons.push_back(pidgeot);
	Pokemons.push_back(rattata);
	Pokemons.push_back(raticate);
	Pokemons.push_back(spearow);
	Pokemons.push_back(fearow);
	Pokemons.push_back(ekans);
	Pokemons.push_back(arbok);
	Pokemons.push_back(pikachu);
	Pokemons.push_back(raichu);
	Pokemons.push_back(sandshrew);
	Pokemons.push_back(sandslash);
	Pokemons.push_back(nidoran_Female);
	Pokemons.push_back(nidorina);
	Pokemons.push_back(nidoqueen);
	Pokemons.push_back(nidoran_Male);
}

void genNPC()
{
	NPC_1.setPokemon(new Bulbasaur, new Charmander, new Squirtle);
	//NPC_2.setPokemon();
	//NPC_3.setPokemon();
	//NPC_4.setPokemon();
	//NPC_5.setPokemon();
	NPC_6.setPokemon(new Weedle, new Pidgey, new Pikachu);
	//NPC_7.setPokemon();
	//NPC_8.setPokemon();
	//NPC_9.setPokemon();
	//NPC_A.setPokemon();
	//NPC_B.setPokemon();
	//NPC_C.setPokemon();
	//NPC_D.setPokemon();
}