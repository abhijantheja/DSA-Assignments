#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

// Forward declarations
class MetroStop;
class MetroLine;
class AVLNode;

// MetroStop class
class MetroStop
{
private:
    std::string stopName;
    MetroStop *nextStop;
    MetroStop *prevStop;
    MetroLine *line;
    int fare;

public:
    MetroStop(std::string name, MetroLine *metroLine, int fare);

    // Getter methods
    std::string getStopName() const;
    MetroStop *getNextStop() const;
    MetroStop *getPrevStop() const;
    MetroLine *getLine() const;
    int getFare() const;

    // Setter methods
    void setNextStop(MetroStop *next);
    void setPrevStop(MetroStop *prev);
};

MetroStop::MetroStop(std::string name, MetroLine *metroLine, int fare)
{
    stopName = name;
    nextStop = nullptr;
    prevStop = nullptr;
    line = metroLine;
    this->fare = fare;
}

std::string MetroStop::getStopName() const
{
    return stopName;
}

MetroStop *MetroStop::getNextStop() const
{
    return nextStop;
}

MetroStop *MetroStop::getPrevStop() const
{
    return prevStop;
}

MetroLine *MetroStop::getLine() const
{
    return line;
}

int MetroStop::getFare() const
{
    return fare;
}

void MetroStop::setNextStop(MetroStop *next)
{
    nextStop = next;
}

void MetroStop::setPrevStop(MetroStop *prev)
{
    prevStop = prev;
}

// MetroLine class
class MetroLine
{
private:
    std::string lineName;
    MetroStop *node;

public:
    MetroLine(std::string name);

    // Getter methods
    std::string getLineName() const;
    MetroStop *getNode() const;

    // Setter methods
    void setNode(MetroStop *node);

    void populateLine(std::string filename);

    // helper function
    void printLine() const;
    int getTotalStops() const;
};

MetroLine::MetroLine(std::string name)
{
    lineName = name;
    node = nullptr;
}

std::string MetroLine::getLineName() const
{
    return lineName;
}

MetroStop *MetroLine::getNode() const
{
    return node;
}

void MetroLine::setNode(MetroStop *node)
{
    this->node = node;
}

void MetroLine::printLine() const
{
    MetroStop *stop = node;
    while (stop != nullptr)
    {
        cout << stop->getStopName() << endl;
        stop = stop->getNextStop();
    }
}

int MetroLine::getTotalStops() const
{
    MetroStop *temp = node;
    int count = 0;
    while (temp != nullptr)
    {
        count++;
        temp = temp->getNextStop();
    }
    return count;
}

void MetroLine::populateLine(std::string filename)
{
    // Read the file and populate the line
    string element;
    string line;
    ifstream file(filename);
    stringstream buffer;
    vector<string> metroline_data;
    vector<string> metroline_data1;
    MetroStop *root = nullptr;
    if (file.is_open())
    {
        buffer << file.rdbuf();
        file.close();
        element = buffer.str();
    }
    istringstream stream(element);
    while (getline(stream, line, '\n'))
    {
        metroline_data.push_back(line);
    }
    for (int i = 0; i < metroline_data.size(); i++)
    {
        istringstream stream(metroline_data[i]);
        while (getline(stream, line, ','))
        {
            metroline_data1.push_back(line);
        }
    }
    for (int k = 0; k < metroline_data1.size(); k++)
    {
        string element, stop, sub, sum;
        int count = 0, fare, space_position;
        element = metroline_data1[k];
        for (int j = 0; j < element.size(); j++)
        {
            if (element[j] == 32)
            {
                space_position = j;
            }
        }
        stop = element.substr(0, space_position);
        sum = element.substr(space_position, element.size() - space_position);
        fare = stoi(sum);
        MetroStop *record = new MetroStop(stop, this, fare);
        if (this->node == NULL)
        {
            this->node = record;
        }
        else
        {
            MetroStop *temp = node;
            while (temp->getNextStop() != nullptr)
            {
                temp = temp->getNextStop();
            }
            temp->setNextStop(record);
            record->setPrevStop(temp);
        }
    }
}

// AVLNode class
class AVLNode
{
private:
    std::string stopName;
    std::vector<MetroStop *> stops;
    AVLNode *left;
    AVLNode *right;
    AVLNode *parent;

public:
    AVLNode(std::string name);

    // Getter methods
    std::string getStopName() const;
    const std::vector<MetroStop *> &getStops() const;
    AVLNode *getLeft() const;
    AVLNode *getRight() const;
    AVLNode *getParent() const;

    // Setter methods
    void addMetroStop(MetroStop *metroStop);
    void setLeft(AVLNode *left);
    void setRight(AVLNode *right);
    void setParent(AVLNode *parent);
};

AVLNode::AVLNode(std::string name)
{
    stopName = name;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

std::string AVLNode::getStopName() const
{
    return stopName;
}

const std::vector<MetroStop *> &AVLNode::getStops() const
{
    return stops;
}

AVLNode *AVLNode::getLeft() const
{
    return left;
}

AVLNode *AVLNode::getRight() const
{
    return right;
}

AVLNode *AVLNode::getParent() const
{
    return parent;
}

void AVLNode::setLeft(AVLNode *left)
{
    this->left = left;
}

void AVLNode::setRight(AVLNode *right)
{
    this->right = right;
}

void AVLNode::setParent(AVLNode *parent)
{
    this->parent = parent;
}

void AVLNode::addMetroStop(MetroStop *metroStop)
{
    stops.push_back(metroStop);
}

// AVLTree class
class AVLTree
{
    // Define your AVLTree implementation here.
private:
    AVLNode *root;

public:
    // getter methods
    AVLNode *getRoot() const;

    // setter methods
    void setRoot(AVLNode *root);
    // helper functions
    int height(AVLNode *node);
    int balanceFactor(AVLNode *node);
    AVLNode *rotateLeft(AVLNode *node);
    AVLNode *rotateRight(AVLNode *node);
    AVLNode *balance(AVLNode *node);
    int stringCompare(string s1, string s2);
    AVLNode *insert(AVLNode *node, MetroStop *metroStop);
    AVLNode *populateTree(MetroLine *metroLine);
    void inOrderTraversal(AVLNode *node);
    int getTotalNodes(AVLNode *node);
    AVLNode *searchStop(string stopName);
};

AVLNode *AVLTree::getRoot() const
{
    return root;
}
void AVLTree::setRoot(AVLNode *root)
{
    this->root = root;
}

int AVLTree::height(AVLNode *node)
{
    if (node == NULL)
    {
        return 0;
    }
    else
    {
        int new_height = 1 + max(height(node->getLeft()), height(node->getRight()));
        return new_height;
    }
}

int AVLTree::stringCompare(string s1, string s2)
{
    // use strcmp

    char *c1 = new char[s1.length() + 1];
    strcpy(c1, s1.c_str());

    char *c2 = new char[s2.length() + 1];
    strcpy(c2, s2.c_str());

    int result = strcmp(c1, c2);
    return result;
}

int AVLTree::balanceFactor(AVLNode *node)
{
    if (node == NULL)
    {
        return 0;
    }
    else
    {
        int balancefactor = height(node->getLeft()) - height(node->getRight());
        return balancefactor;
    }
}

AVLNode *AVLTree::rotateLeft(AVLNode *node)
{
    AVLNode *x, *y, *T2;
    x = node;
    y = x->getRight();
    T2 = y->getLeft();
    y->setLeft(x);
    x->setRight(T2);
    if (x->getParent() == nullptr)
    {
        y->setParent(nullptr);
        x->setParent(y);
    }
    else
    {
        if (x->getParent()->getLeft() == x)
        {
            x->getParent()->setLeft(y);
            y->setParent(x->getParent());
            x->setParent(y);
        }
        else
        {
            x->getParent()->setRight(y);
            y->setParent(x->getParent());
            x->setParent(y);
        }
    }
    if (T2 != nullptr)
    {
        T2->setParent(x);
    }
    return y;
}

AVLNode *AVLTree::rotateRight(AVLNode *node)
{
    AVLNode *x, *y, *T2;
    y = node;
    x = y->getLeft();
    T2 = x->getRight();

    x->setRight(y);
    y->setLeft(T2);

    if (y->getParent() == nullptr)
    {
        x->setParent(nullptr);
        y->setParent(x);
    }
    else
    {
        if (y->getParent()->getLeft() == y)
        {
            y->getParent()->setLeft(x);
            x->setParent(y->getParent());
            y->setParent(x);
        }
        else
        {
            y->getParent()->setRight(x);
            x->setParent(y->getParent());
            y->setParent(x);
        }
    }
    if (T2 != nullptr)
    {
        T2->setParent(y);
    }
    return x;
}

AVLNode *AVLTree::balance(AVLNode *node)
{
    AVLNode *parent = node;
    int balance_fac = balanceFactor(parent);
    if (balance_fac > 1 && balanceFactor(parent->getLeft()) > 0)
    {
        parent = rotateRight(parent);
    }
    else if (balance_fac > 1 && balanceFactor(parent->getLeft()) < 0)
    {
        parent->setLeft(rotateLeft(parent->getLeft()));
        parent = rotateRight(parent);
    }
    else if (balance_fac < -1 && balanceFactor(parent->getRight()) < 0)
    {
        parent = rotateLeft(parent);
    }
    else if (balance_fac < -1 && balanceFactor(parent->getRight()) > 0)
    {
        parent->setRight(rotateRight(parent->getRight()));
        parent = rotateLeft(parent);
    }
    return parent;
}

AVLNode *AVLTree::insert(AVLNode *node, MetroStop *metroStop)
{
    AVLNode *temp = node;
    AVLNode *parent = nullptr;
    string key = metroStop->getStopName();
    AVLNode *new_node = new AVLNode(key);
    while (temp != nullptr)
    {
        parent = temp;
        int result = stringCompare(key, temp->getStopName());
        if (result < 0)
        {
            temp = temp->getLeft();
        }
        else if (result > 0)
        {
            temp = temp->getRight();
        }
    }
    new_node->setParent(parent);
    int net_result;
    if (parent != nullptr)
    {
        net_result = stringCompare(key, parent->getStopName());
    }
    if (getRoot() == nullptr)
    {
        node = new_node;
        new_node->addMetroStop(metroStop);
        return node;
    }
    else if (net_result < 0)
    {
        parent->setLeft(new_node);
        new_node->addMetroStop(metroStop);
    }
    else if (net_result > 0)
    {
        parent->setRight(new_node);
        new_node->addMetroStop(metroStop);
    }
    while (parent != nullptr)
    {
        parent = balance(parent);
        if (parent->getParent() == nullptr)
        {
            node = parent;
        }
        parent = parent->getParent();
    }
    return node;
}

AVLNode *AVLTree::populateTree(MetroLine *metroLine)
{
    AVLNode *node = getRoot();
    MetroStop *metroStop = nullptr;
    MetroStop *temp = metroLine->getNode();
    while (temp != nullptr)
    {
        metroStop = temp;

        if (searchStop(metroStop->getStopName()) == NULL)
        {
            node = insert(node, metroStop);
            setRoot(node);
        }
        else
        {
            searchStop(metroStop->getStopName())->addMetroStop(temp);
        }
        temp = temp->getNextStop();
    }
}

void AVLTree::inOrderTraversal(AVLNode *node)
{
    if (node == nullptr)
    {
        return;
    }
    inOrderTraversal(node->getLeft());
    cout << node->getStopName() << endl;
    inOrderTraversal(node->getRight());
}

int AVLTree::getTotalNodes(AVLNode *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return 1 + getTotalNodes(node->getLeft()) + getTotalNodes(node->getRight());
}

AVLNode *AVLTree::searchStop(string stopName)
{
    AVLNode *temp = getRoot();
    while (temp != nullptr)
    {
        int compare = stringCompare(stopName, temp->getStopName());
        if (compare == 0)
        {
            return temp;
            break;
        }
        else if (compare < 0)
        {
            temp = temp->getLeft();
        }
        else
        {
            temp = temp->getRight();
        }
    }
    if (temp == nullptr)
    {
        return temp;
    }
}
// Trip class
class Trip
{
private:
    MetroStop *node;
    Trip *prev;

public:
    Trip(MetroStop *metroStop, Trip *previousTrip);

    // Getter methods
    MetroStop *getNode() const;
    Trip *getPrev() const;
};

Trip::Trip(MetroStop *metroStop, Trip *previousTrip)
{
    node = metroStop;
    prev = previousTrip;
}

MetroStop *Trip::getNode() const
{
    return node;
}

Trip *Trip::getPrev() const
{
    return prev;
}

// Exploration class is a queue that stores unexplored Trip objects
class Exploration
{
private:
    std::queue<Trip *> trips;

public:
    Exploration();
    // Getter methods
    std::queue<Trip *> getTrips() const;
    // Setter methods
    void enqueue(Trip *trip);
    Trip *dequeue();
    bool isEmpty() const;
};

Exploration::Exploration()
{
}

std::queue<Trip *> Exploration::getTrips() const
{
    return trips;
}

void Exploration::enqueue(Trip *trip)
{
    trips.push(trip);
}

Trip *Exploration::dequeue()
{
    if (trips.empty())
    {
        return nullptr;
    }
    Trip *trip = trips.front();
    trips.pop();
    cout << "Dequeued: " << trip->getNode()->getStopName() << endl;
    return trip;
}

bool Exploration::isEmpty() const
{
    return trips.empty();
}

class Path
{
private:
    std::vector<MetroStop *> stops;
    int totalFare;

public:
    Path();

    // Getter methods
    std::vector<MetroStop *> getStops() const;
    int getTotalFare() const;
    // Setter methods
    void addStop(MetroStop *stop);
    void setTotalFare(int fare);
    // helper functions
    void printPath() const;
};

Path::Path()
{
    totalFare = 0;
}

std::vector<MetroStop *> Path::getStops() const
{
    return stops;
}

int Path::getTotalFare() const
{
    return totalFare;
}

void Path::addStop(MetroStop *stop)
{
    stops.push_back(stop);
}

void Path::setTotalFare(int fare)
{
    totalFare = fare;
}

void Path::printPath() const
{
    for (auto stop : stops)
    {
        cout << stop->getStopName() << endl;
    }
}

// PathFinder class
class PathFinder
{
private:
    AVLTree *tree;
    std::vector<MetroLine *> lines;

public:
    PathFinder(AVLTree *avlTree, const std::vector<MetroLine *> &metroLines);
    void createAVLTree();
    Path *findPath(std::string origin, std::string destination);

    // Getter methods
    AVLTree *getTree() const;
    const std::vector<MetroLine *> &getLines() const;
};

PathFinder::PathFinder(AVLTree *avlTree, const std::vector<MetroLine *> &metroLines)
{
    tree = avlTree;
    lines = metroLines;
}

AVLTree *PathFinder::getTree() const
{
    return tree;
}

const std::vector<MetroLine *> &PathFinder::getLines() const
{
    return lines;
}

void PathFinder::createAVLTree()
{
    tree->setRoot(nullptr);
    for (auto line : lines)
    {
        if (tree->getRoot() == nullptr)
        {
            tree->setRoot(new AVLNode(line->getNode()->getStopName()));
        }
        tree->populateTree(line);
    }
}

Path *PathFinder::findPath(std::string origin, std::string destination)
{
    Trip *prev = nullptr;
    Exploration exp;
    int fare=0;
    Path *path=new Path();
    MetroStop *temp = tree->searchStop(origin)->getStops()[0];
    while (temp!= NULL)
    {
        Trip* trip;
        if (tree->searchStop(temp->getStopName())->getStops().size() == 1)
        {
            trip = new Trip(temp, prev);
            prev = trip;
            if (temp->getStopName() == destination)
            {
                while (trip->getPrev() != nullptr)
                {
                    path->addStop(trip->getNode());
                    fare=trip->getNode()->getFare()-trip->getPrev()->getNode()->getFare();
                    path->setTotalFare(path->getTotalFare()+fare);
                    trip = trip->getPrev();
                }  
                path->addStop(trip->getNode());
                return path;
                break;
            }
        }
        else
        {
            int count1=0,count2=0;
             Trip *trip1;
             Trip* newtrip;
             Trip* newtrip2;
             Path *path=new Path();
            for(auto stop:tree->searchStop(temp->getStopName())->getStops())
            {
            trip1=new Trip(temp,trip);
            exp.enqueue(trip1);
            }
            Trip* new_trip=exp.getTrips().front();
            Trip* duplicate=new_trip;
            MetroStop *current=new_trip->getNode()->getNextStop();
            MetroStop* newcurrent=new_trip->getNode()->getPrevStop();
            Trip* prev2=new_trip;
            Trip* prev3=prev2;
            while(current!=nullptr)
            {
              newtrip=new Trip(current,prev2);
              prev2=newtrip;     
              if(current->getStopName()==destination)
              {      
                while(newtrip->getPrev()!=nullptr)
                {
                    path->addStop(newtrip->getNode());
                    count1=trip->getNode()->getFare()-trip->getPrev()->getNode()->getFare();
                    path->setTotalFare(path->getTotalFare()+count1);
                    newtrip=newtrip->getPrev();
                }
                path->addStop(newtrip->getNode());
                return path;
              }
              current=current->getNextStop();
            }
            if(current==nullptr)
            {
                exp.dequeue();
            }
            while(newcurrent!=nullptr)
            {
                newtrip2=new Trip(newcurrent,prev3);
                prev3=newtrip2;
                if(newcurrent->getStopName()==destination)
                {
                    while(newtrip2->getPrev()!=nullptr)
                    {
                        path->addStop(newtrip2->getNode());
                         count2=trip->getNode()->getFare()-trip->getPrev()->getNode()->getFare();
                    path->setTotalFare(path->getTotalFare()+count2);
                        newtrip2=newtrip2->getPrev();
                    }
                    path->addStop(newtrip2->getNode());
                    return path;
                }
                newcurrent=newcurrent->getPrevStop();
            }
            if(newcurrent==nullptr)
            {
                exp.dequeue();
            }
        }
        temp = temp->getNextStop();
    }
}
vector<MetroLine *> lines;
// int main()
// {
//     string filepath1 = "blue.txt";
//     string name1 = "blue";
//     MetroLine *obj1 = new MetroLine(name1);
//     AVLTree avltree1;
//     obj1->populateLine(filepath1);
//     avltree1.populateTree(obj1);
// }
