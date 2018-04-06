#include <cstdlib>
#include <ctime>

int randomgen(int min, int max)
{
	srand(time(0));
	return (rand()%max + min);
}
