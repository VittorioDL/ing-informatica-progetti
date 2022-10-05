import random

win = 0
tot = 100000
for j in range(tot):
    porte = [True, False, False]
    random.shuffle(porte)
    scelta = random.randint(1, 3)

    for k in range(3):
        if(not porte[k] and k != (scelta-1)):
            porta_vuota = k
                        
    for i in range(3):
        if(i != (scelta-1) and i != porta_vuota):
            if(porte[i]):
                win += 1
                
        
print("Hai vinto "+str(win)+" volte su 100000")
print("Probabilità di vincita: "+str((win/tot)*100)+"%")


