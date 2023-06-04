// classes in a game exemple.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
#include <Windows.h>
#include <iostream>
#include<stdio.h> 
#include<conio.h>  
#include<time.h>
#include <map>
#pragma comment(lib, "Kernel32.lib")





using namespace std;
bool gU = 0;           //2 global variables used in fn_attack function so we dont need to put more variables when not needed
bool* gUpt = &gU;      //never change their value
class player {
private:                   //can be used only inside the class
	int punch = 6;
	int shot = 10;
	int kick = 4;
	int uzibullet = 2;
	int stab = 4;
	int chain = 8;

public:                              //can be used outside the class
	int health = 100, ammo = 100,uziammo = 500,stammo=100;         //attributes=variables that belongs to the class
	int x = 0, y = 1;
	bool A=1;                             //ability to attack 
	bool S = 1;                         //state:alive/dead
	bool B = 0;                         //internal bleeding on or off (losses -1 every turn)
	int EX=0;                                 //enemy X position in the 
	int wp = 0;//wich weapon pack 0 or 1
	string name;
	void FN_dmg(int dmg) {           //methods=functions inside class
		health = health - dmg;
	}
	void FN_print() {
		cout << ammo;
	}
	void FN_ATTACK(int &H,int T,string target,HANDLE handle,int YC,bool &ab,int XE=0,int YE=1,bool *BE=gUpt) {
		if (name == "sam") { A = 1; }                  //attack ability is always on for the player
		COORD C;
		C.X = 0;
		C.Y = YC;
		SetConsoleCursorPosition(handle, C);
		int dmg = 0;
		if ((0 < health) && (A==1)) {                      //can attack only if healh bigger then 0 and attack ability is on
			if ((T == 10) && (wp==0)) {
				if (0 < ammo) {
					ammo = ammo - 1;
					if ((rand() % 4) != 3) {
						dmg =shot + (rand() % 5);                       
						H = H - shot;
						

					}

				}
			}
			if ((T == 11) && (wp == 0)) {
				H = H - punch;
				dmg =punch;
			}
			if ((T == 12)&&(wp==0)) {
				H = H - kick;
				dmg = kick;
				if ((rand() % 2) == 0) {
					ab = 0;
				}
				

			}
			if (T == 13) {
				H = H - chain;
				dmg = chain;
				if ((rand() % 4) == 0) {
					ab = 0;
				}


			}
			
			if ((T == 10) && (wp == 1)) { //uzi
				for (int i = 0; i < 5; i++) {
					if (0 < uziammo) {
						uziammo = uziammo - 1;
						if ((rand() % 4) != 3) {
							H = H - uzibullet;
							dmg = dmg + uzibullet;
							if (H <= 0) { break; }
						}
					}

				}
			}
			if ((T == 11) && (wp == 1)) {//shotgun 
				if (0 < stammo) {
					int S = abs((XE - x) + (YE - y) * 10);
					if (S <= 10) {
						dmg = 12;
					}
					if ((S <= 20) && (10 < S)) {
						if ((rand() % 4) != 3) {
							dmg = 10;
						}
					}
					if ((S <= 30) && (20 < S)) {
						if ((rand() % 2) == 0) {
							dmg = 8;
						}
					}
					if ((S <= 40) && (30 < S)) {
						if ((rand() % 4) == 3) {
							dmg = 6;
						}

					}
					H = H - dmg;


			    }
				else{
					cout << "out of shotgun ammo                                                ";
					return;
				}
			}
			if ((T == 12) && (wp == 1)) {//machette
				*BE = 1;
				dmg = stab;
				H = H - dmg;
				dmg = dmg + 1;
			}
	    }
		if (T == 20) {
			if ((*BE == 1)) {//bleeding from machette
				dmg = dmg + 1;
				H = H - 1;
			}
			return;
		}

	   A = 1;
	   cout << name << " dealt -" << dmg << " damage to " <<target <<"       ";
	   if (H <= 0) {
		   cout<<"   " << target << " is dead ";
	   }
	}
	int FN_shot(int H) {
		H = H - shot;
		ammo = ammo - 1;
		return H;
	}
	void FN_medkit() {
		health = 100;
	}
	bool FN_win(int k,int b=0) {
		if ((k <= 0) & (b <= 0)) {
			return 1;
		}
		else return 0;

	}
	bool enemydead(player a,player b) {
		if ((a.health <= 0) || (b.health <= 0)) {
			return 1;
		}
		else {
			return 0;
		}

	}
	bool ifalive() {
		if (health <= 0) {
			return 0;
		}
		else return 1;
	}
	void setcoord(int X1, int Y1) {
		x = X1;
		y = Y1;
	}



};
void setcursor(int x,int y,HANDLE handle) { 
	COORD C;
	C.X = x;
	C.Y = y;
	SetConsoleCursorPosition(handle, C);
}
void clearline(int y,HANDLE handle) {
	COORD C;
	C.X = 0;
	C.Y = y;
	SetConsoleCursorPosition(handle, C);
	cout << "                                                                                 ";

}


int main() {
	srand(time(0));
	map<int,int> DE = {{0,15},{15,0}};   //dictionary used when one of the enemies is dead 
	SetConsoleTitle("fighting game");
	HANDLE handle;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD C;
	player sam;
	player enemy1, enemy2; //creating objects
	sam.health = 100;
	enemy1.health = 50;
	enemy2.health = 25;
	sam.ammo = 5;
	sam.name = "sam";
	enemy1.name = "enemy1";
	enemy2.name = "enemy2";
	cout << "LEVEL1: sam: health:" << sam.health << " ammo:" << sam.ammo;
	cout << " enemy1: health:" << enemy1.health << " ammo:" << enemy1.ammo;
	cout << " enemy2: health:" << enemy2.health << " ammo:" << enemy2.ammo << endl;
	setcursor(0, 10, handle);
	cout << "=>";
	cout << "1:Shoot:75% chance of landing and deals a damage between 10 and 14";
	setcursor(2, 11, handle);
	cout << "2:punch:-6";
	setcursor(2, 12, handle);
	cout << "3:kick:-4 and 50% chance of making enemy lose his turn";
	setcursor(0, 1, handle);
	cout << "S";
	setcursor(23, 1, handle);
	cout << "E1";
	setcursor(48, 1, handle);
	cout << "E2";
	setcursor(0, 9, handle);
	cout << "=>attack enemy1  attack enemy2";
	bool i = 0;
	COORD E;                 //attacked enemy cursor
	E.X = 0;
	E.Y = 9;
	COORD D;
	D.X = 0;                //attack type cursor
	D.Y = 10;
	int W = 0;
	while(true) {
		if (GetAsyncKeyState(VK_NUMPAD1)) {
			setcursor(D.X, D.Y, handle);
			cout << "  ";
			setcursor(0, 10, handle);
			cout << "=>";
			D.X = 0; D.Y = 10;
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_NUMPAD2)) {
			setcursor(D.X, D.Y, handle);
			cout << "  ";
			setcursor(0, 11, handle);
			cout << "=>";
			D.X = 0; D.Y = 11;
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_NUMPAD3)) {
			setcursor(D.X, D.Y, handle);
			cout << "  ";
			setcursor(0, 12, handle);
			cout << "=>";
			D.X = 0; D.Y = 12;
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_RIGHT)& (sam.enemydead(enemy1, enemy2) == 0)) {
			setcursor(E.X, E.Y, handle);
			cout << "  ";
			if (E.X == 0) {
				E.X = 15;
				setcursor(E.X, E.Y, handle);
				cout << "=>";
			}
			else {
				E.X = 0;
				setcursor(E.X, E.Y, handle);
				cout << "=>";

			}
			Sleep(200);

		}
		if (GetAsyncKeyState(VK_LEFT)& (sam.enemydead(enemy1, enemy2) == 0)) {
			setcursor(E.X, E.Y, handle);
			cout << "  ";
			if (E.X == 15) {
				E.X = 0;
				setcursor(E.X, E.Y, handle);
				cout << "=>";
			}
			else {
				E.X = 15;
				setcursor(E.X, E.Y, handle);
				cout << "=>";

			}
			Sleep(200);


		}
		if (GetAsyncKeyState(VK_NUMPAD5)) {
			if (E.X == 0) {                         //attack enemy 1
				sam.FN_ATTACK(enemy1.health,D.Y,enemy1.name,handle,2,enemy1.A);
			}
			else {
				sam.FN_ATTACK(enemy2.health, D.Y, enemy2.name, handle,2, enemy2.A);
			}
			setcursor(0, 0, handle);
			cout << "LEVEL1: sam: health:" << sam.health << " ammo:" << sam.ammo;
			cout << " enemy1: health:" << enemy1.health << " ammo:" << enemy1.ammo;
			cout << " enemy2: health:" << enemy2.health << " ammo:" << enemy2.ammo << "    " << endl;
			Sleep(500);
			enemy1.FN_ATTACK(sam.health, 10 + rand() % 3, sam.name, handle,3,sam.A);
			Sleep(500);
			enemy2.FN_ATTACK(sam.health, 10 + rand() % 3, sam.name, handle,4,sam.A);
			Sleep(500);
			setcursor(0, 0, handle);
			cout << "LEVEL1: sam: health:" << sam.health << " ammo:" << sam.ammo;
			cout << " enemy1: health:" << enemy1.health << " ammo:" << enemy1.ammo;
			cout << " enemy2: health:" << enemy2.health << " ammo:" << enemy2.ammo << "    " << endl;
			if(sam.FN_win(enemy1.health,enemy2.health) == 1) {
				cout << "you won";
				W = 1;
				break;
			}
			if (sam.FN_win(sam.health) == 1) {
				cout << "you lost                            ";
				break;
			}
			if (sam.enemydead(enemy1, enemy2) == 1) {
				if (i == 0) {
					setcursor(E.X, E.Y, handle);
					cout << "               ";
					E.X = DE[E.X];
					setcursor(E.X, E.Y, handle);
					i = 1;
					cout << "=>";

				}
			}
			
			


		}
		if (GetAsyncKeyState(VK_NUMPAD7)) {
			W = 1;
			break;
		}
	}


	if (W == 1) {    //if player won pass to level 2
		for (int i = 0; i <= 12; i++) {
			clearline(i, handle);
		} 
		player enemy3, enemy4;
		enemy2.health = 50; enemy1.health = 25; enemy3.health = 75; enemy4.health = 100;
		enemy1.wp = 1; enemy2.wp = 1;
		enemy1.EX = 0; enemy2.EX = 15; enemy3.EX = 30; enemy4.EX = 45;
		map<int, player*>ptr{ {enemy1.EX,&enemy1} ,{enemy2.EX,&enemy2},{enemy3.EX,&enemy3},{enemy4.EX,&enemy4} };  //dictionary of pointers to classes
		enemy3.name = "enemy3";
		enemy4.name = "enemy4";
		sam.health = 250;
		sam.uziammo = 50;
		sam.stammo = 5;
		int XR, YR;
		setcursor(0, 0, handle);
		cout << "LEVEL2: sam: health:" << sam.health << " uzi: " << sam.uziammo << " shotgun: " << sam.stammo;
		cout << " enemy1: health:" << enemy1.health;
		cout << " enemy2: health:" << enemy2.health;
		cout << " enemy3: health:" << enemy3.health;
		cout << " enemy4: health:" << enemy4.health <<endl;
		setcursor(sam.x, sam.y, handle);
		cout << "S";
		for (auto dv : ptr) {    //basically this system makes each enemy coordinates random and unique and prevent enemy names from printing inside each other 
			bool r = 0;                
			while (true) {
				XR = 1+(rand() % 30);
				YR = 1 + (rand() % 3);
				for (auto kv : ptr) {
					if (((XR < ((kv.second->x) - 1)) || (((kv.second->x) + 1) < XR)) || (YR != kv.second->y)) {
						continue;
					}
					else { r = 1; }
				}
				if (r == 0) {
					break;
				}
				r = 0;

			}
			dv.second->x = XR;
			dv.second->y = YR;
		}

		setcursor(enemy1.x, enemy1.y, handle);
		cout << "E1";
		setcursor(enemy2.x, enemy2.y, handle);
		cout << "E2";
		setcursor(enemy3.x, enemy3.y, handle);
		cout << "E3";
		setcursor(enemy4.x, enemy4.y, handle);
		cout << "E4";
		setcursor(0, 9, handle);
		cout << "=>attack enemy1  attack enemy2  attack enemy3  attack enemy4";
		setcursor(0, 10, handle);
		cout << "=>";
		cout << "1:UZI:shoots 10 shots each one deals -2 with 75% of landing could shoot 2 enemies at once";
		setcursor(0, 11, handle);
		cout << "  2:SHOTGUN:could hit 3 enemies at once";
		setcursor(0, 12, handle);
		cout << "  3:MACHETTE:deals -5 as initial damage and causes internal bleeding wich deals -1 every turn";
		setcursor(0, 13, handle);
		cout << "  4:CHAIN:deals -8 with 25% of dropping enemy down (loses his turn)";
		D.Y = 10;
		E.X = 0;
		map<int, int> DR{ {0,15}, {15,30}, {30,45},{45,0} }; //right movement dictionary (moving between enemies)
		map<int, int> DL{ {45,30}, {30,15}, {15,0},{0,45} }; //left movement dictionary (moving between enemies)
		player* ptrT[3];
		int n = 0;
		sam.wp = 1;
        int numE=size(ptr); //number of enemies alive
		while (true) {
			if (GetAsyncKeyState(VK_RIGHT)) {
				setcursor(E.X, E.Y, handle);
				cout << "  ";
				E.X = DR[E.X];
				setcursor(E.X, E.Y, handle);
				cout << "=>";
				
				Sleep(200);
			}
			if (GetAsyncKeyState(VK_LEFT)) {
				setcursor(E.X, E.Y, handle);
				cout << "  ";
				E.X = DL[E.X];
				setcursor(E.X, E.Y, handle);
				cout << "=>";
				Sleep(200);
			}
			if (GetAsyncKeyState(VK_NUMPAD1)&&(n==0)) {
				setcursor(D.X, D.Y, handle);
				cout << "  ";
				setcursor(0, 10, handle);
				cout << "=>";
				D.X = 0; D.Y = 10;
				Sleep(100);
			}
			if (GetAsyncKeyState(VK_NUMPAD2) && (n == 0)) {
				setcursor(D.X, D.Y, handle);
				cout << "  ";
				setcursor(0, 11, handle);
				cout << "=>";
				D.X = 0; D.Y = 11;
				Sleep(100);
			}
			if (GetAsyncKeyState(VK_NUMPAD3) && (n == 0)) {
				setcursor(D.X, D.Y, handle);
				cout << "  ";
				setcursor(0, 12, handle);
				cout << "=>";
				D.X = 0; D.Y = 12;
				Sleep(100);
			}
			if (GetAsyncKeyState(VK_NUMPAD4) && (n == 0)) {
				setcursor(D.X, D.Y, handle);
				cout << "  ";
				setcursor(0, 13, handle);
				cout << "=>";
				D.X = 0; D.Y = 13;
				Sleep(100);
			}
			if (GetAsyncKeyState(VK_NUMPAD5)) {
				if ((sam.wp == 1) && ((D.Y == 10) || (D.Y==11))) {
					ptrT[n] = ptr[E.X];
					Sleep(500);
					if (D.Y == 10) {           //for uzi 
						if (n < 1) {
							n = n + 1;
							continue;
						}
						if (n == 1) {
							for (int i = 0; i <= n; i++) {
								sam.FN_ATTACK(ptrT[i]->health, 10, ptrT[i]->name, handle, 5, ptrT[i]->A);
								Sleep(500);
							}
							n = 0;
						}

					}
					if (D.Y == 11) {  //for shotgun
						bool b=1;
						int nmax = 3;        //nmax and numE are to integers to help fixing the problem when you cant shoot up to 3 enemies
						if (numE < 3) {
							nmax = numE; //maximum enemies that you can shoot
						}
						if (n <=(nmax-1)) {
							if (n != 0) {
								for (int i = 0; i <= n - 1; i++) {
									if (ptrT[n] == ptrT[i]) { b=0; }
								}
							}
							if (b == 1) { n=n+1;}
						}
						if (n == nmax) {
							for (int i = 0; i <= (n-1); i++) {
								sam.FN_ATTACK(ptrT[i]->health, 11, ptrT[i]->name, handle, 5, ptrT[i]->A, ptrT[i]->x, ptrT[i]->y);
								Sleep(500);
							}
							if(0<sam.stammo){ sam.stammo = sam.stammo - 1; }
							n = 0;
						}
						else { continue; }
					}
				}
				else {
					sam.FN_ATTACK(ptr[E.X]->health, D.Y, ptr[E.X]->name, handle, 5, ptr[E.X]->A, 0, 0, &(ptr[E.X]->B));
					Sleep(500);
				}
				for (auto KV : ptr) {
					sam.FN_ATTACK((KV.second)->health, 20, (KV.second)->name, handle, 5, (KV.second)->A, 0, 0, &((KV.second)->B));

				}
				enemy1.FN_ATTACK(sam.health,11, sam.name, handle, 6, sam.A,sam.x,sam.y);
				enemy2.FN_ATTACK(sam.health, 10, sam.name, handle, 7, sam.A);
				enemy3.FN_ATTACK(sam.health, 10, sam.name, handle, 8, sam.A);
				enemy4.FN_ATTACK(sam.health,11, sam.name, handle,15, sam.A);
				setcursor(0, 0, handle);
				cout << "LEVEL2: sam: health:" << sam.health << " uzi: " << sam.uziammo << " shotgun: " << sam.stammo;
				cout << " enemy1: health:" << enemy1.health;
				cout << " enemy2: health:" << enemy2.health;
				cout << " enemy3: health:" << enemy3.health;
				cout << " enemy4: health:" << enemy4.health << "  " << endl;
				Sleep(500);
				for (auto KV : ptr) {                       //when someoen dies this system removes its name and fix the chosing wich oppenent to attack menu
					if (KV.second->S == 1) {
						if (KV.second->health <= 0) {
							numE = numE - 1;
							KV.second->S = 0;
							DR[DL[KV.first]]=DR[KV.first];
							DL[DR[KV.first]] = DL[KV.first];
							setcursor(E.X, E.Y, handle);             //these two lines are to fix minor bugs(almost uncessasery)
							cout << "  ";
							E.X = KV.first;
							setcursor(E.X, E.Y, handle);
							cout << "                ";
							E.X = DR[E.X];
							setcursor(E.X, E.Y, handle);
							cout << "=>";
						}
					}
				}
				if (sam.FN_win(sam.health) == 1) {
					cout << "you lost                            ";
					break;
				}
			}

		}

	}
	



}
//note i should add the ability to attack for enemies and add chain 
