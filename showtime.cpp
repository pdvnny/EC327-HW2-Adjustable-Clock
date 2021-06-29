// Copyright 2021 J Carruthers jbc@bu.edu
//
// Accessing time in C++
//
#include <iostream>
#include <chrono>
#include <ctime>
using std::cout;


double besttime() {
  auto now = std::chrono::high_resolution_clock::now();
  auto dur = now.time_since_epoch();
  return dur.count()/1'000'000'000.0;
}

int main() {
  std::cout.precision(18);

  for (int i=0; i<10; i++) {
    double accurate_time = besttime();
    std::time_t time = std::time(NULL);          //reading the time (in seconds) time_t is a 64 bit integer  
    std::tm now = *std::localtime(&time);       // data structure that has the pieces of the time
        // std::tm  === "time structure"

    cout << "\n" << time  << " " << accurate_time << "\n";
    cout << std::asctime(&now);                           // passing address of data structure "now"
    cout << "year: " << 1900+ now.tm_year << "\n";
    cout << "mon: " << now.tm_mon << "\n";
    cout << "day: " << now.tm_mday  << "\n";
    cout << "hour: " << now.tm_hour  << "\n";
    cout << "min: " << now.tm_min  << "\n";
    cout << "sec: " << now.tm_sec  << "\n";
  }
}