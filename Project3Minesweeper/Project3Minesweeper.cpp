#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <fstream>
#include "Minesweep.h"
using namespace std;
using namespace sf;
/*
Sprite loadsprite(string file) {
    string pre = "images/";
    string post = ".png";
    string filename = pre + file + post;

    Texture texture;
    texture.loadFromFile(filename);
    Sprite sprite;
    sprite.setTexture(texture);
    return sprite;
}
*/

int main() {

    Game board("boards/config.cfg");

    RenderWindow window(VideoMode(board.getwidth(), board.getheight()), "SFML works!");
    
    vector<int> minelocations;
    //Loop to set bombs and then loop to sort
    for (int i = 0; i < board.getminecount(); i++) {
        int minespot = rand() % board.gettilecount();
        minelocations.push_back(minespot);
    }

    //Sets tiles
    for (int i = 0; i < board.gettilecount(); i++) {
        Tile tile;

    }

    while (window.isOpen()) {

        Event event;

        //If the window is told to close, close
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::MouseButtonReleased) {

            }
        }

        //Iterates through displaying what's on the screen
        window.clear();

        //Drawing section
        Texture texture;
        texture.loadFromFile("images/tile_hidden.png");

        Sprite sprite;
        sprite.setTexture(texture);

        //Mine
        Texture minet;
        minet.loadFromFile("images/mine.png");

        Sprite mine;
        mine.setTexture(minet);

        //Sets x and y and a counter
        int x = 0;
        int y = 0;
        int count = 0;
       
        //Loops for how many tiles there should be
        for (int i = 0; i < board.gettilecount(); i++) {
            //If Column is full, go to next row
            if (count == board.getColumn()) {
                y += 32;
                count = 0;
            }
            //x calculates the position of x, which moves by 30 each loop            
            x = count * 32;

            //Sets spot and Draws
            sprite.setPosition(x,y);

            window.draw(sprite);
            window.draw(mine);
            count++;
        }

        //Display the bottom menu;
        //I have zero idea how to use it in class because it seems like i would have to redo everything, 
        //but even if I do I still don't understand how to use the window function outside of main and I can't find any info on that, 
        //so i opted to duplicate code.
        //First the smiley
        Texture facet;
        facet.loadFromFile("images/face_happy.png");
        Sprite face;
        face.setTexture(facet);
        int facelocationx = (board.getColumn() / 2) * 32 - 32;
        int facelocationy = y + 32;
        face.setPosition(facelocationx, facelocationy);
        window.draw(face);

        //Debug button
        Texture debugt;
        debugt.loadFromFile("images/debug.png");
        Sprite debug;
        debug.setTexture(debugt);

        facelocationx += 32 + 32+32+32;
        debug.setPosition(facelocationx, facelocationy);
        window.draw(debug);
        //test1 button
        Texture test1t;
        test1t.loadFromFile("images/test_1.png");
        Sprite test1;
        test1.setTexture(test1t);

        facelocationx += 32+32;
        test1.setPosition(facelocationx, facelocationy);
        window.draw(test1);
        //test2 button
        Texture test2t;
        test2t.loadFromFile("images/test_2.png");
        Sprite test2;
        test2.setTexture(test2t);

        facelocationx += 32+32;
        test2.setPosition(facelocationx, facelocationy);
        window.draw(test2);
        //test3 button
        Texture test3t;
        test3t.loadFromFile("images/test_3.png");
        Sprite test3;
        test3.setTexture(test3t);

        facelocationx += 32+32;
        test3.setPosition(facelocationx, facelocationy);
        window.draw(test3);

        //Puts all the draws and stuff and displays it
        window.display();
    }

    return 0;
}

