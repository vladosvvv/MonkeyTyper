#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>


constexpr auto LINES = 5;
const auto xPos = std::vector{400.f, 700.f, 1000.f, 1300.f, 1600.f};
constexpr auto SPAWN_VAR = 600.f;
constexpr auto SPEED = 0.03f;


struct ScoreEntry {
    std::string name;
    int score;
};

auto loadFonts() -> std::vector<sf::Font>;
auto createTextList(const std::vector<std::string>& words,const sf::Font& font,unsigned size) -> std::vector<sf::Text>;
auto readWords(const std::string& path) -> std::vector<std::string>;
auto letterCheck(char c) -> bool;
auto plusScore(int& score, sf::Text& txt) -> void;
auto deleteInput(std::string& in, sf::Text& txt) -> void;
auto setupShape(sf::RectangleShape& s, float x, float y, const sf::Color& fillColor) -> void;
auto setupText(sf::Text& t, float x, float y, sf::Color c) -> void;
auto readTop5(const std::string& path) -> std::vector<ScoreEntry>;
auto writeTop5(const std::vector<ScoreEntry>& v, const std::string& path) -> void;
auto updateTop5(int finalScore, const std::string& playerName, std::vector<ScoreEntry>& old) -> void;
auto formatTop5(const std::vector<ScoreEntry>& v) -> std::string;


