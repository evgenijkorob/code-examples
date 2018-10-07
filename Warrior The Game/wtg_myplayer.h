using namespace std;

void my_player();

void inform()
{
	system("cls");
	printf("Убито: %d\nСмертей: %d\nНанесено ударов: %d\nПромахи: %d\nЗаработано: %d$\nАрена: %d побед/ %d поражений\n\n", bodies, death, ydar, promah, all_gold, win, lose);
	system("pause");
	my_player();
}

void inv_print(int num)
{
	switch (num) {
case (1):
	cout<<weapon.get_name();
	if (weapon.get_name() != "Пусто")
		printf("\nHP\t+%d\nATT\t+%d\nARM\t+%d", weapon.get_hp(), weapon.get_att(), weapon.get_arm());
	break;
case (2):
	cout<<armor.get_name();
	if (armor.get_name() != "Пусто")
		printf("\nHP\t+%d\nATT\t+%d\nARM\t+%d", armor.get_hp(), armor.get_att(), armor.get_arm());
	break;
case (3):
	cout<<amulet.get_name();
	if (amulet.get_name() != "Пусто")
		printf("\nHP\t+%d\nATT\t+%d\nARM\t+%d", amulet.get_hp(), amulet.get_att(), amulet.get_arm());
	break;
default:
	break;
	}
}

bool inv_sel_pun(int maxi, bool shop, int n)
{
	if (shop) {
		if (pun<6)
			shop_print(pun+n);
	} else
		inv_print(pun);
	btn = getch();
	switch (btn) {
	case (72):
		if (pun==1) {
			kur[0] = ' ';
			pun = maxi;
			kur[maxi-1] = '>';
			return true;
		} else {
			kur[pun-1] = ' ';
			kur[pun-2] = '>';
			pun--;
			return true;
		}
	break;
	case (80):
		if (pun==maxi) {
			kur[maxi-1] = ' ';
			pun = 1;
			kur[0] = '>';
			return true;
		} else {
			kur[pun-1] = ' ';
			kur[pun] = '>';
			pun++;
			return true;
		}
	break;
	case (13):
		if (shop) {
			kur[pun-1] = ' ';
			return false;
		} else {
			if (pun == 4) {
				kur[pun-1] = ' ';
				return false;
			} else
				return true;
		}
	break;
	default:
		return true;
	}
}

void inventory()
{
	pun = 1; kur[0] = '>'; bool b_sel = true;
    do {
		system("cls");
		printf("Снаряжение\n\n%cОружие\n%cБроня\n%cАмулет\n%cНазад\n\n", kur[0], kur[1], kur[2], kur[3]);
		b_sel = inv_sel_pun(4, false, 0);
    } while (b_sel);
    my_player();
}

void my_player()
{
	pun = 1; kur[0] = '>'; code = 0;
	do {
		system("cls");
		printf("Мой герой:\nATT %d HP %d ARM %d\n\n%cСнаряжение\n%cСтатистика\n%cВ меню", p_at, p_hp, p_ar, kur[0], kur[1], kur[2]);
		code = select_pun(3);
	} while (code == 0);
	if (code == 1)
		inventory();
	else if (code == 2)
		inform();
	else
		menu();
}
