#include "../include/cadastros.h"
#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

dados_aeronaves_t *nova_aeronave()
{
    dados_aeronaves_t *aeronave = (dados_aeronaves_t*)malloc(sizeof(dados_aeronaves_t));
    int num_tipo;
    int num_status;

    if(aeronave == NULL) {
        printf("Erro de alocação de memória!\n");
        return NULL;
    }
    
    aeronave->qtd_manutencoes = 0;
    
    printf("......CADASTRO DE AERONAVE.......\n");
    
    printf("Identificação da aeronave......: ");
    scanf("%i", &aeronave->id_aeronave);
    while (getchar() != '\n');

    printf("Modelo da aeronave.............: ");
    fgets(aeronave->modelo, STR_SIZE, stdin);
    remover_enter(aeronave->modelo);
    to_upper_string(aeronave->modelo);

    printf("Fabricante da aeronave.........: ");
    fgets(aeronave->fabricante, STR_SIZE, stdin);
    remover_enter(aeronave->fabricante);
    to_upper_string(aeronave->fabricante);

    printf("Matricula do avião.............: ");
    fgets(aeronave->matricula, STR_SIZE, stdin);
    remover_enter(aeronave->matricula);
    to_upper_string(aeronave->matricula);

    printf("Ano de fabricação da aeronave..: ");
    scanf("%i", &aeronave->ano_fabricacao);
    
    printf("Tipo de aeronave (1- CARGA ou 2- PASSAGEIRO): ");
    scanf("%i", &num_tipo);
    while (getchar() != '\n');
    aeronave->tipo = (tipo_aeronave_t)num_tipo;

    if(aeronave->tipo == PASSAGEIRO) {
        printf("Número de passageiros..........: ");
        scanf("%i", &aeronave->num_passageiros);
        while (getchar() != '\n');
        aeronave->qtd_carga_util = 0;
    }
    else { 
        aeronave->num_passageiros = 0;
        printf("Quantidade de carga útil(kg)....: ");
        scanf("%i", &aeronave->qtd_carga_util);
        while (getchar() != '\n');
    }

    printf("Status da aeronave (1- Em operação ou 2- Em manutenção): ");
    scanf("%i", &num_status);
    while (getchar() != '\n');
    aeronave->status = (status_t)num_status;
    
    if(aeronave->status == MANUTENCAO) {
        aeronave->qtd_manutencoes++;
    }

    printf("Tripulação necessaria..........: ");
    scanf("%i", &aeronave->num_tripulantes);
    while (getchar() != '\n');

    aeronave->prox = NULL;
    return aeronave;
}

dados_rotas_t *nova_rota(dados_aeronaves_t *lista_aeronaves)
{
    dados_rotas_t *rota = (dados_rotas_t*)malloc(sizeof(dados_rotas_t));
    if(rota == NULL) {
        printf("Erro de alocação de memória!\n");
        return NULL;
    }
    
    int aeronave_valida = 0;
    dados_aeronaves_t *aeronave_alocada = NULL;

    limpar_tela();
    printf("......CADASTRO DE ROTAS.......\n");

    int encontrou_operacional = 0;
    dados_aeronaves_t *temp = lista_aeronaves;
    while(temp) {
        if(temp->status == OPERACAO) { encontrou_operacional = 1; break; }
        temp = temp->prox;
    }

    if(!encontrou_operacional) {
        printf("Erro! Nenhuma aeronave em operação disponível!\n");
        free(rota);
        mensagem("Pressione ENTER para continuar!");
        return NULL;
    }

    printf("Código da rota..................: ");
    scanf("%d", &rota->codigo_rota);
    while (getchar() != '\n');
    do {
        printf("\nAeronave a ser alocada (Digite o código): ");
        scanf("%i", &rota->id_aeronave);
        while (getchar() != '\n');

        aeronave_alocada = localizar_aeronave_por_id(rota->id_aeronave, lista_aeronaves);

        if(!aeronave_alocada) {
            printf("Erro! Aeronave não encontrada. Tente novamente!\n");
        } else if (aeronave_alocada->status != OPERACAO) {
            printf("Erro! Aeronave em manutenção. Escolha outra!\n");
        } else {
            aeronave_valida = 1;
        }
    } while(!aeronave_valida);

    printf("Data do voo (dd/mm/aaaa)........: ");
    scanf("%i/%i/%i", &rota->data_e_hora.dia, &rota->data_e_hora.mes, &rota->data_e_hora.ano);
    while (getchar() != '\n');

    printf("Horario do voo (hh:mm)..........: ");
    scanf("%i:%i", &rota->data_e_hora.hora, &rota->data_e_hora.min);
    while (getchar() != '\n');

    printf("Local de partida................: ");
    fgets(rota->local_partida, STR_SIZE, stdin);
    remover_enter(rota->local_partida);
    to_upper_string(rota->local_partida);
    
    printf("Local de destino................: ");
    fgets(rota->local_destino, STR_SIZE, stdin);
    remover_enter(rota->local_destino);
    to_upper_string(rota->local_destino);

    printf("Tempo estimado de voo (hh:mm)...: ");
    scanf("%f", &rota->tempo_estimado);
    while (getchar() != '\n');

    printf("Combustivel necessário(litros)..........: ");
    scanf("%f", &rota->combustivel_voo);
    while (getchar() != '\n');

    do {
        printf("Quantidade de passageiros.......: ");
        scanf("%i", &rota->qtd_passageiros);
        while (getchar() != '\n');
        if(rota->qtd_passageiros > aeronave_alocada->num_passageiros) {
            printf("Erro! Capacidade máxima da aeronave é %i passageiros.\n", aeronave_alocada->num_passageiros);
        }
    } while(rota->qtd_passageiros > aeronave_alocada->num_passageiros);

    do {
        printf("Quantidade de carga util(kg)........: ");
        scanf("%i", &rota->carga_util);
        while (getchar() != '\n');
        if(rota->carga_util > aeronave_alocada->qtd_carga_util) {
            printf("Erro! Capacidade máxima de carga é %i kg.\n", aeronave_alocada->qtd_carga_util);
        }
    } while(rota->carga_util > aeronave_alocada->qtd_carga_util);

    do {
        printf("\nTripução necessária para a aeronave: %i\n", aeronave_alocada->num_tripulantes);
        printf("Número de tripulantes para esta rota: ");
        scanf("%i", &rota->num_membros);
        while (getchar() != '\n');

        if(rota->num_membros < aeronave_alocada->num_tripulantes) {
            printf("Erro! Número insuficiente. Mínimo exigido: %i\n", aeronave_alocada->num_tripulantes);
        } else if (rota->num_membros > 10) {
            printf("Erro! O sistema suporta no máximo 10 nomes de tripulantes.\n");
        }
    } while(rota->num_membros < aeronave_alocada->num_tripulantes || rota->num_membros > 10);

    for(int i = 0; i < rota->num_membros; i++) {
        printf("Digite o nome do membro %i da tripulação: ", i + 1);
        fgets(rota->nomes_membros[i], STR_SIZE, stdin);
        remover_enter(rota->nomes_membros[i]);
        to_upper_string(rota->nomes_membros[i]);
    }

    rota->prox = NULL;
    return rota;
}

void inserir_aeronave_lista_pelo_fim(dados_aeronaves_t **lista, dados_aeronaves_t *nova_aeronave)
{
    if (nova_aeronave == NULL) return;
    if (*lista == NULL) {
        *lista = nova_aeronave;
    } else {
        dados_aeronaves_t *ultimo = *lista;
        while (ultimo->prox != NULL) ultimo = ultimo->prox;
        ultimo->prox = nova_aeronave;
    }
}

void inserir_rota_lista_pelo_fim(dados_rotas_t **lista, dados_rotas_t *nova_rota)
{
    if (nova_rota == NULL) return;
    if (*lista == NULL) {
        *lista = nova_rota;
    } else {
        dados_rotas_t *ultimo = *lista;
        while (ultimo->prox != NULL) ultimo = ultimo->prox;
        ultimo->prox = nova_rota;
    }
}

dados_aeronaves_t *localizar_aeronave_por_id(int id_aeronave, dados_aeronaves_t *lista)
{
   if(lista == NULL) return NULL;
   if(lista->id_aeronave == id_aeronave) return lista;
   return localizar_aeronave_por_id(id_aeronave, lista->prox);
}

void alterar_status_aeronave(dados_aeronaves_t **lista_aeronaves)
{
    int id_escolhido, novo_status;
    dados_aeronaves_t *aeronave = NULL;

    printf("ALTERAR STATUS DA AERONAVE\n");
    printf("Digite o ID da aeronave: \n");
    scanf("%i", &id_escolhido);
    while (getchar() != '\n');

    aeronave = localizar_aeronave_por_id(id_escolhido, *lista_aeronaves);
    if(!aeronave) {
        printf("Aeronave não encontrada!\n");
        mensagem("Pressione ENTER para continuar!");
        return;
    }

    printf("Digite o novo status(1 - Em operação ou 2- Em manutenção): ");
    scanf("%i", &novo_status);
    while (getchar() != '\n');

    if((status_t)novo_status == MANUTENCAO && aeronave->status != MANUTENCAO) {
        aeronave->qtd_manutencoes++;
        printf("Aeronave entrou em manutenção pela %iª vez.\n", aeronave->qtd_manutencoes);
    }

    aeronave->status = (status_t)novo_status;
    printf("Status da aeronave ID: %i alterado para %s.\n", id_escolhido, 
          (aeronave->status == OPERACAO) ? "EM OPERAÇÃO" : "EM MANUTENÇÃO");
    mensagem("Pressione ENTER para continuar!");
}