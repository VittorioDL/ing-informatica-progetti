def sqrt(b, n):
	if b <= 0:
		return None
	if n == 2:
		return float((1 + b) / 2)
	else:
		return (sqrt(b, n-1) + b/sqrt(b, n-1)) / 2
