//
//  ofxMultiFboBlur.h
//  ofxMultiFboBlur
//
//  Created by  Tyler Parker on 4/13/15.
//
//

#include "ofMain.h"
#include "ofxFboBlur.h"
#include "ofxMask.h"

#pragma once



class ofxMultiFboBlur{
    
public:
    ofxMultiFboBlur();
    ~ofxMultiFboBlur();
    void setup(ofFbo::Settings s, int levels = 1, float levelBlurSize = 10.0f, float crossfadePercent = 0.8);

    void beginDrawScene();
    void endDrawScene();
    void performBlur();
    
    void drawBlurFbo();
    void drawSceneFbo();
    
    float getBlurOffset();
    int getBlurPasses();
    int getNumBlurOverlays();
    
    ofxFboBlur* getLevel(int level);
    
    int getWidth();
    int getHeight();

    void setBlurOffset(float blurOffset);
    void setBlurPasses(int blurPasses);
    void setNumBlurOverlays(int numBlurOverlays);
    float getLevelScale(int level);
    
    float getInterpolatedLevel();

private:
    float blurOffset;
    float levelBlurSize;
    float crossFadePercent;
    int blurPasses;
    int numBlurOverlays;
    int blurOverlayGain;
    float getCrossfade();
    void drawScaledTexture(ofTexture& tex, float scaleDown);
    deque<ofxFboBlur*> fboBlurLevels;
    ofxMask mask;
};