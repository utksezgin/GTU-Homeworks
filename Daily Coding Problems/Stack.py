# This problem was asked by Amazon.

# Implement a stack that has the following methods:
# •	push(val), which pushes an element onto the stack
# •	pop(), which pops off and returns the topmost element of the stack. If there are no elements in the stack, then it should throw an error or return null.
# •	max(), which returns the maximum value in the stack currently. If there are no elements in the stack, then it should throw an error or return null.


# Each method should run in constant time.


class Stack:

	def __init__(self):
		self.maxInStack = None
		self.stack = []	


	def push(self, val):
		self.stack.append(val)
		if self.maxInStack == None:
			self.maxInStack = val
		elif val > self.maxInStack:
			self.maxInStack = val


	def pop(self):
		if len(self.stack) == 0:
			return None
		item = self.stack[len(self.stack)-1]
		self.stack = self.stack[:-1]
		return item

	def max(self):
		if len(self.stack) == 0:
			return None
		else:
			return self.maxInStack

# Test Driver
s = Stack()
s.push(2)
print("2 pushed to stack")
s.push(5)
print("5 pushed to stack")
print("Current Max %d" % s.max())
s.push(7)
print("7 pushed to stack")
print("Current Max %d" % s.max())
print(s.pop())
print(s.pop())
print(s.pop())
print(s.pop())