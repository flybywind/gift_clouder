//
//  MyLabel.cpp
//  gift_clouder
//
//  Created by flybywind on 14/11/9.
//
//

#include "MyLabel.h"

vector<char**> MyLabel::back_char_mat;
int MyLabel::back_char_id = 0;

MyLabel* MyLabel::create(const string& txt,
                         const string& font_name,
                         float font_size,
                         Color4B normal_color,
                         Color4B hilight_color) {
    MyLabel* ret = new MyLabel(normal_color, hilight_color);
    if (ret == nullptr) {
        delete ret;
        return nullptr;
    }
    ret->autorelease();
    ret->setString(txt);
    ret->setSystemFontName(font_name);
    ret->setSystemFontSize(font_size);
    ret->setTextColor(normal_color);
    
    return ret;
}

MyLabel::MyLabel(Color4B normal_color,
                 Color4B hilight_color ){
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    this->normal_color = normal_color;
    this->hilight_color = hilight_color;
}

void MyLabel::setHilightColor() {
    this->setTextColor(hilight_color);
}

void MyLabel::setNormalColor() {
    this->setTextColor(normal_color);
}

void MyLabel::fallFromUp() {
    int label_left =  origin.x + getContentSize().width/2;
    int label_right = visibleSize.width - getContentSize().width/2;
    int label_up = visibleSize.height - getContentSize().height/2 +
                    visibleSize.height*CCRANDOM_0_1();
    
    setPosition(Vec2(CCRANDOM_0_1()*(label_right - label_left) + label_left,
                            label_up));
    
    schedule(schedule_selector(MyLabel::CheckTouch), 0.5);
    runAction(MoveBy::create(FALLING_TIME,
                                    Vec2(0,
                             -label_up - getContentSize().height)));
    
}
void MyLabel::CheckTouch(float) {
    auto pos = getPosition();
    if (pos.y < 0) {
        fallFromUp();
        setNormalColor();
    } else {
        if (back_char_id >= back_char_mat.size()) {
            if (getNumberOfRunningActions() == 0) {
                setNormalColor();
                runAction(MoveBy::create(FALLING_TIME, Vec2(0, -pos.y - visibleSize.height)));
            }
            return;
        }
        auto mat = back_char_mat[back_char_id];
        if (mat[(int)pos.x][(int)pos.y] > 0) {
            setHilightColor();
            stopAllActions();
        } else {
            if (getNumberOfRunningActions() == 0) {
                setNormalColor();
                runAction(MoveBy::create(FALLING_TIME, Vec2(0, -pos.y - visibleSize.height)));
            }
        }
    }
}