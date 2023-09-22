#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rest_billing.h"

/**
 * main - entry point
 * Return: 0
 * 
 * Auth: Kent Gichuru
*/

int main(void)
{
	int opt;

	int num;
	int i;
	float total;
	orders ord;
	orders order;
	FILE *fp;
	char savebill = 'y', contFlag = 'y';
	char name[50];

	/*dashboard*/
	while(contFlag == 'y'){
	float total = 0;
	int invoice_found = 0;

	printf("\t==========ADV RESTAURANT===========\n\n");
	printf("\n\n Please selects an option\n");
	printf("1. Generate Invoice\n");
	printf("2. Show all invoices\n");
	printf("3. Search Invoice\n");
	printf("4. Exit\n");

	printf("\n\n Your choice is:\n");
	scanf("%d", &opt);
	fgetc(stdin);
	printf("You have selected:%d\n", opt);

	switch (opt)
	{
	case 1:/* constant-expression */
		printf("Please enter the name of the customer:\n");
		fgets(ord.customer, 50, stdin);
		ord.customer[strlen(ord.customer) - 1] = 0;
		strcpy(ord.date, __DATE__);
		printf("\nPlease enter the number of items:\n");
		scanf("%d", &num);

		for (i = 0; i < num; i++)
		{
			fgetc(stdin);
			printf("\n\n");
			printf("Please enter the item %d\t:", i + 1);
			fgets(ord.itm[i].item, 20, stdin);
			ord.itm[i].item[strlen(ord.itm[i].item) - 1] = 0;
			printf("\nPlease enter quantity:\t");
			scanf("%d", &ord.itm[i].qty);
			ord.numofitems = num;
			printf("\nPlease enter the unit price:\t");
			scanf("%f", &ord.itm[i].price);
			total += ord.itm[i].qty * ord.itm[i].price;
		}
		generatebillheader(ord.customer, ord.date);
		for (i = 0; i < ord.numofitems; i++)
		{
			generatebillbody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
		}
		generatebillfooter(total);

		printf("\nDo you want to save the invoice?:(y/n)\n");
		scanf("%s", &savebill);

		if (savebill == 'y')
		{
			fp = fopen("Restaurantbill.dat", "a+");
			fwrite(&ord, sizeof(orders), 1, fp);
			if(fwrite != 0)
			{
				printf("\nSuccessfully saved");
			}
			else
			{
				printf("\nError saving file");
			}
			fclose(fp);
		}
	break;
	case 2:
		fp = fopen("Restaurantbill.dat", "r");
		printf("\n  *****Your Previous Invoices*****\n");
		while(fread(&order, sizeof(orders), 1, fp))
		{
			float total2 = 0;
			generatebillheader(order.customer, order.date);
			for (i = 0; i < order.numofitems; i++)
			{
				generatebillbody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
				total += order.itm[i].qty * order.itm[i].price;
			}
			generatebillfooter(total2);
		}
		fclose(fp);
	break;
	case 3:
		printf("\nEnter the name of the customer:\t");
		/*fgetc(stdin);*/
		fgets(name, 50, stdin);
		name[strlen(name) - 1] = 0;
		fp = fopen("Restaurantbill.dat", "r");
		printf("\t  *****Invoice of %s*****\n", name);
		while(fread(&order, sizeof(orders), 1, fp))
		{
			float total2 = 0;
			if (!strcmp(order.customer, name))
			{
				generatebillheader(order.customer, order.date);
				for (i = 0; i < order.numofitems; i++)
				{
					generatebillbody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
					total += order.itm[i].qty * order.itm[i].price;
				}
				generatebillfooter(total2);
				invoice_found = 1;
			}
		}
		if(!invoice_found)
		{
			printf("The name of the customer does not exist");
		}
		fclose(fp);
	break;

	case 4:
		printf("Bye Bye\n\n");
		exit(0);
	break;

	default:
		printf("Invalid Option");
	break;
	}
	printf("\nDo you want to perform another operation(y/n)\n");
	scanf("%s", &contFlag);
	}
	printf("Bye Bye\n\n");
	printf("\n");

	return (0);
}
