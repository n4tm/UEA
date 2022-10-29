class Vertex:
  def __init__(self, key: str):
    self.key = key
    self.visited = False
    self.adjacent = []
    self.parent = None

  def reset_adjacent(self):
    self.adjacent = []

class Edge:
  def __init__(self, vertex1: Vertex, vertex2: Vertex, weight: int):
    self.vertex1 = vertex1
    self.vertex2 = vertex2
    self.weight = weight

  def process_adjacent(self) -> None:
    self.vertex1.adjacent.append(self.vertex2)
    self.vertex2.adjacent.append(self.vertex1)

  def could_cause_cycle(self) -> bool:
    self.vertex1.visited = True
    visited = [self.vertex1]
    
    def dfs_transversal(vertex, parent) -> bool:
      vertex.visited = True
      visited.append(vertex)
      for adj in vertex.adjacent:
        if not adj.visited:
          if dfs_transversal(adj, vertex):
            return True
        elif parent is not None and adj.key != parent.key:
          return True
      return False

    result = dfs_transversal(self.vertex2, None)

    for v in visited:
      v.visited = False

    return result

class Graph:
  def __init__(self):
    self.edges = {}
    self.vertices = {}

  def add_edge(self, v1_key: str, v2_key: str, weight: int) -> None:
    if not v1_key in self.vertices:
      self.vertices[v1_key] = Vertex(v1_key)
    if not v2_key in self.vertices:
      self.vertices[v2_key] = Vertex(v2_key)
    v1 = self.vertices[v1_key]
    v2 = self.vertices[v2_key]
    edge = Edge(v1, v2, weight)
    self.edges[v1_key, v2_key] = edge

  def is_connected(self) -> bool:
    for edge in self.edges.values():
      edge.process_adjacent()

    visited = []
    start_vertex = self.vertices[next(iter(self.vertices))]
    def DFS(vertex):
      visited.append(vertex)
      vertex.visited = True

      for adj in vertex.adjacent:
        if not adj.visited: DFS(adj)
    
    DFS(start_vertex)
    result = len(visited) == len(self.vertices)
    for v in visited:
      v.visited = False
    for v in self.vertices.values():
      v.reset_adjacent()
    return result

  # Kruskal's Algorithm
  def get_minimal_spanning_tree(self) -> set:
    min_spanning_tree = []
    sorted_edges = {k: v for k, v in sorted(self.edges.items(), key=lambda x: x[1].weight)}
    n = len(self.vertices)
    for edge in sorted_edges.values():
      if edge.could_cause_cycle():
        continue
      
      min_spanning_tree.append(edge)
      edge.process_adjacent()
      if len(min_spanning_tree) == n-1:
        break
    
    return min_spanning_tree

if __name__ == '__main__':
  graph = Graph()

  n = int(input())

  for _ in range(n):
    v1_key, v2_key, edge_weight = input().split()
    edge_weight = int(edge_weight)
    graph.add_edge(v1_key, v2_key, edge_weight)

  if not graph.is_connected():
    print(-1)
  else:
    min_spanning_tree = graph.get_minimal_spanning_tree()
    left_overs = filter(lambda x : x not in min_spanning_tree, graph.edges.values())
    left_overs_weights = map(lambda x : x.weight, left_overs)
    print(sum(left_overs_weights))
