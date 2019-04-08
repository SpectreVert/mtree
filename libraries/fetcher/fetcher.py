import bs4 as bs
import argparse
import os
from urllib.request import urlopen, Request

#default_profile = "1231954082"

class Album(object):
    def __init__(self, album_link, album_title, artist_link, artist_name):
        self.album_link = album_link
        self.album = album_title
        self.artist_link = artist_link
        self.artist = artist_name

    def __str__(self):
        return self.artist + '/' + self.album + '/' + self.album_link.replace('/album/', 'd')

    def __repr__(self):
        return "<Album: " + self.album + ' - ' + self.artist + ">"

def generateFoldersFiles(new, path):
    if not os.path.exists(path):
        print ('error: provided path \'' + path + '\' not accessible')
        exit(3)

    folders = new.split('/')
    
    if os.path.exists(os.path.join(path, folders[0], folders[1])):
        print ('warning; album already exported: \'' + folders[1] + '\'')

    print (folders)

def shootUnwantedChars(string, path):
    string = string.replace(' ', '_').replace('\'', '')

    if path is not None:
        generateFoldersFiles(string, path)

    return string + '\n'

def main():
    parser = argparse.ArgumentParser(description='Fetch some information from deezer profile.')
    parser.add_argument('-p', metavar='<profile>', type=str, nargs=1,
                        help='provide a specific profile to load from.')
    parser.add_argument('-f', metavar='<file>', type=str, nargs=1,
                        help='provide a specific file to output to.')
    parser.add_argument('-g', metavar='<path>', type=str, nargs=1,
                        help='provide a location to build the profile\'s album hierarchy to.')
    args = parser.parse_args()

    if vars(args)['p'] is not None:
        profile = vars(args)['p'][0]
    else:
        profile = '1234567'

    if vars(args)['f'] is not None:
        outputFile = vars(args)['f'][0] + '.dzer'
    else:
        outputFile = 'default.dzer'

    if vars(args)['g'] is not None:
        generatePath = vars(args)['g'][0]
    else:
        generatePath = None

    url_get = urlopen(
            Request(
                'https://www.deezer.com/us/profile/' + profile + '/albums',
                headers={'User-Agent': 'Mozilla/5.0'})
            )
    soup = bs.BeautifulSoup(url_get, features='html.parser')

    albums = list()
    data = list(soup.find_all('a'))[9:]
    for i in range(len(data)):
        if i % 2 == 0:
            albums.append(
                Album(
                    data[i].get('href'),
                    data[i].text,
                    data[i+1].get('href'),
                    data[i+1].text
                )
            )

    with open(outputFile, 'w') as favs:
        for album in albums:
            favs.write(shootUnwantedChars(str(album), generatePath))


if __name__ == '__main__':
    main()
