#include <iostream>
using namespace std;

struct Edge{
    int src, dest, weight;

    Edge() : src(-1), dest(-1), weight(-1) {}
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
};

class DSU{
    int* parent;
    int* rank;

    public:
        DSU(int n){
            parent = new int[n];
            rank = new int[n];

            for (int i = 0; i < n; ++i){
                parent[i] = -1;
                rank[i] = -1;
            }
        }

        // função find
        int find(int i){
            
            if(parent[i] == -1){
                return i;
            }

            return parent[i] = find(parent[i]);
        }

        // função union
        void unite(int i, int j){

            int repi = find(i);
            int repj = find(j);

            if(repi != repj){

                if(rank[repi] < rank[repj]){

                    parent[repi] = repj;
                    rank[repj] += 1;

                }else if(rank[repi] > rank[repj]){

                    parent[repj] = repi;
                    rank[repi] += 1;

                }else{
                    parent[repj] = repi;
                    rank[repi] += 1;
                }
            }
        }
};

class MinHeap{
    private:
        Edge *heapArray;
        int capacity;
        int heapSize;

        int father(int i){

            return (i - 1)/2;
        }
        int leftChild(int i){

            return 2 * i + 1;
        }
        int rightChild(int i){

            return 2 * i + 2;
        }

        void heapify(int i){
            int l = leftChild(i);
            int r = rightChild(i);
            int smallest = i;

            if(l < heapSize && heapArray[l].weight < heapArray[i].weight){
                smallest = l;
            }
            if( r < heapSize && heapArray[r].weight < heapArray[smallest].weight){
                smallest = r;
            }
            if(smallest != i){

                Edge temp = heapArray[i];
                heapArray[i] = heapArray[smallest];
                heapArray[smallest] = temp;
                heapify(smallest);

            }
        }
    public:
        MinHeap(int cap){
            capacity = cap;
            heapSize = 0;
            heapArray = new Edge[capacity];
        }

        ~MinHeap(){
            delete[] heapArray;
        }

        void insert(Edge key){
            if(heapSize == capacity){
                return;
            }

            heapSize++;
            int i = heapSize -1;
            heapArray[i] = key;

            while(i != 0 && heapArray[father(i)].weight > heapArray[i].weight){
                Edge temp = heapArray[i];
                heapArray[i] = heapArray[father(i)];
                heapArray[father(i)] = temp;
                i = father(i);
            }
        }

        Edge extractMin(){
            if(heapSize <= 0){
                return Edge(-1, -1, -1);
            }
            if(heapSize == 1){
                heapSize--;
                return heapArray[0];
            }

            Edge root = heapArray[0];
            heapArray[0] = heapArray[heapSize - 1];
            heapSize--;
            heapify(0);

            return root;
        }
};

int main(){
    // recebendo infos iniciais
    int num_aeroportos, num_trechos, grafo_x, grafo_y, ver1, ver2, weight;
    int custo = 0;
    cin >> num_aeroportos >> num_trechos;

    DSU dsu(num_aeroportos);
    MinHeap minHeap(num_trechos);

    // recebendo as arestas e inserindo na heap
    for (int i = 0; i < num_trechos; ++i){
        cin >> ver1 >> ver2 >> weight;
        Edge aux(ver1, ver2, weight);
        minHeap.insert(aux);

    }

    for (int i = 0; i < num_trechos; ++i){

        Edge minEdge = minHeap.extractMin();
        ver1 = minEdge.src;
        ver2 = minEdge.dest;
        weight = minEdge.weight;

        if (dsu.find(ver1) != dsu.find(ver2)){
            dsu.unite(ver1, ver2);
            custo += weight;
        }
    }

    cout << custo << endl;

    return 0;
}