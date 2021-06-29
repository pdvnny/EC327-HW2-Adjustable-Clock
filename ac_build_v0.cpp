// Copyright 2021 Parker Dunn pgdunn@bu.edu
// Alternate: parker_dunn@outlook.com & pdunn91@gmail.com
// Originated Jun 7, 2021

// Developed for EC327 at Boston University
// HW2 - Use SFML library to create an analog and digital clock graphic

#include <chrono>
#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>  // SFML: https://www.sfml-dev.org

// Might need to be removed later
#include <string>
#include <thread>
#include <vector>

using std::cout;
using std::string;
using std::stoi;

// Might need to be removed later
using std::vector;



// TO DO
// -- Make time to script (review HW2 details to figure out format)
// -- Create function "mod_time" - uses input arg to modify time
// -- Incorporate shapes for the clock in the script
// -- Move the shapes over time
// -- Sync shape movement with clock

// PROBLEMS


int main(int argc, char **argv) {

  vector<string> pdunn = {"First: Parker", "Last: Dunn"};

  // Testing reception of input
  if (argc == 2) {
    cout << "One entry received.\n\n";
    cout << "Here is your input: " << stoi(argv[1]) << "\n\n";
  } else {
    cout << "This function expects one command line argument.\n";
  }

  // Building a SFML window
  sf::RenderWindow window(sf::VideoMode(200,200), "pgdunn@bu.edu");

  // Setting up text in the window
  sf::Text my_name;
  sf::Font output_font;
  output_font.loadFromFile("/usr/share/fonts/truetype/tlwg/TlwgTypewriter-Bold.ttf");
  my_name.setFont(output_font);
  my_name.setFillColor(sf::Color::White);
  my_name.setOutlineColor(sf::Color::Red);
  my_name.setOutlineThickness(1);
  my_name.setCharacterSize(15);
  my_name.setPosition(25, 5);

  // Setting a frame rate limit
  window.setFramerateLimit(60); // 60 fps

  int iterat = 0;
  while (window.isOpen()) {

    // This little block checkes for closing of window
    sf::Event window_activity;
    while (window.pollEvent(window_activity)) {
      if (window_activity.type == sf::Event::Closed)
        window.close();
    }

    window.clear();

    my_name.setString(pdunn.at(iterat % 2));
    window.draw(my_name);
    iterat++;


    window.display();

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  }

  return 0;
}