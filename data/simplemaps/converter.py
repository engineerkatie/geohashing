#!/usr/bin/env python3

import sys
import csv
import math
import json

def main():
    data = sys.stdin.readlines()[:]

    reader = csv.DictReader(data)

    renames = {
        'city_ascii': "name",
        'lat': "lat",
        'lng': "long",
    }
    cities = [
        {
            renames.get(k, None): v
            for k,v
            in x.items()
            if renames.get(k, None)
        }
        for x
        in reader
    ]

    radians_cities = [
        {
            'name': x['name'],
            'lat': math.radians(float(x['lat'])),
            'long': math.radians(float(x['long'])),
        }
        for x
        in cities
    ]

    CONVERTER = 256 / (2 * math.pi)

    web_mercator_cities = [
        {
            'name': x['name'],
           'long': CONVERTER * (x['long'] + math.pi),
           'lat':  CONVERTER * (math.pi - math.log(math.tan((math.pi/4) + (x['lat']/2)))),
        }
        for x
        in radians_cities
    ]


    print(json.dumps(web_mercator_cities, indent=2))

if __name__ =="__main__":
    main()
