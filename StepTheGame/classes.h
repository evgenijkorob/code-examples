using namespace std;

void delay2(int ms)
{
	int c = clock() + ms;
	while(clock() < c);
}

class Player
{
public:
	bool autosave;
	int slot, day, time, health, space, max_space;
	string location;
	char ch_time[5];

	Player()
	{
		day = 1;
		location = "Больница";
		time = 817;
		health = 100;
		space = 0;
		max_space = 0;
		autosave = false;
	}

	void show_health()
	{
		if (health>90)
			printf("здоров");
		else if (health>59)
			printf("ранен");
		else if (health>39)
			printf("плохое");
		else if (health>19)
			printf("очень плохое");
		else if (health>1)
			printf("критическое");
	}

	void get_time(int atime)
	{
		int hours = atime/60;
		int minutes = atime - hours*60;
		char hour[2] = "", minute[2] = "";
		if (hours>10)
			sprintf(hour, "%d", hours);
		else
			sprintf(hour, "0%d", hours);
		if (minutes>10)
			sprintf(minute, "%d", minutes);
		else
			sprintf(minute, "0%d", minutes);
		for (int i = 0; i<2; i++)
			ch_time[i] = hour[i];
		ch_time[2] = ':';
		for (int i = 0; i<2; i++)
			ch_time[i+3] = minute[i];
		for (int i = 0; i<5; i++)
			cout<<ch_time[i];
	}

	void show_time()
	{
		get_time(time);
	}
};

class Item
{
public:
	int weight, id;
	string item_name, item_type;

	Item (string it_nm, int wght, string it_tp, int itm_id)
	{
		item_name = it_nm;
		weight = wght;
		item_type = it_tp;
		id = itm_id;
	}
};

class Firearm : public Item
{
public:
	int power, distance, speed, speed2, reload, bullets, max_bull, bull_id;
	bool single_shooting;

	Firearm (string name, int weght, string type, int it_id) : Item (name, weght, type, it_id)
	{}

	bool shooting()
	{
		if (bullets-1>=0) {
			printf("\n*Выстрел*\a");
			bullets--;
			if (item_type == "machine_gun" && !single_shooting)
				delay2(speed2);
			else
				delay2(speed);
			cout<<endl;
			return true;
		} else
			return false;
	}

	int reloading(int box)
	{
		int need = max_bull-bullets;
		if (box-need>0) {
			box -= need;
			bullets = max_bull;
			printf("\nПерезарядка...");
			delay2(reload);
		} else if (box-need<=0) {
			bullets += box;
			box = 0;
			printf("\nПерезарядка...");
			delay2(reload);
		}
		return box;
	}
};

class BulletBox : public Item
{
public:
	int per_box, average;

	BulletBox (string name, int weght, string type, int it_id) : Item (name, weght, type, it_id)
	{}
};

class Knife : public Item
{
public:
	int power, distance, speed;

	Knife (string name, int weght, string type, int it_id) : Item (name, weght, type, it_id)
	{}
};

class Medicine : public Item
{
public:
	int power, speed;

	Medicine (string name, int weght, string type, int it_id) : Item (name, weght, type, it_id)
	{}
};

