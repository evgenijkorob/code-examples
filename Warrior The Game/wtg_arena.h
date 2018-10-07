using namespace std;

void arena();
void arena_info(bool ap_inf, int plr, bool ap_stake);
void menu();
void save_s(bool echo);

void rakirovka(int a, int b)
{
	int h = pl_scores[a];
	pl_scores[a] = pl_scores[b];
	pl_scores[b] = h;
	h = apl_kill[a];
	apl_kill[a] = apl_kill[b];
	apl_kill[b] = h;
	h = pl_plc_table[a];
	pl_plc_table[a] = pl_plc_table[b];
	pl_plc_table[b] = h;
	string nm = apl_name[a];
	apl_name[a] = apl_name[b];
	apl_name[b] = nm;
}

void do_table()
{
	for (int i = 0; i<5; i++)
		if (apl_hp[i]>0)
			pl_table[0] = i;
	for (int i = 0; i<5; i++)
		switch (pl_table[i]) {
		case (0):
			pl_plc_table[0] = i;
			break;
		case (1):
			pl_plc_table[1] = i;
			break;
		case (2):
			pl_plc_table[2] = i;
			break;
		case (3):
			pl_plc_table[3] = i;
			break;
		case (4):
			pl_plc_table[4] = i;
			break;
		}
}

void analize()
{
	for (int i = 4; i >= 1; i--)
		for (int k = 1; k < i; k++) { //int k = 0
			if (pl_scores[k]<pl_scores[k+1])
				rakirovka(k, k+1);
			else if (pl_scores[k]==pl_scores[k+1]) {
				if (apl_kill[k]<apl_kill[k+1])
					rakirovka(k, k+1);
				else if (apl_kill[k]==apl_kill[k+1]) {
					if (pl_plc_table[k]>pl_plc_table[k+1])
						rakirovka(k, k+1);
				}
			}
		}
}

void arena_p_attack(int fpl_n)
{
	if (apl_hp[fpl_n]>0) {
		if (apl_hp[aen_n[fpl_n]]>0) {
			if (fpl_n == 0) {
				printf("\nВы: %d HP     (Нажмите кнопку, чтобы атаковать)", apl_hp[0]);
				btn = getch();
				system("cls");
			}
			if (random(2, 0) == 1) {
				int damage = attacking(apl_ar[aen_n[fpl_n]], apl_at[fpl_n]);
				cout<<apl_name[fpl_n]<<" нанёс "<<apl_name[aen_n[fpl_n]];
				if (fpl_n == 0) {
					printf("(%d HP)", apl_hp[aen_n[fpl_n]]);
					ydar++;
				}
				printf(" %d урона\n", damage);
				if (apl_hp[aen_n[fpl_n]] - damage>=0) {
					pl_scores[fpl_n] += damage;
					a_rew_xp += damage/3;
				} else {
					pl_scores[fpl_n] += apl_hp[aen_n[fpl_n]];
					a_rew_xp += apl_hp[aen_n[fpl_n]]/3;
				}
				apl_hp[aen_n[fpl_n]] -= damage;
				if (apl_hp[aen_n[fpl_n]]<=0) {
					delay(300);
					cout<<apl_name[aen_n[fpl_n]]<<" погиб\n";
					apl_kill[fpl_n]++;
					arena_all_pl--;
					pl_table[arena_all_pl] = aen_n[fpl_n];
					if (aen_n[fpl_n] == 0)
						death++;
					else if (fpl_n == 0) {
						bodies++;
						a_rew_xp += (apl_ar[aen_n[0]]+apl_at[aen_n[0]]+apl_hp[aen_n[0]])/5;
					}
				}
				delay(1000);
			} else {
				cout<<apl_name[fpl_n]<<" не попал в "<<apl_name[aen_n[fpl_n]];
				if (fpl_n == 0) {
					printf("(%d HP)\n", apl_hp[aen_n[fpl_n]]);
					promah++;
				}
				else
					cout<<endl;
				delay(1000);
			}
		} else if (arena_all_pl>1) {
			int killed = aen_n[fpl_n];
			do {
				aen_n[fpl_n] = random(5, 0);
			} while (aen_n[fpl_n] == fpl_n || aen_n[fpl_n] == killed || apl_hp[aen_n[fpl_n]]<=0);
			arena_p_attack(fpl_n);
		}
	}
}

void ap_info(int num1, bool compare, int num2)
{
	pun = 1; kur[0] = '>'; code = 0;
	do {
		system("cls");
		cout<<"Игрок: "<<apl_name[num1];
		if (compare==true)
			cout<<" и "<<apl_name[num2];
		printf("\nЗдоровье: %d", apl_hp[num1]);
		if (compare==true)
			printf(" / %d", apl_hp[num2]);
		printf("\nАтака: %d", apl_at[num1]);
		if (compare==true)
			printf(" / %d", apl_at[num2]);
		printf("\nБроня: %d", apl_ar[num1]);
		if (compare==true)
			printf(" / %d", apl_ar[num2]);
		printf("\n\n%c", kur[0]);
		if (compare==true) {
			printf("Назад");
			code = select_pun(1);
		} else {
			printf("Сравнить с...\n%cНазад", kur[1]);
			code = select_pun(2);
		}
	} while (code==0);
	if (code==1)
		arena_info(true, num1, false);
	else
		arena_info(false, 6, false);
}

void stake(int plr_st)
{
	system("cls");
	printf("Ваша ставка: ");
	cin>>a_stake;
	if (a_stake>gold) {
		printf("\nУ вас не хватает средств!");
		delay(1000);
		stake(plr_st);
	} else if (a_stake <= 0) {
		printf("\nНе пытайтесь нас надуть!");
		delay(1000);
		stake(plr_st);
	} else {
		pun = 1; kur[0] = '>'; code = 0;
		do {
			system("cls");
			cout<<"Вы уверены, что "<<apl_name[plr_st];
			printf(" победит?\n\n%cНет\n%cДа", kur[0], kur[1]);
			code = select_pun(2);
		} while (code == 0);
		if (code == 2) {
			apl_st = apl_name[plr_st];
			a_stake_b = true;
			gold -= a_stake;
			printf("\n\nСтавка принята!");
			delay(1000);
			arena();
		} else
			arena_info(false, 6, true);
	}
}

void arena_info(bool ap_inf, int plr, bool ap_stake)
{
	pun = 1; kur[0] = '>'; code = 0;
	do {
		system("cls");
		if (ap_inf == true)
			printf("Выбрать игрока\n\n");
		else if (ap_stake == true)
			printf("Поставить на\n\n");
		else
			printf("Информация об игроке\n\n");
		cout<<kur[0]<<apl_name[0]<<endl<<kur[1]<<apl_name[1]<<endl<<kur[2]<<apl_name[2]<<endl<<kur[3]<<apl_name[3]<<endl<<kur[4]<<apl_name[4]<<"\n\n"<<kur[5]<<"Назад";
		code = select_pun(6);
	} while (code == 0);
	if (ap_inf == true && code<6) {
		if (plr == code-1)
			arena_info(true, plr, false);
		else
			ap_info(plr, true, code-1);
	} else if (ap_inf == false && ap_stake == false && code<6)
		ap_info(code-1, false, 6);
	else if (ap_inf == false && ap_stake == true && code<6)
		stake(code-1);
	else
		arena();
}

void arena_start()
{
	system("cls");
	for (int i = 3; i>-1; i--) {
		printf("Бой начнётся через %d", i);
		delay(1000);
		system("cls");
	}
	do {
		for (int i = 0; i<5; i++)
			arena_p_attack(i);
	} while (arena_all_pl>1);
	printf("\n\nБой окончен!\n");
	int winner = 0;
	for (int i = 0; i<5; i++) {
		if (apl_hp[i]>0)
			winner = i;
	}
	rakirovka(0, winner);
	system("pause");
	do_table();
	analize();
	system("cls");
	printf("Место\tИмя\tУбийства\tОчки\n");
	for (int i = 0; i<5; i++) {
		printf("%d-е\t", i+1);
		cout<<apl_name[i];
		printf("\t%d\t\t%d\n", apl_kill[i], pl_scores[i]);
	}
	if (apl_name[0] == p_name) {
		int gld = p_lv*4;
		printf("\nПоздравляю, вы победили! Вы заработали %d$\n", gld);
		gold += gld;
		all_gold += gld;
		win++;
	} else {
		printf("\nУвы. Вы проиграли.\n");
		lose++;
	}
	printf("Заработано %d XP\n", a_rew_xp);
	p_xp += a_rew_xp;
	new_lvl();
	if (a_stake_b) {
		if (apl_st == apl_name[0]) {
			printf("\nИгрок, на которого вы поставили, победил!\nВаш выйгрыш %d$\n\n", a_stake*2);
			gold += a_stake*2;
			all_gold += a_stake*2;
		} else
			printf("\nИгрок, на которого вы поставили, проиграл.\n\n");
	}
	if (autosave)
		save_s(false);
	system("pause");
	menu();
}

void arena()
{
	pun = 1; kur[0] = '>'; code = 0;
	do {
		system("cls");
		printf("Добро пожаловать на арену!\n\n%cИнфо игроков\n%cСделать ставку\n%cК битве\n%cВ меню", kur[0], kur[1], kur[2], kur[3]);
		code = select_pun(4);
	} while (code == 0);
	if (code == 1)
		arena_info(false, 6, false);
	else if (code == 2 && a_stake_b == false) {
		a_stake = 0;
		arena_info(false, 6, true);
	} else if (code == 2 && a_stake_b == true) {
		printf("\n\nВы уже сделали ставку!");
		delay(1000);
		arena();
	} else if (code == 3)
		arena_start();
	else
		menu();
}

void initialization()
{
	printf("Загрузка     0%%");
	delay(400);
	a_rew_xp = 0;
	arena_all_pl = 5;
	a_stake_b = false;
	apl_st = "";
	apl_at[0] = p_at;
	apl_ar[0] = p_ar;
	apl_hp[0] = p_hp;
	system("cls");
	printf("Загрузка     10%%");
	for (int i = 1; i<5; i++) {
		apl_at[i] = apl_at[0]+random(31, -15);
		delay(250);
		apl_ar[i] = apl_ar[0]+random(31, -15);
		delay(250);
		apl_hp[i] = apl_hp[0]+random(31, -15);
		delay(250);
	}
	system("cls");
	printf("Загрузка     35%%");
	for (int i = 0; i<5; i++)
		do {
			aen_n[i] = random(5, 0);
			delay(250);
		} while (aen_n[i]==i);
	system("cls");
	printf("Загрузка     40%%");
	for (int i = 0; i<5; i++) {
		apl_kill[i] = 0;
		pl_scores[i] = 0;
	}
	apl_name[0] = p_name;
	for (int i = 1; i<5; i++) {
		apl_name[i] = pl_names[random(41, 0)];
		for (int k = 1; k<i; k++)
			if (apl_name[i]==apl_name[k])
				do {
					delay(100);
					apl_name[i] = pl_names[random(41, 0)];
				} while (apl_name[i]==apl_name[k]);

	}
	system("cls");
	printf("Загрузка     100%%");
	delay(400);
}
