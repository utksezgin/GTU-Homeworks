# Daily Coding Problem
# This problem was asked by Apple.
# Implement a queue using two stacks. Recall that a queue is a FIFO (first-in, first-out)
# data structure with the following methods: enqueue, which inserts an element into the queue,
# and dequeue, which removes it.

# Used lists as stacks by using only extend and pop functions instead of implementing the stack aswell.

# Queue is basicly the opposite of the stack so moving elements from one stack to other reverses the order. dequeue pops the element from current queue stack and once that one is empty,
# it moves elements from the other stack.

class Queue:

	def __init__(self):
		self.currentQueueIndex = 0
		self.stack = []
		self.stack.append([])
		self.stack.append([])

	def enqueue(self, element):
		if len(self.stack[self.currentQueueIndex]) == 0:
			self.stack[self.currentQueueIndex].append(element)
		else:
			self.stack[(self.currentQueueIndex+1)%2].append(element)
			



	def dequeue(self):
		nextInQueue = self.stack[self.currentQueueIndex].pop()
		if len(self.stack[self.currentQueueIndex]) == 0:
			nextQueueIndex = (self.currentQueueIndex+1)%2
			for i in range(len(self.stack[nextQueueIndex])):
				self.stack[self.currentQueueIndex].append(self.stack[nextQueueIndex])
			self.currentQueueIndex = nextQueueIndex

		return nextInQueue


# Test Driver

# q = Queue()
# q.enqueue(1)
# q.dequeue()
# q.enqueue(3)
# q.enqueue(9)
# q.dequeue()
# q.enqueue(5)
# q.enqueue(8)
# q.dequeue()
# q.dequeue()