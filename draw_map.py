import pandas as pd
import numpy as np
import networkx as nx
import matplotlib.pyplot as plt
from collections import Counter

def draw_map(file,path):
    # define the size of the picture
    plt.figure(figsize=(15, 9))

    # read the path
    list_all_path = path.split(" -> ")
    list_step = []
    for i in range(len(list_all_path) - 1):
        tmp_list = [list_all_path[i], list_all_path[i + 1]]
        list_step.append(tmp_list)

    # read the file
    f = open(file, "r")
    data = pd.read_csv(f, delimiter=" ")

    # 1 and 2 column data (protein)
    csv_protein1 = data.iloc[:, 0]
    list_protein1 = list(np.array(csv_protein1))
    list_protein = list(np.array(csv_protein1))
    csv_protein2 = data.iloc[:, 1]
    list_protein2 = list(np.array(csv_protein2))
    csv_score = data.iloc[:, 2]
    list_score = list(np.array(csv_score))
    j = 0
    for i in list_score:
        list_score[j] = 1200 - list_score[j]
        j += 1
    list_protein.extend(list_protein2)

    # delete the repeated protein
    tmp1 = list(set(list_protein1))
    tmp2 = list(set(list_protein2))
    list_only_protein = tmp1 + tmp2
    list_only_protein.sort()

    # select main data
    counter = Counter(list_protein)
    counter.most_common()
    Pre_main_protein = sorted(counter.items(), key=lambda x: x[1], reverse=True)
    Pre_list_main_protein = Pre_main_protein[:30]
    list_main_protein = []
    for i in Pre_list_main_protein:
        list_main_protein.append(i[0])

    # append the path
    list_onpath_protein = []
    list_path = list_all_path
    for i in data.index:
        if (list_protein1[i] in list_path):
            list_onpath_protein.append(list_protein2[i])
        if (list_protein2[i] in list_path):
            list_onpath_protein.append(list_protein1[i])
    counter1 = Counter(list_onpath_protein)
    counter1.most_common()
    Pre_onpath_protein = sorted(counter1.items(), key=lambda x: x[1], reverse=True)
    Pre_main_onpath_protein = Pre_onpath_protein[:20]
    list_main_onpath_protein = []
    for i in Pre_main_onpath_protein:
        list_main_onpath_protein.append(i[0])
    list_main_protein.extend(list_main_onpath_protein)
    list_main_protein.extend(list_all_path)
    list_main_protein.sort()
    del_lst = []
    for i in range(len(list_main_protein) - 1):
        if list_main_protein[i] == list_main_protein[i + 1]:
            del_lst.append(list_main_protein[i + 1])
    for j in del_lst:
        list_main_protein.remove(j)

    # get the map's data
    map_data = []
    list_edge_colors = []
    flag_path = 0
    for i in data.index:
        tmp_list1 = [list_protein1[i], list_protein2[i]]
        tmp_list2 = [list_protein2[i], list_protein1[i]]
        if (tmp_list1 in list_step) or (tmp_list2 in list_step):
            if (list_protein2[i] in list_all_path) and (list_protein1[i] in list_all_path) and flag_path <= len(
                    list_step) - 1:
                flag_path += 1
                list_edge_colors.append('red')
                tmp_tuple = (list_protein1[i], list_protein2[i], list_score[i])
                map_data.append(tmp_tuple)
        elif (list_protein1[i] in list_main_protein) and (list_protein2[i] in list_main_protein):
            list_edge_colors.append('blue')
            tmp_tuple = (list_protein1[i], list_protein2[i], list_score[i])
            map_data.append(tmp_tuple)

    # draw the map
    G = nx.Graph()
    list_colors = []
    for i in range(len(list_main_protein)):
        list_colors.append(0)
    for i in range(len(list_main_protein)):
        if list_main_protein[i] in list_all_path:
            list_colors[i] = -0.7
        else:
            list_colors[i] = i / len(list_main_protein) * 1

    colors = tuple(list_colors)
    G.add_nodes_from(list_main_protein)
    G.add_weighted_edges_from(map_data)

    pos = nx.spring_layout(G)
    nx.draw(G, font_size=5, with_labels=True, node_size=150, node_color=colors, edge_color=list_edge_colors)
    plt.show()


if __name__ == "__main__":
    draw_map("D:/test/4932.protein.links.v11.0.txt","4932.Q0182 -> 4932.Q0010 -> 4932.Q0017 -> 4932.Q0142")




