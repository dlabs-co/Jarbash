
/*! \file main.cpp
 *  \brief Jarbash main file
 */

#include <locale.h>
#include <panel.h>
#include <cdk.h>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cmath>
#include <unistd.h>

#include "http.h"

using namespace std;

/*! \fn void printBanner(WINDOW *win, std::ifstream &file)
 *  \brief Function to print a banner in form of a figlet.
 *
 *  \param *win Pointer to the window where to print the banner.
 *  \param &file File from where to read the banner.
 */

void printBanner(WINDOW *win, std::ifstream &file);
void wsystem(WINDOW *win, char* command);

int main()
{	
	std::ifstream banner("banner", std::ifstream::in);

	std::ifstream jarbash("jarbash.txt", std::ifstream::in);

	WINDOW *wins[4];
	PANEL  *panels[4];
	CDKSCREEN *scr1;
	int lines = 25, cols = 100, y = 1, x = 1;
	// cambiar lines y cols por LINES y COLS (verificando si funciona)
	// recordar verificar las proporciones
	// #defines para espacios entre ventanas y esas cosas
	// COLS = es el numero de columnas de caracteres en la pantalla (en horizontal)
	// LINES = es el numero de lineas que tiene la pantalla (en vertical)
	
	//setlocale(LC_ALL, "");
	initscr();
	start_color();
	cbreak();
	noecho();
	curs_set(0);

	init_color(COLOR_YELLOW, 176, 176, 176);
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_BLUE, COLOR_BLUE);


	wins[0] = newwin(round(LINES/2)-2, round(COLS/2), y, x);
	wins[1] = newwin(round(LINES/2)-1, round(COLS/2),  round(LINES/2), x);
	wins[2] = newwin(round(LINES/1)-2, round(COLS/3), y, x + round(COLS/2) + 2);
	
	
	scr1 = initCDKScreen(wins[2]);
		
	wbkgd(stdscr, COLOR_PAIR(2));

	for(int i = 0; i < 3; ++i)
	{
		wbkgd(wins[i], COLOR_PAIR(1));
		box(wins[i], 0, 0);
	}

	panels[0] = new_panel(wins[0]);
	panels[1] = new_panel(wins[1]);
	panels[2] = new_panel(wins[2]);

	if(banner.good()) printBanner(wins[0], banner); // verifica que el banner existe (fichero)
	std::string asd = test();
	std::cout << asd << std::endl;
	
	for(;;)
	{
		usleep(200000);
		wprintw(wins[1], asd.c_str());
		box(wins[1], 0, 0);
		update_panels();
		refreshCDKScreen(scr1);
		doupdate();
	}
	endwin();
}


void printBanner(WINDOW *win, std::ifstream &file)
{

	int b = 3;
	wmove(win, 3, 3);
	
	while(!file.eof()){
	
		if(file.peek() == '\n')
		{		
			file.get();
			b++;
			wmove(win, b, 3);
			waddch(win, file.get());
		}
		//else if(file.peek() == EOF)
		//{
		//	box(win, 0, 0);
		//}
		else
		{
			waddch(win, file.get());
		}
	}

	mvwaddstr(win, b, 3, "  ");

}

void wsystem(WINDOW *win, char* command)
{
	werase(win);
	box(win, 0, 0);
	FILE *in;
	char buf[2048];
	//if(!(in = popen("mpstat -I SUM -P ON | sed 's/\_.*//g'", "r")))
	if(!(in = popen(command,"r")))
	{
		exit(1);
	}
	
	int i = 2;
	wmove(win, 1, 1);
	
	while(!feof(in))
	{
		char c = fgetc(in);
		if(c != EOF)
		{
			if(c == '\n')
			{	
				wmove(win,i, 3);
				i++;
			}
			else
			{
				waddch(win, c);
			}
		}
	}

	pclose(in);


}

std::string vsystem(std::string command, int buf_lenght=100)
{
	FILE *in;	

	if(!(in = popen(command.c_str(),"r")))
	{
		exit(1);
	}

	

}
