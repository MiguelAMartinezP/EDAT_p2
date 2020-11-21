#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include <sqltypes.h>

void CustomersFind (SQLHDBC dbc);
void CustomersListProducts (SQLHDBC dbc);
void CustomersBalance (SQLHDBC dbc);

#endif /*CUSTOMERS_H*/
