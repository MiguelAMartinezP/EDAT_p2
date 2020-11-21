#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include "odbc.h"
#include "orders.h"

void OrdersOpen(SQLHDBC dbc);
void OrdersRange(SQLHDBC dbc);
void OrdersDetail(SQLHDBC dbc);

void OrdersOpen (SQLHDBC dbc){
  SQLHENV env = NULL;
  SQLHSTMT stmt = NULL;
  int ret; /* odbc.c */
  SQLRETURN ret2; /* ODBC API return status */
  #define BufferLength 512
  SQLINTEGER ordernumber = 0;


  /* CONNECT */
  ret = odbc_connect(&env, &dbc);
  if (!SQL_SUCCEEDED(ret)) {
      return;
  }

  /* Allocate a statement handle */
  ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
  ret = SQLPrepare(stmt, (SQLCHAR*) "select o.ordernumber from orders o where o.shippeddate is NULL order by o.ordernumber", SQL_NTS);
  if (!SQL_SUCCEEDED(ret)) {
      odbc_extract_error("", stmt, SQL_HANDLE_ENV);
      return;
  }

      (void) SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &ordernumber, 0, NULL);

      (void) SQLExecute(stmt);

      (void) SQLBindCol(stmt, 1, SQL_C_SLONG,&ordernumber,0, NULL);

      /* Loop through the rows in the result-set */
      while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
          printf("Ordernumber = %d\n", ordernumber);
      }

      (void) SQLCloseCursor(stmt);

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

void OrdersRange (SQLHDBC dbc){
  SQLHENV env = NULL;
  SQLHSTMT stmt = NULL;
  int ret; /* odbc.c */
  SQLRETURN ret2; /* ODBC API return status */
  #define BufferLength 512
  SQLINTEGER ordernumber;
  char shippeddate[BufferLength];
  char orderdate[BufferLength];
  char orderdate1[BufferLength];
  char orderdate2[BufferLength];

  /* CONNECT */
  ret = odbc_connect(&env, &dbc);
  if (!SQL_SUCCEEDED(ret)) {
      return;
  }

  /* Allocate a statement handle */
  ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
  ret = SQLPrepare(stmt, (SQLCHAR*) "select o.ordernumber o.orderdate o.shippeddate from orders o where o.orderdate1 like ? and o.orderdate2 like ? order by o.ordernumber", SQL_NTS);
  if (!SQL_SUCCEEDED(ret)) {
      odbc_extract_error("", stmt, SQL_HANDLE_ENV);
      return;
  }


  printf("Enter dates (YYYY-MM-DD - YYYY-MM-DD):");
  scanf("%s - %s", orderdate1, orderdate2);
      (void) SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, ordernumber, 0, NULL);

      (void) SQLExecute(stmt);

      (void) SQLBindCol(stmt, 1, SQL_C_SLONG,&ordernumber,0, NULL);
      (void) SQLBindCol(stmt, 2, SQL_C_TCHAR,(SQLCHAR*)orderdate,BufferLength, NULL);
      (void) SQLBindCol(stmt, 3, SQL_C_TCHAR,(SQLCHAR*)shippeddate,BufferLength, NULL);

      /* Loop through the rows in the result-set */
      while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
          printf("%d %s %s", ordernumber, orderdate,shippeddate);
      }

      (void) SQLCloseCursor(stmt);


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
void OrdersDetail (SQLHDBC dbc){
  SQLHENV env = NULL;
  SQLHSTMT stmt = NULL;
  int ret; /* odbc.c */
  SQLRETURN ret2; /* ODBC API return status */
  #define BufferLength 512
  SQLINTEGER productCode;
  SQLINTEGER quantityordered;
  SQLINTEGER ordernumber;
  SQLINTEGER orderlinenumber;
  int priceeach;

  /* CONNECT */
  ret = odbc_connect(&env, &dbc);
  if (!SQL_SUCCEEDED(ret)) {
      return;
  }

  /* Allocate a statement handle */
  ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
  ret = SQLPrepare(stmt, (SQLCHAR*) "select o.productCode, o.quantityordered, o.priceeach from orderdetails o where o.ordernumber = ? order by o.orderlinenumber", SQL_NTS);
  if (!SQL_SUCCEEDED(ret)) {
      odbc_extract_error("", stmt, SQL_HANDLE_ENV);
      return;
  }


  printf("Enter ordernumber = ");
  (void) fflush(stdout);
  scanf("%d", &ordernumber);
      (void) SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &ordernumber, 0, NULL);

      (void) SQLExecute(stmt);

      (void) SQLBindCol(stmt, 1, SQL_C_SLONG,&productCode,0, NULL);
      (void) SQLBindCol(stmt, 2, SQL_C_SLONG,&quantityordered,0, NULL);
      (void) SQLBindCol(stmt, 3, SQL_C_SLONG,&priceeach,0, NULL);

      /* Loop through the rows in the result-set */
      while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
          printf("%d %d %.2d\n",productCode,quantityordered,priceeach);
      }

      (void) SQLCloseCursor(stmt);

      printf("OK\n");
      /*(void) fflush(stdout);*/

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
