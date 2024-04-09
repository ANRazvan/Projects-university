from random import randint


class Graph:
    def __init__(self, n):
        self.n = n
        self.m = 0
        self.din = {}
        self.dout = {}
        self.dcost = {}
        self.initialise()

    def initialise(self):
        for i in range(0, self.n):
            self.din[i] = []
            self.dout[i] = []

    def is_vertex(self, x):
        """
        Checks if x is a vertex in our graph
        :param x: The vertex to be checked
        :return: True if x is a vertex, False otherwise
        """
        return x in self.din.keys()

    def is_edge(self, x, y):
        """
        Checks if there is an edge from x to y
        :param x: First vertex
        :param y: Second vertex
        :return: True or False accordingly
        """
        return x in self.din[y] and y in self.dout[x]

    def add_vertex(self, x):
        """
        Adds a vertex to the graph
        :param x: The vertex to be added
        :raises: ValueError if the vertex already exists
        Preconditions: x is an integer and doesn't already exist
        """
        if not self.is_vertex(x):
            self.din[x] = []
            self.dout[x] = []
        else:
            raise ValueError("Vertex already exists")

    def add_edge(self, x, y, cost):
        """
        Adds an edge to the graph
        :param x: First vertex
        :param y: Second vertex
        :param cost: The cost
        Preconditions: x,y are vertices and cost is an integer
        """
        if not self.is_vertex(x):
            raise ValueError(f"{x} is not a vertex")
        if not self.is_vertex(y):
            raise ValueError(f"{y} is not a vertex")

        if not self.is_edge(x, y):
            self.din[y].append(x)
            self.dout[x].append(y)
            self.dcost[(x, y)] = cost
        else:
            raise ValueError("Edge already exists")

    def remove_edge(self, x, y):
        """
        Removes an edge from the graph
        :param x: First vertex
        :param y: Second vertex
        Preconditions: The edge (x,y) must exist in the graph
        """
        if x not in self.din.keys():
            raise ValueError(f"{x} is not in the graph")
        if y not in self.din.keys():
            raise ValueError(f"{y} is not in the graph")

        self.din[x].remove(y)
        self.dout[y].remove(x)

        del self.dcost[(x, y)]

    def remove_vertex(self, x):
        """
        Removes a vertex from the graph
        :param x: The vertex to be removed
        Precondition: The vertex x must exist in the graph
        """
        if x not in self.din.keys():
            raise ValueError(f"{x} is not in the graph")

        for y in self.parse_nout(x):
            self.din[y].remove(x)
            if self.is_edge(x, y):
                del self.dcost[(x, y)]

        for y in self.parse_nin(x):
            self.dout[y].remove(x)
            if self.is_edge(x, y):
                del self.dcost[(x, y)]

        del self.din[x]
        del self.dout[x]

    def modify_cost(self, x, y, new_cost):
        """
        This function modifies the cost of an edge
        :param x: The out vertex
        :param y: The in vertex
        :param new_cost: The new cost
        Precondition: The edge must exist in the graph
        :return:
        """
        if not self.is_edge(x, y):
            raise ValueError("The edge doesnt exist")
        self.dcost[(x, y)] = new_cost

    def get_nb_vertices(self):
        """
        This function returns the number of vertices in the graph
        :return:
        """
        return len(self.din)

    def get_nb_edges(self):
        """
        This function returns the number of edges in the graph
        :return: the nb
        """
        return len(self.dcost)

    def get_cost(self, x, y):
        """
        This function returns the cost of the edge between x and y
        :param x: The first vertex
        :param y: The second vertex
        :return: the cost
        Precondition: The edge must exist in the graph
        """
        if not self.is_edge(x, y):
            raise ValueError("The edge doesnt exist")
        return self.dcost[(x, y)]

    def parse_nout(self, x):
        """
        This function returns an iterable array that contains the outbound neighbors of x
        :param x: The vertex
        :return: The list of outbound neighbors
        Precondition: x is a valid vertex of the graph.
        """
        if not self.is_vertex(x):
            raise ValueError("The vertex doesnt exist")
        return list(self.dout[x])

    def parse_nin(self, x):
        """
        This function returns an iterable array that contains the inbound neighbors of x
        :param x: The vertex
        :return: The list of inbound neighbors
        Precondition: x is a valid vertex of the graph
        """
        if not self.is_vertex(x):
            raise ValueError("The vertex doesnt exist")
        return list(self.din[x])

    def parse_vertices(self):
        """
        This function returns a list of the vertices ( in ascending order)
        :return: The list
        """
        l =  list(self.din.keys())
        l.sort()
        return l

    def parse_the_vertices(self):
        """
        This function parses/ prints the vertices on the screen
        :return:
        """
        vertices = self.parse_vertices()
        i = 0
        print("The vertices are: ")
        for vertex in vertices:
            print(vertex, end=" ")
            i = i + 1
            if i % 10 == 0:
                print("\n")
        print("\n")

    def parse_inbound(self, x):
        """
        This function parses the inbound neighbors of x and prints them on the screen
        :param x: The vertex x
        :return:
        Precondition: x is a valid vertex of the graph
        """
        if not self.is_vertex(x):
            raise ValueError("The vertex doesnt exist")
        for y in self.parse_nin(x):
            print(f"({x} {y})")

    def parse_outbound(self, x):
        """
        This function parses the outbound neighbors of x and prints them on the screen
        :param x: The vertex x
        :return:
        Precondition: x is a valid vertex of the graph
        """
        if not self.is_vertex(x):
            raise ValueError("The vertex doesnt exist")
        for y in self.parse_nout(x):
            print(f"({x} {y})")


def print_graph(graph):
    """
    This function prints the graph on the screen
    :param graph: The graph to be printed
    :return:
    """
    for x in graph.parse_vertices():
        if len(graph.parse_nout(x)) + len(graph.parse_nin(x)) == 0:
            print(x)
        for y in graph.parse_nout(x):
            print(x, y, graph.dcost[(x, y)])


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
                    print(ve)


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


def create_random_graph(n, m):
    """
    This function creates a new random graph
    :param n: The number of vertices of the new graph
    :param m: The number of edges of the new graph
    :return:The created graph
    Preconditions: m <= n^2
    """
    if m > n*n or m < 0 or n < 0:
        raise ValueError("Invalid number of edges or vertices")

    g = Graph(n)
    while m != 0:
        a = randint(0, n - 1)
        b = randint(0, n - 1)
        cost = randint(-10, 10)
        if not g.is_edge(a, b):
            g.add_edge(a, b, cost)
            m = m - 1

    return g


def print_menu():
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
    print("0. Exit")


if __name__ == '__main__':

    graph = Graph(0)
    filename1 = "graph.txt"
    n, m = read_nb(filename1)
    n = int(n)
    m = int(m)
    graph = Graph(n)
    read_graph(filename1, graph)
    while True:
        print_menu()

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
                print_graph(graph)
            elif option == "15":
                filename = input("Enter the filename: ")
                n, m = read_nb(filename)
                n = int(n)
                m = int(m)
                graph = Graph(n)
                read_graph(filename, graph)
            elif option == "16":
                filename = input("Enter the filename: ")
                save_graph(filename, graph)
            elif option == "17":
                graph = Graph(0)
                filename = input("Enter the filename: ")
                read_from_save(filename, graph)
            elif option == "18":
                n = int(input("Enter the number of vertices: "))
                m = int(input("Enter the number of edges: "))
                graph = create_random_graph(n, m)
            elif option == "0":
                exit()
        except ValueError as ve:
            print(ve)
