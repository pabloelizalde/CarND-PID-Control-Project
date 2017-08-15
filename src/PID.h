#include <uWS/uWS.h>
#include <iostream>
#include <vector>

#ifndef PID_H
#define PID_H

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */
  double Kp;
  double Ki;
  double Kd;

  /*
  * Helpers
  */
  bool is_initialized;
  bool first_flag;
  bool second_flag;
  int steps;
  double best_error;
  double avg_error;
  double total_error;
  int coefficient;
  std::vector<double> dp;
  /*
  * Constructors
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp_, double Ki_, double Kd_);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();

  /*
  * Reset PID values and simulator.
  */
  void Reset(uWS::WebSocket<uWS::SERVER> ws);

  /*
  * Twiddle algorithm
  */
  void Twiddle(double cte, int max_steps, uWS::WebSocket<uWS::SERVER> ws);
};

#endif /* PID_H */
