#include <Wire.h> //thư viện I2c của Arduino, do PCA9685 sử dụng chuẩn giao tiếp i2c nên thư viện này bắt buộc phải khai báo 
#include <Adafruit_PWMServoDriver.h> // thư viện PCA9685

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
//Khai báo thư viện cho tay cầm
#include <PS2X_lib.h> // Khai báo thư viện
//Định nghĩa các chân điều khiển 
#define PS2_DAT 12 // MISO 
#define PS2_CMD 13 // MOSI 
#define PS2_SEL 15 // SS 
#define PS2_CLK 14 // SLK
//Khởi tạo class của thư viện
PS2X ps2x; // khởi tạo class PS2x
void setup() {
  //Khởi tạo Serial monitor với tốc độ 115200
  Serial.begin(115200);

  //Kết nối với tay cầm bằng hàm ps2x.config_gamepad, thử kết nối lại trong vòng 10 lần nếu quá 10 lần không kết nối được với tay cầm thì sẽ dừng lại

  int error = -1; 
  for (int i = 0; i < 10; i++) // thử kết nối với tay cầm ps2 trong 10 lần 
  {
    delay(1000); // đợi 1 giây 
    // cài đặt chân và các chế độ: GamePad
    error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, true ,true ); 
    Serial.print("."); 
    if(!error) //kiểm tra nếu tay cầm đã kết nối thành công 
	    break; // thoát khỏi vòng lặp 
  } 
  pwm.begin(); //khởi tạo PCA9685 
  pwm.setOscillatorFrequency(27000000); // cài đặt tần số dao động 
  pwm.setPWMFreq(50);// cài đặt tần số PWM. Tần số PWM có thể được cài đặt trong khoảng 24-1600 HZ, tần số này được cài đặt tùy thuộc vào nhu cầu xử dụng. Để điều khiển được cả servo và động cơ DC cùng nhau, tần số PWM điều khiển được cài đặt trong khoảng 50-60Hz.
  Wire.setClock(400000); // cài đặt tốc độ giao tiếp i2c ở tốc độ cao nhất(400 Mhz). Hàm này có thể bỏ qua nếu gặp lỗi hoặc không có nhu cầu tử dụng I2c tốc độ cao
}

void loop() {
 if (ps2x.Button(PSB_PAD_UP)) // đi thẳng
  { 
    pwm.setPWM(8, 0, 2730 ); //chân số 8 set chiều dương (motor 1 banh trai)
    pwm.setPWM(9, 0, 0);    //chân số 9 set chiều âm (motor 1 banh trai )
    pwm.setPWM(10, 0, 2730); //chân số 8 set chiều dương (motor 2 banh phai)
    pwm.setPWM(11, 0, 0);    //chân số 9 set chiều âm (motor 2 banh phai)
  }
  else{
    pwm.setPWM(8, 0, 0);
    pwm.setPWM(9, 0, 0); 
    pwm.setPWM(10, 0, 0);
    pwm.setPWM(11, 0, 0); 
  }
  if (ps2x.Button(PSB_PAD_DOWN)) // đi lùi
  { 
    pwm.setPWM(8, 0, 0); //chân số 8 set chiều dương (motor 1 banh trai)
    pwm.setPWM(9, 0, 2730);    //chân số 9 set chiều âm (motor 1 banh trai )
    pwm.setPWM(10, 0, 0); //chân số 8 set chiều dương (motor 2 banh phai)
    pwm.setPWM(11, 0, 2730);    //chân số 9 set chiều âm (motor 2 banh phai )
  } 
  else{
    pwm.setPWM(8, 0, 0);
    pwm.setPWM(9, 0, 0); 
    pwm.setPWM(10, 0, 0);
    pwm.setPWM(11, 0, 0); 
  }
   if (ps2x.Button(PSB_PAD_LEFT)) // quay trái
  { 
    pwm.setPWM(8, 0, 0); //chân số 8 set chiều dương (motor 1 banh trai)
    pwm.setPWM(9, 0, 2730);    //chân số 9 set chiều âm (motor 1 banh trai )
    pwm.setPWM(10, 0, 2730); //chân số 8 set chiều dương (motor 2 banh phai)
    pwm.setPWM(11, 0, 0);    //chân số 9 set chiều âm (motor 2 banh phai )
  } 
  else{
    pwm.setPWM(8, 0, 0);
    pwm.setPWM(9, 0, 0); 
    pwm.setPWM(10, 0, 0);
    pwm.setPWM(11, 0, 0); 
  }
  if (ps2x.Button(PSB_PAD_RIGHT)) // quay phải
  { 
    pwm.setPWM(8, 0, 2730); //chân số 8 set chiều dương (motor 1 banh trai)
    pwm.setPWM(9, 0, 0);    //chân số 9 set chiều âm (motor 1 banh trai )
    pwm.setPWM(10, 0, 0); //chân số 8 set chiều dương (motor 2 banh phai)
    pwm.setPWM(11, 0, 2730);    //chân số 9 set chiều âm (motor 2 banh phai )
  } 
  else{
    pwm.setPWM(8, 0, 0);
    pwm.setPWM(9, 0, 0); 
    pwm.setPWM(10, 0, 0);
    pwm.setPWM(11, 0, 0); 
  }
  if (ps2x.Button(PSB_GREEN)) // lấy bóng và cánh quạt ấn nút xanh lá hình tam giác
  { 
    pwm.setPWM(12, 0, 2730); //chân số 12 set chiều dương (INTAKE)
    pwm.setPWM(13, 0, 0);    //chân số 13 set chiều âm (INTAKE)
    pwm.setPWM(14, 0, 2730); //chân số 14 set chiều dương (cánh quạt)
    pwm.setPWM(15, 0, 0);    //chân số 15 set chiều âm (cánh quạt)
  }  
  else{
    pwm.setPWM(12, 0, 0);
    pwm.setPWM(13, 0, 0); 
    pwm.setPWM(14, 0, 0);
    pwm.setPWM(15, 0, 0); 
  }
 if (ps2x.Button(PSB_BLUE)) // thả bóng và cánh quạt ấn nút xanh biển hình X
  { 
    pwm.setPWM(12, 0, 0); //chân số 12 set chiều dương (INTAKE)
    pwm.setPWM(13, 0, 2730);    //chân số 13 set chiều âm (INTAKE)
    pwm.setPWM(14, 0, 2730); //chân số 14 set chiều dương (cánh quạt)
    pwm.setPWM(15, 0, 0);    //chân số 15 set chiều âm (cánh quạt)
  }  
  else{
    pwm.setPWM(12, 0, 0);
    pwm.setPWM(13, 0, 0); 
    pwm.setPWM(14, 0, 0);
    pwm.setPWM(15, 0, 0); 
  }
  if (ps2x.Button(PSB_PINK)) // mở cửa servo ấn nút hồng hình Vuông
  { 
    pwm.setPWM(2, 0, 410);//set góc servo = 180 độ (mở cửa)
  }  
  else{
    pwm.setPWM(2, 0, 0);//set góc servo = 0 độ (đóng cửa)
  }
}