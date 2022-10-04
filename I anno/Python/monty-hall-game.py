import random

#TO-DO: iterare simulazioni del gioco scegliendo sempre il
#cambio porta e calcolare probabilità vincita

porte = [True, False, False]
random.shuffle(porte)

print(porte)
scelta = int(input("Scegli una porta tra 1 e 3: "))

for k in range(3):
    if(not porte[k] and k != (scelta-1)):
        porta_vuota = k
        
print("La porta "+str(porta_vuota+1)+" è vuota")
cambio = input("Vuoi cambiare porta? (y/n): ")

if(cambio == "y"):
    for i in range(3):
        if(i != (scelta-1) and i != porta_vuota):
            if(porte[i]):
                print("Hai vinto!!!")
            else:
                print("Hai perso...")
else:
    if(porte[scelta-1]):
        print("Hai vinto!!!")
    else:
        print("Hai perso...")


