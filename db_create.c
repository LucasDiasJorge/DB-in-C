#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

int main() {
    // Conecte-se ao servidor PostgreSQL
    PGconn *conn = PQconnectdb("host=localhost port=5432 user=seu_usuario password=sua_senha");
    
    // Verifique se a conexão foi bem-sucedida
    if (PQstatus(conn) == CONNECTION_BAD) {
        fprintf(stderr, "Erro de conexão: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1);
    }

    // Nome do banco de dados a ser criado
    const char *db_name = "meu_novo_banco_de_dados";

    // Consulta SQL para criar o banco de dados
    const char *create_db_query = "CREATE DATABASE meu_novo_banco_de_dados";

    // Execute a consulta para criar o banco de dados
    PGresult *res = PQexec(conn, create_db_query);
    
    if (PQresultStatus(res) == PGRES_COMMAND_OK) {
        printf("Banco de dados '%s' criado com sucesso.\n", db_name);
    } else {
        fprintf(stderr, "Erro ao criar o banco de dados: %s", PQerrorMessage(conn));
    }

    // Libere os recursos
    PQclear(res);
    PQfinish(conn);

    return 0;
}
