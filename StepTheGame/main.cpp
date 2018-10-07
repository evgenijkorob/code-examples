#include <iostream>
#include <ctime>
#include <conio.h>
#include <cstdlib>
#include <cmath>
#include <windows.h>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iterator>
#include "classes.h"
#include "variables.h"
#include "functions.h"

using namespace std;

bool set_program_pass()
{
	ifstream load;
	load.open("prog_pass.txt");
	char symbol;
	if (!load)
		return false;
	int i = 0;
	for (;;) {
		if (i == 150)
			return false;
		load>>symbol;
		if (symbol == '%')
			break;
		else
			program_pass[i] = symbol;
		i++;
	}
	load.close();
	prog_pass_n = i;
	return true;
}

bool load_item_in_inventory(int id)
{
	set_file_pass("item", id);
	ifstream load_item;
	load_item.open(file_pass);
	if (!load_item)
		return false;
	string text, it_nm;
	int wght;
	for (;;) {
		load_item>>text;
		if (text == "item_name=") {
			for (;;) {
				load_item>>text;
				if (text != "next")
					it_nm += text + " ";
				else
					break;
			}
		}
		if (text == "weight=")
			load_item>>wght;
		if (text == "item_type=") {
			load_item>>glob_it_type;
			break;
		}
	}
	int x;
	if (glob_it_type == "pistol" || glob_it_type == "machine_gun") {
		vecInvFirearm.push_back(new Firearm(it_nm, wght, glob_it_type, id));
		do {
			load_item>>text;
			load_item>>x;
			if (text == "power=")
				vecInvFirearm[vecInvFirearm.size()-1]->power = x;
			if (text == "distance=")
				vecInvFirearm[vecInvFirearm.size()-1]->distance = x;
			if (text == "speed=")
				vecInvFirearm[vecInvFirearm.size()-1]->speed = x;
			if (glob_it_type == "machine_gun" && text == "speed2=")
				vecInvFirearm[vecInvFirearm.size()-1]->speed2 = x;
			if (text == "reload=")
				vecInvFirearm[vecInvFirearm.size()-1]->reload = x;
			if (text == "max_bull=")
				vecInvFirearm[vecInvFirearm.size()-1]->max_bull = x;
			if (text == "bull_id=")
				vecInvFirearm[vecInvFirearm.size()-1]->bull_id = x;
		} while (text != "end");
	}
	if (glob_it_type == "bullets") {
		vecInvBulletBox.push_back(new BulletBox(it_nm, wght, glob_it_type, id));
		do {
			load_item>>text;
			load_item>>x;
			if (text == "per_box=")
				vecInvBulletBox[vecInvBulletBox.size()-1]->per_box = x;
		} while (text != "end");
	}
	if (glob_it_type == "knife") {
		vecInvKnife.push_back(new Knife(it_nm, wght, glob_it_type, id));
		do {
			load_item>>text;
			load_item>>x;
			if (text == "power=")
				vecInvKnife[vecInvKnife.size()-1]->power = x;
			if (text == "distance=")
				vecInvKnife[vecInvKnife.size()-1]->distance = x;
			if (text == "speed=")
				vecInvKnife[vecInvKnife.size()-1]->speed = x;
		} while (text != "end");
	}
	if (glob_it_type == "medicine") {
		vecInvMedicine.push_back(new Medicine(it_nm, wght, glob_it_type, id));
		do {
			load_item>>text;
			load_item>>x;
			if (text == "power=")
				vecInvMedicine[vecInvMedicine.size()-1]->power = x;
			if (text == "speed=")
				vecInvMedicine[vecInvMedicine.size()-1]->speed = x;
		} while (text != "end");
	}
	return true;
}

bool load_game()
{
	system("cls");
	printf("Загрузка...\n");
	ifstream load;
	set_file_pass("slot", code);
	load.open(file_pass);
	if (!load)
		return false;
	string text;
	do {
		load>>text;
		if (text == "location=")
			load>>player.location;
		if (text == "day=")
			load>>player.day;
		if (text == "time=")
			load>>player.time;
		if (text == "slot=")
			load>>player.slot;
		if (text == "health=")
			load>>player.health;
	} while (text != "end");
	load.close();
	set_file_pass("inventory", 0);
	load.open(file_pass);
	if (!load)
		return false;
	int x;
	do {
		load>>text;
		if (text == "space=")
			load>>player.space;
		if (text == "max_space=")
			load>>player.max_space;
		if (text == "item_id:") {
			int item_id;
			for (;;) {
				load>>item_id;
				if (item_id == 0)
					break;
				if (!load_item_in_inventory(item_id))
					return false;
				if (glob_it_type == "pistol" || glob_it_type == "machine_gun") {
					load>>x;
					vecInvFirearm[vecInvFirearm.size()-1]->bullets = x;
				}
				if (glob_it_type == "bullets") {
					load>>x;
					vecInvBulletBox[vecInvBulletBox.size()-1]->average = x;
				}
			}
		}
	} while (text != "end");
	load.close();
	system("pause");
	return true;
}

void save_game()
{
	set_file_pass("slot", player.slot);
	ofstream save;
	save.open(file_pass);
	save<<"location= "<<player.location<<endl
	<<"day= "<<player.day<<endl
	<<"time= "<<player.time<<endl
	<<"slot= "<<player.slot<<endl
	<<"health= "<<player.health<<endl
	<<"end";
	save.close();
	set_file_pass("inventory", 0);
	save.open(file_pass);
	save<<"space= "<<player.space<<endl
	<<"max_space= "<<player.max_space<<endl
	<<"item_id:"<<endl;
	for (unsigned int i = 0; i<vecInvFirearm.size(); i++)
		save<<vecInvFirearm[i]->id<<" "<<vecInvFirearm[i]->bullets<<endl;
	for (unsigned int i = 0; i<vecInvBulletBox.size(); i++)
		save<<vecInvBulletBox[i]->id<<" "<<vecInvBulletBox[i]->average<<endl;
	for (unsigned int i = 0; i<vecInvKnife.size(); i++)
		save<<vecInvKnife[vecInvKnife.size()-1]->id<<endl;
	for (unsigned int i = 0; i<vecInvMedicine.size(); i++)
		save<<vecInvMedicine[vecInvMedicine.size()-1]->id<<endl;
	save<<0<<endl<<"end";
	save.close();
}

bool start_menu()
{
	pun = 1; kur[0] = '>'; code = 0;
	do {
		system("cls");
		printf("%cНовая игра\n%cЗагрузить игру\n%cВыйти\n\n\n\nVersion 0.2.1.2408\n© Korobeinikov Evgenii", kur[0], kur[1], kur[2]);
		code = select_pun(3, "");
	} while (code == 0);
	if (code == 1) {
		if (!select_slot("new_game"))
			start_menu();
		return true;
	} else if (code == 2) {
		if (!select_slot("load"))
			start_menu();
		return true;
	} else
		return false;
}

bool pause()
{
	pun = 1; kur[0] = '>'; int acode;
	do {
		system("cls");
		printf("Пауза\n\n%cПродолжить\n%cНастройки\n%cЗагрузить\n%cСохранить\n%cВыход", kur[0], kur[1], kur[2], kur[3], kur[4]);
		acode = select_pun(5, "pause");
	} while (acode == 0);
	kur[pun-1] = ' ';
	if (acode == 1) {
		code = 0;
		return true;
	} else if (acode == 5) {
		code = -1;
		return true;
	} else
		return false;
}

bool take_firearm(unsigned int num)
{
	pun = 1; kur[0] = '>'; unsigned int acode;
	do {
		system("cls");
		cout<<"В руках "<<vecInvFirearm[num]->item_name;
		printf("\n\n%cВыстрелить\n%cПерезарядить\n%cНазад\n", kur[0], kur[1], kur[2]);
		acode = select_pun(3, "yes_pause");
	} while (acode == 0);
	if (acode == 1) {
		if (!vecInvFirearm[num]->shooting()) {
			printf("\nМагазин пуст");
			delay(600);
		}
		return false;
	} else if (acode == 2) {
		if (vecInvBulletBox.empty())
			return false;
		for (int i = vecInvBulletBox.size()-1; i>=0; i--) {
			if (vecInvFirearm[num]->bull_id == vecInvBulletBox[i]->id) {
				vecInvBulletBox[i]->average = vecInvFirearm[num]->reloading(vecInvBulletBox[i]->average);
				if (vecInvBulletBox[i]->average == 0)
					vecInvBulletBox.erase(vecInvBulletBox.begin()+i);
				return false;
			}
		}
		return false;
	} else
		return true;
}

bool inventory()
{
	pun = 1; kur[0] = '>'; unsigned int acode;
	int avr_items = vecInvFirearm.size() + vecInvBulletBox.size() + vecInvKnife.size() + vecInvMedicine.size();
	do {
		system("cls");
		printf("Состояние: ");
		player.show_health();
		printf("\nВремя ");
		player.show_time();
		printf("\nВ руках ничего\nИнвентарь (%d/%d)\n\n", player.space, player.max_space);
		unsigned int it = vecInvFirearm.size();
		for (unsigned int i = 0; i<it; i++)
			cout<<kur[i]<<vecInvFirearm[i]->item_name<<"("<<vecInvFirearm[i]->bullets<<")\n";
		for (unsigned int i = 0; i<vecInvBulletBox.size(); i++)
			cout<<kur[i+it]<<vecInvBulletBox[i]->item_name<<"("<<vecInvBulletBox[i]->average<<" шт.)\n";
		it += vecInvBulletBox.size();
		for (unsigned int i = 0; i<vecInvKnife.size(); i++)
			cout<<kur[i+it]<<vecInvKnife[i]->item_name<<endl;
		it += vecInvKnife.size();
		for (unsigned int i = 0; i<vecInvMedicine.size(); i++)
			cout<<kur[i+it]<<vecInvMedicine[i]->item_name<<endl;
		it += vecInvMedicine.size();
		printf("%cНазад", kur[avr_items]);
		acode = select_pun(avr_items+1, "");
	} while (acode == 0);
	kur[pun-1] = ' ';
	if (acode == avr_items+1)
		return true;
	else if (acode<=vecInvFirearm.size()) {
		while (!take_firearm(acode-1));
		return false;
	} else
		return false;
}

bool game_window()
{
	pun = 1; kur[0] = '>'; code = 0;
	do {
		system("cls");
		if (!show_text()) {
			printf("show text error\nОшибка! Запрашиваемый ресурс игры поврежден или удалён.\n");
			system("pause");
			return false;
		}
        for (int i = 0; i<choise_amt; i++)
			cout<<endl<<kur[i]<<choises[i];
        code = select_pun(choise_amt, "yes_pause");
	} while (code == 0);
	if (code == -1)
		return false;
	set_curr_stage_pass(code-1, "set");
	if (player.autosave) {
		set_curr_stage_pass(code-1, "save");
		save_game();
	}
	game_window();
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	if (!set_program_pass()) {
		printf("Ошибка чтения пути программы!\n");
		system("pause");
		return 0;
	}
    if (!start_menu())
		return 0;
	if (!set_config("load")) {
		system("cls");
		printf("Ошибка! Файл конфигурации поврежден или удален.\n");
		system("pause");
		set_config("save");
	}
	if (!get_curr_stage_pass()) {
		system("cls");
		printf("curr_stage_pass error\nОшибка! Запрашиваемый ресурс игры поврежден или удалён.\n");
		system("pause");
		return 0;
	}
	if (!game_window())
		return 0;
    return 0;
}

