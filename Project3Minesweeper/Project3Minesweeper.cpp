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
    window.setTitle("Minesweeper");
 
    cout << "Rows: " << board.getRow() << endl;
    cout << "Columns: " << board.getColumn() << endl;

    int debugx, facelocationx, menuy, test1x, test2x, test3x, flagnum = 0;
    bool debugtoggle = false;
    bool defeat = false, win = false;
    string shownface = "images/face_happy.png";
    int wincount = board.gettilecount() - board.getminecount();
    while (window.isOpen()) {

        Event event;

        //If the window is told to close, close
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }
            //If left clicked is pressed
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                Vector2i MousePosition = Mouse::getPosition(window);
                //cout << "X: " << MousePosition.x << " Y: " << MousePosition.y << endl;

                //If click in the menu
                if ((MousePosition.y > board.getheight()-88) && (MousePosition.y < menuy + 64)) {
                    //If click on smiley face
                    if ((MousePosition.x > facelocationx) && (MousePosition.x < facelocationx + 64)) {
                        
                        board.setBoard("boards/config.cfg");
                        shownface = "images/face_happy.png";
                        defeat = false;
                        win = false;
                        debugtoggle = false;
                    }
                    //If click debug
                    if (((MousePosition.x > debugx) && (MousePosition.x < debugx + 64)) && ((defeat == false) && (win == false))) {

                        if (debugtoggle) {
                            for (unsigned int i = 0; i < board.gettilecount(); i++) {
                                if (board.tilevec[i].isbomb) {
                                   board.tilevec[i].revealed = false;
                                }
                            }
                            debugtoggle = false;
                        }
                        else {
                            debugtoggle = true;
                        }
                    }
                    //If click test
                    if ((MousePosition.x > test1x) && (MousePosition.x < test1x + 64)) {
                        defeat = false;
                        board.setTest("boards/recursion_test.brd");
                        debugtoggle = false;
                    }
                    if ((MousePosition.x > test2x) && (MousePosition.x < test2x + 64)) {
                        defeat = false;
                        board.setTest("boards/testboard2.brd");
                        debugtoggle = false;
                    }
                    if ((MousePosition.x > test3x) && (MousePosition.x < test3x + 64)) {
                        defeat = false;
                        board.setTest("boards/testboard3.brd");
                        debugtoggle = false;
                    }
                }
                //If click a tile
                if ((MousePosition.y < menuy) && (defeat == false)) {
                    
                    //#Remainder for what they mean: Row up down column sideways
                    int columnselected = MousePosition.x / 32;
                    int rowselected = MousePosition.y / 32;

                    int tileselected = columnselected + (rowselected*board.getColumn());
                    cout << tileselected << endl;
                    if (board.tilevec[tileselected].flag == false) {
                        board.tilevec[tileselected].revealed = true;

                        if (board.tilevec[tileselected].isbomb) {
                            shownface = "images/face_lose.png";
                            defeat = true;
                            for (unsigned int i = 0; i < board.gettilecount(); i++) {
                                if (board.tilevec[i].isbomb) {
                                    board.tilevec[i].revealed = true;
                                }
                            }
                        }
                        else if (board.tilevec[tileselected].num == 0) {
                            board.recursiveclick(tileselected);
                            
                        }
                    }

                }
            }
            //If right click is pressed
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && ((defeat == false) && (win == false))) {
                Vector2i MousePosition = Mouse::getPosition(window);
                //cout << "X: " << MousePosition.x << " Y: " << MousePosition.y << endl;
                if ((MousePosition.y < menuy)) {
                    
                    int columnselected = MousePosition.x / 32;
                    int rowselected = MousePosition.y / 32;

                    int tileselected = columnselected + (rowselected * board.getColumn());
                    //cout << tileselected << endl;

                    if (board.tilevec[tileselected].revealed == false) {
                        if (board.tilevec[tileselected].flag) {
                            board.tilevec[tileselected].flag = false;
                            flagnum--;
                        }
                        else {
                            board.tilevec[tileselected].flag = true;
                            flagnum++;
                        }
                    }
                }
            }
        }
        if (debugtoggle) {
            for (unsigned int i = 0; i < board.gettilecount(); i++) {
                if (board.tilevec[i].isbomb) {
                    if (debugtoggle % 2 != 0) {
                        board.tilevec[i].revealed = true;
                    }
                    else if (debugtoggle > 1) {
                        board.tilevec[i].revealed = false;

                    }
                }
            }
        }

        //Resets the screen to draw
        window.clear(Color::White);

        //Drawing section
        Texture hiddentex;
        hiddentex.loadFromFile("images/tile_hidden.png");
        Sprite hidden;
        hidden.setTexture(hiddentex);

        Texture revtexture;
        revtexture.loadFromFile("images/tile_revealed.png");
        Sprite revealed;
        revealed.setTexture(revtexture);

        //Mine
        Texture minet;
        minet.loadFromFile("images/mine.png");
        Sprite mine;
        mine.setTexture(minet);

        //Flag
        Texture flagtex;
        flagtex.loadFromFile("images/flag.png");
        Sprite flag;
        flag.setTexture(flagtex);
        //Sets x and y and a counter
        int x = 0;
        int y = 0;
        int count = 0;

        wincount = board.gettilecount() - board.getminecount();
        //Loops for how many tiles there should be
        //Holds the logic for determining, which tile it should be and prints it
        for (int i = 0; i < board.gettilecount(); i++) {
            //If Column is full, go to next row
            if (count == board.getColumn()) {
                y += 32;
                count = 0;
            }
            //x calculates the position of x, which moves by 30 each loop            
            x = count * 32;

            //Sets Tiles and Draws
            if (board.tilevec[i].revealed) {
                revealed.setPosition(x,y);
                window.draw(revealed);
                if ((defeat == false) && (board.tilevec[i].isbomb == false)) {
                    wincount -= 1;
                }
                if (board.tilevec[i].flag) {
                    flag.setPosition(x, y);
                    window.draw(flag);
                }
                if (board.tilevec[i].isbomb) {
                    mine.setPosition(x, y);
                    window.draw(mine);
                }

                else if (board.tilevec[i].num > 0) {
                    int n = board.tilevec[i].num;
                    Texture texture;
                    string one = "images/number_";
                    string two = to_string(n);
                    string three = ".png";
                    string numboar = one + two + three;
                    texture.loadFromFile(numboar);
                    Sprite sprite;
                    sprite.setTexture(texture);
                    sprite.setPosition(x, y);
                    window.draw(sprite);

                }
                /*
                //Recursive reveal
                else {
                    if (board.tilevec[i].top) {
                        if (board.tilevec[i - board.getColumn()].flag == false) {
                            board.tilevec[i - board.getColumn()].revealed = true;
                        }
                    }
                    if (board.tilevec[i].left) {
                        if (board.tilevec[i - 1].flag == false) {
                            board.tilevec[i - 1].revealed = true;
                        }
                    }
                    if (board.tilevec[i].down) {
                        if (board.tilevec[i + board.getColumn()].flag == false) {
                            board.tilevec[i + board.getColumn()].revealed = true;
                        }
                    }
                    if (board.tilevec[i].right) {
                        if (board.tilevec[i + 1].flag == false) {
                            board.tilevec[i + 1].revealed = true;
                        }
                    }

                    if (board.tilevec[i].top && board.tilevec[i].left) {
                        if (board.tilevec[i - board.getColumn() - 1].flag == false) {
                            board.tilevec[i - board.getColumn() - 1].revealed = true;
                        }
                    }
                    if (board.tilevec[i].top && board.tilevec[i].right) {
                        if (board.tilevec[i - board.getColumn() + 1].flag == false) {
                            board.tilevec[i - board.getColumn() + 1].revealed = true;
                        }
                    }
                    if (board.tilevec[i].down && board.tilevec[i].left) {
                        if (board.tilevec[i + board.getColumn() - 1].flag == false) {
                            board.tilevec[i + board.getColumn() - 1].revealed = true;
                        }
                    }
                    if (board.tilevec[i].down && board.tilevec[i].right) {
                        if (board.tilevec[i + board.getColumn() + 1].flag == false) {
                            board.tilevec[i + board.getColumn() + 1].revealed = true;
                        }
                    }
                }*/
            }
            
            else {
                hidden.setPosition(x,y);
                window.draw(hidden);
                if (board.tilevec[i].flag) {

                    flag.setPosition(x, y);
                    window.draw(flag);
                }
                
            }
           
            count++;
        }

        //Victory Conditions
        cout << wincount << endl;
        if ((wincount == 0) && ((defeat == false) && (win == false))) {
            shownface = "images/face_win.png";
            for (unsigned int i = 0; i < board.tilevec.size(); i++) {
                if (board.tilevec[i].isbomb) {
                    board.tilevec[i].flag = true;
                    flagnum++;
                }
            }
            win = true;
        }
        
        //Display the bottom menu;
        //I have zero idea how to use it in class because it seems like i would have to redo everything, 
        //but even if I do I still don't understand how to use the window function outside of main and I can't find any info on that
        //First the smiley
        Texture facet;
        facet.loadFromFile(shownface);
        Sprite face;
        face.setTexture(facet);
        facelocationx = (board.getColumn() / 2) * 32 - 32;
        menuy = y + 32;
        face.setPosition(facelocationx, menuy);
        window.draw(face);

        //Debug button
        Texture debugt;
        debugt.loadFromFile("images/debug.png");
        Sprite debug;
        debug.setTexture(debugt);

        debugx = facelocationx + 32 + 32 + 32 + 32;
        debug.setPosition(debugx, menuy);
        window.draw(debug);
        //test1 button
        Texture test1t;
        test1t.loadFromFile("images/test_1.png");
        Sprite test1;
        test1.setTexture(test1t);

        test1x = debugx + 32 + 32;
        test1.setPosition(test1x, menuy);
        window.draw(test1);

        //test2 button
        Texture test2t;
        test2t.loadFromFile("images/test_2.png");
        Sprite test2;
        test2.setTexture(test2t);

        test2x = test1x + 32 + 32;
        test2.setPosition(test2x, menuy);
        window.draw(test2);

        //test3 button
        Texture test3t;
        test3t.loadFromFile("images/test_3.png");
        Sprite test3;
        test3.setTexture(test3t);

        test3x = test2x + 32 + 32;
        test3.setPosition(test3x, menuy);
        window.draw(test3);
        
        //Digits texture
        int digitsx = 16;
        Texture digitst1;
        Texture digitst2;
        Texture digitst3;
        int digx, digy;
        int digitdisplayed = board.getminecount() - flagnum;
        int digvaluex = 0;
        //Positive digit display
        if (digitdisplayed >= 0) {
            for (int i = 0; i < 10; i++) {
                        if (digitdisplayed % 10 == i) {
                            digitst1.loadFromFile("images/digits.png", IntRect(digvaluex, 0, 21, 32));
                        }
                        if (((digitdisplayed % 100)/10) == i) {
                            digitst2.loadFromFile("images/digits.png", IntRect(digvaluex, 0, 21, 32));
                        }
                        if ((digitdisplayed / 100) == i) {
                            digitst3.loadFromFile("images/digits.png", IntRect(digvaluex, 0, 21, 32));
                        }
                        digvaluex += 21;
                    }
        }
        //Negative digit display
        else {
            for (int i = 0; i < 10; i++) {
                if (digitdisplayed % 10 == -i) {
                    digitst1.loadFromFile("images/digits.png", IntRect(digvaluex, 0, 21, 32));
                }
                if (((digitdisplayed % 100) / 10) == -i) {
                    digitst2.loadFromFile("images/digits.png", IntRect(digvaluex, 0, 21, 32));
                }
                if ((digitdisplayed / 100) == -i) {
                    digitst3.loadFromFile("images/digits.png", IntRect(210, 0, 21, 32));
                }
                digvaluex += 21;
            }
        }
        //Prints digits
        Sprite digit1;
        digit1.setTexture(digitst1);
        digit1.setPosition(digitsx+42, menuy);

        Sprite digit2;
        digit2.setTexture(digitst2);
        digit2.setPosition(digitsx + 21, menuy);

        Sprite digit3;
        digit3.setTexture(digitst3);
        digit3.setPosition(digitsx, menuy);

        window.draw(digit1);
        window.draw(digit2);
        window.draw(digit3);

        //Puts all the draws and stuff and displays it
        window.display();
    }

    return 0;
}

