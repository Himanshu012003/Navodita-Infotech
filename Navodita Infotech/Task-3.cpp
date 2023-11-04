#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;

// Constants
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float BALL_RADIUS = 10.0f;
const float PADDLE_WIDTH = 10.0f;
const float PADDLE_HEIGHT = 100.0f;
const float BALL_SPEED = 200.0f;
const float PADDLE_SPEED = 250.0f;

int main() {
    // Create the game window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pong Game");
    window.setFramerateLimit(60);

    // Create the ball
    sf::CircleShape ball(BALL_RADIUS);
    ball.setFillColor(sf::Color::White);
    ball.setPosition(WINDOW_WIDTH / 2 - BALL_RADIUS, WINDOW_HEIGHT / 2 - BALL_RADIUS);
    float ballXSpeed = BALL_SPEED;
    float ballYSpeed = BALL_SPEED;

    // Create the paddles
    sf::RectangleShape leftPaddle(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
    leftPaddle.setFillColor(sf::Color::White);
    leftPaddle.setPosition(20, (WINDOW_HEIGHT - PADDLE_HEIGHT) / 2);
    float leftPaddleSpeed = 0.0f;

    sf::RectangleShape rightPaddle(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
    rightPaddle.setFillColor(sf::Color::White);
    rightPaddle.setPosition(WINDOW_WIDTH - 20 - PADDLE_WIDTH, (WINDOW_HEIGHT - PADDLE_HEIGHT) / 2);
    float rightPaddleSpeed = 0.0f;

    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Handle user input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            leftPaddleSpeed = -PADDLE_SPEED;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            leftPaddleSpeed = PADDLE_SPEED;
        else
            leftPaddleSpeed = 0.0f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            rightPaddleSpeed = -PADDLE_SPEED;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            rightPaddleSpeed = PADDLE_SPEED;
        else
            rightPaddleSpeed = 0.0f;

        // Update ball position
        float deltaTime = 1.0f / 60.0f;
        ball.move(ballXSpeed * deltaTime, ballYSpeed * deltaTime);

        // Ball collisions
        if (ball.getPosition().y < 0 || ball.getPosition().y > WINDOW_HEIGHT - 2 * BALL_RADIUS)
            ballYSpeed = -ballYSpeed;

        if (ball.getGlobalBounds().intersects(leftPaddle.getGlobalBounds()) || ball.getGlobalBounds().intersects(rightPaddle.getGlobalBounds()))
            ballXSpeed = -ballXSpeed;

        // Ball out of bounds
        if (ball.getPosition().x < 0 || ball.getPosition().x > WINDOW_WIDTH)
            window.close(); // Game over

        // Update paddles position
        leftPaddle.move(0.0f, leftPaddleSpeed * deltaTime);
        rightPaddle.move(0.0f, rightPaddleSpeed * deltaTime);

        // Clear the window
        window.clear(sf::Color::Black);

        // Draw game objects
        window.draw(leftPaddle);
        window.draw(rightPaddle);
        window.draw(ball);

        // Display everything
        window.display();
    }

    return 0;
}
