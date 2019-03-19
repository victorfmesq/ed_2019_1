#include <stdio.h>
#include <stdbool.h>

void put_neg_in_vet(int proximo, int size);

const int MORTO = 0; // global q aplica 0 p diferenciar os vivos dos mortos
const int DIRETA = 1;// p criar a condição p saber qual lado vai morrer 
const int INVERSA = -1;

void preencher_vetor(int vet[], int size){
    for(int i = 0; i < size; i++) // preenchendo o vetor
        vet[i] = i + 1;
}

int buscar_escolhido(int vet[], int size, int escolhido){
    if(escolhido > 0){ // fase direta
        int parada = escolhido; // positivo
        int proximo = (escolhido + 1) % size;
        while(parada != 0){
            if(vet[proximo] == MORTO){
                proximo = (proximo + 1) % size;
                parada++; // incremeta para ele nao considerar o espaco c 0
            }
            proximo = (proximo + 1) % size;
            parada--;
        }
    return proximo;
    }else{ // fase inversa
        int parada = escolhido; // negativo
        int proximo = (escolhido + size - 1) % size;
        while(parada != 0){
            if(vet[proximo] == MORTO){
                proximo = (proximo + size - 1) % size;
                parada--; // decremeta para ele nao considerar o espaco c 0
            }
            proximo = (proximo + size - 1);
            parada++; // incrementa p/ chegar a 0;
        }
    return proximo; 
    }   
}
void put_neg_in_vet(int proximo, int size){
    while(proximo < 0){
            proximo = proximo + size;
    }
}

int buscar_vivo(int vet[], int size, int escolhido){
    if(escolhido > 0){
        int proximo = (escolhido + 1) % size;
        while(vet[proximo] == MORTO){
            proximo = (proximo + 1) % size;
        }
        return proximo;
    }else{
        int proximo = (escolhido + size - 1) % size;
        while(vet[proximo] == MORTO){
            proximo = (proximo +size - 1) % size;
        }
        return proximo;
    }
}

void escolher_fase(int vet[], int size, int fase){
    if(fase == 1){ // fase direta
        for(int i = 0; i < size; i++){
            if(vet[i] % 2 == 0)
                vet[i] = vet[i] * -1;
        }
    }else{ // fase inversa
        for(int i = 0; i < size; i++){
            if(vet[i] % 2 != 0)
                vet[i] = vet[i] * -1;
        }
    }
}

void mostrar_vetor(int vet[], int size, int escolhido){
    printf("[");
    int primeiro = true; // boleano so pra controlar o espaço antes do primeiro
    for(int i = 0; i < size; i++){
        if(vet[i] != MORTO){
            if(vet[i] != (escolhido + 1)){ // se n for escolhido | +1 é para o esc ordenar com os numeros do vetor ja que antes eu subtrai 1 pra igualar com os indices.
                if(primeiro)
                    primeiro = false;
                else
                    printf(" ");
                printf("%d", vet[i]);
            }else{ // se for escolhido
                if(primeiro)
                    primeiro = false;
                else
                    printf(" ");
                printf("%dE", vet[i]);
            }
        }
    }
    printf("]\n");
}

int main(){

    int n_pes = 0; // tamanho do vetor
    int esc = 0; // escolhido
    int fase = 0; // Se o jogo comeca com negativos ou positivos
    puts("Digite, nessa ordem, o numero de:\n Pessoas / escolhido / fase");
    scanf("%d %d %d", &n_pes, &esc, &fase);
    esc = esc - 1; // alinha o numero do escolhido com numero do indice

    int vet[n_pes];
    preencher_vetor(vet, n_pes);
    escolher_fase(vet, n_pes, fase);
    
    int qtd_round = n_pes; // controle de loop.
    while(qtd_round--){ // laço roda enquanto puder decrementar o qtd_round
        mostrar_vetor(vet, n_pes, esc);
        //int saltos = vet[esc] > 0 ? vet[esc] : -vet[esc];
        int decaptado = buscar_vivo(vet, n_pes, esc);
        vet[decaptado] = MORTO;
        esc = decaptado; 
        //for(int i = 0; i < saltos; i++)
            esc = buscar_escolhido(vet, n_pes, esc);
    }
    return 0;
}