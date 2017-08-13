# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program
Alistair Kirk July 2017

---

## Writeup and Reflection
This project explores the creation of a PID algorithm for use with the Term 2 Simulator. The goal is to automate steering of the test vehicle around the lake track loop.
The sensor input to our program provides the current steering angle, velocity, and Current Track Error (CTE). The CTE is the distance of the center of the car from the track centerline.

Videos of the functioning PID controller can be found on Youtube.
  * [PID Project Full Course: Shows the car successfully driving around the whole test track.](https://youtu.be/wpHF9sHSFD8)
  * [PID Project Tough Area: Shows a particularly difficult turn for this controller, where there is a significant amount of overshoot but it recovers.](https://youtu.be/p7rX8X5Yc_s)

### The PID procedure follows what was taught in the lessons.

The majority of the PID controller theory and code style was taken from the Udacity course, with additional learning from resources listed below.

I have implemented two PID controllers in this project:
* The first PID was used to control the steering angle of the car using the Current Track Error.
* The second PID was used to control the speed of the vehicle, where I set it to a fixed value of 15 mph. 

The core of the PID controller is shown here:
```
steer_value = -pid.Kp * pid.p_error * speed_steer - pid.Kd * pid.d_error *speed_steer_id - pid.Ki * pid.i_error*speed_steer_id;
```

### Describe how the final hyperparameters were chosen.
The Proportional, Integral, and Derivative gains were manually tuned for this project:

Controller | Proportional | Integral | Derivative
--- | --- | --- | ---
Default Steering | 0.9 | 0.001 | 0.6 
Speed | 0.65 * 0.9 | 2.6 * 0.001 | 0.65 * 0.6

The PID controller for speed was set as a fraction of the steering controller, because I believed they would need to be correlated to find a suitable stability point during tuning.
Here I have chosen to reduce the Proportional and Derivative rations by 0.65, and increase the Integral by 2.6, when driving at the set full speed of 15 mph.

If the car gets too far off track, the speed is set at 10mph, and the Default Steering values are used in the steering controller.
This helps the car if it gets too far off track or takes a corner too sharply - the proportional and derivative gain are higher which means the rise time of the steering response is increased: it turns more sharply.
The Integral gain is also reduced, which tends to reduce the overshoot during sharp turns.

### Describe the effect each of the P, I, D components had in your implementation.
The selection of the gains went as expected, and was generally aligned with the theory:
1. Obtain an open-loop response and determine what needs to be improved
2. Add a proportional control to improve the rise time
3. Add a derivative control to improve the overshoot
4. Add an integral control to eliminate the steady-state error
5. Adjust each of Kp, Ki, and Kd until you obtain a desired overall response.

Overall the PID controller works well enough to get the car around the course. Drawbacks include the Gains not being ideal for all driving conditions (see tight turns example) and the fact that PID controllers are very much reactive and not proactive controllers.

### Future considerations if one wanted to use a PID controller:
  * Dynamic speed selection: go faster on straight-aways but slow down on the curves, this would improve corner handling and overshoot but would need a way to predict if you were in a turn or not
  * Use of a car model to try and predict where the car will be in a few timesteps. The PID steering control is reactive and not predictive, so as the CTE changes around a turn, the PID controller is playing catchup with the last time-step

## References:
[PID Intro by UMichigan](http://ctms.engin.umich.edu/CTMS/index.php?example=Introduction&section=ControlPID)

[MATLAB PID Theory](https://www.allaboutcircuits.com/technical-articles/an-introduction-to-control-systems-designing-a-pid-controller-using-matlabs/)
