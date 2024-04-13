#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <tuple>
#include <chrono>
#include <ctime>
#include <vector>
using namespace std;

///////////////////// PLANNING MODULE /////////////////////

class PlanningModule{

    vehicleControlModule vcm;
    systemManagementModule smm;
    
    public:

        float forwardCollision, backCollision, lightSensor, accelerometer, breakStatus, gasPedal, interiorThermometer, exteriorThermometer, desiredThermometer, rainSensor, wiperStatus, steeringWheelStatus, roadAngleCamera1, roadAngleCamera2;
        string trafficCamera;
        bool cruiseControlButtonPressed, autoTemperatureStatus, autoWiperStatus, autoTrafficDetection, driverSteering, emergencyVehicleCamera1, emergencyVehicleCamera2, doorLockButtonPressed1, doorLockButtonPressed2, doorLockButtonPressed3, doorLockButtonPressed4;
        float time;

        void ReceiveData(float _time, float _forwardCollision, float _backCollision, float _lightSensor, float _accelerometer, float _breakStatus, float _gasPedal, float _interiorThermometer, float _exteriorThermometer, float _desiredThermometer, float _rainSensor, float _wiperStatus, float _steeringWheelStatus, float _roadAngleCamera1, float _roadAngleCamera2, string _trafficCamera, bool _cruiseControlButtonPressed, bool _autoTemperatureStatus, bool _autoWiperStatus, bool _autoTrafficDetection, bool _driverSteering, bool _emergencyVehicleCamera1, bool _emergencyVehicleCamera2, bool _doorLockButtonPressed1, bool _doorLockButtonPressed2, bool _doorLockButtonPressed3, bool _doorLockButtonPressed4 ){
            time = _time;
            forwardCollision = _forwardCollision;
            backCollision = _backCollision;
            lightSensor = _lightSensor;
            accelerometer = _accelerometer;
            breakStatus = _breakStatus;
            gasPedal = _gasPedal;
            interiorThermometer = _interiorThermometer;
            exteriorThermometer = _exteriorThermometer;
            desiredThermometer = _desiredThermometer;
            rainSensor = _rainSensor;
            wiperStatus = _wiperStatus;
            steeringWheelStatus = _steeringWheelStatus;
            roadAngleCamera1 = _roadAngleCamera1;
            roadAngleCamera2 = _roadAngleCamera2;
            trafficCamera = _trafficCamera;
            cruiseControlButtonPressed = _cruiseControlButtonPressed;
            autoTemperatureStatus = _autoTemperatureStatus;
            autoWiperStatus = _autoWiperStatus;
            autoTrafficDetection = _autoTrafficDetection;
            driverSteering = _driverSteering;
            emergencyVehicleCamera1 = _emergencyVehicleCamera1;
            emergencyVehicleCamera2 = _emergencyVehicleCamera2;
            doorLockButtonPressed1 = _doorLockButtonPressed1;
            doorLockButtonPressed2 = _doorLockButtonPressed2;
            doorLockButtonPressed3 = _doorLockButtonPressed3;
            doorLockButtonPressed4 = _doorLockButtonPressed4;

            Plan();
        }

        void Plan(){

        }

        string getTime(){
            char buff[70];
            std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
            std::time_t now_c = std::chrono::system_clock::to_time_t(now);
            std::tm now_tm = *std::localtime(&now_c);
            strftime(buff, sizeof buff, "%c", &now_tm);
            return buff;
        }

        std::tuple<bool, bool, bool> automaticWindshield(int rainSensor, int wiperStatus, bool automaticWiperStatus, bool increaseWiper, bool decreaseWiper, bool stayWiper){
            // If automaticWiperStatus is false, automatically print "Automatic wipers are off"
            if (automaticWiperStatus == false){
                std::cout << "Automatic wipers are off" << std::endl;
                return std::make_tuple(false, false, false);
            }
            else{
                // depending on the rainSensor value, the wiperStatus has to increase or decrease to match it
                if (rainSensor > wiperStatus){
                    increaseWiper = true;
                    return std::make_tuple(true, false, false);
                }
                else if (rainSensor < wiperStatus){
                    decreaseWiper = true;
                    return std::make_tuple(false, true, false);
                }else if (rainSensor == wiperStatus){
                    stayWiper = true;
                    return std::make_tuple(false, false, true);
                }
            }
            
            // If none of the flags match, return "stayWiper" flag
            return std::make_tuple(false, false, true);
        }

        std::tuple<bool, bool, bool> automaticTemperature(int interiorTemperature, int exteriorTemperature, int desiredTemperature, bool autoTemperatureStatus, bool increaseTemperature, bool decreaseTemperature, bool stayTemperature) {
            // If autoTemperatureStatus is false, automatically print "Automatic temperature is off"
            if (autoTemperatureStatus == false) {
                std::cout << "Automatic temperature is off" << std::endl;
                return std::make_tuple(false, false, false);
            }
            else {
                // increase or decrease the interiorTemperature to match the desiredTemperature
                if (interiorTemperature < desiredTemperature) {
                    if (increaseTemperature) {
                        return std::make_tuple(true, false, false);
                    }
                    else {
                        return std::make_tuple(false, false, true);
                    }
                }
                else if (interiorTemperature > desiredTemperature) {
                    if (decreaseTemperature) {
                        return std::make_tuple(false, true, false);
                    }
                    else {
                        return std::make_tuple(false, false, true);
                    }
                }
            }

            // If the interiorTemperature and desiredTemperature match, return a "stayTemperature" flag
            if (stayTemperature) {
                return std::make_tuple(false, false, true);
            }

            // If none of the flags match, return "stayTemperature" flag
            return std::make_tuple(false, false, true);
        }

        void automaticHeadlights(float lightLevel, bool state){
            ostringstream log;
            if (lightLevel < 400){//Tells VCS to turn on headlights.
                log << getTime() << ": automaticHeadLights{lightLevel: " << lightLevel << " state: " << state << " Decision: " << "on}";
                smm.receiveLog(log.str());
                vcm.adjustHeadlights(true);
                return;
            }
            else if (lightLevel >= 450){//Tells VCS to turn off headlights.
                log << getTime() << ": automaticHeadLights{lightLevel: " << lightLevel << " state: " << state << " Decision: " << "off}";
                smm.receiveLog(log.str());
                vcm.adjustHeadlights(false);
                return;
            }
            //Tells VCS to keep the headlights as they are.
            log << getTime() << ": automaticHeadLights{lightLevel: " << lightLevel << " state: " << state << " Decision: " << "none}";
            smm.receiveLog(log.str());
            vcm.adjustHeadlights(state);
            return;
        }

        void automaticDoorLocks(float speed, bool closeDoors){
            ostringstream log;
            if (closeDoors && speed >= 12){//Locks all doors
                log << getTime() << ": automaticDoorLocks{speed: " << speed << " closeDoors: " << closeDoors << " Decision: " << "lock}";
                smm.receiveLog(log.str());
                vcm.activateLocks();
                return;
            }
            log << getTime() << ": automaticDoorLocks{speed: " << speed << " closeDoors: " << closeDoors << " Decision: " << "none}";
            smm.receiveLog(log.str());
            return;
        }

        //Keeps the vehicle as centered in the lane as possible
        void laneCorrection(float speed, float leftLaneAngle, float rightLaneAngle, bool beingSteered){
            ostringstream log;
            if (beingSteered || speed == 0 || (leftLaneAngle + rightLaneAngle) == 0){
                log << getTime() << ": laneCorrection{speed: " << speed << " leftLaneAngle: " << leftLaneAngle << " rightLaneAngle: " << rightLaneAngle << " beingSteered: " << beingSteered << " Decision: " << "none}";
                smm.receiveLog(log.str());
                return;
            }
            //Assumes that a positive angle means intersection if the vehicle continues forward
            float steerAngle = ((rightLaneAngle - leftLaneAngle)/2) * 4;//Gets the direction needed to steer then multiplies by 4 for full 360 wheel rotation
            log << getTime() << ": laneCorrection{speed: " << speed << " leftLaneAngle: " << leftLaneAngle << " rightLaneAngle: " << rightLaneAngle << " beingSteered: " << beingSteered << " Decision: " << "Steer " << steerAngle << "}";
            smm.receiveLog(log.str());
            vcm.laneCorrection(steerAngle);
            return;
        }

        void ForwardCollision(double time, double dist){

            if ( dist < 0 ){
                std::cout << "ERROR:  Distance is negative" << std::endl;
                return;
            }
            if ( dist  < 250 ){
                if ( dist  < 25 ){
                vcm.applyBrake(5);
            }
            else if ( dist  < 50 ){
                vcm.applyBrake(4);
            }
            else if ( dist  < 100 ){
                vcm.applyBrake(3);
            }
            else if ( dist  < 200 ){
                vcm.applyBrake(2);
            }
            else{
                vcm.applyBrake(1);
            }

            }
        }

        void trafficLightRecognition(string color, bool autoTrafficDetection) {
            // If the driver has this function disabled:
            if(!autoTrafficDetection) {
                cout << "Traffic Light Recognition is off" << endl;
                return; 
            }

            // using the camera, the type of signal displayed determines the action
            if (color == "green") {
                // continueOn()
                cout << "There is a GREEN traffic light." << endl;
                /*
                if obstacle detected {
                    comeToStop()
                    cout << "There is an obstacle blocking the intersection!"
                }
                */
            }
            else if (color == "yellow") {
                // slowDown()
                cout << "There is a YELLOW traffic light." << endl;
            }
            else if(color == "red") {
                // comeToStop()
                cout << "There is a RED traffic light." << endl;
            }
            else if (color == "unidentifiable") {
                // updateDisplay
                cout << "The signal is unidentifiable!" << endl;
            } 

            // if it reaches this, then there is no traffic light
            return;
        }

        void emergencyVehicleDetection(bool emergencyVehicleCamera1, bool emergencyVehicleCamera2) {
            // if either camera detects an active emergency vehicle,
            if(emergencyVehicleCamera1 || emergencyVehicleCamera2) {
                cout << "An Emergency Vehicle is Approaching!" << endl;
            }
            else {
                cout << "No Emergency Vehicle Present." << endl;
            }
        }

};

///////////////////// SENSOR FUSION /////////////////////

class SensorFusion{
    public:

        float forwardCollision1, forwardCollision2;
        float backCollision1, backCollision2;
        float lightSensor1, lightSensor2, lightSensor3, lightSensor4;
        bool cruiseControlButtonPressed;
        float accelerometer, breakStatus, gasPedal;
        float interiorThermometer, exteriorThermometer, desiredThermometer;
        bool autoTemperatureStatus, autoWiperStatus, autoTrafficDetection, driverSteering;
        float rainSensor, wiperStatus, steeringWheelStatus;
        string trafficCamera;
        float roadAngleCamera1, roadAngleCamera2;
        bool emergencyVehicleCamera1, emergencyVehicleCamera2, doorLockButtonPressed1, doorLockButtonPressed2, doorLockButtonPressed3, doorLockButtonPressed4;
        float time;

        float forwardCollision, backCollision, lightSensor;
        PlanningModule planningModule;


        void normalizeData(){
            if((forwardCollision1 == NULL || forwardCollision1 <0) ){
                if(forwardCollision2 != NULL && forwardCollision2 > 0){
                    forwardCollision1 = forwardCollision2;
                }
                else{
                    forwardCollision1 = 250;
                }
            }
            if((forwardCollision2 == NULL || forwardCollision2 <0) ){
                if(forwardCollision1 != NULL && forwardCollision1 > 0){
                    forwardCollision2 = forwardCollision1;
                }
                else{
                    forwardCollision2 = 250;
                }
            }
            if((backCollision1 == NULL || backCollision1 <0) ){
                if(backCollision2 != NULL && backCollision2 > 0){
                    backCollision1 = backCollision2;
                }
                else{
                    backCollision1 = 250;
                }
            }
            if((backCollision2 == NULL || backCollision2 <0) ){
                if(backCollision1 != NULL && backCollision1 > 0){
                    backCollision2 = backCollision1;
                }
                else{
                    backCollision2 = 250;
                }
            }


            forwardCollision = (forwardCollision1+forwardCollision2)/2;
            backCollision = (backCollision1+backCollision2)/2;
            lightSensor = (lightSensor1 + lightSensor2 + lightSensor3 + lightSensor4)/4;

            sendData();

        }

        void sendData(){
            planningModule.ReceiveData(time, forwardCollision,backCollision, lightSensor, accelerometer, breakStatus, gasPedal, interiorThermometer, exteriorThermometer, desiredThermometer, rainSensor, wiperStatus, steeringWheelStatus, roadAngleCamera1, roadAngleCamera2,trafficCamera, cruiseControlButtonPressed, autoTemperatureStatus, autoWiperStatus, autoTrafficDetection, driverSteering, emergencyVehicleCamera1, emergencyVehicleCamera2, doorLockButtonPressed1, doorLockButtonPressed2, doorLockButtonPressed3, doorLockButtonPressed4);
        }


};

///////////////////// VEHICLE CONTROL SYSTEM MODULE /////////////////////

class vehicleControlModule{
    public:
        void adjustWiperLevel(int wiperStatus, bool increaseWiper, bool decreaseWiper){
            if (increaseWiper) {
                wiperStatus++;
                std::cout << "Wiper level increased" << std::endl;
            }
            else if (decreaseWiper) {
                wiperStatus--;
                std::cout << "Wiper level decreased" << std::endl;
            }
            else {
                std::cout << "Wiper level stayed the same" << std::endl;
            }
        }

        void adjustTemperature(int internalTemperature, bool increaseTemperature, bool decreaseTemperature){
            if (increaseTemperature) {
                internalTemperature++;
                std::cout << "Temperature increased" << std::endl;
            }
            else if (decreaseTemperature) {
                internalTemperature--;
                std::cout << "Temperature decreased" << std::endl;
            }
            else {
                std::cout << "Temperature stayed the same" << std::endl;
            }
        }

        void adjustHeadlights(bool state){
            if (state){//Turns headlights on
                //headlightsState = true;
                std::cout << "Headlights on" << std::endl;
            }
            else{//Turns headlights off
                //headlightsState = false;
                std::cout << "Headlights off" << std::endl;
            }
        }


        void activateLocks(){   
            //door1 = locked;
            //door2 = locked;
            //door3 = locked;
            //door4 = locked;
            std::cout << "Doors locked" << std::endl;
        }


        void laneCorrection(float steeringAngle){
            //steeringWheelStatus = steeringAngle
            std::cout << "Steering changed to: " << steeringAngle << std::endl;
        }

        void applyBrake(int brakeLevel){
            //brakeStatus = brakeLevel;
            std::cout << "Brake level applied: " << brakeLevel << std::endl;
        }



};


///////////////////// SYSTEM MANAGEMENT MODULE /////////////////////

class systemManagementModule{
    static vector<string> sysLog;
    public: 
        void receiveLog(string entry){//Records the sent log of data
            sysLog.push_back(entry);
        }

        void displayLog(){//Displays the entire log one entry at a time
            for(int i = 0; i < sysLog.size(); i++){
                cout << sysLog[i] << endl;
            }
        }

};


 
///////////////////// TECHNICIAN INTERFACE /////////////////////

class technicianInterface{ /* Just printing all the data that is necessary*/
    public: 
        //a function showSystemLog()
        void showSystemLog(){
            std::cout << "System Log" << std::endl;
        }

        //a function checkSensorHealth(sensorList)
        void checkSensorHealth(std::string sensorList){
            std::cout << "Sensor Health" << std::endl;
        }

        //a function checkSoftwareHealth() shows if the there are any issues
        void checkSoftwareHealth(){
            std::cout << "Software Health" << std::endl;
        }

        //a function installUpdate() that just prints "Update currently up to date: " and the current time and date
        void installUpdate(){
            auto currentTime = std::chrono::system_clock::now();
            std::time_t time = std::chrono::system_clock::to_time_t(currentTime);
            std::cout << "Update currently up to date: " << std::ctime(&time) << std::endl;
        }

        //a function uploadLogToServer() that just prints "Log uploaded to server: " and the current time and date
        void uploadLogToServer(){
            auto currentTime = std::chrono::system_clock::now();
            std::time_t time = std::chrono::system_clock::to_time_t(currentTime);
            std::cout << "Log uploaded to server: " << std::ctime(&time) << std::endl;
        }
};



///////////////////// DRIVER INTERFACE /////////////////////

class driverInterface{ /* This is where we can create a function like if the password is equal then they can create a log output*/
    public: 
        //a function displaySpeed(speed)
        void displaySpeed(int speed){
            std::cout << "Speed: " << speed << std::endl;
        }

        //a function that toggles cruise control
        void toggleCruiseControl(bool cruiseControlStatus){
            if (cruiseControlStatus) {
                std::cout << "Cruise control is on" << std::endl;
            }
            else {
                std::cout << "Cruise control is off" << std::endl;
            }
        }

        //a function that shows the fuel level
        void displayFuelLevel(int fuelLevel){
            std::cout << "Fuel level: " << fuelLevel << std::endl;
        }

        //a function that shows the temperature
        void displayTemperature(int temperature){
            std::cout << "Temperature: " << temperature << std::endl;
        }

        //a function collisionAlert
        void collisionAlert(int collisionAlert){
            if (collisionAlert > 200){
                std::cout << "Collision Alert: " << collisionAlert << std::endl;
            } else {
                std::cout << "No collision detected" << std::endl;
            }
        }
};

class testingInterface{
    public:
        //test()
        void test(){
            std::cout << "Test" << std::endl;
        }

        //showSystemLog()
        void showSystemLog(){
            std::cout << "System Log" << std::endl;
        }
};



int main() {
    SensorFusion sensorFusion;
    sensorFusion.time = 0;
    PlanningModule planningModule;
    sensorFusion.planningModule = planningModule;
    string filename = "sensor_data.txt";
    ifstream file(filename);

    if (!file) {
        cerr << "Error: Cannot open file " << filename << endl;
        return 1;
    }

    vector<string> sensor_data;

    string line;

    while (getline(file, line)) {
        char *c = new char[line.length() + 1];
        std::copy(line.begin(), line.end(), c);
        c[line.length()] = '\0';
        string sensorName = strtok(c,",");
        string sensorValue = strtok(NULL, ",");


        switch(string sensorName){
            case "forwardCollision1":
                sensorFusion.forwardCollision1 = stof(sensorValue);
                break;
            case "forwardCollision2":
                sensorFusion.forwardCollision2 = stof(sensorValue);
                break;
            case "backCollision1":
                sensorFusion.backCollision1 = stof(sensorValue);
                break;
            case "backCollision2":
                sensorFusion.backCollision2 = stof(sensorValue);
                break;
            case "lightSensor1":
                sensorFusion.lightSensor1 = stof(sensorValue);
                break;
            case "lightSensor2":
                sensorFusion.lightSensor2 = stof(sensorValue);
                break;
            case "lightSensor3":
                sensorFusion.lightSensor3 = stof(sensorValue);
                break;
            case "lightSensor4":
                sensorFusion.lightSensor4 = stof(sensorValue);
                break;
            case "cruiseControlButtonPressed":
                if(strcmp(sensorValue,"true") == 0){
                    sensorFusion.cruiseControllButtonPressed = true;
                }
                else{
                    sensorFusion.cruiseControllButtonPressed = false;
                }
                break;
            case "accelerometer":
                sensorFusion.accelerometer = stof(sensorValue);
                break;
            case "breakStatus":
                sensorFusion.breakStatus = stof(sensorValue);
                break;
            case "gasPedal":
                sensorFusion.gasPedal = stof(sensorValue);
                break;
            case "intereriorThermometer":
                sensorFusion.interiorThermometer = stof(sensorValue);
                break;
            case "exteriorThermometer":
                sensorFusion.exteriorThermometer = stof(sensorValue);
                break;
            case "desiredThermometer":
                sensorFusion.desiredThermometer = stof(sensorValue);
                break;
            case "autoTemperatureStatus":
                if(strcmp(sensorValue,"true") == 0){
                    sensorFusion.autoTemperatureStatus = true;
                }
                else{
                    sensorFusion.autoTemperatureStatus = false;
                }
                break;
            case "rainSensor":
                sensorFusion.rainSensor = stof(sensorValue);
                break;
            case "wiperStatus":
                sensorFusion.wiperStatus = stof(sensorValue);
                break;
            case "autoWiperStatus":
                if(strcmp(sensorValue,"true") == 0){
                    sensorFusion.autoWiperStatus = true;
                }
                else{
                    sensorFusion.autoWiperStatus = false;
                }
                break;
            case "trafficCamera":
                sensorFusion.trafficCamera = sensorValue;
                break;
            case "autoTrafficDetection":
                if(strcmp(sensorValue,"true") == 0){
                    sensorFusion.autoTrafficDetection = true;
                }
                else{
                    sensorFusion.autoTrafficDetection = false;
                }
                break;
            case "driverSteering":
                if(strcmp(sensorValue,"true") == 0){
                    sensorFusion.driverSteering = true;
                }
                else{
                    sensorFusion.driverSteering = false;
                }
                break;
            case "steeringWheelStatus":
                sensorFusion.steeringWheelStatus = stof(sensorValue);
                break;
            case "roadAngleCamera1":
                sensorFusion.roadAngleCamera1 = stof(sensorValue);
                break;
            case "roadAngleCamera2":
                sensorFusion.roadAngleCamera2 = stof(sensorValue);
                break;
            case "emergencyVehicleCamera1":
                if(strcmp(sensorValue,"true") == 0){
                    sensorFusion.emergencyVehicleCamera1 = true;
                }
                else{
                    sensorFusion.emergencyVehicleCamera1 = false;
                }
                break;
            case "emergencyVehicleCamera2":
                if(strcmp(sensorValue,"true") == 0){
                    sensorFusion.emergencyVehicleCamera2 = true;
                }
                else{
                    sensorFusion.emergencyVehicleCamera2 = false;
                }
                break;
            case "doorLockButtonPressed1":
                if(strcmp(sensorValue,"true") == 0){
                    sensorFusion.doorLockButtonPressed1 = true;
                }
                else{
                    sensorFusion.doorLockButtonPressed1 = false;
                }
                break;
            case "doorLockButtonPressed2":
                if(strcmp(sensorValue,"true") == 0){
                    sensorFusion.doorLockButtonPressed2 = true;
                }
                else{
                    sensorFusion.doorLockButtonPressed2 = false;
                }
                break;
            case "doorLockButtonPressed3":
                if(strcmp(sensorValue,"true") == 0){
                    sensorFusion.doorLockButtonPressed3 = true;
                }
                else{
                    sensorFusion.doorLockButtonPressed3 = false;
                }
                break;
            case "doorLockButtonPressed4":
                if(strcmp(sensorValue,"true") == 0){
                    sensorFusion.doorLockButtonPressed4 = true;
                }
                else{
                    sensorFusion.doorLockButtonPressed4 = false;
                }


                sensorFusion.normalizeData;
                sensorFusion.sendData();
                sensorFusion.time += .05;
                break;
            
            default:
        }

        sensor_data.push_back(line);
    }

    file.close();

    // Print the sensor data
    for (string data : sensor_data) {
        cout << data << endl;
    }

    return 0;
}