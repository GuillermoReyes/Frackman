#ifndef ACTOR_H_
#define ACTOR_H_
#include <stack>
#include "GraphObject.h"
#include <cmath>

//#include <random>

class StudentWorld;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class GameObject : public GraphObject {
    
public:
    GameObject(StudentWorld* theWorld,int imageID, int startX, int startY, Direction dir , double size, unsigned int depth);
    GameObject(int imageID, int startX, int startY, Direction dir , double size, unsigned int depth);
    virtual  ~GameObject();
    virtual void doSomething() = 0;
    virtual void annoyed() ;
    StudentWorld* getWorld() const;
    bool isDead();
    void setDead();
    virtual void bribe();
private:
    bool m_dead = false;
    StudentWorld* m_world;
};


class Dirt : public GameObject {
public:
    Dirt(int startX, int startY, StudentWorld* theWorld);
    ~Dirt();
    void doSomething();
private:
    
};
class Gold;
class Squirt;
class Frackman : public GameObject {
public:
    Frackman(int startX, int startY, StudentWorld* theWorld);
    ~Frackman();
    void annoyed();
    void doSomething();
    int getSonar() const ;
    void decSonar();
    void increaseSonar();
    void fireSquirt(Direction dir);
    int getGold() const;
    void increaseGold();
    void decGold();
    int getWater() const ;
    void increaseWater();
    void decWater();
    void dropGold();
    int getHitPoints();
private:
    Gold* m_gold;
    Squirt* m_squirt;
    int hit_pts;
    int gold;
    int sonars;
    int water;
    
};

class Goodies : public GameObject{
public:
    
    Goodies(StudentWorld * theWorld,int imageID, int startX, int startY,Direction dir,double size, unsigned int depth );
    Goodies(Frackman* holder,int imageID, int startX, int startY,Direction dir,double size, unsigned int depth);
    // dont remember to add a destructor for this claas
    bool nearFrackman( int difference);
    
    virtual ~Goodies();
    bool withinRadius(GameObject* mp, int x, int y);
    bool isStable();
    void setUnstable();
    void tickCount();
    int  getTick();
private:
    int tck_count;
    bool stable;
    bool reset;
};
class Boulder : public Goodies {
public:
    
    Boulder(StudentWorld* world, int startX, int startY);
    ~Boulder();
    
    void doSomething();
private:
    
};
class Squirt : public Goodies {
public:
    Squirt(StudentWorld* theWorld, int startX, int startY, Direction dir);
    ~Squirt();
    void doSomething();
    
private:
    
};

class Barrel : public Goodies {
public:
    Barrel(int startX, int startY, StudentWorld* theWorld);
    ~Barrel();
    void doSomething();
};
class Gold : public Goodies {
public:
    //Gold(Frackman* dropper, int startX,int startY);
    Gold(StudentWorld* theWorld, int startX, int StartY, bool temp, bool perm, bool isBribe);
    ~Gold();
    
    void doSomething();
    
private:
    bool temporary;
    bool permanent;
    
};
class Sonar : public Goodies {
public:
    Sonar(StudentWorld* theWorld, int startX, int startY);
    ~Sonar();
    
    void doSomething();
    
private:
    
};
class Water : public Goodies {
public:
    Water(StudentWorld* theWorld, int startX, int startY);
    ~Water();
    
    void doSomething();
private:
    
};
class Protestor : public GameObject {
public:
    Protestor(StudentWorld* theWorld,int imageID, int startX, int startY);
    Protestor(int imageID, int startX, int startY);
    virtual ~Protestor();
    void setRageQuit();
    bool isRageQuit() const ;
    virtual void bribe();
    bool isBribed() const ;
    int getHitPoints() const;
    void decHitPoints(int pts);
    void setHitPoints(int htpts);
    bool obstacleThere(int X, int Y, Direction dir) ;
    void randDir(int X, int Y, Direction& dir);
    void moveProtestor(Direction dir, int& squaresToMove);
   
    bool isViableMove(Direction dir);
    void  moveNormal();
    void computePath();
    
private:
    int numSquarestoMove;
    bool stunned;
    int tick2wait;
    int yellTicks;
    
    
    bool rageQuit;
    bool bribed;
    // may not be necessary
    int hitpoints;
    
};
class RProtestor : public Protestor {
public:
    RProtestor(StudentWorld* theWorld, int startX, int startY);
    ~RProtestor();
    void doSomething();
    void bribe(); 
    void annoyed();
private:
    int normalTick;
    int numSquaresToMove;
    bool stunned;
    bool stunTicks;
    int tick;
    int tick2wait;
    int yellTicks;
    int hitpoints;
};
class HProtestor : public Protestor {
public:
    HProtestor(StudentWorld* theWorld, int startX, int startY);
    ~HProtestor();
    void doSomething();
    void annoyed();
    void bribe(); 
private:
    int normalTick;
    int tick;
    int stunTicks; 
    int numSquaresToMove;
    bool stunned;
    int tick2wait;
    int yellTicks;
    
    
    bool rageQuit;
    bool bribed;
    // may not be necessary
    int hitpoints;

};
#endif // ACTOR_H_

