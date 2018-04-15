#include <face_tracker.h>
#include <time.h>
#include <iostream>

static double diffclock(clock_t clock1, clock_t clock2)
{
	double diffticks = clock2 - clock1;
	double diffms = diffticks / CLOCKS_PER_SEC;
	return diffms;
}

int main(void)
{	

	ftInit();
	int i = 0;
	
	while (i < 60)
	{
		clock_t start_t = clock();
		ftTrack();
		clock_t end_t = clock();

		std::cout << i << ": \n";
		std::cout << "\t" << ftGetX() << ", " << ftGetY() << std::endl;
		std::cout << "\telapsed: " << diffclock(start_t, end_t) << "s" << "\n\n";

		if (ftIsSmiling())
		{
			std::cout << "\t=======\n\tSMILING\n\t===========\n";
		}

		i++;
	}
	ftTerminate();
	return 0;
}