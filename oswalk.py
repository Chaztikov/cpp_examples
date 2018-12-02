import os
import sys


input = sys.argv[0]
cwd=os.get_cwd(input)

for _,f,_ in os.walk():
    print(f)
