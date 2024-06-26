# Hug the Lanes IoT

This was a team project for CS 347 at Stevens Institute of Technology, Spring 2023. The members were: 
- Justerini Mejia (Me)
- Justus Neumeister
- Philip Russo
- TaeSeo Um

## Project Structure

### PDF Documentation 
Includes both our final pitch presentation and software documentation that evolved throughout the course. It details the project scope, features, and instructions.

### Code
`electronsystem.cpp`: The main application code.

`rawData.txt`: Contains the sensor data we processed.

Feel free to change the data to your own. It follows the same format, and here's an example:
```
forwardCollision1, 137
forwardCollision2, 89
backCollision1, 172
backCollision2, 201
lightSensor1, 322
lightSensor2, 768
lightSensor3, 452
lightSensor4, 199
cruiseControlButtonPressed, False
accelerometer, 121
breakStatus, 3
gasPedal, 2
interiorThermometer, 22
exteriorThermometer, 48
desiredThermometer, 68
autoTemperatureStatus, False
rainSensor, 1
wiperStatus, 0
autoWiperStatus, False
trafficCamera, green
autoTrafficDetection, False
driverSteering, True
steeringWheelStatus, -180
roadAngleCamera1, -36
roadAngleCamera2, 63
emergencyVehicleCamera1, False
emergencyVehicleCamera2, False
doorLockButtonPressed1, False
doorLockButtonPressed2, False
doorLockButtonPressed3, False
doorLockButtonPressed4, False
```

| Variable                   | Type    | Description                                        | Possible Values                               |
|----------------------------|---------|----------------------------------------------------|-----------------------------------------------|
| forwardCollision(1/2)      | int     | Distance from sensor to obstacle (front).          | distance in feet                              |
| backCollision(1/2)         | int     | Distance from sensor to obstacle (back).           | distance in feet                              |
| lightSensor(1-4)           | int     | Sensed light level from sensors 1-4.               | lumens                                        |
| cruiseControlButtonPressed | boolean | Indicates if the cruise control button is pressed. | True/False                                    |
| accelerometer              | int     | Current speed of the vehicle.                      | mph                                           |
| breakStatus                | int     | Brake status.                                      | (1-5, with 5 being the highest)               |
| gasPedal                   | int     | Gas pedal pressure.                                | (1-5, with 5 being the highest)               |
| interiorThermometer        | int     | Interior temperature.                              | Fahrenheit                                    |
| exteriorThermometer        | int     | Exterior temperature.                              | Fahrenheit                                    |
| desiredThermometer         | int     | Desired interior temperature.                      | Fahrenheit                                    |
| autoTemperatureStatus      | boolean | Is the automatic temperature control on?           | True/False                                    |
| rainSensor                 | int     | Rain sensor status.                                | (0-5, with 5 being very wet)                  |
| wiperStatus                | int     | Wiper status.                                      | (0-5, with 5 being the highest speed)         |
| autoWiperStatus            | boolean | Is the automatic wiper activation on?              | True/False                                    |
| trafficCamera              | string  | Traffic light detected color                       | "green", "yellow", "red", "unidentifiable"    |
| autoTrafficDetection       | boolean | Is the traffic light detection on?                 | True/False                                    |
| driverSteering             | boolean | Indicates if the driver is steering manually.      | True/False                                    |
| steeringWheelStatus        | int     | Steering wheel angle.                              | (-180 to 180 degrees)                         |
| roadAngleCamera(1/2)       | int     | Road angle detected by each camera.                | (-180 to 180 degrees)                         |
| emergencyVehicleCamera(1/2)| boolean | Is an emergency vehicle sensed?                    | True/False                                    |
| doorLockButtonPressed(1-4) | boolean | Door lock button status for each door.             | True/False                                    |

#### Running the Code
We wrote and ran the code on a Linux VM. 

1. **Clone the repository**:
```bash
git clone https://github.com/jammskia/hug-the-lanes-IoT.git
```

2. **Move to the code directory**:
```bash
cd hug-the-lanes-IoT/AlsetSystem
```

3. **Compile**:
```bash
make
```

4. **Execute the code**
```bash
./electronsystem
```

After the code is executed, it should output a log.txt file in the same directory. It shows the results of all the functions' calculations and the time they were finalized, like this:
```
New entry:
------------------------
2024-04-12 23:59:14.799: automaticHeadLights{lightLevel: 435.25 state: 0 Decision: none}
2024-04-12 23:59:14.799: automaticDoorLocks{speed: 121 closeDoors: 0 Decision: none}
2024-04-12 23:59:14.799: laneCorrection{speed: 121 leftLaneAngle: -36 rightLaneAngle: 63 beingSteered: 0 Decision: Steer 198}
2024-04-12 23:59:14.799: ForwardCollision: Distance : 113 - Applying Brake level 2
2024-04-12 23:59:14.799: RearCollision: Distance : 186.5 - Applying Brake level 2
2024-04-12 23:59:14.799: Wiper status increased to0
2024-04-12 23:59:14.799: Interior temperature increased22
2024-04-12 23:59:14.799: trafficLightRecognition{ Traffic Light Recognition is off }
2024-04-12 23:59:14.799: emergencyVehicleDetection{ No Emergency Vehicle Present. }
2024-04-12 23:59:14.799: automaticHeadLights{lightLevel: 675.25 state: 0 Decision: off}
2024-04-12 23:59:14.799: automaticDoorLocks{speed: 178 closeDoors: 0 Decision: none}
2024-04-12 23:59:14.799: laneCorrection{speed: 178 leftLaneAngle: 45 rightLaneAngle: -54 beingSteered: 0 Decision: Steer -198}
2024-04-12 23:59:14.799: ForwardCollision: Distance : 125 - Applying Brake level 2
2024-04-12 23:59:14.799: RearCollision: Distance : 74 - Applying Brake level 3
2024-04-12 23:59:14.799: Wiper status stayed the same2
2024-04-12 23:59:14.799: Interior temperature increased35
2024-04-12 23:59:14.799: trafficLightRecognition{ YELLOW traffic light detected! }
2024-04-12 23:59:14.799: emergencyVehicleDetection{ Emergency Vehicle is Approaching! }
2024-04-12 23:59:14.799: automaticHeadLights{lightLevel: 472.75 state: 0 Decision: off}
2024-04-12 23:59:14.799: automaticDoorLocks{speed: 46 closeDoors: 0 Decision: none}
2024-04-12 23:59:14.799: laneCorrection{speed: 46 leftLaneAngle: 20 rightLaneAngle: 5 beingSteered: 0 Decision: Steer -30}
```
You don't even have to delete it per run. It should just append each entry to the end.
