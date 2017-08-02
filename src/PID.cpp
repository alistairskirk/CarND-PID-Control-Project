#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_i, double Ki_i, double Kd_i) {
	prev_cte = 0;
	err = 0;
	i_error = 0;
	p_error = 0;
	d_error = 0;
	Kp = Kp_i;	
	Ki = Ki_i;
	Kd = Kd_i;
}

void PID::UpdateError(double cte) {	
	p_error = cte;
	d_error = cte - prev_cte;
	i_error += cte;

	prev_cte = cte;
}

double PID::TotalError() {
}

