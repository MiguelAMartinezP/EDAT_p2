#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include "odbc.h"
#include "customers.h"

void CustomersFind (SQLHDBC dbc);
void CustomersListProducts (SQLHDBC dbc);
void CustomersBalance (SQLHDBC dbc);

void CustomersFind (SQLHDBC dbc){
  SQLHENV env = NULL;
  SQLHSTMT stmt = NULL;
  int ret; /* odbc.c */
  SQLRETURN ret2; /* ODBC API return status */
  #define BufferLength 512
  char customerfirstname[BufferLength];
  char customerlastname[BufferLength];
  SQLINTEGER customernumber;
  char customername[BufferLength];


  /* CONNECT */
  ret = odbc_connect(&env, &dbc);
  if (!SQL_SUCCEEDED(ret)) {
      return;
  }

  /* Allocate a statement handle */
  ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
  ret = SQLPrepare(stmt, (SQLCHAR*) "select c2.customernumber,c2.customerfirstname, c2.contactlastname from customers c2 where c2.firstname like ? or c2.contactlastname like ? order by c2.customernumber", SQL_NTS);
  if (!SQL_SUCCEEDED(ret)) {
      odbc_extract_error("", stmt, SQL_HANDLE_ENV);
      return;
  }


  printf("Enter customer name: ");
  (void) fflush(stdout);
  scanf("%s",customername);
      (void) SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &customername, BufferLength, NULL);

      (void) SQLExecute(stmt);

      (void) SQLBindCol(stmt, 1, SQL_C_SLONG,&customernumber,0, NULL);
      (void) SQLBindCol(stmt, 2, SQL_C_CHAR,(SQLCHAR *) customerfirstname, BufferLength, NULL);
      (void) SQLBindCol(stmt, 3, SQL_C_CHAR,(SQLCHAR *) customerlastname, BufferLength, NULL);

      /* Loop through the rows in the result-set */
      while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
          printf("%d %s %s",customernumber,customerfirstname,customerlastname);
      }

      (void) SQLCloseCursor(stmt);

      printf("OK");
      (void) fflush(stdout);

  printf("\n");

  /* free up statement handle */
  ret2 = SQLFreeHandle(SQL_HANDLE_STMT, stmt);
  if (!SQL_SUCCEEDED(ret2)) {
      odbc_extract_error("", stmt, SQL_HANDLE_STMT);
      return;
  }

  /* DISCONNECT */
  ret = odbc_disconnect(env, dbc);
  if (!SQL_SUCCEEDED(ret)) {
      return;
  }

  return;
}
void CustomersListProducts (SQLHDBC dbc){

}
void CustomersBalance (SQLHDBC dbc){

}
