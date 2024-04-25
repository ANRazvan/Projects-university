from random import randint
import heapq
class Dir_Graph:
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
        return x in self.parse_vertices()

    def is_edge(self, x, y):
        """
        Checks if there is an edge from x to y
        :param x: First vertex
        :param y: Second vertex
        :return: True or False accordingly
        """
        if not self.is_vertex(x):
            raise ValueError(f"{x} is not a vertex")
        if not self.is_vertex(y):
            raise ValueError(f"{y} is not a vertex")
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

    def create_random_graph(self, n, m):
        """
        This function creates a new random graph
        :param n: The number of vertices of the new graph
        :param m: The number of edges of the new graph
        :return:The created graph
        Preconditions: m <= n
        """
        if m > n or m < 0 or n < 0:
            raise ValueError("Invalid number of edges or vertices")
        self.n = n
        self.initialise()
        while m != 0:
            a = randint(0, n - 1)
            b = randint(0, n - 1)
            cost = randint(-10, 10)
            if not self.is_edge(a, b):
                self.add_edge(a, b, cost)
                m = m - 1

    def print_graph(self):
        """
        This function prints the graph on the screen
        :param graph: The graph to be printed
        :return:
        """
        for x in self.parse_vertices():
            if len(self.parse_nout(x)) + len(self.parse_nin(x)) == 0:
                print(x)
            for y in self.parse_nout(x):
                print(x, y, self.dcost[(x, y)])

    def dijkstra(self, s):
        '''Returns a tuple of two dictionaries: prev and dist, each having as keys all
        the accessible vertices from s and the values are: the parent (None for the root) and the distance
        from s
        '''
        queue = [(0, s)]
        prev = {s: None}
        dist = {s: 0}
        while len(queue) > 0:
            dx, x = heapq.heappop(queue)
            nout = self.parse_nout(x)
            for y in nout:
                if y not in prev.keys() or dist[x] + self.dcost[(x, y)] < dist[y]:
                    prev[y] = x;
                    dist[y] = dist[x] + self.dcost[(x, y)]
                    heapq.heappush(queue, (dist[y], y))

        return prev, dist

    def min_cost_path_dijkstra(self, s, t):
        if not self.is_vertex(s) or not self.is_vertex(t):
            raise ValueError("Invalid vertices")
        prev, dist = self.dijkstra(s)
        print(f"prev={prev}")
        print(f"dist={dist}")
        if t not in prev:
            raise ValueError("No path")
        v = t
        result = []
        cost = 0
        while (v != s):
            cost += self.dcost[(prev[v], v)]
            result.append(v)
            v = prev[v]
        result.append(s)
        result.reverse()
        return result,cost

