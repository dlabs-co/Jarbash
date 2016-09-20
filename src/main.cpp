
/*! \file main.cpp
 *  \brief Jarbash main file
 */



#include <panel.h>
#include <cdk/cdk.h>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <thread>

using namespace std;

/*! \fn void printBanner(WINDOW *win, std::ifstream &file)
 *  \brief Function to print a banner in form of a figlet.
 *
 *  \param *win Pointer to the window where to print the banner.
 *  \param &file File from where to read the banner.
 */

void printBanner(WINDOW *win, std::ifstream &file);
void wsystem(WINDOW *win);

void test()
{
	cout << "Hola" << endl;
}

int main()
{	
	std::ifstream banner("test.txt", std::ifstream::in);
	bool b_exists = false;
	if(banner.good())
	{
		b_exists = true;
	}

	WINDOW *wins[4];
	PANEL  *panels[4];
	CDKSCREEN *scr1;
	int lines = 25, cols = 100, y = 2, x = 4;
	
	initscr();
	start_color();
	cbreak();
	noecho();
	
	init_color(COLOR_YELLOW, 176, 176, 176);
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_BLUE, COLOR_BLUE);


	wins[0] = newwin(lines, 100, y, x);
	wins[1] = newwin(lines, cols, y + lines+1, x);
	wins[2] = newwin((lines*2)+1, 70, y, x + cols+1);
	
	
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

	for(;;)
	{
		wattron(wins[0], COLOR_PAIR(1));
		doupdate();
		attron(A_BOLD);
		
		if(b_exists) printBanner(wins[0], banner);
		
		wsystem(my_wins[1]);	
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
		else
		{
			waddch(win, file.get());
		}
	}

	mvwaddch(win,b, 3, ' ');
}

void wsystem(WINDOW *win)
{
	FILE *in;
	char buf[512];
	if(!(in = popen("ls -l", "r")))
	{
		exit(1);
	}
	
	int i = 2;
	wmove(win, 1, 3);
	
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
