from random import randint
from Dir_graph import Dir_Graph
from undirected import Graph


def read_graph(file_name, graph):
    """
    This function rads the graph from a file
    :param file_name: The name of the file
    :param graph: The graph to be read
    :return:
    """
    with (open(file_name, mode='r') as file):
        nr_vertices, nr_edges = file.readline().split()
        for _ in range(int(nr_edges)):
            l = file.readline().strip().split()
            if len(l) == 1:
                if not graph.is_vertex(int(l[0])):
                    graph.add_vertex(int(l[0]))
            else:
                x, y, cost = int(l[0]), int(l[1]), int(l[2])
                if not graph.is_vertex(x):
                    graph.add_vertex(x)
                if not graph.is_vertex(y):
                    graph.add_vertex(y)
                try:
                    graph.add_edge(x, y, cost)
                except ValueError as ve:
                    pass


def read_nb(filename):
    """
    This function reads the number of vertices and edges from a file,
    so we can create the graph using those values
    :param filename: The name of the file
    :return: The nb of vertices and edges
    """
    with open(filename, "r") as f:
        for line in f:
            arg = line.split()
            return arg[0], arg[1]


def save_graph(file_name, graph):
    """
    This function saves a graph to a file
    :param file_name: The file to be saved into
    :param graph: The graph to be saved
    :return:
    """
    with open(file_name, mode='w') as file:
        for x in graph.parse_vertices():
            if len(graph.parse_nout(x)) + len(graph.parse_nin(x)) == 0:
                file.write(f"{x} \n")
            for y in graph.parse_nout(x):
                file.write(f"{x} {y} {graph.dcost[(x, y)]} \n")


def read_from_save(file_name, graph):
    """
    This function reads a graph from a saving
    :param file_name: The name of the file
    :param graph: The graph to be read
    :return:
    """
    with open(file_name, mode='r') as file:
        for line in file:
            l = line.strip().split()
            if len(l) == 1:
                if not graph.is_vertex(int(l[0])):
                    graph.add_vertex(int(l[0]))
            else:
                x, y, cost = int(l[0]), int(l[1]), int(l[2])
                if not graph.is_vertex(x):
                    graph.add_vertex(x)
                if not graph.is_vertex(y):
                    graph.add_vertex(y)
                try:
                    graph.add_edge(x, y, cost)
                except ValueError as ve:
                    print(ve)


def create_random_dir_graph(n, m):
    """
    This function creates a new random graph
    :param n: The number of vertices of the new graph
    :param m: The number of edges of the new graph
    :return:The created graph
    Preconditions: m <= n^2
    """
    if m > n*n or m < 0 or n < 0:
        raise ValueError("Invalid number of edges or vertices")

    g = Dir_Graph(n)
    while m != 0:
        a = randint(0, n - 1)
        b = randint(0, n - 1)
        cost = randint(1, 10)
        if not g.is_edge(a, b):
            g.add_edge(a, b, cost)
            m = m - 1

    return g



def print_menu_dir():
    print("1. Add a vertex")
    print("2. Remove a vertex")
    print("3. Get the number of vertices")
    print("4. Parse the vertices")
    print("5. Add an edge")
    print("6. Remove an edge")
    print("7. Modify the cost of an edge")
    print("8. Get the cost of an edge")
    print("9. Get the number of edges")
    print("10. Check if there is an edge between two vertices")
    print("11. Get the in degree and the out degree of a vertex")
    print("12. Parse the set of inbound edges of a vertex")
    print("13. Parse the set of outbound edges of a vertex")
    print("14. Print the graph")
    print("15. Read a graph from a file")
    print("16. Save to a file")
    print("17. Read from a save")
    print("18. Create a random graph")
    print("19. Print the connected components of the undirected graph")
    print("20. Display the minimum cost path between two vertices")
    print("0. Exit")


if __name__ == '__main__':
    print("1. Directed graph")
    print("2. Undirected graph")
    opt_graph = input("Your option: ").strip()
    graph = Graph(0)
    try:
        if opt_graph == "1":
            graph = Dir_Graph(0)
        elif opt_graph == "2":
            graph = Graph(0)
        else:
            print("Invalid option, creating undirected")
    except ValueError as ve:
        print(ve)

    filename1 = "d1.txt"
    n, m = read_nb(filename1)
    n = int(n)
    m = int(m)
    #graph = Dir_Graph(n)
    graph = Graph(n)
    read_graph(filename1, graph)
    while True:
        print_menu_dir()
        option = input("Your option: ").strip()
        try:
            if option == "1":
                vertex = input("Enter the vertex: ")
                graph.add_vertex(int(vertex))
            elif option == "2":
                vertex = int(input("Enter the vertex: "))
                graph.remove_vertex(vertex)
            elif option == "3":
                print(f"The number of vertices: {graph.get_nb_vertices()}")
            elif option == "4":
                graph.parse_the_vertices()
            elif option == "5":
                edge = input("Enter the edge: ").strip().split()
                graph.add_edge(int(edge[0]), int(edge[1]), int(edge[2]))
            elif option == "6":
                edge = input("Enter the edge:").strip().split()
                graph.remove_edge(edge[0], edge[1])
            elif option == "7":
                edge = input("Enter the edge and its new cost:").strip().split()
                graph.modify_cost(int(edge[0]), int(edge[1]), int(edge[2]))
            elif option == "8":
                edge = input("Enter the edge to get the price for: ").strip().split()
                print(f"For the edge:({edge[0]} {edge[1]}) the cost is:{graph.get_cost(int(edge[0]), int(edge[1]))}")
            elif option == "9":
                print(graph.get_nb_edges())
            elif option == "10":
                edge = input("Enter the edge to check: ").strip().split()
                print(f"({edge[0]} {edge[1]})", end=" ")
                print("is an edge" if graph.is_edge(int(edge[0]), int(edge[1])) == True else "is not an edge")
            elif option == "11":
                vertex = int(input("Enter the vertex: ").strip())
                print(
                    f"The in degree is: {len(graph.parse_nin(vertex))}, the out degree is: {len(graph.parse_nout(vertex))}")
            elif option == "12":
                vertex = int(input("Enter the vertex: ").strip())
                graph.parse_inbound(vertex)
            elif option == "13":
                vertex = int(input("Enter the vertex: ").strip())
                graph.parse_outbound(vertex)
            elif option == "14":
                graph.print_graph()
            elif option == "15":
                filename = input("Enter the filename: ")
                n, m = read_nb(filename)
                n = int(n)
                m = int(m)
                # if opt_graph == 1:
                #     graph = Dir_Graph(n)
                # else:
                #     graph = Graph(n)
                #graph = Dir_Graph(n)
                graph = Graph(n)
                read_graph(filename, graph)
            elif option == "16":
                filename = input("Enter the filename: ")
                save_graph(filename, graph)
            elif option == "17":
                if opt_graph == 1:
                    graph = Dir_Graph(0)
                else:
                    graph = Graph(0)
                filename = input("Enter the filename: ")
                read_from_save(filename, graph)
            elif option == "18":
                n = int(input("Enter the number of vertices: "))
                m = int(input("Enter the number of edges: "))
                graph = create_random_dir_graph(n, m)
            elif option == "19":
                # components = graph.connected_components()
                # print("Connected Components:")
                # for component in components:
                #     print("Component:")
                #     print(component)
                components = graph.connected_components_graphs()
                print("Connected Components:")
                for component in components:
                    print("Component:")
                    component.print_graph()
            elif option == "20":
                x = int(input("Enter the start vertex: "))
                y = int(input("Enter the end vertex: "))
                path, cost = graph.min_cost_path_dijkstra(x, y)
                print(path, "and the cost is: ", cost)
            elif option == "21":
                result = graph.kruskal_min_spanning_tree()
                for edge in result:
                    print(edge)
            elif option == "0":
                exit()
        except ValueError as ve:
            print(ve)
