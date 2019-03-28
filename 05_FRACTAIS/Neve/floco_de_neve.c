#include "xpaint.h"

void floco(int x, int y, float ang, int tamanho, float espessura){

    if(tamanho < 5){ // a recursão para quando tamanho do traço for menor que 10
        return;
    }
    //int xf = x + tamanho * xm_cos(ang); // segundo ponto X da reta >> multiplica pelo angulo p reta mudar de direção
    //int yf = y - tamanho * xm_sin(ang); // segundo ponto X da reta >> multiplica pelo angulo p reta mudar de direção

    int xf = 0;
    int yf = 0;
    //xs_color((XColor){xm_rand(0, 255), xm_rand(0, 255), xm_rand(0, 255)});// cria a cor
    xs_color((XColor){255, 255, 255}); // cria cor
    for(int i = 0; i < 5; i++){
        xf = x + tamanho * xm_cos(ang); // segundo ponto X da reta >> multiplica pelo angulo p reta mudar de direção
        yf = y - tamanho * xm_sin(ang); // segundo ponto X da reta >> multiplica pelo angulo p reta mudar de direção
        
        xs_color((XColor){xm_rand(0, 255), xm_rand(0, 255), xm_rand(0, 255)});// cria a cor
       
        xd_thick_line(x, y, xf, yf, espessura); // cria uma linha grossa
        ang -= 72;
        
        for(int j = 0; j < 5; j++){
            floco(xf, yf, ang - 72, tamanho / 3, espessura );
        }
    }

    //x_step("floco"); //salva o arquivo, mas permite ao usuário controlar os estados
    //for(int i = 0; i < 5; i++){
    //    floco(xf, yf, ang - 72, tamanho - tamanho / 2, espessura );
    //}
}

int main(){
    int largura = 1920;
    int altura = 1800;

    XColor COR = (XColor){30,30,30};

    x_open(largura, altura);  // cria uma janela de tamanho largura x altura
    x_clear(COR); // preenche a janela de preto

    float ang = 270; // define um angulo
    // dimensoes da reta para formar o FLOCO
    int x = largura / 2;
    int y = altura / 2;
    float tamanho = 600; // tamanho da traço do floco
    float espessura = 5;
    

    floco(x, y, ang, tamanho, espessura);// chamada recursiva
    x_save("floco");// salva o arquivo com nome tree
    x_close();// fecha janela criada
    return 0;
}