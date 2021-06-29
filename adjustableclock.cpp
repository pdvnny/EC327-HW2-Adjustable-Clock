// Copyright 2021 Parker Dunn pgdunn@bu.edu
// Alternate: parker_dunn@outlook.com & pdunn91@gmail.com
// Originated Jun 7, 2021

// Developed for EC327 at Boston University
// HW2 - Use SFML library to create an analog and digital clock graphic

#include <chrono>
#include <ctime>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <SFML/Graphics.hpp>

using std::cout;
using std::string;
using std::stoi;
using std::to_string;
using std::vector;

// Duplicated from EC327 lecture material | Returns a highly accurate time
double besttime() {
  auto now = std::chrono::high_resolution_clock::now();
  auto dur = now.time_since_epoch();
  return dur.count()/1'000'000'000.0;
}

// Modify a time_t time value then convert it to a tm structure
std::tm time_adjust(time_t time, int adjust) {
  time += adjust;
  return *localtime(&time);
}

int main(int argc, char **argv) {

  string display_time;
  int clock_adjust;

  if (argc > 1) {
    // Professor said this does not need error-checking
    clock_adjust = stoi(argv[1]);
  } else {
    clock_adjust = 0;
  }

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
  digital_time.setPosition(75, 5);

  // Setting up shapes in the window
  sf::ConvexShape second_hand(3);
  second_hand.setPosition(100, 120);
  second_hand.setPoint(0, sf::Vector2f(-3, 0));
  second_hand.setPoint(1, sf::Vector2f(3, 0));
  second_hand.setPoint(2, sf::Vector2f(0, -70));
  second_hand.setFillColor(sf::Color::Red);
  second_hand.setOutlineColor(sf::Color::White);
  second_hand.setOutlineThickness(0.25);

  sf::ConvexShape minute_hand(3);
  minute_hand.setPosition(100, 120);
  minute_hand.setPoint(0, sf::Vector2f(-3, 0));
  minute_hand.setPoint(1, sf::Vector2f(3, 0));
  minute_hand.setPoint(2, sf::Vector2f(0, -60));
  minute_hand.setFillColor(sf::Color::Blue);
  minute_hand.setOutlineColor(sf::Color::White);
  minute_hand.setOutlineThickness(0.25);

  sf::ConvexShape hour_hand(3);
  hour_hand.setPosition(100, 120);
  hour_hand.setPoint(0, sf::Vector2f(-4, 0));
  hour_hand.setPoint(1, sf::Vector2f(4, 0));
  hour_hand.setPoint(2, sf::Vector2f(0, -45));
  hour_hand.setFillColor(sf::Color::Cyan);
  hour_hand.setOutlineColor(sf::Color::White);
  hour_hand.setOutlineThickness(0.25);

  // Setting a frame rate limit
  window.setFramerateLimit(60); // 60 fps

  // Related to displaying shapes and rotating them
  bool initial_display = true;

  while (window.isOpen()) {

    // check for window close
    sf::Event window_activity;
    while (window.pollEvent(window_activity)) {
      if (window_activity.type == sf::Event::Closed)
        window.close();
    }

    // time gets the current time; returns value of type time_t
    std::time_t time = std::time(NULL);
    std::tm adjusted_time;  // declaring for modification later
    double accurate_time = besttime(); // see above "besttime" for info on this


    // Only displaying in first 25% of the second
    if ((accurate_time - (int)accurate_time) < 0.25) {
    
      adjusted_time = time_adjust(time, clock_adjust);
      display_time = std::asctime(&adjusted_time);

      // Terminal modifications
      cout << display_time << "\n";

      // Window modifications
      window.clear();
      digital_time.setString(display_time.substr(11, 8));
      window.draw(digital_time);

      if (initial_display) {
        double adj_sec = adjusted_time.tm_sec;
        double adj_min = adjusted_time.tm_min;
        double adj_hours = adjusted_time.tm_hour;

        hour_hand.setRotation(360.0 * ((adj_hours / 12.0) + (adj_min / 60.0 / 12.0) + (adj_sec / 60.0 / 60.0 / 12.0)));
        minute_hand.setRotation(360.0 * ((adj_min/ 60.0) + (adj_sec / 60.0 / 60.0)));
        second_hand.setRotation(360.0 * (adj_sec / 60.0));

        initial_display = false;
      } else {
        second_hand.rotate(360.0 * (1.0/60.0));
        minute_hand.rotate(360.0 * (1.0/3600.0));
        hour_hand.rotate(360.0 * (1.0/216000.0));
      }
      window.draw(second_hand);
      window.draw(minute_hand);
      window.draw(hour_hand);

      window.display();
      std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
  }
  cout << "\n";
  return 0; 
}