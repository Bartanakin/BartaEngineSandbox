import cvxpy as cp
import numpy as np
from numpy.linalg import inv

# Q = np.array([[2.0, 0.0],
#               [0.0, 2.0]])
# c = np.array([-2.0, -5.0])
#
# A = np.array([[1, 2], [-1, 2]])
# b = np.array([1, 2])

# x = cp.Variable(2)



Q = np.loadtxt("Q.txt")
A = np.loadtxt("A.txt")
c = np.loadtxt("c.txt")
b = np.loadtxt("b.txt")
x = cp.Variable(18)

x0 = np.loadtxt("x0.txt")

# Define objective
objective = cp.Minimize(-0.5 * cp.quad_form(x, Q) - c @ x)

print(A @ x0 - b)
print(A @ inv(Q) @ c - b)
# Define constraints
constraints = [A @ x >= b]

# Form and solve problem
prob = cp.Problem(objective, constraints)
prob.solve()

# Output results
print("Status:", prob.status)
print("Optimal value:", prob.value)
print("Initial x:", x0)
print("Optimal x:", x.value)
print("Optimal x without constraints:", inv(Q) @ c)
