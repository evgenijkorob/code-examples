using namespace std;

int pun, code, choise_amt, prog_pass_n;
char btn, kur[] = "                    ", program_pass [150], file_pass[200], curr_stage_pass[50], choises_pass[5] [40];
string choises[5], glob_it_type;
vector <Firearm*> vecInvFirearm;
vector <BulletBox*> vecInvBulletBox;
vector <Knife*> vecInvKnife;
vector <Medicine*> vecInvMedicine;

Player player;
