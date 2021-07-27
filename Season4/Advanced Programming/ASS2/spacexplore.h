#pragma once
#ifndef SPACETRAVEL_H
#define SPACETRAVEL_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>

#define SPACESHIP_ENCOUNTER 1
#define PLANET_ENCOUNTER 2
#define TRADE_ENCOUNTER 3
#define EMPTY_SECTOR 4
#define OTHER 5

#define EVENT_TRADE 0
#define EVENT_CONFLICT 1

int get_random(int start, int end);
std::string create_name(int len);

/**
 * Crew and implementations 
 */
class Crew
{
protected:
	int member;
	std::string name;
	int age;
	int ability;

public:
	Crew()
	{
		member = get_random(5, 30);
	}
	int get_member()
	{
		return member;
	}
	void display_officer()
	{
		std::cout << "1. Name -> " << name << " 2. Age -> " << age << " 3. Ability -> " << ability << std::endl;
	}
	virtual int get_ability() { return 1; }
	virtual std::string get_name() { return NULL; }
	virtual int get_age() { return 1; }
};

class Captain : public Crew
{
protected:
public:
	Captain()
	{
		name = create_name(8);
		age = get_random(30, 60);
		ability = get_random(10, 25);
	}
	std::string get_name()
	{
		return name;
	}
	int get_age()
	{
		return age;
	}
};

class Pilot : public Crew
{
protected:
public:
	Pilot()
	{
		name = create_name(8);
		age = get_random(18, 60);
		ability = get_random(5, 25);
	}
	std::string get_name()
	{
		return name;
	}
};

class Engineer : public Crew
{
protected:
public:
	Engineer()
	{
		name = create_name(8);
		age = get_random(18, 60);
		ability = get_random(10, 25);
	}
	std::string get_name()
	{
		return name;
	}
};

class Weaponsmith : public Crew
{
protected:
public:
	Weaponsmith()
	{
		name = create_name(8);
		age = get_random(18, 60);
		ability = get_random(1, 20);
	}
	std::string get_name()
	{
		return name;
	}
};

class Miner : public Crew
{
protected:
public:
	Miner()
	{
		name = create_name(8);
		age = get_random(18, 60);
		ability = get_random(1, 20);
	}
	int get_ability()
	{
		return ability;
	};
	std::string get_name()
	{
		return name;
	}
};

/**
 * Sector and implementations
 */
class Sector
{
protected:
	std::string name;
	int num_fuel;
	int num_food;

public:
	Sector()
	{
		name = create_name(8);
		num_fuel = get_random(1, 500);
		num_food = get_random(1, 500);
	}
	virtual int get_hp() { return 1; }
	virtual int get_civilization_type() { return 1; }
	virtual void set_hp(int drop) {}
	virtual int get_attack() { return 1; }
	virtual int get_defense() { return 1; }
	virtual int get_fuel() { return 1; }
	virtual int get_food() { return 1; }
	virtual int occur_event() { return 1; }
	virtual int get_raw_num() { return 1; }
};

class Spaceship : public Sector
{
protected:
	int civilization_type;
	int hp;
	int defense;
	int attack;

public:
	Spaceship()
	{
		civilization_type = get_random(2200, 8800);
		hp = get_random(50, 150);
		defense = get_random(50, 200);
		attack = get_random(80, 300);
	}
	std::string get_name()
	{
		return name;
	}
	int occur_event()
	{
		return get_random(0, 1);
	}
	int get_civilization_type()
	{
		return civilization_type;
	}
	int get_hp()
	{
		return hp;
	}
	void set_hp(int drop)
	{
		hp = drop > hp ? 0 : (hp - drop);
	}
	int get_attack()
	{
		return attack;
	}
	int get_defense()
	{
		return defense;
	}
	int get_fuel()
	{
		return num_fuel;
	}
	int get_food()
	{
		return num_food;
	}
};

class Tradingstation : public Sector
{
public:
	Tradingstation() {}
	std::string get_name()
	{
		return name;
	}
};

class Planet : public Sector
{
protected:
	int rawNum;

public:
	Planet()
	{
		rawNum = get_random(300, 1000);
	}
	std::string get_name()
	{
		return name;
	}
	int get_raw_num()
	{
		return rawNum;
	}
};

/**
 * Stats and implementations 
 */

class Stats
{
protected:
	int quantity;
	int price;
	int consumption;

public:
};

class Food : public Stats
{
protected:
public:
	Food() {}
	int get_price();
	int get_capacity();
	void consume_food(int unit);
	void set_food(int food);
	void load_food(int food);
};

class Fuel : protected Stats
{
protected:
public:
	Fuel() {}
	void set_fuel(int fuel);
	int get_price();
	int get_capacity();
	void consume_fuel(int unit);
	void load_fuel(int fule);
};

class Raw : public Stats
{
public:
	Raw() {}
	void set_raw(int raw);
	int get_price();
	int get_capacity();
	void load_raw(int raw);
	void sell_raw(int raw);
};

class Money : protected Stats
{
public:
	Money() {}
	void set_money(int money);
	int get_capacity();
	void change_money(int money);
};

class Ship
{
private:
	std::string name;
	int capacity;
	int health;
	int attack;
	int defense;

protected:
	Food ship_food;
	Fuel ship_fuel;
	Money ship_money;
	Raw ship_raws;
	Crew *captain;
	Crew *pilot;
	Crew *engineer;
	Crew *weaponsmith;
	Crew *miner;

public:
	Ship()
	{
		name = "";
		capacity = 0;
		health = 0;
		attack = 0;
		defense = 0;
	}

	void init_stats();
	Ship(std::string, int, int, int, int);
	void display_info();
	int next_sector();
	int check_food();
	int check_fuel();
	int check_money();
	void consume_resource(int time);
	int get_crew();
	void display_crew_info();
	int check_resource();

	void encounter_spaceship();
	void arrive_planet();
	void arrive_tradingstation();

	void gain_materials(int food, int fuel);

	int get_capacity()
	{
		return capacity;
	}
	int get_health_point()
	{
		return health;
	}
	int get_attack()
	{
		return attack;
	}
	int get_defense()
	{
		return defense;
	}
	void set_health(int drop)
	{
		health = drop >= health ? 0 : (health - drop);
	}
	void recover_hp(int recover, int maxHP)
	{
		health = (health + recover) <= maxHP ? (health + recover) : maxHP;
	}

	void gain_award(int food, int fuel);
	int get_current_resource()
	{
		return ship_fuel.get_capacity() + ship_food.get_capacity() + ship_raws.get_capacity();
	}
	int get_money()
	{
		return ship_money.get_capacity();
	}
	int food_price()
	{
		return ship_food.get_price();
	}
	int fuel_price()
	{
		return ship_fuel.get_price();
	}
	int raw_price()
	{
		return ship_raws.get_price();
	}
	void start_mining(Sector *);
	void start_trading(Sector *);

	int fuel_ran_out(int tripTime);

	void black_hole();

	int get_age(Crew *officer)
	{
		return officer->get_age();
	}
	std::string get_name(Crew *officer)
	{
		return officer->get_name();
	}
	void show_display_officer()
	{
		captain->display_officer();
	}
};

void space_journey(Ship, int);

#endif
