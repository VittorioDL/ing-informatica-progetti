import random

doors = [0, 0, 1]
results = []

def f():
	random.shuffle(doors)
	my_door = doors[0]
	result = 1 if my_door == 0 else 0

	results.append(result)
	

for _ in range(1000000):
	f()

print(results.count(1)/len(results))
