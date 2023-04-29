#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> tp;
class shortest_path
{
private:
    int num_vertex;
    vector<vector<int> > adjlist; // n by n matrix
    vector<int> distance, predecessor, set; // set is visited vertex
    vector<bool> visited;

public:
    shortest_path(){}; //constructor
    shortest_path(int n) : num_vertex(n){ //constructor
        adjlist.resize(n), distance.resize(n), predecessor.resize(n); // initalzation array size
        for (int i = 0; i < n; i++)                                   // initalzation 2D array size
            adjlist[i].resize(n);
    };
    void initalzation(int start);
    void dijkstra(int start, string text);
    void addedge(int start, int end, int weight);
    void printresult(); // show output result
    void file_printresult(string text); // write output to file
    void print_matrix(); //show input Matrix
};

void shortest_path::initalzation(int start)
{
    for (int i = 0; i < num_vertex; i++){
        distance[i] = 99999; // 99999 represent unlimited
        predecessor[i] = -1; // -1 represent not previous
    }
    distance[start] = 0;               // self to self distance = 0
    visited.resize(num_vertex, false); // initalzation to false, no vector have been visited
};

void shortest_path::dijkstra(int start, string text)
{
    ofstream hwfile;
    hwfile.open(text, ios::app);

    if(!hwfile.is_open()){
        cout << "Error, file is open!" << endl;
        exit(1);
    }

    initalzation(start);
    priority_queue<tp, vector<tp>, greater<tp> >minqueue;
    // change priority to minimum

    int s,t = 0; // s,t is the number of steps
    cout << "----- step " << s << " -----" << endl;
    printresult(); //start state
    cout << "S = {}" << endl;

    hwfile << "----- step " << s << " -----" << endl; 
    file_printresult(text);
    hwfile << "S = {}" << endl;

    minqueue.push(make_pair(distance[start], start)); //push start
    while (!minqueue.empty()){

    int u = minqueue.top().second; // u is the minimum vertex in the distance matrix

            for (int i = 0; i < adjlist.size(); i++){ // find each neighbor vertex of u
                if(!adjlist[u][i]){} // ignore not exist edge
                else if (distance[i] > distance[u] + adjlist[u][i]){ // distance can be shorter

                    distance[i] = distance[u] + adjlist[u][i]; // update distance
                    predecessor[i] = u; // update predecessor
                    minqueue.push(make_pair(distance[i], i)); // add new distance to queue 
                }
            }
        if(distance[u] == minqueue.top().first){

            cout << "----- step " << ++s << " -----" << endl;
            // cout << "top is = " << minqueue.top().first << endl;
            printresult();
            set.push_back(u); // add visited vertex into Set
            cout << "S = { ";
            for(int i = 0; i < set.size(); i++)
                cout << set[i] << " ";
            cout << "}" << endl;

            hwfile << "----- step " << ++t << " -----" << endl;
            file_printresult(text);
            hwfile << "S = { ";
            for(int i = 0;i < set.size(); i++)
                hwfile << set[i] << " ";
            hwfile << "}" << endl;
        }
        minqueue.pop(); // remove vertex u from queue
    }
    hwfile.close();
};

void shortest_path::addedge(int start, int end, int weigth) // input edge and weigth
{
    adjlist[start][end] = weigth;
};

void shortest_path::print_matrix(){ // print exist edge by matrix
    for (int i = 0; i < adjlist.size(); i++){
        for (int j = 0; j < adjlist[0].size(); j++){
        if (!adjlist[i][j]){} // ignore not exit edge
        else
            cout << "Matrix[" << i << "][" << j << "] = " << adjlist[i][j] << endl; // i = start vertex, j = end vertex 
        }
    }
};

void shortest_path::printresult(){
    cout << "num_vertex\n";
    for (int i = 0; i < num_vertex; i++)
        cout << i << "\t";

    cout << "\npredecessor:\n";
    for (int i = 0; i < num_vertex; i++)
        cout << predecessor[i] << "\t";

    cout << "\ndistance:\n";
    for (int i = 0; i < num_vertex; i++)
        cout << distance[i] << "\t";
    cout << endl;
};

void shortest_path::file_printresult(string text){
    fstream hwfile;
    hwfile.open(text, ios::app);

    hwfile << "\nnum_vertex\n";
    for (int i = 0; i < num_vertex; i++)
        hwfile << i << "\t";

    hwfile << "\npredecessor:\n";
    for (int i = 0; i < num_vertex; i++)
        hwfile << predecessor[i] << "\t";

    hwfile << "\ndistance:\n";
    for (int i = 0; i < num_vertex; i++)
        hwfile << distance[i] << "\t";
    hwfile << endl;

    hwfile.close();
};


int main()
{
    fstream file1, file2;
    file1.open("dijkstra_output1.txt", ios::out);
    file2.open("dijkstra_output2.txt", ios::out);
    // shortest_path G0(8);

    /* G.addedge(start vertex, end vertex, weight) */
    // G0.addedge(4,5,250);
    // G0.addedge(4,3,1500);
    // G0.addedge(5,3,1000);
    // G0.addedge(5,6,900);
    // G0.addedge(5,7,1400);
    // G0.addedge(3,2,1200);
    // G0.addedge(6,7,1000);
    // G0.addedge(7,0,1700);
    // G0.addedge(2,0,1000);
    // G0.addedge(2,1,800);
    // G0.addedge(1,0,300);

    shortest_path G1(9);
    G1.addedge(0, 1, 1);
    G1.addedge(0, 2, 5);
    G1.addedge(0, 3, 7);
    G1.addedge(0, 4, 4);
    G1.addedge(1, 5, 3);
    G1.addedge(1, 6, 10);
    G1.addedge(2, 5, 2);
    G1.addedge(2, 7, 2);
    G1.addedge(3, 6, 1);
    G1.addedge(4, 7, 3);
    G1.addedge(5, 8, 2);
    G1.addedge(6, 8, 9);
    G1.addedge(7, 8, 5);
    G1.print_matrix();

    int start_vertex;
    cout << "Please enter the starting vertex of your first graph : "; 
    cin >> start_vertex;
    cout << "start vertex is = " << start_vertex << endl;
    file1 << "start vertex is = " << start_vertex << endl; 
    G1.dijkstra(start_vertex, "dijkstra_output1.txt");
    cout << "=================================" << endl;

    shortest_path G2(6);
    G2.addedge(0, 1, 8);
    G2.addedge(0, 5, 1);
    G2.addedge(1, 0, 3);
    G2.addedge(1, 2, 1);
    G2.addedge(2, 0, 5);
    G2.addedge(2, 3, 2);
    G2.addedge(2, 4, 2);
    G2.addedge(3, 1, 4);
    G2.addedge(3, 2, 6);
    G2.addedge(3, 4, 7);
    G2.addedge(3, 5, 3);
    G2.addedge(5, 3, 2);
    G2.addedge(5, 4, 8);
    G2.print_matrix();

    cout << "Please enter the starting vertex of your second graph : ";
    cin >> start_vertex;
    cout << "start vertex is = " << start_vertex << endl;
    file2 << "start vertex is = " << start_vertex << endl;
    G2.dijkstra(start_vertex, "dijkstra_output2.txt");
    
    file1.close(); 
    file2.close();

    return 0;
}
