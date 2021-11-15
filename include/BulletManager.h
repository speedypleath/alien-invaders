#pragma once
#include <Bullet.h>
#include <Shader.h>
#include <VAO.h>
#include <vector>

class BulletManager
{
private:
    std::vector<Bullet*> bullets;
    Shader *bulletShader;
    VAO *bulletVAO;
public:
    BulletManager();
    ~BulletManager();

    void update();
    void draw();

    void addBullet(Bullet* bullet);
    void removeBullet(int bullet);
    void removeAllBullets();
    void shoot(float position, float direction);
    void shoot(float position, float direction, VAO *vao, Shader *shader);

    inline std::vector<Bullet*> getBullets(){ return bullets; }
};