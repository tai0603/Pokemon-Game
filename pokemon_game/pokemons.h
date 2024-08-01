#ifndef POKEMONS_H
#define POKEMONS_H
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>
#include <vector>
#include <iomanip>
#include <exception>
using namespace std;

class Pokemon {
private:
	string Name;
	string Type;
	int HP;
	int MaxHP;
	int Attack;
	int Defense;
	int Speed;
	int Ability;
	int Number;
	string Icon;
	int Damage;
	bool Poisoned = false;
	bool usePoisoned = false;
	bool LowerSpeed = false;
	bool useLowerSpeed = false;
	bool LowerAttack = false;
	bool useLowerAttack = false;
	bool LowerDefense = false;
	bool useLowerDefense = false;
	int countPoisoned = 2;
	int countLowerSpeed = 2;
	int countLowerAttack = 2;
	int countLowerDefense = 2;
public:
	Pokemon(string nm, string type, int hp, int mxhp, int atk, int def, int spd, int abt, int num) : Name(nm), Type(type), HP(hp), MaxHP(mxhp), Attack(atk), Defense(def), Speed(spd), Ability(abt), Number(num) 
	{
		if (Number < 10)
			Icon = "icons/color/00" + to_string(Number) + ".txt";
		else
			Icon = "icons/color/0" + to_string(Number) + ".txt";
	};

	void setHP(int hp) 
	{ 
		HP = hp; 
	};

	int getHP() const 
	{ 
		return HP; 
	};

	int getMaxHP() const 
	{ 
		return MaxHP;
	};

	void setAttack(int atk)
	{
		Attack = atk;
	};

	int getAttack() const 
	{ 
		return Attack; 
	};

	void setDefense(int def)
	{
		Defense = def;
	};

	int getDefense() const 
	{ 
		return Defense; 
	};

	void setSpeed(int spd)
	{
		Speed = spd;
	};

	int getSpeed() const
	{
		return Speed;
	};

	int getAbility() const
	{
		return Ability;
	};

	string getName() const
	{
		return Name;
	};

	string getType() const
	{
		return Type;
	};

	int getNumber() const
	{
		return Number;
	};

	string getIcon() const
	{
		return Icon;
	};

	void setDamge(int dmg)
	{
		Damage = dmg;
	};

	int getDamage() const
	{
		return Damage;
	};

	/////////////////////
	void setPoisoned(int x) //是否用過技能
	{
		Poisoned = x;
	};

	bool getPoisoned()
	{
		return Poisoned;
	};

	void setCountPoisoned(int c)
	{
		countPoisoned = c;
	};

	void detoxicify()
	{
		countPoisoned--;
	};

	int getCountPoisoned()
	{
		return countPoisoned;
	};

	void setUsePoisoned(int x)
	{
		usePoisoned = x;
	};

	bool getUsePoisoned()
	{
		return usePoisoned;
	};
	////////////////////

	////////////////////
	void setLowerSpeed(int x)
	{
		LowerSpeed = x;
	};

	bool getLowerSpeed()
	{
		return LowerSpeed;
	};

	void setCountLowerSpeed(int c)
	{
		countLowerSpeed = c;
	};

	void SpeedUp()
	{
		countLowerSpeed--;
	};

	int getCountLowerSpeed()
	{
		return countLowerSpeed;
	};

	void setUseLowerSpeed(int x)
	{
		useLowerSpeed = x;
	};

	bool getUseLowerSpeed()
	{
		return useLowerSpeed;
	};
	////////////////////

	////////////////////
	void setLowerDefense(int x)
	{
		LowerDefense = x;
	};

	bool getLowerDefense()
	{
		return LowerDefense;
	};

	void setCountLowerDefense(int c)
	{
		countLowerDefense = c;
	};

	void DefenseUp()
	{
		countLowerDefense--;
	};

	int getCountLowerDefense()
	{
		return countLowerDefense;
	};

	void setUseLowerDefense(int x)
	{
		useLowerDefense = x;
	};

	bool getUseLowerDefense()
	{
		return useLowerDefense;
	};
	////////////////////

	////////////////////
	void setLowerAttack(int x)
	{
		LowerAttack = x;
	};

	bool getLowerAttack()
	{
		return LowerAttack;
	};

	void setCountLowerAttack(int c)
	{
		countLowerAttack = c;
	};

	void AttackUp()
	{
		countLowerAttack--;
	};

	int getCountLowerAttack()
	{
		return countLowerAttack;
	};

	void setUseLowerAttack(int x)
	{
		useLowerAttack = x;
	};

	bool getUseLowerAttack()
	{
		return useLowerAttack;
	};
	////////////////////

	void showPokemon(int x, int y)
	{
		gotoxy(x, y);
		cout << "Name: " << getName() << endl;
		gotoxy(x, y + 1);
		cout << "Type: " << getType() << endl;
		gotoxy(x, y + 2);
		cout << "MaxHP: " << getMaxHP() << endl;
		gotoxy(x, y + 3);
		cout << "Attack: " << getAttack() << endl;
		gotoxy(x, y + 4);
		cout << "Defense: " << getDefense() << endl;
		gotoxy(x, y + 5);
		cout << "Speed: " << getSpeed() << endl;
	};

	virtual void showStats() 
	{
		cout << "Pokemon(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};

	virtual void attack(Pokemon &p) 
	{
		int dmg = getAttack() - p.getDefense();
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);
	};

	virtual void ability(Pokemon &p) {};
};

//Grass
class Bulbasaur : public Pokemon {
public:
	Bulbasaur() : Pokemon("Bulbasaur", "Grass", 50, 50, 16, 7, 4, 1, 1) {};

	void showStats()
	{
		cout << "Bulbasaur(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (p.getType() == "Fire" || p.getType() == "Grass" || p.getType() == "Poison" || p.getType() == "Flying" || p.getType() == "Bug")
			dmg = (getAttack() / 2) - p.getDefense();
		if (p.getType() == "Water" || p.getType() == "Ground")
			dmg = (getAttack() * 2) - p.getDefense();
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void ability(Pokemon &p)
	{
		if (getHP() + 3 < getMaxHP())
			setHP(getHP() + 3);

		cout << getName() << " uses Heal, " << getName() << " Heals 3 hp";
	};
private:
};

class Ivysaur: public Pokemon {
public:
	Ivysaur() : Pokemon("Ivysaur", "Grass", 65, 65, 19, 9, 6, 1, 2) {};

	void showStats()
	{
		cout << "Ivysaur(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (p.getType() == "Fire" || p.getType() == "Grass" || p.getType() == "Poison" || p.getType() == "Flying" || p.getType() == "Bug")
			dmg = (getAttack() / 2) - p.getDefense();
		if (p.getType() == "Water" || p.getType() == "Ground")
			dmg = (getAttack() * 2) - p.getDefense();
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void ability(Pokemon &p)
	{
		if (getHP() + 3 < getMaxHP())
			setHP(getHP() + 3);

		cout << getName() << " uses Heal, " << getName() << " Heals 3 hp";
	};
private:
};

class Venusaur: public Pokemon {
public:
	Venusaur() : Pokemon("Venusaur", "Grass", 80, 80, 22, 11, 8, 1, 3) {};

	void showStats()
	{
		cout << "Venusaur(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (p.getType() == "Fire" || p.getType() == "Grass" || p.getType() == "Poison" || p.getType() == "Flying" || p.getType() == "Bug")
			dmg = (getAttack() / 2) - p.getDefense();
		if (p.getType() == "Water" || p.getType() == "Ground")
			dmg = (getAttack() * 2) - p.getDefense();
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void ability(Pokemon &p)
	{
		if (getHP() + 3 < getMaxHP())
			setHP(getHP() + 3);

		cout << getName() << " uses Heal, " << getName() << " Heals 3 hp";
	};
private:
};

//Fire
class Charmander: public Pokemon {
public:
	Charmander() : Pokemon("Charmander", "Fire", 48, 48, 17, 6, 6, 2, 4) {};

	void showStats()
	{
		cout << "Charmander(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (p.getType() == "Fire" || p.getType() == "Water")
			dmg = (getAttack() / 2) - p.getDefense();
		if (p.getType() == "Grass" || p.getType() == "Bug")
			dmg = (getAttack() * 2) - p.getDefense();
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void ability(Pokemon &p)
	{
		int burn = rand() % 3 + 1;
		p.setHP(p.getHP() - burn);

		cout << getName() << " uses Burning, " << p.getName() << " got burned -" << burn << " hp";
	};
private:
};

class Charmeleon : public Pokemon {
public:
	Charmeleon() : Pokemon("Charmeleon", "Fire", 62, 62, 20, 8, 8, 2, 5) {};

	void showStats()
	{
		cout << "Charmeleon(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (p.getType() == "Fire" || p.getType() == "Water")
			dmg = (getAttack() / 2) - p.getDefense();
		if (p.getType() == "Grass" || p.getType() == "Bug")
			dmg = (getAttack() * 2) - p.getDefense();
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void ability(Pokemon &p)
	{
		int burn = rand() % 3 + 1;
		p.setHP(p.getHP() - burn);

		cout << getName() << " uses Burning, " << p.getName() << " got burned -" << burn << " hp";
	};
private:
};

class Charizard : public Pokemon {
public:
	Charizard() : Pokemon("Charizard", "Fire", 78, 78, 23, 10, 10, 2, 6) {};

	void showStats()
	{
		cout << "Charizard(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (p.getType() == "Fire" || p.getType() == "Water")
			dmg = (getAttack() / 2) - p.getDefense();
		if (p.getType() == "Grass" || p.getType() == "Bug")
			dmg = (getAttack() * 2) - p.getDefense();
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void ability(Pokemon &p)
	{
		int burn = rand() % 3 + 1;
		p.setHP(p.getHP() - burn);

		cout << getName() << " uses Burning, " << p.getName() << " got burned -" << burn << " hp";
	};
private:
};

//Water
class Squirtle : public Pokemon {
public:
	Squirtle() : Pokemon("Squirtle", "Water", 46, 46, 16, 7, 4, 3, 7) {};

	void showStats()
	{
		cout << "Squirtle(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (p.getType() == "Water" || p.getType() == "Grass")
			dmg = (getAttack() / 2) - p.getDefense();
		if (p.getType() == "Fire" || p.getType() == "Ground")
			dmg = (getAttack() * 2) - p.getDefense();
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void ability(Pokemon &p)
	{
		p.setHP(p.getHP() - p.getDamage() / 5);

		cout << getName() << " uses Counter Attack, " << p.getName() << " -" << p.getDamage() / 5 << " hp";
	};
private:
};

class Wartortle : public Pokemon {
public:
	Wartortle() : Pokemon("Wartortle", "Water", 60, 60, 18, 9, 6, 3, 8) {};

	void showStats()
	{
		cout << "Wartortle(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (p.getType() == "Water" || p.getType() == "Grass")
			dmg = (getAttack() / 2) - p.getDefense();
		if (p.getType() == "Fire" || p.getType() == "Ground")
			dmg = (getAttack() * 2) - p.getDefense();
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void ability(Pokemon &p)
	{
		p.setHP(p.getHP() - p.getDamage() / 5);

		cout << getName() << " uses Counter Attack, " << p.getName() << " -" << p.getDamage() / 5 << " hp";
	};
private:
};

class Blastoise : public Pokemon {
public:
	Blastoise() : Pokemon("Wartortle", "Water", 76, 76, 20, 11, 8, 3, 9) {};

	void showStats()
	{
		cout << "Blastoise(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (p.getType() == "Water" || p.getType() == "Grass")
			dmg = (getAttack() / 2) - p.getDefense();
		if (p.getType() == "Fire" || p.getType() == "Ground")
			dmg = (getAttack() * 2) - p.getDefense();
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void ability(Pokemon &p)
	{
		p.setHP(p.getHP() - p.getDamage() / 5);

		cout << getName() << " uses Counter Attack, " << p.getName() << " -" << p.getDamage() / 5 << " hp";
	};
private:
};

//Bug
class Caterpie : public Pokemon {
public:
	Caterpie() : Pokemon("Caterpie", "Bug", 46, 46, 16, 4, 5, 4, 10) {};

	void showStats()
	{
		cout << "Caterpie(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (p.getType() == "Fire" || p.getType() == "Poison" || p.getType() == "Flying")
			dmg = (getAttack() / 2) - p.getDefense();
		if (p.getType() == "Grass")
			dmg = (getAttack() * 2) - p.getDefense();
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void ability(Pokemon &p)
	{
		if (p.getAbility() == 9 || p.getAbility() == 11 || p.getAbility() == 12)
		{
			if (p.getAbility() == 9)
				p.setLowerSpeed(0);
			else if (p.getAbility() == 11)
				p.setLowerDefense(0);
			else if (p.getAbility() == 12)
				p.setLowerSpeed(0);		
		}
	};
private:
};

class Metapod : public Pokemon {
public:
	Metapod() : Pokemon("Metapod", "Bug", 58, 58, 16, 7, 3, 4, 11) {};

	void showStats()
	{
		cout << "Metapod(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (p.getType() == "Fire" || p.getType() == "Poison" || p.getType() == "Flying")
			dmg = (getAttack() / 2) - p.getDefense();
		if (p.getType() == "Grass")
			dmg = (getAttack() * 2) - p.getDefense();
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void ability(Pokemon &p)
	{
		if (p.getAbility() == 9 || p.getAbility() == 11 || p.getAbility() == 12)
		{
			if (p.getAbility() == 9)
				setSpeed(getSpeed() + 2);
			else if (p.getAbility() == 11)
				setDefense(getDefense() + 2);
			else if (p.getAbility() == 12)
				setAttack(getAttack() + 2);

			cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
		}
	};
private:
};

class Butterfree : public Pokemon {
public:
	Butterfree() : Pokemon("Butterfree", "Bug", 70, 70, 20, 10, 7, 4, 12) {};

	void showStats()
	{
		cout << "Butterfree(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (p.getType() == "Fire" || p.getType() == "Poison" || p.getType() == "Flying")
			dmg = (getAttack() / 2) - p.getDefense();
		if (p.getType() == "Grass")
			dmg = (getAttack() * 2) - p.getDefense();
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void ability(Pokemon &p)
	{
		if (p.getAbility() == 9 || p.getAbility() == 11 || p.getAbility() == 12)
		{
			if (p.getAbility() == 9)
				setSpeed(getSpeed() + 2);
			else if (p.getAbility() == 11)
				setDefense(getDefense() + 2);
			else if (p.getAbility() == 12)
				setAttack(getAttack() + 2);
		}
	};
private:
};

class Weedle : public Pokemon {
public:
	Weedle() : Pokemon("Weedle", "Bug", 47, 47, 16, 4, 5, 5, 13) {};

	void showStats()
	{
		cout << "Weedle(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (p.getType() == "Fire" || p.getType() == "Poison" || p.getType() == "Flying")
			dmg = (getAttack() / 2) - p.getDefense();
		if (p.getType() == "Grass")
			dmg = (getAttack() * 2) - p.getDefense();
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void ability(Pokemon &p)
	{
		int steal = rand() % 2 + 2;
		if (getHP() + steal < getMaxHP())
			setHP(getHP() + steal);

		cout << getName() << " uses Leech Life, " << getName() << " steals " << steal << " hp";
	};
private:
};

class Kakuna : public Pokemon {
public:
	Kakuna() : Pokemon("Kakuna", "Bug", 60, 60, 18, 6, 4, 5, 14) {};

	void showStats()
	{
		cout << "Kakuna(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (p.getType() == "Fire" || p.getType() == "Poison" || p.getType() == "Flying")
			dmg = (getAttack() / 2) - p.getDefense();
		if (p.getType() == "Grass")
			dmg = (getAttack() * 2) - p.getDefense();
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void ability(Pokemon &p)
	{
		int steal = rand() % 2 + 2;
		if (getHP() + steal < getMaxHP())
			setHP(getHP() + steal);

		cout << getName() << " uses Leech Life, " << getName() << " steals " << steal << " hp";
	};
private:
};

class Beedrill : public Pokemon {
public:
	Beedrill() : Pokemon("Beedrill", "Bug", 72, 72, 19, 8, 7, 5, 15) {};

	void showStats()
	{
		cout << "Beedrill(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (p.getType() == "Fire" || p.getType() == "Poison" || p.getType() == "Flying")
			dmg = (getAttack() / 2) - p.getDefense();
		if (p.getType() == "Grass")
			dmg = (getAttack() * 2) - p.getDefense();
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void ability(Pokemon &p)
	{
		int steal = rand() % 2 + 2;
		if (getHP() + steal < getMaxHP())
			setHP(getHP() + steal);

		cout << getName() << " uses Leech Life, " << getName() << " steals " << steal << " hp";
	};
private:
};

//Flying
class Pidgey : public Pokemon {
public:
	Pidgey() : Pokemon("Pidgey", "Flying", 53, 53, 15, 5, 6, 6, 16) {};

	void showStats()
	{
		cout << "Pidgey(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (p.getType() == "Electric")
			dmg = (getAttack() / 2) - p.getDefense();
		if (p.getType() == "Grass" || p.getType() == "Bug")
			dmg = (getAttack() * 2) - p.getDefense();
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void ability(Pokemon &p)
	{
		int *avoid = new int[2]();
		avoid[rand() % 2] = 1;

		if (avoid[rand() % 2] == 1)
		{
			setHP(getHP() + p.getDamage());

			cout << getName() << " uses Avoid, " << p.getName() << " attack missed";
		}
	};
private:
};

class Pidgeotto : public Pokemon {
public:
	Pidgeotto() : Pokemon("Pidgeotto", "Flying", 69, 69, 18, 7, 7, 6, 17) {};

	void showStats()
	{
		cout << "Pidgeotto(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (p.getType() == "Electric")
			dmg = (getAttack() / 2) - p.getDefense();
		if (p.getType() == "Grass" || p.getType() == "Bug")
			dmg = (getAttack() * 2) - p.getDefense();
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void ability(Pokemon &p)
	{
		int *avoid = new int[2]();
		avoid[rand() % 2] = 1;

		if (avoid[rand() % 2] == 1)
		{
			setHP(getHP() + p.getDamage());

			cout << getName() << " uses Avoid, " << p.getName() << " attack missed";
		}
	};
private:
};

class Pidgeot : public Pokemon {
public:
	Pidgeot() : Pokemon("Pidgeot", "Flying", 76, 76, 21, 9, 10, 6, 18) {};

	void showStats()
	{
		cout << "Pidgeot(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (p.getType() == "Electric")
			dmg = (getAttack() / 2) - p.getDefense();
		if (p.getType() == "Grass" || p.getType() == "Bug")
			dmg = (getAttack() * 2) - p.getDefense();
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void ability(Pokemon &p)
	{
		int *avoid = new int[2]();
		avoid[rand() % 2] = 1;

		if (avoid[rand() % 2] == 1)
		{
			setHP(getHP() + p.getDamage());

			cout << getName() << " uses Avoid, " << p.getName() << " attack missed";
		}
	};
private:
};

//Normal
class Rattata : public Pokemon {
public:
	Rattata() : Pokemon("Rattata", "Normal", 53, 53, 16, 8, 7, 0, 19) {};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void showStats()
	{
		cout << "Rattata(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};
private:
};

class Raticate : public Pokemon {
public:
	Raticate() : Pokemon("Raticate", "Normal", 72, 72, 20, 10, 10, 0, 20) {};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void showStats()
	{
		cout << "Raticate(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};
private:
};

//Flying
class Spearow : public Pokemon {
public:
	Spearow() : Pokemon("Spearow", "Flying", 52, 52, 17, 5, 7, 7, 21) {};

	void showStats()
	{
		cout << "Spearow(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (p.getType() == "Electric")
			dmg = (getAttack() / 2) - p.getDefense();
		if (p.getType() == "Grass" || p.getType() == "Bug")
			dmg = (getAttack() * 2) - p.getDefense();
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void ability(Pokemon &p)
	{
		int *atk = new int[2]();
		atk[rand() % 2] = 1;

		if (atk[rand() % 2] == 1)
		{
			p.setHP(p.getHP() - getDamage());

			cout << getName() << " uses Double Attack, " << p.getName() << " -" << getDamage() << " hp";

			setDamge(getDamage() * 2);
		}
	};
private:
};

class Fearow : public Pokemon {
public:
	Fearow() : Pokemon("Fearow", "Flying", 74, 74, 21, 8, 10, 7, 22) {};

	void showStats()
	{
		cout << "Fearow(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (p.getType() == "Electric")
			dmg = (getAttack() / 2) - p.getDefense();
		if (p.getType() == "Grass" || p.getType() == "Bug")
			dmg = (getAttack() * 2) - p.getDefense();
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void ability(Pokemon &p)
	{
		int *atk = new int[2]();
		atk[rand() % 2] = 1;

		if (atk[rand() % 2] == 1)
		{
			p.setHP(p.getHP() - getDamage());

			cout << getName() << " uses Double Attack, " << p.getName() << " -" << getDamage() << " hp";

			setDamge(getDamage() * 2);
		}
	};
private:
};

//Poison
class Ekans : public Pokemon {
public:
	Ekans() : Pokemon("Ekans", "Poison", 53, 53, 16, 6, 5, 8, 23) {};

	void showStats()
	{
		cout << "Ekans(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (p.getType() == "Poison" || p.getType() == "Ground")
			dmg = (getAttack() / 2) - p.getDefense();
		if (p.getType() == "Grass")
			dmg = (getAttack() * 2) - p.getDefense();
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void ability(Pokemon &p)
	{
		if (p.getPoisoned() == false)
		{
			if (getUsePoisoned() == false)
			{
				p.setPoisoned(1);
				setUsePoisoned(1);

				cout << getName() << " uses Poison, " << p.getName() << " got poisoned";
			}
		}
		else
		{
			if (p.getCountPoisoned() > 0)
			{
				p.setHP(p.getHP() - 2);
				p.detoxicify();
				cout << p.getName() << " got poisoned -2 hp, remian " << p.getCountPoisoned() << " round";
			}
		}
	};
private:
};

class Arbok : public Pokemon {
public:
	Arbok() : Pokemon("Arbok", "Poison", 73, 73, 21, 9, 8, 8, 24) {};

	void showStats()
	{
		cout << "Arbok(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (p.getType() == "Poison" || p.getType() == "Ground")
			dmg = (getAttack() / 2) - p.getDefense();
		if (p.getType() == "Grass")
			dmg = (getAttack() * 2) - p.getDefense();
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void ability(Pokemon &p)
	{
		if (p.getPoisoned() == false)
		{
			if (getUsePoisoned() == false)
			{
				p.setPoisoned(1);
				setUsePoisoned(1);

				cout << getName() << " uses Poison, " << p.getName() << " got poisoned";
			}
		}
		else
		{
			if (p.getCountPoisoned() > 0)
			{
				p.setHP(p.getHP() - 2);
				p.detoxicify();
				cout << p.getName() << " got poisoned -2 hp, remian " << p.getCountPoisoned() << " round";
			}
		}
	};
private:
};

//Electric
class Pikachu : public Pokemon {
public:
	Pikachu() : Pokemon("Pikachu", "Electric", 52, 52, 17, 5, 9, 9, 25) {};

	void showStats()
	{
		cout << "Pikachu(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (p.getType() == "Electric" || p.getType() == "Grass")
			dmg = (getAttack() / 2) - p.getDefense();
		if (p.getType() == "Water" || p.getType() == "Flying")
			dmg = (getAttack() * 2) - p.getDefense();
		if (p.getType() == "Ground")
			dmg = 0;
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void ability(Pokemon &p)
	{
		if (p.getLowerSpeed() == false)
		{
			if (getUseLowerSpeed() == false)
			{
				if (p.getAbility() == 4)
					cout << getName() << " use Lower Speed missed";
				else
				{
					p.setLowerSpeed(1);
					setUseLowerSpeed(1);

					cout << getName() << " uses Lower Speed, " << p.getName() << " got reduced speed";
				}
			}
		}
		else
		{
			if (p.getCountLowerSpeed() > 0)
			{
				p.SpeedUp();
				if (p.getCountLowerSpeed() == 2)
				{
					p.setSpeed(p.getSpeed() - 2);
					cout << p.getName() << " got reduced speed -2 speed, remian " << p.getCountLowerSpeed() << " round";
				}
				cout << p.getName() << " got reduced speed, remian " << p.getCountLowerSpeed() << " round";
			}
		}
	};
private:
};

class Raichu : public Pokemon {
public:
	Raichu() : Pokemon("Raichu", "Electric", 68, 68, 20, 9, 11, 9, 26) {};

	void showStats()
	{
		cout << "Raichu(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (p.getType() == "Electric" || p.getType() == "Grass")
			dmg = (getAttack() / 2) - p.getDefense();
		if (p.getType() == "Water" || p.getType() == "Flying")
			dmg = (getAttack() * 2) - p.getDefense();
		if (p.getType() == "Ground")
			dmg = 0;
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void ability(Pokemon &p)
	{
		if (p.getLowerSpeed() == false)
		{
			if (getUseLowerSpeed() == false)
			{
				if (p.getAbility() == 4)
					cout << getName() << " use Lower Speed missed";
				else
				{
					p.setLowerSpeed(1);
					setUseLowerSpeed(1);

					cout << getName() << " uses Lower Speed, " << p.getName() << " got reduced speed";
				}
			}
		}
		else
		{
			if (p.getCountLowerSpeed() > 0)
			{
				p.SpeedUp();
				if (p.getCountLowerSpeed() == 2)
				{
					p.setSpeed(p.getSpeed() - 2);
					cout << p.getName() << " got reduced speed -2 speed, remian " << p.getCountLowerSpeed() << " round";
				}
				cout << p.getName() << " got reduced speed, remian " << p.getCountLowerSpeed() << " round";
			}
		}
	};
private:
};

//Ground
class Sandshrew : public Pokemon {
public:
	Sandshrew() : Pokemon("Sandshrew", "Ground", 56, 56, 16, 7, 4, 10, 27) {};

	void showStats()
	{
		cout << "Sandshrew(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (p.getType() == "Grass" || p.getType() == "Bug")
			dmg = (getAttack() / 2) - p.getDefense();
		if (p.getType() == "Fire" || p.getType() == "Electric" || p.getType() == "Poison")
			dmg = (getAttack() * 2) - p.getDefense();
		if (p.getType() == "Flying")
			dmg = 0;
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void ability(Pokemon &p)
	{
		p.setDamge(p.getDamage() - 2);
		setHP(getHP() + 2);

		cout << getName() << " uses Rock Skin, " << p.getName() << " -2 damage";
	};
private:
};

class Sandslash : public Pokemon {
public:
	Sandslash() : Pokemon("Sandslash", "Ground", 76, 76, 19, 10, 4, 10, 28) {};

	void showStats()
	{
		cout << "Sandslash(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (p.getType() == "Grass" || p.getType() == "Bug")
			dmg = (getAttack() / 2) - p.getDefense();
		if (p.getType() == "Fire" || p.getType() == "Electric" || p.getType() == "Poison")
			dmg = (getAttack() * 2) - p.getDefense();
		if (p.getType() == "Flying")
			dmg = 0;
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void ability(Pokemon &p)
	{
		p.setDamge(p.getDamage() - 2);
		setHP(getHP() + 2);

		cout << getName() << " uses Rock Skin, " << p.getName() << " -2 damage";
	};
private:
};

//Poison
class Nidoran_Female : public Pokemon {
public:
	Nidoran_Female() : Pokemon("Nidoran_Female", "Poison", 55, 55, 16, 7, 4, 11, 29) {};

	void showStats()
	{
		cout << "Nidoran_Female(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (p.getType() == "Poison" || p.getType() == "Ground")
			dmg = (getAttack() / 2) - p.getDefense();
		if (p.getType() == "Grass")
			dmg = (getAttack() * 2) - p.getDefense();
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void ability(Pokemon &p)
	{
		if (p.getLowerDefense() == false)
		{
			if (getUseLowerDefense() == false)
			{
				if (p.getAbility() == 4)
					cout << getName() << " use Lower Defense missed";
				else
				{
					p.setLowerDefense(1);
					setUseLowerDefense(1);

					cout << getName() << " uses Lower Defense, " << p.getName() << " got reduced defense";
				}
			}
		}
		else
		{
			if (p.getCountLowerDefense() > 0)
			{
				p.DefenseUp();
				if (p.getCountLowerDefense() == 2)
				{
					p.setDefense(p.getDefense() - 2);
					cout << p.getName() << " got reduced defense -2 defense, remian " << p.getCountLowerDefense() << " round";
				}
				cout << p.getName() << " got reduced defense, remian " << p.getCountLowerDefense() << " round";
			}
		}
	};
private:
};

class Nidorina : public Pokemon {
public:
	Nidorina() : Pokemon("Nidorina", "Poison", 70, 70, 19, 9, 6, 11, 30) {};

	void showStats()
	{
		cout << "Nidorina(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (p.getType() == "Poison" || p.getType() == "Ground")
			dmg = (getAttack() / 2) - p.getDefense();
		if (p.getType() == "Grass")
			dmg = (getAttack() * 2) - p.getDefense();
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void ability(Pokemon &p)
	{
		if (p.getLowerDefense() == false)
		{
			if (getUseLowerDefense() == false)
			{
				if (p.getAbility() == 4)
					cout << getName() << " use Lower Defense missed";
				else
				{
					p.setLowerDefense(1);
					setUseLowerDefense(1);

					cout << getName() << " uses Lower Defense, " << p.getName() << " got reduced defense";
				}
			}
		}
		else
		{
			if (p.getCountLowerDefense() > 0)
			{
				p.DefenseUp();
				if (p.getCountLowerDefense() == 2)
				{
					p.setDefense(p.getDefense() - 2);
					cout << p.getName() << " got reduced defense -2 defense, remian " << p.getCountLowerDefense() << " round";
				}
				cout << p.getName() << " got reduced defense, remian " << p.getCountLowerDefense() << " round";
			}
		}
	};
private:
};

class Nidoqueen : public Pokemon {
public:
	Nidoqueen() : Pokemon("Nidoqueen", "Poison", 85, 85, 21, 11, 8, 11, 31) {};

	void showStats()
	{
		cout << "Nidoqueen(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (p.getType() == "Poison" || p.getType() == "Ground")
			dmg = (getAttack() / 2) - p.getDefense();
		if (p.getType() == "Grass")
			dmg = (getAttack() * 2) - p.getDefense();
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void ability(Pokemon &p)
	{
		if (p.getLowerDefense() == false)
		{
			if (getUseLowerDefense() == false)
			{
				if (p.getAbility() == 4)
					cout << getName() << " use Lower Defense missed";
				else
				{
					p.setLowerDefense(1);
					setUseLowerDefense(1);

					cout << getName() << " uses Lower Defense, " << p.getName() << " got reduced defense";
				}
			}
		}
		else
		{
			if (p.getCountLowerDefense() > 0)
			{
				p.DefenseUp();
				if (p.getCountLowerDefense() == 2)
				{
					p.setDefense(p.getDefense() - 2);
					cout << p.getName() << " got reduced defense -2 defense, remian " << p.getCountLowerDefense() << " round";
				}
				cout << p.getName() << " got reduced defense, remian " << p.getCountLowerDefense() << " round";
			}
		}
	};
private:
};

class Nidoran_Male : public Pokemon {
public:
	Nidoran_Male() : Pokemon("Nidoran_Male", "Poison", 52, 52, 17, 6, 5, 12, 32) {};

	void showStats()
	{
		cout << "Nidoran_Male(" << setw(3) << getHP() << " / " << setw(3) << getMaxHP() << " )" << endl;
	};

	void attack(Pokemon &p)
	{
		int dmg = getAttack() - p.getDefense();
		if (p.getType() == "Poison" || p.getType() == "Ground")
			dmg = (getAttack() / 2) - p.getDefense();
		if (p.getType() == "Grass")
			dmg = (getAttack() * 2) - p.getDefense();
		if (dmg <= 0)
			dmg = 0;
		setDamge(dmg);
		p.setHP(p.getHP() - dmg);

		cout << getName() << " attacks " << p.getName() << ", " << p.getName() << " -" << getDamage() << " hp";
	};

	void ability(Pokemon &p)
	{
		if (p.getLowerAttack() == false)
		{
			if (getUseLowerAttack() == false)
			{
				if (p.getAbility() == 4)
					cout << getName() << " use Lower Attack missed";
				else
				{
					p.setLowerAttack(1);
					setUseLowerAttack(1);

					cout << getName() << " uses Lower Attack, " << p.getName() << " got reduced attack";
				}
			}
		}
		else
		{
			if (p.getCountLowerAttack() > 0)
			{
				p.AttackUp();
				if (p.getCountLowerAttack() == 2)
				{
					p.setAttack(p.getAttack() - 2);
					cout << p.getName() << " got reduced attack -2 attack, remian " << p.getCountLowerAttack() << " round";
				}
				cout << p.getName() << " got reduced attack, remian " << p.getCountLowerAttack() << " round";
			}
		}
	};
private:
};

template <class T>
class Player {
public:
	Player(string nm, string gd)
	{
		Name = nm;
		Gender = gd;
	};

	void catchPokemon(T* p) //抓寵物
	{
		MyPokemons.push_back(p);
	};

	T* getCurrentPokemon() //回傳活著的寵物
	{
		for (int i = 0; i < 3; i++)
		{
			if (MyPokemons[i]->getHP() > 0)
				return MyPokemons[i];
		}

		return NULL;
	};

	/*void showAlivePokemons()
	{
		for (int i = 0; i < MyPokemons.size(); i++)
			if (MyPokemons[i]->getHP() > 0)
				MyPokemons[i]->showStats();
	};*/

	void showMyPokemons(int x, int y) //展示寵物
	{
		for (int i = 0; i < MyPokemons.size(); i++)
		{
			gotoxy(x, y + i);
			MyPokemons[i]->showStats();
		}
	};

	void dropPokemon(int index) //丟棄寵物
	{
		MyPokemons.erase(MyPokemons.begin() + (index - 1));
	};

	void setPokemon(T* p1, T* p2, T* p3) //直接給寵物debug用
	{
		MyPokemons.push_back(p1);
		MyPokemons.push_back(p2);
		MyPokemons.push_back(p3);
	};

	void recoverPokemon() //戰鬥結束後恢復寵物體力
	{
		for (int i = 0; i < MyPokemons.size(); i++)
		{
			MyPokemons[i]->setHP(MyPokemons[i]->getMaxHP());

			MyPokemons[i]->setPoisoned(0);
			MyPokemons[i]->setCountPoisoned(2);

			MyPokemons[i]->setLowerSpeed(0);
			MyPokemons[i]->setCountLowerSpeed(2);

			MyPokemons[i]->setLowerDefense(0);
			MyPokemons[i]->setCountLowerDefense(2);

			MyPokemons[i]->setLowerAttack(0);
			MyPokemons[i]->setCountLowerAttack(2);
		}
	};

	string getName()
	{
		return Name;
	};

	string getGender()
	{
		return Gender;
	};

	int getPokeNum()
	{
		return MyPokemons.size();
	};

	class ThreePokemons : public exception {
		string msg;
	public:
		ThreePokemons() : msg("") {};
		virtual const char* what() const noexcept override { return "You need 3 pokemons to battle!!"; };
	};
private:
	string Name;
	string Gender;
	vector<T*> MyPokemons;
};

class NPC : public Player<Pokemon>{
public:
	NPC(string nm) : Player(nm, "Boy") {};

private:
};
#endif