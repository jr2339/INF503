import math
import re
from Bio import Phylo
from Bio.Phylo.TreeConstruction import DistanceCalculator, DistanceTreeConstructor
from Bio.Phylo.TreeConstruction import _DistanceMatrix as DistanceMatrix


# Copies the bottom half of a distance matrix to the top half.
def flip_matrix(matrix):
    for i in range(1, len(matrix)):
        for j in range(i):
            matrix[j][i] = matrix[i][j]


# Assumes a queue where each entry is of the format [([Strain1], 3), ([Strain2, Strain4], 4), ...]
# where each node is a tuple with a list of children and a distance value.
# This works by the first entry always being the very last operation and working in reverse.
# Initially it starts with a newick format of n children, then each subsequence gets replaced by later, more specific,
# entries.
def generate_newick(queue):
    # Generate the initial Newick tree
    newick = "("
    for node in queue[0]:
        if len(node[0]) > 1:
            newick += "({}):{}".format(','.join(node[0]), node[1])
        else:
            newick += "{}:{}".format(node[0][0], node[1])
        newick += ","
    # Exclude the last comma
    newick = newick[:-1]
    newick += ");"
    # Loop through all the queue entries starting on the second entry.
    for entry in queue[1:]:
        # Initially assume only a node list of count 1
        # The replacement string takes ever ever is matched and appends :distance to it.
        for node in entry:
            replace = r"\g<0>:" + str(node[1])
            if len(node[0]) > 1:
                # Wrap the matched string with parentheses and and append :distance
                replace = r"(\g<0>):" + str(node[1])

            # Replace a list of strains in the format: (A:3.0, B, C:2.5, D:5) where :number is optional
            # The last entry must end with a ) or , to avoid duplicate matches, such as:
            # ((Strain_1, Strain_2):5, Strain10:5); where otherwise Strain_1 would match twice,
            #newick = re.sub(r"(:\d+.?\d*)?,".join(node[0]) + r"(:\d+.?\d*)?(?=[\),])", replace, newick)

    return newick


# Takes in a distance_matrix of floats/ints and a list of strain strings.
def upgma_method(distance_matrix, strains):
    # Queue used for the Newick generation
    queue = []
    # Make a deep copy of strains as nested lists, used to keep track of combined nodes
    current_strains = [[strain] for strain in strains]
    # Make a deep copy of matrix
    current_matrix = [row[:] for row in distance_matrix]
    # Re-iterate until only two nodes are left.
    while len(current_matrix) > 2:
        # Assume a closest distance of size positive infinity.
        # closest_index is a coordinate tuple like (i, j) or (row, col)
        closest, closest_index = float('inf'), (0, 0)
        # Search through each cell checking the value beats out the past mininum.
        for i in range(1, len(current_matrix)):
            for j in range(i):
                if current_matrix[i][j] < closest:
                    closest = current_matrix[i][j]
                    closest_index = (i, j)

        # Deep copy past current matrix
        next_matrix = [row[:] for row in current_matrix]

        # Assume that the second index, which is guaranteed to be sorted less then or up to the first index, will be
        # used for the new combined node's row and column.
        # Work down the column from after the second index up to the end.
        for i in range(closest_index[1] + 1, len(next_matrix)):
            next_matrix[i][closest_index[1]] = (current_matrix[i][closest_index[1]] + current_matrix[i][closest_index[0]]) / 2
        #  Work through the row up to the second index.
        for j in range(closest_index[1]):
            next_matrix[closest_index[1]][j] = (current_matrix[closest_index[0]][j] + current_matrix[closest_index[1]][j]) / 2
        flip_matrix(next_matrix)

        # Delete the first index's row
        del next_matrix[closest_index[0]]
        # Delete the first index's column
        for row in next_matrix:
            del row[closest_index[0]]

        # print()
        # [print(line) for line in next_matrix]

        # Append new entry / operation to beginning of queue.
        queue.insert(0, [(current_strains[closest_index[1]][:], closest / 2), (current_strains[closest_index[0]][:],
                                                                              closest / 2)])
        # Combine the current list of combined nodes at first index to the end of the second combined node list.
        current_strains[closest_index[1]].extend(current_strains[closest_index[0]])
        # Delete the old first index list, keeping consistent with the dimensions of current_matrix
        del current_strains[closest_index[0]]

        current_matrix = next_matrix

    # Insert the final single cell to the beginning of the queue, accounting for all the nodes.
    queue.insert(0, [(current_strains[0][:], current_matrix[1][0] / 2), (current_strains[1][:], current_matrix[1][0] / 2)])

    return generate_newick(queue)


# Takes in a distance_matrix of floats/ints and a list of strain strings.
def neighbor_joining_method(distance_matrix, strains):
    # Queue used for the Newick generation
    queue = []
    # Make a deep copy of strains as nested lists, used to keep track of combined nodes
    current_strains = [[strain] for strain in strains]
    # Make a deep copy of matrix
    current_matrix = [row[:] for row in distance_matrix]
    # Re-iterate until only two nodes are left.
    while len(current_matrix) > 2:
        temp_matrix = [row[:] for row in current_matrix]
        for i in range(1, len(temp_matrix)):
            for j in range(i):
                temp_matrix[i][j] = ((len(current_strains) - 2) * current_matrix[i][j])\
                                    - sum(current_matrix[i]) - sum(current_matrix[j])
        flip_matrix(temp_matrix)

        # Find the minimum of temp matrix
        # Assume a closest distance of size positive infinity.
        # closest_index is a coordinate tuple like (i, j) or (row, col)
        closest, closest_index = float('inf'), (0, 0)
        # Search through each cell checking the value beats out the past mininum.
        for i in range(1, len(temp_matrix)):
            for j in range(i):
                if temp_matrix[i][j] < closest:
                    closest = temp_matrix[i][j]
                    closest_index = (i, j)
        # Reset closest to reflect the current_matrix's value
        closest = current_matrix[closest_index[0]][closest_index[1]]

        next_matrix = [row[:] for row in current_matrix]
        for z in range(len(current_strains)):
            if z != closest_index[0] and z != closest_index[1]:
                next_matrix[z][closest_index[1]] = (current_matrix[closest_index[0]][z] +
                                                    current_matrix[closest_index[1]][z] - closest) / 2
        flip_matrix(next_matrix)
        distance = (
            (closest +
             (sum(current_matrix[closest_index[0]]) - sum(current_matrix[closest_index[1]])) /
             (len(current_strains) - 2)) / 2,
            (closest -
             (sum(current_matrix[closest_index[0]]) - sum(current_matrix[closest_index[1]])) /
             (len(current_strains) - 2)) / 2
        )

        # Delete the first index's row
        del next_matrix[closest_index[0]]
        # Delete the first index's column
        for row in next_matrix:
            del row[closest_index[0]]

        # Append new entry / operation to beginning of queue.
        queue.insert(0, [(current_strains[closest_index[1]][:], distance[1]), (current_strains[closest_index[0]][:],
                                                                               distance[0])])
        # Combine the current list of combined nodes at first index to the end of the second combined node list.
        current_strains[closest_index[1]].extend(current_strains[closest_index[0]])
        # Delete the old first index list, keeping consistent with the dimensions of current_matrix
        del current_strains[closest_index[0]]

        current_matrix = next_matrix

    # Append the final single cell to the previous cluster.
    queue[0].append((current_strains[1][:], current_matrix[1][0]))

    return generate_newick(queue)


def from_csv_to_distance_matrix(path, is_full=True):
    f = open(path, 'r')
    lines = f.readlines()
    f.close()
    # Take each line and split further by ','
    parsed_lines = [line.strip().split(',') for line in lines]
    # Take the first entry of each line
    strains = [line[0] for line in parsed_lines]
    # Take all the values excluding the first of each line, and convert them each to an integer.
    matrix = []
    if is_full:
        matrix = [[float(val) if val != '' else None for val in line[1:]] + [None] for line in parsed_lines]
        for i in range(len(matrix)):
            matrix[i][i] = 0
        flip_matrix(matrix)
    else:
        for line in parsed_lines:
            row = []
            for val in line[1:]:
                if val != '':
                    row.append(float(val))
            row.append(0)
            matrix.append(row)

    return strains, matrix

if __name__ == '__main__':
    files = ['HW7_distance1.csv', 'HW7_distance2.csv']
    for p in files:
        strains, matrix = from_csv_to_distance_matrix(p)
        print(strains)
        for line in matrix:
           print(line)

           path = ""
        try:
            path = p[:p.rindex('.')]
        except ValueError:
            path = p

        newick = upgma_method(matrix, strains)
        f = open(path + '.upgma.nwk', 'w')
        f.write(newick)
        f.close()
        print(" \n")
        newick = neighbor_joining_method(matrix, strains)
        f = open(path + '.neigh.nwk', 'w')
        f.write(newick)
        f.close()

        _, dist_matrix = from_csv_to_distance_matrix(p, is_full=False)
        print(dist_matrix)
        constructor = DistanceTreeConstructor()
        tree = constructor.nj(DistanceMatrix(names=strains, matrix=dist_matrix))
        Phylo.write([tree], path + '.lib.neigh.nwk', 'newick')
