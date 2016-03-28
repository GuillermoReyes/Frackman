#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include "Actor.h"
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
#include <sstream>
#include <iomanip>
const char WALL = 'X';
const char OPEN = '.';
const char SEEN = 'o';

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};


using namespace std;
int randInt(int min, int max);
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir)
    : GameWorld(assetDir)
    {
    }
    ~StudentWorld();
    virtual int init()
    {   ProtestorCount = 0;
        t_count = 0;
        for(int i = 0; i < 64; i++){
            for(int j = 0; j < 64 ; j++){
                dirt[i][j] = new Dirt(i,j,this);
            }
        }
       // clear dirt at top
        for(int i = 60; i<64; i++){
            for(int j = 0; j<64; j++){
                dirt[j][i]->setDead();
            }
        }
        
        
        
        
        
        //create the vertical bar down the middle of the oil field
        for(int i = 30; i < 34; i++)
            for(int j = 3; j <60; j++)
                dirt[i][j]->setDead();
        
        
        
        
        
        
        int B = fmin(getLevel()/2 + 2, 6);
        int G = fmax(5 - getLevel()/2, 2);
        int L = fmin(2 + getLevel(), 20);
        
        setBarrels(L);
        for(int i = 0; i < L; i++){
            int x = randInt(1, 26);
            int x2 = randInt(35,60);
            int choose1 =  randInt(1,2);
            int y = randInt(1, 55);
            if(choose1==1){
            
            Barrel* hi = new Barrel(x,y, this);
            m_actor.push_back(hi);
            
            }
            if(choose1==2){
                
                    Barrel* hi = new Barrel(x2,y, this);
                    m_actor.push_back(hi);
                
            }
        }
        for(int i = 0; i < G; i++){
            int x = randInt(1, 54);
            int y = randInt(1, 55);
            if(!isInShaft(x, y)){
            Gold* gold = new Gold(this, x,y, false, true, false);
            m_actor.push_back(gold);
            }
        }
        for(int i = 0; i < B; i++){
            int x = randInt(1, 54);
            int y = randInt(4, 54);
            
            
            if(!isInShaft(x, y)){
            Boulder* boulder = new Boulder(this, x,y);
            m_actor.push_back(boulder);
        
            for(int i = 0; i <=3; i++)
                for(int j = 0; j<=3; j++)
                    dirt[x+i][y+j]->setDead();
            
            }
            // add int he first protestor;
            
            
            
        }
        RProtestor*   protestor = new RProtestor(this, 60,60);
        m_actor.push_back(protestor);
        player = new Frackman(30,60,this);
        m_actor.push_back(player);
              // theSonar = new Sonar(this, 10,10);
        //m_actor.push_back(theSonar);
        
       // theWater = new Water(this, 15,18);
        //m_actor.push_back(theWater);
        
         //thePro = new HProtestor(this, 30, 30);
       // m_actor.push_back(thePro);
        
        return GWSTATUS_CONTINUE_GAME;
    }
    
    virtual int move()
    {
        t_count++;
        int T = fmax(25, 200 - getLevel());
        int P = fmin(15, 2 + getLevel() * 1.5) -1;
        int goodiechance =  getLevel()* 25 + 300;
        
        if(goodiechance >=1 && goodiechance <= 200){
            int either = randInt(1, 5);
            int x = randInt(0, 59);
            int y = randInt(0, 59);
            if(either==1 ){
                
                Sonar* sonar = new Sonar(this,0, 60 );
                m_actor.push_back(sonar);
            }
            if(either>1 && isViable(x,y) && !isInShaft(x, y)){
                Water* water = new Water(this, x, y);
                m_actor.push_back(water);
            }
            
        }
        
        
        if(t_count>=T && ProtestorCount < P){
            int Probability = fmin(90, getLevel() * 10 + 30);
            int sample = randInt(1, T);
            if(sample <=Probability){
                // generate a hardcore protestor
            }
            // otherwise generate a ergular protesor
            else
                t_count = 0;
            // make the protestor generation equally distribited
            Protestor* jeff = new RProtestor(this, 60, 60);
            m_actor.push_back(jeff);
            ProtestorCount++;
            // randomly generate a protestor
           
        }
        // display stats
        int score = getScore();
        ostringstream ss;
        
        ss.fill('0');
        ss<<setw(6)<<score<<endl;
        
        ostringstream s1;
        s1<<setw(3)<<getLevel()<<endl;
        
        ostringstream sh;
        double hitpoints = double(player->getHitPoints());
        sh<<setw(3)<<hitpoints/10 *100;
        
       
        std::string s = std::to_string(getLives());
        std::string scr = ss.str();
        std::string lvl = to_string(getLevel());
        std::string lvs = std::to_string(getLives());
        std::string gold = std::to_string(player->getGold());
        std::string water = std::to_string(player->getWater());
        std::string sonar = std::to_string(player->getSonar());
        std::string Bar = std::to_string(getBarrels());
        std::string hlth = sh.str();

        // need to properly implement this feature
        // not yet working
        if(getBarrels()<=0){
            return GWSTATUS_FINISHED_LEVEL;
            
        }
        
        setGameStatText("Scr: "+ scr+" Lvl: "+lvl +" Lives: " +lvs+" Hlth: "+ hlth+ "%  Water: "+water +
                        " Gld: " + gold+ " Sonar: " + sonar+ " Oil left: " + Bar);
        
        for(int i = 0; i < m_actor.size(); i++){
            if(!m_actor.at(i)->isDead())
                m_actor.at(i)->doSomething();
        }
        
        for(int i=0; i<m_actor.size(); i++)
            if(m_actor.at(i)->isDead())
            {
                
                
                
                std::vector<GameObject*>::iterator iter=m_actor.begin(); //create an iterator
                for(int j=0; j<i; j++)
                    iter++;
                m_actor.erase(iter);
                i--;
                
            }
        
        
        
        if(player->isDead()){
            return GWSTATUS_PLAYER_DIED;
        }
        if(getLives()<=0){
           // player lost restart a game
        }
        // This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
        // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
        //decLives();
        //return GWSTATUS_PLAYER_DIED;
        return GWSTATUS_CONTINUE_GAME;
    }
    
    void cleanDead();
    virtual void cleanUp()
    {
        // implement this
        for(int i = 0; i < m_actor.size(); i++){
            delete m_actor.at(i);
        }
        m_actor.clear();
        
        
        for(int i = 0; i < 64; i++)  {
            for(int j = 0; j < 60 ; j++)
                delete dirt[i][j];
        }
        
        
        
        
    }
    
    // return true and sets a pointer if it is true;
    Frackman* accessPlayer();
    // gets player that is there
    bool getObject(GameObject* &mp, int x, int y, int radius);
    bool nearFrackman(int X, int Y, int radius);
    // coordinateds of frakman
    int getPlayerX();
    int getPlayerY();
    //unietrsal tick count
    bool tickCount(const int& interval);
    void setBarrels(int amount);
    void decBarrels();
    int  getBarrels() const ;
    // ode to delete dirt as frackman moves
    void manageDirt(int X, int Y );
    bool dirtThere(int X, int Y);
    // sotre an objet
    void storeItem(GameObject* item);
    void computePath(int currx, int curry , int& nextX, int& nextY);
    // checls if there is a boulder there
    bool  boulderThere(int X, int Y);
    bool  isViable(int X, int Y);
    bool isInShaft(int X, int Y);
    bool pathExists( int nRows, int nCols, int sr, int sc, int er, int ec);
    void updateMaze();
    void explore( int r, int c);
    
private:
  
    
    // worst case scenario
    char a[61][61];
    queue<Coord> toDo;
    int ProtestorCount;
    HProtestor* thePro;
    Water* theWater;
    Sonar* theSonar;
    
    Boulder* theBoulder;
    
    int t_count;
    int m_barrels;
    Frackman* player;
    //[X][Y]
    Dirt* dirt[64][64];
    std::vector<GameObject*> m_actor;
};

#endif

