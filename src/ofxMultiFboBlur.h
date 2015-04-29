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
    /// \brief Generates the levels and assigns settings
    ///
    /// \param ofFbo::Settings s Settings to apply to base blur level, and excluding dimension settings to all subsequent blur levels
    /// \param int levels (optional) Number of levels to allocate (each one half the resolution of the last), needs at least 2
    /// \param float levelBlurSize (optional) Blur amount step to switch between levels, 0 blur would be the base level, blur at levelBlurSize will be the next level, half levelBlurSize will be halfway between the two
    /// \param float crossfadePercent (optional) Percent of the blur distance between levels to crossfade over, centered around midpoint. 1.0 would be continual fade
    void setup(ofFbo::Settings s, int levels = 2, float levelBlurSize = 10.0f, float crossfadePercent = 0.8);
    
    void beginDrawScene();
    void endDrawScene();
    
    /// \brief Performs blur across the two active levels
    void performBlur();
    
    /// \brief Draws the blurred scene
    void drawBlurFbo();
    
    /// \brief Draws the original scene
    void drawSceneFbo();
    
    float getBlurOffset();
    int getBlurPasses();
    int getNumBlurOverlays();
    
    void setBlurOffset(float blurOffset);
    void setBlurPasses(int blurPasses);
    void setNumBlurOverlays(int numBlurOverlays);
    
    /// \brief Returns a pointer to the ofxFboBlur level
    ///
    /// \param int level 0 indexed
    ofxFboBlur* getLevel(int level);
    
    // Gets the width/height of the base level
    int getWidth();
    int getHeight();

    /// \brief Returns number that represents what levels are being faded between, with the floor and ceiling being the level indices
    float getInterpolatedLevel();
    
    bool isAllocated();

private:
    float blurOffset;
    float levelBlurSize;
    float crossFadePercent;
    int blurPasses;
    int numBlurOverlays;
    int blurOverlayGain;
    
    float getLevelScale(int level);
    float getCrossfade();
    void drawScaledTexture(ofTexture& tex, float scaleDown);
    
    deque<ofxFboBlur> fboBlurLevels;
    
    // Uses ofxMask to blend between levels
    ofxMask mask;
};