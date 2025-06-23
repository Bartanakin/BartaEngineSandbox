#include "Sandbox.h"

int main() {
    auto app = new Sandbox();
    app->run();
    delete app;

    return 0;
}

// #include <iostream>
// #include <nlopt.hpp>
// #include <vector>

// // Objective function: f(x, y) = x^2 + y^2
// double objective_function(const std::vector<double>& x, std::vector<double>& grad, void* data) {
//   if (!grad.empty()) {
//     grad[0] = 2 * x[0]; // df/dx
//     grad[1] = 2 * x[1]; // df/dy
//   }
//   return x[0]*x[0] + x[1]*x[1];
// }
//
// // Constraint: x + y >= 1  =>  1 - x - y <= 0
// double constraint_func(const std::vector<double>& x, std::vector<double>& grad, void* data) {
//   if (!grad.empty()) {
//     grad[0] = -1.0; // dg/dx
//     grad[1] = -1.0; // dg/dy
//   }
//   return 1 - x[0] - x[1];
// }
//
// int main() {
//   const int dim = 2;
//   nlopt::opt opt(nlopt::LD_SLSQP, dim); // Use the Method of Moving Asymptotes algorithm
//
//   // Set the objective function
//   opt.set_min_objective(objective_function, nullptr);
//
//   // Add the constraint
//   opt.add_inequality_constraint(constraint_func, nullptr, 1e-8);
//
//   // Set lower and upper bounds (optional)
//   std::vector<double> lb = { -10.0, -10.0 };
//   std::vector<double> ub = { 10.0, 10.0 };
//   opt.set_lower_bounds(lb);
//   opt.set_upper_bounds(ub);
//
//   // Set optimization parameters
//   opt.set_xtol_rel(1e-4);
//
//   // Initial guess
//   std::vector<double> x = { 0.0, 0.0 };
//
//   // Run optimization
//   double minf;
//   nlopt::result result = opt.optimize(x, minf);
//
//   std::cout << "Result: " << result << "\n";
//   std::cout << "Found minimum at f(" << x[0] << ", " << x[1] << ") = " << minf << std::endl;
//
//   return 0;
// }