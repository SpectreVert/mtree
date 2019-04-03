import bs4 as bs
from urllib.request import urlopen, Request


default_profile = "1231954082"

class Album(object):
    def __init__(self, album_link, album_title, artist_link, artist_name):
        self.album_link = album_link
        self.album = album_title
        self.artist_link = artist_link
        self.artist = artist_name

    def __str__(self):
        return self.album + ' - ' + self.artist

    def __repr__(self):
        return "<Album: " + self.album + ' - ' + self.artist + ">"


def main():
    url_get = urlopen(
            Request(
                'https://www.deezer.com/us/profile/' + default_profile + '/albums',
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

    with open('favs.txt', 'w') as favs:
        for album in albums:
            favs.write(str(album) + '\n')


if __name__ == '__main__':
    main()
