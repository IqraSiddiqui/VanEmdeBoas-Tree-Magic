import random 

def generate():
    f = open("myfile.txt", "w")
    for i in range(5000):
    #distance between loc1 and loc2 
        distance = random.randint(0, 100000)
        #5000 locations 
        loc1 = random.randint(0, 5000)
        loc2 = random.randint(0, 5000)
        f.write(str(loc1) + " ")
        f.write(str(loc2) + " ")
        f.write(str(distance))
        f.write("\n")
    f.close()

def readData():
    f = open("myfile.txt", "r")
    wholefile = f.read() 
    f.close()
    loc_dist = wholefile.splitlines()
    new = [loc_dist[i].split() for i in range(len(loc_dist))]
    print(new)


#generate() # run it once only 
readData() 


