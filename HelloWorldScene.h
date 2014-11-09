#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <vector>
#include "config.h"
#include "MyLabel.h"
USING_NS_CC;
using namespace std;
class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
private:
    vector<string> all_symbols;
    vector<MyLabel*> label_vec;
    vector<Action*> action_vec;
    vector<char**> character_mat;
    Size visibleSize;
    Vec2 origin;
    double timer;
    
    
    void init_add_labels(float);
    void time_circle(float);
    void show_char(float);
    MyLabel* rand_add_label();
    void load_characters();
    void fill_symbols();
    
};

#endif // __HELLOWORLD_SCENE_H__
