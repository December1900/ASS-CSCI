#include "spacexplore.h"
#include "base.h"

using namespace std;

void Ship::init_stats()
{
	int init;
	init = get_capacity();
	init = init / 2;
	ship_food.set_food(init);
	ship_fuel.set_fuel(init);
	init = get_random(100, 500);
	ship_money.change_money(init);
	ship_raws.set_raw(0);
}

void Ship::display_crew_info()
{
	cout << "***************************************************" << endl;
	cout << "Captain: ";
	captain->display_officer();
	cout << "Pilot: ";
	pilot->display_officer();
	cout << "Engineer: ";
	engineer->display_officer();
	cout << "Weaponsmith: ";
	weaponsmith->display_officer();
	cout << "Miner: ";
	miner->display_officer();
}

Ship::Ship(std::string nm, int cap, int hlt, int att, int def)
{
	name = nm;
	capacity = cap;
	health = hlt;
	attack = att;
	defense = def;
	init_stats();
	captain = new Captain();
	pilot = new Pilot();
	engineer = new Engineer();
	miner = new Miner();
	weaponsmith = new Weaponsmith();
}

int Ship::check_resource()
{
	int food_left;
	int fuel_left;
	int crew_left;
	cout << "The core stats now have:" << endl;
	crew_left = captain->get_member();
	cout << "crew: " << crew_left << endl;
	food_left = ship_food.get_capacity();
	cout << "food: " << food_left << endl;

	fuel_left = ship_fuel.get_capacity();
	cout << "fuel: " << fuel_left << endl;
	cout << "money: " << check_money() << endl;
	cout << "***************************************************" << endl;
	if (!food_left || !crew_left || !fuel_left)
		return 0;
	else
		return 1;
}

int get_hurt(int m_attack, int m_defense, int attack)
{
	double dam_rate;
	int hurt;
	dam_rate = 1 - 1 / (1 + m_defense / 15.0);
	hurt = attack * (1 - dam_rate);

	return hurt;
}

void Ship::encounter_spaceship(void)
{
	Sector *visit = new Spaceship();
	int enc_civ;
	int happen;
	int epoch = 1;
	int ship_hp_drop = 0;
	int encounter_hp_drop = 0;
	cout << "Encounter the spaceship and Fire......" << endl;
	happen = visit->occur_event();
	enc_civ = visit->get_civilization_type();
	cout << "Civilization type: " << enc_civ << endl;

	if (happen == EVENT_CONFLICT)
	{

		while (get_health_point() != 0 && visit->get_hp() != 0)
		{
			ship_hp_drop = get_hurt(get_attack(), get_defense(), visit->get_attack());
			encounter_hp_drop = get_hurt(visit->get_attack(), visit->get_defense(), get_attack());
			set_health(ship_hp_drop);
			visit->set_hp(encounter_hp_drop);
			cout << "Epoch " << epoch-- << ": Our ship HP -> " << get_health_point() << "; Encounter ship HP -> " << visit->get_hp() << endl;
			epoch++;
		}
		if (get_health_point() == 0)
		{

			cout << "=====================NO HEALTH=====================" << endl;
			cout << "Fight " << epoch << " epochs, journey ends!" << endl;
			cout << "Total " << get_crew() << " of crews died !" << endl;
			display_crew_info();
			cout << "===================================================" << endl;

			exit(0);
		}
		else
		{
			cout << "Win and gain materials" << endl;
			gain_materials(get_random(0, 50), get_random(0, 50));
			check_fuel();
			check_food();
		}
	}
}

void Ship::arrive_planet(void)
{
	Sector *arrive = new Planet();
	int happen = 0;
	cout << "You arrive in the planet....." << endl;
	start_mining(arrive);
}

void Ship::arrive_tradingstation(void)
{
	cout << "You arrive in the trading station ..." << endl;

	Sector *arrive = new Tradingstation();
	start_trading(arrive);
}

void Ship::gain_materials(int food, int fuel)
{
	int current_cap = 0;
	int storage = 0;
	int load_food = 0;
	int load_fuel = 0;
	cout << "Gaining materials " << endl;
	current_cap = ship_food.get_capacity() + ship_fuel.get_capacity() + ship_raws.get_capacity();

	if (capacity > current_cap)
	{
		storage = capacity - current_cap;
		load_food = storage / 2;
		load_food = food > load_food ? load_food : food;
		load_fuel = storage - load_food;
		load_fuel = fuel > load_fuel ? load_fuel : food;
	}

	ship_food.load_food(load_food);
	ship_fuel.load_fuel(load_fuel);
}

int Ship::next_sector(void)
{
	int flag = get_random(1, 20);

	if (flag <= 8)
		flag = SPACESHIP_ENCOUNTER;
	else if (flag > 8 && flag <= 12)
		flag = PLANET_ENCOUNTER;
	else if (flag > 12 && flag <= 16)
		flag = TRADE_ENCOUNTER;
	else if (flag > 16)
		flag = OTHER;
	else
		flag = EMPTY_SECTOR;
	return flag;
}

int Ship::check_food(void)
{
	return ship_food.get_capacity();
}

int Ship::check_fuel(void)
{
	return ship_fuel.get_capacity();
}

int Ship::check_money(void)
{
	return ship_money.get_capacity();
}

void Ship::consume_resource(int time)
{
	ship_food.consume_food(time);
	ship_fuel.consume_fuel(time);
}

int Ship::get_crew()
{
	return captain->get_member();
}

int Ship::fuel_ran_out(int tripTime)
{
	int fuel_left;
	consume_resource(tripTime);

	fuel_left = check_fuel();

	return fuel_left;
}

void Ship::start_trading(Sector *visit)
{
	int storage = 0;
	int money = 0;
	int money_gain = 0;
	int fuel_cost = 0;
	int food_cost = 0;
	int raw_space = 0;

	cout << "Start buying resource ..." << endl;

	raw_space = ship_raws.get_capacity();
	money = get_money();
	cout << "Own money: " << money << endl;

	if (raw_space != 0)
	{
		cout << "Begin to sell raw materials......" << endl;
		ship_raws.sell_raw(raw_space);

		storage = get_capacity() - get_current_resource();
		money_gain = raw_space * raw_price();
		cout << raw_space << " kg raw materials sold out, and make " << money_gain << " money." << endl;

		money += money_gain;
		ship_money.change_money(money);

		cout << "Now own money: " << money << endl;
	}

	if (storage <= 0 && money > 0)
	{
		cout << "Tank full !!!" << endl;
	}

	if (money >= 50)
	{

		fuel_cost = floor(money / 2.5) + 2;
		food_cost = money - fuel_cost;

		cout << "Begin to buy the stats......" << endl;

		cout << "Fuel cost " << fuel_cost << " money, food cost " << food_cost << " money " << endl;

		money -= fuel_cost + food_cost;

		ship_fuel.load_fuel(fuel_cost / fuel_price());
		ship_food.load_food(food_cost / food_price());
		ship_money.change_money(money);
	}
	else
	{
		cout << "Not enough money, cannot make trade !" << endl;
	}
}

void Ship::start_mining(Sector *visit)
{
	int storage = get_capacity() - get_current_resource();
	int min_ab = miner->get_ability();
	int num_mine;
	int num_raw;
	int max_mine = get_capacity() / 3;

	cout << "Start mining raw ..." << endl;

	num_raw = visit->get_raw_num();
	num_mine = num_raw * min_ab / 150;
	if (storage > 0)
	{
		num_mine = num_mine > max_mine ? max_mine : num_mine;
		ship_raws.load_raw(num_mine);
	}
}

void Ship::black_hole(void)
{
	cout << "====================BLACK HOLE=====================" << endl;
	cout << "Journey ends because of black hole." << endl;
	cout << "There are " << get_crew() << " of crews died !" << endl;
	display_crew_info();
	cout << "===================================================" << endl;
	exit(0);
}

void space_journey(Ship chosen_ship, int num)
{
	int nxt_sector = 0;
	int tripTime = 0;
	int maxHP = 0;

	maxHP = chosen_ship.get_health_point();
	chosen_ship.display_crew_info();

	for (int i = 0; i < num; i++)
	{

		if (!chosen_ship.check_resource())
		{
			cout << "=====================NO FOOD=======================" << endl;
			cout << "Journey ends because of insufficient food." << endl;
			cout << "There are " << chosen_ship.get_crew() << " of crews died !" << endl;
			chosen_ship.display_crew_info();
			cout << "===================================================" << endl;
			exit(0);
		}

		nxt_sector = chosen_ship.next_sector();
		tripTime = get_random(1, 20);

		if (chosen_ship.get_health_point() < maxHP)
		{
			chosen_ship.recover_hp(2 * tripTime, maxHP);
			cout << "Recover HP: " << chosen_ship.get_health_point() << endl;
		}

		if (!chosen_ship.fuel_ran_out(tripTime))
		{
			cout << "=====================NO FUEL=======================" << endl;
			cout << "Journey ends because of insufficient fule." << endl;
			cout << "There are " << chosen_ship.get_crew() << " of crews died !" << endl;
			chosen_ship.display_crew_info();
			cout << "===================================================" << endl;
			exit(0);
		}

		switch (nxt_sector)
		{
		case SPACESHIP_ENCOUNTER:
			cout << endl;
			cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
			cout << "Sector " << i + 1 << ": Spaceship encounter !" << endl;
			chosen_ship.encounter_spaceship();
			cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
			break;
		case PLANET_ENCOUNTER:
			cout << endl;
			cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
			cout << "Sector " << i + 1 << ": Planet encounter !" << endl;
			chosen_ship.arrive_planet();
			cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
			break;
		case TRADE_ENCOUNTER:
			cout << endl;
			cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
			cout << "Sector " << i + 1 << ": Trading station encounter!" << endl;
			chosen_ship.arrive_tradingstation();
			cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
			break;
		case OTHER:
			cout << endl;
			cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
			cout << "Sector " << i + 1 << ": Other." << endl;
			chosen_ship.black_hole();
			cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		default:
			cout << endl;
			cout << "Sector " << i + 1 << ": Empty, next trip..." << endl;
			cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
			break;
		}
	}
}

int Food::get_price()
{
	return price;
}
int Food::get_capacity()
{
	return quantity;
}

void Food::set_food(int food)
{
	quantity = food;
	consumption = 2;
	price = 2;
}
void Food::load_food(int food)
{
	cout << "Add " << food << " kg foods" << endl;
	quantity += food;
}

void Fuel::load_fuel(int fule)
{
	cout << "Add " << fule << " kg fules" << endl;
	quantity += fule;
}

void Food::consume_food(int unit)
{
	int result;
	result = consumption * unit;
	quantity = result > quantity ? 0 : (quantity - result);
	cout << result << " kg food consumed !" << endl;
}

void Fuel::consume_fuel(int unit)
{
	int result;
	result = consumption * unit;
	quantity = result > quantity ? 0 : (quantity - result);
	cout << result << " kg fules consumed !" << endl;
}

void Fuel::set_fuel(int fuel)
{
	quantity = fuel;
	consumption = 2;
	price = 4;
}

int Fuel::get_price()
{
	return price;
}

int Fuel::get_capacity()
{
	return quantity;
}

void Money::set_money(int money)
{
	quantity = money;
}
int Money::get_capacity()
{
	return quantity;
}

void Money::change_money(int money)
{
	quantity = money;
}

int Raw::get_price()
{
	return price;
}
void Raw::set_raw(int raw)
{
	quantity = raw;
	price = 2;
}
int Raw::get_capacity()
{
	return quantity;
}
void Raw::load_raw(int raw)
{
	cout << "Add " << raw << " kg raw" << endl;
	quantity += raw;
}
void Raw::sell_raw(int raw)
{
	cout << "Sold " << raw << " kg raw" << endl;
	quantity -= raw;
}

void Ship::display_info()
{
	cout << name << "     " << capacity << "     " << health << "     " << attack << "     " << defense << "     " << std::endl;
}

int main(int argc, char *argv[])
{
	int num = 0;
	int chosen_ship = 0;
	string spaceship_name;
	int capacity = 0;
	int hp = 0;
	int atk_value = 0;
	int dfs_value = 0;
	int nxt_sector = 0;

	if (argc != 2)
	{
		cout << "Input error!" << endl;
		cout << "Please input ./JSE sector numbers " << endl;
		return 0;
	}

	num = atoi(argv[1]);
	if (num > 50 || num < 1)
	{
		cout << "Sector numbers should be greater than 0 and less than 51." << endl;
		return 0;
	}
	if (num < 20)
	{
		cout << "@Tips: Up to 20 sectors might be a fairly high chance of survival for journeys" << endl;
	}

	srand((int)time(0));
	Ship Spaceships[10];

	// init random 10 spaceships
	for (int i = 0; i < 10; i++)
	{
		spaceship_name = "NO." + to_string(i + 1) + " CHINA Galacticos";
		capacity = get_random(200, 500);
		hp = get_random(100, 500);
		atk_value = get_random(50, 200);
		dfs_value = get_random(80, 300);
		Spaceships[i] = Ship(spaceship_name, capacity, hp, atk_value, dfs_value);
	}

	// choose 1 from 10 spaceships
	chosen_ship = get_random(1, 10);

	Ship chosen = Spaceships[chosen_ship - 1];
	cout << "The spaceship info:" << endl;
	cout << "Name   "
		 << "Capacity   "
		 << "Health   "
		 << "Attach Value   "
		 << "Defense Value   " << endl;
	chosen.display_info();
	space_journey(chosen, num);

	return 0;
}
