# PID CONTROLLER

## Intro
This project consists in the implementation of a PID Controller in C++ to maneuver the vehicle around the lake track. For that we will need to use the [simulator](https://github.com/udacity/self-driving-car-sim/releases) that we already used in Term 1.

## Requirements

This project involves the Term 2 Simulator which can be downloaded [here](https://github.com/udacity/self-driving-car-sim/releases)

This repository includes two files that can be used to set up and install [uWebSocketIO](https://github.com/uWebSockets/uWebSockets) for either Linux or Mac systems. For windows you can use either Docker, VMware, or even [Windows 10 Bash on Ubuntu](https://www.howtogeek.com/249966/how-to-install-and-use-the-linux-bash-shell-on-windows-10/) to install uWebSocketIO. 

## How to run the code

Once requirements are fullfield, you can run the code following the next steps:

1. mkdir build
2. cd build
3. cmake ..
4. make
5. ./pid

## Results

### Intro
For the correct behavior of the PID Controller we need to provide  three coefficients: 

* P - Proportional Term: controls the steering angle of the car in proportion to the cross track error (CTE). This controller alone couses the car to always overshoot the reference trajectory. The higher the value the sharper the car makes the turn.
* I - Integral Term: deals with large CTE which might be caused by systematic bias. The integral term adjusts to this bias and affects more and more as the time goes by. The higher the value, the sharper the car makes a turn.
* D - Differential Term: A temporal derivative of the CTE. When applied with P, it allows the car to gracefully approach the target reference trajectory without shooting to the target reference trajectory. The higher the value, the less sharp the car makes a turn.

### Manual way
Once the PID Controller is implemented we provided the coefficients manually and observed how the car maneuvers in the simulator. To find the correct values for Kp, Ki and Kd, we followed the next steps:

1. Set Ki and Kd to zero, and find a value of Kp which works fairly well. The car oscillates and eventually goes out of the track.
2. Set Kp fixed and use some non-zero values for Kd. Slowly increase Kd until the oscillations decrease.
3. Tune both Kd and Kp trying to remove oscillations, so the car drives smoothly.
4. Use non-zero values for Ki. This value must be very small.

Following this steps and after a lot of testing, the best performance I got was with the values:

Kp = 0.14,
Ki = 0.0001,
Kd = 5.5

With this values the car was able to drive through the lake track and staying all the time on the road.

### Twiddle
Once I had the parameters that allowed the car to drive safely on the road. I used Twiddle to optimize those parameters. Twiddle is an optimization algorithm that tries to find a good choice of parametrs for an algorithm that returns an error.
I used Twiddle for an specific amount of steps, starting with 200, and keep increasing this number till 1000 steps to get the best results. I left twiddle running for an hour approximately and got the lowest error with this parameters:

Kp = 0.485079,
Ki = 0.000359376,
Kd = 4.9994

