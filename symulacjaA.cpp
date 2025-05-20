#include "symulacjaA.h"

AntSimulation::AntSimulation() : window(sf::VideoMode(1535, 1024), "Symulacja Kolonii Mrowek"), spiderVelocity(0.5f, 0.5f), simulationEnded(false)
{
    window.setFramerateLimit(60);

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    try
    {
        loadTextures();
        initializeObjects();
        initializeUI();
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << "Blad inicjalizacji: " << e.what() << std::endl;
        window.close();
    }
}

void AntSimulation::loadTextures()
{
    if (!backgroundTexture.loadFromFile("background.png") ||
        !antTexture1.loadFromFile("ant1.png") ||
        !antTexture2.loadFromFile("ant2.png") ||
        !antTexture3.loadFromFile("ant3.png") ||
        !foodTexture1.loadFromFile("food1.png") ||
        !foodTexture2.loadFromFile("food2.png") ||
        !nestTexture.loadFromFile("nest.png") ||
        !spiderTexture.loadFromFile("spider.png"))
      {
        throw std::runtime_error("Nie udało się załadować tekstur");
      }

    if (!font.loadFromFile("Arial-ItalicMT.ttf"))
      {
        throw std::runtime_error("Nie udalo się zaladowac czcionki Arial-ItalicMT.ttf");
      }
}

void AntSimulation::initializeObjects()
 {
    background.setTexture(backgroundTexture);
    background.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y);

    nest.setTexture(nestTexture);
    nest.setScale(0.04f, 0.04f);
    nest.setPosition(
    window.getSize().x / 2.0f - nest.getGlobalBounds().width / 2.0f,
    window.getSize().y / 2.0f - nest.getGlobalBounds().height / 2.0f
);

    spider.setTexture(spiderTexture);
    spider.setScale(0.08f, 0.08f);
    spider.setPosition(
    std::rand() % (window.getSize().x - 40) + 10,
    std::rand() % (window.getSize().y - 40) + 10
);

    foods.resize(3);
    for (auto &food : foods)
    {
        int randomType = std::rand() % 2 + 1;
        food.foodType = randomType;
        food.sprite.setTexture(randomType == 1 ? foodTexture1 : foodTexture2);
        food.sprite.setScale(0.15f, 0.15f);
        food.sprite.setPosition(
        std::rand() % (window.getSize().x - 40) + 10,
        std::rand() % (window.getSize().y - 40) + 10
        );
    }

    Ant initialAnt;
    initialAnt.sprite.setTexture(antTexture1);
    initialAnt.sprite.setScale(0.2f, 0.2f);
    initialAnt.sprite.setPosition(400, 300);
    initialAnt.velocity = sf::Vector2f((std::rand() % 3 - 1) * 0.5f, (std::rand() % 3 - 1) * 0.5f);
    ants.push_back(initialAnt);
}

void AntSimulation::initializeUI()
{
    timerText.setFont(font);
    timerText.setCharacterSize(24);
    timerText.setFillColor(sf::Color::Black);
    timerText.setPosition(10, 10);

    antCounterText.setFont(font);
    antCounterText.setCharacterSize(24);
    antCounterText.setFillColor(sf::Color::Black);
    antCounterText.setPosition(10, 40);
}

bool AntSimulation::isSimulationEnded() const
{
    return simulationEnded;
}

void AntSimulation::run()
{
    PlaySound(TEXT("muzyka.wav"), NULL, SND_ASYNC | SND_LOOP);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        updateAnts();
        updateSpider();


        sf::Time elapsedTime = simulationClock.getElapsedTime();
        int seconds = static_cast<int>(elapsedTime.asSeconds());
        timerText.setString("Czas: " + std::to_string(seconds) + " s");


        antCounterText.setString("Mrowki: " + std::to_string(ants.size()));


        if (ants.empty() || ants.size() > 30)
          {
            simulationEnded = true;
            window.close();
          }

        render();
    }

    PlaySound(NULL, NULL, SND_ASYNC);
}

void AntSimulation::updateAnts()
{
    for (auto &ant : ants)
        {
        if (!ant.hasFood)
        {
            ant.velocity.x += (std::rand() % 3 - 1) * 0.05f;
            ant.velocity.y += (std::rand() % 3 - 1) * 0.05f;

            float speed = std::sqrt(ant.velocity.x * ant.velocity.x + ant.velocity.y * ant.velocity.y);
            if (speed > 1.0f)
             {
                ant.velocity /= speed;
             }

            ant.sprite.move(ant.velocity * ant.speedMultiplier);

            if (ant.sprite.getPosition().x < 0 || ant.sprite.getPosition().x > 1535  )
              {
                ant.velocity.x = -ant.velocity.x;
              }
            if (ant.sprite.getPosition().y < 0 || ant.sprite.getPosition().y > 1024)
              {
                ant.velocity.y = -ant.velocity.y;
              }

            for (auto &food : foods)
              {
                if (ant.sprite.getGlobalBounds().intersects(food.sprite.getGlobalBounds()))
                {
                    ant.hasFood = true;
                    ant.carryingFoodType = food.foodType;
                    ant.velocity = sf::Vector2f(0, 0);
                    ant.speedMultiplier = 2.0f;

                    food.foodType = std::rand() % 2 + 1;
                    food.sprite.setTexture(food.foodType == 1 ? foodTexture1 : foodTexture2);
                    food.sprite.setPosition(std::rand() % 780 + 10, std::rand() % 580 + 10);
                    break;
                }
            }
        }
        else
            {
            sf::Vector2f nestCenter = nest.getPosition() + sf::Vector2f(nest.getGlobalBounds().width / 2.0f, nest.getGlobalBounds().height / 2.0f);
            sf::Vector2f direction = nestCenter - ant.sprite.getPosition();
            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            if (length > 1)
             {
                direction /= length;
                ant.sprite.move(direction * 1.0f * ant.speedMultiplier);
             }
            else
                {
                ant.hasFood = false;
                ant.speedMultiplier = 1.0f;

                int antsToAdd = (ant.carryingFoodType == 1) ? 1 : 2;
                for (int j = 0; j < antsToAdd; ++j)
                    {
                    Ant newAnt;
                    int randomTexture = std::rand() % 3;
                    if (randomTexture == 0)
                    {
                        newAnt.sprite.setTexture(antTexture1);
                    } else if (randomTexture == 1)
                     {
                        newAnt.sprite.setTexture(antTexture2);
                     } else
                     {
                        newAnt.sprite.setTexture(antTexture3);
                     }

                    newAnt.sprite.setScale(0.1f, 0.1f);
                    sf::Vector2f nestCenter = nest.getPosition() + sf::Vector2f(nest.getGlobalBounds().width / 2.0f, nest.getGlobalBounds().height / 2.0f);
                    newAnt.sprite.setPosition(nestCenter);
                    newAnt.velocity = sf::Vector2f((std::rand() % 3 - 1) * 0.5f, (std::rand() % 3 - 1) * 0.5f);
                    ants.push_back(newAnt);
                }

                ant.carryingFoodType = 0;
            }
        }
    }
}

void AntSimulation::updateSpider()
{
    spider.move(spiderVelocity);
    if (spider.getPosition().x < 0 || spider.getPosition().x > 1535  - spider.getGlobalBounds().width)
      {
        spiderVelocity.x = -spiderVelocity.x;
      }
    if (spider.getPosition().y < 0 || spider.getPosition().y > 1024 - spider.getGlobalBounds().height)
      {
        spiderVelocity.y = -spiderVelocity.y;
      }

    ants.erase(std::remove_if(ants.begin(), ants.end(), [&](const Ant &ant)
    {
        return spider.getGlobalBounds().intersects(ant.sprite.getGlobalBounds());
    }
    ), ants.end());
}

void AntSimulation::render()
{
    window.clear(sf::Color::White);
    window.draw(background);
    window.draw(nest);
    for (const auto &food : foods)
      {
        window.draw(food.sprite);
      }
    for (const auto &ant : ants)
      {
        window.draw(ant.sprite);
      }
    window.draw(spider);


    window.draw(timerText);
    window.draw(antCounterText);

    window.display();
}
