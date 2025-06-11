#include <SFML/Graphics.hpp>
#include <windows.h>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <iostream>

struct Ant {
    sf::Sprite sprite;
    sf::Vector2f velocity;
    bool hasFood = false;
    int carryingFoodType = 0;
    float speedMultiplier = 3.0f;
};

struct Food {
    sf::Sprite sprite;
    int foodType;
};

class AntSimulation {
public:
    AntSimulation();
    void run();
    bool isSimulationEnded() const;

private:
    sf::RenderWindow window;
    sf::Texture backgroundTexture, antTexture1, antTexture2, antTexture3;
    sf::Texture foodTexture1, foodTexture2, nestTexture, spiderTexture;
    sf::Sprite background, nest, spider;
    sf::Vector2f spiderVelocity;
    std::vector<Ant> ants;
    std::vector<Food> foods;
    bool simulationEnded;

    sf::Clock simulationClock;
    sf::Font font;
    sf::Text timerText;
    sf::Text antCounterText;

    void loadTextures();
    void initializeObjects();
    void updateAnts();
    void updateSpider();
    void render();
    void initializeUI();
};
