#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class cNode
{
public:
    std::string myName;
    std::vector<cNode *> adjacent;
    cNode(const std::string &name)
        : myName(name)
    {
    }
};

class cGraph
{
public:
    std::vector<cNode *> myNode;
};

std::vector<cNode *>::iterator
search_node(
    std::vector<cNode *> &v,
    const std::string &name)
{
    return std::find_if(
        v.begin(), v.end(),
        [&](cNode *n)
        {
            return n->myName == name;
        });
}

std::vector<cNode *>::iterator
search_node(
    cGraph &g,
    const std::string &name)
{
    return search_node(g.myNode, name);
}

bool search_arc(
    cGraph &g,
    const std::string &c1,
    const std::string &c2)
{
    auto it1 = search_node(g,c1);
    if( it1 == g.myNode.end() )
        return false;
    auto it2 = search_node((*it1)->adjacent,c2);
    if( it2 == (*it1)->adjacent.end() )
        return false;
    return true;
}

void add_node(
    cGraph &g,
    const std::string &c)
{
    if (search_node(g, c) != g.myNode.end())
    {
        std::cout << "\nVyrhyt veche syshtestvuva\n";
        return;
    }

    g.myNode.push_back(new cNode(c));
}

void add_arc(
    cGraph &g,
    const std::string &c1,
    const std::string &c2)
{
    auto it1 = search_node(g, c1);
    auto it2 = search_node(g, c2);
    if (it1 != g.myNode.end() && it2 != g.myNode.end())
        (*it1)->adjacent.push_back(*it2);
}

void del_node(
    cGraph &g,
    const std::string &c)
{
    for (auto &p : g.myNode)
    {
        auto it = search_node(p->adjacent, c);
        if (it != p->adjacent.end())
            p->adjacent.erase(it);
    }
    auto it = search_node(g, c);
    if (it == g.myNode.end())
        return;
    g.myNode.erase(it);
}

void print_menu()
{
    std::cout << "Menu:\n"
                 "1. Dobavqne na vryh ( Add node )\n"
                 "2. Dobavqne na dyga ( Add link )\n"
                 "3. Iztrivane na vryh ( Delete mode )\n"
                 "4. Vizualizirane na grafa ( Display graph )\n"
                 "5. Izhod ( Exit )\n"
                 "Izberete opciq: ";
}

void visualize_graph(cGraph &g)
{
    std::cout << "Graph Visualization:\n";

    for (auto *n : g.myNode)
    {
        std::cout << n->myName << " -> ";
        for (auto *a : n->adjacent)
        {
            std::cout << a->myName << " -> ";
        }
        std::cout << "\n";
    }
}

/// @brief Count links to other nodes
/// @param gr graph
/// @param c node name
/// @return out degree

int outDegree(
    cGraph &g,
    const std::string &c)
{
    auto it = search_node(g,c);
    if( it == g.myNode.end() )
        return 0;
    return (*it)->adjacent.size();
}
int inDegree(
    cGraph &g,
    const std::string &c)
{
    int count = 0;
    for (auto *n : g.myNode)
    {
        auto it = search_node(n->adjacent,c);
        if (it != n->adjacent.end())
            count++;
    }
    return count;
}

void deleteNodes1in1out(cGraph &g)
{
    std::vector<std::string> marked;
    for (auto *n : g.myNode)
    {
        if (outDegree(g, n->myName) == 1 &&
            inDegree(g, n->myName) == 1)
            marked.push_back(n->myName);
    }
    for (auto &c : marked)
    {
        del_node(g, c);
    }
}

void test()
{
    cGraph graph;

    add_node(graph, "a");
    add_node(graph, "b");
    add_node(graph, "c");
    add_arc(graph, "a", "b");
    add_arc(graph, "a", "c");
    std::cout << "test ";
    visualize_graph(graph);

    std::cout << "a outDegree " << outDegree(graph, "a")
              << " inDegree " << inDegree(graph, "a") << "\n";
    std::cout << "b outDegree " << outDegree(graph, "b")
              << " inDegree " << inDegree(graph, "b") << "\n";
    std::cout << "c outDegree " << outDegree(graph, "c")
              << " inDegree " << inDegree(graph, "c") << "\n";

    del_node(graph, "b");

    std::cout << "test delete b ";
    visualize_graph(graph);
}

int main()
{
    test();

    cGraph graph;

    char option;
    std::string c, c1, c2;

    do
    {
        print_menu();
        cin >> option;

        switch (option)
        {
        case '1':
            cout << "Vyvedete vryh: ";
            cin >> c;
            add_node(graph, c);
            break;
        case '2':
            cout << "Vyvedete pyrvi vryh na dygata: ";
            cin >> c1;
            cout << "Vyvedete vtori vryh na dygata: ";
            cin >> c2;
            add_arc(graph, c1, c2);
            break;
        case '3':
            cout << "Vyvedete vryh za iztrivane: ";
            cin >> c;
            del_node(graph, c);
            break;
        case '4':
            visualize_graph(graph);
            break;
        case '5':
            cout << "Izhod ot programata.\n";
            break;
        default:
            cout << "Nevalidna opciq!\n";
            break;
        }
    } while (option != '5');

    return 0;
}
