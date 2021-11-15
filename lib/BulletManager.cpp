#include <BulletManager.h>

BulletManager::BulletManager(){
    bulletShader = new Shader("res/simple_shader.vert", "res/simple_shader.frag");
    bulletVAO = new VAO();
}
BulletManager::~BulletManager(){
    delete bulletShader;
    delete bulletVAO;
    for(int i = 0; i < bullets.size(); i++){
        delete bullets[i];
    }
}

void BulletManager::update(){
    for(int i = 0; i < bullets.size(); i++){
        if(bullets[i]->update());
    }
}
void BulletManager::draw(){
    for (int i = 0; i < bullets.size(); i++){
        bullets[i]->draw();
    }
}

void BulletManager::addBullet(Bullet* bullet){
    bullets.push_back(bullet);
}
void BulletManager::removeBullet(int index){
    bullets.erase(bullets.begin() + index);
}

void BulletManager::removeAllBullets(){ 
    bullets.clear(); 
}

void BulletManager::shoot(float position, float direction){
    Bullet* bullet = new Bullet(position, 135.0f, 0.1f, direction, bulletVAO, bulletShader);
    addBullet(bullet);
    VBO bulletVBO = bullet->getVBO();
    bulletVAO->addBuffer(bulletVBO);
}