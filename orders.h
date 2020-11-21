#ifndef ORDERS_H
#define ORDERS_H

#include <sqltypes.h>

void OrdersOpen (SQLHDBC dbc);
void OrdersRange (SQLHDBC dbc);
void OrdersDetail (SQLHDBC dbc);

#endif /* PRODUCTS_H */
