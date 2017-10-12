#include "node.h"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("\nError: Wrong number of arguments");
		return 1;
	}
	if (!readFile(argv[1]))
		return 1;
	return 0;
}
