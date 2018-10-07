using namespace std;

void shop_print(int num);

void delay (int ms)
{
	int c = clock() + ms;
	while (clock() < c);
}

int random(int n, int m)
{
	srand(time(NULL));
	return rand()%n+m;
}

int attacking(int armor, int attack)
{
	int ar_coef1 = random(50, 1);
	float ar_coef = ar_coef1;
	ar_coef /= 100;
	int ar_damage = armor*ar_coef;
	if (attack-ar_damage<=0)
		return 0;
	else
		return attack-ar_damage;
}

int select_pun(int maxi)
{
	btn = getch();
	switch (btn) {
	case (72): //('w' || 'W' || 72):
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
	break;
	case (80): //('s' || 'S' || 80):
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
	break;
	case (13):
		kur[pun-1] = ' ';
		return pun;
	break;
	default:
		return 0;
	}
}

void new_lvl()
{
	if (p_xp>=lvl[p_lv-1]) {
		printf("Новый уровень! +10$ и +5 ко всем параметрам!\n");
		p_lv++;
		gold += 10;
		p_at += 5;
		p_hp += 5;
		p_ar += 5;
		all_gold+= 10;
		if (p_lv>=6 && arena_lock == true)
			arena_lock = false;
	}
}
