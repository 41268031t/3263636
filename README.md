# 91399472X 王冠群 41268031T 學士班二年級陳廷恩
這段程式使用 可變電阻（potentiometer） 控制 LED 亮度，同時監測 光敏電阻（LDR） 和 水銀開關（Mercury Switch），並根據水銀開關的狀態來控制 伺服馬達（Servo Motor） 的角度。以下是逐行解析：

1. 引入函式庫

#include <Servo.h>

說明：引入 Arduino 內建的 Servo 函式庫，用來控制伺服馬達的角度。

2. 定義常數（接腳配置）

const int potPin = A0;  // 可變電阻
const int ledPin = 9;   // LED
const int ldrPin = A1;  // 光敏電阻
const int mercuryPin = 2; // 水銀開關
const int servoPin = 5;  // 伺服馬達

說明：
 • potPin (A0) → 接可變電阻（滑動變阻器），用來調整 LED 亮度和伺服馬達角度。
 • ledPin (9) → LED 燈腳位，使用 PWM 控制亮度。
 • ldrPin (A1) → 光敏電阻（LDR），讀取環境光強度，但程式中未使用。
 • mercuryPin (2) → 水銀開關，用來偵測裝置的傾斜狀態（0 = 傾斜，1 = 正常）。
 • servoPin (5) → 伺服馬達控制腳。

3. 創建伺服物件

Servo myServo;

說明：建立 myServo 物件，以便後續使用 .attach() 和 .write() 來控制伺服馬達。

4. setup() 設定 Arduino 初始化

void setup() {
  pinMode(ledPin, OUTPUT);            // 設定 LED 為輸出模式
  pinMode(mercuryPin, INPUT_PULLUP);  // 設定水銀開關為輸入模式，並啟用內部上拉電阻
  myServo.attach(servoPin);           // 讓伺服馬達的訊號腳（5號腳）與程式連結
  Serial.begin(9600);                 // 啟動序列監視器，波特率設定為 9600
}

說明：
 1. pinMode(ledPin, OUTPUT); → 設定 LED 為輸出模式。
 2. pinMode(mercuryPin, INPUT_PULLUP); → 設定 水銀開關為輸入模式，並啟用內部上拉電阻（這樣當開關未傾斜時，會讀到 1）。
 3. myServo.attach(servoPin); → 讓伺服馬達與 servoPin 連結，準備開始控制馬達角度。
 4. Serial.begin(9600); → 啟動 序列監視器，用於在電腦端顯示程式運行的數據。

5. loop() 主要運行邏輯

void loop() {
  int potValue = analogRead(potPin);

說明：
 • analogRead(potPin); 讀取 可變電阻的數值（0~1023），用來控制 LED 亮度與伺服馬達角度。

6. 調整 LED 亮度

  int brightness = map(potValue, 0, 1023, 0, 255);
  analogWrite(ledPin, brightness);

說明：
 1. map(potValue, 0, 1023, 0, 255);
 • 將 可變電阻讀取的範圍（01023）對應到 PWM 亮度範圍（0255）。
 • potValue = 0 → LED 最暗（0% 亮度）。
 • potValue = 1023 → LED 最亮（100% 亮度）。
 2. analogWrite(ledPin, brightness);
 • 使用 PWM 技術 調整 LED 亮度。

7. 讀取光敏電阻與水銀開關狀態

  int ldrValue = analogRead(ldrPin);
  int mercuryState = digitalRead(mercuryPin); // 0 = 傾斜, 1 = 正常

說明：
 1. analogRead(ldrPin); → 讀取 光敏電阻數值（0~1023），但程式中未使用這個數據來控制其他元件。
 2. digitalRead(mercuryPin); → 讀取 水銀開關狀態：
 • 0 → 傾斜（水銀導通）。
 • 1 → 正常（水銀未導通）。

8. 計算伺服馬達角度

  int servoAngle = map(potValue, 0, 1023, 0, 180);

說明：
 • map(potValue, 0, 1023, 0, 180);
 • 將 可變電阻範圍（01023）對應到伺服馬達角度範圍（0180 度）。
 • potValue = 0 → 伺服角度 = 0°。
 • potValue = 1023 → 伺服角度 = 180°。

9. 控制伺服馬達

  if (mercuryState == 0) {
    myServo.write(180);
  } else {
    myServo.write(servoAngle);
  }

說明：
 • 如果水銀開關傾斜 (mercuryState == 0)：
 • 強制讓伺服馬達轉到 180 度（無論可變電阻的值是多少）。
 • 如果水銀開關正常 (mercuryState == 1)：
 • 伺服馬達角度依照 可變電阻的值來調整。

10. 顯示序列監視器輸出

  Serial.print(brightness);
  Serial.print(",");
  Serial.print(ldrValue);
  Serial.print(",");
  Serial.print(mercuryState);
  Serial.print(",");
  Serial.println(servoAngle);

說明：
 • 將 brightness、ldrValue、mercuryState、servoAngle 這些變數的數值印到 序列監視器，方便除錯。
 • 使用 "," 讓數據以 逗號分隔，便於 Excel 或其他程式解析。

11. 稍作延遲

  delay(50);
}

說明：
 • 讓程式稍微延遲 50ms，避免讀取數值過快，導致 LED 亮度或伺服馬達抖動。

程式總結
 1. 可變電阻控制 LED 亮度（01023 → 0255）。
 2. 可變電阻控制伺服馬達角度（01023 → 0180°）。
 3. 水銀開關決定伺服馬達是否強制轉到 180°。
 4. 光敏電阻的數值被讀取，但程式未使用它來控制元件（可作未來擴充）。
 5. 序列監視器輸出所有感測數據，方便監測裝置狀態。
