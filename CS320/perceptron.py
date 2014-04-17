#training_set = [((1,0,0), 0), ((1,0,1), 1), ((1,1,0), 1), ((1,1,1), 1)]
training_set = [((1,0,0), 0), ((1,0,1), 0), ((1,1,0), 0), ((1,1,1), 1)]

weight = [0,0,0]
threshold = 0

def dot_product(values, weight):
	return sum(value * weight for value, weight in zip(values,weight))

print "Training set: ", training_set

while True:
	error_count = 0
	for vector, output in training_set:
		result = dot_product(vector,weight) > threshold		#result is greater of dot product and threshold
		error = output - result		#0 is no error. Else is either + or - error and is considered when modifying weight
		if error != 0:
			error_count += 1
			for index, value in enumerate(vector):
				weight[index] += error * value
	if error_count == 0:
		print "Final Weights: ", weight
		break