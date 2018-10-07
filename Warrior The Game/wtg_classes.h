using namespace std;

class Players_item
{
private:
	int arm, att, hp;
	string name;
public:
	void set_param(int armb, int attb, int hpb, string nm)
	{
		arm = armb;
		att = attb;
		hp = hpb;
		name = nm;
	}
	int get_arm()
	{
		return arm;
	}
	int get_att()
	{
		return att;
	}
	int get_hp()
	{
		return hp;
	}
	string get_name()
	{
		return name;
	}
};

class Creature
{
private:
	int arm, att;
	string name;
public:
	int hp;
	void set_param(int aarm, int aatt, int ahp, string nm)
	{
		arm = aarm;
		att = aatt;
		hp = ahp;
		name = nm;
	}
	int get_att()
	{
		return att;
	}
	int get_arm()
	{
		return arm;
	}
	string get_name()
	{
		return name;
	}
};
