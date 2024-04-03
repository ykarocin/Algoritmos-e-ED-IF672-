#include <iostream>
using namespace std;

// struct da linked list
struct Node{
    int data;
    Node* next;

    Node(int value){
        data = value;
        next = nullptr;
    }
};

// função para adicionar os elementos na frente da lista
void add(Node*& head, int value){
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
}

void print(Node* head){
    // conferindo se a lista é vazia
    if(head == nullptr){
        cout << "Lista Vazia" << endl;
    }else{
        // imprimindo os elementos
        while(head != nullptr){
            if (head->next == nullptr){
                cout << head->data << " " << endl;
                
            }else{
                cout << head->data << " ";
            }

            head = head->next;
            
        }
    }
    
}

// dfs

void dfs(Node* grafo[], int vertice, int antecessor[], bool marcado[], int caminho[], int num_vertices){
    marcado[vertice] = true;
    bool aux = true;
    int contador = 0;

    while (aux == true){
                if (caminho[contador] == -1){
                    caminho[contador] = vertice;
                    aux = false;
                }else{
                    ++contador;
                    if (contador == num_vertices){
                        aux == false;
                    }
                }
            }

    Node* current = grafo[vertice];
    while(current != nullptr){
        if(marcado[current->data] == false){

            antecessor[current->data] = vertice;
            dfs(grafo, current->data, antecessor, marcado, caminho, num_vertices);
        }
        aux = true;
        current = current->next;
    }
}

void buscaProfundidade(Node* grafo[], int num_vertices){
    bool marcado[num_vertices];
    int antecessor[num_vertices];
    int caminho[num_vertices];

    // inicializando listas
    for (int i = 0; i < num_vertices; ++i){
        marcado[i] = false;
        antecessor[i] = -1;
        caminho[i] = -1;
    }

    dfs(grafo, 0, antecessor, marcado, caminho, num_vertices);

    for (int i = 0; i < num_vertices; ++i){
        if (caminho[i] != -1){
            cout << caminho[i] << " ";
        }
    }
}



int main()
{   
    // recebendo as infos
    int num_vertices, ver_1, ver_2 = -1;
    int condicao = 1;
    cin >> num_vertices;

    // criando o grafo e lista auxiliar
    Node* grafo[num_vertices] = {nullptr};

    while(condicao != 0){
        cin >> ver_1 >> ver_2 >> condicao;

        // criando as conexões
        add(grafo[ver_1], ver_2);
        add(grafo[ver_2], ver_1);
    }

    // imprimindo lista de adjacências
    for(int i = 0; i < num_vertices; ++i){
        cout << i << ": ";
        print(grafo[i]);

    }

    // dfs
    cout << endl;
    buscaProfundidade(grafo, num_vertices);
    


    return 0;
}