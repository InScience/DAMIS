# coding: utf-8
from matplotlib import pyplot as plt
from pickle import dump, load
from numpy import arange
import sys
from tools import readData, classDistribution, colors

##########   Medžių priemonės   ##########
def loadTree(filename):
    '''Reads tree, saved in file.'''
    return load(open(filename))

def saveTree(filename, tree):
    '''Saves tree in human unreadable format.'''
    dump(tree, open(filename, 'w'))

def classDistStr(classDist, precision=None):
    res = None
    if classDist is not None:
        res = '{'
        entries = []
        for k in classDist:
            count = None
            if precision is not None:
                count = '%.'+str(precision)+'f'
            else:
                count = '%f'
            entries.append(str(k) + ": " + (count % classDist[k]))
        res += ', '.join(entries)
        res += '}'
    return res

def printTree(tree, indent='', indentStep='', childLink = ''):
    if tree.nodeType == 'internal':
        sys.stdout.write(indent+childLink)
        sys.stdout.write('%d <= %.3f' % (tree.test.testedAtt, tree.test.cut))
        if tree.branches[0].nodeType == 'leaf':
            leaf = tree.branches[0]
            sys.stdout.write(': %d\t' % (leaf.leaf))
            if leaf.error is not None:
                print '(%s/%.3f), %s' % (leaf.N, leaf.error, classDistStr(leaf.classDist, 3))
            else:
                print '(%s/%s), %s' % (leaf.N, leaf.error, classDistStr(leaf.classDist, 3))
        else:
            print
            printTree(tree.branches[0], indent + indentStep, ':   ', ':...')
        sys.stdout.write(indent + indentStep)
        sys.stdout.write('%d > %.3f' % (tree.test.testedAtt, tree.test.cut))
        if tree.branches[1].nodeType == 'leaf':
            leaf = tree.branches[1]
            sys.stdout.write(': %d\t' % (leaf.leaf))
            if leaf.error is not None:
                print '(%s/%.3f), %s' % (leaf.N, leaf.error, classDistStr(leaf.classDist, 3))
            else:
                print '(%s/%s), %s' % (leaf.N, leaf.error, classDistStr(leaf.classDist, 3))
        else:
            print
            printTree(tree.branches[1], indent + indentStep, '    ', ':...')
    elif childLink == '':
        sys.stdout.write(': %d\t' % (tree.leaf))
        print '(%s / %s), %s' % (tree.N, tree.error, tree.classDist)


def drawTree(dataFile, treeFile, colors=colors, save_to=''):
    '''Draws 2D plot and displays in it:
         ``data``: (att1, ..., attN, class)
         ``tree`` - displays as colored background
    '''
    if type(dataFile) == str:
        data = readData(dataFile)
    else:
        data = dataFile
    if type(treeFile) == str:
        tree = loadTree(treeFile)
    else:
        tree = treeFile

    attribute_count = len(data[0]) -1
    if attribute_count != 2:
        print "Too many attributes (%d), could draw only 2D plots..." % attribute_count
        return 1

    # Divide data vectors by their class, x, y; find min, max values.
    point_dict = dict()
    min_x, max_x, min_y, max_y = None, None, None, None
    for record in data:
        vector, cls = record[:-1], record[-1]
        if not point_dict.has_key(cls):
            point_dict[cls] = [[],[]]
        x = vector[0]
        y = vector[1]
        point_dict[cls][0].append(x)
        point_dict[cls][1].append(y)
        if not min_x or x < min_x:
            min_x = x
        if not max_x or x > max_x:
            max_x = x
        if not min_y or y < min_y:
            min_y = y
        if not max_y or y > max_y:
            max_y = y

    # Draw tree:
    point_cons = 400
    min_x -= 2 * (min_x + max_x) / point_cons
    max_x += 2 * (min_x + max_x) / point_cons
    min_y -= 2 * (min_y + max_y) / point_cons
    max_y += 2 * (min_y + max_y) / point_cons

    ## Draw tree:
    tree_dict = dict()
    for x in arange(min_x, max_x, (max_x - min_x) / point_cons):
        for y in arange(min_y, max_y, (max_y - min_y) / point_cons):
            point_cls = tree.getClass([x, y])
            if not tree_dict.has_key(point_cls):
                tree_dict[point_cls] = [[],[]]
            tree_dict[point_cls][0].append(x)
            tree_dict[point_cls][1].append(y)

    for cls in tree_dict:
        plt.scatter(tree_dict[cls][0], tree_dict[cls][1], 2,
                                c=colors[int(cls)][1], marker='s', linewidth=0)

    # Draw data points:
    for cls in point_dict:
        plt.scatter(point_dict[cls][0], point_dict[cls][1], 33,
                                c=colors[int(cls)][0], marker='o')
    plt.axis([min_x, max_x, min_y, max_y])
    plt.title(', '.join([colors[cls][2] + ': ' + str(count) for (cls, count) in
                                                classDistribution(data).items()]))
    if save_to:
        plt.savefig(save_to)
        plt.cla()
    else:
        plt.show()
