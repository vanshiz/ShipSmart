#include <iostream>
#include<windows.h>
#include<climits>
#include<queue>
using namespace std;
#define A 10



//Vector STL implementation
template <typename T>
class EVector {
private:
    T* data;
    int size;
    int capacity;

public:
    EVector() {
        this->data=nullptr;
        this->size=0;
        this->capacity=0;
    }


    EVector(const EVector& newData){
        size=newData.size;
        capacity=newData.capacity;
        data = new T[capacity];
        copy(newData.data, newData.data + size, data);
    }

    EVector& operator=(const EVector& newData) {
        if (this != &newData) {
            delete[] data;
            size = newData.size;
            capacity = newData.capacity;
            data = new T[capacity];
            copy(newData.data, newData.data + size, data);
        }
        return *this;
    }
    
    void push_back(const T& value) {
        if (size == capacity) {
            if (capacity == 0) {
                capacity = 1;
            } else {
                capacity =capacity * 2;
            }
            T* newData = new T[capacity];
            copy(data, data + size, newData);
            delete[] data;
            data = newData;
        }
        data[size] = value;
        size++;
    }

    T& operator[](int index) {
        if (index >= size) {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }

    T* begin() const {
        return data;
    }

    T* end() const {
        return data + size;
    }

    bool empty() const {
        return size == 0;
    }
    
    int getSize() const {
        return size;
    }
};

//Map STL implementation

template <typename K, typename V>
class EMap {
private:
    EVector<std::pair<K, V>> data;

public:
 
    void insert(const K& key, const V& value) {
        auto it =custom_find_if(data.begin(), data.end(),
            [&](const auto& pair) { return pair.first == key; });
        if (it != data.end()) {
            it->second = value;
        } else {
            data.push_back(std::make_pair(key, value));
        }
    }


    bool get(const K& key, V& value) const {
        auto it =custom_find_if(data.begin(), data.end(),
            [&](const auto& pair) { return pair.first == key; });
        if (it != data.end()) {
            value = it->second;
            return true;
        } else {
            return false;
        }
    }

    bool empty() const {
        return data.empty();
    }

    
    size_t size() const {
        return data.getSize();
    }

    
    auto begin() {
        return data.begin();
    }

    auto end() {
        return data.end();
    }

    V& operator[](const K& key) {
    // Check if the key already exists
        auto it = custom_find_if(data.begin(), data.end(),
            [&](const auto& pair) { return pair.first == key; });

        if (it != data.end()) {
            // Key already exists, return its associated value
            return it->second;
        } else {
            // Key not found, insert a new pair with an empty value
            data.push_back(std::make_pair(key, V{}));

            // Return the reference to the newly inserted value
            return data[data.getSize() - 1].second;
        }
    }

};


//Queue STL implementation

class Node {
public:
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = NULL;
    }
};

class Queue {
private:
    Node* front;
    Node* rear;

public:
    Queue(){
        this->front=nullptr;
        this->rear=nullptr;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    void enqueue(int data) {
        Node* newNode = new Node(data);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    int dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty" <<endl;
            return -1; 
        } else {
            int data = front->data;
            Node* temp = front;
            front = front->next;
            delete temp;

            if (front == nullptr) {
                rear = nullptr;
            }
            return data;
        }
    }

    int peek() {
        if (isEmpty()) {
            cout << "Queue is empty" <<endl;
            return -1; 
        } else {
            return front->data;
        }
    }
};

//some functions
template <typename InputIterator, typename UnaryPredicate>
InputIterator custom_find_if(InputIterator first, InputIterator last, UnaryPredicate pred) {
    while (first != last) {
        if (pred(*first)) {
            return first;
        }
        ++first;
    }
    return last;
}

template <typename F>
void custom_reverse(F begin, F end) {
    while (begin != end && begin != --end) {
        iter_swap(begin++, end);
    }
}


//graph class implementation

class graph{
    public:
    int vertices,edges;
    EMap<string,string>parent;
    EMap<string,EVector<pair<string,int>>>graph_list;

    graph(int v,int e){
        this->vertices=v;
        this->edges=e;
    }

    
    void add_neighbour(const string& source, const string& destination, int distance) {
        graph_list[source].push_back({destination, distance});
        graph_list[destination].push_back({source, distance});
    }

    

    void print_graph(){
        for(auto element_list: graph_list){
            string node = element_list.first;
            cout<<" "<<node<<" -> ";
            for(auto neighbours: graph_list[node]){
                cout <<" (" << neighbours.first<<" - "<<neighbours.second << "), ";
            }
                cout<<endl;
        }
    }

    void find_shortest_path(string source,bool funCall=false){
        priority_queue< pair<int,string> , vector<pair<int,string>> ,
        greater<pair<int,string>> > queue_;
            queue_.push({0, source});

            EMap<string , bool>visited;
            EMap<string , int > distance;
            for(auto elements : graph_list ){
                distance[elements.first] = INT_MAX;
            }
            distance[source] = 0 ;
            parent[source] = source;
            while(!queue_.empty()){
                auto node_pair = queue_.top();
                queue_.pop();
                string current_node = node_pair.second;
                int node_dist = node_pair.first;

                for(auto neighbour_pair: graph_list[ current_node ]){

                    string neighbour = neighbour_pair.first;
                    int neighbour_dist = neighbour_pair.second;
                    if(!visited[neighbour] && (distance[neighbour] > node_dist + neighbour_dist) ){
                        distance[neighbour] =  node_dist + neighbour_dist;
                        parent[neighbour] = current_node;
                        queue_.push({ node_dist + neighbour_dist , neighbour});
                    }
                }
            }

            if(funCall){
                cout<<" shortest path to all nodes : \n";
                for(auto nodePair:distance){
                    cout<<" "<<nodePair.first<<" -> "<<nodePair.second<<endl;
                }
            }
    }


    void get_path(string source , string destination){
        string indermediate_node = destination;
        EVector<string>path;
        
        while(parent[indermediate_node] != indermediate_node){
            path.push_back(indermediate_node);
            indermediate_node = parent[indermediate_node];
        }

        path.push_back(indermediate_node);

        custom_reverse(path.begin(),path.end());

        cout<<"\n Required path :" << path.getSize() <<endl; ;

        for(int i= 0 ;i < path.getSize() ;i++){
                if(i == (path.getSize() - 1 ))cout<<path[i];
                else cout<<path[i]<<" -> ";
        }
        cout<<endl;
    }


    void get_path_from_two_nodes(){
            string source,destination;
            cout << " Enter source and destination: ";
            cin.ignore();
            getline(cin,source);
            getline(cin,destination);
            find_shortest_path(source);
            get_path(source,destination);
    }



    bool bfs(int rGraph[A][A], int s, int t, int parent[])
    {
        bool visited[A]={0};
        // memset(visited, 0, sizeof(visited));

        Queue q;
        q.enqueue(s);
        visited[s] = true;
        parent[s] = -1;

        while (!q.isEmpty()) {
            int u = q.peek();
            q.dequeue();

            for (int v = 0; v < A; v++) {
                if (visited[v] == false && rGraph[u][v] > 0) {

                    if (v == t) {
                        parent[v] = u;
                        return true;
                    }
                    q.enqueue(v);
                    parent[v] = u;
                    visited[v] = true;
                }
            }
        }
        return false;
    }



    pair <int,int> city_helper(string source,string destination)
    {
        pair< int,int> ans;
        int s,t;

        //sources
        if(source=="Ahmedabad")
        {
            s = 0;
        }
        if(source=="Srinager")
        {
            s = 1;
        }
        if(source=="Delhi")
        {
            s = 2;
        }
        if(source=="Goa")
        {
            s = 3;
        }
        if(source=="Mumbai")
        {
            s = 4;
        }
        if(source=="Lucknow")
        {
            s = 5;
        }
        if(source=="Chennai")
        {
            s = 6;
        }
        if(source=="Noida")
        {
            s = 7;
        }
        if(source=="Kolkata")
        {
            s = 8;
        }
        if(source=="Bangalore")
        {
            s = 9;
        }

        //destinations
        if(destination=="Ahmedabad")
        {
            t = 0;
        }
        if(destination=="Srinager")
        {
            t = 1;
        }
        if(destination=="Delhi")
        {
            t = 2;
        }
        if(destination=="Goa")
        {
            t = 3;
        }
        if(destination=="Mumbai")
        {
            t = 4;
        }
        if(destination=="Lucknow")
        {
            t = 5;
        }
        if(destination=="Chennai")
        {
            t = 6;
        }
        if(destination=="Noida")
        {
            t = 7;
        }
        if(destination=="Kolkata")
        {
            t = 8;
        }
        if(destination=="Bangalore")
        {
            t = 9;
        }
        ans.first = s;
        ans.second = t;
        return ans;
    }

    void city_helper_inverse(int city)
    {
        switch(city)
        {
            case 0:
                cout<<"Ahmedabad";
                break;
            case 1:
                cout<<"Srinager";
                break;
            case 2:
                cout<<"Delhi";
                break;
            case 3:
                cout<<"Goa";
                break;
            case 4:
                cout<<"Mumbai";
                break;
            case 5:
                cout<<"Lucknow";
                break;
            case 6:
                cout<<"Chennai";
                break;
            case 7:
                cout<<"Noida";
                break;
            case 8:
                cout<<"Kolkata";
                break;
            case 9:
                cout<<"Bangalore";
                break;

        }
    }

    
     void fordFulkerson()
    {
        string source,destination;
        cout<<" Enter the source and destination: ";
        cin.ignore();
        getline(cin,source);
        getline(cin,destination);
        auto ans = city_helper(source,destination);
        int s = ans.first;
        int t = ans.second;
        int graph_3[A][A] = {{0,0,0,0,9,0,0,6,0,0},
                            {0,0,10,0,0,15,0,5,0,0},
                            {0,10,0,30,0,0,0,0,0,0},
                            {0,0,30,0,62,0,0,14,2,19},
                            {9,0,0,62,0,0,0,31,0,5},
                            {0,15,0,0,0,0,0,0,18,0},
                            {0,0,0,0,0,0,0,0,16,20},
                            {6,5,0,14,31,0,0,0,0,0},
                            {0,0,0,2,0,18,16,0,0,0},
                            {0,0,0,19,5,0,20,0,0,0} };



        int u, v;

        int rGraph[A][A];
        for (u = 0; u < A; u++)
            for (v = 0; v < A; v++)
                rGraph[u][v] = graph_3[u][v];

        int parent[A];

        int max_flow = 0;

        while (bfs(rGraph, s, t, parent)) {
            int path_flow = INT_MAX;
            for (v = t; v != s; v = parent[v]) {
                u = parent[v];
                path_flow = min(path_flow, rGraph[u][v]);
            }

            for (v = t; v != s; v = parent[v]) {
                u = parent[v];
                rGraph[u][v] -= path_flow;
                rGraph[v][u] += path_flow;
            }

            max_flow += path_flow;
        }
        cout<<" You can deliver maximum "<<max_flow<<" products"<<endl<<endl;

        // Return the overall flow
    }

    int completed[10],n,cost=0;
    int ary[10][10] = { {0,11,21,20,9,26,34,6,22,14},
                            {11,0,10,19,20,15,37,5,21,25},
                            {21,10,0,29,30,25,47,15,31,35},
                            {20,19,29,0,24,20,18,14,2,19},
                            {9,20,30,24,0,35,25,15,26,5},
                            {26,15,25,20,35,0,34,20,18,39},
                            {34,37,47,18,25,34,0,32,16,20},
                            {6,5,15,14,15,20,32,0,16,20},
                            {22,21,31,2,26,18,16,16,0,21},
                            {14,25,35,19,5,39,20,20,21,0} };


     void takeInput(){
        int i,j;

        n=10;

        for(i=0;i<n;i++){
            completed[i]=0;
        }

        cout<<"\n\n The cost list is:";

        for( i=0;i < n;i++){
            cout<<"\n";
            for(j=0;j < n;j++)
            cout<<"\t"<<ary[i][j];
        }
    }


    int least(int c){
        int i,nc=999;
        int min=999,kmin;

        for(i=0;i < n;i++)
        {
        if((ary[c][i]!=0)&&(completed[i]==0))
        if(ary[c][i]+ary[i][c] < min)
        {
        min=ary[i][0]+ary[c][i];
        kmin=ary[c][i];
        nc=i;
        }
        }

        if(min!=999)
        cost+=kmin;

        return nc;
    }


    void mincost(int city){
        int i,ncity;

        completed[city]=1;

        city_helper_inverse(city);
        cout<<"--> ";
        ncity=least(city);

        if(ncity==999)
        {
            ncity=city;
            //city_helper_inverse(ncity);
            cost+=ary[city][ncity];

            return;
        }
        mincost(ncity);
    }

    
    void travellingSalesman(){
        string source;
        cout<<" Enter the source: ";
        cin.ignore();
        getline(cin,source);
        auto ans = city_helper(source,"Goa");
        int s = ans.first;
        takeInput();
        cout<<"\n\n The Path is: ";
        mincost(s);
        cout<<source;
        cout<<"\n\n Minimum cost is "<<cost<<endl<<endl;
    }


    void welcome(){
        system("color 0E");
        cout<<" =================================================================================================================================================================";
        Sleep(800);system("color 0A");
        cout<<endl<<"                                                         WELCOME TO THE E-commerce-Warehouses-Optimisation"<<endl<<endl;
        Sleep(800);system("color 0D");
        cout<<"                            Streamlining Warehousing Excellence: Dijkstra's Algorithm at Your Service for Optimal E-commerce Operations."<<endl;
        Sleep(800);system("color 0F");
        cout<<" =================================================================================================================================================================";
        Sleep(800);system("color 0C");
        Sleep(800);system("color 0B");
        Sleep(800);system("color 0A");
        cout<<endl;
        cout<<endl;
    }
};


int main(){
    graph graph1(10,15);

    graph1.add_neighbour("Srinager","Lucknow",15);
    graph1.add_neighbour("Srinager","Delhi",10);
    graph1.add_neighbour("Srinager","Noida",5);

    graph1.add_neighbour("Kolkata","Lucknow",18);
    graph1.add_neighbour("Kolkata","Goa",2);
    graph1.add_neighbour("Kolkata","Chennai",16);

    graph1.add_neighbour("Chennai","Bangalore",20);
    graph1.add_neighbour("Delhi","Goa",30);

    graph1.add_neighbour("Bangalore","Goa",19);
    graph1.add_neighbour("Mumbai","Bangalore",5);
    graph1.add_neighbour("Mumbai","Goa",62);

    graph1.add_neighbour("Noida","Mumbai",31);

    graph1.add_neighbour("Mumbai","Ahmedabad",9);
    graph1.add_neighbour("Ahmedabad","Noida",6);
    graph1.add_neighbour("Noida","Goa",14);

    system("cls");
    graph1.welcome();
    int choice, exit=1;
    while(exit==1)
    {
        cout<<endl;
        system("color 0A");
        cout << "Press 1: View the Warehouse Layout Map" << endl;
        cout << "Press 2: Find the Shortest Distance from a Storage Area to All Other Zones" << endl;
        cout << "Press 3: Optimize the Shortest Path for Efficient Order Fulfillment" << endl;
        cout << "Press 4: Maximize Parcel Deliveries Between Two Key Locations" << endl;
        cout << "Press 5: Discover the Most Cost-Effective Route to Traverse the Warehouse" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        switch(choice)
            {
                case 1:
                    cout<<endl;
                    system("color 0B");
                    cout<<" Following is the Warehouse Layout Map: "<<endl;
                    graph1.print_graph();
                    cout<<" To exit press 0 else press 1: ";
                    cin>>exit;
                    break;
                case 2:
                    {cout<<endl;
                    system("color 0B");
                    cout << " Enter source: ";
                    string source;
                    cin.ignore();
                    getline(cin,source);
                    graph1.find_shortest_path(source,1);
                    cout<<" To exit press 0 else press 1: ";
                    cin>>exit;
                    break;}
                case 3:
                    cout<<endl;
                    system("color 0B");
                    graph1.get_path_from_two_nodes();
                    cout<<" To exit press 0 else press 1: ";
                    cin>>exit;
                    break;
                case 4:
                    cout<<endl;
                    system("color 0B");
                    graph1.fordFulkerson();
                    cout<<" To exit press 0 else press 1: ";
                    cin>>exit;
                    break;
                case 5:
                    cout<<endl;
                    system("color 0B");
                    graph1.travellingSalesman();
                    cout<<" To exit press 0 else press 1: ";
                    cin>>exit;
                    break;
            }
    }

    return 0;
}


