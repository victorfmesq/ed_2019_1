#include "xpaint.h"

void tree(int x, int y, float ang, int tamanho, float espessura){
    float raio = 5;
    int cx = x + tamanho;
    int cy = y + tamanho;

    if(tamanho < 10){ // a recursão para quando tamanho do traço for menor que 10
        xs_color((XColor){xm_rand(0, 255), xm_rand(0, 255), xm_rand(0, 255)}); // cria cor
        xd_filled_circle(cx, cy, raio);
        return;
    }
    int xf = x + tamanho * xm_cos(ang); // segundo ponto X da reta >> multiplica pelo angulo p reta mudar de direção
    int yf = y - tamanho * xm_sin(ang); // segundo ponto X da reta >> multiplica pelo angulo p reta mudar de direção

    //xs_color((XColor){xm_rand(0, 255), xm_rand(0, 255), xm_rand(0, 255)});// cria a cor
    xs_color((XColor){0, 100, 0}); // cria cor
    xd_thick_line(x, y, xf, yf, espessura); // cria uma linha grossa
    x_step("tree"); //salva o arquivo, mas permite ao usuário controlar os estados

    tree(xf, yf, ang - xm_rand(10, 30), tamanho - xm_rand(5, 30), espessura - 0.5);
    tree(xf, yf, ang + xm_rand(10, 30), tamanho - xm_rand(5, 30), espessura - 0.5);
    //tree(xf, yf, ang - 30, tamanho - 30);
    //tree(xf, yf, ang + 30, tamanho - 30);   
}

int main(){
    int largura = 1920;
    int altura = 1800;

    x_open(largura, altura);  // cria uma janela de tamanho largura x altura
    x_clear(BLACK); // preenche a janela de preto

    float ang = 90; // define um angulo
    // dimensoes da reta para formar a arvore
    int x = largura / 2;
    int y = altura - 10;
    float tamanho = 200; // tamanho da arvore
    float espessura = 5;
    

    tree(x, y, ang, tamanho, espessura);// chamada recursiva
    x_save("tree");// salva o arquivo com nome tree
    x_close();// fecha janela criada
    return 0;
}