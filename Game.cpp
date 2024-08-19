#include "Game.h"

Game::Game():
    window{
        sf::VideoMode(window_width, window_height), 
        "My First Game"
    },
    fence{}
{
    window.clear(window_color);
    window.setPosition(sf::Vector2i(0, 0));
}

// Game::~Game()
// {

// }

void Game::run()
{
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

        window.draw(white_king.get_king());
        window.draw(white_king.get_throne());
        window.draw(black_king.get_king());
        window.draw(black_king.get_throne());
        window.draw(fence);
        
        window.display();
    }
}