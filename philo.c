#include "philo.h"

int main(int argc, char *argv[])
{
	t_monitor	monitor; // memoria no dinamica -> no hay que hacerle free :) ! pero a los malloc que se hagan por dentro si 

	// 1. validate & parse input
	ft_parse_input(&monitor, argc, argv);

	// 2. init data

	// 3. philos do things

	// 4. end -> clean + exit

	return 0;
}
