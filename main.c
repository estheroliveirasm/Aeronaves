#include "./include/types.h"
#include "./include/menus.h"
#include "./include/cadastros.h"
#include "./include/relatorios.h"
#include "./include/consultas.h"
#include "./include/arquivos.h"
#include "./include/utils.h"
#include <stdio.h>
#include <string.h>

int main ()
{
    dados_aeronaves_t *lista_aeronaves = NULL;
    dados_rotas_t *lista_rotas = NULL;
    int opc_main, opc_sub, opc_sub_sub; 
    char nome_arq[STR_SIZE];
    
    ler_dados_aeronaves_bin(ARQUIVO_AERONAVES, &lista_aeronaves);
    ler_dados_rotas_bin(ARQUIVO_ROTAS, &lista_rotas);
    
    do { 
        opc_main = menu_principal();

        switch (opc_main) {
            case 1: 
                do {
                    opc_sub = menu_cadastro();
                    if(opc_sub == 1) {
                        dados_aeronaves_t *nova = nova_aeronave();
                        if(nova != NULL) {
                            inserir_aeronave_lista_pelo_fim(&lista_aeronaves, nova);
                            mensagem("Aeronave cadastrada com sucesso!");
                        }
                    } else if(opc_sub == 2) {
                        dados_rotas_t *nova = nova_rota(lista_aeronaves); 
                        if(nova != NULL){
                            inserir_rota_lista_pelo_fim(&lista_rotas, nova);
                            mensagem("Rota cadastrada com sucesso!");
                        }
                    }
                } while (opc_sub != 0);
                break;

            case 2:
                do {
                    opc_sub = menu_relatorios();
                    if (opc_sub != 0) {
                        limpar_tela();
                        switch (opc_sub) {
                            case 1: relatorio_aeronaves(lista_aeronaves, stdout); break;
                            case 2: relatorio_rotas(lista_rotas, stdout); break;
                            case 3: listar_rotas_maiornumero_passageiros(lista_rotas, stdout); break;
                            case 4: listar_rotas_menornumero_passageiros(lista_rotas, stdout); break;
                        }
                        mensagem("Pressione ENTER para voltar.");
                    }
                } while (opc_sub != 0);
                break;

            case 3: 
                do {
                    opc_sub = menu_escolha_consultas();
                    if(opc_sub == 1) { 
                        do {
                            opc_sub_sub = menu_consultas_aeronaves();
                            switch (opc_sub_sub) {
                                case 1: buscar_aeronave_por_prefixo(lista_aeronaves); break;
                                case 2: listar_aeronaves_por_fabricante(lista_aeronaves); break;
                                case 3: listar_aeronaves_por_tipo(lista_aeronaves); break;
                                case 4: listar_aeronaves_por_modelo(lista_aeronaves); break;
                                case 5: listar_aeronaves_por_fabricacao(lista_aeronaves); break;
                                case 6: listar_aeronaves_por_situacao(lista_aeronaves); break;
                            }
                            if(opc_sub_sub != 0) mensagem("Consulta finalizada.");
                        } while (opc_sub_sub != 0);
                    } 
                    else if (opc_sub == 2) {
                        do {
                            opc_sub_sub = menu_consultas_rotas();
                            switch (opc_sub_sub) {
                                case 1: consultar_rota_por_data(lista_rotas); break;
                                case 2: consultar_rota_por_origem(lista_rotas); break;
                                case 3: consultar_rota_por_destino(lista_rotas); break;
                                case 4: listar_rotas_por_status_temporal(lista_rotas); break;
                            }
                            if(opc_sub_sub != 0) mensagem("Consulta finalizada.");
                        } while (opc_sub_sub != 0);
                    }
                    else if (opc_sub == 3) {
                        do {
                            opc_sub_sub = menu_consultas_estatisticas();
                            switch (opc_sub_sub) {
                                case 1: consumototal_combustivel_por_data(lista_rotas); break;
                                case 2: percentual_voos_por_aeronaves(lista_rotas, lista_aeronaves); break;
                                case 3: percentual_voos_em_destino_por_intervalo_datas(lista_rotas); break;
                            }
                            if(opc_sub_sub != 0) mensagem("Estatisticas geradas com sucesso!");
                        } while (opc_sub_sub != 0);
                    }
                } while (opc_sub != 0);
                break;

            case 4:
                alterar_status_aeronave(&lista_aeronaves);
                mensagem("Status alterado!");
                break;

            case 5: 
                buscar_qtd_manutencao_por_aeronaves(lista_aeronaves);
                mensagem("Busca concluida!");
                break;

            case 6: 
                do {
                    opc_sub = menu_arquivos();
                    if (opc_sub == 1) {
                        salvar_dados_aeronaves_bin(lista_aeronaves, ARQUIVO_AERONAVES);
                        salvar_dados_rotas_bin(lista_rotas, ARQUIVO_ROTAS);
                        mensagem("Dados salvos em arquivos binarios!");
                    } 
                    else if (opc_sub == 2) { 
                        do {
                            opc_sub_sub = menu_exportar_aeronaves();
                            if (opc_sub_sub >= 1 && opc_sub_sub <= 3) {
                                printf("Digite o nome do arquivo (sem extensao): ");
                                fgets(nome_arq, STR_SIZE, stdin);
                                remover_enter(nome_arq);

                                if (opc_sub_sub == 1) { strcat(nome_arq, ".txt"); exportar_aeronaves_txt(lista_aeronaves, nome_arq); }
                                else if (opc_sub_sub == 2) { strcat(nome_arq, ".csv"); exportar_aeronaves_csv(lista_aeronaves, nome_arq); }
                                else if (opc_sub_sub == 3) { strcat(nome_arq, ".html"); exportar_aeronaves_html(lista_aeronaves, nome_arq); }
                                mensagem("Exportacao de aeronaves concluida!");
                            }
                        } while (opc_sub_sub != 0);
                    } 
                    else if (opc_sub == 3) { 
                        do {
                            opc_sub_sub = menu_exportar_rotas();
                            if (opc_sub_sub >= 1 && opc_sub_sub <= 3) {
                                printf("Digite o nome do arquivo (sem extensao): ");
                                fgets(nome_arq, STR_SIZE, stdin);
                                remover_enter(nome_arq);

                                if (opc_sub_sub == 1) { strcat(nome_arq, ".txt"); exportar_rotas_txt(lista_rotas, nome_arq); }
                                else if (opc_sub_sub == 2) { strcat(nome_arq, ".csv"); exportar_rotas_csv(lista_rotas, nome_arq); }
                                else if (opc_sub_sub == 3) { strcat(nome_arq, ".html"); exportar_rotas_html(lista_rotas, nome_arq); }
                                mensagem("Exportacao de rotas concluida!");
                            }
                        } while (opc_sub_sub != 0);
                    }
                } while (opc_sub != 0);
                break;

            case 0: 
                printf("Saindo do programa e salvando dados...\n");
                salvar_dados_aeronaves_bin(lista_aeronaves, ARQUIVO_AERONAVES);
                salvar_dados_rotas_bin(lista_rotas, ARQUIVO_ROTAS);
                printf("Dados salvos em arquivos binários.");
                break;
        }

    } while (opc_main != 0);

    return 0;
}