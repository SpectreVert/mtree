import bs4 as bs
import argparse
from urllib.request import urlopen, Request

#default_profile = "1231954082"

class Album(object):
    def __init__(self, album_link, album_title, artist_link, artist_name):
        self.album_link = album_link
        self.album = album_title
        self.artist_link = artist_link
        self.artist = artist_name

    def __str__(self):
        return self.artist + '/' + self.album + '/'

    def __repr__(self):
        return "<Album: " + self.album + ' - ' + self.artist + ">"

def shootUnwantedChars(string):
    string = string.replace(' ', '_')
    string = string.replace('\'', '')

    return string

def main():
    parser = argparse.ArgumentParser(description='Fetch some information from deezer profile.')
    parser.add_argument('-p', metavar='<profile>', type=str, nargs=1,
                        help='provide a specific profile to load from.')
    parser.add_argument('-f', metavar='<file>', type=str, nargs=1,
                        help='provide a specific file to output to.')
    args = parser.parse_args()

    if vars(args)['p'] is not None:
        profile = vars(args)['p'][0]
    else:
        profile = '1234567'

    if vars(args)['f'] is not None:
        outputFile = vars(args)['f'][0] + '.dzer'
    else:
        outputFile = 'default.dzer'

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
            favs.write(shootUnwantedChars(str(album) + '\n'))


if __name__ == '__main__':
    main()
