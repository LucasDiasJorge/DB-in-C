#include <stdio.h>
#include <stdlib.h>
#include <postgresql/libpq-fe.h>

PGconn *connectDB() {
    PGconn *conn = PQconnectdb("dbname=valgroup user=postgres password=postgres ");
    
    if (PQstatus(conn) != CONNECTION_OK) {
        printf("Erro ao conectar ao banco de dados: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        return NULL;
    }
    
    return conn;
}

void executeSelect(PGconn *conn, const char *query) {
    PGresult *res = PQexec(conn, query);
    
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        printf("Erro ao executar a consulta: %s\n", PQerrorMessage(conn));
        PQclear(res);
        return;
    }
    
    int numRows = PQntuples(res);
    int numCols = PQnfields(res);
    
    printf("Resultado da consulta:\n");
    
    for (int i = 0; i < numCols; i++) {
        printf("%-15s", PQfname(res, i));
    }
    
    printf("\n");
    
    int i = 0;

    for (;i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            printf("%-15s", PQgetvalue(res, i, j));
        }
        
        printf("\n");
    }

    printf("Foram encontados %d resultados.\n",i);
    
    PQclear(res);
}

int main() {
    PGconn *conn = connectDB();
    
    if (conn == NULL) {
        return 1;
    }
    
    const char *query = "SELECT epc FROM sys_item";
    
    executeSelect(conn, query);
    
    PQfinish(conn);
    
    return 0;
}
