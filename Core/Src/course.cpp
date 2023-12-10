#include "../Inc/course.hpp"

float Course::find_decimal_place_grade() const {
  float decimal_place = 0.;
  if (grade.size() == 2) {
    switch (grade[1]) {
      case '+':
        decimal_place = 0.3;
        break;
      case '-':
        decimal_place = -0.3;
        break;
    }
  }
  return decimal_place;
}