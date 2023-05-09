#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetDataPathRoot("../Resources/data/");
    ofBackground(0, 0, 0);
    ofSetVerticalSync(true);
    ofSetCircleResolution(64);
    ofEnableAlphaBlending();
        
    radius = 0; //円の半径
    r = 0;
    b = 255;
    //bufSize = 152;
    
    nBandsToGet = 1024;
    
    //spectrum = new float[bufSize];
    mySound.load("beat.wav"); //サウンドファイルの読込み
    mySound.setLoop(true); //ループ再生をONに
}

//--------------------------------------------------------------
void ofApp::update(){
    float * val = ofSoundGetSpectrum(1); //再生中のサウンドの音量を取得
    radius = val[0] * 3000.0; //円の半径に適用
    fft = ofSoundGetSpectrum(nBandsToGet);
}

//--------------------------------------------------------------
void ofApp::draw(){
    float width = float(ofGetWidth())/float(nBandsToGet)/2.0f;
    pan = float(ofGetWidth())/2.0f;
    // 音量に応じた半径でマウスの位置に円を描く
    ofFill();
    ofSetColor(r, 63, b, 180);
    ofDrawCircle(mouseX, mouseY, radius);
    
    ofSetColor(255, 255, 255, 20);
    ofNoFill();
    ofSetLineWidth(2);
    
    for(int i = 0; i < nBandsToGet; i++){
        ofDrawCircle(pan+width*i, ofGetHeight()/2, fft[i]*400);
        ofDrawCircle(pan-width*i, ofGetHeight()/2, fft[i]*400);
        
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    //パンの設定
    mySound.setPan(x / (float)ofGetWidth() * 2 - 1.0f);
    //再生スピード変更
    mySound.setSpeed( 0.5f + ((float)(ofGetHeight() - y) / (float)ofGetHeight())*1.0f);
    r = (int)((255*(ofGetHeight()-y)/ofGetHeight()));
    b = (int)(255*y/ofGetHeight());
    if(b > 100){
        b = 100;
    }
    //r = 100;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    //パンの設定
    mySound.setPan(x / (float)ofGetWidth() * 2 - 1.0f);
    //再生スピード設定
    mySound.setSpeed( 0.5f + ((float)(ofGetHeight() - y) / (float)ofGetHeight())*1.0f);
    r = (int)((255*(ofGetHeight()-y)/ofGetHeight()));
    b = (int)(255*y/ofGetHeight());
    if(b > 100){
        b = 100;
    }
    //サウンド再生開始
    mySound.play();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    mySound.stop(); //サウンド再生終了
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
