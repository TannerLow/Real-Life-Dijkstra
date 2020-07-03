file   = open("map (2).osm", 'r')
tokens = file.read().split("<node ")
file.close()

nodes = []
ways  = []

#populate nodes list
for token in tokens:
	#print(token)
	#print('\n\n')

	if token[:2] == "id":
		splitToken = token.split()
		nodes.append([splitToken[0].split('\"')[1],
					  splitToken[7].split('\"')[1], 
					  splitToken[8].split('\"')[1]])


	#print('=' * 100)

#populate ways list
waysTokens = tokens[len(tokens)-1].split("<way ")
waysTokens.pop(0)
#print(len(waysTokens), '<-------')
for way in waysTokens:
	#print(way)
	ndTokens = way.split("<nd ")[1:]
	#print('\n\n')

	temp = []
	for nd in ndTokens:
		temp.append(nd.split('\"')[1])
	ways.append(temp)

	#print('=' * 100)

#write nodes info file
file = open("./extract/nodes.txt", 'w')

for each in nodes:
	print(each)
	for data in each:
		file.write(data + ' ')

	file.write('\n')

file.close()

#write ways info file
file = open("./extract/ways.txt", 'w')

for each in ways:
	print(each)
	for data in each:
		file.write(data + ' ')

	file.write('\n')

file.close()