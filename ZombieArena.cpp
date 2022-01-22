#include "Player.h"
#include "SFML/Graphics.hpp"
#include "ZombieArena.h"

using namespace sf;

int main()
{
    // Game state
    enum class State
    {
        PAUSED,
        LEVELING_UP,
        GAME_OVER,
        PLAYING
    };

    State state = State::GAME_OVER;

    // Get the screen resolution
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie Arena", Style::Fullscreen);

    // Create a an SFML View for the main action
    View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

    Clock clock;

    Time gameTimeTotal;

    // Mouse world cordinate
    Vector2f mouseWorldPositions;
    // Mouse screen cordinate
    Vector2i mouseScreenPosition;

    Player player;

    // The boundaries of the arena
    IntRect arena;

    // Create background
    VertexArray background;
    // Load the texture for our backgroung vertex array
    Texture textureBackground;
    textureBackground.loadFromFile("graphics/background_sheet.png");

    // game Loop
    while (window.isOpen())
    {
        // Handle input
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Return && state == State::PLAYING)
                {
                    state = State::PAUSED;
                }

                else if (event.key.code == Keyboard::Return && state == State::PAUSED)
                {
                    state = State::PLAYING;
                    clock.restart();
                }

                else if (event.key.code == Keyboard::Return && state == State::GAME_OVER)
                {
                    state = State::LEVELING_UP;
                }

                if (state == State::PLAYING)
                {
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        if (state == State::PLAYING)
        {
            // Controll WASD
            if (Keyboard::isKeyPressed(Keyboard::W))
            {
                player.moveUp();
            }
            else
            {
                player.stopUp();
            }

            if (Keyboard::isKeyPressed(Keyboard::S))
            {
                player.moveDown();
            }
            else
            {
                player.stopDown();
            }

            if (Keyboard::isKeyPressed(Keyboard::A))
            {
                player.moveLeft();
            }
            else
            {
                player.stopLeft();
            }

            if (Keyboard::isKeyPressed(Keyboard::D))
            {
                player.moveRight();
            }
            else
            {
                player.stopRight();
            }
        } // End Controll WASD

        // Handle the LEVELINH up state
        if (state == State::LEVELING_UP)
        {
            // Handele the player Leveling up
            if (event.key.code == Keyboard::Num1)
            {
                state = State::PLAYING;
            }

            if (event.key.code == Keyboard::Num2)
            {
                state = State::PLAYING;
            }

            if (event.key.code == Keyboard::Num3)
            {
                state = State::PLAYING;
            }

            if (event.key.code == Keyboard::Num4)
            {
                state = State::PLAYING;
            }

            if (event.key.code == Keyboard::Num5)
            {
                state = State::PLAYING;
            } 

            if (Keyboard::isKeyPressed(Keyboard::Num6)) // bug event.key.code == Keyboard::Num5 coincide with space ascii 32
            {
                state = State::PLAYING;
            }

            if (state == State::PLAYING)
            {
                // Prepare the level
                arena.width = 500;
                arena.height = 500;
                arena.left = 0;
                arena.top = 0;

                //int tileSize = 50;
                int tileSize = createBackground(background, arena);
                player.spawn(arena, resolution, tileSize);
                // Reset the clock so there isn't a frame jump
                clock.restart();
            }
        } // End Leveling up

        // Update the frame
        if (state == State::PLAYING)
        {
            // Update the delta time
            Time dt = clock.restart();
            gameTimeTotal += dt;

            float dtAsSeconnds = dt.asSeconds();

            mouseScreenPosition = Mouse::getPosition();
            // Convert mouse position to world coordinates of mainView
            mouseWorldPositions = window.mapPixelToCoords(Mouse::getPosition(), mainView);

            // Update the player
            player.update(dtAsSeconnds, Mouse::getPosition());

            // Make a note of the players new position
            Vector2f playerPosition(player.getCenter());

            // Make the view centre around the player
            mainView.setCenter(player.getCenter());
        } // End updating the scene

        // Draw the scene
        if (state == State::PLAYING)
        {
            window.clear();
            window.setView(mainView);

            // Draw the background
            window.draw(background, &textureBackground);

            window.draw(player.getSprite());
        }

        if (state == State::LEVELING_UP)
        {
        }

        if (state == State::PAUSED)
        {
        }

        if (state == State::GAME_OVER)
        {
        }

        window.display();

    } // End game loop

    return 0;
}
