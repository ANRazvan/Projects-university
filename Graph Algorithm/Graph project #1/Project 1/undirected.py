from random import randint
import sys
sys.setrecursionlimit(100000)

class Graph:
    def __init__(self, n):
        self.n = n
        self.m = 0
        self.dvert = {}
        self.dcost = {}
        self.visited = [False] * n
        for i in range(self.n):
            self.dvert[i] = []

    def add_vertex(self, x):
        """
        Adds a vertex to the graph
        :param x: The vertex to be added
        :raises: ValueError is the vertex already exists
        """

        if not self.is_vertex(x):
            self.dvert[x] = []
        else:
            raise ValueError("Vertex already exists")

    def add_edge(self, x, y, cost):
        """
        Adds an edge to the graph
        :param x: The first vertex
        :param y: The second vertex
        :param cost: The cost of the edge
        :raises: ValueError if the edge already exists
        """
        # if x == y:
        #     raise ValueError("Cannot add an edge to the same vertex")

        if not self.is_vertex(x) or not self.is_vertex(y):
            raise ValueError("Vertex does not exist")

        if not self.is_edge(x, y) and x != y:
            self.dvert[y].append(x)
            self.dvert[x].append(y)
            self.dcost[(x, y)] = cost
            self.dcost[(y, x)] = cost
        else:
            raise ValueError("Edge already exists")

    def is_vertex(self, x):
        """
        Checks if a vertex exists
        :param x: The vertex
        :return: True if the vertex exists, False otherwise
        """

        return x in self.dvert.keys()

    def is_edge(self, x, y):
        """
        Checks if an edge exists
        :param x: The first vertex
        :param y: The second vertex
        :return: True if the edge exists, False otherwise
        """

        if self.is_vertex(x) and self.is_vertex(y):
            return x in self.dvert[y] and y in self.dvert[x]
        else:
            return False

    def remove_edge(self, x, y):
        """
        Deletes an edge
        :param x: The first vertex
        :param y: The second vertex
        :raises: ValueError if the edge does not exist
        """

        if not self.is_edge(x, y):
            raise ValueError("Edge does not exist")
        self.dvert[y].remove(x)
        self.dvert[x].remove(y)
        del self.dcost[(x, y)]
        del self.dcost[(y, x)]

    def remove_vertex(self, x):
        """
        Deletes a vertex
        :param x: The vertex
        :raises: ValueError if the vertex does not exist
        """

        if not self.is_vertex(x):
            raise ValueError("Vertex does not exist")

        for y in self.dvert[x]:
            if self.is_edge(y, x):
                self.dvert[y].remove(x)
                del self.dcost[(y, x)]
        del self.dvert[x]

    def parse_nout(self, x):
        """
        Returns the outbound edges of a vertex
        :param x: The vertex
        :return: A list of outbound edges
        """
        return list(self.dvert[x])

    def parse_nin(self, x):
        """
        Returns the inbound edges of a vertex
        :param x: The vertex
        :return: A list of inbound edges
        """
        return list(self.dvert[x])

    def parse_vertices(self):
        """
        Returns a list of all vertices
        :return: A list of all vertices
        """
        return list(self.dvert.keys())

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
            if y < x:
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
            if y > x:
                print(f"({x} {y})")

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
                if x < y:
                    print(x, y, self.dcost[(x, y)])

    def dfs(self, v, component):
        """
        This function is the depth-first algorithm
        It goes into depth searching for the edges connected with the current edge
        :param v: the current edge
        :param component: The list where we add the connected components
        :return: The list of all connected components
        """
        component.append(v) # we append the vertex to the component list
        self.visited[v] = True # we mark the vertex as visited
        for u in self.parse_nin(v): # we parse the inbound neighbors of the vertex
            if not self.visited[u]: # if the vertex wasn't visited, we call the dfs function recursively
                self.dfs(u, component) # we call the dfs function recursively

    def connected_components(self):
        """
        This function goes through every vertex of the graph
        if the vertex wasn't visited till that point, it creates a new component
        containing it and calls the dfs algorithm to get its connected components
        we then add the list of components to the final list
        in the end we reinitialise the visited list with false in case of another future call
        :return: a list of lists (a list containing all connected components)
        """
        components = [] # the list of all connected components
        self.visited = [False] * len(self.parse_vertices()) # we reinitialise the visited list
        for v in self.parse_vertices(): # we parse all the vertices
            if not self.visited[v]: # if the vertex wasn't visited till that point
                component = [] # we create a new component
                self.dfs(v, component) # we call the dfs algorithm
                components.append(component) # we add the component to the list of components

        return components

    def connected_components_graphs(self):
        """
        This function goes through every vertex of the graph
        if the vertex wasn't visited till that point, it creates a new component
        containing it and calls the dfs algorithm to get its connected components
        we then add the list of components to the final list
        in the end we reinitialize the visited list with false in case of another future call
        :return: a list of graphs (a graph for each connected component)
        """
        components = []  # the list of all connected components represented as graphs
        self.visited = [False] * len(self.parse_vertices())  # we reinitialize the visited list
        for v in self.parse_vertices():  # we parse all the vertices
            if not self.visited[v]:  # if the vertex wasn't visited till that point
                component = []  # we create a new component
                self.dfs(v, component)  # we call the dfs algorithm
                # Create a new graph for the current component
                subgraph = Graph(0)
                # Add vertices to the subgraph
                for vertex in component:
                    subgraph.add_vertex(vertex)
                # Add edges to the subgraph
                for vertex in component:
                    for neighbor in self.parse_nout(vertex):
                        if neighbor in component:
                            try:
                                subgraph.add_edge(vertex, neighbor, self.dcost[(vertex, neighbor)])
                            except ValueError:
                                pass
                components.append(subgraph)  # we add the graph representing the component to the list of components

        return components

    def min_cost_path_dijkstra(self, s, t):
        return 0;

    def kruskal_min_spanning_tree(self):
        # Initialize result list to store MST
        result = []

        # Initialize a list to store parent of each vertex
        parent = [i for i in range(self.n)]

        # Find the root of the set containing vertex 'i'
        def find(i):
            if parent[i] == i:
                return i
            parent[i] = find(parent[i])
            return parent[i]

        # Merge two sets containing u and v
        def union(u, v):
            root_u = find(u)
            root_v = find(v)
            parent[root_u] = root_v

        # Sort edges by weight
        edges = [(self.dcost[edge], edge[0], edge[1]) for edge in self.dcost]
        edges.sort()

        # Iterate through sorted edges and add them to MST if they don't form a cycle
        for weight, u, v in edges:
            if find(u) != find(v):
                result.append((u, v, weight))
                union(u, v)

        return result