/* snake.cpp */
#include "snake.h"
#include <cstdlib>
#include <ctime>
#include <unistd.h>

Snake::~Snake()
{
	for (int i = 0; i < geom.size.x; i++) {

		delete[] tab[i];
	}
	delete[] tab;
};
void Snake::move_snake(dir d)
{
	if (d == RIGHT) {
		if (head.x == geom.size.x - 2) {

			head.x = 1;
		}
		else {
			head.x = head.x + 1;
		}
		for (auto it = body.begin(); it != body.end(); ++it) {
			if (it != body.begin() && head.x == it->x && head.y == it->y) {
				alive = false;
				return;
			}
		}
		body.push_back(CPoint(head.x, head.y));
	}
	else if (d == LEFT) {
		if (head.x == 1) {
			head.x = geom.size.x - 2;
		}
		else {
			head.x = head.x - 1;
		}
		for (auto it = body.begin(); it != body.end(); ++it) {
			if (it != body.begin() && head.x == it->x && head.y == it->y) {
				alive = false;
				return;
			}
		}
		body.push_back(CPoint(head.x, head.y));
	}
	else if (d == UP) {
		if (head.y == 1) {
			head.y = geom.size.y - 2;
		}
		else {
			head.y -= 1;
		}
		for (auto it = body.begin(); it != body.end(); ++it) {
			if (it != body.begin() && head.x == it->x && head.y == it->y) {
				alive = false;
				return;
			}
		}
		body.push_back(CPoint(head.x, head.y));
	}
	else {
		if (head.y == geom.size.y - 2) {
			head.y = 1;
		}
		else {
			head.y += 1;
		}
		for (auto it = body.begin(); it != body.end(); ++it) {
			if (it != body.begin() && head.x == it->x && head.y == it->y) {
				alive = false;
				return;
			}
		}
		body.push_back(CPoint(head.x, head.y));
	}

	body.pop_front();
	tail.x = body.front().x;
	tail.y = body.front().y;
};
void Snake::spawn_apple()
{
	int x = rand() % (geom.size.x - 1);
	int y = rand() % (geom.size.y - 1);
	this->tab[x][y] = 2;
};
void Snake::paint()
{
	CFramedWindow::paint();

	if (alive == false) {
		gotoyx(geom.topleft.y, geom.topleft.x);
		for (int i = 1; i < geom.size.x - 1; i++) {
			for (int j = 1; j < geom.size.y - 1; j++) {
				gotoyx(geom.topleft.y + j, geom.topleft.x + i);
				if (tab[i][j] == 2) {
					printw("o");
				}
				else {
					printw(" ");
				}
			}
		}
		for (CPoint i : body) {
			gotoyx(geom.topleft.y + i.y, geom.topleft.x + i.x);
			if (head.x == i.x && head.y == i.y) {
				printw("*");
			}
			else {
				printw("x");
			}
		}
		gotoyx(geom.topleft.y + 1, geom.topleft.x + 4);
		printw("GAME OVER!! YOUR SCORE %d", length);
	}
	else {
		gotoyx(geom.topleft.y - 2, geom.topleft.x);
		printw("+");
		for (int i = 0; i < 7; i++) {
			printw("-");
		}
		printw("+");
		if (games_on == 0) {
			gotoyx(geom.topleft.y - 1, geom.topleft.x);
			printw("|LEVEL %d|", length);
			gotoyx(geom.topleft.y + 1, geom.topleft.x + 4);
			printw("PAUSED PRESS i TO UNTOGGLE INFO");
			if (toggle == false) {
				gotoyx(geom.topleft.y, geom.topleft.x);
				gotoyx(geom.topleft.y + 4, geom.topleft.x + 1);
				printw("i - toggle help information");
				gotoyx(geom.topleft.y + 6, geom.topleft.x + 1);
				printw("p - pause/play");
				gotoyx(geom.topleft.y + 8, geom.topleft.x + 1);
				printw("r - restart game");
				gotoyx(geom.topleft.y + 10, geom.topleft.x + 1);
				printw("arrows - move snake");
			}
		}
		else {
			gotoyx(geom.topleft.y - 1, geom.topleft.x);
			printw("|LEVEL %d|", length);
			gotoyx(geom.topleft.y, geom.topleft.x);

			for (int i = 1; i < geom.size.x - 1; i++) {
				for (int j = 1; j < geom.size.y - 1; j++) {
					gotoyx(geom.topleft.y + j, geom.topleft.x + i);
					if (tab[i][j] == 2) {
						printw("o");
					}
					else {
						printw(" ");
					}
				}
			}
			for (CPoint i : body) {
				gotoyx(geom.topleft.y + i.y, geom.topleft.x + i.x);
				if (head.x == i.x && head.y == i.y) {
					printw("*");
				}
				else {
					printw("x");
				}
			}
			if (start) {
				spawn_apple();
				start = false;
			}
			if (eaten) {
				spawn_apple();
				eaten = 0;
			}
		}
	}
};
void Snake::grow()
{
	if (tab[head.x][head.y] == 2) {
		tab[head.x][head.y] = 0;
		if (tail.x == 1) {
			tail.x = geom.size.x - 2;
			body.push_front(CPoint(tail.x, tail.y));
		}
		body.push_front(CPoint(tail.x - 1, tail.y));

		this->length++;
		eaten = 1;
	}
}
void Snake::restart_game()
{
	for (int i = 0; i < geom.size.x; i++) {
		for (int j = 0; j < geom.size.y; j++) {
			if (i == 5 && j == 5) {
				tab[i][j] = 3;
				tab[i - 1][j] = 1;
				tab[i - 2][j] = 1;
			}
			else {
				tab[i][j] = 0;
			}
		}
	}
	body.clear();
	head.x = 5;
	head.y = 5;
	tail.x = 3;
	tail.y = 5;
	body.push_back(head);
	body.push_back(CPoint(4, 5));
	body.push_back(tail);
	level = 1;
	games_on = 1;
	eaten = 1;
	length = 2;
	alive = true;
}
bool Snake::handleEvent(int key)
{	
	
	if (games_on && alive == true) {
		
		switch (key) {

		case KEY_UP:
			grow();
			if (dir_ == DOWN) {
				return false;
			}
			move_snake(UP);
			dir_ = UP;
			return true;
		case KEY_DOWN:
			grow();
			if (dir_ == UP) {
				return false;
			}
			move_snake(DOWN);
			dir_ = DOWN;
			return true;
		case KEY_RIGHT:
			grow();
			if (dir_ == LEFT) {
				return false;
			}
			move_snake(RIGHT);
			dir_ = RIGHT;
			return true;
		case KEY_LEFT:
			grow();
			if (dir_ == RIGHT) {
				return false;
			}
			move_snake(LEFT);
			dir_ = LEFT;
			return true;
		case 'p':
			games_on = 0;
			return true;
		
		case -69:
			grow();
			move_snake(dir_);
			return true;
		}
	}

	else {
		if (CFramedWindow::handleEvent(key)) {
			return true;
		}
		switch (key) {
		case 'r':
			restart_game();

			return true;
		case 'i':
			if (toggle == true) {
				toggle = false;
			}
			else {
				toggle = true;
			}

			return true;

		case 'p': 
			games_on = 1;
			return true;
		}
	}
	return false;
};
int main()
{
	CDesktop d;
	Snake* snake = new Snake(CRect(CPoint(26, 4), CPoint(40, 20)));
	d.insert(snake);
	d.insert(new CWindow(CRect(CPoint(2,3), CPoint(20,10)), '#'));
	d.insert(new CInputLine(CRect(CPoint(5,7), CPoint(15,15))));
	d.run();
	return 0;
}
