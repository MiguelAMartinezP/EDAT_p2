#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>

#include "odbc.h"
#include "products.h"

void ProductsStock(SQLHDBC dbc){
  SQLHENV env = NULL;
  SQLHSTMT stmt = NULL;
  int ret; /* odbc.c */
  SQLRETURN ret2; /* ODBC API return status */
  #define BufferLength 512
  SQLINTEGER quantityinstock=0;
  char productCode[BufferLength];


  /* CONNECT */
  ret = odbc_connect(&env, &dbc);
  if (!SQL_SUCCEEDED(ret)) {
      return;
  }

  ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
  ret = SQLPrepare(stmt, (SQLCHAR*) "select p.quantityinstock from products p where p.productcode = ?", SQL_NTS);
  if (!SQL_SUCCEEDED(ret)) {
      odbc_extract_error("", stmt, SQL_HANDLE_ENV);
      return;
  }


  printf("Enter productCode >");
  (void) fflush(stdout);
  scanf("%s", productCode);
      (void) SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_TCHAR, SQL_VARCHAR, 0, 0, productCode,BufferLength, NULL);

      (void) SQLExecute(stmt);

      (void) SQLBindCol(stmt, 1, SQL_C_SLONG,&quantityinstock,(SQLLEN)sizeof(SQLINTEGER), NULL);

      /* Loop through the rows in the result-set */
      while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
          printf("%d\n", quantityinstock);
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


void ProductsFind(SQLHDBC dbc){
    SQLHENV env = NULL;
    SQLHSTMT stmt = NULL;
    int ret; /* odbc.c */
    SQLRETURN ret2; /* ODBC API return status */
    #define BufferLength 512
    char productCode[BufferLength];
    char productName[BufferLength];


    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return;
    }

    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    ret = SQLPrepare(stmt, (SQLCHAR*) "select p.productCode, p.productName from products p where p.productname like ? order by p.productCode", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return;
    }


    printf("Enter productname > ");
    (void) fflush(stdout);
    scanf("%s", productName);
        (void) SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_TCHAR, SQL_VARCHAR, 0, 0,productName,BufferLength, NULL);

        (void) SQLExecute(stmt);

        (void) SQLBindCol(stmt, 1, SQL_C_CHAR,productCode, BufferLength, NULL);
        (void) SQLBindCol(stmt, 2, SQL_C_CHAR,productName, BufferLength, NULL);

        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            printf("%s %s\n", productCode, productName);
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
