/*
 * 2016/03/09　アーロと少年　FireBugs インタラクティブシステム
 * 赤外線で人の動体検知。
 * ホタルを飛ばす
 * ホタルはその場にとどまる、飛び立つ。の二種類。
 * 飛び立ったホタルはアーロのシルエットを形成するように集まり、人がそこへ行くと飛散する
 */


#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    gui.setup(); // most of the time you don't need a name

    gui.loadFromFile("settings.xml");
    
    //画面の基本設定
    ofBackground(0, 0, 0);
    ofEnableAlphaBlending();
    
    

    iR_Viewer.setup();    //動体検知初期化
}

//--------------------------------------------------------------
void ofApp::update(){
    iR_Viewer.update();     //動体検知アップデート

}

//--------------------------------------------------------------
void ofApp::draw(){
    iR_Viewer.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    iR_Viewer.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::exit(){
    gui.saveToFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    printf("x:%d,:y%d",x,y);
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
