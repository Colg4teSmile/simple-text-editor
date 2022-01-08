#include "gap_buffer.h"

#include <stdio.h>

int main(int argc, char const *argv[])
{
	init_gap_buffer();
	//print_stats();

	while(1)
	{
		char ch = getchar();
		insert(ch);
		//resize();
		//print_stats();
	}

	return 0;
}