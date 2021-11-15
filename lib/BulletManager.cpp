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
    if(bullets.empty())
        return;
    for(Bullet *bullet : bullets){
        bullet->update();
    }
}
void BulletManager::draw(){
    if(bullets.empty())
        return;
    for(Bullet *bullet : bullets){
        bullet->draw();
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

void BulletManager::shoot(float position, float direction, VAO *vao, Shader *shader){
    Bullet* bullet = new Bullet(position, 135.0f, 0.1f, direction, vao, shader);
    addBullet(bullet);
    VBO bulletVBO = bullet->getVBO();
    vao->addBuffer(bulletVBO);
}