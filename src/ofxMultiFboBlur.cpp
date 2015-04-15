//
//  ofxMultiFboBlur.cpp
//  ofxMultiFboBlur
//
//  Created by  Tyler Parker on 4/13/15.
//
//

#include "ofxMultiFboBlur.h"

ofxMultiFboBlur::ofxMultiFboBlur(){
    
}

ofxMultiFboBlur::~ofxMultiFboBlur(){
    for(int level = 0; level < fboBlurLevels.size(); level++){
        delete getLevel(level);
    }
}

void ofxMultiFboBlur::setup(ofFbo::Settings s, int levels, float levelBlurSize, float crossFadePercent){
    this->levelBlurSize = levelBlurSize;
    this->crossFadePercent = crossFadePercent;
    mask.setup(s, ofxMask::LUMINANCE, true);
    for(int level = 0; level < levels; level++){
        ofxFboBlur* fboBlurLevel = new ofxFboBlur();
        fboBlurLevel->setup(s, true, getLevelScale(level));
        fboBlurLevel->blurOverlayGain = 255;
        fboBlurLevels.push_back(fboBlurLevel);
    }
}

float ofxMultiFboBlur::getLevelScale(int level){
    return 1.0f/pow(2.0f,level);
}

float ofxMultiFboBlur::getInterpolatedLevel(){
    return min(blurOffset/levelBlurSize, 1.0f*(fboBlurLevels.size()-1));
}
               
float ofxMultiFboBlur::getCrossfade(){
    float il = getInterpolatedLevel();
    float percent = ofMap(il, floor(il), floor(il+1), 0.0f, 1.0f);
    float crossFadeBuffer = (1.0f-crossFadePercent)/2.0f;
    return ofMap(percent, crossFadeBuffer, 1.0-crossFadeBuffer, 0.0f, 1.0f, true);
}
               
int ofxMultiFboBlur::getWidth(){
    return isAllocated() ? getLevel(0)->getSceneFbo().getWidth() : 0;
}

int ofxMultiFboBlur::getHeight(){
    return isAllocated() ? getLevel(0)->getSceneFbo().getHeight() : 0;
}

void ofxMultiFboBlur::beginDrawScene(){
    getLevel(0)->beginDrawScene();
}

void ofxMultiFboBlur::endDrawScene(){
    getLevel(0)->endDrawScene();
    for(int i = 1; i < fboBlurLevels.size(); i++){
        getLevel(i)->beginDrawScene();
        ofSetColor(255);
        getLevel(0)->drawSceneFBO();
        getLevel(i)->endDrawScene();
    }
}

void ofxMultiFboBlur::performBlur(){
    int levelA = floor(getInterpolatedLevel());
    int levelB = ceil(getInterpolatedLevel());
    
    float crossfade = getCrossfade();

    getLevel(levelA)->performBlur();
    
    if(crossfade > 0.0f){
        getLevel(levelB)->performBlur();
    }
}

void ofxMultiFboBlur::drawBlurFbo(){
    int levelAIndex = floor(getInterpolatedLevel());
    int levelBIndex = ceil(getInterpolatedLevel());
    
    float crossfade = getCrossfade();
    ofTexture& texA = getLevel(levelAIndex)->getBlurredSceneFbo().getTexture();
    
    if(crossfade > 0){
        mask.beginA();
        texA.draw(0, 0, getWidth(), getHeight());
        mask.endA();
        
        ofTexture& texB = getLevel(levelBIndex)->getBlurredSceneFbo().getTexture();
        
        mask.beginB();
        texB.draw(0, 0, getWidth(), getHeight());
        mask.endB();
        
        mask.beginMask();
        ofSetColor((1.0f-crossfade)*255);
        ofDrawRectangle(0, 0, mask.getWidth(), mask.getHeight());
        mask.endMask();
        
        mask.draw();
    }
    else{
        texA.draw(0, 0, getWidth(), getHeight());
    }
    
}

void ofxMultiFboBlur::drawScaledTexture(ofTexture& tex, float scaleDown){
#if (OF_VERSION_MINOR >= 8)
    tex.draw(0, 0, tex.getWidth() / scaleDown, tex.getHeight() / scaleDown);
#else
    tex.draw(0, tex.getHeight(), tex.getWidth() / scaleDown, -tex.getHeight() / scaleDown);
#endif
}

void ofxMultiFboBlur::drawSceneFbo(){
    getLevel(0)->drawSceneFBO();
}
               
ofxFboBlur* ofxMultiFboBlur::getLevel(int level){
    if(level < 0 || level >= fboBlurLevels.size()){
        ofLogError("ofxMultiFboBlur::getLevel", "No corresponding level for "+ofToString(level)+", returning NULL");
        return NULL;
    }
    return fboBlurLevels[level];
}

float ofxMultiFboBlur::getBlurOffset(){
	return this->blurOffset;
}
int ofxMultiFboBlur::getBlurPasses(){
	return this->blurPasses;
}
int ofxMultiFboBlur::getNumBlurOverlays(){
	return this->numBlurOverlays;
}

void ofxMultiFboBlur::setBlurOffset(float blurOffset){
	this->blurOffset = blurOffset;
    for(int level = 0; level < fboBlurLevels.size(); level++){
        ofxFboBlur* fboBlurLevel = getLevel(level);
        float scaleDown = getLevelScale(level);
        fboBlurLevel->blurOffset = this->blurOffset*scaleDown;
    }
}

void ofxMultiFboBlur::setBlurPasses(int blurPasses){
	this->blurPasses = blurPasses;
    for(int level = 0; level < fboBlurLevels.size(); level++){
        ofxFboBlur* fboBlurLevel = getLevel(level);
        fboBlurLevel->blurPasses = this->blurPasses;
    }
}

void ofxMultiFboBlur::setNumBlurOverlays(int numBlurOverlays){
	this->numBlurOverlays = numBlurOverlays;
    for(int level = 0; level < fboBlurLevels.size(); level++){
        ofxFboBlur* fboBlurLevel = getLevel(level);
        fboBlurLevel->numBlurOverlays = this->numBlurOverlays;
    }
}

bool ofxMultiFboBlur::isAllocated(){
    return fboBlurLevels.size() > 0;
}