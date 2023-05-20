#include <iostream>
#include <vector>

using namespace std;

const int n = 10;

struct link
{
    char key;
    link *next;
} *G[n];

void init(link *gr[n])
{
    for (int i = 0; i < n; i++)
        gr[i] = NULL;
}

int search_node(link *gr[n], char c)
{
    int flag = 0;
    for (int i = 0; i < n; i++)
        if (gr[i])
            if (gr[i]->key == c)
                flag = 1;
    return flag;
}

int search_arc(link *gr[5], char c1, char c2)
{
    int flag = 0;
    if (search_node(gr, c1) && search_node(gr, c2))
    {
        int i = 0;
        link *p;
        do
        {
            if ((gr[i] == NULL) || (gr[i] && gr[i]->key != c1))
                i++;
        } while (gr[i]->key != c1);
        p = gr[i];
        while (p->key != c2 && p->next != NULL)
            p = p->next;
        if (p->key == c2)
            flag = 1;
    }
    return flag;
}

void add_node(link *gr[n], char c)
{
    if (search_node(gr, c))
    {
        cout << "\nVyrhyt veche syshtestvuva\n";
    }
    else
    {
        int j = 0;
        while (gr[j] && (j < n))
            j++;
        if (gr[j] == NULL)
        {
            gr[j] = new link;
            gr[j]->key = c;
            gr[j]->next = NULL;
        }
        else
        {
            cout << "\nPrepylvane na strukturata\n";
        }
    }
}

void add_arc(link *gr[n], char c1, char c2)
{
    if (search_node(gr, c1) && search_node(gr, c2))
    {
        int i = 0;
        link *p;
        while (gr[i]->key != c1)
            i++;
        p = new link;
        p->key = c2;
        p->next = gr[i]->next;
        gr[i]->next = p;
    }
    else
    {
        cout << "\nVryhove ne sushtestvuva";
    }
}

void del_node(link *gr[n], char c)
{
    // loop over nodes in graph
    for (int i = 0; i < n; i++)
    {
        auto *p = gr[i];
        if (!p)
        {
            // undefined node
            continue;
        }

        if (p->key == c)
        {
            // remove node from graph
            gr[i] = 0;
            continue;
        }

        if (!p->next)
        {
            // no adjacent nodes
            continue;
        }

        // search adjacency list for deleted node
        while (true)
        {
            if (p->next->key == c)
            {
                // remove node from adjacency list
                p->next = p->next->next;
            }

            if (!p->next)
                break;
            p = p->next;
        }
    }
}

void print_menu()
{
    cout << "Menu:\n";
    cout << "1. Dobavqne na vryh ( Add node )\n";
    cout << "2. Dobavqne na dyga ( Add link )\n";
    cout << "3. Iztrivane na vryh ( Delete mode )\n";
    cout << "4. Vizualizirane na grafa ( Display graph )\n";
    cout << "5. Izhod ( Exit )\n";
    cout << "Izberete opciq: ";
}

void visualize_graph(link *gr[n])
{
    cout << "Graph Visualization:\n";
    for (int i = 0; i < n; i++)
    {
        if (gr[i])
        {
            cout << gr[i]->key << " -> ";
            link *p = gr[i]->next;
            while (p != NULL)
            {
                cout << p->key << " -> ";
                p = p->next;
            }
            cout << "NULL\n";
        }
    }
    cout << endl;
}

/// @brief Count links to other nodes
/// @param gr graph
/// @param c node name
/// @return out degree

int outDegree(link *gr[n], char c)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        auto *p = gr[i];
        if (!p)
            continue;
        if (p->key != c)
            continue;

        while (p->next)
        {
            count++;
            p = p->next;
        }
        break;
    }
    return count;
}
int inDegree(link *gr[n], char c)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        auto *p = gr[i];
        if (!p)
            continue;
        while (p->next)
        {
            if (p->next->key == c)
            {
                count++;
            }

            if (!p->next)
                break;
            p = p->next;
        }
    }
    return count;
}

void deleteNodes1in1out(link *gr[n])
{
    std::vector<char> marked;
    for (int i = 0; i < n; i++)
    {
        auto *p = gr[i];
        if (!p)
            continue;
        if( outDegree(gr,p->key) == 1 &&
            inDegree(gr,p->key) == 1 )
            marked.push_back( p->key);
    }
    for( char c : marked )
    {
        del_node(gr,c);
    }
}

void test()
{
    link *graph[n];
    init(graph);

    add_node(graph, 'a');
    add_node(graph, 'b');
    add_node(graph, 'c');
    add_arc(graph, 'a', 'b');
    add_arc(graph, 'a', 'c');
    std::cout << "test ";
    visualize_graph(graph);

    std::cout << "a outDegree " << outDegree(graph,'a')
        << " inDegree " << inDegree(graph,'a')  <<"\n";
    std::cout << "b outDegree " << outDegree(graph,'b')
        << " inDegree " << inDegree(graph,'b')<<"\n";
    std::cout << "c outDegree " << outDegree(graph,'c')
        << " inDegree " << inDegree(graph,'c')<<"\n";

    del_node(graph, 'b');

    std::cout << "test delete b ";
    visualize_graph(graph);
}

int main()
{
    test();

    link *graph[n];
    init(graph);

    char option;
    char c, c1, c2;

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
