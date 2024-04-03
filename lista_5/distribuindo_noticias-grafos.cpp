#include <iostream>
using namespace std;

int abs(int num){
    if (num < 0){
        return -num;
    }else{
        return num;
    }
}

int find(int i, int *parents){

    // confere se o pai do elemento é ele mesmo
    if (parents[i] < 0){
        return i;
    }else {
        // encontrando o pai de i
        int result = find(parents[i], parents);
        parents[i] = result;
        return result;
    }
}

void unionsets(int i, int j, int *parents){
    // encontrando os representantes de i e j
    int irep, jrep;

    irep = find(i, parents);
    jrep = find(j, parents);

    if ((parents[irep] == parents[jrep]) && (irep != jrep)){
        // caso ambos sejam do mesmo tamanho
        parents[irep] = parents[irep] + parents[jrep];
        parents[jrep] = irep;

    }else if (parents[irep] < parents[jrep]){
        // caso a árvpre de i seja maior
        parents[irep] = parents[irep] + parents[jrep];
        parents[jrep] = irep;
    }else if (parents[irep] > parents[jrep]){
        // caso a árvore de j seja maior
        parents[jrep] = parents[jrep] + parents[irep];
        parents[irep] = jrep;
    }
    
}

int main(){
    // recebendo infos iniciais
    int num_users, conections, user_1, user_2;
    cin >> num_users >> conections;

    // construindo array de parents p/ union-find
    int *parents = new int[num_users + 1]; 
    for (int i = 0; i <= num_users; ++i){
        parents[i] = -1;
    }

    // implementando conexões
    for (int i = 0; i < conections; ++i){
        cin >> user_1 >> user_2;
        unionsets(user_1,user_2,parents);
    }

    // printando usuários que saberiam da notícia
    for (int i = 1; i <= num_users; ++i){
        if (i < num_users){
            cout << abs(parents[find(i, parents)]) << " "; 
        }else{
            cout << abs(parents[find(i, parents)]) << endl;
        }
    }

    delete[] parents;
    return 0;
}