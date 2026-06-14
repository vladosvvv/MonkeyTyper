#include "game.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <fmt/ostream.h>

int main() {

    start_menu:

    // Window
    auto menuWin = sf::RenderWindow{sf::VideoMode({1920, 1080}), "Menu - MonkeyTyper"};
    auto gameWin = sf::RenderWindow{sf::VideoMode({1920, 1080}), "MonkeyTyper"};
    gameWin.setVisible(false);

    // Background
    auto menuBgTex = sf::Texture{};
    auto gameBgTex = sf::Texture{};
    if (!menuBgTex.loadFromFile("resources/menu_background.png"))
        fmt::println("Failed to load menu_background.png");
    if (!gameBgTex.loadFromFile("resources/game_background.png"))
        fmt::println("Failed to load game_background.png");
    auto menuBg = sf::Sprite{menuBgTex};
    auto gameBg = sf::Sprite{gameBgTex};
    menuBg.setScale({
        static_cast<float>(menuWin.getSize().x) / menuBgTex.getSize().x,
        static_cast<float>(menuWin.getSize().y) / menuBgTex.getSize().y
    });
    gameBg.setScale({
        static_cast<float>(gameWin.getSize().x) / gameBgTex.getSize().x,
        static_cast<float>(gameWin.getSize().y) / gameBgTex.getSize().y
    });

    // Fonts
    auto fonts = loadFonts();
    auto currentFont = fonts[0];
    auto fontSize = 40;
    auto defaultFont = fonts[0];

    // Word list
    auto easyWords = readWords("resources/wordseasy.txt");
    auto mediumWords = readWords("resources/wordsmedium.txt");
    auto hardWords = readWords("resources/wordshard.txt");
    if (easyWords.empty()) easyWords = {"Error"};
    if (mediumWords.empty()) mediumWords = {"Error"};
    if (hardWords.empty()) hardWords = {"Error"};
    auto currentWords = easyWords;

    // Text position
    auto texts = std::vector<std::vector<sf::Text>>(LINES);
    auto index = std::vector<int>(LINES);
    auto pos = std::vector<sf::Vector2f>(LINES);

    for (auto line = 0; line < LINES; ++line) {
        texts[line] = createTextList(currentWords, currentFont, fontSize);
        for (auto i = 0; i < 1; ++i) {
            index[line] = std::rand() % texts[line].size();
            auto randOffset = std::rand() % static_cast<int>(SPAWN_VAR);
            pos[line] = {
                xPos[line],
                static_cast<float>(gameWin.getSize().y) + randOffset
            };
        }
    }

    // Score and lives
    auto score = 0;
    auto scoreText = sf::Text{defaultFont, "0", 50};
    setupText(scoreText, 180.f, 60.f, sf::Color::White);
    auto scoreLabel = sf::Text{defaultFont, "Score:", 50};
    setupText(scoreLabel, 20.f, 60.f, sf::Color::White);

    auto lives = 5;
    auto livesText = sf::Text{defaultFont, std::to_string(lives), 50};
    setupText(livesText, 170.f, 5.f, sf::Color::White);
    auto livesLabel = sf::Text{defaultFont, "Lives:", 50};
    setupText(livesLabel, 20.f, 5.f, sf::Color::White);

    // Input text
    auto input = std::string{};
    auto inputText = sf::Text{defaultFont, input, 40};
    setupText(inputText, 20.f, 1000.f, sf::Color::White);
    auto inputWordText = sf::Text{defaultFont, "Input:", 50};
    setupText(inputWordText, 20.f, 940.f, sf::Color::White);

    auto playing = true;
    auto rankingUpdated = false;
    auto top5 = readTop5("resources/top5.txt");

    // Menu gui
    auto startBtn = sf::RectangleShape{{160.f, 50.f}};
    setupShape(startBtn, 50.f, 200.f, sf::Color(222,184,135));
    auto startLabel = sf::Text{defaultFont, "Start", 30};
    setupText(startLabel, 70.f, 210.f, sf::Color::White);

    auto leaderBtn = sf::RectangleShape{{160.f, 50.f}};
    setupShape(leaderBtn, 50.f, 410.f, sf::Color(222,184,135));
    auto leaderLabel = sf::Text{defaultFont, "Top 5", 30};
    setupText(leaderLabel, 70.f, 420.f, sf::Color::White);
    auto leaderTextBtn = sf::RectangleShape{{1200.f, 50.f}};
    setupShape(leaderTextBtn, 260.f, 410.f, sf::Color(0,100,0));
    auto leaderText = sf::Text{defaultFont, formatTop5(top5), 30};
    setupText(leaderText, 280.f, 415.f, sf::Color::White);

    auto fontBtn = sf::RectangleShape{{160.f, 50.f}};
    setupShape(fontBtn, 50.f, 270.f, sf::Color(222,184,135));
    auto fontLabel = sf::Text{defaultFont, "Font", 30};
    setupText(fontLabel, 70.f, 280.f, sf::Color::White);

    auto sizeBtn = sf::RectangleShape{{160.f, 50.f}};
    setupShape(sizeBtn, 50.f, 340.f, sf::Color(222,184,135));
    auto sizeLabel = sf::Text{defaultFont, "Font Size", 30};
    setupText(sizeLabel, 70.f, 350.f, sf::Color::White);

    auto levelBtn = sf::RectangleShape{{160.f, 50.f}};
    setupShape(levelBtn, 50.f, 480.f, sf::Color(222,184,135));
    auto levelLabel = sf::Text{defaultFont, "Level", 30};
    setupText(levelLabel, 70.f, 490.f, sf::Color::White);

    auto speedBtn = sf::RectangleShape{{160.f, 50.f}};
    setupShape(speedBtn, 50.f, 550.f, sf::Color(222,184,135));
    auto speedLabel = sf::Text{defaultFont, "Speed", 30};
    setupText(speedLabel, 70.f, 560.f, sf::Color::White);

    auto nameBtn = sf::RectangleShape{{200.f, 50.f}};
    setupShape(nameBtn, 50.f, 620.f, sf::Color(222,184,135));
    auto nameLabel = sf::Text{defaultFont, "Enter Name:", 30};
    setupText(nameLabel, 70.f, 630.f, sf::Color::White);
    auto nameInputBtn = sf::RectangleShape{{400.f, 50.f}};
    setupShape(nameInputBtn, 280.f, 620.f, sf::Color(100,100,100));

    auto fontChoices = std::vector<sf::RectangleShape>{};
    auto fontNames = std::vector<sf::Text>{};
    for (auto i = 0; i < fonts.size(); ++i) {
        auto b = sf::RectangleShape{{160.f, 50.f}};
        setupShape(b, 260.f + 160.f * i, 270.f, sf::Color(222,184,135));
        fontChoices.push_back(b);
        auto t = sf::Text{defaultFont, fmt::format("Font{}", i+1), 30};
        setupText(t, 280.f + 160.f * i, 280.f, sf::Color::White);
        fontNames.push_back(t);
    }
    fontChoices[0].setFillColor(sf::Color::Red);

    auto sizeChoices = std::vector<sf::RectangleShape>{};
    auto sizeNames = std::vector<sf::Text>{};
    for (auto i = 0; i < 4u; ++i) {
        auto b = sf::RectangleShape{{80.f, 50.f}};
        setupShape(b, 260.f + 80.f * i, 340.f, sf::Color(222,184,135));
        sizeChoices.push_back(b);
        auto t = sf::Text{defaultFont, std::to_string(i+1), 30};
        setupText(t, 280.f + 80.f * i, 350.f, sf::Color::White);
        sizeNames.push_back(t);
    }
    sizeChoices[0].setFillColor(sf::Color::Red);

    auto levelChoices = std::vector<sf::RectangleShape>{};
    auto levelNames = std::vector<sf::Text>{};
    auto levelLabelsVec = std::vector<std::string>{"Easy","Medium","Hard"};
    for (auto i = 0; i < levelLabelsVec.size(); ++i) {
        auto b = sf::RectangleShape{{150.f, 50.f}};
        setupShape(b, 260.f + 160.f * i, 480.f, sf::Color(222,184,135));
        levelChoices.push_back(b);
        auto t = sf::Text{defaultFont, levelLabelsVec[i], 30};
        setupText(t, 280.f + 160.f * i, 490.f, sf::Color::White);
        levelNames.push_back(t);
    }
    levelChoices[0].setFillColor(sf::Color::Red);

    auto speedChoices = std::vector<sf::RectangleShape>{};
    auto speedNames = std::vector<sf::Text>{};
    auto speedLabelsVec = std::vector<std::string>{"0.5x","1x","1.5x","2x"};
    for (auto i = 0; i < speedLabelsVec.size(); ++i) {
        auto b = sf::RectangleShape{{100.f, 50.f}};
        setupShape(b, 260.f + 110.f * i, 550.f, sf::Color(222,184,135));
        speedChoices.push_back(b);
        auto t = sf::Text{defaultFont, speedLabelsVec[i], 24};
        setupText(t, 280.f + 110.f * i, 560.f, sf::Color::White);
        speedNames.push_back(t);
    }
    speedChoices[1].setFillColor(sf::Color::Red);

    auto playerName = std::string{};
    auto nameInputText = sf::Text{defaultFont, playerName, 30};
    setupText(nameInputText, 300.f, 630.f, sf::Color::White);

    auto showLeaders = false, showFonts = false, showSizes = false, showLevels = false, showSpeeds = false, editingName = false;
    auto speedX = 1.0f;

    // MENU LOOP
    while (menuWin.isOpen()) {
        while (auto optEvent = menuWin.pollEvent()) {
            const auto& ev = *optEvent;
            if (ev.is<sf::Event::Closed>()) return 0;
            if (ev.is<sf::Event::MouseButtonPressed>()) {
                auto mb = *ev.getIf<sf::Event::MouseButtonPressed>();
                if (mb.button == sf::Mouse::Button::Left) {
                    auto mousePos = sf::Vector2f{static_cast<float>(mb.position.x), static_cast<float>(mb.position.y)};
                    if (startBtn.getGlobalBounds().contains(mousePos)) {
                        menuWin.close();
                        gameWin.setVisible(true);
                    } else if (leaderBtn.getGlobalBounds().contains(mousePos)) {
                        showLeaders = !showLeaders;
                    } else if (fontBtn.getGlobalBounds().contains(mousePos)) {
                        showFonts = !showFonts;
                    } else if (sizeBtn.getGlobalBounds().contains(mousePos)) {
                        showSizes = !showSizes;
                    } else if (levelBtn.getGlobalBounds().contains(mousePos)) {
                        showLevels = !showLevels;
                    } else if (speedBtn.getGlobalBounds().contains(mousePos)) {
                        showSpeeds = !showSpeeds;
                    } else if (nameBtn.getGlobalBounds().contains(mousePos)) {
                        editingName = !editingName;
                    }

                    if (showFonts) {
                        for (auto i = 0; i < fonts.size(); ++i) {
                            if (fontChoices[i].getGlobalBounds().contains(mousePos)) {
                                currentFont = fonts[i];
                                for (auto& b : fontChoices) b.setFillColor(sf::Color(222,184,135));
                                fontChoices[i].setFillColor(sf::Color::Red);
                                for (auto ln = 0; ln < LINES; ++ln) {
                                    texts[ln] = createTextList(currentWords, currentFont, fontSize);
                                }
                            }
                        }
                    }

                    if (showSizes) {
                        for (auto i = 0; i < sizeChoices.size(); ++i) {
                            if (sizeChoices[i].getGlobalBounds().contains(mousePos)) {
                                fontSize = 40.f + 10.f * i;
                                for (auto& b : sizeChoices) b.setFillColor(sf::Color(222,184,135));
                                sizeChoices[i].setFillColor(sf::Color::Red);
                                for (auto ln = 0; ln < LINES; ++ln) {
                                    texts[ln] = createTextList(currentWords, currentFont, fontSize);
                                }
                            }
                        }
                    }

                    if (showLevels) {
                        for (auto i = 0; i < levelChoices.size(); ++i) {
                            if (levelChoices[i].getGlobalBounds().contains(mousePos)) {
                                for (auto& b : levelChoices) b.setFillColor(sf::Color(222,184,135));
                                levelChoices[i].setFillColor(sf::Color::Red);
                                switch (i) {
                                    case 0: currentWords = easyWords; break;
                                    case 1: currentWords = mediumWords; break;
                                    default: currentWords = hardWords;
                                }
                                for (auto ln = 0; ln < LINES; ++ln) {
                                    texts[ln] = createTextList(currentWords, currentFont, fontSize);
                                    index[ln] = std::rand() % texts[ln].size();
                                    pos[ln] = { xPos[ln], static_cast<float>(gameWin.getSize().y) + (std::rand() % static_cast<int>(SPAWN_VAR)) };
                                }
                            }
                        }
                    }

                    if (showSpeeds) {
                        for (auto i = 0; i < speedChoices.size(); ++i) {
                            if (speedChoices[i].getGlobalBounds().contains(mousePos)) {
                                for (auto& b : speedChoices) b.setFillColor(sf::Color(222,184,135));
                                speedChoices[i].setFillColor(sf::Color::Red);
                                switch (i) {
                                    case 0: speedX = 0.5f; break;
                                    case 1: speedX = 1.0f; break;
                                    case 2: speedX = 1.5f; break;
                                    case 3: speedX = 2.0f; break;
                                    default: speedX = 1.0f;
                                }
                            }
                        }
                    }
                }
            }

            if (editingName && ev.is<sf::Event::TextEntered>()) {
                auto c = static_cast<char>(ev.getIf<sf::Event::TextEntered>()->unicode);
                if (letterCheck(c)) {
                    playerName.push_back(c);
                    nameInputText.setString(playerName);
                } else if (c == '\b' && !playerName.empty()) {
                    playerName.pop_back();
                    nameInputText.setString(playerName);
                }
            }
        }

        menuWin.clear();
        menuWin.draw(menuBg);
        menuWin.draw(startBtn);
        menuWin.draw(startLabel);
        menuWin.draw(leaderBtn);
        menuWin.draw(leaderLabel);
        if (showLeaders) {
            menuWin.draw(leaderTextBtn);
            menuWin.draw(leaderText);
        }
        menuWin.draw(fontBtn);
        menuWin.draw(fontLabel);
        if (showFonts) {
            for (auto i = 0; i < fontChoices.size(); ++i) {
                menuWin.draw(fontChoices[i]);
                menuWin.draw(fontNames[i]);
            }
        }
        menuWin.draw(sizeBtn);
        menuWin.draw(sizeLabel);
        if (showSizes) {
            for (auto i = 0; i < sizeChoices.size(); ++i) {
                menuWin.draw(sizeChoices[i]);
                menuWin.draw(sizeNames[i]);
            }
        }
        menuWin.draw(levelBtn);
        menuWin.draw(levelLabel);
        if (showLevels) {
            for (auto i = 0; i < levelChoices.size(); ++i) {
                menuWin.draw(levelChoices[i]);
                menuWin.draw(levelNames[i]);
            }
        }
        menuWin.draw(speedBtn);
        menuWin.draw(speedLabel);
        if (showSpeeds) {
            for (auto i = 0; i < speedChoices.size(); ++i) {
                menuWin.draw(speedChoices[i]);
                menuWin.draw(speedNames[i]);
            }
        }

        menuWin.draw(nameBtn);
        menuWin.draw(nameInputBtn);
        menuWin.draw(nameLabel);
        menuWin.draw(nameInputText);

        menuWin.display();
    }

    // GAME LOOP
    while (gameWin.isOpen()) {
        while (auto optEvent = gameWin.pollEvent()) {
            const auto& ev = *optEvent;
            if (ev.is<sf::Event::Closed>()) return 0;
            if (ev.is<sf::Event::TextEntered>()) {
                auto c = static_cast<char>(ev.getIf<sf::Event::TextEntered>()->unicode);
                if (letterCheck(c)) {
                    input.push_back(c);
                    inputText.setString(input);
                }
                for (auto line = 0; line < LINES; ++line) {
                    if (input == texts[line][index[line]].getString()) {
                            deleteInput(input, inputText);
                            plusScore(score, scoreText);
                            index[line] = (index[line]+ 1) % texts[line].size();
                            pos[line] = { xPos[line], static_cast<float>(gameWin.getSize().y) + (std::rand() % static_cast<int>(SPAWN_VAR)) };
                    }
                }
            }
            if (ev.is<sf::Event::KeyPressed>()) {
                auto kp = *ev.getIf<sf::Event::KeyPressed>();
                if (kp.code == sf::Keyboard::Key::Backspace) {
                    if (!input.empty()) input.pop_back();
                    inputText.setString(input);
                } else if (kp.code == sf::Keyboard::Key::Escape) {
                    deleteInput(input, inputText);
                } else if (kp.code == sf::Keyboard::Key::Enter && !playing) {
                    score = 0; scoreText.setString("0");
                    lives = 5; livesText.setString("5");
                    for (auto line = 0; line < LINES; ++line) {
                        index[line] = std::rand() % texts[line].size();
                        pos[line] = { xPos[line], static_cast<float>(gameWin.getSize().y) + (std::rand() % static_cast<int>(SPAWN_VAR)) };
                    }
                    deleteInput(input, inputText);
                    playing = true; rankingUpdated = false;
                    top5 = readTop5("resources/top5.txt");
                }
            }
        }
        for (auto line = 0; line < LINES; ++line) {
            pos[line].y -= SPEED * speedX;
                if (pos[line].y < 0) {
                    --lives;
                    livesText.setString(std::to_string(lives));
                    index[line] = (index[line] + 1) % texts[line].size();
                    pos[line] = { xPos[line], static_cast<float>(gameWin.getSize().y) + (std::rand() % static_cast<int>(SPAWN_VAR)) };
            }
        }
        if (lives < 1) playing = false;
        if (!playing && !rankingUpdated) {
            updateTop5(score, playerName.empty() ? "Anonymous" : playerName, top5);
            rankingUpdated = true;
        }
        gameWin.clear();
        gameWin.draw(gameBg);
        if (playing) {
            for (auto line = 0; line < LINES; ++line){

                auto& txt = texts[line][index[line]];
                    txt.setPosition(pos[line]);
                    auto winH = static_cast<float>(gameWin.getSize().y);
                    auto y = pos[line].y;
                    if (y <= winH * 0.25f) txt.setFillColor(sf::Color::Red);
                    else if (y <= winH * 0.5f) txt.setFillColor(sf::Color::Yellow);
                    else txt.setFillColor(sf::Color::Green);
                    gameWin.draw(txt);
            }
            gameWin.draw(inputText);
            gameWin.draw(inputWordText);
            gameWin.draw(scoreText);
            gameWin.draw(scoreLabel);
            gameWin.draw(livesLabel);
            gameWin.draw(livesText);
        } else {
            auto finalScoreText = sf::Text{defaultFont, "Final score: " + std::to_string(score), 50};
            setupText(finalScoreText, 810, 480, sf::Color::White);
            gameWin.draw(finalScoreText);
            auto menuBtn = sf::RectangleShape{{200.f, 50.f}};
            setupShape(menuBtn, 710, 560, sf::Color(70,130,180));
            auto menuBtnText = sf::Text{defaultFont, "Menu", 30};
            setupText(menuBtnText, 740, 570, sf::Color::White);
            auto restartBtn = sf::RectangleShape{{200.f, 50.f}};
            setupShape(restartBtn, 1010, 560, sf::Color(34,139,34));
            auto restartBtnText = sf::Text{defaultFont, "Restart", 30};
            setupText(restartBtnText, 1040, 570, sf::Color::White);
            gameWin.draw(menuBtn);
            gameWin.draw(menuBtnText);
            gameWin.draw(restartBtn);
            gameWin.draw(restartBtnText);
            gameWin.display();
            auto waiting = true;
            while (waiting) {
                while (auto ev2opt = gameWin.pollEvent()) {
                    const auto& ev2 = *ev2opt;
                    if (ev2.is<sf::Event::Closed>()) return 0;
                    if (ev2.is<sf::Event::MouseButtonPressed>()) {
                        auto mb2 = *ev2.getIf<sf::Event::MouseButtonPressed>();
                        auto mpos2 = sf::Vector2f{static_cast<float>(mb2.position.x), static_cast<float>(mb2.position.y)};
                        if (menuBtn.getGlobalBounds().contains(mpos2)) {
                            gameWin.close();
                            menuWin.setVisible(true);
                            goto start_menu;
                        }
                        if (restartBtn.getGlobalBounds().contains(mpos2)) {
                            score = 0; scoreText.setString("0");
                            lives = 5; livesText.setString("5");
                            for (auto line = 0; line < LINES; ++line) {
                                index[line] = std::rand() % texts[line].size();
                                pos[line] = { xPos[line], static_cast<float>(gameWin.getSize().y) + (std::rand() % static_cast<int>(SPAWN_VAR)) };
                            }
                            deleteInput(input, inputText);
                            playing = true; rankingUpdated = false;
                            top5 = readTop5("resources/top5.txt");
                            waiting = false;
                        }
                    }
                }
            }
        }
        gameWin.display();
    }

    return 0;
}
