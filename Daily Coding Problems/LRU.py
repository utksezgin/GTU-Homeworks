from collections import deque
# This problem was asked by Google.

# Implement an LRU (Least Recently Used) cache. It should be able to be initialized with a cache size n, and contain the following methods:
# •	set(key, value): sets key to value. If there are already n items in the cache and we are adding a new item, then it should also remove the least recently used item.
# •	get(key): gets the value at key. If no such key exists, return null.
# Each operation should run in O(1) time.

#deque from collections used as a queue and dictionary as hashmap.

class LRU:

	def __init__(self, n):
		self.size = n
		self.hashMapCache = {}
		self.q = deque()

	def set(self, key, value):
		if len(self.q) >= self.size:
			removedItem = self.q.pop()
			for x in removedItem:
				self.hashMapCache.pop(x, None)
			print(str(removedItem) + "is removed from cache")
			self.size -= 1

		self.hashMapCache[key] = value
		print(str({key:value}) + "is added to cache" )
		self.q.appendleft({key:value})

	def get(self, key):
		return self.hashMapCache.pop(key, None)



# Test Driver
l = LRU(5)
l.set("test0", 0)
l.set("test1", 1)
l.set("test2", 2)
l.set("test3", 3)
l.set("test4", 4)
l.set("test5", 5)
l.set("test6", 6)
l.set("test7", 7)
l.set("test8", 8)
print(l.get("test1"))