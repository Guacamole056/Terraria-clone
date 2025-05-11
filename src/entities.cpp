#include "entities.h"
#include <iostream>

int randomrange(int min_val, int max_val);
bool randompercent(float chance);

using namespace std;

extern float deltatime;
extern entities player;

entities::entities() {
    x = 0;
    y = 0;
    totalframetime = 0;
    animationposition = 0;
    animationstate = 0;
    frametime = 0;
    life = 0;
    maxlife = 0;
    canjump = false;
    moving = false;
    movingright = false;
    movingdown = false;
    invurnerabilitytime = 0;
    frosttime = 0;
    armour = 0;
    falldamagerezistance = 0;
}

entities::entities(float x_, float y_) {
    x = x_;
    y = y_;
    totalframetime = 0;
    animationposition = 0;
    animationstate = 0;
    frametime = 0;
    life = 0;
    maxlife = 0;
    canjump = false;
    moving = false;
    movingright = false;
    movingdown = false;
    invurnerabilitytime = 0;
    frosttime = 0;
    armour = 0;
    falldamagerezistance = 0;
}

playerentity::playerentity() : entities() {
    maxlife = 100;
    life = maxlife;
    spawnpoint = sf::Vector2i(0, 0);
}

playerentity::playerentity(float x_, float y_) : entities(x_, y_) {
    maxlife = 100;
    life = maxlife;
    spawnpoint = sf::Vector2i(x_, y_);
}

float entities::getcenterx() { return x + sizeofentity.x / 2; }
float entities::getcentery() { return y + sizeofentity.y / 2; }

void entities::updatedraw() {
    uint8_t numberofframes = 7;
    if (numberofframes != 1) {
        totalframetime += deltatime;
        if (totalframetime > frametime) {
            animationposition++;
            if (animationposition > numberofframes - 1) {
                animationposition = 0;
            }
            totalframetime = 0;
        }
    }
    else {
        animationposition = 0;
    }
}

void entities::draw(sf::RenderWindow& window, float deltatime, int add) {
    if (invurnerabilitytime > 0) {
        invurnerabilitytime -= deltatime;
        sprite.setColor(sf::Color(255, 10, 10));
    }
    else {
        invurnerabilitytime = 0;
    }

    if (frosttime > 0) {
        frosttime -= deltatime;
        sprite.setColor(sf::Color(10, 10, 255));
    }
    else {
        frosttime = 0;
    }

    animationstate += add;

    if (movingright) {
        sprite.setTextureRect(sf::IntRect(sizeofentity.x * animationposition,
            sizeofentity.y * animationstate,
            sizeofentity.x, sizeofentity.y));
    }
    else {
        sprite.setTextureRect(sf::IntRect(sizeofentity.x * (animationposition + 1),
            sizeofentity.y * animationstate,
            -sizeofentity.x, sizeofentity.y));
    }

    sprite.setPosition(x, y);
    window.draw(sprite);
    sprite.setColor(sf::Color::White);
}

bool entities::operator==(entities other) {
    int deltax = getcenterx() - other.getcenterx();
    int deltay = getcentery() - other.getcentery();
    int intersectx = abs(deltax) - (other.sizeofentity.x / 2 + sizeofentity.x / 2);
    int intersecty = abs(deltay) - (other.sizeofentity.y / 2 + sizeofentity.y / 2);

    return intersectx < 0.0f && intersecty < 0.0f;
}

bool entities::operator==(sf::Vector2u other) {
    int deltax = getcenterx() - other.x * 32 - 16;
    int deltay = getcentery() - other.y * 32 - 16;
    int intersectx = abs(deltax) - (16 + sizeofentity.x / 2);
    int intersecty = abs(deltay) - (16 + sizeofentity.y / 2);

    return intersectx < 0.0f && intersecty < 0.0f;
}

enemy::enemy() {}

bool enemy::checktime() {
    float elapsed = time.getElapsedTime().asSeconds();
    livetime -= elapsed;
    time.restart();
    return livetime >= 0;
}

void entities::dealdamage(float damage) {
    if (invurnerabilitytime <= 0) {
        damage -= armour;
        if (damage < 1) damage = 1;
        invurnerabilitytime = 1.2f;
        life -= damage;
    }
}

bool entities::dealfalldamage(float damage) {
    damage -= falldamagerezistance;
    if (damage <= 0 || falldamagerezistance <= -1) damage = 0;
    life -= damage;
    return damage > 0;
}

void entities::freeze(float time) {
    if (!freezerezistance) frosttime = time;
}
