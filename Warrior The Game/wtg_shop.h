using namespace std;

void shop();
bool inv_sel_pun(int maxi, bool shop, int n);

void shop_print(int num)
{
	itm_id = num;
	int arm, hp, att;
	if (itm_id<=5) {
		arm = armor.get_arm();
		att = armor.get_att();
		hp = armor.get_hp();
	} else if (itm_id>5 && itm_id<=10) {
		arm = weapon.get_arm();
		att = weapon.get_att();
		hp = weapon.get_hp();
	} else if (itm_id>10) {
		arm = amulet.get_arm();
		att = amulet.get_att();
		hp = amulet.get_hp();
	}
	printf("Цена \t%d$\nHP\t+%d(%d)\nATT\t+%d(%d)\nARM\t+%d(%d)", price[num], hp_b[num], hp_b[num] - hp, att_b[num], att_b[num] - att, arm_b[num], arm_b[num] - arm);
	price_itm = price[num];
}

void buy()
{
	if (itm_id<=5) {
		p_ar += arm_b[itm_id] - arm_b[arm_id];
		p_at += att_b[itm_id] - att_b[arm_id];
		p_hp += hp_b[itm_id] - hp_b[arm_id];
		armor.set_param(arm_b[itm_id], att_b[itm_id], hp_b[itm_id], shop_item[itm_id]);
		gold -= price[itm_id];
		arm_id = itm_id;
	} else if (itm_id>5 && itm_id<=10) {
		p_ar += arm_b[itm_id] - arm_b[att_id];
		p_at += att_b[itm_id] - att_b[att_id];
		p_hp += hp_b[itm_id] - hp_b[att_id];
		weapon.set_param(arm_b[itm_id], att_b[itm_id], hp_b[itm_id], shop_item[itm_id]);
		gold -= price[itm_id];
		att_id = itm_id;
	} else if (itm_id>10) {
		p_ar += arm_b[itm_id] - arm_b[item_id];
		p_at += att_b[itm_id] - att_b[item_id];
		p_hp += hp_b[itm_id] - hp_b[item_id];
		amulet.set_param(arm_b[itm_id], att_b[itm_id], hp_b[itm_id], shop_item[itm_id]);
		gold -= price[itm_id];
		item_id = itm_id;
	}
}

void buy_item(int a, string itm)
{
	pun = 1; kur[0] = '>'; bool dont_buy = true;
	do {
		system("cls");
		cout<<"Купить "<<itm;
		printf("\nДеньги: %d$\n\n", gold);
		int kr = 0;
		for (int i = 1+a; i<6+a; i++) {
			cout<<kur[kr]<<shop_item[i]<<endl;
			kr++;
		}
		printf("%cНазад\n\n", kur[5]);
		dont_buy = inv_sel_pun(6, true, a);
	} while (dont_buy);
	if (pun<6) {
		if (att_id == itm_id || arm_id == itm_id || item_id == itm_id) {
			system("cls");
			printf("У вас уже есть эта вещь!");
			btn = getch();
			buy_item(a, itm);
		} else {
			if (price_itm<=gold) {
				pun = 1; kur[0] = '>'; code = 0;
				do {
					system("cls");
					printf("Купить?\n%cНет\n%cДа", kur[0], kur[1]);
					code = select_pun(2);
				} while (code == 0);
				if (code == 2) {
					buy();
					shop();
				} else
					buy_item(a, itm);
			} else {
				system("cls");
				printf("Вам не хватает %d$", price_itm - gold);
				btn = getch();
				buy_item(a, itm);
			}
		}
	} else
		shop();
}

void shop()
{
	pun = 1; kur[0] = '>'; code = 0;
	do {
		system("cls");
		printf("Магазин\nДеньги: %d$\n\n%cБроня\n%cОружие\n%cАмулеты\n\n%cВ меню", gold, kur[0], kur[1], kur[2], kur[3]);
		code = select_pun(4);
	} while (code == 0);
	if (code == 1)
		buy_item(0, "броню");
	else if (code == 2)
		buy_item(5, "оружие");
	else if (code == 3)
		buy_item(10, "амулет");
	else
		menu();
}
