#include <BulletManager.h>
#include <errorHandle.h>

BulletManager::BulletManager(){
    currentBullet = 0;
    bulletShader = new Shader("res/simple_shader.vert", "res/simple_shader.frag");
    bulletVAO = new VAO();
    Bullet *bullet;
    for(int i = 0; i < 10; i++){
        bullet = new Bullet(WIDTH, 50.0f, 0.1, PI/2, bulletVAO, bulletShader);
        addBullet(bullet);
    }
}
BulletManager::~BulletManager(){
    for(int i = 0; i < bullets.size(); i++){
        delete bullets[i];
    }
}

void BulletManager::update(){
    for(Bullet *bullet : bullets){
        bullet->update();
    }
}
void BulletManager::draw(){
    for(Bullet *bullet : bullets){
        bullet->draw();
    }
}

void BulletManager::addBullet(Bullet* bullet){
    bullets.push_back(bullet);
}

void BulletManager::shoot(float position, float direction){
    while(bullets.at(currentBullet)->update()){
        currentBullet = (currentBullet + 1) % 10; 
    }
    if(!bullets.at(currentBullet)->update()){
        bullets.at(currentBullet)->setPosition(position);
        bullets.at(currentBullet)->setDirection(direction);
    }
}