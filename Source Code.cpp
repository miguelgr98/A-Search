
#include <iomanip> //Thus library allows to call the setw function
#include <iostream>
#include <string>
using namespace std;

void star_search(int, int, int & );
void get_city_id(int * );
void show_list_cities();
string get_steps(string & , int, int[], int[], int);
void print_results(int, int, int[], int, int[]);


//Implementation of the cities by a Adjacency matrix with weight
string city_names[] = {
    "Arad",
    "Zerind",
    "Oradea",
    "Timisoara",
    "Lugoj",    
    "Mehadia",
    "Drobeta",
    "Craiova",
    "Ramnicu Valcea",
    "Sibiu",
    "Fagaras",
    "Pitesti",
    "Bucuresti",
    "Giurgiu",
    "Urziceni",
    "Harsova",
    "Eforie",
    "Vaslui",
    "Iasi",
    "Neamt"
};

//Here I could write 20 directly, but in case we want to delete or add a city we don´t have to change nothing
const int size = sizeof(city_names) / sizeof(city_names[0]);

//  Adjacency matrix by distance
int distances[][size] = {
    {0, 75, 0, 118, 0, 0, 0, 0, 0, 140, 0, 0, 0, 0,0, 0, 0, 0, 0, 0},
    {75, 0, 71, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 71, 0, 0, 0, 0, 0, 0, 0, 151, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {118, 0, 0, 0, 111, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 111, 0, 70, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 70, 0, 75, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 75, 0, 120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 120, 0, 146, 0, 0, 138, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 146, 0, 80, 0, 97, 0, 0, 0, 0, 0, 0, 0, 0},
    {140, 0, 151, 0, 0, 0, 0, 0, 80, 0, 99, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 99, 0, 0, 211, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 138, 97, 0, 0, 0, 101, 0, 0, 0, 0, 0, 0, 0},  
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 211, 101, 0, 90, 85, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 90, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 85, 0, 0, 98, 0, 142, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 98, 0, 86, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 86, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 142, 0, 0, 0, 92, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 92, 0, 87},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 87, 0}
};

//String with the distances from Bucarest to the others cities
int estimates[size] = {366, 374, 380, 329, 244, 241, 242, 160, 193,253, 176, 10, 0, 77, 80, 151, 161, 199, 226, 234};

bool display_steps = false; // Setting: displays intermediate steps

string separator =
"\n************************************************************\n"; //This is only a visual improve for be more clear

int main(int argc, char * argv[]) {

    // Parsing the arguments with which the application is started
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-d") {
             display_steps = true;
        }
    }
    int start;
    int finish;
    int cost_star;
    
    // Input loop to be able to try different combinations of cities, without restarting the application and without hardcoding them
    while (true) {
        show_list_cities();
        
        cout << "\n\n Write the location of the first friend ";
        get_city_id( & start);
        
        cout << "From " << city_names[start];
        cout << "\n\n Write the location of the seccond friend ";
        get_city_id( & finish);
        
        cout << "To  " << city_names[finish];


        star_search(start, finish, cost_star);
        cout << "\n\n Total:" << separator;
        cout << "Result : " << setw(4) << cost_star << " km\n";
        cout << separator;
       // resets the variables for the next input
        cost_star = 0;
    }
    return 0;
}


//The star search
void star_search(int start_node, int finish_node, int & cost) {
    int frontier[size] = {
        start_node
    };

    int frontier_count = 1;
    bool explored[size] = {
        false
    };

    explored[start_node] = true;
    
    int ascendants[size] = {
        0
    };  

    bool found = false;
    int costs[size] = {
        0
    };

    int step = 1;
    string recorded_steps = "";
    while (!found && frontier_count > 0) {
        // The first element in the boundary becomes the current node
        int current_node = frontier[0];
        int current_cost = costs[current_node];

        // Record the steps
        if (display_steps) {
            get_steps(recorded_steps, step, frontier, costs, frontier_count);
        }
        
        step++;

        // Remove the first element from the border 
        for (int i = 0; i < frontier_count - 1; i++) {
            frontier[i] = frontier[i + 1];
        }
        frontier_count--; 

        // Updates the number of nodes to explore, check if the current node is the target
        if (current_node == finish_node) {
            found = true;
        } 
        else {

        // Iterates in the line from the adjacent matrix, corresponding to the current node to find the successor nodes
            for (int i = 0; i <size; i ++) {
                if ((distances[current_node][i] != 0) && !explored[i]) {
                    frontier[frontier_count] = i;
                    costs[i] = current_cost + distances[current_node][i];
                    frontier_count++;
                    explored[i] = true;
                    ascendants[i] = current_node;
                }
            }      
            for (int i = 0; i < frontier_count - 1; i++) {
                for (int j = i + 1; j < frontier_count; j++) {
                    //If the sum of the estimated dsitance plus the frontier is bigger than the next node then go next node
                    if ((costs[frontier[i]] + estimates[frontier[i]]) > (costs[frontier[j]] + estimates[frontier[j]])) {
                            int temp = frontier[i];
                            frontier[i] = frontier[j];
                            frontier[j] = temp;
                        }
                    }
                }   
            }
        }

    

        // Display the intermediate steps
        cout << recorded_steps;
        int solution[size] = {

        };

        int solution_count = 0;
        int current_node = finish_node;

        while (current_node != start_node) {
            solution[solution_count] = current_node;
            solution_count++;
            current_node = ascendants[current_node];
        }

        solution[solution_count] = start_node;
        solution_count++;
        cost = costs[finish_node];
        print_results(start_node, finish_node, solution, solution_count,costs);
    }

    //Read the start and finish city we had introduce
    void get_city_id(int * id) {
        int temp;
        while (true) {
            if ((cin >> temp) && (temp >= 0) && (temp < size)) {
                break;
            }
            cout << "Index must be an integer between 0 and" << size - 1 << "! \n Please try again:";
            cin.clear();
        }
    * id = temp;
}

//Show the lits of the cities
void show_list_cities() {
    cout << "List of the cities:\n";
    for (int i = 0; i < size; i++) {
        cout << setw(4) << std::right << i << ". ";
        cout << setw(15) << std::left << city_names[i] << "\t";
        if ((i + 1) % 4 == 0) {
            cout << '\n';
        }   
    }
}

//Get the steps the path follows 
string get_steps(string & recorded_steps, int step, int frontier[], int nodes[], int node_count) {
    if (display_steps) {
        char node[10];
        sprintf(node, "%3d: ", step);
        recorded_steps.append(node);
        for (int i = 0; i < node_count; i++) {
            char distance[10];
            sprintf(distance, "%d", nodes[frontier[i]]);
            string city = city_names[frontier[i]] + " [" + distance + "] ";
            recorded_steps.append(city);
        }
        recorded_steps.append("\n");
    }
    return recorded_steps;
}

//Shows the results 
void print_results(int start_node, int finish_node, int path[size], int path_nodes_count, int cost[size]) {
    cout << "\n Friend A \n" <<
    
    city_names[start_node] << " -> " << city_names[finish_node] << '\n';

    for (int i = path_nodes_count - 1; i >= 0; i--) {
        
        cout << setw(15) << std::left << city_names[path[i]];
        cout << std::right << setw(9) << cost[path[i]]-cost[path[i+1]] << " km and minutes";//Displays the cost node by node
        cout << '\n';
    }
    
     cout << "\n Friend B \n" <<
    
    city_names[finish_node] << " -> " << city_names[start_node] << '\n';

    for (int j = 0; j <= path_nodes_count-1; j++) {
        
        cout << setw(15) << std::left << city_names[path[j]];
        cout << std::right << setw(9) << cost[path[j]]-cost[path[j+1]] << " km and minutes";
        cout << '\n';
    }
       cout << setw(10) << std::left << " Total distance and time " << cost[path[0]] << "km and minutes\n";
}
