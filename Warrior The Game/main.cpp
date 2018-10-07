#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <windows.h>
#include <fstream>
#include <conio.h>
#include <cstring>
#include "d:\C++\Warrior The Game\Warrior The Game\wtg_classes.h"
#include "d:\C++\Warrior The Game\Warrior The Game\wtg_var.h"
#include "d:\C++\Warrior The Game\Warrior The Game\wtg_functions.h"
#include "d:\C++\Warrior The Game\Warrior The Game\wtg_arena.h"
#include "d:\C++\Warrior The Game\Warrior The Game\wtg_shop.h"
#include "d:\C++\Warrior The Game\Warrior The Game\wtg_myplayer.h"
#include "d:\C++\Warrior The Game\Warrior The Game\wtg_adventure.h"

using namespace std;

void menu();

void enter_p_name()
{
	system("cls");
	printf("Введите ваш ник: ");
	cin>>::p_name;
}

void load_s()
{
	ifstream load;
	load.open ("save.gws");
	if (load) {
		system("cls");
		printf("Загрузка...");
		load>>p_name>>gold>>p_at>>p_hp>>p_ar>>p_lv>>p_xp>>lvl_loc>>tren>>victory>>enemy>>enemy_cof>>loc_score>>all_gold>>bodies>>ydar>>promah>>proid>>win>>lose>>death>>att_id>>arm_id>>item_id>>arena_lock>>info;
		load.close();
		load.open("wtg_config.conf");
		if (load) {
			load>>autosave;
			load.close();
		} else {
			ofstream save;
			save.open("wtg_config.conf");
			save<<false;
			save.close();
		}
		delay(1000);
	} else {
		system("cls");
		printf("Файл сохранения не найден!");
		delay(1000);
		enter_p_name();
	}
}

void save_s(bool echo)
{
	if (echo) {
		system("cls");
		printf("Сохранение...\n");
	}
	ofstream save;
	save.open("save.gws");
	save<<p_name<<endl<<gold<<endl<<p_at<<endl<<p_hp<<endl<<p_ar<<endl<<p_lv<<endl<<p_xp<<endl<<lvl_loc<<endl<<tren<<endl<<victory<<endl<<enemy<<endl<<enemy_cof<<endl<<loc_score<<endl<<all_gold<<endl<<bodies<<endl<<ydar<<endl<<promah<<endl<<proid<<endl<<win<<endl<<lose<<endl<<death<<endl<<att_id<<endl<<arm_id<<endl<<item_id<<endl<<arena_lock<<endl<<info;
	save.close();
	save.open("wtg_config.conf");
	save<<autosave;
	save.close();
	if (echo) {
		delay(1000);
		printf("Успешно сохранено!\n");
		system("pause");
		menu();
	}
}

void game_menu()
{
	pun = 1; kur[0] = '>'; code = 0;
	do {
		system("cls");
		printf("Warrior The Game v 0.5.3 (final version)\n\n%cНовая игра\n%cЗагрузить игру\n\n\nIf you don't see russian text you should open README.txt", kur[0], kur[1]);
		code = select_pun(2);
	} while (code==0);
	if (code==1)
		enter_p_name();
	else
		load_s();
}

void prepare()
{
	lvl[0] = 100;
	for (int i=1; i<50; i++)
		lvl[i] = lvl[ i-1 ]*2;
	tren_pr[0] = 3;
	for (int i=1; i<100; i++)
		tren_pr[i] = tren_pr[i-1]+3;
	armor.set_param(arm_b[arm_id], att_b[arm_id], hp_b[arm_id], shop_item[arm_id]);
	weapon.set_param(arm_b[att_id], att_b[att_id], hp_b[att_id], shop_item[att_id]);
	amulet.set_param(arm_b[item_id], att_b[item_id], hp_b[item_id], shop_item[item_id]);
}

void settings()
{
	pun = 1; kur[0] = '>'; code = 0;
	do {
		system("cls");
		printf("Настройки\n\n%cАвтосохранение\t", kur[0]);
		if (autosave)
			printf("Вкл");
		else
			printf("Выкл");
		printf("\n%cВ меню", kur[1]);
		code = select_pun(2);
	} while (code == 0);
	if (code == 1) {
		if (autosave)
			autosave = false;
		else
			autosave = true;
		settings();
	} else
		menu();
}

void menu()
{
	pun = 1; kur[0] = '>'; code = 0;
	do {
		system("cls");
		cout<<"Игрок: "<<p_name;
		printf(" (%d Lvl)\nДеньги: %d$\nОпыт: %d/%d XP\n\n%cПутешествие\n%cАрена", p_lv, gold, p_xp, lvl[p_lv-1], kur[0], kur[1]);
		if (arena_lock == true)
			printf(" (Доступна с 6 уровня)");
		printf("\n%cМагазин\n%cМой герой\n%cСохранить игру\n%cНастройки", kur[2], kur[3], kur[4], kur[5]);
		code = select_pun(6);
	} while (code==0);
	if (code==1)
		adventure_start();
	else if (code == 2 && arena_lock==false) {
		system("cls");
		initialization();
		arena();
	} else if (code == 3)
		shop();
	else if (code == 4)
		my_player();
	else if (code == 5)
		save_s(true);
	else if (code == 6)
		settings();
	else
		menu();
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	game_menu();
	prepare();
	menu();
	return 0;
}
