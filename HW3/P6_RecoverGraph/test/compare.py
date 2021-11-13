import sys
from warnings import warn

def parseFile(fn):
    with open(fn, 'r') as f:
        res = f.readline()
		
        adj = {}
        for i in range(1,N):
            line = f.readline()
            array = []
            array.append([int(x) for x in line.split()])
            adj[i] = array
    return adj 

def compare(ada:dict, ade:dict):
	if (len(ada.keys()) != len(ade.keys())):
		warn("Differnt nodes number: Ans {}; EST {}".format(len(ada.keys()), len(ade.keys())))
		return False 
	valid = True
	N = len(ada.keys())

	for i in range(1,N):
		a = ada[i]
		b = ade[i]
		diff = [i for i, j in zip(a, b) if i != j]
		if (len(diff) > 0):
			warn("Different adjacency list at node {}".format(i))
			valid=False
	
	return valid	



def main(argv):
	Fans = argv[1]
	Fest = argv[2]

	ada = parseFile(Fans)
	ade = parseFile(Fest)

	return compare(ada, ade)


if __name__ == "__main__":
	main(sys.argv)