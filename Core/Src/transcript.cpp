#include "../Inc/transcript.hpp"

#include <ctime>

using namespace std;

void Transcript::updatePrint_date() {
  time_t rawtime;
  struct tm *timeinfo;
  string buffer;
  char temp[100];

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(temp, 100, "%d %B %Y\n", timeinfo);
  buffer.append(temp);
  strftime(temp, 100, "%X", timeinfo);
  buffer.append(temp);

  print_date = buffer;
}