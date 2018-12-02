import os, sys


def main(sys.argc, sys.argv):
    sys.argv[0]
    wdir=[]
    for val in sys.argv:
        wdir.append(str(val))
    print(wdir) 
    out = [f for _,f,_ in os.walk(wdir)]
    print(out)
    return out
