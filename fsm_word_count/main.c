#include <stdio.h>
#include "stateMachine.h"
#include <stdint.h>
#include "string.h"

typedef enum 
{
	SEPARATION,
	NOT_SEPARATION,
	STOP,
}event_type;

event_type current_event(const char one_char) ;
struct stateMachine m;
uint8_t count = 0;
void in_word_entryAction( void *stateData, struct event *event )
{
	count++;
}


struct state in_word,out_word,final,no_final,sE;
struct state in_word = {
	.parentState = &no_final,
	.transitions = (struct transition[]){
      { SEPARATION, NULL, NULL,NULL,&out_word},
	},
    .numTransitions = 1,
	.entryAction = in_word_entryAction,
	};

struct state out_word = {
	.parentState = &no_final,
	.transitions = (struct transition[]){
	  { NOT_SEPARATION, NULL, NULL,NULL,&in_word},
   },
	.numTransitions = 1,
};
struct state no_final = {
	.transitions = (struct transition[]){
	  { STOP, NULL, NULL,NULL,&final},
   },
	.numTransitions = 1,
};

uint8_t get_word_count(char* str)
{
	count = 0;
	
    stateM_init( &m, &out_word, &sE );

	uint8_t len = strlen(str) + 1;
	
	for(int i = 0;i < len;i++)
	{
		stateM_handleEvent( &m, &(struct event){ current_event(str[i]),NULL } );
	}
	return count;

}


event_type current_event(const char one_char) 
{
	char separate_char[] = { ',', '.', ' ' };
	char final_char = '\0';

	if (one_char == final_char) {
		return STOP;
	}

	for (int i = 0; i < sizeof(separate_char); i++) {
		if (one_char == separate_char[i]) {
			return SEPARATION;
		}
	}

	return NOT_SEPARATION;
}



int main()
{
	
	printf("strlen is %d\n",get_word_count("nin hao,wo shi song qing de."));
	return 0;
}