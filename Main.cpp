#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <stdio.h>
using namespace std;
using namespace sf;

int main()
{   
    RenderWindow window(VideoMode(800, 600), "Game", Style::Titlebar | Style::Close);
    srand(time(0));
    Texture PlayerIdle, ENEMY,bg;
    PlayerIdle.loadFromFile("Texture/PlayerIdle.png");
    ENEMY.loadFromFile("Texture/ENEMY.png");
    bg.loadFromFile("Texture/bg.png");
    Sprite player,enemy[5],BG;
    struct enemy {
        int left;
        int up;
    }enemy_stat[5];
   
    player.setScale(3, 3);   
    player.setTexture(PlayerIdle);
    player.setOrigin(Vector2f(player.getTexture()->getSize().x*0.5, player.getTexture()->getSize().y*0.5));
    BG.setScale(1.3f,1.f);
    BG.setTexture(bg);
    const float PI = 3.14159265;
 
    player.setPosition(600, 500);
    
    for (int i = 0;i < 5;i++) {
        
        enemy[i].setScale(3, 3);
        enemy[i].setTexture(ENEMY);
        enemy[i].setPosition(rand()%701, 0);
        window.draw(enemy[i]);
        enemy_stat[i].left = rand() % 2;
        enemy_stat[i].up = rand() % 2;
    }

    while (window.isOpen())
    {
        Event ev;
        while (window.pollEvent(ev))
        {
            if (ev.type == Event::Closed)
                window.close();
        }
        
        if (Keyboard::isKeyPressed(Keyboard::Key::A) && player.getPosition().x > 0 ) { player.move(-0.2, 0); }
        if (Keyboard::isKeyPressed(Keyboard::Key::D) && player.getPosition().x < 800 ) { player.move(0.2, 0); }
        if (Keyboard::isKeyPressed(Keyboard::Key::W) && player.getPosition().y > 0 ) { player.move(0, -0.15); }
        if (Keyboard::isKeyPressed(Keyboard::Key::S) && player.getPosition().y < 600 ) { player.move(0, 0.15); }

        Vector2f curPos = player.getPosition();
        Vector2i position = sf::Mouse::getPosition(window);

        float dx = curPos.x - position.x;
        float dy = curPos.y - position.y;
        player.setRotation(((atan2(dy, dx)) * 180 / PI) + 180);



       
        window.clear();
        
        window.draw(BG);
        window.draw(player);
        for (int j = 0;j < 5;j++)
        {
           
            if (enemy_stat[j].left == 0 && enemy[j].getPosition().x < 750) { enemy[j].move(0.1, 0); }
            else if (enemy[j].getPosition().x >= 750) { enemy_stat[j].left = 1; }
            if (enemy_stat[j].left == 1 && enemy[j].getPosition().x > 0) { enemy[j].move(-0.1, 0); }
            else if (enemy[j].getPosition().x <= 0) { enemy_stat[j].left = 0; }
            if (enemy_stat[j].up == 0 && enemy[j].getPosition().y < 250) { enemy[j].move(0, 0.1); }
            else if (enemy[j].getPosition().y >= 250) { enemy_stat[j].up = 1; }
            if (enemy_stat[j].up == 1 && enemy[j].getPosition().y > 0) { enemy[j].move(0, -0.1); }
            else if (enemy[j].getPosition().y <= 0) { enemy_stat[j].up = 0; }
            window.draw(enemy[j]);
        }
      
        window.display();
        
    }
    return 0;
}