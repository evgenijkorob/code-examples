using namespace std;

void set_file_pass(string target, int slot_n);
bool load_game();
void save_game();
bool pause();
bool inventory();

void delay(int ms)
{
	int c = clock() + ms;
	while(clock() < c);
}

void show_slot(int num)
{
	if (num<4) {
		ifstream load;
		set_file_pass("slot", num);
		load.open(file_pass);
		if (load) {
			string text;
			do {
				load>>text;
				if (text == "location=") {
					load>>text;
					cout<<"\nЛокация: "<<text;
				}
				if (text == "day=") {
					int day;
					load>>day;
					printf("\nДень %d, ", day);
				}
				if (text == "time=") {
					int ftime;
					load>>ftime;
					player.get_time(ftime);
				}
			} while (text != "end");
			load.close();
		} else
			printf("\nПусто");
	}
}

int select_pun(int maxi, string target)
{
	if (target == "slot")
		show_slot(pun);
	btn = getch();
	if (target == "yes_pause" && (btn == 112 || btn == 105)) {
		if (btn == 112) {
			kur[pun-1] = ' ';
			for (;;) {
				if (pause())
					break;
			}
			pun = 1; kur[0] = '>';
			return code;
		}
		if (btn == 105) {
			kur[pun-1] = ' ';
			for (;;) {
				if (inventory())
					break;
			}
			pun = 1; kur[0] = '>';
			return 0;
		}
	}
	if (target == "pause" && btn == 112)
		return 1;
	if (target == "inventory" && btn == 105)
		return 1;
	if (btn == 87 || btn == 119 || btn == 72) {
		if (pun==1) {
			kur[0] = ' ';
			pun = maxi;
			kur[maxi-1] = '>';
			return 0;
		} else {
			kur[pun-1] = ' ';
			kur[pun-2] = '>';
			pun--;
			return 0;
		}
	} else if (btn == 83 || btn == 115 || btn == 80) {
		if (pun==maxi) {
			kur[maxi-1] = ' ';
			pun = 1;
			kur[0] = '>';
			return 0;
		} else {
			kur[pun-1] = ' ';
			kur[pun] = '>';
			pun++;
			return 0;
		}
	} else if (btn == 13) {
		kur[pun-1] = ' ';
		return pun;
	} else
		return 0;
}

void set_file_pass(string target, int x)
{
	char file_name [50] = "";
	if (target == "text") {
		for (int i = 0; i<50; i++)
			file_name[i] = curr_stage_pass[i];
	} else if (target == "stage")
		sprintf(file_name, "data\\slot_%d\\stg.dat", player.slot);
	else if (target == "config")
		sprintf(file_name, "data\\config.conf");
	else if (target == "slot")
		sprintf(file_name, "data\\slot_%d\\save.dat", x);
	else if (target == "inventory")
		sprintf(file_name, "data\\slot_%d\\inv.dat", player.slot);
	else if (target == "item")
		sprintf(file_name, "res\\item\\%d.bin", x);
	int a = 0;
	for (;;) {
		if (file_name[a] == '.') {
			if (target == "config")
				a += 5;
			else
				a += 4;
			break;
		} else
			a++;
	}
	for (int i = 0; i<prog_pass_n; i++)
		file_pass[i] = program_pass[i];
	for (int i = 0; i < a; i++)
		file_pass[i+prog_pass_n] = file_name[i];
	for (int i = a+prog_pass_n; i<200; i++)
		file_pass[i] = ' ';
	/*cout<<endl;
	for (int i = 0; i<a+prog_pass_n; i++)
		cout<<file_pass[i];
	system("pause");*/
}

bool show_text()
{
	set_file_pass("text", 0);
	ifstream load;
	load.open(file_pass);
	if (!load)
		return false;
	string text;
	do {
		load>>text;
		if (text == "") {
			load.close();
			return false;
		} else if (text == "endl")
			cout<<endl;
		else if (text != "txtend")
			cout<<text<<" ";
	} while (text != "txtend");

	for (int i = 0; i<5; i++) {
		choises[i] = "";
		for (int a = 0; a<40; a++)
			choises_pass[i] [a] = ' ';
	}
	load>>choise_amt;
	char ch;
	int n = 0;
	for (int i = 0; i<choise_amt; i++) {
		do {
			load>>text;
			if (text != "pass")
				choises[i] += text + " ";
		} while (text != "pass");
		for (;;) {
			if (n>39)
				return false;
			load>>ch;
			if (ch != '%') {
				choises_pass[i] [n] = ch;
				n++;
			} else
				break;
		}
		n = 0;
	}
	load.close();
	return true;
}

bool set_curr_stage_pass(int num, string target)
{
	int a = 0;
	for (;;) {
		if (choises_pass[num] [a] == '.')
			break;
		a++;
	}
	if (target == "set") {
		for (int i = 0; i<50; i++)
			curr_stage_pass[i] = ' ';
		for (int i = 0; i<a+4; i++)
			curr_stage_pass[i] = choises_pass[num] [i];
	} else if (target == "save") {
		set_file_pass("stage", 0);
		ofstream save;
		save.open(file_pass);
		for (int i = 0; i<a+4; i++)
			save<<choises_pass[num] [i];
		save<<'%';
		save.close();
	} else
		return false;
	return true;
}

bool get_curr_stage_pass()
{
	set_file_pass("stage", 0);
	ifstream load;
	load.open(file_pass);
	if (!load)
		return false;
	load>>curr_stage_pass;
	load.close();
	if (curr_stage_pass != NULL) {
		int i = 0;
		for (;;) {
			if (curr_stage_pass[i] == '%')
				break;
			else if (i > 49)
				break;
			else
				i++;
		}
		if (i == 0 || i > 49)
			return false;
		else
			return true;
	} else
		return false;
}

bool set_config(string target)
{
	if (target == "load") {
		ifstream load;
		set_file_pass("config", 0);
		load.open(file_pass);
		if (!load)
			return false;
		string text;
		do {
			load>>text;
			if (text == "autosave=")
				load>>player.autosave;
		} while (text != "end");
		load.close();
		return true;
	} else if (target == "save") {
		ofstream save;
		set_file_pass("config", 0);
		save.open(file_pass);
		save<<"autosave= "<<player.autosave<<endl<<"end";
		save.close();
		return true;
	} else
		return false;
}

bool select_slot(string target)
{
	pun = 1; kur[0] = '>'; code = 0;
	do {
		system("cls");
		if (target == "load")
			printf("Загрузить\n\n");
		else if (target == "save")
			printf("Сохранить\n\n");
		else if (target == "new_game")
			printf("Новая игра\n\n");
		for (int i = 0; i<3; i++)
			printf("%cСлот %d\n", kur[i], i+1);
		printf("%cНазад\n", kur[3]);
		code = select_pun(4, "slot");
		cout<<endl;
	} while (code == 0);
	if (code<4) {
		if (target == "load") {
			if (!load_game()) {
				system("cls");
				printf("Сохранение не найдено!\n");
				system("pause");
				select_slot(target);
			} else
				return true;
		} else if (target == "save") {
			player.slot = code;
			save_game();
			return true;
		} else if (target == "new_game") {
			player.slot = code;
			save_game();
			ofstream save;
			set_file_pass("stage", 0);
			save.open(file_pass);
			save<<"res\\txt\\chapter_1\\st_1.bin%";
			save.close();
			return true;
		}
	} else
		return false;
}

