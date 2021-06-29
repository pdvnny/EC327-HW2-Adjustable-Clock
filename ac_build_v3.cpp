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
// -- Make time to script (review HW2 details to figure out format)
// -- Create function "mod_time" - uses input arg to modify time
// -- Incorporate shapes for the clock in the script
// -- Move the shapes over time
// -- Sync shape movement with clock

// PROBLEMS


// Duplicated from EC327 lecture material | Returns a highly accurate time
double besttime() {
  auto now = std::chrono::high_resolution_clock::now();
  auto dur = now.time_since_epoch();
  return dur.count()/1'000'000'000.0;
}


// vector<int> time_adjust(double time, int adjust) {
  
//   ** Not read for this yet ... need to get more done first
//   ** Basically need to do baseconvert in base 60 here though!

//   need to remove extra days first like we need the time since 

// }



string format_digital_clock(vector<int>* time_vec) {
  vector<string> dig_time(3,"00");
  for (int i = 0; i < (*time_vec).size(); i++) {
    if ((*time_vec).at(i) < 10) {
      dig_time.at(i) = ("0" + to_string((*time_vec).at(i)));
    } else {
      dig_time.at(i) = to_string((*time_vec).at(i));
    }
  }

  return (dig_time.at(0) + ":" + dig_time.at(1) + ":" + dig_time.at(2));
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

    // All operations for getting the time
    
    // Time for terminal output
    std::time_t time = std::time(NULL);
    std::tm now = *std::localtime(&time);
    auto ascii_time = std::asctime(&now);
    double accurate_time = besttime();

    // Only displaying new time in the first 25% of the second
    if ((accurate_time -  (int)accurate_time) < 0.25) {
      
      // Get time to manipulate
      vector<int> time_vec(3,0);
      time_vec.at(0) = now.tm_hour;
      time_vec.at(1) = now.tm_min;
      time_vec.at(2) = now.tm_sec;
      
      // time_adjust(&time_vec, 0); // 0 will eventually become the time adjustment

      // Terminal modifications
      cout << ascii_time;

      // Window modifications
    
      window.clear();
      display_time = format_digital_clock(&time_vec);
      digital_time.setString(display_time);
      window.draw(digital_time);
      
      // modifications to analog clock here

      window.display();


      std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

  }
  cout << "\n";
  return 0;
}