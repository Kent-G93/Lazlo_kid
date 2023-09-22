#ifndef REST_BILLING_H
#define REST_BILLING_H

/**
 * struct items - struct for items
 * @item: goods
 * @price: price
 * @qty: quantity
*/

typedef struct items
{
	char item[50];
	float price;
	int qty;
}
items;

/**
 * struct orders - struct for orders
 * @numofitems: number of items
 * @customer: name of cust
 * @date: date
 * @itm: items
*/
typedef struct orders
{
	char customer[50];
	char date[50];
	char numofitems;
	items itm[50];
}
orders;

/******FUNCTIONS******/

void generatebillheader(char name[50], char date[30]);
void generatebillbody(char item[30], int qty, float price);
void generatebillfooter(float total);

#endif
