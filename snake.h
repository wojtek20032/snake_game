#pragma once
#include "winsys.h"
#include <list>
enum dir { LEFT, RIGHT, UP, DOWN };
using namespace std;
class Snake : public CFramedWindow {

public:

	int length;
	bool start;
	int games_on;
	int eaten;
	bool alive;
	list<CPoint> body;
	int** tab;
	bool toggle;
	CPoint head;
	CPoint tail;
	dir dir_;
	int level;
    Snake(CRect r, char _c = ' '): CFramedWindow(r, _c){
		start = true;
		alive = true;
		length = 0;
		level = 1;
		eaten = 0;
		toggle = false;
		head.x = 5;
		head.y = 5;
		tail.x = 3;
		tail.y = 5;
		body.push_back(head);
		body.push_back(CPoint(4, 5));
		body.push_back(tail);
		games_on = 0;
		dir_ = RIGHT;
		tab = (int**)calloc(geom.size.x, sizeof(int*));
		for (int j = 0; j < geom.size.x; j++) {
			tab[j] = (int*)calloc(geom.size.y, sizeof(int));
		}
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
		}
    ~Snake();
    void restart_game();
    void move_snake(dir d);
    void spawn_apple();
    void paint();
    void grow();
    bool handleEvent(int key);
    bool auto_move();
  
};

