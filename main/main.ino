#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

struct Schedule {
  int hour;
  int minute;
  const char* activity;
};

Schedule dailySchedule[] = {
  {6, 0, "Wake up & exercise"},
  {7, 0, "Breakfast"},
  {9, 0, "Work or study"},
  {12, 0, "Lunch break"},
  {13, 2, "Work or study"},
  {17, 0, "Dinner"},
  {18, 0, "Relax & hobbies"},
  {21, 0, "Prepare for bed"},
  {22, 0, "Go to sleep"}
};

const int scheduleSize = sizeof(dailySchedule) / sizeof(dailySchedule[0]);

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.print("Waiting for time");
}

void loop() {
  if (Serial.available()) {
    String currentTime = "";
    while (Serial.available()) {
      char c = Serial.read();
      currentTime += c;
      delay(2);  // Small delay to ensure we get the complete string
    }

    // Parse the incoming time string
    int year = currentTime.substring(0, 4).toInt();
    int month = currentTime.substring(5, 7).toInt();
    int day = currentTime.substring(8, 10).toInt();
    int hour = currentTime.substring(11, 13).toInt();
    int minute = currentTime.substring(14, 16).toInt();
    int second = currentTime.substring(17, 19).toInt();

    // Display date and time
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(currentTime.substring(0, 10));  // Display date
    lcd.setCursor(0, 1);
    lcd.print(currentTime.substring(11));  // Display time

    // Check and display current activity
    displayActivity(hour, minute);
  }
  delay(1000);  // Update the display every second
}
void displayActivity(int currentHour, int currentMinute) {
  for (int i = 0; i < scheduleSize; i++) {
    if (currentHour == dailySchedule[i].hour && currentMinute == dailySchedule[i].minute) {
      lcd.clear();
      lcd.setCursor(0, 0);

      String activity = dailySchedule[i].activity;
      int maxLength = 16; // Number of characters per line on a 16x2 LCD
      int line = 0;

      for (int j = 0; j < activity.length(); j++) {
        if (j > 0 && j % maxLength == 0) {
          line++;
          lcd.setCursor(0, line); // Move to the next line
          if (line >= 2) break; // Stop if more than 2 lines
        }
        lcd.print(activity[j]);
      }
      lcd.setCursor(14,1);
      lcd.print(":)");

      delay(60000);  // Show activity for 1 minute
      lcd.clear();
      return;
    }
  }
}


