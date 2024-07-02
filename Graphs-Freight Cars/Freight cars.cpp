#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <list>
using namespace std;
class Parcel
{
public:
    int time_tick;
    std::string parcel_id;
    std::string origin;
    std::string destination;
    int priority;
    bool delivered;
    std::string current_location;

    Parcel() = default;
    Parcel(int time_tick, std::string parcel_id, std::string origin, std::string destination, int priority)
    {
        this->time_tick = time_tick;
        this->parcel_id = parcel_id;
        this->origin = origin;
        this->destination = destination;
        this->priority = priority;
        this->delivered = false;
        this->current_location = origin;
    }
};

class MaxHeap
{
public:
    std::vector<Parcel *> heap;

    int parent(int i)
    {
        // fill in this function
        return (i - 1) / 2;
    }

    int left(int i)
    {
        // fill in this function
        return 2 * i + 1;
    }

    int right(int i)
    {
        // fill in this function
        return 2 * i + 2;
    }

    Parcel *get_max()
    {
        // fill in this function
        return heap[0];
    }

    Parcel *extract_max()
    {
        // function that returns the max element and removes it from the heap

        Parcel *max_extract = heap[0];
        if (heap.size() > 0)
        {
            heap[0] = heap[heap.size() - 1];
            heap.pop_back();
            max_heapify(0);
        }
        return max_extract;
    }

    void max_heapify(int i)
    {
        // function that maintains the max heap property
        int max;
        if (heap[left(i)] != nullptr && heap[right(i)] != nullptr)
        {
            if (left(i) <= heap.size() && heap[left(i)]->priority > heap[i]->priority)
            {
                max = left(i);
            }
            else
            {
                max = i;
            }
            if (right(i) <= heap.size() && heap[right(i)]->priority > heap[i]->priority)
            {
                max = right(i);
            }
            if (max != i)
            {
                swap(heap[i], heap[max]);
                max_heapify(max);
            }
        }
    }
    void check()
    {
        for (auto &i : heap)
        {
            cout << i->parcel_id << " " << i->origin << " " << i->destination << " " << i->priority << endl;
        }
        cout << endl;
    }
    void insert(Parcel *item)
    {
        // function that inserts item into the heap
        heap.push_back(item);
        int n = heap.size() - 1;
        while (n > 0 && heap[parent(n)]->priority < heap[n]->priority)
        {
            swap(heap[parent(n)], heap[n]);
            n = parent(n);
        }
        // check();
    }
    bool is_empty()
    {
        return heap.empty();
    }
};

class FreightCar
{
public:
    int max_parcel_capacity;
    std::vector<Parcel *> parcels;
    std::string destination_city;
    std::string next_link;
    std::string current_location;
    bool sealed;

    FreightCar(int max_parcel_capacity)
    {
        this->max_parcel_capacity = max_parcel_capacity;
        // instantiate parcels vector as empty initially
        this->parcels = {};
        this->destination_city = "";
        this->next_link = "";
        this->current_location = "";
        this->sealed = false;
    }

    void load_parcel(Parcel *parcel)
    {
        // load parcel
        if (parcels.size() < max_parcel_capacity)
        {
            parcels.push_back(parcel);
        }
        else
            return;
    }

    bool can_move()
    {
        // if length of parcels is equal to max_parcel_capacity return true else return false
        if (parcels.size() == max_parcel_capacity)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void move(std::string destination)
    {
        // function that moves freight car to destination (link)
    }
};

class Vertex
{
public:
    std::string name;
    std::vector<FreightCar *> freight_cars;
    std::vector<Vertex *> neighbors;
    // trains_to_move is dict of destination and freight cars
    std::map<std::string, std::vector<FreightCar *>> trains_to_move;
    int min_freight_cars_to_move;
    int max_parcel_capacity;
    std::unordered_map<std::string, MaxHeap *> parcel_destination_heaps;
    std::vector<FreightCar *> sealed_freight_cars;
    std::string check;
    std::vector<Parcel *> all_parcels;
    Vertex() = default;
    Vertex(std::string name, int min_freight_cars_to_move, int max_parcel_capacity)
    {
        this->name = name;
        this->freight_cars = {};
        this->neighbors = {};
        this->trains_to_move = {};
        this->min_freight_cars_to_move = min_freight_cars_to_move;
        this->max_parcel_capacity = max_parcel_capacity;
        this->parcel_destination_heaps = {};
        this->sealed_freight_cars = {};
        this->all_parcels = {};
        this->check = "unvisited";
    }

    void add_neighbor(Vertex *neighbor)
    {
        // add neighbor to neighbors vector
        neighbors.push_back(neighbor);
    }

    // add get neighbors function
    std::vector<Vertex *> get_neighbors()
    {
        return this->neighbors;
    }

    std::vector<Parcel *> get_all_current_parcels()
    {
        // get all parcels from all destination heaps
        return all_parcels;
    }

    void clean_unmoved_freight_cars()
    {
        // after time tick t, freight cars with parcels < min parcels should be deleted and parcels are to be added to heap
        int a;
        for (int i = freight_cars.size() - 1; i >= 0; i--)
        {
            a++;
            if (freight_cars[i]->parcels.size() < max_parcel_capacity)
            {
                for (auto &j : freight_cars[i]->parcels)
                {
                    loadParcel(j);
                }
            }
            freight_cars.erase(freight_cars.begin() + i);
        }
        
        
    }

    void loadParcel(Parcel *parcel)
    {
        // load parcel into heap
        int flag = 1;
        for (auto &i : parcel_destination_heaps)
        {
            if (i.first == parcel->destination)
            {
                i.second->insert(parcel);
                // cout << "=== Start of Heap ===" << endl;
                // for(auto &j:i.second.heap)
                // {
                //     cout<<j->parcel_id<<" "<<j->origin<<" "<<j->destination<<" "<<j->priority<<endl;
                // }
                //   cout << "=== End of Heap ===" << endl;
                flag = 0;
                break;
            }
        }
        if (flag == 1)
        {
            MaxHeap *obj = new MaxHeap();
            obj->insert(parcel);
            parcel_destination_heaps.insert({parcel->destination, obj});
        }
        // print_parcels_in_freight_cars();
    }

    void loadFreightCars()
    {
        // load parcels into freight cars (making sure that each freight car has parcels from only one destination, and # parcels == min_parcel_capacity)
        // cout << "entered" << endl;
        for (auto &i : this->parcel_destination_heaps)
        {
            // for (auto &k : i.second.heap)
            // {
            //     cout << k->origin << " " << k->destination << endl;
            // }
            int rem = (i.second->heap.size()) % (max_parcel_capacity);
            if (i.second->heap.size() <= max_parcel_capacity)
            {
                FreightCar *car = new FreightCar(max_parcel_capacity);
                car->destination_city = i.first;
                car->current_location = this->name;
                freight_cars.push_back(car);
                for (auto &j : i.second->heap)
                {
                    car->load_parcel(i.second->extract_max());
                }
                int assertion;
            }
            else if (i.second->heap.size() > max_parcel_capacity && rem == 0)
            {
                int n = (i.second->heap.size()) / (max_parcel_capacity);
                for (int k = 0; k < n; k++)
                {
                    FreightCar *newcar1 = new FreightCar(max_parcel_capacity);
                    newcar1->current_location = this->name;
                    newcar1->destination_city = i.first;
                    freight_cars.push_back(newcar1);
                    for (auto &j : i.second->heap)
                    {
                   
                        if (newcar1->can_move())
                        {
                            break;
                        }
                        newcar1->load_parcel(i.second->extract_max());
                    }
                }
            }
            else if (i.second->heap.size() > max_parcel_capacity && rem != 0)
            {
                int m = (i.second->heap.size()) / (max_parcel_capacity);
                for (int l = 0; l < m + 1; l++)
                {
                
                    FreightCar *newcar2 = new FreightCar(max_parcel_capacity);
                    newcar2->destination_city = i.first;
                    newcar2->current_location = this->name;
                    freight_cars.push_back(newcar2);
                    for (auto &j : i.second->heap)
                    {
                        int you;
                        if (newcar2->can_move())
                        {
                            break;
                        }
                        newcar2->load_parcel(i.second->extract_max());
                    }
                }
            }
        }
    }
    void print_parcels_in_heaps()
    {
        for (auto &i : this->parcel_destination_heaps)
        {
            for (auto &parcel : i.second->heap)
            {
                std::cout << "Parcel ID: " << parcel->parcel_id << "delivered: " << parcel->delivered << ", Parcel origin: " << parcel->origin << ", Parcel location: " << parcel->current_location << ", Parcel destination: " << parcel->destination << ", Parcel priority: " << parcel->priority << std::endl;
            }
        }
    }
    void print_parcels_in_freight_cars()
    {
        this->loadFreightCars();
        cout << this->freight_cars.size() << endl;
        for (auto &i : this->freight_cars)
        {
            cout << "SIZE:                          " << i->parcels.size() << endl;
            for (auto &j : i->parcels)
            {
                cout << j->parcel_id << " " << j->origin << " " << j->destination << endl;
            }
        }
    }

    // void print_parcels_in_freight_cars() {
    //     for (auto& [destination, heap] : this->parcel_destination_heaps) {
    //         for (auto& parcel : heap.heap) {
    //             std::cout << "Parcel ID: " << parcel.parcel_id << ", Parcel origin: " << parcel.origin << ", Parcel destination: " << parcel.destination << ", Parcel priority: " << parcel.priority << std::endl;
    //         }
    //     }
    // }
};

class Graph
{

public:
    std::list<Vertex *> vertices;
    std::vector<std::pair<Vertex *, Vertex *>> edges;
    vector<string> subpath;
    vector<vector<string>> path;
    unordered_map<string, vector<vector<string>>> bfs1;
    void add_edge(std::string source, std::string destination, int min_freight_cars_to_move, int max_parcel_capacity)
    {

        // check if source and destination vertices exist
        // if they do not exist, create them
        // add edges accordingly
        int flag1 = 1, flag2 = 1, count = 0;
        Vertex *v1 = new Vertex(source, min_freight_cars_to_move, max_parcel_capacity);
        Vertex *v2 = new Vertex(destination, min_freight_cars_to_move, max_parcel_capacity);
        for (auto &i : vertices)
        {
            if (i->name == source)
            {
                v1 = i;
                flag1 = 0;
            }
            if (i->name == destination)
            {
                v2 = i;
                flag2 = 0;
            }
        }
        if (flag1 == 1)
        {
            int zzzzz;
            vertices.push_back(v1);
            Vertex *addr1 = vertices.back();
            v1 = addr1;
        }
        if (flag2 == 1)
        {
            vertices.push_back(v2);
            Vertex *addr2 = vertices.back();
            v2 = addr2;
        }
        edges.emplace_back(v1, v2);
        v1->add_neighbor(v2);
        v2->add_neighbor(v1);
    }

    void print_graph()
    {
        std::cout << "Printing graph, vertices: " << vertices.size() << std::endl;
        for (auto &vertex : this->vertices)
        {
            std::cout << "Vertex: " << vertex->name << std::endl;
            std::cout << "Neighbors: ";
            for (auto &neighbor : vertex->neighbors)
            {
                std::cout << neighbor->name << " ";
            }
            std::cout << std::endl;
        }
    }

    std::vector<std::string> bfs(std::string source, std::string destination)
    {
        // function to return path from source to destination using bfs
        for (auto &i : vertices)
        {
            i->check = "unvisited";
        }
        queue<pair<string, vector<string>>> que;
        que.push({source, {source}});
        Vertex *vertex = nullptr;
        for (auto &i : vertices)
        {
            if (i->name == source)
            {
                i->check = "visited";
            }
        }
        while (!que.empty())
        {
            string current = que.front().first;
            vector<string> path = que.front().second;
            // for (auto i : path)
            // {
            //     cout << i << " ";
            // }
            // cout << endl;
            for (auto &i : vertices)
            {
                if (i->name == current)
                {
                    vertex = i;
                }
            }
            que.pop();
            if (current == destination)
            {
                return path;
            }
            for (auto &i : vertex->get_neighbors())
            {
                if (i->check == "unvisited")
                {
                    i->check = "visited";
                    vector<string> newpath = path;
                    newpath.push_back(i->name);
                    que.push({i->name, {newpath}});
                }
            }
        }
    }
    std::vector<std::string> dfs(std::string source, std::string destination,bool find=true)
    {
        // function to return path from source to destination using 
        if(find)
        {
            for(auto &i:vertices)
            {
                i->check="unvisited";
            }
        }
        Vertex *vertex = nullptr;
        for (auto &i : vertices)
        {
            if (i->name == source)
            {
                if (i->check == "unvisited")
                {
                    subpath.push_back(source);
                    i->check = "visited";
                }
                vertex = i;
            }
        }
        if (source == destination)
        {
            path.push_back(subpath);
            for (auto &i : vertices)
            {
                if (i->name == destination)
                {
                    i->check = "unvisited";
                }
            }
            subpath.pop_back();
            return path[0];
        }
        for (auto &i : vertex->get_neighbors())
        {
            string current = i->name;
            if (i->check == "unvisited")
            {
                i->check = "visited";
                subpath.push_back(i->name);
                dfs(i->name, destination,false);
            }
        }
        subpath.pop_back();
        if (path.empty())
        {
            return vector<string>();
        }
        else
        {
            return path[0];
        }
    }

    void groupFreightCars()
    {
        // for every vertex, group freight cars by links
       
        for (auto &i : vertices)
        {
            i->loadFreightCars();
          
           
            for (auto &freight_car : i->freight_cars)
            {
             
                if (freight_car->parcels.size() == freight_car->max_parcel_capacity)
                {
                    i->sealed_freight_cars.push_back(freight_car);
                    i->sealed_freight_cars[i->sealed_freight_cars.size() - 1]->destination_city = freight_car->destination_city;
                    i->sealed_freight_cars[i->sealed_freight_cars.size() - 1]->current_location = i->name;
                    freight_car->sealed = "true";
                }
            }
            for (auto &sealed : i->sealed_freight_cars)
            {
                int flag = 1;
              
                for (auto &j : i->trains_to_move)
                {
                    if (j.first == bfs(sealed->current_location, sealed->destination_city)[1])
                    {
                        sealed->next_link = j.first;
                        flag = 0;
                        j.second.push_back(sealed);
                    }
                }
                if (flag == 1)
                {
                    
                    string link_name = bfs(sealed->current_location, sealed->destination_city)[1];
              
                    sealed->next_link = link_name;
                    vector<FreightCar *> inserted;
                    inserted.push_back(sealed);
                    i->trains_to_move.insert({link_name, inserted});
                
                }
            }
            i->sealed_freight_cars.clear();
            for (auto &trains : i->trains_to_move)
            {
                if (trains.second.size() < i->min_freight_cars_to_move)
                {
                    for (auto &freightcars : trains.second)
                    {
                        i->sealed_freight_cars.push_back(freightcars);
                    }
                    for (auto &j : trains.second)
                    {
                        trains.second.pop_back();
                    }
                }
            }
            for (auto &sealed : i->sealed_freight_cars)
            {
               
               
         
                int flag1 = 1;
                for (auto &j : i->trains_to_move)
                {
                    if (j.first == dfs(sealed->current_location, sealed->destination_city)[1])
                    {
                        sealed->next_link = j.first;
                        flag1 = 0;
                        j.second.push_back(sealed);
                    }
                }
                if (flag1 == 1)
                {

                    string link_name = dfs(sealed->current_location, sealed->destination_city)[1];
                    sealed->next_link = link_name;
                    vector<FreightCar *> inserted;
                    inserted.push_back(sealed);
                    i->trains_to_move.insert({link_name, inserted});
                }
            }
            i->clean_unmoved_freight_cars();
        }
    }

    void moveTrains()
    {
        // for every vertex, move freight cars to next link
        for (auto &vertex : vertices)
        {
            for (auto &trains : vertex->trains_to_move)
            {
                Vertex *old_vertex = vertex;
                if (trains.second.size() >= vertex->min_freight_cars_to_move)
                {
                    for (int i = old_vertex->freight_cars.size() - 1; i >= 0; i--)
                    {
                        for (int j = 0; j < trains.second.size(); j++)
                        {
                            if (old_vertex->freight_cars[i] == trains.second[j])
                            {
                                old_vertex->freight_cars.erase(old_vertex->freight_cars.begin() + i);
                            }
                        }
                    }
                    for (int i = old_vertex->all_parcels.size() - 1; i >= 0; i--)
                    {
                        for (auto &j : trains.second)
                        {
                            for (int k = 0; k < j->parcels.size(); k++)
                            {
                                if (old_vertex->all_parcels[i] == j->parcels[k])
                                {
                                    old_vertex->all_parcels.erase(old_vertex->all_parcels.begin() + i);
                                }
                            }
                        }
                    }
                    for (auto &link_vertex : vertices)
                    {
                        if (trains.first == link_vertex->name)
                        {
                            for (auto &freight_car : trains.second)
                            {
                                freight_car->current_location = trains.first;
                                link_vertex->freight_cars.push_back(freight_car);
                                for (auto &parcel : freight_car->parcels)
                                {
                                    link_vertex->all_parcels.push_back(parcel);
                                    if (parcel->destination == freight_car->destination_city)
                                    {
                                        parcel->delivered = "true";
                                    }
                                }
                            }
                        }
                    }
                    trains.second.clear();
                }
            }
        }
    }
};

class PRC
{
public:
    Graph graph;
    std::vector<FreightCar *> freight_cars;
    std::map<std::string, Parcel *> parcels;
    std::map<int, std::vector<Parcel *>> parcels_with_time_tick;
    int max_parcel_capacity;
    int min_freight_cars_to_move;
    int time_tick;
    std::map<std::string, std::string> old_state;
    std::map<std::string, std::string> new_state;
    vector<Parcel*> parcele;
    int max_time_tick;

    PRC(int max_parcel_capacity, int min_freight_cars_to_move)
    {
        this->max_parcel_capacity = max_parcel_capacity;
        this->min_freight_cars_to_move = min_freight_cars_to_move;
        this->time_tick = 1;
        this->max_time_tick = 100;
        this->freight_cars = {};
        this->parcels = {};
        this->parcels_with_time_tick = {};
        this->old_state = {};
        this->new_state = {};
    }

    void create_graph(std::string graph_file_name)
    {

        // read graph.txt file and create graph
        vector<string> vertexes;
        vector<string> graphdata;
        string element;
        string line;
        stringstream buffer;
        ifstream file(graph_file_name);
        if (file.is_open())
        {
            buffer << file.rdbuf();
            file.close();
            element = buffer.str();
        }
        istringstream stream(element);
        while (getline(stream, line, '\n'))
        {
            graphdata.push_back(line);
        }
        for (int i = 0; i < graphdata.size(); i++)
        {
            istringstream stream(graphdata[i]);
            string word;
            string v1, v2;
            while (getline(stream, word, ' '))
            {
                v1 = word;
                vertexes.push_back(word);
            }
        }
        for (int k = 0; k < vertexes.size(); k = k + 2)
        {
            if (k + 1 < vertexes.size())
            {
                graph.add_edge(vertexes[k], vertexes[k + 1], min_freight_cars_to_move, max_parcel_capacity);
            }
        }
    }

    void process_parcels(std::string parcels_file_name)
    {
        // read parcels.txt file and create parcels
        vector<string> parceldata;
        string element;
        string line;
        stringstream buffer;
        ifstream file(parcels_file_name);
        if (file.is_open())
        {
            buffer << file.rdbuf();
            file.close();
            element = buffer.str();
        }
        istringstream stream(element);
        while (getline(stream, line, '\n'))
        {
            parceldata.push_back(line);
        }
        for (int i = 0; i < parceldata.size(); i++)
        {
            istringstream stream(parceldata[i]);
            int time_tick, priority;
            string parcel_id, source_city, destination_city;
            string word;
            int itr = 1;
            while (getline(stream, word, ' '))
            {
                if (itr == 1)
                {
                    time_tick = stoi(word);
                    itr++;
                }
                else if (itr == 2)
                {
                    parcel_id = word;
                    itr++;
                }
                else if (itr == 3)
                {
                    source_city = word;
                    itr++;
                }
                else if (itr == 4)
                {
                    destination_city = word;
                    itr++;
                }
                else if (itr == 5)
                {
                    priority = stoi(word);
                    Parcel *parcel = new Parcel(time_tick, parcel_id, source_city, destination_city, priority);
                    // for (auto &i : graph.vertices)
                    // {
                    //     if (i->name == source_city)
                    //     {
                    //         i->all_parcels.push_back(parcel);
                    //         i->loadParcel(parcel);
                    //     }
                    // }
                    parcels.insert({parcel->parcel_id, parcel});
                    parcele.push_back(parcel);
                }
            }
        }
        old_state = get_state();
    }

    // function to return bookings at a particular time tick at a particular vertex
    std::vector<Parcel *> get_bookings(int time_tick, std::string vertex)
    {
        run_simulation(time_tick);
        for (auto &i : graph.vertices)
        {
            if (i->name == vertex)
            {
                return i->all_parcels;
            }
        }
    }

    std::map<std::string, std::string> get_state()
    {
        std::map<std::string, std::string> state;
        // from this.parcels
        // should return the dict of parcel_id and current_location
        for (auto &i : this->parcels)
        {
            Parcel *parcel = i.second;
            state[parcel->parcel_id] = parcel->current_location;
        }
        return state;
    }

    // run simulation function, takes run_till_time_tick as argument
    // if run_till_time_tick is not provided then run simulation till max_time_tick

    void run_simulation(int run_till_time_tick = -1)
    {
        // function to run simulation
        new_state.clear();
        while (run_till_time_tick != 1 && !convergence_check())
        {
            for (auto &p : parcele)
            {
             
                for (auto &i : graph.vertices)
                {
                    if ((i->name == p->origin) && (time_tick == p->time_tick))
                    {
                        i->all_parcels.push_back(p);
                        i->loadParcel(p);
                    }
                }
            }
            old_state = get_state();
            time_tick++;
            graph.groupFreightCars();
            graph.moveTrains();
            run_till_time_tick--;
            new_state = get_state();
        }
    }

    bool convergence_check()
    {
        // function to check convergence between old_state and new_state
        int flag = 0;
        if (new_state.size() == 0)
        {
            return false;
        }
        for (auto &i : old_state)
        {
            if (old_state[i.first] != new_state[i.first])
            {
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            return false;
        }
        else
        {
            return true;
        }
        old_state = new_state;
    }

    bool all_parcels_delivered()
    {
        for (auto &parcel_pair : this->parcels)
        {
            Parcel *parcel = parcel_pair.second;
            if (!parcel->delivered)
            {
                return false;
            }
        }
        return true;
    }

    std::vector<std::string> get_stranded_parcels()
    {
        vector<string> parcel_ids;
        for (auto &i : graph.vertices)
        {
            for (auto &j : i->all_parcels)
            {
                if (!j->delivered)
                {
                    parcel_ids.push_back(j->parcel_id);
                }
            }
        }
        return parcel_ids;
        // return parcel_ids of stranded parcels
       
    }

    std::vector<std::string> get_delivered_parcels()
    {
        // return parcel_ids of delivered parcels
        vector<string> parcel_ids;
        for (auto &i : graph.vertices)
        {
            for (auto &j : i->all_parcels)
            {
                if (j->delivered)
                {
                    parcel_ids.push_back(j->parcel_id);
                }
            }
        }
        return parcel_ids;
    }

    // get status of all parcels at time tick t (status = id, current location, delivered/not delivered)
    std::vector<std::string> get_status_of_all_parcels(int t)
    {
        // std::string status = parcel.parcel_id + " " + parcel.current_location + " " + std::to_string(parcel.delivered) + "\n" ;
        // return the status of all parcels at time tick t as a vector of strings (each string formatted as above)
        run_simulation(t);
        vector<string> status_of_all_parcels;
        for (auto &i : graph.vertices)
        {
            for (auto &parcel : i->all_parcels)
            {
                string status = parcel->parcel_id + " " + parcel->current_location + " " + to_string(parcel->delivered) + "\n";
                status_of_all_parcels.push_back(status);
            }
        }
    }

    // get status of parcel_id at time tick t (status = id, current location, delivered/not delivered)
    std::string get_status_of_parcel(std::string parcel_id, int t)
    {
        // status = parcel.parcel_id + " " + parcel.current_location + " " + std::to_string(parcel.delivered);
        // return status of one parcel at time tick t as a string (formatted as above)
        run_simulation(t);
        string status;
        for (auto &i : graph.vertices)
        {
            for (auto &parcel : i->all_parcels)
            {
                if (parcel->parcel_id == parcel_id)
                    status = parcel->parcel_id + " " + parcel->current_location + " " + to_string(parcel->delivered);
            }
        }
        return status;
    }

    // get parcels delivered up to time tick t
    std::vector<std::string> get_parcels_delivered_up_to_time_tick(int t)
    {
        // return list of parcel_ids of parcels delivered up to time tick t
        run_simulation(t);
        vector<string> delivered_vector;
        for (auto &i : graph.vertices)
        {
            for (auto &j : i->all_parcels)
            {
                if (j->delivered == true)
                {
                    delivered_vector.push_back(j->parcel_id);
                }
            }
        }
        cout<<delivered_vector.size()<<endl;
        return delivered_vector;
    }
};

// int main()
// {

//     PRC prc = PRC(2, 2);
//     string filename = "samples/4/graph.txt";
//     string filename1 = "samples/4/bookings.txt";
//     prc.create_graph(filename);
//     prc.process_parcels(filename1);
//     //  prc.run_simulation(20);
//     prc.run_simulation(3);
//     // for (auto &i : prc.graph.vertices)
//     // {
//     //     cout << i->name << endl;
//     //     i->print_parcels_in_heaps();
//     //     cout << "next vertex" << endl;
//     // }
//     // std::vector<string>bfs_paths=prc.graph.bfs("Mumbai", "Ahmedabad");
//     std::vector<std::string> dfs_path = prc.graph.dfs("Mumbai", "Tirupati");
//     for (auto &i : dfs_path)
//     {
//         cout << i << endl;
//     }

//     // cout<<dfs_paths.size()<<endl;
//     return 0;
// }
