from sys import argv
import re

great_node = -1
graph = []
file = open(argv[1], "r")

for line in file:
    if not re.match("//", line):
        info = line.split(" ")
        arrest = {info[0] + "&" + info[1]: info[2].replace('\n', '')}
        if int(info[0]) > great_node:
            great_node = int(info[0])
        if int(info[1]) > great_node:
            great_node = int(info[1])
        graph.append(arrest)

nodes = great_node + 1
prim = []
min_dist = {}
added = []
added.append(int(list(graph[0].keys())[0].split("&")[0]))

i = 0
while i < nodes:
    for node in range(len(graph)):
        n = list(graph[node].keys())[0].split("&")
        if (int(n[0]) in added or int(n[1]) in added) and (int(
                n[0]) not in added or int(n[1]) not in added):
            if len(min_dist) == 0:
                min_dist = graph[node]
            elif int(list(graph[node].values())[0]) < int(
                    list(min_dist.values())[0]):
                min_dist = graph[node]
    if min_dist:
        prim.append(min_dist)
        if int(list(min_dist.keys())[0].split("&")[0]) not in added:
            added.append(int(list(min_dist.keys())[0].split("&")[0]))

        if int(list(min_dist.keys())[0].split("&")[1]) not in added:
            added.append(int(list(min_dist.keys())[0].split("&")[1]))
    min_dist = {}
    i += 1


print("======MST Nodes=====")
print(prim)
print("======Final Cost=====")
cost = 0
for i in prim:
    if i:
        cost += int(list(i.values())[0])
print(cost)