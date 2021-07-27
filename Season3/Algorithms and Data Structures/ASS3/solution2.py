from pygraph.classes.digraph import digraph
from math import sqrt

class HITSIterator:
    __doc__ = "calculate the Hup and Authority value of a graph"

    def __init__(self, bg):
        self.max_iterations = 100  
        self.min_delta = 0.0001  
        self.graph = bg

        self.hub = {}
        self.authority = {}
        for node in self.graph.nodes():
            self.hub[node] = 1
            self.authority[node] = 1

    def hits(self):
        if not self.graph:
            return

        flag = False
        for i in range(self.max_iterations):
            change = 0.0 
            norm = 0  
            tmp = {}
            tmp = self.authority.copy()
            for node in self.graph.nodes():
                self.authority[node] = 0
                for incident_page in self.graph.incidents(node):  
                    self.authority[node] += self.hub[incident_page]
                norm += pow(self.authority[node], 2)
            norm = sqrt(norm)
            for node in self.graph.nodes():
                self.authority[node] /= norm
                change += abs(tmp[node] - self.authority[node])

            # calculate the hup value of each page
            norm = 0
            tmp = self.hub.copy()
            for node in self.graph.nodes():
                self.hub[node] = 0
                for neighbor_page in self.graph.neighbors(node):  
                    self.hub[node] += self.authority[neighbor_page]
                norm += pow(self.hub[node], 2)
            # normalization 
            norm = sqrt(norm)
            for node in self.graph.nodes():
                self.hub[node] /= norm
                change += abs(tmp[node] - self.hub[node])

            print("====This is NO.%s iteration===" % (i + 1))
            print("@authority", self.authority)
            print("@hub", self.hub)

            if change < self.min_delta:
                flag = True
                break
        if flag:
            print("***finished in %s iterations!***" % (i + 1))
        else:
            print("***finished out of 100 iterations!***")

        print("The best authority page: ", max(self.authority.items(), key=lambda x: x[1]))
        print("The best hub page: ", max(self.hub.items(), key=lambda x: x[1]))


if __name__ == '__main__':
    bg = digraph()

    bg.add_nodes(["A", "B", "C", "D", "E"])

    bg.add_edge(("A", "C"))
    bg.add_edge(("A", "D"))
    bg.add_edge(("B", "D"))
    bg.add_edge(("C", "E"))
    bg.add_edge(("D", "E"))
    bg.add_edge(("B", "E"))
    bg.add_edge(("E", "A"))

    hits = HITSIterator(bg)
    hits.hits()