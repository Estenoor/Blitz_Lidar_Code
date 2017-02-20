//Defining Pins for SoftI2C to work
#define SCL_PIN 3      //Define I2C Clock Pin as 11
#define SCL_PORT PORTB
#define SDA_PIN 2      //Define I2C Data Pin as 10
#define SDA_PORT PORTB
#define I2C_TIMEOUT 1000 //Set the timeout  
#define I2C_FASTMODE 1

//Include Files
#include <Servo.h>
#include <Wire.h>
#include "SoftI2CMaster.h"
#include "SoftWire.h"

//Class Declarations
Servo servo;
SoftWire lidar = SoftWire();

//Define Array Locations
#define highArray 0
#define lowArray 1
#define MAX_BYTES_RECEIVED 4

//Byte Declarations
byte lidarData[2][37];
byte dataToSend[74];
byte readData[2];

//Integer Declarations
int lidarSerial[37];
int commandReceiver[4];
int arrayPointer = 0;

//Double Declarations
double degree = 45;

void setup()
{
  //Servo Setup Code
  servo.attach(9);
  servo.write(degree);

  //SoftI2C Setup Code
  lidar.begin();

  //Normal I2C Setup Code
  Wire.begin(0x73); //This makes the arduino an i2c slave device with an address of 0x73
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);

  //Serial Debug Code
  Serial.begin(19200);
  Serial.println("> Lidar Starting...");
  Serial.print("> Servo Starting At: ");
  Serial.println(degree);
}

void loop()
{
  lidarServo(0x00, 0x8f, readData, true, 0x62);
}

void receiveEvent()
{
  for (int x; x < Wire.available(); x++)
  {
    if (x < MAX_BYTES_RECEIVED)
    {
      commandReceiver[x] = Wire.read();
    }
    else
    {
      Wire.read();
    }
  }
}

void requestEvent()
{
  if (commandReceiver[0] == 0x01)
  {
    sendAllData();
  }
  else if (commandReceiver[0] == 0x02)
  {
    sendAngleData(&commandReceiver[1]);
  }
}

void sendAngleData(int anglePointer)
{
  int z = ((anglePointer * 2) - 2); //This finds the position that the arduino should start writing from for the position
  for (int x = z; x < 2; x++)
  {
    Wire.write(dataToSend[x]);
  }
}

void sendAllData()
{
  if (arrayPointer == 0) //Send Bytes 0-9
  {
    for (int z = 0; z < 10; z++)
    {
      Wire.write(dataToSend[z]);
    }
    arrayPointer += 10;
    Serial.println("> Request 1");
    return;
  }

  else if (arrayPointer == 10) //Send Bytes 10-19
  {
    for (int z = 10; z < 20; z++)
    {
      Wire.write(dataToSend[z]);
    }
    arrayPointer += 10;
    Serial.println("> Request 2");
    return;
  }

  else if (arrayPointer == 20) //Send Bytes 20-29
  {
    for (int z = 20; z < 30; z++)
    {
      Wire.write(dataToSend[z]);
    }
    arrayPointer += 10;
    Serial.println("> Request 3");
    return;
  }

  else if (arrayPointer == 30) //Send Bytes 30-39
  {
    for (int z = 30; z < 40; z++)
    {
      Wire.write(dataToSend[z]);
    }
    arrayPointer += 10;
    Serial.println("> Request 4");
    return;
  }

  else if (arrayPointer == 40) //Send Bytes 40-49
  {
    for (int z = 40; z < 50; z++)
    {
      Wire.write(dataToSend[z]);
    }
    arrayPointer += 10;
    Serial.println("> Request 5");
    return;
  }

  else if (arrayPointer == 50) //Send Bytes 50-59
  {
    for (int z = 40; z < 50; z++)
    {
      Wire.write(dataToSend[z]);
    }
    arrayPointer += 10;
    Serial.println("> Request 6");
    return;
  }

  else if (arrayPointer == 60) //Send Bytes 60-69
  {
    for (int z = 50; z < 60; z++)
    {
      Wire.write(dataToSend[z]);
    }
    arrayPointer += 10;
    Serial.println("> Request 7");
    return;
  }

  else if (arrayPointer == 70) //Send Bytes 70-73
  {
    for (int z = 70; z < 84; z++)
    {
      Wire.write(dataToSend[z]);
    }
    arrayPointer = 0;
    Serial.println("> Request 8");
    return;
  }
}

//This Function runs the servo and grabs the lidar data while placing it in an array
void lidarServo(char writeAdress, char readAddress, byte dataArray[2], bool moniterBusy, char lidarliteAddress)
{
  int x = 0;
  int z = 0;
  int a = 1;

  for (degree = 45; degree < 135; degree += 2.5)
  {
    Lidarwrite(writeAdress, 0x04, lidarliteAddress);
    Lidarread(readAddress, 2, dataArray, moniterBusy, lidarliteAddress);
    dataToSend[z] = readData[0];
    dataToSend[a] = readData[1];
    lidarData[highArray][x] = readData[0];
    lidarData[lowArray][x] = readData[1];
    lidarSerial[x] = ((lidarData[highArray][x] * 256) + lidarData[lowArray][x]);
    //Serial.println(lidarSerial[x]);
    int lengthofBusy = Lidarbusy(lidarliteAddress);
    servo.write(degree);
    x++;
    z += 2;
    a += 2;
    delay(5);
  }

  int y = 0;
  for (degree = 135; degree > 45; degree -= 2.5)
  {
    Lidarwrite(writeAdress, 0x04, lidarliteAddress);
    Lidarread(readAddress, 2, readData, moniterBusy, lidarliteAddress);
    dataToSend[z] = readData[0];
    dataToSend[a] = readData[1];
    lidarData[highArray][x] = readData[0];
    lidarData[lowArray][x] = readData[1];
    lidarSerial[x] = ((lidarData[highArray][x] * 256) + lidarData[lowArray][x]);
    //Serial.println(lidarSerial[y]);
    int lengthofBusy = Lidarbusy(lidarliteAddress);
    servo.write(degree);
    x--;
    y++;
    z -= 2;
    a -= 2;
    delay(5);
  }
}

//This Function Tells if the lidar is busy. It returns the time it takes the lidar to respond in miliseconds
int Lidarbusy(char lidarliteAddress)
{
  int busyFlag = 1; // busyFlag monitors when the device is done with a measurement
  int busyCounter = 0; // busyCounter counts number of times busy flag is checked, for timeout

  while (busyFlag != 0) // Loop until device is not busy
  {
    // Read status register to check busy flag
    lidar.beginTransmission((int)lidarliteAddress);
    lidar.write(0x01); // Set the status register to be read

    // A nack means the device is not responding, report the error over serial
    int nackCatcher = lidar.endTransmission();
    if (nackCatcher != 0)
    {
      Serial.println("> nack");
    }

    lidar.requestFrom((int)lidarliteAddress, 1); // Read register 0x01
    busyFlag = bitRead(lidar.read(), 0); // Assign the LSB of the status register to busyFlag

    busyCounter++; // Increment busyCounter for timeout

    // Handle timeout condition, exit while loop and goto bailout
    if (busyCounter > 9999)
    {
      Serial.println("> Lidar Busy");
    }
  }
  return busyCounter;
}

//This Function sends information to the LidarLiteV3 through I2C
void Lidarwrite(char myAddress, char myValue, char lidarliteAddress)
{
  lidar.beginTransmission((int)lidarliteAddress);
  lidar.write((int)myAddress); // Set register for write
  lidar.write((int)myValue); // Write myValue to register

  // A nack means the device is not responding, report the error over serial
  int nackCatcher = lidar.endTransmission();
  if (nackCatcher != 0)
  {
    Serial.println("> nack");
  }

  delay(1); // 1 ms delay for robustness with successive reads and writes
} /* LIDARLite::write */


//This Function reads what the LidarLiteV3 sends on the I2C Bus after a request was sent
void Lidarread(char myAddress, int numOfBytes, byte arrayToSave[2], bool monitorBusyFlag, char lidarliteAddress)
{
  int busyFlag = 0; // busyFlag monitors when the device is done with a measurement
  if (monitorBusyFlag)
  {
    busyFlag = 1; // Begin read immediately if not monitoring busy flag
  }
  int busyCounter = 0; // busyCounter counts number of times busy flag is checked, for timeout

  while (busyFlag != 0) // Loop until device is not busy
  {
    // Read status register to check busy flag
    lidar.beginTransmission((int)lidarliteAddress);
    lidar.write(0x01); // Set the status register to be read

    // A nack means the device is not responding, report the error over serial
    int nackCatcher = lidar.endTransmission();
    if (nackCatcher != 0)
    {
      Serial.println("> nack");
    }

    lidar.requestFrom((int)lidarliteAddress, 1); // Read register 0x01
    busyFlag = bitRead(lidar.read(), 0); // Assign the LSB of the status register to busyFlag

    busyCounter++; // Increment busyCounter for timeout

    // Handle timeout condition, exit while loop and goto bailout
    if (busyCounter > 9999)
    {
      goto bailout;
    }
  }

  // Device is not busy, begin read
  if (busyFlag == 0)
  {
    lidar.beginTransmission((int)lidarliteAddress);
    lidar.write((int)myAddress); // Set the register to be read

    // A nack means the device is not responding, report the error over serial
    int nackCatcher = lidar.endTransmission();
    if (nackCatcher != 0)
    {
      Serial.println("> nack");
    }

    // Perform read of 1 or 2 bytes, save in arrayToSave
    lidar.requestFrom((int)lidarliteAddress, numOfBytes);
    int i = 0;
    if (numOfBytes <= lidar.available())
    {
      while (i < numOfBytes)
      {
        arrayToSave[i] = lidar.read();
        i++;
      }
    }
  }

  // bailout reports error over serial
  if (busyCounter > 9999)
  {
bailout:
    busyCounter = 0;
    Serial.println("> read failed");
  }
} /* LIDARLite::read */

