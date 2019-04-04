# mtree

mtree is a custom recursive directory listing program very similar to the 'tree' command from and for *nix systems.

The twist here is that mtree is made for using directory and file hierarchy as a way to **classify music**.

## Usage

If you've never used mtree, I suggest you read the [Abstract](https://github.com/SpectreVert/mtree/tree/master#abstract)
section to understand how to prepare your folders and files.

```
Usage: mtree <file> [filter] [options]

Options:
   -p               Print only audio items, with their absolute path, and with no line-feed between items.

Filters:
   -a <artist>      filter albums and songs from artist.
   -g <genre>       filter subgenres, albums and songs from genre.
   -m <album>	    filter albums containing string (non case-sensitive)
   -s <string>      filter songs containing string (non case-sensitive)
```

Examples:

```
$ mtree music/ -s scenery
02.Scenery.flac by Ryo_Fukui [1994-My_Favorite_Tune]
06.Scenery.flac by Ryo_Fukui [1976-Scenery]

songs: 2
```

```
$ vlc $(mtree music/ -aHoly_Oysters -p)
```

## Abstract

I've thought of a simple and explicit file naming system to provide informations about a song without tampering
with audio (or any type, really) files. mtree understands easily how all the metadata is linked and can do
its job by displaying, filtering or listing these informations. 

And using it keeps your local collection neat and tidy :)

### Naming Convention

mtree naming system recognizes 4 types of items:
  - genre
  - artist
  - album
  - songs -- or more accurately "audio item"

Genre, artist and album items are represented by a folder. Audio items are any file.

Folder naming follows simple rules that allow to differenciate them. They can be represented by a regex string:

  - genre folders match: `^[a-z]+[a-zA-Z0-9_-]*$`
  - artist folders match: `^[A-Z]+[a-zA-Z0-9_-]*$`
  - album folders match: `^[0-9]+[a-zA-Z0-9_-]*$`
    
Genre, artist and album folders respectively need to start with a **lower case**, **capital case** and **digit**.
Characters after the first one can be alphanumerical or a dash or hyphen.

Audio items can be named using any character that wouldn't need to be escaped by bash. Spaces, exclamation
maks and colons, for instance, should be avoided. Best practice would recommend to stick to **alphanumerical characters** with the addition of **dash**, **hypens** and **dots**.

### Example hierarchy

Here is the output of a music directory using the 'tree' command compared to the mtree command:

```
$ tree                                                  $ mtree
.                                                       music/
├── jazz                                                `--- jazz/
│   └── fusion                                               `--- fusion/
│       └── Masaki_Matsubara                                      `--- Masaki_Matsubara/
│           ├── 1983-Sniper                                            `--- 1983-Sniper
│           │   ├── Busted.flac                                             `--- Someday.flac
|           |   |   [6 lines removed]                                       `    [6 lines removed]
│           │   └── You_Know_What_I_Like.flac                               `--- Give_Our_Love.flac
│           └── 1984-Been                                              `--- 1984-Been/
│               ├── 01.Been.flac                                            `--- 01.Been.flac
|               |   [6 lines removed]                                       `    [6 lines removed]
│               └── 08.Da-ba-da.flac                                        `--- 07.Stand.flac
└── pop                                                 `--- pop
    └── synth-pop                                            `--- synth-pop
        └── Holy_Oysters                                          `--- Holy_Oysters
            └── 2017-Egonomy                                           `--- 2017-Egonomy
                ├── 0-Egonomy.mp3                                           `--- 0-Egonomy.mp3
                |   [7 lines removed]                                       `
                └── 8-Drifts.mp3                                            `--- 8-Drifts.mp3

9 directories, 25 files                                 songs: 25       artists: 2
                                                        albums: 3       genres: 5
```
_Nope, mtree doesn't classify names in alphabetical order._

Here we have **four** genres: *jazz*, *fusion*, *pop* and *synth-pop*. Two of them are **subgenres** (can you guess which?)

We also have **two** artists: *Masaki_Matsubara* and *Holy_Oysters*.

**Three** is the number of albums: *1983-Sniper*, *1984-Been* and *2017-Egonomy*.

And finally, the grand total of songs is **25** (I won't list them for obvious reasons). 

**Notes:**

The same artist can be present in different genre directories.

Audio items don't need to belong to a genre, album or artist.

**Actually**, directories and files can be placed anywhere and mtree will never complain; but keep in mind that you 
might get strange results when using options if you don't follow the implicit order (genre -> artist -> album -> audio items).
