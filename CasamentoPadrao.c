#include "CasamentoPadrao.h"

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getTamanhoString(char *str) {
    int i = 0;
    if (str) {
        for (i = 0; str[i]; i++);
    }
    return i;
}

int getNumeroPalavrasTexto(FILE *arqTexto) {
    int k = 0;
    char palavra[20];

    fseek(arqTexto, 0, SEEK_SET);
    while (fscanf(arqTexto, "%s", palavra) != EOF)
        k++;

    return k;
}

int getNumeroCaracteresTexto(FILE *arqTexto) {
    int k = 0;

    fseek(arqTexto, 0, SEEK_SET);
    while (fgetc(arqTexto) != EOF)
        k++;

    return k;
}

int CasamentoPadrao_KMP(char* texto, char* padrao) {

    int tamanhoTexto = getTamanhoString(texto);
    int tamanhoPadrao = getTamanhoString(padrao);
    int *pi = (int*) malloc(sizeof (int)*tamanhoPadrao);

    pi[0] = 0;
    int k = 0, casamento = 0;
    int q, i;

    for (q = 2; q <= tamanhoPadrao; q++) {
        while (k > 0 && padrao[k] != padrao[q - 1])
            k = pi[k - 1];
        if (padrao[k] == padrao[q - 1])
            k++;
        pi[q - 1] = k;
    }
    q = 0;
    for (i = 0; i < tamanhoTexto; i++) {
        while (q > 0 && padrao[q] != texto[i])
            q = pi[q - 1];
        if (padrao[q] == texto[i])
            q++;
        if (q == tamanhoPadrao) // Casamento !
        {
            casamento++;
            q = pi[q - 1];
        }
    }

    return casamento;
}

/*** Algoritmo Boyer-Moore-Horspool ***/
int CasamentoPadrao_BMH(char * texto, char *padrao) {

    int i, casamento = 0;
    int tamanhoTexto = getTamanhoString(texto);
    int tamanhoPadrao = getTamanhoString(padrao);

    if ((tamanhoTexto == 0) || (tamanhoPadrao == 0)) {
        fprintf(stderr, "Texto e/ou padrao vazio(s)\n");
        return -1;
    }

    int badCharHtable[ALFA_TAM];

    for (i = 0; i < ALFA_TAM; i++) {
        badCharHtable[i] = -1;
    }

    for (i = 0; i < tamanhoPadrao; i++) {
        badCharHtable[(int) padrao[i]] = i;
    }

    int shift = 0;

    while (shift <= tamanhoTexto - tamanhoPadrao) {
        int index = tamanhoPadrao - 1;

        while ((index >= 0) && (padrao[index] == texto[shift + index]))
            index--;

        if (index < 0) {
            casamento++;

            if (shift + tamanhoPadrao < tamanhoTexto) {
                shift += tamanhoPadrao - badCharHtable[texto[shift + tamanhoPadrao]];
            } else {
                shift += 1;
            }
        } else {
            shift += max(1, index - badCharHtable[texto[shift + index]]);
        }
    }
    return casamento;
}

int CasamentoPadrao_ForcaBruta(char *texto, char *padrao) {
    int i, j;
    int casamento = 0;

    int tamanhoTexto = getTamanhoString(texto);
    int tamanhoPadrao = getTamanhoString(padrao);

    for (i = 0; i <= tamanhoTexto - tamanhoPadrao; i++) {

        for (j = 0; j < tamanhoPadrao; j++) {
            if (padrao[j] != texto[i + j])
                break;
        }

        if (j == tamanhoPadrao) //Se existe casamento incrementa
            casamento++;
    }
    return casamento;
}

double Tempo_ForcaBruta(char *texto, char *padrao) {

    int i, j;
    int casamento = 0;
    double tempoTotal;
    clock_t ticks[2] = {0.0, 0.0};

    int tamanhoTexto = getTamanhoString(texto);
    int tamanhoPadrao = getTamanhoString(padrao);

    ticks[0] = clock(); // Desconsiderando o tempo do calculo do tamanho das strings

    for (i = 0; i <= tamanhoTexto - tamanhoPadrao; i++) {

        for (j = 0; j < tamanhoPadrao; j++) {
            if (padrao[j] != texto[i + j])
                break;
        }

        if (j == tamanhoPadrao) //Se existe casamento incrementa
            casamento++;
    }

    ticks[1] = clock();
    tempoTotal = (double) (ticks[1] - ticks[0]) * 1000.0 / CLOCKS_PER_SEC;

    return tempoTotal;
}

double Tempo_BMH(char *texto, char *padrao) {

    int i, casamento = 0;
    int tamanhoTexto = getTamanhoString(texto);
    int tamanhoPadrao = getTamanhoString(padrao);

    double tempoTotal;
    clock_t ticks[2] = {0.0, 0.0};

    ticks[0] = clock(); // Desconsiderando o tempo do calculo do tamanho das strings

    if ((tamanhoTexto == 0) || (tamanhoPadrao == 0)) {
        fprintf(stderr, "Texto e/ou padrao vazio(s)\n");
        return -1;
    }

    int badCharHtable[ALFA_TAM];

    for (i = 0; i < ALFA_TAM; i++) {
        badCharHtable[i] = -1;
    }

    for (i = 0; i < tamanhoPadrao; i++) {
        badCharHtable[(int) padrao[i]] = i;
    }

    int shift = 0;

    while (shift <= tamanhoTexto - tamanhoPadrao) {
        int index = tamanhoPadrao - 1;

        while ((index >= 0) && (padrao[index] == texto[shift + index]))
            index--;

        if (index < 0) { //Se encontrou um casamento, incrementa a variavel
            casamento++;

            //Se ainda há caracteres suficientes para uma nova comparação
            if (shift + tamanhoPadrao < tamanhoTexto) {
                shift += tamanhoPadrao - badCharHtable[texto[shift + tamanhoPadrao]];
            } else {
                shift += 1;
            }
        } else {
            shift += max(1, index - badCharHtable[texto[shift + index]]);
        }
    }

    ticks[1] = clock();
    tempoTotal = (double) (ticks[1] - ticks[0]) * 1000.0 / CLOCKS_PER_SEC;

    return tempoTotal;
}

double Tempo_KMP(char *texto, char *padrao) {

    int tamanhoTexto = getTamanhoString(texto);
    int tamanhoPadrao = getTamanhoString(padrao);
    int *pi = (int*) malloc(sizeof (int)*tamanhoPadrao);

    pi[0] = 0;
    int k = 0, casamento = 0;
    int q, i;

    double tempoTotal;
    clock_t ticks[2] = {0.0, 0.0};

    ticks[0] = clock(); // Desconsiderando o tempo do calculo do tamanho das strings

    for (q = 2; q <= tamanhoPadrao; q++) {
        while (k > 0 && padrao[k] != padrao[q - 1])
            k = pi[k - 1];
        if (padrao[k] == padrao[q - 1])
            k++;
        pi[q - 1] = k;
    }
    q = 0;
    for (i = 0; i < tamanhoTexto; i++) {
        while (q > 0 && padrao[q] != texto[i])
            q = pi[q - 1];
        if (padrao[q] == texto[i])
            q++;
        if (q == tamanhoPadrao) // Casamento !
        {
            casamento++;
            q = pi[q - 1];
        }
    }

    ticks[1] = clock();
    tempoTotal = (double) (ticks[1] - ticks[0]) * 1000.0 / CLOCKS_PER_SEC;

    return tempoTotal;
}