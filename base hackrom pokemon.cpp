#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <fstream>
#include <cmath>
#include <conio.h>
using namespace std;

class player
{
private:
	string nome;
	string classe;
	int danno;
	int speed;
	int vita;
	int crit;
	int vita_max;
	int posx;
	int posy;
	vector<string>sprite;
	vector<string>sprite_attk;

public:
	bool vivo() {
		bool vivi;
		vivi = vita > 0;
		return vivi;

	}
	void setName()
	{
		cout << "come ti chiami?" << endl;
		getline(cin, nome);
	}

	void choose_classe()
	{
		cout << "\033[2J\033[1;1H";
		this_thread::sleep_for(chrono::milliseconds(300));
		cout << "ciao " << nome << endl;
		this_thread::sleep_for(chrono::milliseconds(1000));
		char scelta = 0;
		while (!(scelta == '1' || scelta == '2' || scelta == '3')) {
			cout << "scegli una classe" << endl;
			cout << "1)tank 150 hp,30 speed,40 danno,25% crit" << endl;
			cout << "2)blade master 75 hp,70 speed,30 danno,40% crit" << endl;
			cout << "3)assassino 100 hp,90 speed,20 danno,50% crit" << endl;
			scelta = _getch();
			switch (scelta) {
			case '1':
				classe = "tank";
				vita = 150;
				danno = 40;
				speed = 30;
				crit = 25;
				vita_max = vita;
				break;
			case '2':
				classe = "blade master";
				vita = 75;
				danno = 30;
				speed = 70;
				crit = 40;
				vita_max = vita;
				break;
			case '3':
				classe = "assassino";
				vita = 100;
				danno = 20;
				speed = 90;
				crit = 50;
				vita_max = vita;
				break;
			default:

				cout << "scegli 1,2 o 3" << endl;

			}
		}
	}

	void cura(int danno_nemico)
	{
		vita += 2 * danno_nemico;
		if (vita > vita_max)
		{
			vita = vita_max;
		}
		cout << "hai " << vita << " hp" << endl;
	}

	void attacchi(int& mob_vita) {
		cout << "lo colpisci" << endl;


		bool crittato = rand() % 100 < crit;
		if (crittato)
		{
			cout << "colpo critico" << endl;
			mob_vita -= danno * 2;
		}
		else
			mob_vita -= danno;
		if (mob_vita < 0)
			mob_vita = 0;

	}
	void turno(int& mob_vita, int danno_nemico)
	{
		cout << vita<<" hp"<<endl;
		cout << "e il tuo turno cosa fai?" << endl << "1) attacchi" << endl << "2)ti curi" << endl;
		char scelta = _getch();
		while (scelta != '1' && scelta != '2')
		{
			cout << "inserire valore valido" << endl;
			cin >> scelta;
		}
		if (scelta == '1')
			attacchi(mob_vita);
		else
			cura(danno_nemico);

	}
	void pos_play1(int mappaymax, int mappaxmax)
	{
		posx = rand() % mappaxmax;
		posy = rand() % mappaymax;
	}
	string getclasse() { return classe; }
	string getname() { return nome; }
	int& getposx() { return posx; }
	int& getposy() { return posy; }
	int& getvita() { return vita; }
	int getspeed() { return speed; }
};
class nemico
{
private:
	string classen;
	int dannon;
	int speedn;
	int vitan;
	int critn;
	int posxn;
	int posyn;
	vector<string>sprite;
	vector<string>sprite_attk;
	vector<string>sprite_kill;
public:
	void attacca(int& play_vita) {
		cout << "ti colpisce" << endl;
		bool crittato = rand() % 100 < critn;
		if (crittato)
		{
			cout << "colpo critico" << endl;
			play_vita -= dannon * 2;
		}
		else
			play_vita -= dannon;
		if (play_vita < 0)
			play_vita = 0;
	}
	nemico(string c, int v, int d, int s, int cr, vector<string>sprit, vector<string>sprit_attk, vector<string>sprit_kill)
	{
		classen = c;
		vitan = v;
		dannon = d;
		speedn = s;
		critn = cr;
		sprite = sprit;
		sprite_attk = sprit_attk;
		sprite_kill = sprit_kill;

	}
	void disegna_fermo()
	{
		for (string linea : sprite)
		{
			cout << "\t\t\t\t\t\t\t\t\t\t" << linea << endl;
		}
	}
	void disegna_attacco()
	{

		for (string linea : sprite_attk)
		{
			cout << "\t\t\t\t\t\t\t\t\t\t" << linea << endl;
		}

	}
	void disegna_morto()
	{
		{
			for (string linea : sprite_kill)
			{
				cout << "\t\t\t\t\t\t\t\t\t\t" << linea << endl;
			}
		}
	}
	void pos_nemico1(int mappaymax, int mappaxmax)
	{
		posxn = rand() % mappaxmax;
		posyn = rand() % mappaymax;
	}
	string getclasse() { return  classen; }
	int getdanno() { return dannon; }
	int& getvita() { return vitan; }
	int getspeed() { return speedn; }
	int& getposnx() { return posxn; }
	int& getposny() { return posyn; }
};
class orco : public nemico
{
public:
	orco() : nemico
	(
		"orco",
		120,
		30,
		25,
		15,
		{
			R"(              __ _____ __    )",
			R"(           __ \_| \ / |_/    )",
			R"(           | |__| ___ |___   )",
			R"(           | |.  \___// . \  )",
			R"(           |_|__/  ___\___/  )",
			R"(          /   \|. | -   - |  )",
			R"(          \___/|. |  {*}  |  )",
			R"(           | |  \ \  [|]  /  )",
			R"(          / # \ |[=\_____/   )",
			R"(         |  #  | /| /\ |\   )",
			R"(         |  #  |(  |  |  )   )",
			R"(          \___/ |  |  | _|   )",
			R"(               [___|  |___]   )"
		},
		{
			R"(          _   __ _____ __    )",
			R"(       /   \  \_| \ / |_/    )",
			R"(       \  | \___| ___ |___   )",
			R"(        \_  / .  \___// . \  )",
			R"(          \_\___/ .___\___/  )",
			R"(         /   \ |. | -   - |  )",
			R"(         \___/ |. |  {*}  |  )",
			R"(            \ \ \ \  [|]  /  )",
			R"(             \ \|[=\_____/   )",
			R"(              \/ /| /\ |\   )",
			R"(                (  |  |  )   )",
			R"(                |  |  | _|   )",
			R"(               [___|  |___]   )"
		},
		{
			R"(              __ _____ __        )",
			R"(              \_| X X |_/        )",
			R"(      ___    ___| ___ |___       )",
			R"(      | |  // .  \___// . \      )",
			R"(      | |  |\___/ . . \___/\     )",
			R"(      |_| /  | |. . . .||  |     )",
			R"(     /   \___/ |. . . .||  |     )",
			R"(     \___/      \ . . //  /      )",
			R"(      | |       |[=X=]/__/__     )",
			R"(     / # \    ___/| | -   - |    )",
			R"(    |  #  |  (   ___|  {*}  |__  )",
			R"(    |  #  |  |  |   \  [|]  /  | )",
			R"(     \___/  [___|    \_____/ |_| )"
		}
	)
	{
	}
};
class mago_nero : public nemico
{
public:
	mago_nero() : nemico
	(
		"Mago nero",
		80,
		35,
		35,
		20,
		{
			R"(                 /\              )",
			R"(                /  \             )",
			R"(              _/____\_           )",
			R"(               |\  /|            )",
			R"(      |     ____\--/____         )",
			R"(      |    /    \\//    \        )",
			R"(     _|___/      \/     |        )",
			R"(     \_\    /|   ||     |        )",
			R"(        \__/ |   ||   | |        )",
			R"(             |   ||   |_|        )",
			R"(             |   ||   |/         )",
			R"(             |   /\   |          )",
			R"(            /___/  \___\         )"
		},
		{
			R"(                 /\              )",
			R"(        |       /  \             )",
			R"(        |     _/____\_           )",
			R"(        |      |\  /|            )",
			R"(        /\  ____\--/____         )",
			R"(        \/\/    \\//    \        )",
			R"(        /        \/     |        )",
			R"(         \  /|   ||     |        )",
			R"(          \/ |   ||   | |        )",
			R"(             |   ||   |_|        )",
			R"(             |   ||   |/         )",
			R"(             |   /\   |          )",
			R"(            /___/  \___\         )"
		},
		{
			R"(                 /\              )",
			R"(                /  \             )",
			R"(              _/____\_           )",
			R"(               |X  X|            )",
			R"(            ____\--/____         )",
			R"(           /    \\//    \        )",
			R"(          /      \/     |        )",
			R"(         /   |   ||   | |        )",
			R"(    ____/\  /|   ||   | |        )",
			R"(        \/\/ |   ||   |/         )",
			R"(             |   ||   |          )",
			R"(             |   /\   |          )",
			R"(            /___/  \___\         )"
		}
	)
	{
	}
};
class barbaro : public nemico
{
public:
	barbaro() : nemico
	(
		"barbaro",
		90,
		30,
		70,
		30,
		{
			R"(               |\/\/\/|          )",
			R"(               | \  / |          )",
			R"(               |  __  |          )",
			R"(             ___\____/___        )",
			R"(            /\__/    \__/\       )",
			R"(           / /|  °  °  | |       )",
			R"(          / / | °    ° | |       )",
			R"(         /_/  \  °  °  /_|       )",
			R"(      __/_/__ [/|\##/|\]_|       )",
			R"(       | | |   |  /\  |          )",
			R"(       | | |   ( |  | )          )",
			R"(       | | |   | |  | |          )",
			R"(       | | |  [__|  |__]         )"
		},
		{
			R"(    |\         |\/\/\/|          )",
			R"(    | \        | \  / |          )",
			R"(     \ \       |  __  |          )",
			R"(      \ \/   ___\____/___        )",
			R"(       \/\  /\__/    \__/\       )",
			R"(       /\/\/ /|  °  °  | |       )",
			R"(         \  / | °    ° | |       )",
			R"(          \/  \  °  °  /_|       )",
			R"(              [/|\##/|\]_|       )",
			R"(               |  /\  |          )",
			R"(               ( |  | )          )",
			R"(               | |  | |          )",
			R"(              [__|  |__]         )"
		},
		{
			R"(                                 )",
			R"(               |\/\/\/|          )",
			R"(               | X  X |          )",
			R"(               |  __  |          )",
			R"(             ___\____/___        )",
			R"(            /\__/    \__/\       )",
			R"(          |--------\°  | |       )",
			R"(       ---|-------| ° | |       )",
			R"(          |--------/°  /_|       )",
			R"(            |_[/|\##/|\]_|       )",
			R"(               |  /\  | __       )",
			R"(               | |/ | |/  |      )",
			R"(               (__/|(__/|_|      )"
		}
	)
	{
	}
};



void crea_mob(vector<nemico*>& mob)
{
	int mob_type;
	mob_type = rand() % 3;
	switch (mob_type)
	{


	case 0:
		mob.push_back(new orco());
		break;

	case 1:
		mob.push_back(new mago_nero());
		break;

	case 2:
		mob.push_back(new barbaro());
		break;
	}
}
bool prima(vector<nemico*> mob, player giocatore, int index)
{
	bool primo;
	if (mob[index]->getspeed() < giocatore.getspeed())
		primo = true;
	else
		primo = false;
	return primo;
}

void combattimento(vector<nemico*>& mob, player& giocatore, int index,int& kill)
{
	cout << "\033[2J\033[1;1H";
	this_thread::sleep_for(chrono::milliseconds(100));
	cout << "e comparso un... " << mob[index]->getclasse();
	this_thread::sleep_for(chrono::milliseconds(1200));
	while (true)
	{
		cout << "\033[2J\033[1;1H";
		cout << "\t\t\t\t\t\t\t\t\t\t" << mob[index]->getclasse() << " " << mob[index]->getvita() << " hp " << endl;
		mob[index]->disegna_fermo();
		this_thread::sleep_for(chrono::milliseconds(1000));
		if (prima(mob, giocatore, index))
		{
			giocatore.turno(mob[index]->getvita(), mob[index]->getdanno());
			if (mob[index]->getvita() > 0)
			{
				cout << "\033[2J\033[1;1H";
				cout << "\t\t\t\t\t\t\t\t\t\t" << mob[index]->getclasse() << " " << mob[index]->getvita() << " hp " << endl;
				mob[index]->disegna_attacco();
				mob[index]->attacca(giocatore.getvita());
			}
		}
		else
		{
			cout << "\033[2J\033[1;1H";
			cout << "\t\t\t\t\t\t\t\t\t\t" << mob[index]->getclasse() << " " << mob[index]->getvita() << " hp " << endl;
			mob[index]->disegna_attacco();
			mob[index]->attacca(giocatore.getvita());
			this_thread::sleep_for(chrono::milliseconds(1500));
			if (giocatore.getvita() > 0) 
			{
				cout << "\033[2J\033[1;1H";
				cout << "\t\t\t\t\t\t\t\t\t\t" << mob[index]->getclasse() << " " << mob[index]->getvita() << " hp " << endl;
				mob[index]->disegna_fermo();
				giocatore.turno(mob[index]->getvita(), mob[index]->getdanno());
			}
		}
		if (mob[index]->getvita() <= 0)
		{
			cout << "\033[2J\033[1;1H";
			mob[index]->disegna_morto();
			delete mob[index];
			mob.erase(mob.begin() + index);
			kill += 1;
			this_thread::sleep_for(chrono::milliseconds(1500));
			break;
		}
		this_thread::sleep_for(chrono::milliseconds(1500));
		if (giocatore.getvita() <= 0)
			break;
	}

}
int main()
{
	srand(time(NULL));
	vector<string>mappa =
	{
		"####################",
		"#                  #",
		"#                  #",
		"#        #         #",
		"#        #         #",
		"####################",
	};
	int mappaymax = mappa.size();
	int mappaxmax = mappa[0].size();

	player you;
	you.setName();
	you.choose_classe();
	vector<nemico*>mob;
	char input;
	int kill = 0;
	int nmob = rand() % 4;
	for (int i = 0; i <= nmob; i++)
	{
		crea_mob(mob);
	}
	do { you.pos_play1(mappaymax, mappaxmax); } while (mappa[you.getposy()][you.getposx()] == '#');
	//pos nemico
	for (int i = 0; i < mob.size(); i++)
	{
		do { mob[i]->pos_nemico1(mappaymax, mappaxmax); } while (mappa[mob[i]->getposny()][mob[i]->getposnx()] == '#' ||  //controlla pos nemico diversa da muri
			(you.getposy() == mob[i]->getposny() && you.getposx() == mob[i]->getposnx()));//controlla pos nemico diversa da player

	}
	while (true)
	{

		cout << "\033[2J\033[1;1H";
		cout << you.getname() << endl
			<< you.getclasse() << endl
			<< you.getvita()<<" hp" << endl 
			<< "uccisioni: " << kill <<endl
			<<"mostri rimasti : " <<mob.size() << endl << endl << endl;
		for (int y = 0; y < mappa.size(); y++)
		{
			for (int x = 0; x < mappa[y].size(); x++)
			{
				if (y == you.getposy() && x == you.getposx())
				{
					cout << 'p';
				}
				else
				{
					bool mobtrovato = false;
					for (int i = 0; i < mob.size(); i++)
					{
						if (y == mob[i]->getposny() && x == mob[i]->getposnx())
						{
							cout << 'm';
							mobtrovato = true;
							break;
						}
					}
					if (!mobtrovato)
					{
						cout << mappa[y][x];
					}
				}
			}
			cout << endl;
		}
		char input = _getch();
		int newposy = you.getposy();
		int newposx = you.getposx();
		if (input == 'w')
			newposy--;
		if (input == 'a')
			newposx--;
		if (input == 's')
			newposy++;
		if (input == 'd')
			newposx++;
		if (mappa[newposy][newposx] != '#')
		{
			for (int i = 0; i < mob.size(); i++)
			{
				int ym = mob[i]->getposny();
				int xm = mob[i]->getposnx();
				if (newposy == ym && newposx == xm)
				{
					combattimento(mob, you, i, kill);
					break;
				}

			}
			if (you.getvita() > 0)
			{
				you.getposy() = newposy;
				you.getposx() = newposx;
			}
			else
				break;
		}
		if (you.getvita() <= 0)
			break;
		this_thread::sleep_for(chrono::milliseconds(300));
		if (mob.size()==0)
		{
			nmob = rand() % 4;
			for (int i = 0; i <= nmob; i++)
			{
				crea_mob(mob);
			}
		}
	}
	cout << "game over";
	cin.ignore();
	cin.get();
	return 0;
}


// Per eseguire il programma: CTRL+F5 oppure Debug > Avvia senza eseguire debug
// Per eseguire il debug del programma: F5 oppure Debug > Avvia debug

// Suggerimenti per iniziare: 
//   1. Usare la finestra Esplora soluzioni per aggiungere/gestire i file
//   2. Usare la finestra Team Explorer per connettersi al controllo del codice sorgente
//   3. Usare la finestra di output per visualizzare l'output di compilazione e altri messaggi
//   4. Usare la finestra Elenco errori per visualizzare gli errori
//   5. Passare a Progetto > Aggiungi nuovo elemento per creare nuovi file di codice oppure a Progetto > Aggiungi elemento esistente per aggiungere file di codice esistenti al progetto
//   6. Per aprire di nuovo questo progetto in futuro, passare a File > Apri > Progetto e selezionare il file con estensione sln
