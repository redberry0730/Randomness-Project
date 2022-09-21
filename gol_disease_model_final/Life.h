#pragma once
#include "World.h"
class Life : public World
{
public:
	Life(int x, int y, unsigned int mode) : World(x, y, mode){}

	virtual void update_main(unsigned int mode);

	void brian_brain_update(unsigned int x, unsigned int y);
	void gol_update(unsigned int x, unsigned int y);
	void infect_update(unsigned int x, unsigned int y);
	void gol_infect_update(unsigned int x, unsigned int y);
	void gol_infect_update2(unsigned int x, unsigned int y);
	void gol_infect_update3(unsigned int x, unsigned int y);
	void gol_infect_update4(unsigned int j, unsigned int i);
	void gol_infect_update5(unsigned int j, unsigned int i);
	void glider(unsigned int , unsigned int);

};

class Counter
{
public:
	Counter(int j, int i);
	~Counter();

	void counting();
	unsigned int count;
private :
	int y;
	int x;
};
