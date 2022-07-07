import numpy as np
import matplotlib.pyplot as plt
nb_ep=40

fichier1=open("data1.txt","r")
fichier2=open("data2.txt","r")
fichier3=open("data3.txt","r")
liste_lignes1=fichier1.readlines()
liste_lignes2=fichier2.readlines()
liste_lignes3=fichier3.readlines()

x,y=list(),list()
for ch in liste_lignes1[:nb_ep]:
    x.append(int((ch.split())[0]))
    y.append(int((ch.split())[1]))

plt.figure("Nombre d'actions par episode")
plt.plot(x,y,label="Facteur d'apprentissage=1")
plt.legend(loc="upper right")
plt.title("Effect de la variation de la vitesse d'apprentissage")
plt.xlabel("Numero de l'episode")
plt.ylabel("Nombre d'actions")

x.clear()
y.clear()

for ch in liste_lignes2[:nb_ep]:
    x.append(int((ch.split())[0]))
    y.append(int((ch.split())[1]))


plt.plot(x,y,label="Facteur d'apprentissage=0.5")
plt.legend(loc="upper right")


x.clear()
y.clear()

for ch in liste_lignes3[:nb_ep]:
    x.append(int((ch.split())[0]))
    y.append(int((ch.split())[1]))

plt.plot(x,y,label="Facteur d'apprentissage=0.1")
plt.legend(loc="upper right")

plt.ylim(0, 2000)

plt.show()

    

print("Python3 marche bien")

fichier1.close()
fichier2.close()
fichier3.close()
