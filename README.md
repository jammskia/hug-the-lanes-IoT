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
2024-04-12 23:59:14.799: ForwardCollision: Distance : 121.5 - Applying Brake level 2
2024-04-12 23:59:14.799: RearCollision: Distance : 97 - Applying Brake level 3
2024-04-12 23:59:14.799: Wiper status decreased to1
2024-04-12 23:59:14.799: Interior temperature increased55
2024-04-12 23:59:14.799: trafficLightRecognition{ Traffic Light Recognition is off }
2024-04-12 23:59:14.799: emergencyVehicleDetection{ Emergency Vehicle is Approaching! }
2024-04-12 23:59:14.799: automaticHeadLights{lightLevel: 536.75 state: 0 Decision: off}
2024-04-12 23:59:14.799: automaticDoorLocks{speed: 96 closeDoors: 0 Decision: none}
2024-04-12 23:59:14.799: laneCorrection{speed: 96 leftLaneAngle: -10 rightLaneAngle: 47 beingSteered: 0 Decision: Steer 114}
2024-04-12 23:59:14.799: ForwardCollision: Distance : 157.5 - Applying Brake level 2
2024-04-12 23:59:14.799: RearCollision: Distance : 109 - Applying Brake level 2
2024-04-12 23:59:14.799: Wiper status increased to0
2024-04-12 23:59:14.799: Interior temperature increased44
2024-04-12 23:59:14.799: trafficLightRecognition{ GREEN traffic light detected! }
2024-04-12 23:59:14.799: emergencyVehicleDetection{ Emergency Vehicle is Approaching! }
2024-04-12 23:59:14.799: automaticHeadLights{lightLevel: 463 state: 0 Decision: off}
2024-04-12 23:59:14.799: automaticDoorLocks{speed: 150 closeDoors: 0 Decision: none}
2024-04-12 23:59:14.799: laneCorrection{speed: 150 leftLaneAngle: 85 rightLaneAngle: -73 beingSteered: 0 Decision: Steer -316}
2024-04-12 23:59:14.800: ForwardCollision: Distance : 140 - Applying Brake level 2
2024-04-12 23:59:14.800: RearCollision: Distance : 155.5 - Applying Brake level 2
2024-04-12 23:59:14.800: Wiper status stayed the same3
2024-04-12 23:59:14.800: Interior temperature increased30
2024-04-12 23:59:14.800: trafficLightRecognition{ Traffic Light Recognition is off }
2024-04-12 23:59:14.800: emergencyVehicleDetection{ Emergency Vehicle is Approaching! }
2024-04-12 23:59:14.800: automaticHeadLights{lightLevel: 577.25 state: 0 Decision: off}
2024-04-12 23:59:14.800: automaticDoorLocks{speed: 189 closeDoors: 0 Decision: none}
2024-04-12 23:59:14.800: laneCorrection{speed: 189 leftLaneAngle: -50 rightLaneAngle: 12 beingSteered: 0 Decision: Steer 124}
2024-04-12 23:59:14.800: ForwardCollision: Distance : 111.5 - Applying Brake level 2
2024-04-12 23:59:14.800: RearCollision: Distance : 86.5 - Applying Brake level 3
2024-04-12 23:59:14.800: Wiper status decreased to1
2024-04-12 23:59:14.800: Interior temperature decreased78
2024-04-12 23:59:14.800: trafficLightRecognition{ RED traffic light detected! }
2024-04-12 23:59:14.800: emergencyVehicleDetection{ Emergency Vehicle is Approaching! }
2024-04-12 23:59:14.800: automaticHeadLights{lightLevel: 643 state: 0 Decision: off}
2024-04-12 23:59:14.800: automaticDoorLocks{speed: 34 closeDoors: 0 Decision: none}
2024-04-12 23:59:14.800: laneCorrection{speed: 34 leftLaneAngle: 65 rightLaneAngle: -88 beingSteered: 0 Decision: Steer -306}
2024-04-12 23:59:14.800: ForwardCollision: Distance : 100.5 - Applying Brake level 2
2024-04-12 23:59:14.800: RearCollision: Distance : 148 - Applying Brake level 2
2024-04-12 23:59:14.800: Wiper status stayed the same2
2024-04-12 23:59:14.800: Interior temperature increased40
2024-04-12 23:59:14.800: trafficLightRecognition{ Traffic Light Recognition is off }
2024-04-12 23:59:14.800: emergencyVehicleDetection{ Emergency Vehicle is Approaching! }
2024-04-12 23:59:14.800: automaticHeadLights{lightLevel: 398.5 state: 0 Decision: on}
2024-04-12 23:59:14.800: automaticDoorLocks{speed: 111 closeDoors: 0 Decision: none}
2024-04-12 23:59:14.800: laneCorrection{speed: 111 leftLaneAngle: 0 rightLaneAngle: 30 beingSteered: 0 Decision: Steer 60}
2024-04-12 23:59:14.800: ForwardCollision: Distance : 199.5 - Applying Brake level 2
2024-04-12 23:59:14.800: RearCollision: Distance : 76.5 - Applying Brake level 3
2024-04-12 23:59:14.800: Wiper status increased to0
2024-04-12 23:59:14.800: Interior temperature increased67
2024-04-12 23:59:14.800: trafficLightRecognition{ YELLOW traffic light detected! }
2024-04-12 23:59:14.800: emergencyVehicleDetection{ Emergency Vehicle is Approaching! }
2024-04-12 23:59:14.800: automaticHeadLights{lightLevel: 718.25 state: 0 Decision: off}
2024-04-12 23:59:14.800: automaticDoorLocks{speed: 159 closeDoors: 0 Decision: none}
2024-04-12 23:59:14.800: laneCorrection{speed: 159 leftLaneAngle: 75 rightLaneAngle: -60 beingSteered: 0 Decision: Steer -270}
2024-04-12 23:59:14.800: ForwardCollision: Distance : 159.5 - Applying Brake level 2
2024-04-12 23:59:14.800: RearCollision: Distance : 217.5 - Applying Brake level 1
2024-04-12 23:59:14.800: Wiper status increased to1
2024-04-12 23:59:14.800: Interior temperature decreased84
2024-04-12 23:59:14.800: trafficLightRecognition{ Traffic Light Recognition is off }
2024-04-12 23:59:14.800: emergencyVehicleDetection{ Emergency Vehicle is Approaching! }
2024-04-12 23:59:14.800: automaticHeadLights{lightLevel: 522 state: 0 Decision: off}
2024-04-12 23:59:14.800: automaticDoorLocks{speed: 67 closeDoors: 0 Decision: none}
2024-04-12 23:59:14.800: laneCorrection{speed: 67 leftLaneAngle: -15 rightLaneAngle: 80 beingSteered: 0 Decision: Steer 190}
2024-04-12 23:59:14.800: ForwardCollision: Distance : 163.5 - Applying Brake level 2
2024-04-12 23:59:14.800: RearCollision: Distance : 78.5 - Applying Brake level 3
2024-04-12 23:59:14.800: Wiper status decreased to3
2024-04-12 23:59:14.800: Interior temperature increased32
2024-04-12 23:59:14.800: trafficLightRecognition{ GREEN traffic light detected! }
2024-04-12 23:59:14.800: emergencyVehicleDetection{ Emergency Vehicle is Approaching! }
```