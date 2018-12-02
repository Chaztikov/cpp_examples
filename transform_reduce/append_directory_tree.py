import os, sys


def main():
    sys.argv[0]
    wdir=[]
    for val in sys.argv:
        wdir.append(str(val))
    print((wdir) 
    return [f for _,f,_ in os.walk(wdir)]

