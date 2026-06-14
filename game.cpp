#include "game.h"
#include <iostream>
#include <algorithm>
#include <fmt/ostream.h>



auto loadFonts() -> std::vector<sf::Font> {
    auto out = std::vector<sf::Font>{};
    auto f = sf::Font{};
    if (f.openFromFile("resources/font1.ttf")) out.push_back(f);
    if (f.openFromFile("resources/font2.ttf")) out.push_back(f);
    if (f.openFromFile("resources/font3.ttf")) out.push_back(f);
    if (f.openFromFile("resources/font4.ttf")) out.push_back(f);
    return out;
}


auto createTextList(
    const std::vector<std::string>& words,
    const sf::Font& font,
    unsigned size
) -> std::vector<sf::Text> {
    auto list = std::vector<sf::Text>{};
    for (auto const& w : words) {
        list.emplace_back(font, sf::String(w), size);
        list.back().setFillColor(sf::Color::Black);
    }
    return list;
}

auto readWords(const std::string& path) -> std::vector<std::string> {
    auto file = std::fstream{path};
    auto words = std::vector<std::string>{};
    auto s = std::string{};
    while (file >> s) words.push_back(s);
    return words;
}

auto letterCheck(char a) -> bool {
    return (a >= 'A' && a <= 'Z') || (a >= 'a' && a <= 'z');
}

auto plusScore(int& score, sf::Text& txt) -> void {
    txt.setString(std::to_string(++score));
}

auto deleteInput(std::string& in, sf::Text& txt) -> void {
    in.clear();
    txt.setString(in);
}

auto setupShape(sf::RectangleShape& s, float x, float y, const sf::Color& fillColor) -> void {
    s.setPosition({x, y});
    s.setFillColor(fillColor);
    s.setOutlineColor(sf::Color(255, 215, 200));
    s.setOutlineThickness(3.f);
}

auto setupText(sf::Text& t, float x, float y, sf::Color c) -> void {
    t.setPosition({x, y});
    t.setFillColor(c);
}

auto readTop5(const std::string& path) -> std::vector<ScoreEntry> {
    auto file = std::fstream{path};
    auto top = std::vector<ScoreEntry>{};
    auto name = std::string{};
    auto score = int{};
    while (top.size() < 5 && file >> name >> score) {
        top.push_back({name, score});
    }
    return top;
}

auto writeTop5(const std::vector<ScoreEntry>& v, const std::string& path) -> void {
    auto file = std::fstream{path};
    for (auto const& top : v) {
        file << top.name << ' ' << top.score << '\n';
    }
}

auto updateTop5(int finalScore, const std::string& playerName, std::vector<ScoreEntry>& old) -> void {
    old.push_back({playerName, finalScore});
    std::ranges::sort(old.begin(), old.end(),
        [](auto const& a, auto const& b) { return a.score > b.score; });
    if (old.size() > 5) {
        old.resize(5);
    }
    writeTop5(old, "resources/top5.txt");
}

auto formatTop5(const std::vector<ScoreEntry>& v) -> std::string {
    auto out = std::string{};
    int idx = 1;
    for (auto const& e : v) {
        out += fmt::format("{}. {} - {}  ", idx++, e.name, e.score);
    }
    return out;
}

