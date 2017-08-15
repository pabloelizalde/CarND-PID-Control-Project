#include "PID.h"

using namespace std;

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  Kp = Kp_;
  Ki = Ki_;
  Kd = Kd_;
  p_error = 0.0;
  i_error = 0.0;
  d_error = 0.0;
  steps = 0;
  total_error = 0.0;
  avg_error = 0.0;
  coefficient = 0;
  is_initialized = false;
  first_flag = true;
  second_flag = true;
  dp = {0.0345192, 0.00005, 0.313811}; // This values were also optimized with Twiddle
}

void PID::UpdateError(double cte) {

  d_error = cte - p_error;
  p_error = cte;
  i_error += cte;

  steps++;
  total_error += (cte * cte);
  avg_error = total_error / steps;
}

double PID::TotalError() {
  return -Kp * p_error - Kd * d_error - Ki * i_error;;
}

void PID::Reset(uWS::WebSocket<uWS::SERVER> ws) {
  steps = 0;
  total_error = 0;
  p_error = 0.0;
  i_error = 0.0;
  d_error = 0.0;
  string reset_message = "42[\"reset\",{}]";
  ws.send(reset_message.data(), reset_message.length(), uWS::OpCode::TEXT);
}

void PID::Twiddle(double cte, int max_steps, uWS::WebSocket<uWS::SERVER> ws) {

  if (steps == max_steps) {

		if (!is_initialized) {
			best_error = avg_error;
			is_initialized = true;
			std::cout << "Initialization Kp: " << Kp << " Ki: " << Ki
									<< " Kd: " << Kd << " Error: " << best_error << std::endl;
		} else {
			if (first_flag) {
				switch (coefficient) {
				case 0:
					Kp += dp[coefficient];
					break;
				case 1:
					Ki += dp[coefficient];
					break;
				case 2:
					Kd += dp[coefficient];
				}
				first_flag = false;
				second_flag = true;
			} else if (avg_error < best_error) {
				best_error = avg_error;
				dp[coefficient] *= 1.1;
				coefficient = (coefficient + 1) % 3;
				first_flag = true;
				std::cout << "New best Kp: " << Kp << " Ki: " << Ki
						<< " Kd: " << Kd << " Error: "
						<< best_error << std::endl;
			} else if (second_flag) {
				switch (coefficient) {
				case 0:
					Kp -= 2 * dp[coefficient];
					break;
				case 1:
					Ki -= 2 * dp[coefficient];
					break;
				case 2:
					Kd -= 2 * dp[coefficient];
				}
				second_flag = false;
			} else {
				switch (coefficient) {
				case 0:
					Kp += dp[coefficient];
					break;
				case 1:
					Ki += dp[coefficient];
					break;
				case 2:
					Kd += dp[coefficient];
				}
				dp[coefficient] *= 0.9;
				first_flag = true;
				coefficient = (coefficient + 1) % 3;
			}

		}
		std::cout << "Updated Kp: " << Kp << " Ki: " << Ki << " Kd: " << Kd << std::endl;
    std::cout << "Values of dp[0]: " << dp[0] << " dp[1]: " << dp[1] << " dp[2]: "<< dp[2] << std::endl;
    Reset(ws);
	}

}
