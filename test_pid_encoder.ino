#define DUONG 6
#define AM 7

int vitri = 0, vitrimm = 2400, error; 

int pid (float error, float kp, float ki, float kd)
{
  int derror;
  static int preerror = 0, ierror = 0;
  int temp;
  derror = error - preerror;
  ierror += error;
// Giới hạn giá trị của ierror

  preerror = error;
  temp = kp * error + ki * ierror + kd * derror;
  // Giới hạn giá trị của temp
  if(temp >= 255)
  {
    temp = 255;
  }
  if(temp <= -255)
  {
    temp = -255;
  }

  return temp;
}

void chay()
{
  if(digitalRead(4) == LOW)
    vitri++;
  else
    vitri--;
}

void quay(int nangluong)
{
  // Giới hạn giá trị của nangluong
  if(nangluong >= 255)
  {
    nangluong = 255;
  }
  if(nangluong <= -255)
  {
    nangluong = -255;
  }

  if (nangluong > 0)
  {
    analogWrite(DUONG, nangluong);
    analogWrite(AM, 0);
  }
  else if (nangluong < 0)
  {
    analogWrite(DUONG, 0);
    analogWrite(AM, -nangluong); // Đảm bảo giá trị luôn dương
  }
  else
  {
    analogWrite(DUONG, 0);
    analogWrite(AM, 0); // Dừng động cơ
  }
}

void setup() {
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), chay, RISING); // Đảm bảo chân đúng
  Serial.begin(9600);
}

void loop() {
  Serial.println(vitri);
  error = vitrimm - vitri;
  quay(pid(error,0.228 ,0.089 ,0)); // Điều chỉnh hệ số PID theo nhu cầu
  //delay(100); // Thêm delay để tránh quá tải điều khiển
}
