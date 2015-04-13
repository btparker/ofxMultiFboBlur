#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableAlphaBlending();
    ofSetFrameRate(60);
    levels = 5;
    
    img.load("hall-thruster.jpg");
    tex.loadData(img.getPixels());
    ofSetWindowShape(tex.getWidth()/2.0, tex.getHeight()/2.0);
    
    //choose your fbo settings
    ofFbo::Settings fboS;
    fboS.width = img.getWidth();
    fboS.height = img.getHeight();
    fboS.internalformat = GL_RGB;
    
    //setup thing
    multiFboBlur.setup(fboS, levels, 40.0f);
    multiFboBlur.setNumBlurOverlays(1);
}

//--------------------------------------------------------------
void ofApp::update(){
    //tweak your blurring
    multiFboBlur.setBlurOffset(200 * ofMap(mouseX, 0, ofGetWidth(), 0, 1, true));
    multiFboBlur.setBlurPasses(10. * ofMap(mouseY, 0, ofGetHeight(), 1, 0, true));
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(22);
    
    multiFboBlur.beginDrawScene();
    ofClear(0,0,0);
    ofSetColor(ofColor::white);
    tex.draw(0, 0, tex.getWidth(), tex.getHeight());
    multiFboBlur.endDrawScene();
    
    multiFboBlur.performBlur();
    
    ofPushMatrix();
    ofScale(0.5, 0.5);
    multiFboBlur.drawBlurFbo();
    ofPopMatrix();

    //draw info
    string info =   "framerate: " + ofToString(ofGetFrameRate()) + "\n" +
    "blurOffset: " + ofToString(multiFboBlur.getBlurOffset()) + "\n" +
    "blurPasses: " + ofToString(multiFboBlur.getBlurPasses()) + "\n" +
    "interpolated level: " + ofToString(multiFboBlur.getInterpolatedLevel());
    ofDrawBitmapStringHighlight(info, 20,20);
    
    ofDrawBitmapStringHighlight("MouseX to control Blur Passes\nMouseY to control blur Offset", 400,20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}