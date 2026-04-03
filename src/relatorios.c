#include "../include/relatorios.h"
#include "../include/utils.h"
#include <stdio.h>

void mostrar_dados_aeronaves(dados_aeronaves_t *aeronave, FILE *fp) {
    fprintf(fp, "\n......DADOS DA AERONAVE......\n");
    fprintf(fp, "IDENTIFICACAO........: %d\n", aeronave->id_aeronave);
    fprintf(fp, "MODELO...............: %s\n", aeronave->modelo);
    fprintf(fp, "FABRICANTE...........: %s\n", aeronave->fabricante);
    fprintf(fp, "MATRICULA............: %s\n", aeronave->matricula);
    fprintf(fp, "ANO DE FABRICACAO....: %d\n", aeronave->ano_fabricacao);
    
    if(aeronave->tipo == CARGA){
        fprintf(fp, "TIPO.................: CARGA (CAPACIDADE: %d KG)\n", aeronave->qtd_carga_util);
    } else {
        fprintf(fp, "TIPO.................: PASSAGEIROS (CAPACIDADE: %d)\n", aeronave->num_passageiros);
    }

    if(aeronave->status == OPERACAO){
        fprintf(fp, "STATUS...............: EM OPERACAO\n");
    } else {
        fprintf(fp, "STATUS...............: EM MANUTENCAO (QTD. MANUTENCOES: %d)\n", aeronave->qtd_manutencoes);
    }
    fprintf(fp, "TRIPULANTES NECESSARIOS: %d\n", aeronave->num_tripulantes);
}

void mostrar_dados_rotas(dados_rotas_t *rota, FILE *fp) {
    fprintf(fp, "\n......DADOS DA ROTA......\n");
    fprintf(fp, "CODIGO DA ROTA..................: %d\n", rota->codigo_rota);
    fprintf(fp, "AERONAVE ALOCADA................: %d\n", rota->id_aeronave);
    fprintf(fp, "DATA DO VOO.....................: %02d/%02d/%04d\n", 
            rota->data_e_hora.dia, rota->data_e_hora.mes, rota->data_e_hora.ano);
    fprintf(fp, "HORARIO DO VOO..................: %02d:%02d\n", 
            rota->data_e_hora.hora, rota->data_e_hora.min);
    fprintf(fp, "LOCAL DE PARTIDA................: %s\n", rota->local_partida);        
    fprintf(fp, "LOCAL DE DESTINO................: %s\n", rota->local_destino);
    fprintf(fp, "COMBUSTIVEL NECESSARIO..........: %.2f LITROS\n", rota->combustivel_voo);
    fprintf(fp, "QUANTIDADE DE PASSAGEIROS.......: %d\n", rota->qtd_passageiros);
    fprintf(fp, "QUANTIDADE DE CARGA UTIL........: %d\n", rota->carga_util);
    fprintf(fp, "NUMERO DE TRIPULANTES...........: %d\n", rota->num_membros);

    for(int i = 0; i < rota->num_membros; i++){
        fprintf(fp, "  - MEMBRO %d: %s\n", i + 1, rota->nomes_membros[i]);
    }
}
// ... (resto das funções de listagem permanecem iguais)

void relatorio_aeronaves(dados_aeronaves_t *lista, FILE *fp) {
    dados_aeronaves_t *atual = lista;
    int contador = 0;
    if(lista == NULL){
        printf("Nenhuma aeronave cadastrada!\n");
        mensagem("Pressione ENTER para continuar!");
        return;
    }
    printf("......RELATÓRIO DE AERONAVES CADASTRADAS......\n");
    while(atual != NULL) {
        printf("\n--- AERONAVE %d ---\n", contador + 1);
        mostrar_dados_aeronaves(atual, stdout);
        contador++;
        atual = atual->prox;
    }
    printf("\nTotal de aeronaves: %d\n", contador); 
    mensagem("Pressione ENTER para continuar!");
}

void relatorio_rotas(dados_rotas_t *lista, FILE *fp) {
    dados_rotas_t *atual = lista;
    int contador = 0;
    if(lista == NULL){
        printf("Nenhuma rota cadastrada!\n");
        mensagem("Pressione ENTER para continuar!");
        return;
    }
    printf("......RELATÓRIO DE ROTAS CADASTRADAS......\n");
    while(atual != NULL) {
        printf("\n--- ROTA %d ---\n", contador + 1);
        mostrar_dados_rotas(atual, stdout);
        contador++;
        atual = atual->prox;
    }
    printf("\nTotal de rotas: %d\n", contador); 
    mensagem("Pressione ENTER para continuar!");
}

void listar_rotas_maiornumero_passageiros(dados_rotas_t *lista, FILE *fp) {
    int max_passageiros = -1;
    dados_rotas_t *atual = lista;
    if(lista == NULL){
        printf("Nenhuma rota cadastrada!");
        mensagem("Pressione ENTER para continuar!");
        return;
    }
    while(atual != NULL) {
        if(atual->qtd_passageiros > max_passageiros) max_passageiros = atual->qtd_passageiros;
        atual = atual->prox;
    }
    printf("......ROTAS COM O MAIOR NÚMERO DE PASSAGEIROS (%d)......\n", max_passageiros);
    atual = lista; 
    while(atual != NULL) {
        if(atual->qtd_passageiros == max_passageiros) mostrar_dados_rotas(atual, stdout);
        atual = atual->prox;
    }
    mensagem("Pressione ENTER para continuar!");
}

void listar_rotas_menornumero_passageiros(dados_rotas_t *lista, FILE *fp) {
    int min_passageiros = 2147483647; 
    dados_rotas_t *atual = lista;
    if(lista == NULL){
        printf("Nenhuma rota cadastrada!");
        mensagem("Pressione ENTER para continuar!");
        return;
    }
    while(atual != NULL) {
        if(atual->qtd_passageiros < min_passageiros) min_passageiros = atual->qtd_passageiros;
        atual = atual->prox;
    }
    printf("......ROTAS COM O MENOR NÚMERO DE PASSAGEIROS (%d)......\n", min_passageiros);
    atual = lista; 
    while(atual != NULL) {
        if(atual->qtd_passageiros == min_passageiros) mostrar_dados_rotas(atual, stdout);
        atual = atual->prox;
    }
    mensagem("Pressione ENTER para continuar!");
}