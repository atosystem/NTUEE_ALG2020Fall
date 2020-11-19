# usage: python generate_cases.py <N>
import sys
import numpy as np

print("N={}".format(int(sys.argv[1])))

arr = np.arange(2*int(sys.argv[1]))


np.random.shuffle(arr)

# print(arr)


x = 0
outfile = open(sys.argv[2],'w')
outfile.write("{}\n".format(2*int(sys.argv[1])))
while(x<2*int(sys.argv[1])):
    outfile.write("{} {}\n".format(arr[x],arr[x+1]))
    x=x+2

outfile.write("0\n")

outfile.close()
print("Done")


