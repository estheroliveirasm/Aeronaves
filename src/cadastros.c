#include "../include/cadastros.h"
#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

dados_aeronaves_t *nova_aeronave() {
    dados_aeronaves_t *aeronave = (dados_aeronaves_t*)malloc(sizeof(dados_aeronaves_t));
    int num_tipo, num_status;
    if(aeronave == NULL) return NULL;
    
    aeronave->qtd_manutencoes = 0;
    printf(".........CADASTRO DE AERONAVE.........\n");
    printf("Identificacao da aeronave...........: ");
    scanf("%d", &aeronave->id_aeronave);
    while (getchar() != '\n');

    printf("Modelo da aeronave..................: ");
    fgets(aeronave->modelo, STR_SIZE, stdin);
    remover_enter(aeronave->modelo);
    to_upper_string(aeronave->modelo); 

    printf("Fabricante da aeronave..............: ");
    fgets(aeronave->fabricante, STR_SIZE, stdin);
    remover_enter(aeronave->fabricante);
    to_upper_string(aeronave->fabricante);

    printf("Matricula do aviao..................: ");
    fgets(aeronave->matricula, STR_SIZE, stdin);
    remover_enter(aeronave->matricula);
    to_upper_string(aeronave->matricula);

    printf("Ano de fabricacao...................: ");
    scanf("%d", &aeronave->ano_fabricacao);
    
    printf("Tipo (1- CARGA | 2- PASSAGEIRO).....: ");
    scanf("%d", &num_tipo);
    while (getchar() != '\n');
    aeronave->tipo = (tipo_aeronave_t)num_tipo;

    if(aeronave->tipo == PASSAGEIRO) {
        printf("Numero de passageiros...............: ");
        scanf("%d", &aeronave->num_passageiros);
        aeronave->qtd_carga_util = 0;
    } else { 
        aeronave->num_passageiros = 0;
        printf("Quantidade de carga util (kg).......: ");
        scanf("%d", &aeronave->qtd_carga_util);
    }
    while (getchar() != '\n');

    printf("Status (1- OPERACAO | 2- MANUTENCAO): ");
    scanf("%d", &num_status);
    while (getchar() != '\n');
    aeronave->status = (status_t)num_status;
    
    if(aeronave->status == MANUTENCAO) aeronave->qtd_manutencoes++;

    printf("Tripulacao necessaria...............: ");
    scanf("%d", &aeronave->num_tripulantes);
    while (getchar() != '\n');

    aeronave->prox = NULL;
    return aeronave;
}

dados_rotas_t *nova_rota(dados_aeronaves_t *lista_aeronaves) {
    dados_rotas_t *rota = (dados_rotas_t*)malloc(sizeof(dados_rotas_t));
    if(rota == NULL) return NULL;
    
    int aeronave_valida = 0;
    dados_aeronaves_t *aero_ref = NULL;

    limpar_tela();
    printf("..........CADASTRO DE ROTAS..........\n");

    do {
        printf("\nAeronave a ser alocada (ID)........: ");
        scanf("%d", &rota->id_aeronave);
        while (getchar() != '\n');
        aero_ref = localizar_aeronave_por_id(rota->id_aeronave, lista_aeronaves);

        if(!aero_ref) printf(" Erro: Aeronave nao localizada.\n");
        else if (aero_ref->status != OPERACAO) printf(" Erro: Aeronave indisponivel (em manutencao).\n");
        else aeronave_valida = 1;
    } while(!aeronave_valida);

    printf("Codigo da rota.....................: ");
    scanf("%d", &rota->codigo_rota);
    while (getchar() != '\n');

    printf("Data do voo (DD/MM/AAAA)...........: ");
    scanf("%d/%d/%d", &rota->data_e_hora.dia, &rota->data_e_hora.mes, &rota->data_e_hora.ano);
    while (getchar() != '\n');

    printf("Horario de partida (HH:MM).........: ");
    scanf("%d:%d", &rota->data_e_hora.hora, &rota->data_e_hora.min);
    while (getchar() != '\n');

    printf("Local de partida...................: ");
    fgets(rota->local_partida, STR_SIZE, stdin);
    remover_enter(rota->local_partida);
    to_upper_string(rota->local_partida);

    printf("Local de destino...................: ");
    fgets(rota->local_destino, STR_SIZE, stdin);
    remover_enter(rota->local_destino);
    to_upper_string(rota->local_destino);

    printf("Combustivel necessario (litros)....: ");
    scanf("%f", &rota->combustivel_voo);
    while (getchar() != '\n');

    if (aero_ref->tipo == PASSAGEIRO) {
        do {
            printf("Quantidade de passageiros (Max %d): ", aero_ref->num_passageiros);
            scanf("%d", &rota->qtd_passageiros);
            while (getchar() != '\n');
        } while(rota->qtd_passageiros > aero_ref->num_passageiros);
        rota->carga_util = 0;
    } else {
        do {
            printf("Quantidade de carga (Max %d kg)....: ", aero_ref->qtd_carga_util);
            scanf("%d", &rota->carga_util);
            while (getchar() != '\n');
        } while(rota->carga_util > aero_ref->qtd_carga_util);
        rota->qtd_passageiros = 0;
    }

    do {
        printf("Numero de tripulantes (Min %d)......: ", aero_ref->num_tripulantes);
        scanf("%d", &rota->num_membros);
        while (getchar() != '\n');
    } while (rota->num_membros < aero_ref->num_tripulantes || rota->num_membros > 10);

    for(int i = 0; i < rota->num_membros; i++) {
        printf("Nome do membro %d..................: ", i + 1);
        fgets(rota->nomes_membros[i], STR_SIZE, stdin);
        remover_enter(rota->nomes_membros[i]);
        to_upper_string(rota->nomes_membros[i]);
    }

    rota->prox = NULL;
    return rota;
}

void inserir_aeronave_lista_pelo_fim(dados_aeronaves_t **lista, dados_aeronaves_t *nova_aeronave) {
    if (nova_aeronave == NULL) return;
    if (*lista == NULL) {
        *lista = nova_aeronave;
    } else {
        dados_aeronaves_t *ultimo = *lista;
        while (ultimo->prox != NULL) ultimo = ultimo->prox;
        ultimo->prox = nova_aeronave;
    }
}

void inserir_rota_lista_pelo_fim(dados_rotas_t **lista, dados_rotas_t *nova_rota) {
    if (nova_rota == NULL) return;
    if (*lista == NULL) {
        *lista = nova_rota;
    } else {
        dados_rotas_t *ultimo = *lista;
        while (ultimo->prox != NULL) ultimo = ultimo->prox;
        ultimo->prox = nova_rota;
    }
}

dados_aeronaves_t *localizar_aeronave_por_id(int id_aeronave, dados_aeronaves_t *lista) {
   if(lista == NULL) return NULL;
   if(lista->id_aeronave == id_aeronave) return lista;
   return localizar_aeronave_por_id(id_aeronave, lista->prox);
}

void alterar_status_aeronave(dados_aeronaves_t **lista_aeronaves) {
    int id_escolhido, novo_status;
    dados_aeronaves_t *aeronave = NULL;

    printf("\n--- ALTERACAO DE STATUS ---\n");
    printf("Informe o ID da aeronave...........: ");
    scanf("%d", &id_escolhido);
    while (getchar() != '\n');

    aeronave = localizar_aeronave_por_id(id_escolhido, *lista_aeronaves);
    if(!aeronave) {
        printf(" Erro: Aeronave nao localizada.\n");
        mensagem("Pressione ENTER para retornar ao menu.");
        return;
    }

    printf("Novo status (1- OPERACAO | 2- MANUTENCAO): ");
    scanf("%d", &novo_status);
    while (getchar() != '\n');

    if((status_t)novo_status == MANUTENCAO && aeronave->status != MANUTENCAO) {
        aeronave->qtd_manutencoes++;
        printf(" Registro: Aeronave em manutencao pela %dª vez.\n", aeronave->qtd_manutencoes);
    }

    aeronave->status = (status_t)novo_status;
    printf("\n Sucesso: Status da aeronave %d alterado para %s.\n", id_escolhido, 
          (aeronave->status == OPERACAO) ? "OPERACAO" : "MANUTENCAO");
    mensagem("Pressione ENTER para continuar.");
}