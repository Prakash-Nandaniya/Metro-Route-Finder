#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

// Forward declarations
class MetroStop;
class MetroLine;
class AVLNode;
class Trip;
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
    // constructor
    MetroStop(std::string name, MetroLine *metroLine, int fare)
    {
        stopName = name;
        nextStop = nullptr;
        prevStop = nullptr;
        line = metroLine;
        this->fare = fare;
    }
    // getters

    std::string getStopName() const
    {
        return stopName;
    }

    MetroStop *getNextStop() const
    {
        return nextStop;
    }

    MetroStop *getPrevStop() const
    {
        return prevStop;
    }

    MetroLine *getLine() const
    {
        return line;
    }

    int getFare() const
    {
        return fare;
    }
    // setters
    void setNextStop(MetroStop *next)
    {
        nextStop = next;
    }

    void setPrevStop(MetroStop *prev)
    {
        prevStop = prev;
    }
};

// string to int function
int string_to_int(string str)
{
    int ans = 0;
    for (int i = 0; i < str.size(); i++)
    {
        switch (str[i])
        {
        case '1':
        {
            ans = ans * 10 + 1;
            break;
        }
        case '2':
        {
            ans = ans * 10 + 2;
            break;
        }
        case '3':
        {
            ans = ans * 10 + 3;
            break;
        }
        case '4':
        {
            ans = ans * 10 + 4;
            break;
        }
        case '5':
        {
            ans = ans * 10 + 5;
            break;
        }
        case '6':
        {
            ans = ans * 10 + 6;
            break;
        }
        case '7':
        {
            ans = ans * 10 + 7;
            break;
        }
        case '8':
        {
            ans = ans * 10 + 8;
            break;
        }
        case '9':
        {
            ans = ans * 10 + 9;
            break;
        }
        case '0':
        {
            ans = ans * 10 + 0;
            break;
        }
        default:
        {
            break;
        }
        }
    }
    return ans;
}

// MetroLine class
class MetroLine
{
private:
    std::string lineName;
    MetroStop *node;

public:
    // constructor
    MetroLine(std::string name)
    {
        lineName = name;
        node = nullptr;
    }
    // Getter
    std::string getLineName() const
    {
        return lineName;
    }
    MetroStop *getNode() const
    {
        return node;
    }
    int getTotalStops()
    {
        int ans = 0;
        MetroStop *temp = this->getNode();
        while (1)
        {
            if (temp == 0)
            {
                ans = ans ;
                return ans;
            }
            else
            {
                ans++;
                temp = temp->getNextStop();
            }
        }
    }

    // populateline function
    void populateLine(string file_path)
    {
        vector<string> row;
        string line, word;
        fstream file(file_path, ios::in);
        string str = "";
        MetroStop *prev = 0;
        while (getline(file, line))
        {
            row.clear();
            stringstream str(line);
            if (line == "")
                break;
            string name = line;
            while (getline(str, word, ' '))
            {
                row.push_back(word);
            }
            while (1)
            {
                name.erase(name.length() - 1);
                if (name[name.length() - 1] == ' ')
                {
                    name.erase(name.length() - 1);
                    break;
                }
            }
            string s = row[row.size() - 1];
            while (1)
            {
                if (s[s.length() - 1] == ',')
                {
                    s.erase(s.length() - 1);
                }
                else
                {
                    break;
                }
            }
            int fare = string_to_int(s);
            MetroStop *stop = new MetroStop(name, this, fare);

            if (prev != 0)
            {
                prev->setNextStop(stop);
                stop->setPrevStop(prev);
            }
            else
            {
                node = stop;
            }
            prev = stop;
        }
    }

    void setNode(MetroStop *node)
    {
        this->node = node;
    }
    void printLine() const
    {
        MetroStop *stop = node;
        while (stop != nullptr)
        {
            cout << stop->getStopName() << endl;
            stop = stop->getNextStop();
        }
    }
};

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
    parent = NULL;
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

int test = 0;

// AVLTree class
class AVLTree
{
private:
    AVLNode *root;

public:
    // constructor
    AVLTree()
    {
        root = 0;
    }
    AVLNode *getRoot() const
    {
        return root;
    }

    void setRoot(AVLNode *root)
    {
        this->root = root;
    }

    int height(AVLNode *node)
    {
        if (node == 0)
        {
            return 0;
        }
        int left = height(node->getLeft());
        int right = height(node->getRight());
        return max(left, right) + 1;
    }

    int balanceFactor(AVLNode *node)
    {
        if (node == NULL)
            return 0;
        return height(node->getLeft()) - height(node->getRight());
    }

    AVLNode *rotateLeft(AVLNode *x)
    {
        AVLNode *y = x->getRight();
        AVLNode *T2 = y->getLeft();
        AVLNode *x_parent = x->getParent();
        x->setParent(y);
        if (T2 != 0)
        {
            T2->setParent(x);
        }
        y->setLeft(x);
        x->setRight(T2);
        return y;
    }

    AVLNode *rotateRight(AVLNode *y)
    {
        AVLNode *x = y->getLeft();
        AVLNode *T2 = x->getRight();
        AVLNode *y_parent = y->getParent();
        y->setParent(x);
        if (T2 != 0)
        {
            T2->setParent(y);
        }
        x->setRight(y);
        y->setLeft(T2);
        return x;
    }

    int stringCompare(string s1, string s2)
    {
        // use strcmp

        char *c1 = new char[s1.length() + 1];
        strcpy(c1, s1.c_str());

        char *c2 = new char[s2.length() + 1];
        strcpy(c2, s2.c_str());

        int result = strcmp(c1, c2);
        return result;
    }

    // inorder traversal
    void inOrderTraversal(AVLNode *root)
    {
        if (root == NULL)
        {
            return;
        }
        inOrderTraversal(root->getLeft());
        cout << root->getStopName() << endl;
        inOrderTraversal(root->getRight());
        return;
    }

    // calculaing lexicographical value
    int lex_order(string s1, string s2)
    {
        int l1 = s1.length();
        int l2 = s2.length();
        for (int i = 0; (i < l1) && (i < l2); i++)
        {
            if (int(s1[i]) == int(s2[i]))
            {
                continue;
            }
            else if (int(s1[i]) < int(s2[i]))
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        if (l1 == l2)
        {
            return -1;
        }
        else if (l1 < l2)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    // adding AVLNodes in AVLTree
    AVLNode *addnode(string &to_add, AVLNode *root, MetroStop *ptr)
    {
        if (root == NULL)
        {
            AVLNode *node = new AVLNode(to_add);
            node->addMetroStop(ptr);
            return node;
        }
        string s = root->getStopName();
        if (lex_order(to_add, s) == -1)
        {
            root->addMetroStop(ptr);
            return root;
        }
        if (lex_order(to_add, s))
        {
            root->setLeft(addnode(to_add, root->getLeft(), ptr));
            root->getLeft()->setParent(root);
        }
        else
        {
            root->setRight(addnode(to_add, root->getRight(), ptr));
            root->getRight()->setParent(root);
        }
        // getting balance factor
        int balance = balanceFactor(root);
        string s1 = root->getStopName();
        // Left  Case
        if (balance == 2)
        {
            string s = root->getLeft()->getStopName();
            // Left Left case
            if (lex_order(to_add, s))
            {
                return rotateRight(root);
            }
            // Left Right case
            if (!lex_order(to_add, s))
            {
                root->setLeft(rotateLeft(root->getLeft()));
                return rotateRight(root);
            }
        }

        // Right Case
        if (balance == -2)
        {
            string s = root->getRight()->getStopName();
            // Right Right case
            if (lex_order(s, to_add))
            {
                return rotateLeft(root);
            }
            // Right Left case
            if (!lex_order(s, to_add))
            {
                root->setRight(rotateRight(root->getRight()));
                return rotateLeft(root);
            }
        }
        return root;
    }

    void insert(AVLNode *root, MetroStop *metroStop)
    {
        string to_add = metroStop->getStopName();
        AVLNode *x = addnode(to_add, root, metroStop);
        this->setRoot(x);
    }

    void populateTree(MetroLine *metroLine)
    {
        MetroStop *temp = metroLine->getNode();
        AVLNode *AVLTree_root = this->getRoot();
        if (AVLTree_root != 0)
        {
            if (AVLTree_root->getLeft() == 0 && AVLTree_root->getRight() == 0)
            {
                temp = temp->getNextStop();
            }
        }
        if (AVLTree_root == 0)
        {
            AVLNode *node = new AVLNode(temp->getStopName());
            node->addMetroStop(temp);
            this->setRoot(node);
            temp = temp->getNextStop();
        }
        while (temp != 0)
        {
            insert(this->getRoot(), temp);
            temp = temp->getNextStop();
        }
    }

    int getTotalNodes(AVLNode *node)
    {
        if (node == 0)
        {
            return 0;
        }
        int l = getTotalNodes(node->getLeft());
        int r = getTotalNodes(node->getRight());
        return l + r + 1;
    }

    AVLNode *search(AVLNode *node, string &stopname)
    {
        if (node == 0)
        {
            return 0;
        }
        string s = node->getStopName();
        if (s == stopname)
        {
            return node;
        }
        AVLNode *left = search(node->getLeft(), stopname);
        AVLNode *right = search(node->getRight(), stopname);
        if (left != 0)
        {
            return left;
        }
        else if (right != 0)
        {
            return right;
        }
        else
        {
            return 0;
        }
    }

    AVLNode *searchStop(string stopName)
    {
        return search(this->getRoot(), stopName);
    }
};

// Exploration class
class Exploration
{
private:
    std::queue<Trip *> trips;

public:
    // constructor
    Exploration()
    {
    }
    // getter
    std::queue<Trip *> getTrips() const
    {
        return trips;
    }
    // functions
    void enqueue(Trip *trip)
    {
        trips.push(trip);
    }

    Trip *dequeue()
    {
        if (trips.empty())
        {
            return nullptr;
        }
        Trip *trip = trips.front();
        trips.pop();
        // cout << "Dequeued: " << trip->getNode()->getStopName() << endl;
        return trip;
    }

    bool isEmpty() const
    {
        return trips.empty();
    }
};

// Trip class
class Trip
{
private:
    MetroStop *node;
    Trip *prev;

public:
    // constructor
    Trip(MetroStop *metroStop, Trip *previousTrip = 0)
    {
        node = metroStop;
        prev = previousTrip;
    }
    // getter
    MetroStop *getNode() const
    {
        return node;
    }

    Trip *getPrev() const
    {
        return prev;
    }
    // setter
    void setPrev(Trip *prev)
    {
        this->prev = prev;
    }
};

class Path
{
private:
    std::vector<MetroStop *> stops;
    int totalFare;

public:
    // constructor
    Path()
    {
        totalFare = 0;
    }
    // getter
    std::vector<MetroStop *> getStops() const
    {
        return stops;
    }

    int getTotalFare() const
    {
        return totalFare;
    }
    // setter
    void addStop(MetroStop *stop)
    {
        stops.push_back(stop);
    }

    void setTotalFare(int fare)
    {
        totalFare = fare;
    }

    vector<string> getPath() const
    {
        vector<string> ans;
        if (stops.size() == 0)
        {
            return {};
        }
        for (auto stop : stops)
        {
            ans.push_back(stop->getStopName());
        }
        return ans;
    }
};

// PathFinder class
class PathFinder
{
private:
    AVLTree *tree;
    std::vector<MetroLine *> lines;

public:
    string starting_location;
    // constructor
    PathFinder(AVLTree *avlTree, const std::vector<MetroLine *> &metroLines)
    {
        tree = avlTree;
        lines = metroLines;
    }
    // getter
    AVLTree *getTree() const
    {
        return tree;
    }

    const std::vector<MetroLine *> &getLines() const
    {
        return lines;
    }

    void createAVLTree()
    {
        for (int i = 0; i < lines.size(); i++)
        {
            MetroLine *metroline = lines[i];
            tree->populateTree(metroline);
        }
    }

    int test = 0;

    Trip *searchpath_left(std::string origin, std::string destination, vector<string> junction_v_2, vector<Path *> &possible_path, Trip *prev_tail)
    {
        Trip *tail = 0;
        vector<MetroStop *> v = tree->searchStop(origin)->getStops();
        // cout<<v.size()<<endl;
        for (int idx = 0; idx < v.size(); idx++)
        {
            tail = 0;
            MetroStop *curr = v[idx];
            int z = 0;
            while (1)
            {
                if (curr == 0)
                {
                    break;
                }
                Trip *t = new Trip(curr, tail);
                if (z == 0)
                {
                    t->setPrev(prev_tail);
                    z = 1;
                }
                tail = t;
                // cout << curr->getStopName() << endl;
                if (curr->getStopName() == destination)
                {
                    Trip *t = tail;
                    Path *path = new Path();
                    MetroStop *curr_2 = t->getNode();
                    while (t != 0)
                    {
                        curr_2 = t->getNode();
                        path->addStop(curr_2);
                        t = t->getPrev();
                    }
                    possible_path.push_back(path);
                    return 0;
                }
                for (int j = 0; j < junction_v_2.size(); j++)
                {
                    if (junction_v_2[j] == curr->getStopName())
                    {
                        return 0;
                    }
                }
                vector<MetroStop *> v_2 = tree->searchStop(curr->getStopName())->getStops();
                if (v_2.size() != 1)
                {
                    junction_v_2.push_back(curr->getStopName());
                    // cout<<v_2.size()<<endl;
                    for (int i = 0; i < v_2.size(); i++)
                    {
                        if (v_2[i]->getNextStop() != 0)
                        {
                            searchpath_right(v_2[i]->getNextStop()->getStopName(), destination, junction_v_2, possible_path, tail);
                        }
                        if (v_2[i]->getPrevStop() != 0)
                        {
                            searchpath_left(v_2[i]->getPrevStop()->getStopName(), destination, junction_v_2, possible_path, tail);
                        }
                    }
                    return 0;
                }
                curr = curr->getPrevStop();
            }
        }
        return 0;
    }

    Trip *searchpath_right(std::string origin, std::string destination, vector<string> junction_v, vector<Path *> &possible_path, Trip *prev_tail)
    {
        Trip *tail = 0;
        vector<MetroStop *> v = tree->searchStop(origin)->getStops();
        // cout<<v.size()<<endl;
        for (int idx = 0; idx < v.size(); idx++)
        {
            tail = 0;
            MetroStop *curr = v[idx];
            int z = 0;
            while (1)
            {
                if (curr == 0)
                {
                    break;
                }
                Trip *t = new Trip(curr, tail);
                if (z == 0)
                {
                    t->setPrev(prev_tail);
                    z = 1;
                }
                tail = t;
                // cout << curr->getStopName() << endl;
                if (curr->getStopName() == destination)
                {
                    Trip *t = tail;
                    Path *path = new Path();
                    MetroStop *curr_2 = t->getNode();
                    while (t != 0)
                    {
                        curr_2 = t->getNode();
                        path->addStop(curr_2);
                        t = t->getPrev();
                    }
                    possible_path.push_back(path);
                    return 0;
                }
                for (int j = 0; j < junction_v.size(); j++)
                {
                    if (junction_v[j] == curr->getStopName())
                    {
                        return 0;
                    }
                }
                vector<MetroStop *> v_2 = tree->searchStop(curr->getStopName())->getStops();
                if (v_2.size() != 1)
                {
                    junction_v.push_back(curr->getStopName());
                    // cout<<v_2.size()<<endl;
                    for (int i = 0; i < v_2.size(); i++)
                    {
                        if (v_2[i]->getNextStop() != 0)
                        {
                            searchpath_right(v_2[i]->getNextStop()->getStopName(), destination, junction_v, possible_path, tail);
                        }
                        if (v_2[i]->getPrevStop() != 0)
                        {
                            searchpath_left(v_2[i]->getPrevStop()->getStopName(), destination, junction_v, possible_path, tail);
                        }
                    }
                    return 0;
                }
                curr = curr->getNextStop();
            }
        }
        return 0;
    }

    Path *findPath(std::string origin, std::string destination)
    {
        vector<string> junction_v;
        vector<string> junction_v_2;
        junction_v.push_back(origin);
        test = 0;
        starting_location = origin;
        Path *ans = 0;
        int fare = 0;
        MetroStop *curr = tree->searchStop(origin)->getStops()[0];
        vector<Path *> possible_path;
        Trip *tail_right = new Trip(curr, 0);
        Trip *tail_left = new Trip(curr, 0);
        if (curr->getNextStop() != 0)
        {
            searchpath_right(curr->getNextStop()->getStopName(), destination, junction_v, possible_path, tail_right);
        }
        if (curr->getPrevStop() != 0)
        {
            searchpath_left(curr->getPrevStop()->getStopName(), destination, junction_v_2, possible_path, tail_left);
        }
        if (possible_path.size() == 0)
        {
            Path *path = new Path();
            return path;
        }
        int min = INT_MAX;
        for (int i = 0; i < possible_path.size(); i++)
        {
            if (possible_path[i]->getStops().size() < min)
            {
                ans = possible_path[i];
                min = possible_path[i]->getStops().size();
            }
        }
        vector<MetroStop *> stops = ans->getStops();
        curr = 0;
        for (int i = 0; i < (stops.size() - 1); i++)
        {
            if (stops[i + 1]->getLine()->getLineName() != stops[i]->getLine()->getLineName())
            {
                vector<MetroStop *> v1 = tree->searchStop(stops[i]->getStopName())->getStops();
                vector<MetroStop *> v2 = tree->searchStop(stops[i + 1]->getStopName())->getStops();
                int l = 0;
                for (int p = 0; p < v1.size(); p++)
                {
                    if (l == 1)
                    {
                        break;
                    }
                    for (int q = 0; q < v2.size(); q++)
                    {
                        if (v1[p]->getLine()->getLineName() == v2[q]->getLine()->getLineName())
                        {
                            if (v1[p]->getNextStop() != 0)
                            {
                                if (v1[p]->getNextStop()->getStopName() == v2[q]->getStopName())
                                {
                                    fare = fare + abs(v2[q]->getFare() - v1[p]->getFare());
                                    l = 1;
                                    break;
                                }
                            }
                            if (v1[p]->getPrevStop() != 0)
                            {
                                if (v1[p]->getPrevStop()->getStopName() == v2[q]->getStopName())
                                {
                                    fare = fare + abs(v2[q]->getFare() - v1[p]->getFare());
                                    l = 1;
                                    break;
                                }
                            }
                        }
                    }
                }
                continue;
            }
            fare = fare + abs(stops[i]->getFare() - stops[i + 1]->getFare());
        }
        ans->setTotalFare(fare);
        return ans;
    }
};
vector<MetroLine *> lines;


vector<string> getFileNames()
{
    vector<string> filenames;
    filenames.push_back("../linesData/blue.txt");
    filenames.push_back("../linesData/green.txt");
    filenames.push_back("../linesData/magenta.txt");
    filenames.push_back("../linesData/orange.txt");
    filenames.push_back("../linesData/red.txt");
    filenames.push_back("../linesData/violet.txt");
    filenames.push_back("../linesData/yellow.txt");
    return filenames;
}

void PopulateLine()
{
    vector<string> filenames = getFileNames();
    for (int i = 0; i < filenames.size(); i++)
    {
        string lineName = filenames[i].substr(0, filenames[i].length() - 4);
        MetroLine *metroLine = new MetroLine(lineName);
        metroLine->populateLine(filenames[i]);
        lines.push_back(metroLine);
    }
}

vector<string> FindPath(string from,string to,int &fare)
{
    PathFinder *pathFinder = new PathFinder(new AVLTree(), lines);
    pathFinder->createAVLTree();
    Path *path = pathFinder->findPath(from,to);
    fare=path->getTotalFare();
    return path->getPath();
}

int main(int argc, char* argv[])
{
    PopulateLine();
    int fare=0;
    vector<string> path;
    path=FindPath(argv[1],argv[2],fare);
    // cout<<fare<<endl;
    for(auto i:path)
    {
        cout<<i<<endl;
    }
    return 0;
}