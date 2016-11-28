/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: vinicius
text *
 * Created on November 21, 2016, 6:09 PM
 */

#include "CasamentoPadrao.h"

/*
 * 
 */
int main(int argc, char** argv) {
    FILE *arq;
    
    double tempo_FB = 0.0;
    double tempo_BMH = 0.0;
    double tempo_KMP = 0.0;
    
    int casamentos = 0, i = 0;
    int opc, nExecucoes;

    char *texto;
    char nomeArquivo[20];
    char padrao[20];

    printf("Digite o nome do arquivo onde esta contido o texto que deseja pesquisar\n");
    scanf("%s", nomeArquivo);

    if (arq = fopen(nomeArquivo, "r")) {

        texto = (char*) malloc(sizeof (char)*getNumeroCaracteresTexto(arq)+1);
        fseek(arq, 0, SEEK_SET);

        while (!feof(arq)) {
            texto[i] = fgetc(arq);
            i++;
        }
        
        printf("Digite a palavra(padrao) pelo qual deseja buscar no texto\n");
        scanf("%s", padrao);

        printf("1- Pesquisar ocorrencias do padrao no texto | 2- #DEBUG - Pesquisar ocorrencias do padrao mostrando os tempos medio de cada algoritmo | 0- Sair\n");
        scanf("%d", &opc);

        switch (opc) {
            case 0:
                return (EXIT_SUCCESS);
                break;
            case 1:
                casamentos = CasamentoPadrao_BMH(texto, padrao);
                fprintf(stdout, "Algoritmo BMH:\nTexto: %s\n\nPadrao: %s\nCasamentos = %d\n\n", texto, padrao, casamentos);
                casamentos = 0;
                casamentos = CasamentoPadrao_ForcaBruta(texto, padrao);
                fprintf(stdout, "Algoritmo Força Bruta:\nTexto: %s\n\nPadrao: %s\nCasamentos = %d\n\n", texto, padrao, casamentos);
                casamentos = 0;
                casamentos = CasamentoPadrao_KMP(texto, padrao);
                fprintf(stdout, "Algoritmo KMP:\nTexto: %s\n\nPadrao: %s\nCasamentos = %d\n\n", texto, padrao, casamentos);
                break;
            case 2:
                printf("Quantas vezes deseja que os algoritmos sejam executados ?\n");
                scanf("%d", &nExecucoes);

                printf("\nO texto possui '%d' palavras e um total de '%d' caracteres\n", getNumeroPalavrasTexto(arq), getNumeroCaracteresTexto(arq));

                for (i = 0; i < nExecucoes; i++) {
                    tempo_FB += Tempo_ForcaBruta(texto, padrao);
                    tempo_BMH += Tempo_BMH(texto, padrao);
                    tempo_KMP += Tempo_KMP(texto, padrao);
                }

                printf("O resultados mostrados sao a media de tempo de execucao de %d execucoes sobre o mesmo texto\n\n", nExecucoes);

                fprintf(stdout, "Tempo medio algoritmo Força Bruta: %lf\n", tempo_FB / (double) nExecucoes);
                fprintf(stdout, "Tempo medio algoritmo BMH: %lf\n", tempo_BMH / (double) nExecucoes);
                fprintf(stdout, "Tempo medio algoritmo KMP: %lf\n\n", tempo_KMP / (double) nExecucoes);

                break;
            default:
                printf("Opcao Inexistente\n");
                break;
        }
    } else
        printf("Erro, arquivo nao encontrado !\n");

    free(texto);
    fclose(arq);
    
    return (EXIT_SUCCESS);
}

