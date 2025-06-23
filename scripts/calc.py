import numpy as np
from scipy.optimize import minimize, LinearConstraint
from numpy.linalg import inv

Q = np.loadtxt("Q.txt")
A = np.loadtxt("A.txt")
c = np.loadtxt("c.txt")
u0 = np.loadtxt("x0.txt")
b = np.loadtxt("b.txt")

C = np.array([-6.30246, -6.30246, 42])
np.set_printoptions(suppress=True)
r = 8.

print(A @ u0 - b)
print(A @ inv(Q) @ c - b)


# C = np.array([43.7677,43.7677,60])
# np.set_printoptions(suppress=True)
# r = 8.
#
# displ1 = np.array([5.11682,5.11682,-3.41121])
#
# n = np.array([-0.948683,0,0.316228])
# alpha0 = 0
# alpha1 = 0.113314
# alpha2 = 0.886686
# u0 = np.array([40,60,30])
# u1 = np.array([40,40,30])
# u2 = np.array([50,50,60])
# uS1 = alpha0 * u0 + alpha1  * u1 + alpha2 * u2
# uB1 = C + displ1
# print(n)
# # print(u0)
# print(uS1)
# print(uB1)
# print("uB1 - uS1", uB1 - uS1)
# print((uB1 - uS1).dot(n))

# print(alpha0 * u0 + alpha1 * u1)