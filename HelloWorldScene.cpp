#include "HelloWorldScene.h"
#include <stdio.h>
#include <math.h>
#define FALLING_TIME 5
#define VEC_SIZE 1000
USING_NS_CC;


void HelloWorld::fill_symbols() {
    all_symbols.push_back("L");
    all_symbols.push_back("O");
    all_symbols.push_back("V");
    all_symbols.push_back("E");
    all_symbols.push_back("そ");
    all_symbols.push_back("ば");
    all_symbols.push_back("に");
    all_symbols.push_back("い");
    all_symbols.push_back("て");
    all_symbols.push_back("ほ");
    all_symbols.push_back("し");
    all_symbols.push_back("사");
    all_symbols.push_back("랑");
    all_symbols.push_back("L");
    all_symbols.push_back("O");
    all_symbols.push_back("V");
    all_symbols.push_back("E");
    all_symbols.push_back("사");
    all_symbols.push_back("랑");
    all_symbols.push_back("해");
    all_symbols.push_back("ฉั");
    all_symbols.push_back("น");
    all_symbols.push_back("L");
    all_symbols.push_back("O");
    all_symbols.push_back("V");
    all_symbols.push_back("E");
    all_symbols.push_back("사");
    all_symbols.push_back("랑");
    all_symbols.push_back("해");
    all_symbols.push_back("รั");
//
//    Vec2 tv = Vec2(10, 10);
//    set<Vec2> vs;
//    vs.insert(Vec2(10,10));
//    vs.insert(Vec2(10, 29));
//    vs.insert(Vec2(15, 29));
//    if (vs.count(tv) > 0) {
//        CCLOG("find vec2");
//    }
}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...
    timer = 0;
    fill_symbols();
    load_characters();
    schedule(schedule_selector(HelloWorld::symbols_falling), 0.005);
    schedule(schedule_selector(HelloWorld::check_touch), 0.5);
//    show_char(0);
    return true;
}

Label * HelloWorld::rand_add_label(Label* label) {
    if (nullptr == label) {
        double rand_num = CCRANDOM_0_1();
        string& txt = all_symbols[floor(rand_num * all_symbols.size())];
        int font_size = 25*(rand_num + 1);
        label = Label::create(txt.c_str(), "Arial", font_size);
        label->setTextColor(Color4B(0, rand_num*20 + 80, 0, rand_num*255));
        this->addChild(label, rand_num*100);
    }
    int label_left =  origin.x + label->getContentSize().width/2;
    int label_right = visibleSize.width - label->getContentSize().width/2;
    int label_up = visibleSize.height - label->getContentSize().height/2 +
                    visibleSize.height*CCRANDOM_0_1();
    
    label->setPosition(Vec2(CCRANDOM_0_1()*(label_right - label_left) + label_left,
                            label_up));
  
    label->runAction(
        MoveBy::create(FALLING_TIME, Vec2(0, -label_up - label->getContentSize().height))
                         );
    return label;
}
void HelloWorld::symbols_falling(float)
{
    if (label_vec.size() < VEC_SIZE) {
        // 增加一个label
        auto label = rand_add_label();
        Color4B col = label->getTextColor();
        label_vec.push_back({
            label,
            Color4B(col.r, col.g*2 + 55, col.b, col.a),
            col
        });
    }
}
void HelloWorld::check_touch(float t) {
    timer += t;
    int char_id = 0;
    if (timer > 30) {
        timer = 0;
    }
    if (timer < 10) {
        char_id = 0;
    } else if (timer < 20) {
        char_id = 1;
    } else if (timer < 30) {
        char_id = 2;
    }
    set<Vec2>& vec_set = character_vec[char_id];
    
    for (auto mylabel : label_vec) {
        auto label = mylabel.label;
        auto pos = label->getPosition();
        // 检查是否有到达底部的label，有的话重新放回顶部
        if (pos.y < 0) {
            rand_add_label(label);
        }
        // highlight the label:
        if (vec_set.count(Vec2((int)pos.x, (int)pos.y)) > 0) {
            label->setTextColor(mylabel.hilight);
            label->stopAllActions();
        } else {
            if (label->getNumberOfRunningActions() == 0) {
                label->setTextColor(mylabel.normal);
                label->runAction(MoveBy::create(FALLING_TIME, Vec2(0, -pos.y - visibleSize.height)));
            }
        }
    }
}

void HelloWorld::show_char(float) {
    set<Vec2>&char_sym = character_vec[1];
    for (int i = 0; i < visibleSize.width; ++i) {
        for (int j = 0; j < visibleSize.height; ++j ) {
            auto pos = Vec2(i,j);
            if (char_sym.count(pos) > 0) {
                auto l = Label::create("*", "Arial", 20);
                l->setPosition(pos);
                this->addChild(l, 1);
            }
        }
    }
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::load_characters() {
    int min_len = std::min(visibleSize.width, visibleSize.height);
    const double character_size = 600;
    double scale = min_len/character_size;
    double xp = visibleSize.width/2 - min_len/2;
    double yp = visibleSize.height/2 - min_len/2;
    char file_name[100];
    int xloc, yloc;
    character_vec.resize(3);
    for (int i = 1; i <= 3; ++i) {
        sprintf(file_name, "%d.txt", i);
        const string cs_file_path = FileUtils::getInstance()->fullPathForFilename(file_name);
        FILE* fid = fopen(cs_file_path.c_str(), "r");
        set<Vec2> &v = character_vec[i-1];
        while (fscanf(fid, "%d,%d", &yloc, &xloc) != EOF) {
            int x = xp + xloc*scale;
            int y = yp + (character_size - yloc)*scale;
            v.insert(Vec2(x,y));
        }
    }
}
