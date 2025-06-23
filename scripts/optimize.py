import numpy as np
import osqp
from scipy import sparse
from scipy.optimize import minimize, LinearConstraint
from numpy.linalg import inv

Q = np.loadtxt("Q.txt")
A = np.loadtxt("A.txt")
c = np.loadtxt("c.txt")
b = np.loadtxt("b.txt")


def objective(x):
    return -0.5 * (x @ Q @ x) - c @ x  # Negative for maximization

# Gradient (Jacobian) of the objective
def grad_objective(x):
    return -(Q @ x + c)

# Constraints: A x >= b ⇨ -A x <= -b
linear_constraint = LinearConstraint(-A, -np.inf, -b)


# Initial guess
x0 = np.loadtxt("x0.txt")
# print("constraints", A@x0 - b)

result = minimize(
    objective,
    x0,
    method='SLSQP',
    jac=grad_objective,
    constraints=[linear_constraint],
    options={'disp': True}
)

if result:
    print("Optimal x:", result)
    print("Optimal x:", result.x, A @ result.x - b)
else:
    print("Optimization failed:", result.message)

print (np.array(inv(Q) @ c), A @ inv(Q) @ c - b)
print( x0 , A @ x0 - b)