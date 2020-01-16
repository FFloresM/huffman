import random
with open('number.txt', 'w+') as n:
	for i in range(2**25):
		n.write(str(random.randint(0,1)))