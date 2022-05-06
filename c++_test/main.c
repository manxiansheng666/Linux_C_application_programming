#include <stdio.h>
#include "linux_list.h"
#include <stdint.h>

typedef struct 
{
	uint8_t age;
	uint8_t name[20];
	struct list_head node;
}Person;

int main()
{
	LIST_HEAD(person);
	
	Person p1 = {20,"yi"};
	Person p2 = {30,"er"};
	Person p3 = {25,"san"};

	list_add_tail(&p1.node,&person);
	list_add_tail(&p2.node,&person);
	list_add_tail(&p3.node,&person);
	
	Person *p;
	list_for_each_entry_reverse(p,&person,node)
	{
		printf("age is %d,name is %s\n",p->age,(char *)(p->name));
	}
	
	return 0;
}