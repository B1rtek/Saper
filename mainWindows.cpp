#include <bits/stdc++.h>                                     //BITSY SĄ NAJLEPSZE - BITSY FOREVER!!!
#include <windows.h>                                         //NIE MA TO JAK APLIKACJE KONSOLOWE !!!! :DDDD nie bo są za wolne
#include <conio.h>                                           //EZ INPUT BOIIII
#include <queue>                                             //YEA BOII ADVANCED CODING TEKNIQUEZ (tak btw to to jest w bitsach)

using namespace std;

int wys=8, szer=8, miny=10, exitValue=0, flagi=0;            //ZMIENNE WIELKOŚCI PLANSZY
int takasobiezmiennaniesluzacaniczemuproduktywnemu=0;        //STAWIANIE FLAG NA ŚLEPO
char wybor;
int plansza[200][200];                                       //GLOBALNA PLANSZA
int odkryte[200][200];
int winXPmode=1, np, pozostale, centrmode=1;                 //USTAWIENIA
string winXPstate="ON", centrstate="ON";                     //RESZTA ZMIENNYCH USTAWIEŃ
string sterstate="Lewostronne";
string level="Łatwy";                                        //ZMIENNA POZIOMU TRUDNOŚCI
char lewo='a', prawo='d', up='w', down='s', chord='n', reveal='m'; 
int ruchy=0;

void menu()
{
	cout<<"Witaj w Saperze Konsolowym 1.31!"<<endl;
	if(level=="Niestandardowy")
	{
		cout<<"1 - Zacznij grę ("<<level<<" - "<<wys<<"/"<<szer<<"/"<<miny<<")"<<endl;
	}
	else
	{
		cout<<"1 - Zacznij grę ("<<level<<")"<<endl;
	}
	cout<<"2 - Ustawienia gry"<<endl;
	cout<<"3 - Jak grać"<<endl;
	cout<<"4 - Ustawienia"<<endl;
	cout<<"5 - Wyjście"<<endl;
}

void settings()
{
	system("cls");
	cout<<"Wybierz poziom trudności:"<<endl;
	cout<<"1 - Łatwy"<<endl;
	cout<<"2 - Zaawansowany"<<endl;
	cout<<"3 - Ekspert"<<endl;
	cout<<"4 - Niestandardowy..."<<endl;
	wybor=getch();
	switch(wybor)
	{
		case '1':
			{
				wys=8;
				szer=8;
				miny=10;
				level="Łatwy";
			}
		break;
		case '2':
			{
				wys=16;
				szer=16;
				miny=40;
				level="Zaawansowany";
			}
		break;
		case '3':
			{
				wys=24;
				szer=24;
				miny=99;
				level="Ekspert";
			}
		break;
		case '4':
			{
				err1:
				err2:
				err4:
				cout<<"Podaj wysokość planszy (max=25):";
				cin>>wys;
				if(wys>25)
				{
					cout<<"To za dużo.	\n";
					goto err2;
				}
				err3:
				cout<<"Podaj szerokość planszy (max=120):";
				cin>>szer;
				if(szer>120)
				{
					cout<<"To za dużo.	\n";
					goto err3;
				}
				if(wys*szer<10)
				{
					cout<<"Ta plansza jest za mała. Minimalny wymiar planszy to 10.\n"<<endl;
					goto err4;
				}
				cout<<"Podaj ilość min (max="<<wys*szer-9<<"):";
				cin>>miny;
				if(miny>wys*szer-9)
				{
					cout<<"Niewłaściwe ustawienia."<<endl;
					goto err1;
				}
				level="Niestandardowy";
			}
		break;
	}
}

void ui()
{
	HANDLE hOut;
	hOut = GetStdHandle( STD_OUTPUT_HANDLE );
	dobrazmiana:
	system("cls");
	cout<<"Ustawienia"<<endl;
	cout<<"1 - Rozdzielczość"<<endl;
	cout<<"2 - Windows Mode: "<<winXPstate<<endl;
	cout<<"3 - Centralizacja: "<<centrstate<<endl;
	cout<<"4 - Sterowanie: "<<sterstate<<endl;
	wybor=getch();
	switch(wybor)
	{
		case '1':
			{
				system("cls");
				cout<<"Aby zmienić rozdzielczość:"<<endl;
				cout<<" - Kliknij prawym na pasek konsoli -> Właściwości"<<endl;
				cout<<" - W zakładce Czcionka zmiana rozmiaru zmieni wielkośc elementów. \n   Domyślny rozmiar to 16."<<endl;
				cout<<"Przy zmniejszaniu rozdzielczości może nastąpić spadek wielkości okna gry. Aby ją zmienić:"<<endl;
				cout<<" - Kliknij prawym na pasek konsoli -> Właściwości"<<endl;
				cout<<" - W zakładce Układ zmień rozmiar okna na 120x30 - jest to minimum dla tego programu."<<endl;
				cout<<"Przy zwiększaniu rozdzielczości sugerowane jest wyłączenie centralizacji."<<endl;
				/*HWND console = GetConsoleWindow();
				RECT ConsoleRect;
				GetWindowRect(console, &ConsoleRect);
				MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 993, 519, TRUE);*/
				SetConsoleTextAttribute(hOut, 0);
				system("pause");
				SetConsoleTextAttribute(hOut, 7);
			}
		break;
		case '2':
			{
				system("cls");
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
				if(sterstate=="Lewostronne")
				{
					sterstate="Prawostronne";
					lewo=75; prawo=77, up=72, down=80, chord='s', reveal='d';
					cout<<"\nZmieniono sterowanie na strzałki + s = chord, d = reveal\n"; 
				}
				else
				{
					sterstate="Lewostronne";
					lewo='a'; prawo='d', up='w', down='s', chord='n', reveal='m';
					cout<<"\nZmieniono sterowanie na wasd + n = chord, m = reveal\n";  
				}
				system("pause");
				goto dobrazmiana;
			}
		break;
	}
}

void howToPlayOTejgrze()
{
	HANDLE hOut;
	system("cls");
	cout<<"Oflaguj wszystkie miny, aby wygrać!"<<endl;
	cout<<"Liczby na polach oznaczają ilość min naokoło pola. Ilość min pozostałych do oznaczenia\npokazana jest poniżej planszy."<<endl;
	cout<<"Sterowanie:"<<endl;
	cout<<"w, a, s, d - poruszanie się po planszy"<<endl;
	cout<<"m - odkrycie pola"<<endl;
	cout<<"n - na polu nieodkrytym - oflagowanie pola"<<endl;
	cout<<"  - na polu odkrytym - chord\n"<<endl;
	SetConsoleTextAttribute(hOut, 0);
	system("pause");
	SetConsoleTextAttribute(hOut, 7);
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
	HANDLE hOut;
	hOut = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute(hOut, 16*0+0);
	if(centrmode==1)
	{
		for(int i=1; i<=(120-szer)/2; i++)
		{
			cout<<" ";
		}
	}
	SetConsoleTextAttribute(hOut, 16*1+15);
	int wyw=0;
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
	SetConsoleTextAttribute(hOut, 16*1+4);
	cout<<"X";
	if(winXPmode==0)
	{
		goto winXPskip;
	}
	cout<<endl;
	SetConsoleTextAttribute(hOut, 16*0+0);
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
	SetConsoleTextAttribute(hOut, 16*7+0);
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
	SetConsoleTextAttribute(hOut, 16*0+4);
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
	SetConsoleTextAttribute(hOut, 16*7+0);
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
	SetConsoleTextAttribute(hOut, 16*6+0);
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
	SetConsoleTextAttribute(hOut, 16*7+0);
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
	SetConsoleTextAttribute(hOut, 16*0+4);
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
	SetConsoleTextAttribute(hOut, 16*7+0);
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
	cout<<endl;
	SetConsoleTextAttribute(hOut, 16*0+0);
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
	HANDLE hOut;
	hOut = GetStdHandle( STD_OUTPUT_HANDLE );
	ruchy=0;
	//GRA - PĘTLA GŁÓWNA
	for(;;)
	{
		if(ruchy==0)
		{
			system("cls");
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
				cout<<endl;
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
						bg=8;
						fg=0;
						zmiana=1;
					}
					else
					{
						bg=0;
						fg=8;
						zmiana=0;
					}
				}
				if(odkryte[i][j]==1 || odkryte[i][j]==2)
				{
					if(zmiana==0)
					{
						bg=15;
						zmiana=1;
					}
					else
					{
						bg=7;
						zmiana=0;
					}
					switch(plansza[i][j])
					{
						case 0:
							{
								fg=7;
							}
						break;
						case 1:
							{
								fg=1;
							}
						break;
						case 2:
							{
								fg=10;
							}
						break;
						case 3:
							{
								fg=4;
							}
						break;
						case 4:
							{
								fg=5;
							}
						break;
						case 5:
							{
								fg=6;
							}
						break;
						case 6:
							{
								fg=11;
							}
						break;
						case 7:
							{
								fg=0;
							}
						break;
						case 8:
							{
								fg=8;
							}
						break;
					}
				}
				if(odkryte[i][j]==2)
				{
					fg=12;
				}
				if(i==wskY && j==wskX)
				{
					bg=3;
				}
				SetConsoleTextAttribute(hOut, 16*bg+fg);
				//WYPISYWANIE PO DOKONANIU INTERPRETACJI KOLORU POLA
				if(odkryte[i][j]==1)
				{
					if(plansza[i][j]==9)
					{
						cout<<char(164);
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
					cout<<char(173);
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
			cout<<endl;
			SetConsoleTextAttribute(hOut, 16*0+0);
		}
		SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		if(winXPmode==0) 
		{
			if(centrmode==1)
			{
				for(int i=1; i<=(120-szer)/2; i++)
				{
					cout<<" ";
				}
			}
			cout<<"Pozostało:"<<flagi;
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
				cout<<"GG!\n";
				SetConsoleTextAttribute(hOut, 16*0+0);
				system("pause");
				SetConsoleTextAttribute(hOut, 16*0+7);
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
						system("cls");
						if(centrmode==1)
						{
							for(int i=1; i<=(30-(wys+2))/2; i++)
							{
								cout<<endl;
							}
						}
						windowsXP(szer, flagi, 1);
						int zmiennik=0;
						for(int i=1; i<=wys; i++)
						{
							SetConsoleTextAttribute(hOut, 16*0+0);
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
									bg=7;
									zmiennik=1;
								}
								else
								{
									bg=15;
									zmiennik=0;
								}
								switch(plansza[i][j])
								{
									case 0:
										{
											fg=7;
										}
									break;
									case 1:
										{
											fg=1;
										}
									break;
									case 2:
										{
											fg=10;
										}
									break;
									case 3:
										{
											fg=4;
										}
									break;
									case 4:
										{
											fg=5;
										}
									break;
									case 5:
										{
											fg=6;
										}
									break;
									case 6:
										{
											fg=11;
										}
									break;
									case 7:
										{
											fg=0;
										}
									break;
									case 8:
										{
											fg=8;
										}
									break;
									case 9:
										{
											fg=4;
										}
									break;
								}
								if(odkryte[i][j]==2)
								{
									fg=12;
									if(plansza[i][j]!=9)
									{
										fg=0;
									}
								}
								SetConsoleTextAttribute(hOut, 16*bg+fg);
								if(plansza[i][j]==9)
								{
									if(odkryte[i][j]==2)
									{
										cout<<"!";
									}
									else
									{
										cout<<char(164);
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
							cout<<endl;
						}
						SetConsoleTextAttribute(hOut, 16*0+7);
						if(winXPmode==0)
						{
							if(centrmode==1)
							{
								for(int j=1; j<=(120-szer)/2; j++)
								{
									cout<<" ";
								}
							}
							cout<<"DED   :("<<endl;
						} 
						if(centrmode==1)
						{
							for(int i=1; i<=(120-szer)/2; i++)
							{
								cout<<" ";
							}
						}
						SetConsoleTextAttribute(hOut, 16*0+0);
						system("pause");
						SetConsoleTextAttribute(hOut, 16*0+7);
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
						/*cout<<"wtf dlaczego stawiasz flagi na ślepo boiiii\n";
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
	cout<<endl;
}

int main()
{
	setlocale(LC_CTYPE, "Polish");	
	srand(time(NULL));
	for(;;)
	{
		system("cls");
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
					cout<<"\n";
				}
			break;
		}
		if(exitValue==1)
		{
			break;
		}
	}
}
