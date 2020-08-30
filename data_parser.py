def removeLeadingSpaces(file):
	while file.read(1).decode() == ' ':
		pass


with open("D:/Map Data/us-west-latest.osm", 'rb') as file:
	count = 0
	for _ in range(1000):
		removeLeadingSpaces(file)
		line = file.read(4).decode("utf8")
		#file.readline()
		full = file.readline().decode("utf8")
		if not line:
			break	
		# if line[:4] == "<way":
		# 	print(count)
		# 	break
		#print(line)
		if line == "way ":
			break
		elif line == "node":
			print(full)
			print("lat", full.split("\"")[7], end=' ')
			print("lon", full.split("\"")[9])
			#print(full.split("\""))
			count += 1
	print(count)