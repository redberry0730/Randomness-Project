#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include<fstream>

using std::malloc;
using std::cout;
using std::endl;

#ifndef _WORLD_H
#define _WORLD_H

class World
{
protected:
	short** grid_ptr;
	short** new_grid_ptr;
	

	short* grid;
	short* new_grid;
	short* check_grid;

	unsigned int width;
	unsigned int height;

	int getNewLife(int x, int y);
	void setNewLife(int x, int y, int val);
	void swapGrids();

public:
	World(int, int, unsigned int);
	~World();

	int getNeighbors(int, int, int);
	int getNeighbors_disease(int, int, int);
	int getNeighbors_disease2(int x, int y, int val);


	int fast_getNeighbors(int, int, int);
	int brian_getNeighbors(int, int);
	int getNeighbors2(int, int);

	int getLifeform(int x, int y);
	void setLife(int x, int y, int val);
	virtual void update_main(){ }
	

	void print();
	bool check(short*grid, short*check_grid);
	void copy_grid();

	void stabilize();
	void print_grid();
	void clear();
	void shuffle_new();
	void shuffle_old();

	void disease(unsigned int a);

	unsigned int count_immune(unsigned int mode);
	unsigned int count_sick(unsigned int mode);

	unsigned int count_susceptible(unsigned int mode);

	void Counter(unsigned int mode);
	void record_data(unsigned int* data, unsigned int size, unsigned int mode);
	void export_data();

	void calc_deriv();
	float calc_gamma(unsigned int );
	float calc_beta(unsigned int);

	unsigned int count;
	bool count_bool = true;
	float infect_rate = 1.0f - 0.2f;

	unsigned int immune_threshold = 2;
	unsigned int disease_threshold = immune_threshold + 40;
	unsigned int healthy_threshold = disease_threshold + 3;


	unsigned int data[3000];
	unsigned int offset = 0;
};

#endif
