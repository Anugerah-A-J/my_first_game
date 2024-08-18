#include <SFML/Graphics.hpp>

int main()
{
    auto window_width{1900};
    auto window_height{950};
    auto space{20.f};
    auto line_width{2.f};
    auto radius{5.f};
    sf::Color window_color{17, 17, 17, 255};

    // sf::RenderWindow window(sf::VideoMode(1000, 1000), "My First Game");
    sf::RenderWindow window{
        sf::VideoMode(window_width, window_height), 
        "My First Game"
    };
    // 255 = 3 * 5 * 17
    // 255 = 3 * 85
    // 255 = 5 * 51
    window.clear(window_color);
    window.setPosition(sf::Vector2i(0, 0));
    
    sf::RectangleShape border{sf::Vector2f(
        window_width - 4 * space,
        window_height - 2 * space
    )};
    border.move(2 * space, space);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(line_width);
    border.setOutlineColor(sf::Color::Red);

    sf::CircleShape White_boss{radius};
    White_boss.move(
        space + border.getSize().x - radius - line_width,
        border.getSize().y / 2 + space - line_width
    );
    White_boss.setFillColor(sf::Color::White);
    White_boss.setOutlineThickness(line_width);
    White_boss.setOutlineColor(sf::Color::White);

    sf::CircleShape Black_boss{radius};
    Black_boss.move(
        3 * space - line_width,
        border.getSize().y / 2 + space - line_width
    );
    Black_boss.setFillColor(sf::Color::Transparent);
    Black_boss.setOutlineThickness(line_width);
    Black_boss.setOutlineColor(sf::Color::White);

    sf::RectangleShape White_boss_house{sf::Vector2f(
        White_boss.getRadius() + 2 * space,
        White_boss.getRadius() + 2 * space
    )};
    White_boss_house.move(
        White_boss.getPosition().x 
        + White_boss.getRadius() - White_boss_house.getSize().x / 2,

        White_boss.getPosition().y 
        + White_boss.getRadius() - White_boss_house.getSize().y / 2
    );
    White_boss_house.setFillColor(sf::Color::Transparent);
    White_boss_house.setOutlineThickness(line_width);
    White_boss_house.setOutlineColor(sf::Color::White);

    sf::RectangleShape Black_boss_house{sf::Vector2f(
        Black_boss.getRadius() + 2 * space,
        Black_boss.getRadius() + 2 * space
    )};
    Black_boss_house.move(
        Black_boss.getPosition().x 
        + Black_boss.getRadius() - Black_boss_house.getSize().x / 2,

        Black_boss.getPosition().y 
        + Black_boss.getRadius() - Black_boss_house.getSize().y / 2
    );
    Black_boss_house.setFillColor(sf::Color::Transparent);
    Black_boss_house.setOutlineThickness(line_width);
    Black_boss_house.setOutlineColor(sf::Color::White);
    
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized)
                window.setView(
                    sf::View(
                        sf::FloatRect(
                            0, 0, event.size.width, event.size.height
                        )
                    )
                );
        }

        sf::Vector2i mouse_position = sf::Mouse::getPosition(window);

        window.clear(window_color);

        window.draw(White_boss_house);
        window.draw(Black_boss_house);
        window.draw(border);
        window.draw(White_boss);
        window.draw(Black_boss);
        
        window.display();
    }

    return 0;
}