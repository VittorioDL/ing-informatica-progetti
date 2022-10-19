import random

def simulation(n_people, iterations):
	"""
	Il birthday problem consiste nel trovare la probabilità che almeno due persone all'interno
	del campione siano nate lo stesso giorno.

	Questa funzione simula un campione di n persone rappresentate da un numero compreso tra [1, 365], e conta
	il numero di occorrenze.

	params: n_people: numero di persone in un gruppo
	params: iterations: numero di iterazioni 
	"""

	count = 0

	for i in range(iterations):
		birthdays = [random.randint(1, 365) for n in range(n_people)]

		if len(set(birthdays)) != len(birthdays):
			count += 1


	return float(count)/iterations*100


print(simulation(20, 1000))
