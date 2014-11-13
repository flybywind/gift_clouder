//
//  MyLabel.h
//  gift_clouder
//
//  Created by flybywind on 14/11/9.
//
//

#ifndef gift_clouder_MyLabel_h
#define gift_clouder_MyLabel_h
#include "cocos2d.h"
#include <string>
#include <vector>
#include "config.h"
USING_NS_CC;
using namespace std;

class MyLabel : public Label {
public:
    static MyLabel* create(const string& txt,
                   const string& font,
                   float font_size,
                   Color4B normal_color = Color4B::WHITE,
                   Color4B hilight_color = Color4B::WHITE);
    static int back_char_id;
    static vector<char**> back_char_mat;
    
    void setHilightColor();
    void setNormalColor();
    void fallFromUp();
    
    
private:
    Color4B normal_color;
    Color4B hilight_color;
    Size visibleSize;
    Vec2 origin;
    
    MyLabel(Color4B normal_color, Color4B hilight_color);
    void CheckTouch(float);
};


#endif
