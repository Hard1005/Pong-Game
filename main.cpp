#include <iostream>
#include <sstream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Collision.h"
int main()
{

srand((int)time(0));

//States
bool up=false, down=false;
bool paused = true;

//Variables
float Upad_velocity = 0;
float AIpad_velocity = 0;
float Ball_xvelocity = 0.0;
float Ball_yvelocity = 0.0;
float Ball_cxvelocity = 2.5;
float Ball_cyvelocity = 2.5;
int u=0,ai=0;

//Texture
sf::Texture Upad_tex;
Upad_tex.loadFromFile("Data/Upad_texture_1.png");
sf::Texture AIpad_tex;
AIpad_tex.loadFromFile("Data/AIpad_texture_1.png");
sf::Texture BG_texture;
BG_texture.loadFromFile("Data/Background_1.png");
sf::Texture Ball_tex;
Ball_tex.loadFromFile("Data/Ball_texture1.png");

//Shapes
sf::RectangleShape BG(sf::Vector2f(800,600));
BG.setTexture(&BG_texture);



//Sprites
sf::Sprite ball;
ball.setTexture(Ball_tex);
ball.setOrigin(200,200);
ball.setScale(0.0950,0.0950);
ball.setPosition(400,300);

sf::Sprite Upad;
Upad.setTexture(AIpad_tex);
Upad.setScale(0.2,1.3);
Upad.setOrigin(0,47);

sf::Sprite AIpad;
AIpad.setTexture(AIpad_tex);
AIpad.setScale(0.2,1.3);
AIpad.setOrigin(0,47);
Upad.setPosition(10,300);
AIpad.setPosition(770,300);


//Fonts
sf::Font score;
score.loadFromFile("Data/dacasa.ttf");

//Text
sf::Text scoreboard;
scoreboard.setFont(score);
scoreboard.setString("0 - 0");
scoreboard.setPosition(398,0);
scoreboard.setColor(sf::Color(0,50,200));

sf::Text msg;
msg.setFont(score);
msg.setString("! Press Enter To Start !");
msg.setColor(sf::Color::White);
msg.setCharacterSize(40);
msg.setPosition(210,200);
msg.setOutlineThickness(1);
msg.setOutlineColor(sf::Color::Red);


//Sounds
sf::SoundBuffer hit;
hit.loadFromFile("Data/hit.wav");
sf::SoundBuffer point;
point.loadFromFile("Data/point.wav");

sf::Sound hit_sound;
hit_sound.setBuffer(hit);
hit_sound.setVolume(70);
sf::Sound point_sound;
point_sound.setBuffer(point);
point_sound.setVolume(70);

//Music
sf::Music BGM;
BGM.openFromFile("Data/BGM.wav");
BGM.setLoop(true);
BGM.setVolume(40);
BGM.play();

    sf::RenderWindow win(sf::VideoMode(800,600),"It's The PONG Game.");
    sf::Event eve;
    win.setFramerateLimit(60);
    while(win.isOpen())
    {
        while(win.pollEvent(eve))
        {
            if(eve.type == sf::Event::Closed)
            {
                win.close();
            }
            if(eve.type == sf::Event::KeyPressed)
            {
                if(eve.key.code == sf::Keyboard::Up)up=true;
                if(eve.key.code == sf::Keyboard::Down)down= true;
            }
            if(eve.type == sf::Event::KeyReleased)
            {
                if(eve.key.code == sf::Keyboard::Up)up=false;
                if(eve.key.code == sf::Keyboard::Down)down= false;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                paused = false;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                paused = true;
            }

        }



        //Logic

        if(!paused)
        {
            if(up == true)
        {
            Upad_velocity =-4;
            Upad.move(0,Upad_velocity);
        }
        if(down == true)
        {
            Upad_velocity = 4;
            Upad.move(0,Upad_velocity);
        }

        if(Upad.getPosition().y < 0)
        {
            Upad.move(0,-Upad_velocity);
        }
        if(Upad.getPosition().y > 600)
        {
            Upad.move(0,-Upad_velocity);
        }
        if(ball.getPosition().y > 580)
        {
            Ball_cyvelocity = -Ball_cyvelocity;
            Ball_yvelocity = -Ball_yvelocity;
        }
        if(ball.getPosition().y < 20)
        {
            Ball_cyvelocity = -Ball_cyvelocity;
            Ball_yvelocity = -Ball_yvelocity;
        }

        if(ball.getPosition().y < AIpad.getPosition().y && Ball_cxvelocity > 0)
        {
            AIpad_velocity = -3;
            AIpad.move(0,AIpad_velocity);
        }
        else
        {
            int no = (rand()%2);
            if(no == 0)
            {
                AIpad_velocity += 0.2;
            }
            else
            {
                AIpad_velocity -= 0.2;
            }

        }
        if(ball.getPosition().y > AIpad.getPosition().y && Ball_cxvelocity > 0)
        {
            AIpad_velocity = 3;
            AIpad.move(0,AIpad_velocity);
        }
        else
        {
            int no = (rand()%2);
            if(no == 0)
            {
                AIpad_velocity += 0.2;
            }
            else
            {
                AIpad_velocity -= 0.2;
            }
            AIpad.move(0,AIpad_velocity);

        }
        if(AIpad.getPosition().y < 0)
        {
            AIpad_velocity = -AIpad_velocity;
            AIpad.move(0,AIpad_velocity);
        }
        if(AIpad.getPosition().y > 600)
        {
            AIpad_velocity = -AIpad_velocity;
            AIpad.move(0,AIpad_velocity);
        }

        if(Collision::PixelPerfectTest(Upad,ball))
        {
            Ball_cxvelocity = -Ball_cxvelocity + 0.19;
            Ball_xvelocity = -Ball_xvelocity;
            hit_sound.play();
            if(Ball_cyvelocity < 0)
                Ball_cyvelocity -= 0.2;
            else
                Ball_cyvelocity += 0.2;

        }
        if(Collision::PixelPerfectTest(AIpad,ball))
        {
            Ball_cxvelocity = -Ball_cxvelocity -0.19;
            Ball_xvelocity = -Ball_xvelocity;
            hit_sound.play();
            if(Ball_cyvelocity < 0)
                Ball_cyvelocity -= 0.2;
            else
                Ball_cyvelocity += 0.2;
        }
        if(ball.getPosition().x<10)
        {
            point_sound.play();
            ai++;
            ball.setPosition(400,300);
            Ball_xvelocity = 0.0;
            Ball_yvelocity = 0.0;
            Ball_cxvelocity = 2.5;
            Ball_cyvelocity = -2.5;
            std::stringstream strr;
            strr <<u<<" - "<<ai;
            scoreboard.setString(strr.str());
        }
        if(ball.getPosition().x > 790)
        {
            point_sound.play();
            u++;
            ball.setPosition(400,300);
            Ball_xvelocity = 0.0;
            Ball_yvelocity = 0.0;
            Ball_cxvelocity = -2.5;
            Ball_cyvelocity = 2.5;
            std::stringstream strr;
            strr <<u<<" - "<<ai;
            scoreboard.setString(strr.str());
        }
        ball.move(Ball_cxvelocity+Ball_xvelocity,Ball_cyvelocity+Ball_yvelocity);
        ball.rotate(1);
        }


        //Drawing part
        win.clear();
        win.draw(BG);
        win.draw(ball);
        if(paused)
        {
            win.draw(msg);
        }
        win.draw(scoreboard);
        win.draw(Upad);
        win.draw(AIpad);
        win.display();
    }
    return 0;
}
