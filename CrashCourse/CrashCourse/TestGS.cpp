#include "TestGS.h"
#include <iostream>

const int TestGS::SCREEN_WIDTH = 700;
const int TestGS::SCREEN_HEIGHT = 700;

TestGS::TestGS() {
	settings.antialiasingLevel = 8;
	window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Trails", sf::Style::Default, settings);
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(60);
	isPlaying = true;
	mousePressed = false;

	trail = new Trail();
}

void TestGS::update() {
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code) {
			case sf::Keyboard::Escape:
				window.close();
			case sf::Keyboard::Space:
				isPlaying = !isPlaying;
			default:
				break;
			}
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left) {
				mousePressed = true;
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left) {
				mousePressed = false;
			}
			break;
		default:
			break;
		}
	}

	if (isPlaying) {
		if (mousePressed) {
			trail->update(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
		}
		else {
			trail->update();
		}
	}
}

void TestGS::render() {
	window.clear(sf::Color::Black);

	window.draw(*trail);

	window.display();
}

void TestGS::execute() {
	while (window.isOpen()) {
		update();
		render();
	}
}
