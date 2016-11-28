/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CasamentoPadrao.h
 * Author: vinicius
 *
 * Created on November 21, 2016, 8:49 PM
 */

#ifndef CASAMENTOPADRAO_H
#define CASAMENTOPADRAO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
    
#define ALFA_TAM 256

    int max(int a, int b);
    int getTamanhoString(char *str);
    int CasamentoPadrao_BMH(char *texto, char *padrao);
    int CasamentoPadrao_ForcaBruta(char *texto, char *padrao);
    int CasamentoPadrao_KMP(char* texto, char* padrao);
    
    double Tempo_BMH(char *texto, char *padrao);
    double Tempo_ForcaBruta(char *texto, char *padrao);
    double Tempo_KMP(char *texto, char *padrao);
        
    int getNumeroPalavrasTexto(FILE *arqTexto);
    int getNumeroCaracteresTexto(FILE *arqTexto);
    
    struct timeval seed;

#ifdef __cplusplus
}
#endif

#endif /* CASAMENTOPADRAO_H */

