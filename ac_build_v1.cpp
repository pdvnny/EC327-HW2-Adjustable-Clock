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

/* Wanted to work on the function to adjust the time but not compile yet

vector<int> clock_adjust() {
  
  ** Not read for this yet ... need to get more done first
  ** Basically need to do baseconvert in base 60 here though!

}


*/

int main(int argc, char **argv) {

  // Professor said this does not need error-checking
  int clock_adjust = stoi(argv[1]);

  // REMOVE LATER
  std::cout.precision(18);

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
    std::time_t time = std::time(NULL);  // returns time (in sec) as a 64-bit int and stores in time_t structure
    std::tm now = *std::localtime(&time);
    auto ascii_time = std::asctime(&now);    // formats time that "now" points to?
    // Accurate time
    double accurate_time = besttime();

    // Only displaying new time in the first 25% of the second
    while ((besttime() -  (int)besttime()) < 0.25) {
    
      // Terminal modifications
      cout << accurate_time << "  -  " << ascii_time;
      std::this_thread::sleep_for(std::chrono::milliseconds(250));

    }
    
    // Window modifications
    
    window.clear();
    digital_time.setString("Digital clock");
    window.draw(digital_time);
    window.display();

    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  }
  cout << "\n";
  return 0;
}