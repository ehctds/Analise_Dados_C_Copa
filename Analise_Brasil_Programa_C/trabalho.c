#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef enum { false, true } bool; //Enum para utilizar valor bool dentro do código.

float media(float soma, int divisor){
    float media;
    media = soma / divisor;
    return media;
} //Função da média.

float desvio_padrao(float array[], int tam) {
    float soma = 0.0, media, desvio = 0.0;
    int i;
    for (i = 0; i < tam; ++i) {
        soma += array[i];
    }
    media = soma / tam;
    for (i = 0; i < tam; ++i) {
        desvio += pow(array[i] - media, 2);
    }
    return sqrt(desvio / tam);
} //Função do desvio padrão.

float variancia(float array[], int tam){
    float var;
    var = desvio_padrao(array,tam);
    var = pow(var,2);
    return var;
} //Função da variância.

int main(){
    
    FILE *arquivo = fopen("Brasil.csv","r");
    int contador=0, contador_token=0;
    char dadostring[20000];
    float valor=0;
    float media_valores, desvio_valores, variancia_valores;
    float soma_idades=0, soma_partidas_jogadas=0, soma_tempo_de_jogo=0;
    float array_idades[100],array_partidas[100],array_tempo[100];
    bool bool = false; //Bool começa falso para pular primeira linha do csv.


    if (arquivo != NULL){ //Verifica se o arquivo.csv foi aberto corretamente.
        printf("O arquivo foi aberto com sucesso\n");
    }
    else{
        printf("Erro ao abrir arquivo.\n");
        getchar();
        return 0;
    }

    while(fgets(dadostring,sizeof(dadostring),arquivo)){ //Lê as linhas do arquivo até o final e retornar NULL.
        char *token = strtok(dadostring, ","); //Quebra a string da linha em vários tokens, dividindo pela ",".
        if (bool == true){
            while(token != NULL) { //Enquanto tiverem tokens a serem analisados, vai entrar no loop.
                if(contador==2){
                    printf("JOGADOR: %s\n", token);
                }
                else if(contador==3){
                    printf("IDADE: %s\n", token);
                    valor = strtof(token,NULL); //Retorna token como float.
                    soma_idades += valor;
                    array_idades[contador_token] = valor;
                }
                else if(contador==4){
                    printf("PARTIDAS JOGADAS: %s\n", token);
                    valor = strtof(token,NULL);
                    soma_partidas_jogadas += valor;
                    array_partidas[contador_token] = valor;
                }
                else if(contador==5){
                    printf("TEMPO DE JOGO: %s\n", token);
                    valor = strtof(token,NULL);
                    soma_tempo_de_jogo += valor;
                    array_tempo[contador_token] = valor;
                }
                token = strtok(NULL, ","); //Pula para próximo token.
                contador++; //Contador que representa a linha atual no loop.
            }
            contador_token++; //Contador para armazenar o número de Jogadores.
        }
        bool = true; //Coloca bool como true para entrar no loop a partir da 2° linha do csv
        contador = 0; //Reseta o contador
    
    }
    int num;
    printf("DIGITE QUAL ANALISE VOCE QUER: 1 - IDADE, 2 - TEMPO DE JOGO, 3 - PARTIDAS JOGADAS, 4 - TODAS \n");
    scanf("%d",&num);
    bool = true;
    while(bool == true){ //Loop até usuário escolher opção correta.
        switch(num){ //Switch das opções de escolha do usuário.
            case 1: 
                media_valores = media(soma_idades,contador_token);
                desvio_valores = desvio_padrao(array_idades,contador_token);
                variancia_valores = variancia(array_idades,contador_token);
                printf("MEDIA DAS IDADES: %f\n", media_valores);
                printf("DESVIO PADRAO DAS IDADES: %f\n", desvio_valores);
                printf("VARIANCIA DAS IDADES: %f\n", variancia_valores);
                bool = false;
                break;
            case 2:
                media_valores = media(soma_tempo_de_jogo,contador_token);
                desvio_valores = desvio_padrao(array_tempo,contador_token);
                variancia_valores = variancia(array_tempo,contador_token);
                printf("MEDIA DO TEMPO DE JOGO: %f\n", media_valores);
                printf("DESVIO PADRAO DO TEMPO DE JOGO: %f\n", desvio_valores);
                printf("VARIANCIA DO TEMPO DE JOGO: %f\n", variancia_valores);
                bool = false;
                break;
            case 3:
                media_valores = media(soma_partidas_jogadas,contador_token);
                desvio_valores = desvio_padrao(array_partidas,contador_token);
                variancia_valores = variancia(array_partidas,contador_token);
                printf("MEDIA DAS PARTIDAS JOGADAS: %f\n", media_valores);
                printf("DESVIO PADRAO DAS PARTIDAS JOGADAS: %f\n", desvio_valores);
                printf("VARIANCIA DAS PARTIDAS JOGADAS: %f\n", variancia_valores);
                bool = false;
                break;
            case 4: 
                media_valores = media(soma_idades,contador_token);
                desvio_valores = desvio_padrao(array_idades,contador_token);
                variancia_valores = variancia(array_idades,contador_token);
                printf("MEDIA DAS IDADES: %f\n", media_valores);
                printf("DESVIO PADRAO DAS IDADES: %f\n", desvio_valores);
                printf("VARIANCIA DAS IDADES: %f\n\n", variancia_valores);
                bool = false;
                media_valores = media(soma_tempo_de_jogo,contador_token);
                desvio_valores = desvio_padrao(array_tempo,contador_token);
                variancia_valores = variancia(array_tempo,contador_token);
                printf("MEDIA DO TEMPO DE JOGO: %f\n", media_valores);
                printf("DESVIO PADRAO DO TEMPO DE JOGO: %f\n", desvio_valores);
                printf("VARIANCIA DO TEMPO DE JOGO: %f\n\n", variancia_valores);
                bool = false;
                media_valores = media(soma_partidas_jogadas,contador_token);
                desvio_valores = desvio_padrao(array_partidas,contador_token);
                variancia_valores = variancia(array_partidas,contador_token);
                printf("MEDIA DAS PARTIDAS JOGADAS: %f\n", media_valores);
                printf("DESVIO PADRAO DAS PARTIDAS JOGADAS: %f\n", desvio_valores);
                printf("VARIANCIA DAS PARTIDAS JOGADAS: %f\n\n", variancia_valores);
                bool = false;
                break;
            default:
                printf("VALOR INVALIDO, DIGITE UM VALOR VALIDO\n");
                scanf("%d",&num);
                break;
        }
    }

    fclose(arquivo); //Fecha arquivo.
    
}
