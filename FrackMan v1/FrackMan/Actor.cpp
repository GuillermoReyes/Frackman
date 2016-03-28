#include "Actor.h"
#include "StudentWorld.h"
#include <random>
// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp


#include<iostream>
int randInt(int min, int max)
{
    if (max < min)
        std::swap(max, min);
    static std::random_device rd;
    static std::mt19937 generator(rd());
    std::uniform_int_distribution<> distro(min, max);
    return distro(generator);
}
// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
GameObject::GameObject(StudentWorld* theWorld,int imageID, int startX, int startY, Direction dir , double size , unsigned int depth)
:GraphObject(imageID,startX,startY,dir,size,depth), m_world(theWorld)
{
    
}
GameObject::GameObject(int imageID, int startX, int startY, Direction dir , double size, unsigned int depth)
: GraphObject(imageID,startX,startY,dir, size, depth)
{
    
}


void GameObject::annoyed() {
    // default behavior is to do nothing
}
StudentWorld* GameObject::getWorld() const{
    return m_world;
}
bool GameObject::isDead(){
    return m_dead;
}
void GameObject::setDead(){
    m_dead = true;
    setVisible(false);
    
}
GameObject::~GameObject(){
    // each deried class must implemrt its own destructor
}
Goodies::Goodies(Frackman* holder,int imageID, int startX, int startY,Direction dir,double size, unsigned int depth)
: GameObject(imageID,startX, startY, dir, size,depth)
{   reset = true;
    stable = true;
    tck_count = 0;
}
Goodies::Goodies(StudentWorld * theWorld,int imageID, int startX, int startY,Direction dir,double size, unsigned int depth)
:GameObject(theWorld, imageID,startX, startY,dir, size, depth)
{
    reset = true;
    stable = true;
    tck_count = 0;
}
bool Goodies::nearFrackman(int difference){
    //int tempX = abs(getWorld()->getPlayerX() - getX());
    //int tempY = abs(getWorld()->getPlayerY() - getY());
    //if (tempX <= difference || tempY <= difference)
    //    return true;
    
    return false;
}
void Goodies::tickCount(){
    
    
    tck_count++;
    
}
int Goodies::getTick(){
    return tck_count;
}
bool Goodies::isStable(){
    return stable;
}
void Goodies::setUnstable(){
    stable = false;
}

Goodies::~Goodies(){
    // each deried lass must implemet their own destruot
}
Dirt::Dirt(int startX, int startY, StudentWorld* theWorld)
: GameObject(theWorld,IID_DIRT, startX, startY, right, .25,3)
{
    setVisible(true);
}

void Dirt::doSomething() {
}
Dirt::~Dirt() {
    setVisible(false);
}

Frackman::Frackman(int startX, int startY,StudentWorld* theWorld)
: GameObject(theWorld,IID_PLAYER, startX, startY, right,1,0)
{
    hit_pts = 10;
    water = 5;
    sonars = 1;
    gold = 0;
    setVisible(true);
    
}
void Frackman::annoyed() {
    // implemet whaterer  makes fracman annoyed
    if(hit_pts <=2){
        getWorld()->playSound(SOUND_PLAYER_GIVE_UP);
        setDead();
    }
    
    hit_pts-=2;
}

void Frackman::doSomething() {
    if(isDead()){
        return ;
    }
    
    int x,y;
    x = getX();
    y = getY();
    getWorld()->manageDirt(x,y);
    int ch;
    if (getWorld()->getKey(ch)== true )
    {   Direction temp = getDirection();
        int x = getX();
        int y = getY();
        
        switch(ch){
            case 'z':
                // implemetn zap
                break;
            case KEY_PRESS_TAB:
                // implement gold dropping
            case KEY_PRESS_SPACE :
                if(getWater()>0){
                    
                    
                    fireSquirt(temp);
                    decWater();
                    getWorld()->playSound(SOUND_PLAYER_SQUIRT);
                }
                break;
            case  KEY_PRESS_ESCAPE :
                setDead();
                break;
            case KEY_PRESS_UP :
                if(temp != up){
                    setDirection(up);
                }
                else{
                    if(y<60){
                        moveTo(x,y+1);
                        getWorld()->playSound(SOUND_DIG);
                        getWorld()->manageDirt(x,y+1);
                    }}
                break;
            case KEY_PRESS_DOWN :
                if(temp != down){
                    setDirection(down);
                }
                else{
                    if(y>0) {
                        moveTo(x,y-1);
                        getWorld()->playSound(SOUND_DIG);
                        getWorld()->manageDirt(x,y-1);
                    }}
                
                
                break ;
            case KEY_PRESS_LEFT :
                if(temp != left){
                    setDirection(left);
                }
                
                else if(x>0&&x<64){
                    moveTo(x-1,y);
                    getWorld()->playSound(SOUND_DIG);
                    getWorld()->manageDirt(x-1,y);
                }
                break;
            case KEY_PRESS_RIGHT :
                if(temp != right){
                    setDirection(right);
                } else{
                    if(x<60){
                        moveTo(x+1, y);
                        getWorld()->playSound(SOUND_DIG);
                        getWorld()->manageDirt(x+1,y);
                    }}
                break;
        }
    }
    
    
}
int Frackman::getSonar() const {
    return sonars;
}
void Frackman::decSonar()
{
    sonars-=1;
}
void Frackman::increaseSonar(){
    sonars+=1;
}
void Frackman::fireSquirt(Direction dir){
    // this may give problems later;
    m_squirt = new Squirt(getWorld(),  getX(), getY(),dir);
    getWorld()->storeItem(m_squirt);
}
int Frackman::getGold() const {
    return gold;
}
void Frackman::increaseGold(){
    gold+=1;
}
void Frackman::decGold(){
    gold-=1;
}
int Frackman::getWater() const {
    return water;
}
void Frackman::increaseWater(){
    water +=5;
}
void Frackman::decWater(){
    water-=1;
}
Frackman::~Frackman() {
    setVisible(false);
}
Boulder::Boulder(StudentWorld* world, int startX, int startY)
:Goodies(world, IID_BOULDER, startX,startY,down,1,1 )
{
        
    
    
    
    
    
    setVisible(true);
}
void Boulder::doSomething() {
    if(isDead()) {
        return;
    }
    
    if(isStable()){
        int Y = getY();
        int X = getX();
        for(int i = 0; i <=3; i++){
            for(int j = 1; j<=3; j++)
            if(!getWorld()->dirtThere(X+i,Y-j))
                setUnstable();
        }
    }
    if(!isStable()){
        tickCount();
    }
    if(getTick()>=30 && getY() >0){
        
        moveTo(getX(), getY()-1);
        getWorld()->playSound(SOUND_FALLING_ROCK);
        
        if(getWorld()->dirtThere(getX(), getY()))
            setDead();
        
        
        if(getWorld()->getPlayerX() == getX() && getWorld()->getPlayerY() == getY()) {
            
            getWorld()->accessPlayer()->setDead();
            getWorld()->decLives();
            
        }
        
    }
    
    
    
}

Boulder::~Boulder(){
    setVisible(false);
}
Squirt::Squirt(StudentWorld* theWorld, int startX, int startY, Direction dir)
: Goodies(theWorld,IID_WATER_SPURT,startX, startY,dir ,1,1)
{
    setVisible(true);
}
void Squirt::doSomething(){
    // if it has radius of 3 to one or more protestors ase annoyance to pretestor
    // sets annoyane by 2 oints and sets itself to dead;
    GameObject* ptr;
    tickCount();
    if(getWorld()->getObject(ptr,getX(), getY(), 3)){
        if(ptr->getID()==IID_PROTESTER){
            
            ptr->annoyed();
            setDead();
        }
        
        
        
        
    }
    
    if(getDirection()== up)
        moveTo(getX(), getY() + 1);
    
    if(getDirection()==right )
        moveTo(getX()+1,getY());
    
    if(getDirection() == down)
        moveTo(getX(), getY()-1);
    
    if(getDirection()== left)
        moveTo(getX()-1, getY());
    
    if(getTick()== 15)
        setDead();
}
Squirt::~Squirt(){
    setVisible(false);
}
Barrel::Barrel(int startX, int startY, StudentWorld* theWorld)
: Goodies(theWorld, IID_BARREL,startX,startY,right,1,2){
    setVisible(false);
}
void Barrel::doSomething(){
    if(isDead()){
        return;
    }
    //GameObject* ptr;
    if(getWorld()->nearFrackman( getX(), getY(), 4)){
        
        setVisible(true);
    }
    
    if(getWorld()->nearFrackman( getX(), getY(), 3)){
        
        setDead();
        getWorld()->playSound(SOUND_FOUND_OIL);
        getWorld()->increaseScore(1000);
        getWorld()->decBarrels();
        
    }
    // of course first check to makesure it is alive
    // if fraclman is within radius 4 - > , make itself isible return
    // if radius is wihtin 3 , set itself to dead, play sound, gie player 1000 points
}
Barrel::~Barrel(){
    // just delete mamory
}
// construotr for bribe gold
/*Gold::Gold(Frackman* dropper, int startX, int startY)
 : Goodies(dropper,IID_GOLD,startX, startY,right,1,2)
 {
 
 setVisible(true);
 temporary = true;
 permanent = false;
 }*/
// c'tor for regular frackamn pick-up-able gold
Gold::Gold(StudentWorld* theWorld, int startX,int startY, bool temp, bool perm, bool isBribe)
: Goodies(theWorld,IID_GOLD,startX,startY, right,1,2)
{   permanent = perm;
    temporary = temp;
    setVisible(isBribe);
}
void Gold::doSomething(){
    // return if dead
    if(isDead()){
        return ;
    }
    if(permanent){
        if(getWorld()->nearFrackman(getX(), getY(), 4)){
            setVisible(true);
        }
        
        if(getWorld()->nearFrackman(getX(), getY(), 3)){
            setDead();
            getWorld()->playSound(SOUND_GOT_GOODIE);
            getWorld()->increaseScore(10);
            getWorld()->accessPlayer()->increaseGold();
        }
    }
    // this is the code to bribe the protestors
    if(temporary){
        tickCount();
        // find how long this tick count should be
        // to delete item
        GameObject* ptr;
        if(getWorld()->getObject(ptr,getX(), getY(), 3) ){
            if(ptr->getID()== IID_PROTESTER || ptr->getID()==IID_HARD_CORE_PROTESTER){
                setDead();
                getWorld()->playSound(SOUND_PROTESTER_FOUND_GOLD);
                // bribe the protester
                getWorld()->increaseScore(25);
            }
            
        }
    }
    
}
Gold::~Gold(){
    setVisible(false);
}
Sonar::Sonar(StudentWorld* theWorld, int startX, int startY)
: Goodies(theWorld, IID_SONAR, startX, startY, right,1,2)
{
    setVisible(true);
}
void Sonar::doSomething() {
    if(isDead()){
        return ;
    }
    
    int T = fmax(100, 300- 10*getWorld()->getLevel());
    
    tickCount();
    if(getTick() >= T){
        setDead();
    }
    if(getWorld()->nearFrackman(getX(), getY(), 3)){
        setDead();
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->accessPlayer()->increaseSonar();
        getWorld()->increaseScore(75);
        
    }
    
    
}
Sonar::~Sonar(){
    setVisible(false);
}

Water::Water(StudentWorld* theWorld, int startX, int startY)
: Goodies(theWorld, IID_WATER_POOL, startX,startY,right,1,2)
{
    setVisible(true);
    // there are other factors that have to be considered here
    // consult the spec
}
void Water::doSomething(){
    if(isDead()){
        return;
    }
    tickCount();
    int T = fmax(100, 300 - 10*getWorld()->getLevel());
    if(getTick() >=T){
        setDead();
        return ;
    }
    if(getWorld()->nearFrackman(getX(), getY(), 3)){
        setDead();
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->increaseScore(100);
        getWorld()->accessPlayer()->increaseWater();
        
    }
    
    // must be able to detect frackman
    // increse his points by 100
}
Water::~Water(){
    setVisible(false);
}
Protestor::Protestor(StudentWorld* theWorld, int imageID, int startX, int startY)
:GameObject(theWorld, imageID, startX, startY, left,1,0)
{   stunned = false;
    tick2wait = 0;
    yellTicks = 0;
    numSquarestoMove = randInt(8, 60);
    hitpoints = 5;
    bribed = false;
    rageQuit = false;
}
void Protestor::setHitPoints(int htpts){
    hitpoints = htpts;
}
void Protestor::setRageQuit(){
    rageQuit = true;
}
bool Protestor::isRageQuit() const {
    return rageQuit;
}
void Protestor::bribe(){
    bribed = true;
    getWorld()->playSound(SOUND_PROTESTER_FOUND_GOLD);
    getWorld()->increaseScore(25);
    setRageQuit();
}
bool Protestor::isBribed() const {
    return bribed;
}
int Protestor::getHitPoints() const{
    return hitpoints;
}
void Protestor::decHitPoints(int pts){
    hitpoints+=pts;
    if(hitpoints <= 0){
        setRageQuit();
    }
}
bool Protestor::step1(){
    
    
    if(isRageQuit()){
        if(getX()==60 && getY()==60){
            setDead();
        }
        setDead();
        //otherwise compute next step
        //int nextX;
        //int nextY;
        //getWorld()->computePath(getX(), getY(), nextX, nextY);
       // moveTo(nextX, nextY);
        return true;
    }// end rage quit
    
    if(getWorld()->nearFrackman(getX(), getY(), 4)){
        // if same direction as frackman and within radius 4 of frackman
        //if it yelled withing the last 15 resting ticks
        if(yellTicks < 15){
            yellTicks++;
            return true;
        }
        // if it can yell again
        if(yellTicks >=15){
            yellTicks = 0;
            getWorld()->playSound(SOUND_PROTESTER_YELL);
            getWorld()->accessPlayer()->annoyed();
            return true;
        }
        
    } // end if - when protestor is near frackman
    // if it is greater than 4 units then
    return false;
    
    //end tick
}

bool Protestor::step2(){
    // part 4
    
    if(getY()== getWorld()->getPlayerY()){
        if(getX() > getWorld()->getPlayerX()){
            setDirection(left);
            if( !obstacleThere(getX(), getY(), left)){
                moveTo(getX()-1, getY());
            numSquarestoMove = 0;
            return true;
            }
        }
        
        else{
            setDirection(right);
            if( !obstacleThere(getX(), getY(), right)) {
                moveTo(getX()+1, getY());
            numSquarestoMove = 0;
            return true;
            }
        }
        
    }
    
    if(getX()== getWorld()->getPlayerX()){
        if(getY() > getWorld()->getPlayerY()){
            setDirection(down);
            if( !obstacleThere(getX(), getY(), down )){
                moveTo(getX(), getY()-1);
            numSquarestoMove = 0;
            return true;
            }
            
        }
        
        else {
            setDirection(up);
            if( !obstacleThere(getX() , getY(), up) ) {
                moveTo(getX(), getY()+1);
                numSquarestoMove = 0;
                return true;
            }
            
        }
    }
    
    
    
    
    
    
    return false;
    
}
void Protestor::step3(){
    numSquarestoMove--;
    // if numsquares to move is equal to zero;
    if(numSquarestoMove<=0){
        Direction dir;
        //randDir(dir);
        if(!obstacleThere(getX(), getY(), dir)){
            setDirection(dir);
            numSquarestoMove = randInt(8,60);
        }
        
        
        
       
    if(obstacleThere(getX(), getY(), getDirection())){
        numSquarestoMove = 0;
        return;
     }
    }
    
    
    if(!obstacleThere(getX(), getY(), getDirection())){
    moveProtestor(getDirection());
        return ;
    }
    
}
void Protestor::moveProtestor(Direction dir){
    if(dir == left)  moveTo(getX()-1, getY());
    if(dir == right)  moveTo(getX()+1, getY());
    if(dir == up)  moveTo(getX(), getY()+1);
    if(dir == down)  moveTo(getX()-1, getY()-1);
}
void Protestor::randDir(int X, int Y,Direction& dir){
    int rand = randInt(1,4);
    if(rand == 1) dir = left;
    if(rand == 2) dir = up;
    if(rand == 3) dir = right;
    if(rand == 4) dir = down;
   // if(obstacleThere(X, Y, dir)){
    // randDir(X, Y, dir);
  // }
    
}
bool Protestor::obstacleThere(int X, int Y, Direction dir){
    if(dir == left){
            if(getWorld()->boulderThere(X-1, Y) || !getWorld()->isViable(X-1, Y)){
                    return true;
                }
       
     
        return false;
    }
    if(dir == right){
        if(getWorld()->boulderThere(X-1, Y) || !getWorld()->isViable(X-1, Y)){
                    return true;
        }
        return false;
    }
    if(dir == up){
        
        if(getWorld()->boulderThere(X, Y+1) || !getWorld()->isViable(X, Y+1) ){
                    return true;
        }
      
        return false;
    }
    
    if(dir == down){
        if(getWorld()->boulderThere(X, Y-1) || !getWorld()->isViable(X, Y-1)){
                    return true;
            }
       
    return false;
    }
    return false;
   
}

Protestor::~Protestor(){
    setVisible(false);
}
RProtestor::RProtestor(StudentWorld* theWorld, int startX, int startY)
: Protestor(theWorld, IID_PROTESTER,startX, startY)
{   numSquaresToMove = randInt(8,60);
    hitpoints = 5;
    stunned = false;
    stunTicks = 0;
    tick = 0;
    tick2wait = 0;
    yellTicks = 0;
    setVisible(true);
}
void RProtestor::doSomething(){
    if(isDead()){
        return;
        
    }
    int T2wait = fmax(0, 3 - getWorld()->getLevel()/4);
    // if it is in its resting period
    if(stunned) {
        T2wait += fmax(50, 100  - getWorld()->getLevel() * 10);
    }
    
    if(tick2wait < T2wait){
        tick2wait++;
        return ;
    }
    if(isRageQuit()){
        // get the hell out of there;
        setDead();
    }
    // if it is time to do something
    if(tick2wait>=T2wait){
        tick2wait = 0;
        
        yellTicks++;
    if(yellTicks >=15){
    if(getWorld()->nearFrackman(getX(), getY(), 4)){
        getWorld()->accessPlayer()->annoyed();
        getWorld()->playSound(SOUND_PROTESTER_YELL);
        yellTicks = 0;
        return;
    
     }
        }
        
    if(!getWorld()->nearFrackman(getX(), getY(), 4)){
        if(getX() == getWorld()->getPlayerX()){
            if(getY() > getWorld()->getPlayerY()){
                setDirection(down);
                if(getWorld()->isViable(getX(), getY()-1)){
                    moveTo(getX(), getY()-1);
                    numSquaresToMove = 0;
                    return;
                }
            }
            
            else
                setDirection(up);
            if(getWorld()->isViable(getX(), getY()+1)){
                moveTo(getX(), getY()+1);
                numSquaresToMove= 0;
                return;
            }
        }
        if(getY() == getWorld()->getPlayerY()){
            if(getX() > getWorld()->getPlayerX()){
                setDirection(left);
                if(getWorld()->isViable(getX()-1, getY())){
                    moveTo(getX()-1, getY());
                    numSquaresToMove = 0;
                    return;
                }
            }
            
            else
                setDirection(right);
            if(getWorld()->isViable(getX()+1, getY())){
                moveTo(getX()+1, getY());
                numSquaresToMove= 0;
                return;
            }
        }

    }
        
        
        
        numSquaresToMove--;
        if(numSquaresToMove<=0){
            Direction dir;
            randDir(getX(), getY(), dir);
            setDirection(dir);
            numSquaresToMove = randInt(8, 60);
        }
        
        if(obstacleThere(getX(), getY(), getDirection())){
            numSquaresToMove = 0;
            return;
        }
        
        else if (!obstacleThere(getX(), getY(), getDirection())){
            moveProtestor(getDirection());
        }
    
        }
}
void RProtestor::annoyed(){
    hitpoints-=2;
    if(hitpoints < 0) {
        setRageQuit();
        getWorld()->playSound(SOUND_PROTESTER_GIVE_UP);
        tick2wait = 0;
    }
}
RProtestor::~RProtestor(){
    
    setVisible(false);
}
HProtestor::HProtestor(StudentWorld* theWorld, int startX, int startY)
: Protestor(theWorld, IID_HARD_CORE_PROTESTER,startX, startY)
{
    setHitPoints(10);
    setVisible(true);
}
void HProtestor::doSomething(){
    if(isDead()){
        return;
    }
    
    
    //add the code that determines the M- blah blah blah
}
void HProtestor::annoyed(){
    // whateer annoyes the protestor
}
HProtestor::~HProtestor(){
    setVisible(false);
}
