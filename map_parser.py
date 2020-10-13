#Author: Tanner Lowthorp
import sys
from os import path

#default files
rawDataFile      = "map.osm"
nodesExtractFile = "nodes.txt"
waysExtractFile  = "ways.txt"

#Basic input validation
if len(sys.argv) == 2:
	rawDataFile = sys.argv[1]

elif len(sys.argv) == 3:
	nodesExtractFile = sys.argv[1]
	waysExtractFile  = sys.argv[2]

elif len(sys.argv) == 4:
	rawDataFile      = sys.argv[1]
	nodesExtractFile = sys.argv[1]
	waysExtractFile  = sys.argv[2]

elif len(sys.argv) > 4:
	print("Too many arguments")
	print("Uses:")
	print("map_parser.py")
	print("map_parser.py <osm file>")
	print("map_parser.py <nodes file> <ways file>")
	print("map_parser.py <osm file> <nodes file> <ways file>")
	sys.exit(0)

#open map data file
file = None
if path.exists(rawDataFile):
	file = open(rawDataFile, 'r', encoding="utf8")
else:
	print("File", rawDataFile, "not found")
	sys.exit(0)

#Begin parsing map data
tokens = file.read().split("<node ")
file.close()

nodes = []
ways  = []

#populate nodes list
for token in tokens:
	#print(token)
	#print('\n\n')
	#parse id, latitude, and longitude for each node
	if token[:2] == "id":
		nodeInfo = []
		splitToken = token.split("id=\"")
		nodeInfo.append(splitToken[1].split('\"')[0])
		splitToken = token.split("lat=\"")
		nodeInfo.append(splitToken[1].split('\"')[0])
		splitToken = token.split("lon=\"")
		nodeInfo.append(splitToken[1].split('\"')[0])
		nodes.append(nodeInfo)



#populate ways list
waysTokens = tokens[len(tokens)-1].split("<way ")
waysTokens.pop(0) #discard all data prior to the first way

for way in waysTokens:
	#parse all node id's that belong to a way
	ndTokens = way.split("<nd ")[1:]

	temp = []
	for nd in ndTokens:
		temp.append(nd.split('\"')[1])
	ways.append(temp)


#helper function for writing data to files
def writeToFile(file, list):
	for each in list:
		for data in each:
			file.write(data + ' ')

		file.write('\n')

	file.close()

#write nodes info file
file = open(nodesExtractFile, 'w')
writeToFile(file, nodes)

#write ways info file
file = open(waysExtractFile, 'w')
writeToFile(file, ways)