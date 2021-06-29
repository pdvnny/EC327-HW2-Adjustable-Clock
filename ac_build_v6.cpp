// Copyright 2021 Parker Dunn pgdunn@bu.edu
// Alternate: parker_dunn@outlook.com & pdunn91@gmail.com
// Originated Jun 7, 2021

// Developed for EC327 at Boston University
// HW2 - Use SFML library to create an analog and digital clock graphic

#include <chrono>
#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>  // SFML: https://www.sfml-dev.org
#include <string>
#include <thread>
#include <vector>

using std::cout;
using std::string;
using std::stoi;
using std::to_string;
using std::vector;



// TO DO
// -- Incorporate shapes for the clock in the script
// -- Move the shapes over time
// -- Sync shape movement with clock

// PROBLEMS
// -- Need to figure out how to make adjustments to ascii time!!!
// -- Not sure what happens if no argument is entered in Terminal!


// Duplicated from EC327 lecture material | Returns a highly accurate time
double besttime() {
  auto now = std::chrono::high_resolution_clock::now();
  auto dur = now.time_since_epoch();
  return dur.count()/1'000'000'000.0;
}

// This function should modify a time_t time value then convert it to a tm structure
std::tm time_adjust(time_t time, int adjust) {
  time += adjust;
  return *localtime(&time);
}


int main(int argc, char **argv) {

  string display_time;

  // Professor said this does not need error-checking
  int clock_adjust = stoi(argv[1]);

  // Building a SFML window
  sf::RenderWindow window(sf::VideoMode(200,200), "pgdunn@bu.edu");

  // Setting up text in the window
  sf::Text digital_time;
  sf::Font output_font;
  output_font.loadFromFile("/usr/share/fonts/truetype/tlwg/TlwgTypewriter-Bold.ttf");
  digital_time.setFont(output_font);
  digital_time.setFillColor(sf::Color::White);
  digital_time.setOutlineColor(sf::Color::Red);
  digital_time.setOutlineThickness(1);
  digital_time.setCharacterSize(15);
  digital_time.setPosition(25, 5);

  // Setting a frame rate limit
  window.setFramerateLimit(60); // 60 fps

  while (window.isOpen()) {

    
    // check for window close
    sf::Event window_activity;
    while (window.pollEvent(window_activity)) {
      if (window_activity.type == sf::Event::Closed)
        window.close();
    }

    // All operations for getting the time - Multiple formats copied from class example.
    // Haven't had to examine how to best use them all
    std::time_t time = std::time(NULL);       // time gets the current time; returns value of type time_t
    // std::tm now = *std::localtime(&time);     // localtime() converts time_t object to a tm structure

    // two time objects that I need to use
    std::tm adjusted_time;
    double accurate_time = besttime(); // see above "besttime" for info on this



    // Only displaying new time in the first 25% of the second - REQUIREMENT of assignment
    if ((accurate_time -  (int)accurate_time) < 0.25) {
    
      adjusted_time = time_adjust(time, clock_adjust);
      display_time = std::asctime(&adjusted_time);

      // Terminal modifications
      cout << display_time << "\n";

      // Window modifications
    
      window.clear();
      digital_time.setString(display_time.substr(11,8));
      window.draw(digital_time);
      
      // modifications to analog clock here
      cout << "Checking on these values: " << adjusted_time.tm_hour << " : "
           << adjusted_time.tm_min << " : " << adjusted_time.tm_hour;

      
      cout << "Angle calculations:"
           << "Hour - " << (adjusted_time.tm_hour) % 12
           << " | Minutes - " << (adjusted_time.tm_min) % 60
           << " | Seconds - " << (adjusted_time.tm_sec) % 60;

      window.display();


      std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

  }
  cout << "\n";
  return 0;
}