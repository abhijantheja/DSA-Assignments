#include "Freight cars.cpp"
#include <cassert>

void test_case_1()
{
    // create a PRC object
    PRC prc(2, 2);
    // create a graph
    prc.create_graph("samples/2/graph.txt");
    prc.process_parcels("samples/2/bookings.txt");
    prc.run_simulation(3);
    assert(prc.all_parcels_delivered() == false);
    std::vector<std::string> stranded_parcels_before = prc.get_stranded_parcels();
    assert(std::find(stranded_parcels_before.begin(), stranded_parcels_before.end(), "P2Ludhiana4") != stranded_parcels_before.end());

    prc.run_simulation(4);
    std::vector<std::string> stranded_parcels = prc.get_stranded_parcels();
    assert(std::find(stranded_parcels.begin(), stranded_parcels.end(), "P2Ludhiana4") == stranded_parcels.end());
    // delete the prc object
    // prc.~PRC();
    cout << "test_case_1_successfully" << endl;
}

void test_case_2()
{
    // create a PRC object
    PRC prc(5, 5);
    // create a graph
    prc.create_graph("samples/5/graph.txt");
    prc.process_parcels("samples/5/bookings.txt");
    prc.run_simulation(4);
    assert(prc.all_parcels_delivered() == false);
    std::vector<std::string> delivered_parcels = prc.get_delivered_parcels();
    assert(std::find(delivered_parcels.begin(), delivered_parcels.end(), "P31") == delivered_parcels.end());
    assert(prc.get_parcels_delivered_up_to_time_tick(4).size() == 25);
    cout << "test_case_2_successfully" << endl;
}

void test_case_3()
{
    // create a PRC object
    PRC prc(2, 2);
    // create a graph
    prc.create_graph("samples/1/graph.txt");
    prc.process_parcels("samples/1/bookings.txt");
    prc.run_simulation(20);
    assert(prc.time_tick < 20);
    cout << "test_case_3_successfully" << endl;
}

void test_case_4()
{
    // create a PRC object
    PRC prc(5, 5);
    // create a graph
    prc.create_graph("samples/3/graph.txt");
    prc.process_parcels("samples/3/bookings.txt");

    // read the graph file and check if the graph is created correctly
    assert(prc.graph.vertices.size() == 30);
    assert(prc.graph.edges.size() == 119);
    cout << "test_case_4_successfully" << endl;
}

void test_case_5()
{
    // create a PRC object
    PRC prc(5, 5);
    // create a graph
    prc.create_graph("samples/4/graph.txt");
    prc.process_parcels("samples/4/bookings.txt");

    // check bfs
    std::vector<std::string> bfs_path = prc.graph.bfs("Mumbai", "Ahmedabad");
    assert(bfs_path.size() == 3);
    assert(bfs_path[0] == "Mumbai");
    assert(bfs_path[1] == "Nashik");
    assert(bfs_path[2] == "Ahmedabad");
    cout << "test_case_5_successfully" << endl;
}

void test_case_6()
{
    // create a PRC object
    PRC prc(5, 5);
    // create a graph
    prc.create_graph("samples/4/graph.txt");
    prc.process_parcels("samples/4/bookings.txt");

    std::vector<std::string> dfs_path = prc.graph.dfs("Chennai", "Rohtak");
    // for (auto &i : dfs_path)
    // {
    //     cout << i << endl;
    // }
    assert(std::find(dfs_path.begin(), dfs_path.end(), "Tirupati") == dfs_path.end());
    cout << "test_case_6_successfully" << endl;
}

int main()
{
    // test_case_1();
    test_case_2();
    test_case_3();
    test_case_4();
    test_case_5();
    test_case_6();
    return 0;
}
