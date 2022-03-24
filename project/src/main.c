#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

int main(void) 
{
	int choice = 0;	
	FILE *Ptr;
	FILE *Ptr_2;
	FILE *blackrecord;
  	Data client_data = {0};
	Data transfer = {0};
	printf("%s", "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
	while (scanf("%d", &choice) != -1)
	{
		switch(choice) {
			case 1:
				Ptr = fopen(filename_record, "r+");
				if (Ptr == NULL)
					puts("Not access");
				else
				{
					masterWrite(Ptr, client_data);	
					fclose(Ptr);
				}
				break;
			case 2:
				Ptr = fopen(filename_transaction, "r+");
				if (Ptr == NULL)
					puts("Not access");
				else
				{
					transactionWrite(Ptr, transfer);
					fclose(Ptr);
				}
				break;	
			case 3:
				Ptr = fopen(filename_record, "r");
				Ptr_2 = fopen(filename_transaction, "r");
				blackrecord = fopen(filename_blackrecord, "w");
				if (Ptr == NULL || Ptr_2 == NULL || blackrecord == NULL)
					puts("exit");
				else
				{
					blackRecord(Ptr, Ptr_2, blackrecord, client_data, transfer);
					//free(Ptr);
					fclose(Ptr);
					fclose(Ptr_2);	
					fclose(blackrecord);
				}
				break;
			default:
				puts("error");
				break ;
			}
 			printf("%s", "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
	}
	return 0;	
}
