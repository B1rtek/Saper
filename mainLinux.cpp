#include <bits/stdc++.h>                                     //BITSY SĄ NAJLEPSZE - BITSY FOREVER!!!
#include <iostream>
//#include <windows.h>                                         //NIE MA TO JAK APLIKACJE KONSOLOWE !!!! :DDDD nie bo są za wolne
#include <curses.h>                                           //EZ INPUT BOIIII
#include <queue>                                             //YEA BOII ADVANCED CODING TEKNIQUEZ (tak btw to to jest w bitsach)

using namespace std;

int wys=8, szer=8, miny=10, exitValue=0, flagi=0;            //ZMIENNE WIELKOŚCI PLANSZY
int takasobiezmiennaniesluzacaniczemuproduktywnemu=0;        //STAWIANIE FLAG NA ŚLEPO
char wybor;
int plansza[200][200];                                       //GLOBALNA PLANSZA
int odkryte[200][200];
int winXPmode=1, np, pozostale, centrmode=1;                 //USTAWIENIA
string winXPstate="ON", centrstate="ON";                     //RESZTA ZMIENNYCH USTAWIEŃ
string sterstate="WASD, M - sweep, N - flag";
string level="Easy";                                        //ZMIENNA POZIOMU TRUDNOŚCI
char lewo='a', prawo='d', up='w', down='s', chord='n', reveal='m';
int ruchy=0;

//https://stackoverflow.com/questions/26920261/read-a-string-with-ncurses-in-c
std::string getstring()
{
    std::string input;

    // let the terminal do the line editing
    nocbreak();
    echo();

    // this reads from buffer after <ENTER>, not "raw"
    // so any backspacing etc. has already been taken care of
    int ch = getch();

    while ( ch != '\n' )
    {
        input.push_back( ch );
        ch = getch();
    }

    // restore your cbreak / echo settings here

//    noecho();
    cbreak();

    return input;
}

void menu()
{
    system("clear");
	cout<<"Welcome to Terminal Minesweeper 1.31!\r\n";
	if(level=="Custom")
	{
		cout<<"1 - Start game ("<<level<<" - "<<wys<<"/"<<szer<<"/"<<miny<<")\r\n";
	}
	else
	{
		cout<<"1 - Start game ("<<level<<")\r\n";
	}
	cout<<"2 - Choose difficulty\r\n";
	cout<<"3 - How to play\r\n";
	cout<<"4 - Game settings\r\n";
	cout<<"5 - Exit\r\n";
}

void settings()
{
	system("clear");
	cout<<"Choose a difficulty level:\r\n";
	cout<<"1 - Easy\r\n";
	cout<<"2 - Advanced\r\n";
	cout<<"3 - Expert\r\n";
	cout<<"4 - Custom...\r\n";
    wybor=getch();
	switch(wybor)
	{
		case '1':
			{
				wys=8;
				szer=8;
				miny=10;
				level="Easy";
			}
		break;
		case '2':
			{
				wys=16;
				szer=16;
				miny=40;
				level="Advanced";
			}
		break;
		case '3':
			{
				wys=24;
				szer=24;
				miny=99;
				level="Expert";
			}
		break;
		case '4':
			{
				err1:
				err2:
				err4:
				cout<<"Enter custom board height (max=25):\r\n";
				wys = stoi(getstring());
//                cin>>wys;
				if(wys>25)
				{
					cout<<"That's too much.	\r\n";
					goto err2;
				}
				err3:
				cout<<"Enter custom board width (max=120):\r\n";
//				cin>>szer;
                szer = stoi(getstring());
				if(szer>120)
				{
					cout<<"That's too much.	\r\n";
					goto err3;
				}
				if(wys*szer<10)
				{
					cout<<"This board is too small. The minimum size of the board is 10.\r\n\r\n";
					goto err4;
				}
				cout<<"Enter the amount of mines (max="<<wys*szer-9<<"):\r\n";
//				cin>>miny;
                miny = stoi(getstring());
				if(miny>wys*szer-9)
				{
					cout<<"These settings are incorrect.\r\n";
					goto err1;
				}
				level="Custom";
			}
		break;
	}
}

void ui()
{
	dobrazmiana:
	system("clear");
	cout<<"Game settings\r\n";
	cout<<"1 - Change resolution\r\n";
	cout<<"2 - Windows Mode: "<<winXPstate<<"\r\n";
	cout<<"3 - Center the board: "<<centrstate<<"\r\n";
	cout<<"4 - Key binds: "<<sterstate<<"\r\n";
	wybor=getch();
	switch(wybor)
	{
		case '1':
			{
				system("clear");
				cout << "Not supported\r\n";
//                cout<<"Aby zmienić rozdzielczość:\r\n";
//				cout<<" - Kliknij prawym na pasek konsoli -> Właściwości\r\n";
//				cout<<" - W zakładce Czcionka zmiana rozmiaru zmieni wielkośc elementów. \r\n   Domyślny rozmiar to 16.\r\n";
//				cout<<"Przy zmniejszaniu rozdzielczości może nastąpić spadek wielkości okna gry. Aby ją zmienić:\r\n";
//				cout<<" - Kliknij prawym na pasek konsoli -> Właściwości\r\n";
//				cout<<" - W zakładce Układ zmień rozmiar okna na 120x30 - jest to minimum dla tego programu.\r\n";
//				cout<<"Przy zwiększaniu rozdzielczości sugerowane jest wyłączenie centralizacji.\r\n";
				/*HWND console = GetConsoleWindow();
				RECT ConsoleRect;
				GetWindowRect(console, &ConsoleRect);
				MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 993, 519, TRUE);*/
//				SetConsoleTextAttribute(hOut, 0);
				getch();
//				SetConsoleTextAttribute(hOut, 7);
			}
		break;
		case '2':
			{
				system("clear");
				if(winXPmode==0)
				{
					winXPmode=1;
					winXPstate="ON";
				}
				else
				{
					winXPmode=0;
					winXPstate="OFF";
				}
				goto dobrazmiana;
			}
		break;
		case '3':
			{
				if(centrmode==1)
				{
					centrmode=0;
					centrstate="OFF";
				}
				else
				{
					centrmode=1;
					centrstate="ON";
				}
				goto dobrazmiana;
			}
		break;
		case '4':
			{
				if(sterstate=="WASD, M - sweep, N - flag")
				{
					sterstate="Arrow keys, D - sweep, S - flag";
					lewo=75; prawo=77, up=72, down=80, chord='s', reveal='d';
					cout<<"\r\nChanged binds to: Arrow keys, D - sweep, S - flag\r\n";
				}
				else
				{
					sterstate="WASD, M - sweep, N - flag";
					lewo='a'; prawo='d', up='w', down='s', chord='n', reveal='m';
					cout<<"\r\nChanged binds to: WASD, M - sweep, N - flag\r\n";
				}
				system("pause");
				goto dobrazmiana;
			}
		break;
	}
}

void howToPlayOTejgrze()
{
//	HANDLE hOut;
	system("clear");
	cout<<"Flag all mines to win!\r\n";
	cout<<"Number on a field tells how many mines are on the adjacent fields around it. The amount of mines left\r\nis shown on the counter below the board or on the titlebar.\r\n";
//	cout<<"Sterowanie:\r\n";
//	cout<<"w, a, s, d - poruszanie się po planszy\r\n";
//	cout<<"m - odkrycie pola\r\n";
//	cout<<"n - na polu nieodkrytym - oflagowanie pola\r\n";
//	cout<<"  - na polu odkrytym - chord\n\r\n";
//	SetConsoleTextAttribute(hOut, 0);
	getch();
//	SetConsoleTextAttribute(hOut, 7);
}

void field(int y, int x)
{
	odkryte[y][x]=1;
	if(plansza[y-1][x-1]==0 && odkryte[y-1][x-1]==0)
	{
		field(y-1, x-1);
	}
	if(odkryte[y-1][x-1]==2)
	{
		flagi++;
	}
	odkryte[y-1][x-1]=1;
	if(plansza[y-1][x]==0 && odkryte[y-1][x]==0)
	{
		field(y-1, x);
	}
	if(odkryte[y-1][x]==2)
	{
		flagi++;
	}
	odkryte[y-1][x]=1;
	if(plansza[y-1][x+1]==0 && odkryte[y-1][x+1]==0)
	{
		field(y-1, x+1);
	}
	if(odkryte[y-1][x+1]==2)
	{
		flagi++;
	}
	odkryte[y-1][x+1]=1;
	if(plansza[y][x-1]==0 && odkryte[y][x-1]==0)
	{
		field(y, x-1);
	}
	if(odkryte[y][x-1]==2)
	{
		flagi++;
	}
	odkryte[y][x-1]=1;
	if(plansza[y][x+1]==0 && odkryte[y][x+1]==0)
	{
		field(y, x+1);
	}
	if(odkryte[y][x+1]==2)
	{
		flagi++;
	}
	odkryte[y][x+1]=1;
	if(plansza[y+1][x-1]==0 && odkryte[y+1][x-1]==0)
	{
		field(y+1, x-1);
	}
	if(odkryte[y+1][x-1]==2)
	{
		flagi++;
	}
	odkryte[y+1][x-1]=1;
	if(plansza[y+1][x]==0 && odkryte[y+1][x]==0)
	{
		field(y+1, x);
	}
	if(odkryte[y+1][x]==2)
	{
		flagi++;
	}
	odkryte[y+1][x]=1;
	if(plansza[y+1][x+1]==0 && odkryte[y+1][x+1]==0)
	{
		field(y+1, x+1);
	}
	if(odkryte[y+1][x+1]==2)
	{
		flagi++;
	}
	odkryte[y+1][x+1]=1;
}

void windowsXP(int szer, int miny, int tryb)
{
	//WINDOWS XP ADDONS OH YEA BOI XD
//	HANDLE hOut;
//	hOut = GetStdHandle( STD_OUTPUT_HANDLE );
//	SetConsoleTextAttribute(hOut, 16*0+0);
    cout <<"\033[30m";
	if(centrmode==1)
	{
		for(int i=1; i<=(120-szer)/2; i++)
		{
			cout<<" ";
		}
	}
//	SetConsoleTextAttribute(hOut, 16*1+15);
	int wyw=0;
    cout <<"\033[37;44m";
	if(szer<9)
		{
		if(szer>=5)
		{
			cout<<"S";
			wyw++;
			for(int i=2; i<=szer-4; i++)
				{
				cout<<".";
				wyw++;
			}
		}
		if(wyw==szer-4)
		{
			cout<<" ";
		}
	}
	else
	{
		cout<<"Saper";
		for(int i=1; i<=szer-8; i++)
		{
			cout<<" ";
		}
	}
	cout<<"_"<<char(182);
//	SetConsoleTextAttribute(hOut, 16*1+4);
	cout<<"\033[31m";
    cout<<"X";
	if(winXPmode==0)
	{
		goto winXPskip;
	}
	cout<<"\r\n";
    cout <<"\033[30;40m";
//	SetConsoleTextAttribute(hOut, 16*0+0);
	if(centrmode==1)
	{
		for(int i=1; i<=(120-szer)/2; i++)
		{
			cout<<" ";
		}
	}
	if(szer%2==1)
	{
		np=1;
	}
	pozostale=szer-8-np;
//	SetConsoleTextAttribute(hOut, 16*7+0);
    cout <<"\033[47m";
    if(pozostale%4==2)
	{
		for(int i=0; i<(pozostale-2)/4; i++)
		{
			cout<<" ";
		}
	}
	else
	{
		for(int i=0; i<pozostale/4; i++)
		{
			cout<<" ";
		}
	}
//	SetConsoleTextAttribute(hOut, 16*0+4);
    cout <<"\033[31;40m";
    if(szer<=4)
	{
		if(miny>9)
		{
			cout<<9;
		}
		else
		{
			cout<<miny;
		}
	}
	else if(szer<=7)
	{
	if(miny>99)
		{
			cout<<99;
		}
		else
		{
			if(miny<10)
			{
				cout<<0;
			}
			cout<<miny;
		}
	}
	else
	{
		if(miny>999)
		{
			cout<<999;
		}
		else
		{
			if(miny<100)
			{
				cout<<0;
			}
			if(miny<10)
			{
				cout<<0;
			}
			cout<<miny;
		}
	}
//	SetConsoleTextAttribute(hOut, 16*7+0);
    cout <<"\033[47m";
	if(pozostale%4==2)
	{
		for(int i=0; i<(pozostale+2)/4; i++)
		{
			cout<<" ";
		}
	}
	else
	{
		for(int i=0; i<pozostale/4; i++)
		{
			cout<<" ";
		}
	}
//	SetConsoleTextAttribute(hOut, 16*6+0);
    cout <<"\033[30;43m";
	if(szer==3 || szer==5)
	{
		if(tryb==1)
		{
			cout<<"X";
		}
		else
		{
			cout<<"D";
		}
	}
	else
	{
		if(tryb==1)
		{
			cout<<"XD";
		}
		else
		{
			cout<<":D";
		}
		if(np==1)
		{
			cout<<" ";
		}
	}
//	SetConsoleTextAttribute(hOut, 16*7+0);
    cout <<"\033[47m";
	if(pozostale%4==2)
	{
		for(int i=0; i<(pozostale+2)/4; i++)
		{
			cout<<" ";
		}
	}
	else
	{
		for(int i=0; i<pozostale/4; i++)
		{
			cout<<" ";
		}
	}
//	SetConsoleTextAttribute(hOut, 16*0+4);
    cout <<"\033[31;40m";
	if(szer<=4)
	{
		if(ruchy>9)
		{
			cout<<9;
		}
		else
		{
			cout<<ruchy;
		}
	}
	else if(szer<=7)
	{
		if(ruchy>99)
		{
			cout<<99;
		}
		else
		{
			if(ruchy<10)
			{
				cout<<0;
			}
			cout<<ruchy;
		}
	}
	else
	{
		if(ruchy>999)
		{
			cout<<999;
		}
		else
		{
			if(ruchy<100)
			{
				cout<<0;
			}
			if(ruchy<10)
			{
				cout<<0;
			}
			cout<<ruchy;
		}
	}
//	SetConsoleTextAttribute(hOut, 16*7+0);
    cout <<"\033[47m";
	if(pozostale%4==2)
	{
		for(int i=0; i<(pozostale-2)/4; i++)
		{
			cout<<" ";
		}
	}
	else
	{
		for(int i=0; i<pozostale/4; i++)
		{
			cout<<" ";
		}
	}
	winXPskip:
	cout<<"\r\n";
//	SetConsoleTextAttribute(hOut, 16*0+0);
    cout <<"\033[30;40m";
	//TUN DUN DUN DUUUUUUUUN HASTA LA VISTA BILL GATES
}

void gra(int wys, int szer, int miny)
{
	//INDICATOR ODKRYCIA POLA - ZEROWANIE
	for(int i=1; i<=wys; i++)
	{
		for(int j=1; j<=szer; j++)
		{
			odkryte[i][j]=0;
		}
	}
	//GENERACJA POLA WEWNĄTRZ FTOAFU - CASE N (FTOAF==TRUE)
	char wejscie;
	int wskX=szer/2;
	int wskY=wys/2;
	bool ftoaf=true;
	int oflagowane=0;
	flagi=miny;
//	HANDLE hOut;
//	hOut = GetStdHandle( STD_OUTPUT_HANDLE );
	ruchy=0;
	//GRA - PĘTLA GŁÓWNA
	for(;;)
	{
		if(ruchy==0)
		{
			system("clear");
		}
		else
		{
			for(int i=1; i<=30; i++)
			{
				cout<<"\r\x1b[A\r";
			}
		}
		if(centrmode==1)
		{
			for(int i=1; i<=(30-(wys+2))/2; i++)
			{
				cout<<"\r\n";
			}
		}
		int bg=0;                       //ZMIENNE OKREŚLAJĄCE BARWĘ OUTPUTU - KOLORY NA PODSTAWIE PALETA_BARW.CPP
		int fg=0;
		int zmiana=0;
		windowsXP(szer, flagi, 0);
		for(int i=1; i<=wys; i++)
		{
			if(centrmode==1)
			{
				for(int i=1; i<=(120-szer)/2; i++)
				{
					cout<<" ";
				}
			}
			for(int j=1; j<=szer; j++)
			{
				//INTERPRETER KOLORU:
				if(odkryte[i][j]==0)
				{
					if(zmiana==0)
					{
						bg=100;
						fg=30;
						zmiana=1;
					}
					else
					{
						bg=40;
						fg=90;
						zmiana=0;
					}
				}
				if(odkryte[i][j]==1 || odkryte[i][j]==2)
				{
					if(zmiana==0)
					{
						bg=107;
						zmiana=1;
					}
					else
					{
						bg=47;
						zmiana=0;
					}
					switch(plansza[i][j])
					{
						case 0:
							{
								fg=37;
							}
						break;
						case 1:
							{
								fg=34;
							}
						break;
						case 2:
							{
								fg=92;
							}
						break;
						case 3:
							{
								fg=31;
							}
						break;
						case 4:
							{
								fg=35;
							}
						break;
						case 5:
							{
								fg=36;
							}
						break;
						case 6:
							{
								fg=93;
							}
						break;
						case 7:
							{
								fg=30;
							}
						break;
						case 8:
							{
								fg=90;
							}
						break;
					}
				}
				if(odkryte[i][j]==2)
				{
					fg=91;
				}
				if(i==wskY && j==wskX)
				{
					bg=46;
				}
                string color = "\033[" + to_string(bg) + ";" + to_string(fg) + "m";
                cout << color;
//				SetConsoleTextAttribute(hOut, 16*bg+fg);
				//WYPISYWANIE PO DOKONANIU INTERPRETACJI KOLORU POLA
				if(odkryte[i][j]==1)
				{
					if(plansza[i][j]==9)
					{
						cout<<"x";
					}
					else if(plansza[i][j]==0)
					{
						cout<<" ";
					}
					else
					{
						cout<<plansza[i][j];
					}
				}
				else if(odkryte[i][j]==2)
				{
					cout<<"!";
				}
				else
				{
					cout<<"-";
				}
			}
			if(szer%2==0)
			{
				if(zmiana==1)
				{
					zmiana=0;
				}
				else
				{
					zmiana=1;
				}
			}
			cout<<"\r\n"<<"\033[30;40m";
//			SetConsoleTextAttribute(hOut, 16*0+0);
		}
        cout<<"\033[37m";
//		SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		if(winXPmode==0)
		{
			if(centrmode==1)
			{
				for(int i=1; i<=(120-szer)/2; i++)
				{
					cout<<" ";
				}
			}
			cout<<"Mines left:"<<flagi;
		}
		//WIN CONDITION
		if(oflagowane==miny)
		{
			int przypax=0;
			for(int i=1; i<=wys; i++)
			{
				for(int j=1; j<=szer; j++)
				{
					if(odkryte[i][j]==0)
					{
						przypax++;
					}
				}
			}
			if(przypax==0)
			{
				if(centrmode==1)
				{
					for(int i=1; i<=((120-3)/2)+1; i++)
					{
						cout<<" ";
					}
				}
				cout<<"GG!\r\n";
//				SetConsoleTextAttribute(hOut, 16*0+0);
                getch();
//				SetConsoleTextAttribute(hOut, 16*0+7);
				break;
			}
		}
		wejscie=getch();
		if(wejscie==lewo)
				{
					wskX--;
					if(wskX==0)
					{
						wskX=szer;
					}
					ruchy++;
				}
		else if(wejscie==prawo)
				{
					wskX++;
					if(wskX>szer)
					{
						wskX=1;
					}
					ruchy++;
				}
		else if(wejscie==up)
				{
					wskY--;
					if(wskY==0)
					{
						wskY=wys;
					}
					ruchy++;
				}
		else if(wejscie==down)
				{
					wskY++;
					if(wskY>wys)
					{
						wskY=1;
					}
					ruchy++;
				}
		else if(wejscie==reveal)
				{
					if(odkryte[wskY][wskX]==2)
					{
						goto flaga;
					}
					odkryte[wskY][wskX]=1;
					if(ftoaf==true)
					{
						//GENERACJA PLANSZY - LOSOWANIE MIN
						int wielkosc=wys*szer;
						int wynikL[wielkosc+1];
						for(int i=1; i<=wielkosc; i++)
						{
							wynikL[i]=0;
						}
						int left=miny;
						int drop=0;
						re:
						for(int i=1; i<=wielkosc; i++)
						{
							drop=rand()%(left*2)+1;            // <-------------------- RANDOMIZER !!! <---------------- GENERATOR MAPY !!! ---------------
							if(drop==1)						   // <-- ABY ZMIENIĆ GENERACJĘ, ZMIENIAMY LICZBĘ X W WYRAŻENIU (LEFT*X) -->
							{
							if(wynikL[i]==0)
								{
									wynikL[i]=1;
									left--;
								}
								if(left==0)
								{
									break;
								}
							}
						}
						if(left!=0)
						{
							goto re;
						}
						//ZEROWANIE PLANSZY I WSTAWIENIE GRANIC
						for(int i=0; i<=wys+1; i++)
						{
							for(int j=0; j<=szer+1; j++)
							{
								if(i==0 || i==wys+1 || j==0 || j==szer+1)
								{
									plansza[i][j]=10;
								}
								else
								{
									plansza[i][j]=0;
								}
							}
						}
						for(int i=0; i<=szer+1; i++)
						{
							plansza[0][i]=10;
						}
						//WSTAWIENIE BOMB NA PLANSZĘ Z UWAGĄ NA FTOAF
						int doRelokacji=0, naPolu=0;
						queue <int> relokacja;
						for(int i=1; i<=wys; i++)
						{
							for(int j=1; j<=szer; j++)
							{
								if(wynikL[(i-1)*szer+j]==1)
								{
									int przypal=0;
									if(i==wskY || i==wskY-1 || i==wskY+1)
									{
										if(j==wskX || j==wskX-1 || j==wskX+1)
										{
											przypal++;
										}
									}
									if(przypal==0)
									{
										plansza[i][j]=9;
										naPolu++;
									}
									else
									{
										doRelokacji++;
										wynikL[(i-1)*szer+j]=0;
									}
								}
								else
								{
									int wsad=(i-1)*szer+j;
									relokacja.push(wsad);
								}
							}
						}
						rel:
						int rele=0;
						if(doRelokacji>0)
						{
							for(int i=1; i<=doRelokacji; i++)
							{
								wynikL[relokacja.front()]=1;
								naPolu++;
								relokacja.pop();
							}
							for(int i=1; i<=wys; i++)
							{
								for(int j=1; j<=szer; j++)
								{
									if(wynikL[(i-1)*szer+j]==1)
									{
										int przypal=0;
										if(i==wskY || i==wskY-1 || i==wskY+1)
										{
											if(j==wskX || j==wskX-1 || j==wskX+1)
											{
												przypal++;
											}
										}
										if(przypal==0)
										{
											if(plansza[i][j]!=9)
											{
												plansza[i][j]=9;
												doRelokacji--;
											}
										}
										else
										{
											rele=1;
										}
									}
								}
							}
						}
						if(rele==1)
						{
							goto rel;
						}
						//GENERACJA NUMERÓW PLANSZY
						for(int i=1; i<=wys; i++)
						{
							for(int j=1; j<=szer; j++)
							{
								if(plansza[i][j]==9) continue;
								int pole=0;
								if(plansza[i-1][j-1]==9) pole++;
								if(plansza[i-1][j]==9) pole++;
								if(plansza[i-1][j+1]==9) pole++;
								if(plansza[i][j-1]==9) pole++;
								if(plansza[i][j+1]==9) pole++;
								if(plansza[i+1][j-1]==9) pole++;
								if(plansza[i+1][j]==9) pole++;
								if(plansza[i+1][j+1]==9) pole++;
								plansza[i][j]=pole;
							}
						}
						//FIELD OPEN
						field(wskY, wskX);
						ftoaf=false;
					}
					if(plansza[wskY][wskX]==9)
					{
						ded:
                        cout << "\033[30;40m";
						system("clear");
						if(centrmode==1)
						{
							for(int i=1; i<=(30-(wys+2))/2; i++)
							{
								cout<<"\r\n";
							}
						}
						windowsXP(szer, flagi, 1);
						int zmiennik=0;
						for(int i=1; i<=wys; i++)
						{
//							SetConsoleTextAttribute(hOut, 16*0+0);
                            cout << "\033[30;40m";
							if(centrmode==1)
							{
								for(int i=1; i<=(120-szer)/2; i++)
								{
									cout<<" ";
								}
							}
							for(int j=1; j<=szer; j++)
							{
								//INTERPRETER KOLORU EKRANU ŚMIERCI (NIE, PODSTAWOWY <strong> NIE </strong> DZIAŁA
								if(zmiennik==0)
								{
									bg=47;
									zmiennik=1;
								}
								else
								{
									bg=107;
									zmiennik=0;
								}
								switch(plansza[i][j])
								{
									case 0:
										{
											fg=37;
										}
									break;
									case 1:
										{
											fg=34;
										}
									break;
									case 2:
										{
											fg=92;
										}
									break;
									case 3:
										{
											fg=31;
										}
									break;
									case 4:
										{
											fg=35;
										}
									break;
									case 5:
										{
											fg=33;
										}
									break;
									case 6:
										{
											fg=36;
										}
									break;
									case 7:
										{
											fg=30;
										}
									break;
									case 8:
										{
											fg=94;
										}
									break;
									case 9:
										{
											fg=31;
										}
									break;
								}
								if(odkryte[i][j]==2)
								{
									fg=91;
									if(plansza[i][j]!=9)
									{
										fg=30;
									}
								}
                                string color = "\033[" + to_string(bg) + ";" + to_string(fg) + "m";
                                cout << color;
//								SetConsoleTextAttribute(hOut, 16*bg+fg);
								if(plansza[i][j]==9)
								{
									if(odkryte[i][j]==2)
									{
										cout<<"!";
									}
									else
									{
										cout<<"x";
									}
								}
								else if(odkryte[i][j]==2)
								{
									cout<<"X";
								}
								else if(plansza[i][j]==0)
								{
									cout<<" ";
								}
								else
								{
									cout<<plansza[i][j];
								}
							}
							if(szer%2==0)
							{
								if(zmiennik==1)
								{
									zmiennik=0;
								}
								else
								{
									zmiennik=1;
								}
							}
                            cout << "\033[30;40m";
							cout<<"\r\n";
						}
//						SetConsoleTextAttribute(hOut, 16*0+7);
                        cout <<"\033[40;37m";
						if(winXPmode==0)
						{
							if(centrmode==1)
							{
								for(int j=1; j<=(120-szer)/2; j++)
								{
									cout<<" ";
								}
							}
							cout<<"DED   :(\r\n";
						}
						if(centrmode==1)
						{
							for(int i=1; i<=(120-szer)/2; i++)
							{
								cout<<" ";
							}
						}
//						SetConsoleTextAttribute(hOut, 16*0+0);
						getch();
//						SetConsoleTextAttribute(hOut, 16*0+7);
						goto deedhooh;
					}
					if(plansza[wskY][wskX]==0)
					{
						field(wskY, wskX);
					}
					flaga:
					cout<<" ";
					ruchy++;
				}
			else if(wejscie==chord)
				{
					if(odkryte[wskY][wskX]==1)
					{
						int x=wskX;
						int y=wskY;
						int sumaFlag=0;
						if(odkryte[y-1][x-1]==2)
						{
							sumaFlag++;
						}
						if(odkryte[y-1][x]==2)
						{
							sumaFlag++;
						}
						if(odkryte[y-1][x+1]==2)
						{
							sumaFlag++;
						}
						if(odkryte[y][x-1]==2)
						{
							sumaFlag++;
						}
						if(odkryte[y][x+1]==2)
						{
							sumaFlag++;
						}
						if(odkryte[y+1][x-1]==2)
						{
							sumaFlag++;
						}
						if(odkryte[y+1][x]==2)
						{
							sumaFlag++;
						}
						if(odkryte[y+1][x+1]==2)
						{
							sumaFlag++;
						}
						if(plansza[y][x]==sumaFlag)
						{
							if(plansza[y-1][x-1]==9 && odkryte[y-1][x-1]!=2)
							{
								goto ded;
							}
							if(odkryte[y-1][x-1]==0)
							{
								odkryte[y-1][x-1]=1;
								if(plansza[y-1][x-1]==0)
								{
									field(y-1, x-1);
								}
							}
							if(plansza[y-1][x]==9 && odkryte[y-1][x]!=2)
							{
								goto ded;
							}
							if(odkryte[y-1][x]==0)
							{
								odkryte[y-1][x]=1;
								if(plansza[y-1][x]==0)
								{
									field(y-1, x);
								}
							}
							if(plansza[y-1][x+1]==9 && odkryte[y-1][x+1]!=2)
							{
								goto ded;
							}
							if(odkryte[y-1][x+1]==0)
							{
								odkryte[y-1][x+1]=1;
								if(plansza[y-1][x+1]==0)
								{
									field(y-1, x+1);
								}
							}
							if(plansza[y][x-1]==9 && odkryte[y][x-1]!=2)
							{
								goto ded;
							}
							if(odkryte[y][x-1]==0)
							{
								odkryte[y][x-1]=1;
								if(plansza[y][x-1]==0)
								{
									field(y, x-1);
								}
							}
							if(plansza[y][x+1]==9 && odkryte[y][x+1]!=2)
							{
								goto ded;
							}
							if(odkryte[y][x+1]==0)
							{
								odkryte[y][x+1]=1;
								if(plansza[y][x+1]==0)
								{
									field(y, x+1);
								}
							}
							if(plansza[y+1][x-1]==9 && odkryte[y+1][x-1]!=2)
							{
								goto ded;
							}
							if(odkryte[y+1][x-1]==0)
							{
								odkryte[y+1][x-1]=1;
								if(plansza[y+1][x-1]==0)
								{
									field(y+1, x-1);
								}
							}
							if(plansza[y+1][x]==9 && odkryte[y+1][x]!=2)
							{
								goto ded;
							}
							if(odkryte[y+1][x]==0)
							{
								odkryte[y+1][x]=1;
								if(plansza[y+1][x]==0)
								{
									field(y+1, x);
								}
							}
							if(plansza[y+1][x+1]==9 && odkryte[y+1][x+1]!=2)
							{
								goto ded;
							}
							if(odkryte[y+1][x+1]==0)
							{
								odkryte[y+1][x+1]=1;
								if(plansza[y+1][x+1]==0)
								{
									field(y+1, x+1);
								}
							}
						}
					}
					else if(odkryte[wskY][wskX]==2)
					{
						if(ftoaf==true)
						{
							goto blad1;
						}
						odkryte[wskY][wskX]=0;
						if(plansza[wskY][wskX]==9)
						{
							oflagowane--;
						}
						flagi++;
					}
					else
					{
						if(ftoaf==true)
						{
							goto blad1;
						}
						if(flagi>0)
						{
							odkryte[wskY][wskX]=2;
							if(plansza[wskY][wskX]==9)
							{
								oflagowane++;
							}
							flagi--;
						}
					}
					if(takasobiezmiennaniesluzacaniczemuproduktywnemu==1)
					{
						blad1:
						/*cout<<"wtf dlaczego stawiasz flagi na ślepo boiiii\r\n";
						system("pause");/*/
						takasobiezmiennaniesluzacaniczemuproduktywnemu=1;
					}
					ruchy++;
				}
		else if(wejscie=='u')
				{
					goto ded;
				}
		else
				{
					continue;
				}
	}
	deedhooh:
	for(int i=1; i<=wys; i++)
	{
		for(int j=1; j<=szer; j++)
		{
			plansza[i][j]=0;
		}
	}
	cout<<"\r\n";
}

int main()
{
    initscr();
    refresh();
	setlocale(LC_CTYPE, "Polish");
	srand(time(NULL));
	for(;;)
	{
		system("clear");
		menu();
		wybor=getch();
		switch(wybor)
		{
			case '1':
				{
					gra(wys, szer, miny);
				}
			break;
			case '2':
				{
					settings();
				}
			break;
			case '3':
				{
					howToPlayOTejgrze();
				}
			break;
			case '4':
				{
					ui();
				}
			break;
			case '5':
				{
					exitValue=1;
				}
			break;
			default:
				{
					cout<<"\r\n";
				}
			break;
		}
		if(exitValue==1)
		{
			break;
		}
	}
    endwin();
    return 0;
}
