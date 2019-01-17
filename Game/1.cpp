#include<SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <SFML/Audio.hpp>
#include "menu.h"
//#include "bomb.h"
//#include "game.h"
#include "Collision.h"
#include <bits/stdc++.h>

using namespace std;
using namespace sf;

vector< pair <int,int> > vect1;
int bombNum = 0;
int bombAra[5];

 int swap_devil_y=3;
 int dir_x=0,dir_y=0.05;

class classBomb
{
public:
    Sprite spriteBomb;
    Sprite spriteExplosion;
    Clock exClock;
    float exTime = 0.0f;
    void initBomb(Texture *texture,Texture *textureBomb)
    {
        exTime = exClock.getElapsedTime().asSeconds();
        spriteBomb.setTexture(*texture);
        spriteBomb.setPosition(-200, -200);

        spriteExplosion.setTexture(*textureBomb);
        spriteExplosion.setScale(0.1689f,0.1451475f);
        //spriteExplosion.setPosition(x-14.25,y-12.5);

    }

    void setPos(int x, int y){
        spriteBomb.setPosition(x, y);
    }
};

int main()
{
    srand(time(NULL));
    RenderWindow window;
    window.create(VideoMode(925,600),"Bomber Friends");
    enum Direction{Down,Left,Right,Up};
    sf::Vector2i player(1,Down);
    ///TEXT
    Text goalTxt,gameovertxt;
    Font goalfont,gameoverfont;

    goalfont.loadFromFile("data/font/Goals.ttf");
    gameoverfont.loadFromFile("data/font/gameover.ttf");

    goalTxt.setFont(goalfont);
    goalTxt.setString("GOALS :");
    goalTxt.setCharacterSize(80);
    goalTxt.setScale(Vector2f(.25,.25));
    goalTxt.setPosition(0.f,60.f);
    goalTxt.setFillColor(Color::Blue);


///TEXTURE DECLERATION
    sf::Texture texturePlayer;
    sf::Texture textureFrame;
    sf::Texture textureGrass;
    sf::Texture textureBlock;
    sf::Texture texture_death_scythe;
    sf::Texture texture_devil;
    sf::Texture texture_hulk;
    sf::Texture texture_redskull;
    sf::Texture Block_footbe;
    sf::Texture Block_footbe1;
    sf::Texture textureBomb;
    sf::Texture textureExplosion;
    sf::Texture textureHealth;
    sf:;Texture textureKey;
    sf::Texture texturePower;
        Texture player_sole_box;
        Texture devil_sole_box;
        Texture hulk_sole_box;
        Texture redskull_sole_box;

    ///LOAD FILE
    texturePlayer.loadFromFile("data/image/kavi.png");
    textureFrame.loadFromFile("data/image/frame1.png");
    textureGrass.loadFromFile("data/image/grass.png");
    texture_death_scythe.loadFromFile("data/image/death_scythe.png");
    texture_devil.loadFromFile("data/image/devil.png");
    texture_hulk.loadFromFile("data/image/hulk.png");
    texture_redskull.loadFromFile("data/image/redskull.png");
    Block_footbe.loadFromFile("data/step0001.png");
    Block_footbe1.loadFromFile("data/image/footbe_type2.png");
    textureBlock.loadFromFile("data/image/block_fix.png");
    textureBomb.loadFromFile("data/000.png");
    textureExplosion.loadFromFile("data/explosion/boxAgun.png");
    textureHealth.loadFromFile("data/heart.png");
    textureKey.loadFromFile("data/key.png");
    texturePower.loadFromFile("data/Bolt.png");
    player_sole_box.loadFromFile("data/image/transparent.png");
    devil_sole_box.loadFromFile("data/image/transparent.png");
    hulk_sole_box.loadFromFile("data/image/transparent.png");
    redskull_sole_box.loadFromFile("data/image/transparent.png");

    ///sprite decl
    sf::Sprite playerImage(texturePlayer); //,sf::IntRect(0,0,35,50)
    sf::Sprite blocki(textureBlock);
    sf::Sprite death_scythe(texture_death_scythe);
        Sprite devil(texture_devil);
        Sprite hulk(texture_hulk);
        Sprite redskull(texture_redskull);
    sf::Sprite frame(textureFrame);
    sf::Sprite grass(textureGrass);
    sf::Sprite block_foot (Block_footbe);
    sf::Sprite block_foot1 (Block_footbe1);
    sf::Sprite spriteHealth(textureHealth);
    sf::Sprite menuKey(textureKey);
    sf::Sprite spritePower(texturePower);
        Sprite player_sole(player_sole_box);
        Sprite devil_sole(devil_sole_box);
        Sprite hulk_sole(hulk_sole_box);
        Sprite redskull_sole(redskull_sole_box);

        //Sprite spriteBomb(textuteBomb);
        //Sprite spriteExplosion(textureExplosion);

    ///Position
    playerImage.setPosition(186,50);
    death_scythe.setPosition(356,50);
    devil.setPosition(476,450);
    hulk.setPosition(706 ,100);
    redskull.setPosition(820,345);
    frame.setPosition(0,0);
    grass.setPosition(125,0);
    menuKey.setPosition(0,90);
    spriteHealth.setPosition(0,205);
    spritePower.setPosition(-5,250);

    ///position detector
    int player_pos_x = 186,player_pos_y = 50;
    int devil_pos_x=476,devil_pos_y=450;

    ///enemy_ani
    int death_scythe_x = 0,death_scythe_y = 0;
    int devil_x = 0,devil_y = 0;
    int hulk_x = 0,hulk_y = 0;
    int redskull_x = 1,redskull_y = 1;

    int death_scythe_counter = 0;
    int devil_counter = 0;
    int hulk_counter = 0;
    int redskull_counter = 0;
    //spriteBomb.setPosition(player_pos_x,player_pos_y);
    //spriteExplosion.setPosition(player_pos_x-14.25,player_pos_y-12.5);

    ///pixel scale
    blocki.setScale(Vector2f(1.117f,.92f));
    block_foot.setScale(Vector2f(1.15f,.92f));
    block_foot1.setScale(Vector2f(1.21f,.99f));
    //spriteExplosion.setScale(0.1689f,0.1451475f);
    spriteHealth.setScale(0.28f,0.28f);
    menuKey.setScale(.546875f,.546875f);
    spritePower.setScale(0.08789f,0.08789f);///.078125(40)
    playerImage.setScale(Vector2f(1.3f,1.2f));
    devil.setScale(1.25f,1.25f);

    ///player sole
    player_sole.setScale(Vector2f(0.04f,.019f));
    //player_sole.setColor(Color(0, 255, 0, 0));


    ///devil sole
    devil_sole.setScale(Vector2f(0.04f,.019f));
    //devil_sole.setColor(Color(0, 255, 0, 0));
   //

    ///hulk sole
    hulk_sole.setScale(Vector2f(0.04f,.019f));
    hulk_sole.setColor(Color(0, 255, 0, 0));
    hulk_sole.setPosition(player_pos_x+8,player_pos_y+48);

    ///redskull sole
    redskull_sole.setScale(Vector2f(0.04f,.019f));
    //redskull_sole.setColor(Color(0, 255, 0, 0));
    redskull_sole.setPosition(player_pos_x+8,player_pos_y+48);

    ///dataset_array
    int arr1[49]={2,5,8,11   ,1,1,3,3,3,4,4,6,7,7,9,9,10,10,12,12,12,2,2,2,3,4,4,5,5,5,5,6,6,7,7,7,8,9,10,10,11,11,12};
    int arr2[49]={2,4,6,8,10 ,5,8,1,4,6,3,9,5,3,8,3,6,4 ,6 ,1,5 ,8,5,7,3,3,7,8,1,3,5,9,3,4,5,7,9,3,2,9 ,10, 3 ,9  ,4 };
    for(int n=0;n<39;n++)
    {
        vect1.push_back(make_pair(arr1[n],arr2[n]));
    }
     ///Time
    vector <Time>explosionTime ;
    explosionTime.clear();

    ///Clock
    sf::Clock explosionClock;
    sf::Clock bombClock[5];
    //std::vector<Clock>explosionClock;

    classBomb vecBomb[5];
    for(int i=0; i<5; i++)
        vecBomb[i].initBomb(&textureBomb,&textureExplosion);

    sf::SoundBuffer soundBuffer;
    sf::SoundBuffer menuBuffer;
    sf::SoundBuffer buttonBuffer;

    sf::Sound gameSound;
    sf::Sound menuSound;
    sf::Sound buttonSound;

    soundBuffer.loadFromFile("data/music/game.wav");
    menuBuffer.loadFromFile("data/music/menu.wav");
    buttonBuffer.loadFromFile("data/music/button1.wav");

    gameSound.setBuffer(soundBuffer);
    menuSound.setBuffer(menuBuffer);
    buttonSound.setBuffer(buttonBuffer);

    buttonSound.setVolume(100);
    menuSound.setVolume(15);

    menuSound.play();
    menuSound.setLoop(true);
    gameSound.setLoop(true);

    Menu menu(window.getSize().x,window.getSize().y);
    bool menu1 = true,game = false, gameover = false, Display = false,bomb1 = false,explosion = false ,gameBack = false,bellExplosion = false,bombBool[5];
    for(int i=0; i<5; i++) bombBool[i]=false;

    ///INITIALIZE

    ///bool colli
    bool player_colli[4]={false};
    bool devil_colli=false;
    bool hulk_colli=false;
    bool redskull_colli=false;

    while(window.isOpen())
    {
        Event event;
        if(menu1)
        {
            if(gameBack)
            {
                ///Position
                playerImage.setPosition(186,50);
                death_scythe.setPosition(356,50);
                devil.setPosition(476,450);
                hulk.setPosition(706 ,100);
                redskull.setPosition(820,360);
                //grass.setPosition(125,0);

                player_pos_x = 186,player_pos_y = 50;
                devil_pos_x =476,devil_pos_y=450;

                death_scythe_x = 0,death_scythe_y = 0;
                devil_x = 0,devil_y = 0;
                hulk_x = 0,hulk_y = 0;
                redskull_x = 1 ,redskull_y = 1;

                death_scythe_counter = 0;
                devil_counter = 0;
                hulk_counter = 0;
                redskull_counter = 0;
                //spriteBomb.setPosition(player_pos_x,player_pos_y);
                //spriteExplosion.setPosition(186,50);
                bombNum = 0;
                //vecBomb[]={0};
                explosionTime.clear();
            }
            while(window.pollEvent(event))
            {
                ///keyboard event in menu
                switch(event.type)
                {
                    case Event::Closed:
                        window.close();
                        break;
                    case Event::KeyReleased:
                        if(event.key.code == sf::Keyboard::Up)
                        {
                            buttonSound.play();
                            menu.MoveUp();
                            //break;
                        }
                    else if(event.key.code == sf::Keyboard::Down)
                    {
                        buttonSound.play();
                        menu.MoveDown();
                        //break;
                    }
                    else if(event.key.code == sf::Keyboard::Return)
                    {
                        switch(menu.GetPressedItem())
                        {
                            case 0:
                                cout << "Play button" <<endl;
                                menuSound.pause();
                                gameSound.play();
                                menu1 = false;
                                game = true;
                                gameover = false;
                                break;
                            case 1:
                                cout << "Credit button pressed" << endl;
                                break;
                            case 2:
                                window.close();
                                break;
                        }
                    }
                    break;
                }
            }
                window.clear();
                menu.draw(window);
                window.display();
        }

        if(game)
        {
            Display = true;

            if(Keyboard::isKeyPressed(Keyboard::Escape) && game == true)
            {
                menu1 = true;
                gameBack = true;
                game = false;
                gameover = false;
                Display = false;
                gameSound.pause();
                menuSound.play();
            }
            while(window.pollEvent(event))
            {
                switch(event.type)
                {
                    case Event::Closed:
                        window.close();
                        break;
                    case sf::Event::KeyPressed:

                    if((event.key.code == sf::Keyboard::Down))
                    {
                        if(!(player_colli[0]))
                        {
                            player.y = Down;
                            playerImage.move(0,+10);
                            player_pos_y+=10;
                        }
                    }
                    else if((event.key.code == sf::Keyboard::Left) )
                    {
                        if(!(player_colli[1]))
                        {
                            player.y = Left;
                            playerImage.move(-10,0);
                            player_pos_x-=10;
                        }
                    }
                    else if((event.key.code == sf::Keyboard::Right) )
                    {
                        if(!(player_colli[2]))
                        {
                            player.y = Right;
                            playerImage.move(+10,0);
                            player_pos_x+=10;
                        }
                    }
                    else  if((event.key.code == sf::Keyboard::Up)  )
                    {

                        if(!(player_colli[3]))
                        {
                            player.y = Up;
                            playerImage.move(0,-10);
                            player_pos_y-=10;
                        }
                    }
                   else if(event.key.code == sf::Keyboard::Escape)
                    {
                        window.clear();
                        game = false;
                        gameover = false;
                        Display = false;
                        gameSound.pause();
                        menuSound.play();

                        //return;
                    }
                   else if(event.key.code == sf::Keyboard::Space)
                     {
                        bombBool[bombNum] = true;
                        bombClock[bombNum].restart();
                        bomb1 = true;
                        vecBomb[bombNum].setPos(player_pos_x,player_pos_y);
                        bombNum = (bombNum+1)%5;
                     }

                        break;
               }
               // cout << "X = " << player_pos_x << "\tY = " << player_pos_y << endl;
                player.x++;
                if(player.x*32 >= texturePlayer.getSize().x)
                {
                    player.x = 0;
                }
            }

            if(Display)
            {

                window.clear();
                window.draw(frame);
                window.draw(grass);
                window.draw(goalTxt);
                window.draw(menuKey);
                window.draw(spritePower);
                window.draw(spriteHealth);

                ///player enemy move texture
                playerImage.setTextureRect(IntRect(player.x * 32,player.y * 48,32,48));
                death_scythe.setTextureRect(IntRect(death_scythe_x*50, death_scythe_y*48, 50, 48));
                devil.setTextureRect(IntRect(devil_x*32, devil_y*48, 32, 48));
                hulk.setTextureRect(IntRect(hulk_x*40, hulk_y*54, 40, 58));
                redskull.setTextureRect(IntRect(redskull_x*32,redskull_y*48, 32, 48));

                player_sole.setPosition(player_pos_x+8,player_pos_y+48);
                devil_sole.setPosition(devil_pos_x,devil_pos_y+48);

                ///ENEMY Move in spritesheet

                if(death_scythe_counter == 60)
                {
                    death_scythe_x = (death_scythe_x + 1) % 4;
                    death_scythe_counter = 0;
                }
                death_scythe_counter++;

                if(devil_counter == 60)
                {
                    devil_x = (devil_x + 1) % 4;
                    devil_counter = 0;
                }
                devil_counter++;

                if(hulk_counter == 60)
                {
                    hulk_x = (hulk_x + 1) % 4;
                    hulk_counter = 0;
                }
                hulk_counter++;

                if(redskull_counter == 60)
                {
                    redskull_x = (redskull_x + 1) % 4;
                    redskull_counter = 1;
                }
                redskull_counter++;
                /*
                 if(!death_scythe.getGlobalBounds().intersects(blocki.getGlobalBounds()) || !death_scythe.getGlobalBounds().intersects(block_foot.getGlobalBounds()) || !death_scythe.getGlobalBounds().intersects(block_foot1.getGlobalBounds()))
                        {
                            death_scythe.move(0,.05);
                        }
                */
                 //death_scythe.move(0,.5);
               ///coolision false

                for(int a=0;a<=3;a++)
                    player_colli[a]=false;

                    devil_colli=false;

                ///fix block
                for(int column=1;column<=4;column++)
                {
                    for(int row=1;row<=5;row++)
                    {

                        int x=125+vect1[column-1].first*57+2;
                        int y=vect1[row-1].second*50-5;
                        blocki.setPosition(x,y);
                        window.draw(blocki);
                        if(player_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                player_colli[player.y]=true;
                           }
                        if(devil_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                           {
                                devil_colli =true;
                           }
                    }
                }

            ///boundery

                ///upper boundery
                int ubx=67;
                for(int i=0;i<=14;i++)
                {
                    ubx=ubx+57;
                    int y=-5;
                    blocki.setPosition(ubx,y);
                    window.draw(blocki);

                    if(player_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                    {
                        player_colli[player.y]=true;
                    }
                    if(devil_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                    {
                        devil_colli =true;
                    }
                }
               ///lower boundery
               int dbx=67;
               for(int i=0;i<=14;i++)
                    {
                        dbx=dbx+57;
                        int y=545;
                        blocki.setPosition(dbx,y);

                        window.draw(blocki);

                        if(player_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                        {
                            player_colli[player.y]=true;
                        }
                        if(devil_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                        {
                            devil_colli =true;
                        }
                    }

                ///left boundery
               int lby=0;
               for(int i=0;i<=11;i++)
                    {
                        int lbx=125;
                        lby+=50;
                        blocki.setPosition(lbx,lby);

                        window.draw(blocki);

                        if(player_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                        {
                            player_colli[player.y]=true;
                        }
                        if(devil_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                        {
                            devil_colli =true;
                        }
                    }
                    ///last left
                        blocki.setPosition(125,545);

                        window.draw(blocki);

                        if(player_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                        {
                            player_colli[player.y]=true;
                        }
                        if(devil_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                        {
                            devil_colli =true;
                        }

                ///right boundery
               int rby=0;
               for(int i=0;i<=11;i++)
                    {
                        int rbx=925-57;
                        rby+=50;
                        blocki.setPosition(rbx,rby);

                        window.draw(blocki);

                        if(player_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                        {
                            player_colli[player.y]=true;
                        }
                        if(devil_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                        {
                            devil_colli =true;
                        }
                    }
                    ///last left
                        blocki.setPosition(925-57,545);
                        window.draw(blocki);

                        if(player_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                            {
                                player_colli[player.y]=true;
                            }
                        if(devil_sole.getGlobalBounds().intersects(blocki.getGlobalBounds()))
                        {
                            devil_colli =true;
                        }
                ///foota block
                int j=4;
                while(j<=vect1.size())
                {
                    int xf=vect1[j].first*57+126;
                    int yf= vect1[j+1].second*50-5;
                    block_foot.setPosition(xf,yf);
                    block_foot1.setPosition(xf,yf);
                    if(j<21)
                    {
                        window.draw(block_foot);

                        if(player_sole.getGlobalBounds().intersects(block_foot.getGlobalBounds()))
                        {
                                player_colli[player.y]=true;
                        }
                        if(devil_sole.getGlobalBounds().intersects(block_foot.getGlobalBounds()))
                        {
                            devil_colli =true;
                        }
                    }
                    else
                    {

                        window.draw(block_foot1);

                        if(player_sole.getGlobalBounds().intersects(block_foot1.getGlobalBounds()))
                        {
                            player_colli[player.y]=true;
                        }
                        if(devil_sole.getGlobalBounds().intersects(block_foot1.getGlobalBounds()))
                        {
                            devil_colli=true;
                        }

                    }
                    j++;
                }

                if(devil_colli)
                {
                    cout<<endl<<"devil_collided"<<endl;
                    int temp=devil_y;
                        devil_y=swap_devil_y;
                        swap_devil_y=temp;
                        //dir_y=0-dir_y;
                }
                devil.move(0,-1);
                //devil_pos_y=devil_pos_y-0.0000000005;
                cout<<" X ="<<devil_pos_x<<"   "<<"Y ="<<devil_pos_y<<endl;
                window.draw(devil_sole);

                window.draw(player_sole);

                window.draw(playerImage);
                window.draw(death_scythe);
                window.draw(devil);
                window.draw(hulk);
                window.draw(redskull);


                if(bomb1)
                {
                    //bomb.Draw(window,player_pos_x,player_pos_y);
                    ///explosionTime = explosionClock.getElapsedTime();
                    ///window.draw(spriteBomb);
                    for(int i = 0; i < 5; i++)
                    {
                        window.draw(vecBomb[i].spriteBomb);
                        explosion = true;
                        bellExplosion = true;

                        if(bombBool[i] == true)
                        {
                            if(bombClock[i].getElapsedTime().asSeconds() >= 5 )
                            {
                                vecBomb[i].setPos(-200,-200);
                                window.draw(vecBomb[i].spriteExplosion);
                                bombBool[i]  = false;
                            }
                        }

                        //explosionTime[i] = explosionClock.getElapsedTime();
                        //cout << explosionTime[i].asSeconds() << endl;
                       /* if(explosionTime[i].asSeconds() > 5)
                        {
                            cout << "BOOOOOOOM" << endl;
                            vecBomb.erase(vecBomb.begin()+i);
                            //explosionClock.restart();

                        }*/


                        /*if(bellExplosion)
                        {
                            explosionClock.restart();
                            bellExplosion  = false;
                        }
                        if(explosion)
                        {
                            if(explosionClock.getElapsedTime().asSeconds() <= .60)
                            {
                                window.draw(vecBomb[i].spriteExplosion);
                            }
                        }*/

                        /*explosionTime[i] = explosionClock[i].getElapsedTime();

                        if(explosionTime[i].asSeconds() >= 3.5)
                        {
                            //spriteBomb.clear();
                            vecBomb.erase(vecBomb.begin()+i);
                            window.draw(spriteExplosion);
                            /*if(explosionTime[i].asSeconds() >= 4.5)
                                explosionClock.restart();}*/

                    }

                    bomb1 == false;
                }

                death_scythe.move(0,.05);
                hulk.move(0,.05);
                redskull.move(-0.05,0);
                /*if(player_collision::PixelPerfectTest(death_scythe,block_foot1))
                {
                    cout << "player_collision" << endl;
                }
                else if(player_collision::PixelPerfectTest(death_scythe,block_foot))
                {
                    cout << "player_collision 000)))" << endl;
                }
                else if(player_collision::PixelPerfectTest(death_scythe,blocki))
                {
                    cout << "xx player_collision xx" << endl;
                }
                else if(player_collision::PixelPerfectTest(death_scythe,playerImage))
                {
                    cout << "PLAYER player_collision " << endl;
                }
                else
                {
                    cout << "nnnnnnn" << endl;
                }*/
                    window.display();
            }
        }
    }
}
