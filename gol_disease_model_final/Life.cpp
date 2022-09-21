#include "Life.h"

Counter::Counter(int j, int i)
{
	y = j;
	x = i;
	count = 0;
}

void Life::update_main(unsigned int mode)
{

	if (true)
	{
		for (unsigned int i = 1; i <= height; i++)
		{
			for (unsigned int j = 1; j <= width; j++)
			{
				if (mode == 1)
					brian_brain_update(j, i);
				if (mode == 2)
					gol_update(j, i);
				if (mode == 3)
				{
					infect_rate = 1.0f - 0.2f;
					disease_threshold = immune_threshold + 50;
					gol_infect_update4(j, i);
				}
				if (mode == 4)
					gol_infect_update5(j, i);
				if (mode == 5)
					gol_infect_update2(j,i);

			}
		}
	}


	//if ((count % 100 == 99))
	//	//shuffle_old();
	//	shuffle_new();

	Counter(mode);
	swapGrids();
}

//void Life::test_update(unsigned int j, unsigned int i)
//{
//
//}

void Life::gol_infect_update5(unsigned int j, unsigned int i)
{
	int m = getNeighbors_disease2(j, i, 0);

	//every cell on the grid starts with a constant health_threshold
	//if cell goes into contact with a sick "cloud" in multiple generations, it be sick
	//disease stage corresponds to number from (2) to (healthy_threshold-2) of the value held a cell
	//every cell in the disease stage will decrement untill reaching immune state
	if (m == 3)
	{
		if (getLifeform(j - 1, i) > immune_threshold && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, healthy_threshold - 1);
		else if (getLifeform(j - 1, i) > immune_threshold && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, healthy_threshold - 1);
		else if (getLifeform(j + 1, i - 1) > immune_threshold && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, healthy_threshold - 1);
		else if (getLifeform(j - 1, i - 1) > immune_threshold && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, healthy_threshold - 1);
		else if (getLifeform(j + 1, i) > immune_threshold && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, healthy_threshold - 1);
		else if (getLifeform(j, i + 1) > immune_threshold && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, healthy_threshold - 1);
		else if (getLifeform(j + 1, i + 1) > immune_threshold && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, healthy_threshold - 1);
		else if (getLifeform(j - 1, i + 1) > immune_threshold && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, healthy_threshold - 1);
		
	}


	////long period exposure to disease -> sick
	if (getLifeform(j, i) < healthy_threshold && getLifeform(j, i) > immune_threshold)
	{
		setNewLife(j, i, getLifeform(j, i) - 1);
	}

	//if sick -> countdown to immune or die
	if (getLifeform(j, i) <=disease_threshold && getLifeform(j,i) > immune_threshold)
	{
		setNewLife(j, i, getLifeform(j,i) - 1);
		if (getNewLife(j, i) <= immune_threshold)
		{
			if (((float)rand() / RAND_MAX) > 0.05f)
			{
				setNewLife(j, i, healthy_threshold);
			}
			else
			{
				setNewLife(j, i, immune_threshold);
			}
		}
	}
	if ( m != 1 && m !=2 && m != 3 &&getLifeform(j, i) > disease_threshold)
	{
		setNewLife(j, i, healthy_threshold);
	}
	//immune stays immune
	if (getLifeform(j, i) == immune_threshold)
		setNewLife(j, i, immune_threshold);

}


void Life::gol_infect_update4(unsigned int j, unsigned int i)
{
	int m = getNeighbors_disease(j, i, 0);

	//neighboring sick cells spawn a sick cell in the center
	if (m == 3 && getLifeform(j, i) != 1)
	{
		if (getLifeform(j - 1, i) > 1 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, disease_threshold);
		else if (getLifeform(j - 1, i) > 1 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, disease_threshold);
		else if (getLifeform(j + 1, i - 1) > 1 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, disease_threshold);
		else if (getLifeform(j - 1, i - 1) > 1 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, disease_threshold);
		else if (getLifeform(j + 1, i) > 1 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, disease_threshold);
		else if (getLifeform(j, i + 1) > 1 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, disease_threshold);
		else if (getLifeform(j + 1, i + 1) > 1 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, disease_threshold);
		else if (getLifeform(j - 1, i + 1) > 1 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, disease_threshold);
	}

	//sick cell slowly become immune
	if (getLifeform(j, i) != 0 && getLifeform(j, i) != 1)
	{
		setNewLife(j, i, getLifeform(j, i) - 1);
		if (getNewLife(j, i) == 0) setNewLife(j, i, 1);
	}

	//immune cells stay immune
	if (getLifeform(j, i) == 1)
	{
		setNewLife(j, i, 1);
	}
}


void Life::gol_infect_update2(unsigned int j, unsigned int i)
{
	int m = getNeighbors(j, i, 0);


	if (m == 3)
	{
		if (getLifeform(j - 1, i) >1 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, healthy_threshold);
		else if (getLifeform(j - 1, i) > 1 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, healthy_threshold);
		else if (getLifeform(j + 1, i - 1) > 1 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, healthy_threshold);
		else if (getLifeform(j - 1, i - 1) > 1 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, healthy_threshold);
		else if (getLifeform(j + 1, i) > 1 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, healthy_threshold);
		else if (getLifeform(j, i + 1) > 1 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, healthy_threshold);
		else if (getLifeform(j + 1, i + 1) > 1 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, healthy_threshold);
		else if (getLifeform(j - 1, i + 1) > 1 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, healthy_threshold);
		else setNewLife(j, i, 1);
	}


	if (m == 2)
	{
		if (getLifeform(j, i) != 0)
		{
			if ((float)rand() / RAND_MAX > infect_rate)
				setNewLife(j, i, healthy_threshold);
			else
				setNewLife(j, i, getLifeform(j, i));

		}
		else setNewLife(j, i, getLifeform(j, i));
	}

	//recovering rule
	if (getLifeform(j, i) != 0 && getLifeform(j, i) > 2)
	{
		setNewLife(j, i, getLifeform(j, i) - 2);
		if(getLifeform(j,i) == 0) setNewLife(j,i, 1);
	}

	if (m != 2 && m != 3)
	{
		setNewLife(j, i, 0);
	}
}

void Life::gol_infect_update(unsigned int j, unsigned int i)
{
	int m = getNeighbors(j, i, 0);

	if (m == 3)
	{
		
		if (getLifeform(j - 1, i) == 2 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, 2);
		else if (getLifeform(j - 1, i) == 2 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, 2);
		else if (getLifeform(j + 1, i - 1) == 2 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, 2);
		else if (getLifeform(j - 1, i - 1) == 2 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, 2);
		else if (getLifeform(j + 1, i) == 2 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, 2);
		else if (getLifeform(j, i + 1) == 2 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, 2);
		else if (getLifeform(j + 1, i + 1) == 2 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, 2);
		else if (getLifeform(j - 1, i + 1) == 2 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, 2);
		else setNewLife(j, i, 1);
	}

	if (m == 2)
	{
		if (getLifeform(j,i) == 1)
		{
			if ((float)rand() / RAND_MAX > infect_rate)
				setNewLife(j, i, 2);
			else
				setNewLife(j, i, getLifeform(j,  i));

		}
		else setNewLife(j, i, getLifeform(j, i));
	}
	if (m != 2 && m != 3)
	{
		setNewLife(j, i ,0);
	}
}


void Life::infect_update(unsigned int j, unsigned int i)
{

	float a = (float)rand() / RAND_MAX;
	if (a < 0.25f) setLife(i, j + 1, 1);
	if (a >= 0.25f && a < 0.5f) setLife(i + 1, j, 0);
	if (a >= 0.5f && a < 0.75f) setLife(i, j - 1, 1);
	if (a >= 0.75f) setLife(i - 1, j, 0);

	if (getLifeform(i - 1, j) == 2 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, 2);
	else if (getLifeform(i - 1, j) == 2 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, 2);
	else if (getLifeform(i + 1, j - 1) == 2 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, 2);
	else if (getLifeform(i - 1, j - 1) == 2 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, 2);
	else if (getLifeform(i + 1, j) == 2 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, 2);
	else if (getLifeform(i, j + 1) == 2 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, 2);
	else if (getLifeform(i + 1, j + 1) == 2 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, 2);
	else if (getLifeform(i - 1, j + 1) == 2 && (((float)rand() / RAND_MAX) > infect_rate)) setNewLife(j, i, 2);
	else setNewLife(j, i, 1);

}

void Life::brian_brain_update(unsigned int j, unsigned int i)
{
	int m = brian_getNeighbors(j, i);

	if (m == 2 && getLifeform(j, i) == 0)
	{
		setNewLife(j, i, 1);
	}
	else if (getLifeform(j, i) == 1)
	{
		setNewLife(j, i, 2);
	}
	else if (getLifeform(i, j) == 2)
	{
		setNewLife(j, i, 0);
	}
	else setNewLife(j, i, 0);


}

void Life::gol_update(unsigned int j, unsigned int i)
{
	int m = fast_getNeighbors(j, i, 0);

	if (m == 3)
	{
		setNewLife(j, i, 1);
	}
	if (m == 2)
	{
		setNewLife(j, i, getLifeform(j, i));
	}

	if (m != 3 && m != 2)
	{
		setNewLife(j, i, 0);
	}
}

void Life::glider(unsigned int x, unsigned int y)
{
	setLife(x + 41, y + 13, 1);
	setLife(x + 41, y + 14, 1);
	setLife(x + 42, y + 13, 1);
	setLife(x + 42, y + 14, 1);
	setLife(x + 50, y + 14, 1);
	setLife(x + 51, y + 13, 1);
	setLife(x + 51, y + 14, 1);
	setLife(x + 51, y + 15, 1);
	setLife(x + 52, y + 12, 1);
	setLife(x + 52, y + 13, 1);
	setLife(x + 52, y + 14, 1);
	setLife(x + 52, y + 15, 1);
	setLife(x + 52, y + 16, 1);
	setLife(x + 53, y + 11, 1);
	setLife(x + 53, y + 12, 1);
	setLife(x + 53, y + 16, 1);
	setLife(x + 53, y + 17, 1);
	setLife(x + 57, y + 13, 1);
	setLife(x + 57, y + 14, 1);
	setLife(x + 57, y + 15, 1);
	setLife(x + 58, y + 13, 1);
	setLife(x + 58, y + 14, 1);
	setLife(x + 58, y + 15, 1);
	setLife(x + 60, y + 12, 1);
	setLife(x + 61, y + 11, 1);
	setLife(x + 61, y + 13, 1);
	setLife(x + 62, y + 10, 1);
	setLife(x + 62, y + 14, 1);
	setLife(x + 63, y + 11, 1);
	setLife(x + 63, y + 12, 1);
	setLife(x + 63, y + 13, 1);
	setLife(x + 64, y + 9, 1);
	setLife(x + 64, y + 10, 1);
	setLife(x + 64, y + 14, 1);
	setLife(x + 64, y + 15, 1);
	setLife(x + 75, y + 11, 1);
	setLife(x + 75, y + 12, 1);
	setLife(x + 76, y + 11, 1);
	setLife(x + 76, y + 12, 1);
	setLife(x + 109,y + 104, 1);
	setLife(x + 109,y + 105, 1);
	//setLife(x + 130,y + 104, 1);
	//setLife(x + 130,y + 105, 1);
	//setLife(x + 140,y + 103, 1);

}

