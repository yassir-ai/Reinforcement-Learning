import matplotlib.pyplot as plt

def affichergraphe(a):
    f = lambda n : a/(2*(n+a))

    x=list(range(0,1001))
    y=[f(i) for i in x]
    ch="a = "+str(a)
    plt.plot(x,y,label=ch)

affichergraphe(500)
affichergraphe(200)
affichergraphe(50)
plt.title("Suite de Variation de epsilon dans ε-greedy")
plt.legend(loc="upper right")
plt.xlabel("Nombre d'episodes")
plt.ylabel("Valeur de epsilon")
plt.show()
