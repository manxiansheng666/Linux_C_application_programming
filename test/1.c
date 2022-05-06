#include <stdio.h>

#define STR(arg) #arg

int main()
{
	
	#ifdef DEBUG
	printf("debug!%s\n",STR(arg) "haha");
	#endif
	printf("hello!\n");
	return 0;
}