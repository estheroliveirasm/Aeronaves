#include "../include/arquivos.h"
#include "../include/cadastros.h"
#include "../include/types.h"
#include "../include/relatorios.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void salvar_dados_aeronaves_bin(dados_aeronaves_t *lista, string nome_arq) {
    FILE *fp = fopen(nome_arq, "wb"); 
    if (!fp) {
        printf("\n Erro ao salvar o arquivo aeronaves: %s\n", nome_arq);
        return;
    }
    dados_aeronaves_t *atual = lista;
    while (atual) {
        if (fwrite(atual, sizeof(dados_aeronaves_t), 1, fp) != 1) break;
        atual = atual->prox;
    }
    fclose(fp); 
}

void ler_dados_aeronaves_bin(string nome_arq, dados_aeronaves_t **lista) {
    FILE *fp = fopen(nome_arq, "rb");
    if (!fp) {
        printf("\n Arquivo %s nao encontrado. Iniciando novo banco de dados...\n", nome_arq);
        return;
    }
    *lista = NULL;
    size_t lidos;
    while (1) {
        dados_aeronaves_t *novo = (dados_aeronaves_t*)malloc(sizeof(dados_aeronaves_t));
        if (!novo) break;
        lidos = fread(novo, sizeof(dados_aeronaves_t), 1, fp);
        if (lidos != 1) {
            free(novo);
            break;
        }
        novo->prox = NULL;
        inserir_aeronave_lista_pelo_fim(lista, novo);
    }
    fclose(fp);
}

void salvar_dados_rotas_bin(dados_rotas_t *lista, string nome_arq) {
    FILE *fp = fopen(nome_arq, "wb");
    if (!fp) {
        printf("\n Erro ao salvar o arquivo rotas: %s\n", nome_arq);
        return;
    }
    dados_rotas_t *atual = lista;
    while (atual) {
        if (fwrite(atual, sizeof(dados_rotas_t), 1, fp) != 1) break;
        atual = atual->prox;
    }
    fclose(fp);
}

void ler_dados_rotas_bin(string nome_arq, dados_rotas_t **lista) {
    FILE *fp = fopen(nome_arq, "rb");
    if (!fp) {
        printf("\n Arquivo %s nao encontrado. Iniciando novo banco de dados...\n", nome_arq);
        return;
    }
    *lista = NULL;
    size_t lidos;
    while (1) {
        dados_rotas_t *novo = (dados_rotas_t*)malloc(sizeof(dados_rotas_t));
        if (!novo) break;
        lidos = fread(novo, sizeof(dados_rotas_t), 1, fp);
        if (lidos != 1) {
            free(novo);
            break;
        }
        novo->prox = NULL;
        inserir_rota_lista_pelo_fim(lista, novo);
    }
    fclose(fp);
}

void exportar_aeronaves_txt(dados_aeronaves_t *lista_aeronaves, string nome_arq) {
    FILE *fp = fopen(nome_arq, "w");
    if (!fp) {
        printf("\n Erro ao abrir o arquivo de texto: %s\n", nome_arq);
        return;
    }
    dados_aeronaves_t *atual = lista_aeronaves;
    while (atual) {
        mostrar_dados_aeronaves(atual, fp);
        fprintf(fp, "\n------------------------------\n");
        atual = atual->prox;
    }
    fclose(fp);
    printf("\n Dados de aeronaves exportados com sucesso para TXT.\n");
    printf(" Arquivo gerado: %s\n", nome_arq);
}

void exportar_aeronaves_csv(dados_aeronaves_t *lista_aeronaves, string nome_arq) {
    FILE *fp = fopen(nome_arq, "w");
    if (!fp) {
        printf("\n Erro ao abrir o arquivo CSV: %s\n", nome_arq);
        return;
    }
    fprintf(fp, "ID;MATRICULA;MODELO;FABRICANTE;ANO;TIPO;STATUS;PASSAGEIROS;CARGA;TRIPULANTES;MANUTENCOES\n");
    
    dados_aeronaves_t *atual = lista_aeronaves;
    while (atual) {
        fprintf(fp, "%i;%s;%s;%s;%i;%s;%s;%i;%i;%i;%i\n", 
            atual->id_aeronave, atual->matricula, atual->modelo, atual->fabricante, 
            atual->ano_fabricacao, 
            (atual->tipo == CARGA) ? "CARGA" : "PASSAGEIRO", 
            (atual->status == OPERACAO) ? "OPERACAO" : "MANUTENCAO",
            atual->num_passageiros, atual->qtd_carga_util, 
            atual->num_tripulantes, atual->qtd_manutencoes);
        atual = atual->prox;
    }
    fclose(fp);
    printf("\n Dados de aeronaves exportados com sucesso para CSV.\n");
    printf(" Arquivo gerado: %s\n", nome_arq);
}

void exportar_aeronaves_html(dados_aeronaves_t *lista_aeronaves, string nome_arq) {
    FILE *fp = fopen(nome_arq, "w");
    if (!fp) {
        printf("\n Erro ao abrir o arquivo HTML: %s\n", nome_arq);
        return;
    }
    fprintf(fp, "<html><head><meta charset='UTF-8'><style>table{width:100%%;border-collapse:collapse;}th,td{border:1px solid #ddd;padding:8px;text-align:left;}th{background-color:#4CAF50;color:white;}tr:nth-child(even){background-color:#f2f2f2;}</style></head><body>");
    fprintf(fp, "<h1>Relatorio de Aeronaves</h1><table><tr><th>ID</th><th>Matricula</th><th>Modelo</th><th>Tipo</th><th>Status</th></tr>");
    
    dados_aeronaves_t *atual = lista_aeronaves;
    while (atual) {
        fprintf(fp, "<tr><td>%i</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td></tr>", 
            atual->id_aeronave, atual->matricula, atual->modelo,
            (atual->tipo == CARGA) ? "Carga" : "Passageiro",
            (atual->status == OPERACAO) ? "Em Operacao" : "Em Manutencao");
        atual = atual->prox;
    }
    fprintf(fp, "</table></body></html>");
    fclose(fp);
    printf("\n Dados de aeronaves exportados com sucesso para HTML.\n");
    printf(" Arquivo gerado: %s\n", nome_arq);
}

void exportar_rotas_txt(dados_rotas_t *lista_rotas, string nome_arq) {
    FILE *fp = fopen(nome_arq, "w");
    if (!fp) {
        printf("\n Erro ao abrir o arquivo de texto: %s\n", nome_arq);
        return;
    }
    dados_rotas_t *atual = lista_rotas;
    while (atual) {
        mostrar_dados_rotas(atual, fp);
        fprintf(fp, "\n------------------------------\n");
        atual = atual->prox;
    }
    fclose(fp);
    printf("\n Dados de rotas exportados com sucesso para TXT.\n");
    printf(" Arquivo gerado: %s\n", nome_arq);
}

void exportar_rotas_csv(dados_rotas_t *lista_rotas, string nome_arq) {
    FILE *fp = fopen(nome_arq, "w");
    if (!fp) {
        printf("\n Erro ao abrir o arquivo CSV: %s\n", nome_arq);
        return;
    }
    fprintf(fp, "CODIGO;ID_AERONAVE;DATA;HORA;ORIGEM;DESTINO;DURACAO;COMBUSTIVEL;PASSAGEIROS;CARGA;TRIPULACAO\n");
    
    dados_rotas_t *atual = lista_rotas;
    while (atual) {
        fprintf(fp, "%i;%i;%02i/%02i/%i;%02i:%02i;%s;%s;%.2f;%.2f;%i;%i;%i\n", 
            atual->codigo_rota, atual->id_aeronave,
            atual->data_e_hora.dia, atual->data_e_hora.mes, atual->data_e_hora.ano,
            atual->data_e_hora.hora, atual->data_e_hora.min,
            atual->local_partida, atual->local_destino,
            atual->tempo_estimado, atual->combustivel_voo,
            atual->qtd_passageiros, atual->carga_util, atual->num_membros);
        atual = atual->prox;
    }
    fclose(fp);
    printf("\n Dados de rotas exportados com sucesso para CSV.\n");
    printf(" Arquivo gerado: %s\n", nome_arq);
}

void exportar_rotas_html(dados_rotas_t *lista_rotas, string nome_arq) {
    FILE *fp = fopen(nome_arq, "w");
    if (!fp) {
        printf("\n Erro ao abrir o arquivo HTML: %s\n", nome_arq);
        return;
    }
    fprintf(fp, "<html><head><meta charset='UTF-8'><style>table{width:100%%;border-collapse:collapse;}th,td{border:1px solid #ddd;padding:8px;text-align:left;}th{background-color:#2196F3;color:white;}tr:nth-child(even){background-color:#f9f9f9;}</style></head><body>");
    fprintf(fp, "<h1>Relatorio de Rotas</h1><table><tr><th>Codigo</th><th>ID Aero</th><th>Data/Hora</th><th>Origem</th><th>Destino</th></tr>");
    
    dados_rotas_t *atual = lista_rotas;
    while (atual) {
        fprintf(fp, "<tr><td>%i</td><td>%i</td><td>%02i/%02i/%i %02i:%02i</td><td>%s</td><td>%s</td></tr>", 
            atual->codigo_rota, atual->id_aeronave,
            atual->data_e_hora.dia, atual->data_e_hora.mes, atual->data_e_hora.ano,
            atual->data_e_hora.hora, atual->data_e_hora.min,
            atual->local_partida, atual->local_destino);
        atual = atual->prox;
    }
    fprintf(fp, "</table></body></html>");
    fclose(fp);
    printf("\n Dados de rotas exportados com sucesso para HTML.\n");
    printf(" Arquivo gerado: %s\n", nome_arq);
}