const int analogIn = A0;
int mVperAmp = 528; // use 100 for 20A Module and 66 for 30A Module
int RawValue = 0;
float ACSoffset = 450;
double Voltage = 0;
double Amps = 0;

// Define the number of samples to keep track of.  The higher the number,
// the more the readings will be smoothed, but the slower the output will
// respond to the input.  Using a constant rather than a normal variable lets
// use this value to determine the size of the readings array.

const int numReadings = 100;

int readings[numReadings];      // the readings from the analog input
int index = 0;                  // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

void setup()
{
  Serial.begin(115200);
  Serial.println("Alex Current Meter Test");
  
  
  
  // initialize all the readings to 0: 
  for (int thisReading = 0; thisReading < numReadings; thisReading++)
  readings[thisReading] = 0;   
}

void loop()
{
  
  // subtract the last reading:
  total= total - readings[index];         
  // read from the sensor:  
  readings[index] = analogRead(analogIn); 
  // add the reading to the total:
  total= total + readings[index];       
  // advance to the next position in the array:  
  index = index + 1;                    

  // if we're at the end of the array...
  if (index >= numReadings)              
  // ...wrap around to the beginning: 
  index = 0;                           

  // calculate the average:
  average = total / numReadings;         
    
  RawValue = average;
  
  Voltage = (RawValue / 1023.0) * 5000; // convertaveraged raw value to mV 
  Amps = ((Voltage - ACSoffset)/ mVperAmp);

  Serial.print("Raw Value = " ); // shows pre-scaled value
  Serial.print(RawValue);
  Serial.print("\t mV = "); // shows the voltage measured
  Serial.print(Voltage, 3); // Display 3 digits after decimal point
  Serial.print("\t Amps = "); // shows the voltage measured
  Serial.println(Amps, 3); // Display 3 digits after decimal point
  delay(0);

 
}
