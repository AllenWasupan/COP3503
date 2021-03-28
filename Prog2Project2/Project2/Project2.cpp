// Prog2Project2.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <fstream>
#include "Img.h"
using namespace std;

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

int main() {
    //Loads stuff so i dont have to later
    Img car, circles, layer_blue, layer_green, layer_red, layer1, layer2, pattern1, pattern2, text, text2;
    car.Load("input/car.tga");
    circles.Load("input/circles.tga");
    layer_blue.Load("input/layer_blue.tga");
    layer_green.Load("input/layer_green.tga");
    layer_red.Load("input/layer_red.tga");
    layer1.Load("input/layer1.tga");
    layer2.Load("input/layer2.tga");
    pattern1.Load("input/pattern1.tga");
    pattern2.Load("input/pattern2.tga");
    text.Load("input/text.tga");
    text2.Load("input/text2.tga");

//Part one;
    //Multiply blends
    Img one = Multiblend(layer1, pattern1);
    one.write("output/part1.tga");

//Part two;
    Img two = Subblend(layer2, car);
    two.write("output/part2.tga");

//Part three
    Img three = Multiblend(layer1, pattern2);
    three = Screenblend(three, text);
    three.write("output/part3.tga");

//Part four;
    Img four = Multiblend(layer2, circles);
    four = Subblend(pattern2, four);
    four.write("output/part4.tga");

//Part five;
    Img five = Overblend(layer1, pattern1);
    five.write("output/part5.tga");

//Part six;
    Img six = addcolor(car, 0, 0, 200);
    six.write("output/part6.tga");

//Part seven;
    Img seven = multcolor(car, 4, 0, 1);
    seven.write("output/part7.tga");

//Part eight;
    Img eight_r = channelcolor(car, 1);
    eight_r.write("output/part8_r.tga");
    Img eight_b = channelcolor(car, 2);
    eight_b.write("output/part8_b.tga");
    Img eight_g = channelcolor(car, 3);
    eight_g.write("output/part8_g.tga");

//Part nine;
    Img nine = reversechannel(layer_red, layer_blue, layer_green);
    nine.write("output/part9.tga");

//Part ten
    Img ten = 

    return 0;
}