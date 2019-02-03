#include "../include/Being.h"

int main()
{
	initscr();
	cbreak();
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK); 
	init_pair(5, COLOR_CYAN, COLOR_BLACK);

	WINDOW * win = newwin(10, 20, 10, 10);
	refresh();

	//box(win, 0, 0);
	
	Player load("Name", "Class", 0, 0, 0, 0, 0, 0);
	int input = 0;
	while (input != '9') 
	{
		clear();
		refresh();
		printw("\n");
		printw("                _         []|                        |[]\n");
		printw("      _       /   \\         |        I~~~~~~~I       |               \n");
		printw("    /   \\ _ /      \\ _      /\\   I^^^^^^^^^^^^^^^I   /\\               \n");
		printw("  /         \\          \\   /__\\__I O  O  O  O  O I__/__\\             \n");
		printw("/ \\                      \\ I     I               I     I             \n");
		printw("                           I     I               I     I               \n");
		printw("            [^^^]          I  [^^^]             [^^^]  I          [^^^]\n");
		printw("            [ o ]-------------[ o ]-------------[ o ]-------------[ o ]\n");
		printw("            [   ]             [   ]     ___     [   ]             [   ]\n");
		printw("            [   ]             [   ]    / | \\    [   ]             [   ]\n");
		printw("            [   ]             [   ]   |--|--|   [   ]             [   ]\n");
		printw("            [   ]             [   ]   |--|--|   [   ]             [   ]\n");
		printw("____________[___]_____________[___]___|--|--|___[___]_____________[___]_________\n\n");
		//SetConsoleTitle("The Scions of Channeling");
		attron(COLOR_PAIR(5));
		printw("\t\t\t      The Scions of Channeling\n\n");
		attroff(COLOR_PAIR(5));
		printw("\t\t\t\t    1: New game\n");
		printw("\t\t\t\t    2: Load    \n");
		printw("\t\t\t\t    8: Credits \n");
		printw("\t\t\t\t    9: Exit    \n");
		printw("\t\t\t\t    >");
		input = getch();

		if (input == '1')
			Intro();

		if (input == '2')
		{
			load.Reset();
			if (Load(&load))
			{
				if (load.levelGet() >= 1)
				{
					load.viewStatus();
					Tyria(&load);
				}
				else
					PausedString("Not a valid save.");
			}
		}

		if (input == '8')
		{
			clear();
			printw("\nCredits", '-');
			printw("\n");
			printw("\nMain Developer:");
			printw("\nTheCyberMonk\n");
			printw("\nWorld Building:");
			printw("\nTheCyberMonk");
			printw("\nAyatoma\n");
			printw("\nPlay Testing:");
			printw("\nAyatoma");
			printw("\nStephen Bonnefoy\n\n\n");
			Pause();
		}
		if (input == '9')
		{
			load.yPosSet(22);
			Paragraph(&load, "Thanks for playing!", false, false, false, 39);
			SleepC(2000);
		}
	}
	endwin();
	return 0;
}