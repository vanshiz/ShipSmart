#include<iostream>
#include<vector>
#include<map>
#include<queue>
#include<limits.h>
#include<algorithm>
#include <cstdlib>
#include<windows.h>
using namespace std;

#define V 10

class graph{
    public:

    int vertices,edges;
    map<string,string>parent;
    map<string,vector<pair<string,int>>>graph_list;

    graph(int v,int e){
        this->vertices=v;
        this->edges=e;
    }

    void add_neighbour(string source,string destination,int distance){
        graph_list[source].push_back({destination,distance});
        graph_list[destination].push_back({source,distance});
    }

    void print_graph(){

        for(auto element_list : graph_list ){
            string node = element_list.first;
            cout<<" "<<node<<" -> ";
            for( auto neighbours : graph_list[node] )
                cout <<" (" << neighbours.first<<" - "<<neighbours.second << "), ";
            cout<<endl;
        }
    }


    void find_shortest_path(string source,bool funCall=false){


        priority_queue< pair<int,string> , vector<pair<int,string>> , greater<pair<int,string>> > queue_;
        queue_.push({0, source});

        map<string , bool>visited;
        map<string , int > distance;
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
        vector<string>path;

        while(parent[indermediate_node] != indermediate_node){
            path.push_back(indermediate_node);
            indermediate_node = parent[indermediate_node];
        }

        path.push_back(indermediate_node);

        reverse(path.begin(),path.end());

        cout<<"\n Required path :" << path.size() <<endl; ;

        for(int i= 0 ;i < path.size() ;i++){
                if(i == (path.size() - 1 ))cout<<path[i];
                else cout<<path[i]<<" -> ";
        }cout<<endl;
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

    bool bfs(int rGraph[V][V], int s, int t, int parent[])
{

    bool visited[V];
    memset(visited, 0, sizeof(visited));

    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (visited[v] == false && rGraph[u][v] > 0) {

                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return false;
}

    //to convert city into index
    pair <int,int> city_helper(string source,string destination)
    {

        pair< int,int> ans;
        int s,t;
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


    //to convert index into city
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
    int graph_3[V][V] = { {0,0,0,0,9,0,0,6,0,0},
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

    int rGraph[V]
              [V];
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
            rGraph[u][v] = graph_3[u][v];

    int parent[V];

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

    void takeInput()
    {
                int i,j;

                n=10;

                for(i=0;i < n;i++)
                {
                completed[i]=0;
                }

                cout<<"\n\n The cost list is:";

                for( i=0;i < n;i++)
                {
                cout<<"\n";

                for(j=0;j < n;j++)
                cout<<"\t"<<ary[i][j];

                }
    }

    int least(int c)
    {
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


    void mincost(int city)
    {
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
    graph1.add_neighbour("Srinager","New Delhi",10);
    graph1.add_neighbour("Srinager","Noida",5);

    graph1.add_neighbour("Kolkata","Lucknow",18);
    graph1.add_neighbour("Kolkata","Goa",2);
    graph1.add_neighbour("Kolkata","Chennai",16);

    graph1.add_neighbour("Chennai","Bangalore",20);
    graph1.add_neighbour("New Delhi","Goa",30);

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


// Authentication
//admin :view Add Update Delete
//user : View 1-shortest 2b/w maximum cost eff