#include "World.h"


World::World(int w, int h, unsigned int mode)
{
	width = w;
	height = h;
	grid = (short*)malloc((width + 2) * (height + 2) * sizeof(short));
	new_grid = (short*)malloc((width + 2) * (height + 2) * sizeof(short));
	check_grid = (short*)malloc((width + 2) * (height + 2) * sizeof(short));

	grid_ptr = &grid;
	new_grid_ptr = &new_grid;

	if (mode == 4)
	{
		for (unsigned int i = 0; i < (width + 2) * (height + 2); i++)
		{
			grid[i] = healthy_threshold;
			new_grid[i] = healthy_threshold;
			check_grid[i] = healthy_threshold;

		}
	}
	else
	{
		for (unsigned int i = 0; i < (width + 2) * (height + 2); i++)
		{
			grid[i] = 0;
			new_grid[i] = 0;
			check_grid[i] = 0;
		}
	}

}

World::~World() {
	free(grid); free(new_grid); free(check_grid);
}

int World::getNewLife(int x, int y)
{
	return new_grid[x * (width + 2) + y];
}

void World::setNewLife(int x, int y, int val)
{
	new_grid[x * (width + 2) + y] = val;
}

void World::swapGrids()
{
	short* temp = *grid_ptr;
	*grid_ptr = *new_grid_ptr;
	*new_grid_ptr = temp;

}

int World::getNeighbors(int x, int y, int val)
{
	int count = 0;

	count += (grid[(x - 1) * (width + 2) + (y)] != 0);
	count += (grid[(x) * (width + 2) + (y - 1)] != 0);
	count += (grid[(x - 1) * (width + 2) + (y - 1)] !=0);
	count += (grid[(x + 1) * (width + 2) + (y)]!= 0);

	count += (grid[(x) * (width + 2) + (y + 1)]!= 0);
	count += (grid[(x + 1) * (width + 2) + (y + 1)]!= 0);
	count += (grid[(x + 1) * (width + 2) + (y - 1)]!= 0);
	count += (grid[(x - 1) * (width + 2) + (y + 1)]!= 0);

	return count;
}
int World::getNeighbors_disease(int x, int y, int val)
{
	int count = 0;

	count += ((grid[(x - 1) * (width + 2) + (y)] >1));
	count += ((grid[(x) * (width + 2) + (y - 1)] > 1));
	count += ((grid[(x - 1) * (width + 2) + (y - 1)]> 1));
	count += ((grid[(x + 1) * (width + 2) + (y)] > 1));

	count += ((grid[(x) * (width + 2) + (y + 1)] > 1));
	count += ((grid[(x + 1) * (width + 2) + (y + 1)] > 1));
	count += ((grid[(x + 1) * (width + 2) + (y - 1)] > 1));
	count += ((grid[(x - 1) * (width + 2) + (y + 1)] > 1));

	return count;
}

int World::getNeighbors_disease2(int x, int y, int val)
{

	int count = 0;

	count += (grid[(x - 1) * (width + 2) + (y)] > immune_threshold) && (grid[(x - 1) * (width + 2) + (y)] < healthy_threshold);
	count += (grid[(x) * (width + 2) + (y - 1)] > immune_threshold) && (grid[(x) * (width + 2) + (y - 1)] < healthy_threshold);
	count += (grid[(x - 1) * (width + 2) + (y - 1)] > immune_threshold)&& (grid[(x - 1) * (width + 2) + (y - 1)] < healthy_threshold);
	count += (grid[(x + 1) * (width + 2) + (y)] > immune_threshold)&& (grid[(x + 1) * (width + 2) + (y)] < healthy_threshold);

	count += (grid[(x) * (width + 2) + (y + 1)] > immune_threshold)&& (grid[(x) * (width + 2) + (y + 1)] < healthy_threshold);
	count += (grid[(x + 1) * (width + 2) + (y + 1)] > immune_threshold)&& (grid[(x + 1) * (width + 2) + (y + 1)] < healthy_threshold);
	count += (grid[(x + 1) * (width + 2) + (y - 1)] > immune_threshold)&& (grid[(x + 1) * (width + 2) + (y - 1)] < healthy_threshold);
	count += (grid[(x - 1) * (width + 2) + (y + 1)] > immune_threshold)&& (grid[(x - 1) * (width + 2) + (y + 1)] < healthy_threshold);

	return count;
}


int World::fast_getNeighbors(int x, int y, int val)
{
	int count = 0;
	count +=  grid[(x - 1) * (width + 2) + (y)];
	count +=  grid[(x) * (width + 2) + (y - 1)] ;
	count +=  grid[(x - 1) * (width + 2) + (y - 1)];
	count +=  grid[(x + 1) * (width + 2) + (y)];

	count +=  grid[(x) * (width + 2) + (y + 1)];
	count +=  grid[(x + 1) * (width + 2) + (y + 1)];
	count +=  grid[(x + 1) * (width + 2) + (y - 1)];
	count +=  grid[(x - 1) * (width + 2) + (y + 1)];
	return count;
}

int World::brian_getNeighbors(int x, int y)
{
	int count = 0;
	count += grid[(x - 1) * (width + 2) + (y)] % 2;
	count += grid[(x) * (width + 2) + (y - 1)] % 2;
	count += grid[(x - 1) * (width + 2) + (y - 1)] % 2;
	count += grid[(x + 1) * (width + 2) + (y)] % 2;

	count += grid[(x) * (width + 2) + (y + 1)] % 2;
	count += grid[(x + 1) * (width + 2) + (y + 1)] % 2;
	count += grid[(x + 1) * (width + 2) + (y - 1)] % 2;
	count += grid[(x - 1) * (width + 2) + (y + 1)] % 2;
	return count;
}


int World::getLifeform(int x, int y)
{
	return grid[x * (width + 2) + y];
}

void World::setLife(int x, int y, int val)
{
	grid[x * (width + 2) + y] = val;
}

void World::print_grid()
{
	for (unsigned int i = 1; i <= height; i++)
	{
		cout << endl;
		for (unsigned int j = 1; j <= width; j++)
		{
			cout << check_grid[i * (width + 2) + j] << " ";
		}
	}
	cout << endl;

}

void World::copy_grid()
{
	for (unsigned int i = 1; i <= height; i++)
	{

		for (unsigned int j = 1; j <= width; j++)
		{
			check_grid[i * (width + 2) + j] = grid[i * (width + 2) + j];
		}
	}
}

bool World::check(short* grid, short* check_grid)
{
	for (int i = 0; i < (width + 2) * (height + 2); i++)
	{
		if (check_grid[i] != grid[i]) return false;
	}
	return true;
	
}

void World::stabilize()
{
	if (count % 10 == 0)
	{
		copy_grid();
		//std::cout << "copy" << std::endl;
		//std::cout << count << std::endl;
		//print();
	}

	if (check(new_grid, check_grid) == true && count_bool == true) {
		std::cout << "stabilized after: " << count << " generations" << std::endl;
		count_bool = false;
	}


}

void World::clear()
{
	for (unsigned int i = 1; i <= height; i++)
	{
		for (unsigned int j = 1; j <= width; j++)
		{
			grid[i * (width + 2) + j] = 0;
		}
	}
}

void World::shuffle_new()
{
	for (int i = 0; i < (width + 2) * (height + 2); i++) {
		int r = i + (rand() % (((width + 2) * (height + 2)) - i));
		short temp = new_grid[i]; 
		new_grid[i] = new_grid[r]; 
		new_grid[r] = temp; 
	}
}
void World::shuffle_old()
{
	for (int i = 0; i < (width + 2) * (height + 2); i++) {
		int r = i + (rand() % (((width + 2) * (height + 2)) - i));
		short temp = grid[i];
		grid[i] = grid[r];
		grid[r] = temp;
	}
}

void World::disease(unsigned int a)
{
	for (int i = 0; i < a; i++)
	{
		int x = rand() % (width + 1);
		int y = rand() % (height + 1);
		if(getLifeform(x,y) != 0)setLife(x, y, a);
	}
}

unsigned int World::count_immune(unsigned int mode)
{
	int count = 0;
	if (mode == 4)
	{
		for (unsigned int i = 1; i <= height; i++)
		{
			for (unsigned int j = 1; j <= width; j++)
			{
				if (getLifeform(j, i) == immune_threshold) count++;
			}
		}
	}
	else
	{
		for (unsigned int i = 1; i <= height; i++)
		{
			for (unsigned int j = 1; j <= width; j++)
			{
				if (getLifeform(j, i) == 1) count++;
			}
		}
	}
	return count;
}

unsigned int World::count_sick(unsigned int mode)
{
	int count = 0;
	if (mode == 4)
	{
		for (unsigned int i = 1; i <= height; i++)
		{
			for (unsigned int j = 1; j <= width; j++)
			{
				if (getLifeform(j, i) <= disease_threshold && getLifeform(j, i) > immune_threshold) count++;
			}
		}
	}
	else
	{
		for (unsigned int i = 1; i <= height; i++)
		{
			for (unsigned int j = 1; j <= width; j++)
			{
				if (getLifeform(j, i) <= disease_threshold && getLifeform(j,i) > immune_threshold) count++;
			}
		}
	}
	return count;
}

unsigned int World::count_susceptible(unsigned int mode)
{
	int count = 0;
	if (mode == 4)
	{
		for (unsigned int i = 1; i <= height; i++)
		{
			for (unsigned int j = 1; j <= width; j++)
			{
				if (getLifeform(j, i) > disease_threshold) count++;
			}
		}
	}
	if (mode == 3)
	{
		for (unsigned int i = 1; i <= height; i++)
		{
			for (unsigned int j = 1; j <= width; j++)
			{
				if (getLifeform(j, i) ==0 ) count++;
			}
		}
	}
	return count;

}

void World::record_data(unsigned int* data, unsigned int offset, unsigned int mode)
{
	data[offset] = count_susceptible(mode);
	data[offset + 1] = count_sick(mode);
	data[offset + 2] = count_immune(mode);
}


void World::Counter(unsigned int mode)
{
	stabilize();
	count++;
	if (count % 2 == 0 && offset/3 < 1000 && offset < (sizeof(data)/ sizeof(unsigned int)))
	{
		record_data(data, offset, mode);
		offset += 3;

		if(count % 6 == 0)
		{
			calc_deriv();
			float i = calc_beta(mode);
			//std::cout << i << std::endl;
		}
		
	}
}

void World::export_data()
{
	std::ofstream myfile("coordinates.txt");

	if (myfile.is_open())
	{
		myfile << "total population = " << width*height << std::endl;
		myfile << "  S    " << "I    " << "R    " << std::endl;
		for (int i = 0; i < (sizeof(data)/sizeof(unsigned int) ) +3; i += 3)
		{
			myfile << data[i] << ", " << data[i + 1] << ", " << data[i + 2] << std::endl;
		}
		myfile << "lines recored: " << (offset) / 3 << endl;
	}

	myfile.close();
}

void World::calc_deriv()
{
	std::cout << "ds/dt,   " << "di/dt,    " << "dr/dt      " << std::endl;
	
	float s_change = 0.0f;
	float i_change= 0.0f;
	float r_change = 0.0f;


	r_change = int(data[offset - 1] - data[offset - 4]);
	i_change = int(data[offset - 2] - data[offset - 5]);
	s_change = int(data[offset - 3] - data[offset - 6]);
		

	//std::cout << data[offset - 4] << ", " << data[offset - 5] << ", " << data[offset - 6] << std::endl;
	//std::cout << data[offset - 1] << ", " << data[offset - 2] << ", " << data[offset - 3] << std::endl << std::endl;
	std::cout << s_change << ", " << i_change << ", " << r_change  << std::endl;

}

float World::calc_beta(unsigned int mode)
{
	int S = count_susceptible(mode);
	int N = width * width;
	int I = count_sick(mode);
	int beta = 3;

	float probability = ((float)(beta) * S * I) / (float)(N * N);

	//std::cout << (float)(-beta * S*I)/(N*N)<< std::endl;
	return probability;

}

float World::calc_gamma(unsigned int mode)
{
	return 0;
}