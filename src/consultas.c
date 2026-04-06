#include "../include/consultas.h"
#include "../include/utils.h"
#include "../include/relatorios.h"
#include "../include/cadastros.h"
#include "../include/types.h"
#include "../include/menus.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

long long converter_para_long_comparativo(int dia, int mes, int ano, int hora, int min) {
    return (long long)ano * 100000000LL + 
           (long long)mes * 1000000LL + 
           (long long)dia * 10000LL + 
           (long long)hora * 100LL + 
           (long long)min;
}

void buscar_aeronave_por_prefixo(dados_aeronaves_t *lista)
{
    char buscar_prefixo[STR_SIZE];
    int encontrou = FALSE;
    dados_aeronaves_t *atual = lista;

    printf(".....BUSCAR AERONAVE POR PREFIXO.....\n");
    printf("Digite o prefixo (matricula)........: ");
    fgets(buscar_prefixo, STR_SIZE, stdin);
    remover_enter(buscar_prefixo);
    to_upper_string(buscar_prefixo);

    while(atual != NULL){
        if(strcmp(atual->matricula, buscar_prefixo) == 0){ 
            mostrar_dados_aeronaves(atual, stdout);
            encontrou = TRUE;
            break;
        }
        atual = atual->prox;
    }

    if(encontrou == FALSE){
        printf(" Nenhuma aeronave encontrada com o prefixo informado.\n");
    }

    mensagem("Pressione ENTER para continuar.");
}

void listar_aeronaves_por_fabricante(dados_aeronaves_t *lista)
{
    char buscar_fabricante[STR_SIZE];
    int encontrou = FALSE;
    dados_aeronaves_t *atual = lista;

    printf("....LISTAR AERONAVE POR FABRICANTE...\n");
    printf("Digite o nome do fabricante.........: ");
    fgets(buscar_fabricante, STR_SIZE, stdin);
    remover_enter(buscar_fabricante);
    to_upper_string(buscar_fabricante);

    printf("\n Aeronaves do fabricante %s:\n", buscar_fabricante);

    while(atual != NULL){
        if(strcmp(atual->fabricante, buscar_fabricante) == 0){
            mostrar_dados_aeronaves(atual, stdout);
            encontrou = TRUE;
        }
        atual = atual->prox;
    }

    if(encontrou == FALSE){
        printf(" Nenhuma aeronave encontrada para este fabricante.\n");
    }

    mensagem("Pressione ENTER para continuar.");
}

void listar_aeronaves_por_tipo(dados_aeronaves_t *lista)
{
    int tipo_escolhido;
    int encontrou = FALSE;
    dados_aeronaves_t *atual = lista;

    printf(".......LISTAR AERONAVE POR TIPO......\n");
    printf("Tipo (1- CARGA | 2- PASSAGEIRO).....: ");
    scanf("%i", &tipo_escolhido);
    while (getchar() != '\n');

    if(tipo_escolhido != CARGA && tipo_escolhido != PASSAGEIRO) {
        printf("\n Erro: Tipo de aeronave invalido.\n");
        mensagem("Pressione ENTER para continuar.");
        return;
    }

    if(tipo_escolhido == CARGA){
        printf("\n Aeronaves de carga:\n");
    }
    else {
        printf("\n Aeronaves de passageiros:\n");
    }

    while(atual != NULL) {
        if(atual->tipo == (tipo_aeronave_t)tipo_escolhido){
            mostrar_dados_aeronaves(atual, stdout);
            encontrou = TRUE;
        }
        atual = atual->prox;
    }

    if(encontrou == FALSE){
        printf(" Nenhuma aeronave encontrada para o tipo informado.\n");
    }

    mensagem("Pressione ENTER para continuar.");
}

void listar_aeronaves_por_modelo(dados_aeronaves_t *lista)
{
    char buscar_modelo[STR_SIZE];
    int encontrou = FALSE;
    dados_aeronaves_t *atual = lista;

    printf("......BUSCAR AERONAVE POR MODELO.....\n");
    printf("Digite o modelo da aeronave.........: ");
    fgets(buscar_modelo, STR_SIZE, stdin);
    remover_enter(buscar_modelo);
    to_upper_string(buscar_modelo);

    printf("\n Aeronaves do modelo %s:\n", buscar_modelo);

    while(atual != NULL){
        if(strcmp(atual->modelo, buscar_modelo) == 0){
            mostrar_dados_aeronaves(atual, stdout);
            encontrou = TRUE;
        }
        atual = atual->prox;
    }

    if(encontrou == FALSE){
        printf(" Nenhuma aeronave encontrada para este modelo.\n");
    }

    mensagem("Pressione ENTER para continuar.");
}

void listar_aeronaves_por_fabricacao(dados_aeronaves_t *lista)
{
    int buscar_ano;
    int encontrou = FALSE;
    dados_aeronaves_t *atual = lista;

    printf("...LISTAR POR ANO DE FABRICACAO.....\n");
    printf("Digite o ano de fabricacao..........: ");
    scanf("%i", &buscar_ano);
    while(getchar() != '\n');

    printf("\n Aeronaves fabricadas no ano %i:\n", buscar_ano);

    while(atual != NULL){
        if(atual->ano_fabricacao == buscar_ano){
            mostrar_dados_aeronaves(atual, stdout);
            encontrou = TRUE;
        }
        atual = atual->prox;
    }

    if(encontrou == FALSE){
        printf(" Nenhuma aeronave fabricada no ano informado.\n");
    }

    mensagem("Pressione ENTER para continuar.");
}

void listar_aeronaves_por_situacao(dados_aeronaves_t *lista)
{
    int situacao_escolhida;
    int encontrou = FALSE;
    dados_aeronaves_t *atual = lista;

    printf(".....LISTAR AERONAVE POR SITUACAO....\n");
    printf("Status (1- OPERACAO | 2- MANUTENCAO): ");
    scanf("%i", &situacao_escolhida);
    while (getchar() != '\n');

    if(situacao_escolhida != OPERACAO && situacao_escolhida != MANUTENCAO) {
        printf("\n Erro: Situacao invalida.\n");
        mensagem("Pressione ENTER para continuar.");
        return;
    }

    if(situacao_escolhida == OPERACAO){
        printf("\n Aeronaves em operacao:\n");
    }
    else {
        printf("\n Aeronaves em manutencao:\n");
    }

    while(atual != NULL) {
        if(atual->status == (status_t)situacao_escolhida){
            mostrar_dados_aeronaves(atual, stdout);
            encontrou = TRUE;
        }
        atual = atual->prox;
    }

    if(encontrou == FALSE){
        printf(" Nenhuma aeronave encontrada nesta situacao.\n");
    }

    mensagem("Pressione ENTER para continuar.");
}

void consultar_rota_por_data(dados_rotas_t *lista)
{
    data_t buscar_data;
    int encontrou = FALSE;
    dados_rotas_t *atual = lista;

    printf(".......CONSULTAR ROTA POR DATA.......\n");
    printf("Digite a data (dd/mm/aaaa)..........: ");
    scanf("%i/%i/%i", &buscar_data.dia, &buscar_data.mes, &buscar_data.ano);
    getchar();

    printf("\n Rotas para o dia %02i/%02i/%i:\n", buscar_data.dia, buscar_data.mes, buscar_data.ano);

    while(atual != NULL){
        if(atual->data_e_hora.dia == buscar_data.dia &&
           atual->data_e_hora.mes == buscar_data.mes &&
           atual->data_e_hora.ano == buscar_data.ano){
                mostrar_dados_rotas(atual, stdout);
                encontrou = TRUE;
            }
        atual = atual->prox;
    }

    if(encontrou == FALSE){
        printf(" Nenhuma rota localizada para esta data.\n");
    }

    mensagem("Pressione ENTER para continuar.");
}

void consultar_rota_por_origem(dados_rotas_t *lista)
{
    char buscar_origem[STR_SIZE];
    int encontrou = FALSE;
    dados_rotas_t *atual = lista;

    printf("......CONSULTAR ROTA POR ORIGEM......\n");
    printf("Digite o local de origem............: ");
    fgets(buscar_origem, STR_SIZE, stdin);
    remover_enter(buscar_origem);
    to_upper_string(buscar_origem);

    while(atual != NULL){
        if(strcmp(atual->local_partida, buscar_origem) == 0){
            mostrar_dados_rotas(atual, stdout);
            encontrou = TRUE;
        }
        atual = atual->prox;
    }

    if (encontrou == FALSE){
        printf(" Nenhuma rota encontrada para a origem informada.\n");
    }

    mensagem("Pressione ENTER para continuar.");
}

void consultar_rota_por_destino(dados_rotas_t *lista)
{
    char buscar_destino[STR_SIZE];
    int encontrou = FALSE;
    dados_rotas_t *atual = lista;

    printf(".....CONSULTAR ROTA POR DESTINO......\n");
    printf("Digite o local de destino...........: ");
    fgets(buscar_destino, STR_SIZE, stdin);
    remover_enter(buscar_destino);
    to_upper_string(buscar_destino);

    printf("\n Rotas com destino em %s:\n", buscar_destino);

    while(atual != NULL){
        if(strcmp(atual->local_destino, buscar_destino) == 0){
            mostrar_dados_rotas(atual, stdout);
            encontrou = TRUE;
        }
        atual = atual->prox;
    }

    if (encontrou == FALSE){
        printf(" Nenhuma rota encontrada para o destino informado.\n");
    }

    mensagem("Pressione ENTER para continuar.");
}

void listar_rotas_por_status_temporal(dados_rotas_t *lista_rotas)
{
    if (lista_rotas == NULL) {
        printf(" Nenhuma rota cadastrada.\n");
        mensagem("Pressione ENTER para continuar.");
        return;
    }

    time_t t = time(NULL);
    struct tm data_atual = *localtime(&t);
    
    long long agora = converter_para_long_comparativo(
        data_atual.tm_mday, 
        data_atual.tm_mon + 1, 
        data_atual.tm_year + 1900, 
        data_atual.tm_hour, 
        data_atual.tm_min
    );

    printf("\n.......ROTAS FINALIZADAS........\n");
    dados_rotas_t *atual = lista_rotas;
    int encontrou_passado = FALSE;
    while (atual) {
        long long data_rota = converter_para_long_comparativo(
            atual->data_e_hora.dia, atual->data_e_hora.mes, atual->data_e_hora.ano,
            atual->data_e_hora.hora, atual->data_e_hora.min
        );
        if (data_rota < agora) {
            printf(" [%02i/%02i/%i %02i:%02i] Codigo: %i | %s -> %s\n",
                   atual->data_e_hora.dia, atual->data_e_hora.mes, atual->data_e_hora.ano,
                   atual->data_e_hora.hora, atual->data_e_hora.min,
                   atual->codigo_rota, atual->local_partida, atual->local_destino);
            encontrou_passado = TRUE;
        }
        atual = atual->prox;
    }
    if (!encontrou_passado) printf(" Nenhuma rota finalizada encontrada.\n");

    printf("\n........PROXIMAS ROTAS.........\n");
    atual = lista_rotas;
    int encontrou_futuro = FALSE;
    while (atual) {
        long long data_rota = converter_para_long_comparativo(
            atual->data_e_hora.dia, atual->data_e_hora.mes, atual->data_e_hora.ano,
            atual->data_e_hora.hora, atual->data_e_hora.min
        );
        if (data_rota >= agora) {
            printf(" [%02i/%02i/%i %02i:%02i] Codigo: %i | %s -> %s\n",
                   atual->data_e_hora.dia, atual->data_e_hora.mes, atual->data_e_hora.ano,
                   atual->data_e_hora.hora, atual->data_e_hora.min,
                   atual->codigo_rota, atual->local_partida, atual->local_destino);
            encontrou_futuro = TRUE;
        }
        atual = atual->prox;
    }
    if (!encontrou_futuro) printf(" Nenhuma rota agendada encontrada.\n");
    
    mensagem("\nPressione ENTER para voltar.");
}

double consumototal_combustivel_por_data(dados_rotas_t *lista)
{
    data_t data_inicio, data_fim;
    double consumo_total = 0.0;
    dados_rotas_t *atual = lista;
    int encontrou_voo = FALSE;

    printf(".......CONSUMO DE COMBUSTIVEL........\n");
    printf("Data inicial (dd/mm/aaaa)...........: ");
    scanf("%i/%i/%i", &data_inicio.dia, &data_inicio.mes, &data_inicio.ano);
    while(getchar() != '\n');

    printf("Data final (dd/mm/aaaa).............: ");
    scanf("%i/%i/%i", &data_fim.dia, &data_fim.mes, &data_fim.ano);
    while(getchar() != '\n');

    long long inicio = converter_para_long_comparativo(data_inicio.dia, data_inicio.mes, data_inicio.ano, 0, 0);
    long long fim = converter_para_long_comparativo(data_fim.dia, data_fim.mes, data_fim.ano, 23, 59);

    while(atual != NULL){
        long long data_v = converter_para_long_comparativo(atual->data_e_hora.dia, atual->data_e_hora.mes, atual->data_e_hora.ano, atual->data_e_hora.hora, atual->data_e_hora.min);
        
        if(data_v >= inicio && data_v <= fim) {
            consumo_total += atual->combustivel_voo;
            encontrou_voo = TRUE;
        }
        atual = atual->prox;
    }

    printf("\n.......RESULTADO DO CONSUMO.........\n");
    printf(" Periodo: %02i/%02i/%i a %02i/%02i/%i\n", data_inicio.dia, data_inicio.mes, data_inicio.ano, data_fim.dia, data_fim.mes, data_fim.ano);
    
    if(encontrou_voo == FALSE) {
        printf(" Nenhuma rota encontrada para o periodo.\n");
    } else {
        printf(" Consumo total: %.2f Litros\n", consumo_total);
    }

    mensagem("Pressione ENTER para continuar.");
    return consumo_total;
}

double percentual_voos_por_aeronaves(dados_rotas_t *lista_rotas, dados_aeronaves_t *lista_aeronaves)
{
    int id_procurado;
    int voos_aeronave = 0;
    int total_rotas = 0;
    dados_rotas_t *atual_rota = lista_rotas;
    dados_aeronaves_t *aeronave_buscada = NULL;
    double percentual = 0.0;

    printf(".....PERCENTUAL DE VOOS POR AERONAVE....\n");

    if(lista_rotas == NULL){
        printf(" Nenhuma rota cadastrada para o calculo.\n");
        mensagem("Pressione ENTER para continuar.");
        return 0.0;
    }

    printf("Digite o ID da aeronave...........: ");
    scanf("%i", &id_procurado);
    while(getchar() != '\n');

    aeronave_buscada = localizar_aeronave_por_id(id_procurado, lista_aeronaves);
    if(aeronave_buscada == NULL){
        printf(" Erro: Aeronave ID %i nao encontrada.\n", id_procurado);
        mensagem("Pressione ENTER para continuar.");
        return 0.0;
    }

    while(atual_rota != NULL) {
        total_rotas++;
        if(atual_rota->id_aeronave == id_procurado){
            voos_aeronave++;
        }
        atual_rota = atual_rota->prox;
    }
    
    if (total_rotas != 0) {
        percentual = (double)voos_aeronave / total_rotas * 100.0;
    }

    printf("\n.......RESULTADO DO PERCENTUAL.......\n");
    printf(" Aeronave: %s (ID %i)\n", aeronave_buscada->matricula, id_procurado);
    printf(" Total de rotas do sistema: %i\n", total_rotas);
    printf(" Voos desta aeronave: %i\n", voos_aeronave);
    printf(" Participacao no total: %.2f%%\n", percentual);

    mensagem("Pressione ENTER para continuar.");
    return percentual;
}

double percentual_voos_em_destino_por_intervalo_datas(dados_rotas_t *lista)
{
    data_t data_inicio, data_fim;
    char destino_procurado[STR_SIZE];
    int voos_no_intervalo = 0;
    int voos_no_destino = 0;
    dados_rotas_t *atual = lista;

    printf(".......PERCENTUAL POR DESTINO........\n");

    if(lista == NULL){
        printf(" Nenhuma rota cadastrada para o calculo.\n");
        mensagem("Pressione ENTER para continuar.");
        return 0.0;
    }

    printf("Data inicial (dd/mm/aaaa)...........: ");
    scanf("%i/%i/%i", &data_inicio.dia, &data_inicio.mes, &data_inicio.ano);
    while(getchar () != '\n');

    printf("Data final (dd/mm/aaaa).............: ");
    scanf("%i/%i/%i", &data_fim.dia, &data_fim.mes, &data_fim.ano);
    while(getchar() != '\n');

    long long inicio = converter_para_long_comparativo(data_inicio.dia, data_inicio.mes, data_inicio.ano, 0, 0);
    long long fim = converter_para_long_comparativo(data_fim.dia, data_fim.mes, data_fim.ano, 23, 59);

    printf("Destino para verificacao............: ");
    fgets(destino_procurado, STR_SIZE, stdin);
    remover_enter(destino_procurado);
    to_upper_string(destino_procurado);

    while(atual != NULL){
        long long data_v = converter_para_long_comparativo(atual->data_e_hora.dia, atual->data_e_hora.mes, atual->data_e_hora.ano, atual->data_e_hora.hora, atual->data_e_hora.min);

        if(data_v >= inicio && data_v <= fim){
            voos_no_intervalo++;
            if(strcmp(atual->local_destino, destino_procurado) == 0){
                voos_no_destino++;
            }
        }
        atual = atual->prox;
    }

    if(voos_no_intervalo == 0){
        printf(" Nenhuma rota encontrada no periodo.\n");
        mensagem("Pressione ENTER para continuar.");
        return 0.0;
    }

    double percentual = (double)voos_no_destino / voos_no_intervalo * 100.0;

    printf("\n.......RESULTADO DO PERCENTUAL.......\n");
    printf(" Periodo: %02i/%02i/%i a %02i/%02i/%i\n", data_inicio.dia, data_inicio.mes, data_inicio.ano, data_fim.dia, data_fim.mes, data_fim.ano);
    printf(" Total de voos no periodo: %i\n", voos_no_intervalo);
    printf(" Voos para %s: %i\n", destino_procurado, voos_no_destino);
    printf(" Participacao do destino: %.2f%%\n", percentual);

    mensagem("Pressione ENTER para continuar.");
    return percentual;
}

int buscar_qtd_manutencao_por_aeronaves(dados_aeronaves_t *lista)
{
    int id_procurado;
    dados_aeronaves_t *aeronave = NULL;

    printf(".......HISTORICO DE MANUTENCAO.......\n");
    printf("Digite o ID da aeronave...........: ");
    scanf("%i", &id_procurado);
    while (getchar() != '\n');

    aeronave = localizar_aeronave_por_id(id_procurado, lista);

    if(aeronave != NULL){
        printf("\n Aeronave: %s (ID %i)\n", aeronave->matricula, id_procurado);
        printf(" Total de manutencoes registradas: %i\n", aeronave->qtd_manutencoes);
    }
    else{
        printf(" Erro: Aeronave nao encontrada.\n");
    }

    mensagem("Pressione ENTER para continuar.");
    return (aeronave != NULL) ? aeronave->qtd_manutencoes : 0;
}