/*
  ADXL3xx

  Reads an Analog Devices ADXL3xx accelerometer and communicates the
  acceleration to the computer. The pins used are designed to be easily
  compatible with the breakout boards from SparkFun, available from:
  http://www.sparkfun.com/commerce/categories.php?c=80

  The circuit:
  - analog 0: accelerometer self test
  - analog 1: z-axis
  - analog 2: y-axis
  - analog 3: x-axis
  - analog 4: ground
  - analog 5: vcc

*/
int scale = 3;
boolean micro_is_5V = true; 
 int a = 0;
 long Time;

// these constants describe the pins. They won't change:
const int groundpin = 18;             // analog input pin 4 -- ground
const int powerpin = 19;              // analog input pin 5 -- voltage
const int xpin = A3;                  // x-axis of the accelerometer
const int ypin = A2;                  // y-axis
const int zpin = A1;                  // z-axis (only on 3-axis models)

void setup() {
  // initialize the serial communications:
  Serial.begin(9600);

  // Provide ground and power by using the analog inputs as normal digital pins.
  // This makes it possible to directly connect the breakout board to the
  // Arduino. If you use the normal 5V and GND pins on the Arduino,
  // you can remove these lines.
  pinMode(groundpin, OUTPUT);
  pinMode(powerpin, OUTPUT);
  digitalWrite(groundpin, LOW);
  digitalWrite(powerpin, HIGH);
}

void loop() {
  int rawX = analogRead(A0);
  int rawY = analogRead(A1);
  int rawZ = analogRead(A2);
 float scaledX, scaledY, scaledZ; // Scaled values for each axis
  if (micro_is_5V) // microcontroller runs off 5V
  {
    scaledX = map(rawX, 0, 675, -scale, scale); // 3.3/5 * 1023 =~ 675
  }
  else // microcontroller runs off 3.3V
  {
    scaledX = map(rawX, 0, 1023, -scale, scale);
  }
  
  //Serial.print(" \n \n DO NOT MOVE TILL 6secs\n");
  int acc_int_x[100], acc_int_y[100], acc_int_z[100];

  

  //Serial.print("YOU MOVE NOW \n");
  
             

  int acc_x[200], acc_y[200], acc_z[200];
  long acc_mean_x=0L, acc_mean_y=0L, acc_mean_z=0L;
  for(int i=0;i<200;i++)
  {
    acc_x[i]=analogRead(xpin);
    acc_y[i]=analogRead(ypin);
    acc_z[i]=analogRead(zpin);

//    Serial.print(acc_x[i]);
//    Serial.print(" ");
//    Serial.print(acc_y[i]);
//    Serial.print(" ");
//    Serial.println(acc_z[i]);
  }

  
//  long ax = 0L, ay = 0L, az = 0L;
//   for(int i = 0; i<200; i++)
//   {
//    ax = ax+acc_x[i];
//    ay = ay+acc_y[i];
//    az = az+acc_z[i];
//    
//    } 
//    Serial.print(ax/200);
//    Serial.print(" ");
//    Serial.print(ay/200);
//    Serial.print(" ");
//    Serial.println(az/200);




    long sum_x=0L, sum1_x = 0L, variance_x;
    long sum_y=0L, sum1_y = 0L, variance_y;
    long sum_z=0L, sum1_z = 0L, variance_z;

    for (int i = 0; i < 200; i++)
    {
        sum_x = sum_x + acc_x[i];
        sum_y = sum_y + acc_y[i];
        sum_z = sum_z + acc_z[i];
    }
    long average_x = sum_x / 200;
    long average_y = sum_y / 200;
    long average_z = sum_z / 200;
    /*  Compute  variance  and standard deviation  */
    for (int i = 0; i < 200; i++)
    {
        sum1_x = sum1_x + pow((acc_x[i] - average_x), 2);
        sum1_y = sum1_y + pow((acc_y[i] - average_y), 2);
        sum1_z = sum1_z + pow((acc_z[i] - average_z), 2);
    }
    variance_x = sum1_x / 200;
    variance_y = sum1_y / 200;
    variance_z = sum1_z / 200;
    long std_deviation_x = sqrt(variance_x);
    long std_deviation_y = sqrt(variance_y);
    long std_deviation_z = sqrt(variance_z);
    Serial.println("deviation of x = ");
    Serial.print(variance_x);
    Serial.print(" ");
    //Serial.println("\n deviation of y = ");
    Serial.println(variance_y);
   // Serial.println("\n deviation of z = ");
   Serial.print(" ");
    Serial.println(variance_z);
    delay(500);

    long samp = variance_x + variance_y + variance_z;
//       Serial.print(" ");
//    Serial.print(samp);
  
   
    if(samp <= 3 )
    {
      a=1;
      
      Serial.println("sitting");
     
      }
      else if(samp>3 && samp<=6000 )
      {
        a=2;
        Serial.println("walking");
        }
        else if(samp>6000 )
        {
          a=3;
          Serial.println("running");
          }

    
}
