import requests

left   = input("left  : ")
bottom = input("bottom: ")
right  = input("right : ")
top    = input("top   : ")

#left, bottom, right, top = '-118.02154', '33.81460', '-118.01741', '33.81807'

baseUrl = 'https://api.openstreetmap.org/api/0.6/map?bbox='
url     =  baseUrl + left + ',' + bottom + ',' + right + ',' + top
r = requests.get(url, allow_redirects=True)

open('map_data.osm', 'wb').write(r.content)
