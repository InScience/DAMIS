import csv

# Classification colors: (point color, background color)
colors = [
          # ('#ff5b5b', '#ffaaaa', 'red', 'o'),
          # ('#aed9b0', '#dde4dd', 'green', 's'),
          # ('#0e0eb3', '#385fb3', 'blue', '^'), #0a0a80
          ('#880000', '#FF7777', 'red', 'o'),
          ('#006600', '#77FF77', 'green', 's'),
          ('#000099', '#77BBFF', 'blue', '^'),
          ('#FFCC00', '#FFFF66', 'yellow', 'o'),
          ('#334433', '#88aaaa', 'dark_green', 's'),
          ('#8C3629', '#BC6F64', 'dull red', '^'),
          ('#660099', '#9966FF', 'purple', 'o'),
          ('#5C5C5C', '#C2C2C2', 'gray', 's')]

def readData(inFile):
    ''' Reads data vectors with last column denoting class'''
    csvfile = open(inFile, 'rb')
    reader = csv.reader(csvfile, delimiter=',', quotechar='"')
    data = []
    for row in reader:
        v = map(float, row[:-1])
        v.append(int(row[-1]))
        data.append(v)
    return data

def writeData(data, outFile):
    csvfile = open(outFile, 'wb')
    writer = csv.writer(csvfile, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
    for row in data:
        writer.writerow(row)
    csvfile.close()

def classDistribution(data):
    '''Counts vectors in each class'''
    if type(data) == str:
        data = readData(data)
    cls_dict = dict()
    for record in data:
        cls = record[-1]
        if not cls_dict.has_key(cls):
            cls_dict[cls] = 0
        cls_dict[cls] += 1
    return cls_dict
