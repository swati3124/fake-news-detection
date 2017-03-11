import urllib
import os
from os import listdir
import sys

def get_sentiment_score(text):
    data = urllib.urlencode({"text": text})
    u = urllib.urlopen("http://text-processing.com/api/sentiment/", data)
    the_page = u.read()
    print(the_page)


if __name__ == "__main__":

    get_sentiment_score("I'm a very good boy ")

    dir = os.path.dirname(__file__)
    for f in listdir(os.path.join(dir, '../../Fake')):
        print f
        file = open(os.path.join(dir, '../../Fake/')+f, 'r')
        print get_sentiment_score(file.read())

    for f in listdir(os.path.join(dir, '../../Real')):
        print f
        file = open(os.path.join(dir, '../../Real/')+f, 'r')
        print get_sentiment_score(file.read())