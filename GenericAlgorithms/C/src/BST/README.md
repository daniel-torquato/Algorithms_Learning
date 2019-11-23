# Definition
	"Let x be a node in a binary search tree. If y is a node in the left subtree
	of x. then y.key <= x.key. If y is a node in the right subtree of x, then
	y.key >= x.key." by Cormen [1]

# Theorem
	If x is the root of an n-node subtree, then the call INODER_TREE_WALK(x)
	takes O(n) time.

12.2
	We can implemnt the dynamic-set operations SEARCH, MINIMUM, MAXIMUM,
	SUCESSOR, and PREDECESSOR so that each one runs in O(h) time on a binary
	search tree of height h.


