#include <stdio.h>
#include <stdlib.h> //srand, rand
#include <time.h> // time()

const char TREE = '#';
const char FIRE = 'o';
const char EMPTY = '.';
const char BURN = 'X';

//left, up, right, down
int deltaL[] = {0, -1, 0, 1};
int deltaC[] = {-1, 0, 1, 0};
int lados = sizeof(deltaL)/sizeof(int); 
//int delta[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

void shuffle(int vet[], int size){ // troca a ordem dos comandos => Up, Down, Left, Right
    for(int i = 0; i < size; i++){
        int esc = rand() % size; // randomiza um valor
        int temp = vet[i]; // faz a troca
        vet[i] = vet[esc];
        vet[esc] = temp;
    }
}

void show(int nl, int nc, char mat[nl][nc]){ // printa na tela a matriz
    for(int l = 0; l < nl; l++){
        for(int c = 0; c < nc; c++){
            printf("%c", mat[l][c]);
        }
        puts("");
    }
    printf("\n");
    getchar();
}

int tocar_fogo(int nl, int nc, char mat[nl][nc], int l, int c){
    if((l < 0) || (l >= nl) || (c < 0) || (c >= nc)) // se l || c forem espaços fora da matriz (invalidos).
        return 0;
    if(mat[l][c] != TREE) // se a posição escolhido nao for arvore.
        return 0;
    mat[l][c] = FIRE; // queima a arvore.
    show(nl, nc, mat); // mostrar matriz.
    int cont = 1; /*criação do contador para saber quantas arvores serão queimadas no final do processo.
                    Inicia com 1 pois a recursao vai somar 1 sempre que a arvore se queimar.*/
    int neib[] = {0, 1, 2, 3}; // eh uma vetor auxiliar de vizinhos para randomizar de forma mais legivel a direção do fogo.
    shuffle(neib, lados); // troca a ordem em que o fogo se espalha.
    // Laço para queimar de forma aleatoria e guardar a qtd de arvores queimadas.
    for(int v = 0; v < lados; v++){
        int i = neib[v]; // variavel auxiliar para facilitar a leitura do codigo.
        cont += tocar_fogo(nl, nc, mat, l + deltaL[i], c + deltaC[i]);
    }
    mat[l][c] = BURN; // Marca como queimada apos DESEMPILHAR as funções.
    show(nl, nc, mat); // mostra o vetor
    //cont += tocar_fogo(nl, nc, mat, l + 0, c - 1); //left
    //cont += tocar_fogo(nl, nc, mat, l - 1, c + 0); //up
    //cont += tocar_fogo(nl, nc, mat, l + 0, c + 1); //right
    //cont += tocar_fogo(nl, nc, mat, l + 1, c + 0); //down
    
    return cont; // retorna a qtd de avores queimadas.
}

int main(){
    srand(time(NULL));
    int nl = 0; //numero linhas
    int nc = 0; // numero colunas
    puts("Digite dimensoes da matriz");
    scanf("%d %d", &nl, &nc);
    puts("Digite a porcentagem de arvores 0-100");
    int porc_tree = 0; // para gerar umas porcentgem x de arvores
    scanf("%d", &porc_tree);
    char mat[nl][nc]; // matriz
    // preencher a matriz
    for(int l = 0; l < nl; l++){
        for(int c = 0; c < nc; c++){
            if(rand() % 101 <= porc_tree) // randomiza um numero 
                mat[l][c] = TREE; // se <= porcentagem escolhida ele vira arvore
            else
                mat[l][c] = EMPTY;// se nao vira espaço
        }
    }
    show(nl, nc, mat); // mostra matriz
    puts("Onde queres incendiar?");
    int l = 0; // linha do inicio do incendio
    int c = 0; // coluna do incio do incendio
    scanf("%d %d", &l, &c);
    
    int total = tocar_fogo(nl, nc, mat, l, c); // retorna a qtd de arvores queimadas
    show(nl, nc, mat); // mostra vetor
    printf("total do estrago: %d\n", total); // mostra qtd de arvores queimadas
}
