#include "../include/menus.h"
#include "../include/utils.h"
#include "../include/types.h"
#include <stdio.h>

int menu_principal()
{
    int opc;
    limpar_tela();
    printf("..........MENU PRINCIPAL..........\n");
    printf(" 1. Cadastro (Aeronave ou Rota)\n");
    printf(" 2. Relatorios\n");
    printf(" 3. Buscas e Consultas\n");
    printf(" 4. Alterar status da aeronave\n");
    printf(" 5. Historico de manutencoes\n");
    printf(" 6. Arquivos e Exportacao\n");
    printf(" 0. Sair do programa\n");
    printf(" Opcao: ");
    scanf("%d", &opc);
    getchar();
    return opc;
}

int menu_cadastro()
{
    int opc;
    limpar_tela();
    printf("............CADASTRO.............\n");
    printf(" 1. Cadastrar nova aeronave\n");
    printf(" 2. Cadastrar nova rota\n");
    printf(" 0. Voltar ao menu principal\n");
    printf(" Opcao: ");
    scanf("%d", &opc);
    getchar();
    return opc;
}

int menu_relatorios()
{
    int opc;
    limpar_tela();
    printf("...........RELATORIOS............\n");
    printf(" 1. Listar todas as aeronaves\n");
    printf(" 2. Listar todas as rotas\n");
    printf(" 3. Rotas com mais passageiros\n");
    printf(" 4. Rotas com menos passageiros\n");
    printf(" 0. Voltar ao menu principal\n");
    printf(" Opcao: ");
    scanf("%d", &opc);
    getchar();
    return opc;
}

int menu_escolha_consultas()
{
    int opc;
    limpar_tela();
    printf(".......BUSCAS E CONSULTAS........\n");
    printf(" 1. Aeronaves\n");
    printf(" 2. Rotas\n");
    printf(" 3. Estatisticas\n");
    printf(" 0. Voltar ao menu principal\n");
    printf(" Opcao: ");
    scanf("%d", &opc);
    getchar();
    return opc;
}

int menu_consultas_aeronaves()
{
    int opc;
    limpar_tela();
    printf("...........AERONAVES.............\n");
    printf(" 1. Buscar por prefixo (Matricula)\n");
    printf(" 2. Listar por fabricante\n");
    printf(" 3. Listar por tipo\n");
    printf(" 4. Listar por modelo\n");
    printf(" 5. Listar por ano de fabricacao\n");
    printf(" 6. Listar por situacao atual\n");
    printf(" 0. Voltar ao menu anterior\n");
    printf(" Opcao: ");
    scanf("%d", &opc);
    getchar();
    return opc;
}

int menu_consultas_rotas()
{
    int opc;
    limpar_tela();
    printf("..............ROTAS..............\n");
    printf(" 1. Consultar rota por data\n");
    printf(" 2. Consultar rota por origem\n");
    printf(" 3. Consultar rota por destino\n");
    printf(" 4. Status temporal (Passadas/Futuras)\n");
    printf(" 0. Voltar ao menu anterior\n");
    printf(" Opcao: ");
    scanf("%d", &opc);
    getchar();
    return opc;
}

int menu_consultas_estatisticas()
{
    int opc;
    limpar_tela();
    printf("..........ESTATISTICAS...........\n");
    printf(" 1. Consumo total de combustivel\n");
    printf(" 2. Percentual de voos por aeronave\n");
    printf(" 3. Percentual de voos por destino\n");
    printf(" 0. Voltar ao menu anterior\n");
    printf(" Opcao: ");
    scanf("%d", &opc);
    getchar();
    return opc;
}

int menu_arquivos()
{
    int opc;
    limpar_tela();
    printf("......ARQUIVOS E EXPORTACAO......\n");
    printf(" 1. Salvar dados (Binario)\n");
    printf(" 2. Exportar Aeronaves (TXT/CSV/HTML)\n");
    printf(" 3. Exportar Rotas (TXT/CSV/HTML)\n");
    printf(" 0. Voltar ao menu anterior\n");
    printf(" Opcao: ");
    scanf("%d", &opc);
    getchar();
    return opc;
}

int menu_exportar_aeronaves()
{
    int opc;
    limpar_tela();
    printf(".......EXPORTAR AERONAVES........\n");
    printf(" 1. Formato TXT\n");
    printf(" 2. Formato CSV\n");
    printf(" 3. Formato HTML\n");
    printf(" 0. Voltar ao menu anterior\n");
    printf(" Opcao: ");
    scanf("%d", &opc);
    getchar();
    return opc;
}

int menu_exportar_rotas()
{
    int opc;
    limpar_tela();
    printf(".........EXPORTAR ROTAS.........\n");
    printf(" 1. Formato TXT\n");
    printf(" 2. Formato CSV\n");
    printf(" 3. Formato HTML\n");
    printf(" 0. Voltar ao menu anterior\n");
    printf(" Opcao: ");
    scanf("%d", &opc);
    getchar();
    return opc;
}