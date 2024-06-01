#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <LiquidCrystal.h>
extern LiquidCrystal lcd;

struct Schedule {
  int hour;
  int minute;
  const char* activity;
};

const Schedule dailySchedule[] = {
  {6, 0, "Wake up & exercise"}, {7, 0, "Breakfast"}, {9, 0, "Work or study"},
  {12, 0, "Lunch break"}, {13, 0, "Work or study"}, {17, 0, "Dinner"},
  {18, 0, "Relax & hobbies"}, {21, 0, "Prepare for bed"}, {22, 0, "Go to sleep"}
};

const int scheduleSize = sizeof(dailySchedule) / sizeof(dailySchedule[0]);

void displayActivity(int currentHour, int currentMinute);

#endif
