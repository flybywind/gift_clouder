#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <vector>

USING_NS_CC;
using namespace std;

struct LabelTowColor {
    Label* label;
    Color4B hilight;
    Color4B normal;
};
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
    vector<Rect> char_rect_border;
    vector<string> all_symbols;
    vector<LabelTowColor> label_vec;
    vector<Action*> action_vec;
    vector<char**> character_mat;
    Size visibleSize;
    Vec2 origin;
    void symbols_falling(float);
    void check_touch(float);
    void show_char(float);
    Label* rand_add_label(Label * label=nullptr);
    void load_characters();
    void fill_symbols();
    
    double timer;
};

#endif // __HELLOWORLD_SCENE_H__
