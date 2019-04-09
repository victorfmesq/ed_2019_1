#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;


template <class Elem>
struct Vector{ // toda struct em C++ eh uma classe publica
    Elem * data; // criamos um atributo DATA(dados) do tipo Elem uma classe que recebe os elementos do vector
    int size; // tamano do vector
    int capacity; // capacidade do vector

    //contrutor
    Vector(int cap){
        this->size = 0;
        this->capacity = cap;
        this->data = new Elem[cap];
    }
    // destrutdor
    ~Vector(){
        delete[] this->data;
    }
    // Metodos
    void resize(int new_capacity){ // realoca a capacidade do Vector
        this->data = (Elem*) realloc(this->data, new_capacity * sizeof(int)); //atribuimos à data deste objeto um Realloc. convertemos o tipo do realoc com (Elem*)
        this->capacity = new_capacity; // a capacidade do objeto recebe a nova capacidade
        if(new_capacity < this->size)
            this->size = new_capacity; // tamanho recebe nova capacidade
    }

    void push_back(Elem value){ // coloca elementos no final de Vector
        if(this->size == this->capacity){ // se o tamanho for igual a capacidade
            if(this->size == 0) // se o tamanho do vetor for 0
                resize(1); // tamanho agora sera 1
            else
                resize(this->capacity * 2); // duplica a capacidade
        }
        this->data[this->size] = value; // nosso Vector na ultima fosição livre recebe o valor
        this->size++; // incrementamos o tamanho
    }

    void pop_back() { // remove o ultimo elemento do Vector
        if(this->size > 0)
            this->size--;
    }

    void show() { // mostra o Vector
        printf("%02d/%02d [ ", this->size, this->capacity); // mostra o tamanho e a capacidade do Vector
        for(int i = 0; i < this->size; i++){
            cout << this->data[i] << " "; // mostra na tela 
        }
        printf("]\n");
    }

    void insert(int index, int value){ // insere um elemento no meio do Vector
        if((index < 0) || (index > this->size)) // se index for menor que 0 OU maior que o temanho de vector 
            return; 

        if(this->capacity == this->size) // se a capacidade == tamanho de Vector
            this->resize(this->capacity * 2); // duplique a capacidade

        for(int i = this->size; i >= index; i--) // decremente de size ate index
            this->data[i + 1] = this->data[i]; // desloque todos os elementos no intervalo uma casa para direita

        this->data[index] = value; // insira o valor na posição escolhida 
        this->size++; // incremente o tamanho
    }

    void remove(int index){ // Remove o valor de um indice qualquer
        for(int i = index; i < this->size - 1; i++){ // incrementa de index ate size - 1 pq vector comeca em 0
            this->data[i] = this->data[i + 1]; // desloca todos os elem no intervalo uma casa para esquerda(engole o valor que esta no index)
        }
        this->size -= 1; // decrementa o tamanho
    }

    void remove_all(int value){ // remove de Vector todos os elemento que tem value
        for(int i = this->size - 1; i >= 0; i--){ // decrementa de tamanho até 0 buscando elementos
            if(this->data[i] == value) // se algum elemento em data for igual a value
                this->remove(i); // remova este elemento
        }
    }

    void bubble_sort(){
        int aux; // variavel auxiliar
        for(int j = 0; j < this->size; j++){
            for(int i = 0; i < this->size - 1; i++){ // busc ate size - 2 pq size - 1 eh o outimo elemento entao se o indice chegar nele ele compararia com o prox q n existe
                if(this->data[i] > this->data[i + 1]){
                    aux = this->data[i];
                    this->data[i] = this->data[i + 1];
                    this->data[i + 1] = aux;
                }
            }
        }
    }

    // ver o codigo do david de insertion
    void insertion_sort(){
        int aux = 0;
        for(int i = 1; i < this->size; i++){ // onde quero posicionar o elemento
            int j = i;
            while(j > 0 && this->data[j - 1] < this->data[j]){
                aux = this->data[j];
                this->data[j] = this->data[j - 1];
                this->data[j - 1] = aux;
                j--;
            }
        }

    }

    /*void quick_sort(int * a, int left, int right){
        int aux;
        int l = left;
        int r = right;
        int * vec = a[(left + right) / 2];

        while(left <= right){
            while((vec[l] < vec) && (l < right)){
                l++;
            }
            while((vec[r] > vec) && (r > left)){
                r--;
            }
            if(l <= r){
                aux = vec[l];
                vec[l] = vec[r];
                vec[r] = aux;
                l++;
                r--;
            }
        }
        if(r > left){
            quick_sort(a, left, r);
        }
        if(l < right){
            quick_sort(a, l, right);
        }
    }
    */
};

#include <sstream> // stringstream

int main(){

    Vector<int> vec(0); // criando vector que implementamos c/ 0 elem
    // INICIO DO LACO INFINITO
    while(true){
        string line; 
        string cmd;  // vai receber um comando no terminal p executar uma funcao
        getline(cin, line); // le da entrada padrão e coloca em LINE
        stringstream ui(line); // cria um fluxo baseado em line pegando a primeira palavra da linha(puxa apenas uma unica informação)
        ui >> cmd; // primeiro comando(cmd) é a primeira coisa que tirarmos do fluxo
        if(cmd == "end") // se comando for "end" sai do laço
            break;
        else if(cmd == "add"){ // se comando for "add" 
            int value;
            // cria um laço para enquanto houver entradas. EX: add 1 2 3 4 6 5 2 3 (...)
            while(ui >> value){ // para add um valor e precisar tirar esse dalor da ui (user imput)
                vec.push_back(value); // o valor no fim do vector
            }
        }else if(cmd == "show"){ //se comando for show
            vec.show(); // mostra o vetor
        }else if(cmd == "bubble"){
                vec.bubble_sort();
        }else if(cmd == "insertion"){
                vec.insertion_sort();
        //}else if(cmd == "quick"){
        //        vec.quick_sort(vec.data, 0, vec.size - 1);
        }else{
            cout << "Fail: comando invalido\n"; // se n for nenhum comando registrado
        }
    }
}