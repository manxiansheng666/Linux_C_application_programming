#include "stdio.h"

int main()
{
	#ifdef __cplusplus
		printf("c++\n");
	#else
		printf("c\n");
	#endif
	
	return 0;
}