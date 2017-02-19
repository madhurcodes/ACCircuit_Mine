import random
import string
def genWord(n):
    a = ""
    for x in range(n):
        a += random.choice(string.ascii_letters)
    return a
genWord(6)
dd = open("test.txt","w")
def genComponent(nl):
    a= ""
    a += (genWord(random.choice(range(2,9)))+" ")
    a += (random.choice(nl)+" " + random.choice(nl)+" ")
    a += (str(random.choice(range(4,199)))+random.choice(["","N","K","MEG","P","F","U"])+random.choice(["","H","F"])+"\n")
    return a
ll = ["","N","K","MEG","P","F","U"]
def genSource(nl):
    a= ""
    a += (random.choice(["I","V"])+genWord(random.choice(range(2,9)))+" ")
    a+=(random.choice(nl)+" " + random.choice(nl)+" ")
    a+= ("SINE ( "+ str(random.choice(range(4,199)))+" "+str(random.choice(range(4,199)))+" "+ str(random.choice(range(4,199)))+random.choice(ll)+"HZ "+str(random.random())+"S "+str(random.random())+" )\n")
    return a
ml = []
def addNets(k):
    for s in range(k):
        ml.append(genWord(random.choice(range(2,9))))
def main():
    addNets(100)
    for r in range(4000):
        dd.write(genComponent(ml))
        dd.write(genSource(ml))
main()
dd.close()
