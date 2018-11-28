"""
example:

A = Node(STOPLINE);
B = Node(STOPLINE);
R = Node(ROUNDABOUT);

course = [A, B, R]

A.addExit(R, 5)
R.addExit(A, 5)
B.addExit(R, 10)
R.addExit(B, 10)
"""
import heapq

class NodeType:
    STOPLINE = 1
    PARKING = 2
    ROUNDABOUT = 3

class Command:
    IGNORE = 'ignr'
    STOP = 'stop'
    PARK = 'park'
    UN_PARK = 'un_park'
    ENTER = 'entr'
    EXIT = 'exit'

class Node:
    def __init__(self, node_type=NodeType.STOPLINE):
        self.type = node_type
        self.outgoing = []

    def addEdge(self, end, cost):
        self.outgoing.append(Edge(self, end, cost))


class Edge:
    def __init__(self, start, end, cost=0):
        self.start = start
        self.end = end
        self.cost = cost

    def __lt__(self, other):
        return self.cost < other.cost

class WeightedNode:
    def __init__(self, node, path=[], weight=float('inf')):
        self.node = node
        self.path = path
        self.weight = weight
    
    def __lt__(self, other):
        return self.weight < other.weight

def closest_path(course, src, dst):
    path = [src]
    unvisited = []

    for node in course:
        if node == src:
            unvisited.append(WeightedNode(src, path, 0))
        else:
            unvisited.append(WeightedNode(node, path))

    while(unvisited):
        cur = min(unvisited)
        if cur.node == dst:
            path = cur.path
            break

        for edge in cur.node.outgoing:
            for node in unvisited:
                if edge.end == node.node:
                    if cur.weight + edge.cost < node.weight:
                        node.path = cur.path + [node.node]
                        node.weight = cur.weight + edge.cost
        
        unvisited.remove(cur)

    return path

def create_mission(path):
    node, rest = path[0], path[1:]
    if node.type is NodeType.STOPLINE:
        return ([Command.IGNORE] if rest else [Command.STOP]) + create_mission(rest)
    elif node.type is NodeType.PARKING:
        return ([Command.IGNORE] if rest else [Command.PARK]) + [Command.UN_PARK] + create_mission(rest)
    else: # ROUNDABOUT
        src, dst = 0, 0
        exit_count = len(node.exits)
        for i in range(exit_count):
            if node.exits[i][0] == src: src = i
            elif node.exits[i][0] == dst: dst = i
        ignore_count = (dst-src) % exit_count - 1
        return [Command.ENTER] + ignore_count*[Command.IGNORE] + [Command.EXIT] + create_mission(rest)
