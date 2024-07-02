#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;
class Vehicle;

class Trip
{
public:
    Trip(Vehicle *vehicle, std::string pick_up_location, std::string drop_location, int departure_time)
        : vehicle(vehicle), pick_up_location(pick_up_location), drop_location(drop_location), departure_time(departure_time), booked_seats(0) {}

    // Getter functions
    Vehicle *getVehicle() const
    {
        return vehicle;
    }

    std::string getPickUpLocation() const
    {
        return pick_up_location;
    }

    std::string getDropLocation() const
    {
        return drop_location;
    }

    int getDepartureTime() const
    {
        return departure_time;
    }

    int getBookedSeats() const
    {
        return booked_seats;
    }

    // Setter functions
    void setVehicle(Vehicle *v)
    {
        vehicle = v;
    }

    void setPickUpLocation(std::string location)
    {
        pick_up_location = location;
    }

    void setDropLocation(std::string location)
    {
        drop_location = location;
    }

    void setDepartureTime(int time)
    {
        departure_time = time;
    }

    void setBookedSeats(int seats)
    {
        booked_seats = seats;
    }

private:
    Vehicle *vehicle;
    std::string pick_up_location;
    std::string drop_location;
    int departure_time;
    int booked_seats;
};

class BinaryTreeNode
{
public:
    BinaryTreeNode(int departuretime = 0, Trip *tripenodeptr = nullptr, BinaryTreeNode *parentptr = nullptr)
        : leftptr(nullptr), rightptr(nullptr), parentptr(parentptr), departuretime(departuretime), tripnodeptr(tripenodeptr) {}

    // Getter functions
    BinaryTreeNode *getLeftPtr() const
    {
        return leftptr;
    }

    BinaryTreeNode *getRightPtr() const
    {
        return rightptr;
    }

    BinaryTreeNode *getParentPtr() const
    {
        return parentptr;
    }

    int getDepartureTime() const
    {
        return departuretime;
    }

    Trip *getTripNodePtr() const
    {
        return tripnodeptr;
    }

    // Setter functions
    void setLeftPtr(BinaryTreeNode *left)
    {
        leftptr = left;
    }

    void setRightPtr(BinaryTreeNode *right)
    {
        rightptr = right;
    }

    void setParentPtr(BinaryTreeNode *parent)
    {
        parentptr = parent;
    }

    void setDepartureTime(int time)
    {
        departuretime = time;
    }

    void setTripNodePtr(Trip *trip)
    {
        tripnodeptr = trip;
    }

private:
    BinaryTreeNode *leftptr;
    BinaryTreeNode *rightptr;
    BinaryTreeNode *parentptr;
    int departuretime;
    Trip *tripnodeptr;
};

class TransportService
{
public:
    TransportService(std::string name) : name(name), BSThead(nullptr) {}

    // Getter functions
    std::string getName() const
    {
        return name;
    }

    BinaryTreeNode *getBSTHead() const
    {
        return BSThead;
    }

    // Setter functions
    void setName(std::string service_name)
    {
        name = service_name;
    }

    void setBSTHead(BinaryTreeNode *node)
    {
        BSThead = node;
    }

    void addTrip(int key, Trip *trip)
    {

        BinaryTreeNode *new_node = new BinaryTreeNode(key, trip);
        BinaryTreeNode *temp = BSThead;
        BinaryTreeNode *parent = nullptr;
        while (temp != nullptr)
        {
            parent = temp;
            if (key < temp->getDepartureTime())
            {
                temp = temp->getLeftPtr();
            }
            else
            {
                temp = temp->getRightPtr();
            }
        }
        new_node->setParentPtr(parent);
        if (parent == nullptr)
        {

            BSThead = new_node;
            BSThead->setTripNodePtr(new_node->getTripNodePtr());
        }
        else if (key < parent->getDepartureTime())
        {
            parent->setLeftPtr(new_node);
            parent->getLeftPtr()->setTripNodePtr(new_node->getTripNodePtr());
        }
        else
        {
            parent->setRightPtr(new_node);
            parent->getRightPtr()->setTripNodePtr(new_node->getTripNodePtr());
        }
    }

private:
    std::string name;
    BinaryTreeNode *BSThead;
};

class Vehicle
{
public:
    Vehicle(std::string vehicle_number, int seating_capacity)
        : vehicle_number(vehicle_number), seating_capacity(seating_capacity) {}
    Vehicle *vehicle;

    // Getter functions
    std::string getVehicleNumber() const
    {
        return vehicle_number;
    }

    int getSeatingCapacity() const
    {
        return seating_capacity;
    }

    // Setter functions
    void setVehicleNumber(std::string number)
    {
        vehicle_number = number;
    }

    void setSeatingCapacity(int capacity)
    {
        seating_capacity = capacity;
    }

    void addTrip(Trip *trip)
    {
        trips.push_back(trip);
    }
    vector<Trip *> getTrips()
    {
        return trips;
    }

private:
    std::string vehicle_number;
    int seating_capacity;
    std::vector<Trip *> trips;
};

class Location
{
public:
    Location(std::string name) : name(name) {}

    // Getter functions
    std::string getName() const
    {
        return name;
    }

    TransportService *getServicePtr(std::string droplocation) const
    {
        for (int i = 0; i < serviceptrs.size(); i++)
        {
            if (serviceptrs[i]->getName() == droplocation)
            {
                return serviceptrs[i];
                break;
            }
        }
    }
    const std::vector<Trip *> &getTrips() const
    {
        return trips;
    }
    // Setter functions
    void setName(std::string location_name)
    {
        name = location_name;
    }
    const std::vector<TransportService *> &getserviceptrs() const
    {

        return serviceptrs;
    }
    TransportService *setServicePtr(std::string droplocation)
    {
        TransportService *service_obj = new TransportService(droplocation);
        return service_obj;
    }

    void addTrip(Trip *trip)
    {
        trips.push_back(trip);
        int flag = 1;
        if (serviceptrs.size() == 0)
        {
            TransportService *service = new TransportService(trip->getDropLocation());
            serviceptrs.push_back(service);

            getServicePtr(trip->getDropLocation())->addTrip(trip->getDepartureTime(), trip);
        }
        else
        {
            for (int i = 0; i < serviceptrs.size(); i++)
            {
                if (serviceptrs[i]->getName() == trip->getDropLocation())
                {
                    flag = 0;
                    getServicePtr(trip->getDropLocation())->addTrip(trip->getDepartureTime(), trip);
                }
            }
            if (flag == 1)
            {
                TransportService *service = new TransportService(trip->getDropLocation());
                serviceptrs.push_back(service);
                getServicePtr(trip->getDropLocation())->addTrip(trip->getDepartureTime(), trip);
            }
        }
    }

private:
    std::string name;
    std::vector<TransportService *> serviceptrs;
    std::vector<Trip *> trips;
};

class BinaryTree
{
protected:
    BinaryTreeNode *root;

public:
    BinaryTree() : root(nullptr) {}

    int getHeight() const
    {
        // Implement this function to return the height of the tree
        return new_height(root); // Placeholder
    }
    int getNumberOfNodes() const
    {
        // Implement this function to return the number of nodes in the tree
        return new_counting(root); // Placeholder
    }
    int new_height(BinaryTreeNode* node) const
    {
        if(node==nullptr)
        {
            return 0;
        }
        else
        {
          return 1+max(new_height(node->getLeftPtr()),new_height(node->getRightPtr()));
        }   
    }
    int new_counting(BinaryTreeNode* node) const
    {
       if(node==nullptr)
       {
        return 0;
       }
       else{
        return 1+new_counting(node->getLeftPtr())+new_counting(node->getRightPtr());
       }
    }
};

class BinarySearchTree : public BinaryTree
{
public:
    BinarySearchTree() {}

    BinaryTreeNode *getElementWithMinimumKey() const
    {
        // Implement this function to return the element with the minimum key
        BinaryTreeNode *temp = root;
        while (temp != nullptr && temp->getLeftPtr() != nullptr)
        {
            temp = temp->getLeftPtr();
        }
        return temp; // Placeholder
    }

    BinaryTreeNode *getElementWithMaximumKey() const
    {
        // Implement this function to return the element with the maximum key
        BinaryTreeNode *temp = root;
        while (temp != nullptr && temp->getRightPtr() != nullptr)
        {
            temp = temp->getRightPtr();
        }
        return temp; // Placeholder
    }

    BinaryTreeNode *searchNodeWithKey(int key) const
    {
        // Implement this function to search for a node with the given key or the next larger key
        BinaryTreeNode *current = root;
        while (current!= NULL &&key!=current->getDepartureTime()  )
        {
            if (key < current->getDepartureTime())
            {
                current = current->getLeftPtr();
            }
            else
            {
                current = current->getRightPtr();
            }
        }
        return current;
    }

    BinaryTreeNode *getSuccessorNode(BinaryTreeNode *node) const
    {
        // Implement this function to return the successor node of the given node
        BinaryTreeNode *temp = root;
        if (node->getRightPtr() != nullptr)
        {
            node = node->getRightPtr();
            while (node != nullptr && node->getLeftPtr() != nullptr)
            {
                node = node->getLeftPtr();
            }
            return node;
        }

        else
        {
            BinaryTreeNode *new_node = node->getParentPtr();
            while (new_node != nullptr && node == new_node->getRightPtr())
            {
                node = new_node;
                new_node = new_node->getParentPtr();
            }
            return new_node;
        }
        return nullptr;
    }

    BinaryTreeNode *getSuccessorNodeByKey(int key) const
    {
        // Implement this function to return the successor node by key
        BinaryTreeNode *temp = root;
        BinaryTreeNode *successor_node = nullptr;
        while (temp->getDepartureTime() != key && temp != nullptr)
        {
            if (key < temp->getDepartureTime())
            {
                successor_node = temp;
                temp = temp->getLeftPtr();
            }
            else if (key > temp->getDepartureTime())
            {
                temp = temp->getRightPtr();
            }
        }
        if (temp == nullptr)
        {
            return nullptr; // Placeholder
        }
        else
        {
            return getSuccessorNode(temp);
        }
    }

    BinaryTreeNode *getPredecessorNode(BinaryTreeNode *node) const
    {
        // Implement this function to return the predecessor node of the given node
        if (node->getLeftPtr() != nullptr)
        {
            node = node->getLeftPtr();
            while (node != nullptr && node->getRightPtr() != nullptr)
            {
                node = node->getRightPtr();
            }
            return node;
        }
        else
        {
            BinaryTreeNode *new_node = node->getParentPtr();
            while (new_node != nullptr && node == new_node->getLeftPtr())
            {
                node = new_node;
                new_node = new_node->getParentPtr();
            }
        }
        return nullptr; // Placeholder
    }

    BinaryTreeNode *getPredecessorNodeByKey(int key) const
    {
        // Implement this function to return the predecessor node by key
        BinaryTreeNode *temp = root;
        while (temp->getDepartureTime() != key)
        {
            if (key < temp->getDepartureTime())
            {
                temp = temp->getLeftPtr();
            }
            else if (key > temp->getDepartureTime())
            {
                temp = temp->getRightPtr();
            }
        }
        if (temp != nullptr)
        {
            BinaryTreeNode *predecessor_node = getPredecessorNode(temp);
            return predecessor_node;
        }
        else
        {
            return nullptr; // Placeholder
        }
    }
};

class TravelDesk
{
public:
    void addTrip(std::string vehicle_number, int seating_capacity, std::string pick_up_location, std::string drop_location, int departure_time)
    {
        // Implement this function to add a trip
        Vehicle *record = new Vehicle(vehicle_number, seating_capacity);
        int flag = 1, t = 1;
        if (vehicles.size() == 0)
        {
            vehicles.push_back(record);
            Trip *new_rec = new Trip(vehicles[0], pick_up_location, drop_location, departure_time);
            record->addTrip(new_rec);
        }
        else
        {
            for (int i = 0; i < vehicles.size(); i++)
            {
                if (vehicles[i]->getVehicleNumber() == record->getVehicleNumber())
                {
                    flag = 0;
                    Trip *new_rec = new Trip(vehicles[i], pick_up_location, drop_location, departure_time);
                    vehicles[i]->addTrip(new_rec);
                }
            }
            if (flag == 1)
            {
                vehicles.push_back(record);
                Trip *new_rec = new Trip(vehicles[vehicles.size() - 1], pick_up_location, drop_location, departure_time);
                record->addTrip(new_rec);
            }
        }
        Location *location = new Location(pick_up_location);
        if (locations.size() == 0)
        {
            locations.push_back(location);
            Trip *new_rec = new Trip(vehicles[0], pick_up_location, drop_location, departure_time);
            location->addTrip(new_rec);
        }
        else
        {
            for (int i = 0; i < locations.size(); i++)
            {
                if (locations[i]->getName() == location->getName())
                {
                    t = 0;
                    Trip *new_rec = new Trip(vehicles[i], pick_up_location, drop_location, departure_time);
                    locations[i]->addTrip(new_rec);
                }
            }
            if (t == 1)
            {
                locations.push_back(location);
                Trip *new_rec = new Trip(vehicles[vehicles.size() - 1], pick_up_location, drop_location, departure_time);
                location->addTrip(new_rec);
            }
        }
    }
    std::vector<Trip *> showTrips(std::string pick_up_location, int after_time, int before_time)
    {
        // Implement this function to retrieve trips within a specified time range
        vector<Trip *> trips1;
        for (int i = 0; i < locations.size(); i++)
        {
            if (locations[i]->getName() == pick_up_location)
            {
                for (int j = 0; j < locations[i]->getserviceptrs().size(); j++)
                {
                    BinaryTreeNode *root = locations[i]->getserviceptrs()[j]->getBSTHead();
                    BinaryTreeNode *temp = root;
                    inorderTraversal1(root);
                    for (int k1 = 0; k1 < keys1.size(); k1++)
                    {
                        if (keys1[k1] > after_time && keys1[k1] < before_time)
                        {
                            new_keys1.push_back(keys1[k1]);
                        }
                    }
                    for (int k2 = 0; k2 < new_keys1.size(); k2++)
                    {
                        if (root->getDepartureTime() == new_keys1[k2])
                        {
                            Trip *trip = temp->getTripNodePtr();
                            trips1.push_back(trip);
                        }
                        else
                        {
                            while (temp->getDepartureTime() != new_keys1[k2])
                            {
                                if (new_keys1[k2] < temp->getDepartureTime())
                                {
                                    temp = temp->getLeftPtr();
                                }
                                else if (new_keys1[k2] > temp->getDepartureTime())
                                {
                                    temp = temp->getRightPtr();
                                }
                                else if (temp == nullptr)
                                {
                                    break;
                                }
                            }

                            Trip *trip = temp->getTripNodePtr();
                            trips1.push_back(trip);
                        }
                    }
                    keys1.clear();
                    new_keys1.clear();
                }
            }
        }
        return trips1; // Placeholder
    }
    std::vector<Trip *> showTripsbydestination(std::string pick_up_location, std::string destination, int after_time, int before_time)
    {
        std::vector<Trip *> trips;
        // Implement this function to retrieve trips within a specified time range form pickup to droplocatin
        for (int i = 0; i < locations.size(); i++)
        {
            for (int j = 0; j < locations[i]->getserviceptrs().size(); j++)
            {
                if (locations[i]->getName() == pick_up_location && locations[i]->getserviceptrs()[j]->getName() == destination)
                {
                    BinaryTreeNode *root = locations[i]->getserviceptrs()[j]->getBSTHead();
                    BinaryTreeNode *temp = root;
                    inorderTraversal(root);
                    for (int k1 = 0; k1 < keys.size(); k1++)
                    {
                        if (keys[k1] > after_time && keys[k1] < before_time)
                        {
                            new_keys.push_back(keys[k1]);
                        }
                    }
                    for (int k2 = 0; k2 < new_keys.size(); k2++)
                    {
                        if (root->getDepartureTime() == new_keys[k2])
                        {
                            Trip *trip = temp->getTripNodePtr();
                            trips.push_back(trip);
                        }
                        else
                        {
                            while (temp->getDepartureTime() != new_keys[k2])
                            {
                                if (new_keys[k2] < temp->getDepartureTime())
                                {
                                    temp = temp->getLeftPtr();
                                }
                                else if (new_keys[k2] > temp->getDepartureTime())
                                {
                                    temp = temp->getRightPtr();
                                }
                            }
                            Trip *trip = temp->getTripNodePtr();
                            trips.push_back(trip);
                        }
                    }
                }
            }
        }
        return trips; // Placeholder
    }

    Trip *bookTrip(std::string pick_up_location, std::string drop_location, std::string vehicle_number, int departure_time)
    {
        // Implement this function to book a trip

        for (int i = 0; i < locations.size(); i++)
        {
            for (int j = 0; j < locations[i]->getserviceptrs().size(); j++)
            {
                if (locations[i]->getName() == pick_up_location && locations[i]->getserviceptrs()[j]->getName() == drop_location)
                {
                    BinaryTreeNode *root = locations[i]->getserviceptrs()[j]->getBSTHead();
                    BinaryTreeNode *temp = root;
                    int key = departure_time;
                    while (temp->getDepartureTime() != key)
                    {
                        if (key < temp->getDepartureTime())
                        {
                            temp->getLeftPtr();
                        }
                        else
                        {
                            temp = temp->getRightPtr();
                        }
                    }
                    int count = temp->getTripNodePtr()->getBookedSeats();
                    if (temp->getTripNodePtr()->getVehicle()->getSeatingCapacity() >= count + 1)
                    {
                        count++;
                        temp->getTripNodePtr()->setBookedSeats(count);
                        Trip *trip = temp->getTripNodePtr();
                        return trip;
                    }
                }
            }
        }
        // Placeholder
    }
    Location *getLocation(std::string location)
    {
        for (Location *L : locations)
        {
            if (L->getName() == location)
            {
                return L;
            }
        }
        return nullptr;
    }
    void inorderTraversal1(BinaryTreeNode *root)
    {
        BinaryTreeNode *temp = root;
        if (temp == NULL)
        {
            return;
        }
        inorderTraversal1(temp->getLeftPtr());
        keys1.push_back(temp->getDepartureTime());
        //    cout<<keys1.size()<<endl;
        inorderTraversal1(temp->getRightPtr());
    }
    void inorderTraversal(BinaryTreeNode *root)
    {
        BinaryTreeNode *temp = root;
        if (temp == NULL)
        {
            return;
        }
        inorderTraversal(temp->getLeftPtr());
        keys.push_back(temp->getDepartureTime());
        inorderTraversal(temp->getRightPtr());
    }
    void read_inputFile(string filepath)
    {
        string line;
        string element;
        ifstream file(filepath);
        stringstream buffer;
        if (file.is_open())
        {
            buffer << file.rdbuf();
            file.close();
            element = buffer.str();
        }
        istringstream stream(element);
        while (getline(stream, line, '\n'))
        {
            traveldata.push_back(line);
        }
        for (int i = 0; i < traveldata.size(); i++)
        {
            istringstream stream(traveldata[i]);
            string name;
            int itr = 1, itr1 = 1;
            int flag = 1;
            string element;
            string vehicle_num, pick_up, drop, first_name, destination;
            int capacity, departure_time, after_time, before_time;
            while (getline(stream, element, ' '))
            {
                if (itr == 1)
                {
                    first_name = element;
                    itr++;
                }
                else if (itr == 2 && first_name == "ADDTRIP")
                {
                    vehicle_num = element;
                    itr++;
                }
                else if (itr == 3 && first_name == "ADDTRIP")
                {
                    capacity = stoi(element);
                    itr++;
                }
                else if (itr == 4 && first_name == "ADDTRIP")
                {
                    pick_up = element;
                    itr++;
                }
                else if (itr == 5 && first_name == "ADDTRIP")
                {
                    drop = element;
                    itr++;
                }
                else if (itr == 6 && first_name == "ADDTRIP")
                {
                    element = element.substr(0, 2);
                    departure_time = stoi(element);
                    addTrip(vehicle_num, capacity, pick_up, drop, departure_time);
                    itr = 1;
                }
                else if (itr == 2 && first_name == "SHOWTRIPSBYDESTINATION")
                {
                    pick_up = element;
                    itr++;
                }
                else if (itr == 3 && first_name == "SHOWTRIPSBYDESTINATION")
                {
                    drop = element;
                    itr++;
                }
                else if (itr == 4 && first_name == "SHOWTRIPSBYDESTINATION")
                {
                    element = element.substr(0, 2);
                    after_time = stoi(element);
                    itr++;
                }
                else if (itr == 5 && first_name == "SHOWTRIPSBYDESTINATION")
                {
                    element = element.substr(0, 2);
                    before_time = stoi(element);
                    showTripsbydestination(pick_up, drop, after_time, before_time);
                    itr = 1;
                }
                else if (itr == 2 && first_name == "SHOWTRIPS")
                {
                    pick_up = element;
                    cout << pick_up << " ";
                    itr++;
                }
                else if (itr == 3 && first_name == "SHOWTRIPS")
                {
                    element = element.substr(0, 2);
                    after_time = stoi(element);
                    cout << after_time << " ";
                    itr++;
                }
                else if (itr == 4 && first_name == "SHOWTRIPS")
                {
                    element = element.substr(0, 2);
                    before_time = stoi(element);
                    cout << before_time << endl;
                    showTrips(pick_up, after_time, before_time);
                    itr == 1;
                }
            }
        }
    }
    void display1()
    {
        for (int i = 0; i < locations.size(); i++)
        {
            for (int j = 0; j < locations[i]->getserviceptrs().size(); j++)
            {
                if (locations[i]->getserviceptrs()[j]->getBSTHead()->getRightPtr() != nullptr)
                {
                    cout << locations[i]->getserviceptrs()[j]->getBSTHead()->getRightPtr()->getDepartureTime() << endl;
                }
            }
        }
        cout << locations[3]->getserviceptrs()[0]->getBSTHead()->getRightPtr()->getDepartureTime() << endl;
    }

private:
    std::vector<Vehicle *> vehicles;
    std::vector<Location *> locations;
    vector<string> traveldata;
    vector<int> keys;
    vector<int> new_keys;
    vector<int> new_keys1;
    vector<int> keys1;
};