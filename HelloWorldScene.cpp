#include "HelloWorldScene.h"
#include <stdio.h>
#include <math.h>
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
    MyLabel::back_char_id = 0;
    MyLabel::back_char_mat = character_mat;
    schedule(schedule_selector(HelloWorld::init_add_labels), 0.5, VEC_SIZE/50, 0);
    schedule(schedule_selector(HelloWorld::time_circle), EACH_CHAR_TIME/2.0);
//    show_char(0);
    return true;
}

MyLabel * HelloWorld::rand_add_label() {
    double rand_num = CCRANDOM_0_1();
    string& txt = all_symbols[floor(rand_num * all_symbols.size())];
    int font_size = 25*(rand_num + 1);
    auto label = MyLabel::create(txt, "Arial", font_size,
                            Color4B(0, rand_num*20 + 80, 0, rand_num*255),
                            Color4B(0, rand_num*40 + 215, 0, rand_num*255)
                        );
    this->addChild(label, rand_num*100);
    label->fallFromUp();
    return label;
}
void HelloWorld::init_add_labels(float)
{
    if (label_vec.size() < VEC_SIZE) {
        // 增加多个label
        for (int i = 0; i < 50; ++ i) {
            auto label = rand_add_label();
            label_vec.push_back(label);
        }
    }
}
void HelloWorld::time_circle(float t) {
    timer += t;
    if (timer > 3*EACH_CHAR_TIME) {
        timer = 0;
    }
    MyLabel::back_char_id = (int)timer/EACH_CHAR_TIME;
}
void HelloWorld::show_char(float) {
    Rect r = char_rect_border[1];
    char** mat = character_mat[1];
    for (int i = 0; i < visibleSize.width; i += 5) {
        for (int j = 0; j < visibleSize.height; j += 5 ) {
            auto pos = Vec2(i,j);
            if (r.containsPoint(pos) && mat[i][j] > 0) {
                auto l = MyLabel::create("*", "Arial", 20);
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
    char_rect_border.resize(3);
    character_mat.resize(3);
    for (int i = 1; i <= 3; ++i) {
        sprintf(file_name, "%d.txt", i);
        const string cs_file_path = FileUtils::getInstance()->fullPathForFilename(file_name);
        FILE* fid = fopen(cs_file_path.c_str(), "r");
        char** &mat = character_mat[i-1];
        Rect& rect = char_rect_border[i-1];
        int left = visibleSize.width;
        int right = 0;
        int up = 0;
        int buttom = visibleSize.height;
        // initial mat:
        int mat_width = (int)visibleSize.width;
        int mat_height = (int)visibleSize.height;
        mat = new char*[mat_width];
        for (int i = 0; i < mat_width; ++i) {
            mat[i] = new char[mat_height];
            bzero(mat[i], mat_height);
        }
        
        while (fscanf(fid, "%d,%d", &yloc, &xloc) != EOF) {
            int x = xp + xloc*scale;
            int y = yp + (character_size - yloc)*scale;
            mat[x][y] = 1;
            if (x < left) {
                left = x;
            }
            if (x > right) {
                right = x;
            }
            if (y < buttom) {
                buttom = y;
            }
            if (y > up) {
                up = y;
            }
        }
        rect.setRect(left, buttom, right - left, up - buttom);
    }
}
