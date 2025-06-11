#include "klasa_gra.h"

int Gra2::startGame()
{
    srand(static_cast<unsigned>(time(nullptr)));

    PlaySound(NULL, NULL, 0);

    sf::RenderWindow levelWindow(sf::VideoMode(1536, 1024), "Level 1");
    sf::Texture levelTexture;
    if (!levelTexture.loadFromFile("level_1.png")) return -1;
    sf::Sprite levelBackground(levelTexture);

    sf::Clock levelClock;
    while (levelWindow.isOpen())
    {
        sf::Event levelEvent;
        while (levelWindow.pollEvent(levelEvent)) {
            if (levelEvent.type == sf::Event::Closed) levelWindow.close();
        }


        if (levelClock.getElapsedTime().asSeconds() >= 2.f) {
            levelWindow.close();
        }

        levelWindow.clear();
        levelWindow.draw(levelBackground);
        levelWindow.display();
    }

     playBackgroundMusic("background_music.wav");


    sf::RenderWindow window(sf::VideoMode(1536, 1024), "SFML Game");

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("mapa1.png")) return -1;
    sf::Sprite background(backgroundTexture);

    sf::Texture heartTexture;
    if (!heartTexture.loadFromFile("czerwone.png")) return -1;
    sf::Texture grayHeartTexture;
    if (!grayHeartTexture.loadFromFile("szare.png")) return -1;

    Mage mage(&window);
    Archer archer(&window);
    mage.setWindow(&window);
    archer.setWindow(&window);

    std::vector<Character*> characters = {&mage, &archer};
    std::vector<Projectile> projectiles;

    auto tex1 = std::make_shared<sf::Texture>();
    auto tex2 = std::make_shared<sf::Texture>();
    if (!tex1->loadFromFile("kula1.png") || !tex2->loadFromFile("kula2.png")) return -1;
    auto texArrow = std::make_shared<sf::Texture>();
    if (!texArrow->loadFromFile("strzala.png")) return -1;

    std::vector<Ant> ants;
    auto antTexture = std::make_shared<sf::Texture>();
    if (!antTexture->loadFromFile("mrowka11.png")) return -1;

    for (int i = 0; i < 10; ++i) {
        float randX = static_cast<float>(rand() % window.getSize().x);
        float randY = static_cast<float>(rand() % window.getSize().y);
        ants.emplace_back(antTexture, &window, sf::Vector2f(randX, randY), 1);  // Przekazujemy poziom 1

    }

    sf::Clock clock;
    sf::Clock shootClock;
    sf::Clock shootClockArcher;

    std::vector<Heart> mageHearts;
    std::vector<Heart> archerHearts;

    int mageTouches = 0;
    int archerTouches = 0;

    sf::Clock mageTouchClock;
    sf::Clock archerTouchClock;

    float leftX = 20.f;
    float space = 30.f;
    for (int i = 0; i < 3; i++) {
        mageHearts.emplace_back(heartTexture, sf::Vector2f(leftX + i * space, 10.f));
    }

    float rightX = window.getSize().x - 37.f;
    for (int i = 0; i < 3; i++) {
        archerHearts.emplace_back(heartTexture, sf::Vector2f(rightX - (i + 1) * space, 10.f));
    }

    playBackgroundMusic("background_music.wav");

    bool waitingForNextLevel = false;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && shootClock.getElapsedTime().asSeconds() >= 0.5f) {
                sf::FloatRect bounds = mage.getSprite().getGlobalBounds();
                sf::Vector2f start(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);

                Direction dir = mage.getLastDirection();
                std::shared_ptr<sf::Texture> tex = (rand() % 2 == 0) ? tex1 : tex2;

                projectiles.emplace_back(tex, start, dir);
                shootClock.restart();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && shootClockArcher.getElapsedTime().asSeconds() >= 0.5f) {
                sf::FloatRect bounds = archer.getSprite().getGlobalBounds();
                sf::Vector2f start(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);

                Direction dir = archer.getLastDirection();
                projectiles.emplace_back(texArrow, start, dir);
                shootClockArcher.restart();
            }
        }

        for (auto* character : characters) character->poruszanie(deltaTime);
        for (auto& p : projectiles) p.update(deltaTime);
        for (auto& ant : ants) ant.poruszanie(deltaTime);

        for (auto it = projectiles.begin(); it != projectiles.end();) {
            bool removed = false;

            for (auto jt = ants.begin(); jt != ants.end(); ++jt) {
                if (it->getBounds().intersects(jt->getSprite().getGlobalBounds())) {
                    it = projectiles.erase(it);
                    jt = ants.erase(jt);
                    removed = true;
                    break;
                }
            }

            if (!removed) {
                ++it;
            }
        }
        for (auto& ant : ants) {
            if (ant.checkCollision(mage.getSprite()) && mageTouches < 3) {
                if (mageTouchClock.getElapsedTime().asSeconds() >= 2.f) {
                    for (auto& heart : mageHearts) {
                        if (!heart.isGray) {
                            heart.changeToGray(grayHeartTexture);
                            mageTouches++;
                            mageTouchClock.restart();
                            break;
                        }
                    }
                }
            }
            if (ant.checkCollision(archer.getSprite()) && archerTouches < 3) {
                if (archerTouchClock.getElapsedTime().asSeconds() >= 2.f) {
                    for (auto& heart : archerHearts) {
                        if (!heart.isGray) {
                            heart.changeToGray(grayHeartTexture);
                            archerTouches++;
                            archerTouchClock.restart();
                            break;
                        }
                    }
                }
            }
        }

        projectiles.erase(
            std::remove_if(projectiles.begin(), projectiles.end(),
                [&window](const Projectile& p) {
                    auto b = p.getBounds();
                    return b.left > window.getSize().x || b.left + b.width < 0 ||
                           b.top > window.getSize().y || b.top + b.height < 0;
                }),
            projectiles.end()
        );


        if (checkGameOver(window, mageHearts, archerHearts)){return 0;};

        window.clear();
        window.draw(background);

        for (auto& heart : mageHearts) {
            window.draw(heart.getDrawable());
        }
        for (auto& heart : archerHearts) {
            window.draw(heart.getDrawable());
        }

        for (auto& ant : ants) {
            window.draw(ant.getDrawable());
        }

        for (auto& p : projectiles) window.draw(p.getDrawable());
        for (auto* character : characters) window.draw(character->getDrawable());

        window.display();

        if (allAntsDead(ants) && !waitingForNextLevel) {
            waitingForNextLevel = true;

            sf::Clock countdownClock;

            while (window.isOpen()) {
                if (countdownClock.getElapsedTime().asSeconds() >= 3.f) {
                    window.close();
                    break;
                }

                for (auto* character : characters) character->poruszanie(deltaTime);
                for (auto& p : projectiles) p.update(deltaTime);
                for (auto& ant : ants) ant.poruszanie(deltaTime);

                window.clear();
                window.draw(background);

                for (auto& heart : mageHearts){window.draw(heart.getDrawable());}
                for (auto& heart : archerHearts){window.draw(heart.getDrawable());}
                for (auto& ant : ants){window.draw(ant.getDrawable());}
                for (auto& p : projectiles) window.draw(p.getDrawable());
                for (auto* character : characters) window.draw(character->getDrawable());
                window.display();
            }
sf::RenderWindow levelWindow2(sf::VideoMode(1536, 1024), "Level 2");
sf::Texture level2Texture;
if (!level2Texture.loadFromFile("level_2.png")) return -1;
sf::Sprite level2Background(level2Texture);

sf::Clock level2Clock;
while (levelWindow2.isOpen())
{
    sf::Event level2Event;
    while (levelWindow2.pollEvent(level2Event)) {
        if (level2Event.type == sf::Event::Closed) levelWindow2.close();
    }

    if (level2Clock.getElapsedTime().asSeconds() >= 2.f) {
        levelWindow2.close();
    }

    levelWindow2.clear();
    levelWindow2.draw(level2Background);
    levelWindow2.display();
}

    sf::RenderWindow gameWindow2(sf::VideoMode(1536, 1024), "SFML Game");
    sf::Texture backgroundTexture2;
if (!backgroundTexture2.loadFromFile("mapa2.png")) {

    return -1;
}
sf::Sprite background2(backgroundTexture2);

auto antTexture2 = std::make_shared<sf::Texture>();
if (!antTexture2->loadFromFile("mrowka22.png")) {

    return -1;
}

std::vector<Ant> ants2;
for (int i = 0; i < 10; ++i) {
    float randX = static_cast<float>(rand() % gameWindow2.getSize().x);
    float randY = static_cast<float>(rand() % gameWindow2.getSize().y);
    ants2.emplace_back(antTexture2, &gameWindow2, sf::Vector2f(randX, randY), 1);

    ants2.back().setSpeed(600.f);
}


bool waitingForLevelEnd = false;

while (gameWindow2.isOpen())
{
    float deltaTime = clock.restart().asSeconds();

    sf::Event event;
    while (gameWindow2.pollEvent(event)) {
        if (event.type == sf::Event::Closed) gameWindow2.close();

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && shootClock.getElapsedTime().asSeconds() >= 0.5f) {
            sf::FloatRect bounds = mage.getSprite().getGlobalBounds();
            sf::Vector2f start(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);

            Direction dir = mage.getLastDirection();
            std::shared_ptr<sf::Texture> tex = (rand() % 2 == 0) ? tex1 : tex2;

            projectiles.emplace_back(tex, start, dir);
            shootClock.restart();
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && shootClockArcher.getElapsedTime().asSeconds() >= 0.5f) {
            sf::FloatRect bounds = archer.getSprite().getGlobalBounds();
            sf::Vector2f start(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);

            Direction dir = archer.getLastDirection();
            projectiles.emplace_back(texArrow, start, dir);
            shootClockArcher.restart();
        }
    }

    for (auto* character : characters) character->poruszanie(deltaTime);
    for (auto& p : projectiles) p.update(deltaTime);
    for (auto& ant : ants2) ant.poruszanie(deltaTime);

    for (auto it = projectiles.begin(); it != projectiles.end();) {
        bool removed = false;

        for (auto jt = ants2.begin(); jt != ants2.end(); ++jt) {
            if (it->getBounds().intersects(jt->getSprite().getGlobalBounds())) {

                it = projectiles.erase(it);
                jt = ants2.erase(jt);
                removed = true;
                break;
            }
        }

        if (!removed) {
            ++it;
        }
    }

    for (auto& ant : ants2) {
        if (ant.checkCollision(mage.getSprite()) && mageTouches < 3) {
            if (mageTouchClock.getElapsedTime().asSeconds() >= 2.f) {
                for (auto& heart : mageHearts) {
                    if (!heart.isGray) {
                        heart.changeToGray(grayHeartTexture);
                        mageTouches++;
                        mageTouchClock.restart();
                        break;
                    }
                }
            }
        }
        if (ant.checkCollision(archer.getSprite()) && archerTouches < 3) {
            if (archerTouchClock.getElapsedTime().asSeconds() >= 2.f) {
                for (auto& heart : archerHearts) {
                    if (!heart.isGray) {
                        heart.changeToGray(grayHeartTexture);
                        archerTouches++;
                        archerTouchClock.restart();
                        break;
                    }
                }
            }
        }
    }

    projectiles.erase(
        std::remove_if(projectiles.begin(), projectiles.end(),
            [&gameWindow2](const Projectile& p) {
                auto b = p.getBounds();
                return b.left > gameWindow2.getSize().x || b.left + b.width < 0 ||
                    b.top > gameWindow2.getSize().y || b.top + b.height < 0;
            }),
        projectiles.end()
    );


    if (allAntsDead(ants2) && !waitingForLevelEnd) {
        countdownClock.restart();
        waitingForLevelEnd = true;
    }

    if (waitingForLevelEnd && countdownClock.getElapsedTime().asSeconds() >= 3.f) {
        gameWindow2.close();
    }

    if (checkGameOver(gameWindow2, mageHearts, archerHearts)){return 0;};

    gameWindow2.clear();
    gameWindow2.draw(background2);

    for (auto& ant : ants2){gameWindow2.draw(ant.getDrawable());}
    for (auto& heart : mageHearts){gameWindow2.draw(heart.getDrawable());}
    for (auto& heart : archerHearts){gameWindow2.draw(heart.getDrawable());}
    for (auto& p : projectiles) gameWindow2.draw(p.getDrawable());
    for (auto* character : characters) gameWindow2.draw(character->getDrawable());
    gameWindow2.display();
}

sf::RenderWindow levelWindow3(sf::VideoMode(1536, 1024), "Level 3");
sf::Texture level3Texture;
if (!level3Texture.loadFromFile("level_3.png")) return -1;
sf::Sprite level3Background(level3Texture);

auto newAntTexture = std::make_shared<sf::Texture>();
if (!newAntTexture->loadFromFile("mrowka22.png")) {
    std::cerr << "B³¹d: Nie uda³o siê wczytaæ tekstury mrowka22.png!" << std::endl;
    return -1;
}

sf::Clock level3Clock;

while (levelWindow3.isOpen())
{
    sf::Event level3Event;
    while (levelWindow3.pollEvent(level3Event)) {
        if (level3Event.type == sf::Event::Closed) {
            levelWindow3.close();
        }
    }

    if (level3Clock.getElapsedTime().asSeconds() >= 2.f) {
        levelWindow3.close();
    }

    levelWindow3.clear();
    levelWindow3.draw(level3Background);
    levelWindow3.display();
}

sf::RenderWindow gameWindow3(sf::VideoMode(1536, 1024), "SFML Game");

auto antTexture3 = std::make_shared<sf::Texture>();
if (!antTexture3->loadFromFile("bossMrowka.png")) {
    std::cerr << "B³¹d: Nie uda³o siê wczytaæ tekstury bossMrowka.png!" << std::endl;
    return -1;
}

sf::Texture backgroundTexture3;
if (!backgroundTexture3.loadFromFile("mapa3.png")) {
    std::cerr << "B³¹d: Nie uda³o siê wczytaæ t³a mapa3.png!" << std::endl;
    return -1;
}
sf::Sprite background3(backgroundTexture3);

std::vector<Ant> ants3;
float randX = static_cast<float>(rand() % gameWindow3.getSize().x);
float randY = static_cast<float>(rand() % gameWindow3.getSize().y);
ants3.emplace_back(antTexture3, &gameWindow3, sf::Vector2f(randX, randY), 3);

ants3.back().getSprite().setScale(0.3f, 0.3f);
ants3.back().setSpeed(800.f);

sf::Clock smallAntSpawnClock;
bool isBigAntDead = ants3.empty();
sf::Clock endGameClock;
bool waitingForEndGame = false;

while (gameWindow3.isOpen())
{
    float deltaTime = clock.restart().asSeconds();

    sf::Event event;
    while (gameWindow3.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            gameWindow3.close();
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && shootClock.getElapsedTime().asSeconds() >= 0.5f) {
            sf::FloatRect bounds = mage.getSprite().getGlobalBounds();
            sf::Vector2f start(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);

            Direction dir = mage.getLastDirection();
            std::shared_ptr<sf::Texture> tex = (rand() % 2 == 0) ? tex1 : tex2;

            projectiles.emplace_back(tex, start, dir);
            shootClock.restart();
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && shootClockArcher.getElapsedTime().asSeconds() >= 0.5f) {
            sf::FloatRect bounds = archer.getSprite().getGlobalBounds();
            sf::Vector2f start(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2);

            Direction dir = archer.getLastDirection();
            projectiles.emplace_back(texArrow, start, dir);
            shootClockArcher.restart();
        }
    }

    bool isBigAntDead = ants3.empty() || ants3[0].isDead();

    if (isBigAntDead && !waitingForEndGame) {
        endGameClock.restart();
        waitingForEndGame = true;
    }

    if (waitingForEndGame && endGameClock.getElapsedTime().asSeconds() >= 3.f) {
        gameWindow3.close();
    }

    if (waitingForEndGame) {
        sf::RenderWindow endWindow(sf::VideoMode(1536, 1024), "Game Over");

        sf::Texture endTexture;
        if (!endTexture.loadFromFile("end.png")) return -1;
        sf::Sprite endBackground(endTexture);

        sf::Clock endClock;
        while (endWindow.isOpen()) {
            sf::Event endEvent;
            while (endWindow.pollEvent(endEvent)) {
                if (endEvent.type == sf::Event::Closed) {
                    endWindow.close();
                }
            }

            if (endClock.getElapsedTime().asSeconds() >= 2.f) {
                endWindow.close();
            }

            endWindow.clear();
            endWindow.draw(endBackground);
            endWindow.display();
        }

        return 0;
    }

    if (!isBigAntDead && smallAntSpawnClock.getElapsedTime().asSeconds() >= 2.f) {
        float randX = static_cast<float>(rand() % gameWindow3.getSize().x);
        float randY = static_cast<float>(rand() % gameWindow3.getSize().y);

        Ant smallAnt(newAntTexture, &gameWindow3, sf::Vector2f(randX, randY), 1);
        smallAnt.setSpeed(400.f);

        ants3.push_back(smallAnt);

        smallAntSpawnClock.restart();
    }

    for (auto* character : characters) character->poruszanie(deltaTime);
    for (auto& p : projectiles) p.update(deltaTime);
    for (auto& ant : ants3) ant.poruszanie(deltaTime);

    for (auto it = projectiles.begin(); it != projectiles.end();) {
        bool removed = false;

        for (auto jt = ants3.begin(); jt != ants3.end();) {
            if (it->getBounds().intersects(jt->getSprite().getGlobalBounds())) {
                jt->incrementHitCount();
                if (jt->isDead()) {
                    it = projectiles.erase(it);
                    jt = ants3.erase(jt);
                    removed = true;
                    break;
                } else {
                    it = projectiles.erase(it);
                    removed = true;
                    break;
                }
            } else {
                ++jt;
            }
        }

        if (!removed) {
            ++it;
        }
    }

    projectiles.erase(
        std::remove_if(projectiles.begin(), projectiles.end(),
            [&gameWindow3](const Projectile& p) {
                auto b = p.getBounds();
                return b.left > gameWindow3.getSize().x || b.left + b.width < 0 ||
                       b.top > gameWindow3.getSize().y || b.top + b.height < 0;
            }),
        projectiles.end()
    );

    for (auto& ant : ants3) {
        if (ant.checkCollision(mage.getSprite()) && mageTouches < 3) {
            if (mageTouchClock.getElapsedTime().asSeconds() >= 2.f) {
                for (auto& heart : mageHearts) {
                    if (!heart.isGray) {
                        heart.changeToGray(grayHeartTexture);
                        mageTouches++;
                        mageTouchClock.restart();
                        break;
                    }
                }
            }
        }
        if (ant.checkCollision(archer.getSprite()) && archerTouches < 3) {
            if (archerTouchClock.getElapsedTime().asSeconds() >= 2.f) {
                for (auto& heart : archerHearts) {
                    if (!heart.isGray) {
                        heart.changeToGray(grayHeartTexture);
                        archerTouches++;
                        archerTouchClock.restart();
                        break;
                    }
                }
            }
        }
    }

    projectiles.erase(
        std::remove_if(projectiles.begin(), projectiles.end(),
            [&gameWindow3](const Projectile& p) {
                auto b = p.getBounds();
                return b.left > gameWindow3.getSize().x || b.left + b.width < 0 ||
                    b.top > gameWindow3.getSize().y || b.top + b.height < 0;
            }),
        projectiles.end()
    );

    if (checkGameOver(gameWindow3, mageHearts, archerHearts)) {return 0;}

    gameWindow3.clear();
    gameWindow3.draw(background3);

    for (auto& ant : ants3)
    {
        ant.drawHealthBar(gameWindow3);
        gameWindow3.draw(ant.getDrawable());
    }
    for (auto& heart : mageHearts){gameWindow3.draw(heart.getDrawable());}
    for (auto& heart : archerHearts){gameWindow3.draw(heart.getDrawable());}
    for (auto& p : projectiles){gameWindow3.draw(p.getDrawable());}
    for (auto* character : characters){gameWindow3.draw(character->getDrawable());}
    gameWindow3.display();
}
    }}
}
