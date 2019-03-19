#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define LADOS 4
// define get_neibs(l, c) {{l, c - 1}, {l - 1, c}, {l, c + 1}, {l + 1, c}}
const char WALL = '#';
const char HOLE = ' ';

typedef struct{ // Coordena atual do lab
    int l;
    int c;
} Pos;

typedef struct{
    Pos vet[LADOS];
} Neibs;

Neibs get_neibs(int l, int c){
    Neibs neibs = {{{l, c - 1}, {l - 1, c}, {l, c + 1}, {l + 1, c}}};
    return neibs;
}

void shuffle(Pos vet[], int size){
    for(int i = 0; i < size; i++){
        int esc = rand() % size;
        Pos aux = vet[i];
        vet[i] = vet[esc];
        vet[esc] = aux;
    }

}

void show(int nline, int ncol, char lab[nline][ncol]){
    for(int l = 0; l < nline; l++){
        for(int c = 0; c < ncol; c++){
            if(lab[l][c] == '#')
                printf("#");
            else
                printf("%c", lab[l][c]);
        }
        puts("");
    }
}

bool equals(int nline, int ncol, char lab[nline][ncol], int l, int c, char value){
    if((l < 0) || (l >= nline) || (c < 0) || (c >= ncol))
        return false;
    return lab[l][c] == value;
}

bool eh_furavel(int nline, int ncol, char lab[nline][ncol], int l, int c){
    if(!equals(nline, ncol, lab, l, c, '#'))
        return false;
    int cont = 0;
    Neibs neibs = get_neibs(l, c);
    for(int i = 0; i < 4; i++)
        if(equals(nline, ncol, lab, neibs.vet[i].l, neibs.vet[i].c, '#'))
            cont++;
    if(cont < 3)
        return false;
    return true;
}

void crash(int nline, int ncol, char lab[nline][ncol], int l, int c){
    // se existir
    if(!eh_furavel(nline, ncol, lab, l, c))
        return;
    lab[l][c] = HOLE; // quebra parede
    //show(nline, ncol, lab);
    Neibs neibs = get_neibs(l, c); //obtem vizinhos
    shuffle(neibs.vet, LADOS); // randomiza a direção
    for(int i = 0; i < LADOS; i++)
        crash(nline, ncol, lab, neibs.vet[i].l, neibs.vet[i].c); // chamada recursiva
   // show(nline, ncol, lab);
}

int main(){
    srand(time(NULL));
    int nline = 0;
    int ncol = 0;
    puts("Escreva o tamanho do labirinto:\n N_linhas | N_colunas");
    scanf("%d%d", &nline, &ncol);
    char lab[nline][ncol];
    // lendo / contruindo labirinto
    for(int l = 0; l < nline; l++){
        for(int c = 0; c < ncol; c++){
            lab[l][c] = WALL;
        }
    }
    // printando matriz
    show(nline, ncol, lab);
    int l = 0; //coordenada X
    int c = 0; //coordenada Y
    puts("Escreva as coordenadas do inicios do labirinto");
    scanf("%d %d", &l, &c);

    crash(nline, ncol, lab, l, c);
    show(nline, ncol, lab);
   // recursão

    return 0;
}