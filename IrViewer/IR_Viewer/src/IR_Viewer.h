#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxOsc.h"
#include "ofxGui.h"

class IR_Viewer{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    int WIDTH = 1024;
    int HEIGHT = 768;
    
    ofVideoGrabber 		vidGrabber;
    ofxCvColorImage colorImg; //オリジナルのカラー映像
    ofxCvGrayscaleImage grayImage; //グレースケールに変換後
    ofxCvGrayscaleImage grayBg; //キャプチャーした背景画像
    ofxCvGrayscaleImage grayDiff; //現在の画像と背景との差分
    ofxCvContourFinder contourFinder; //輪郭抽出のためのクラス
    
    int eraseNoise = 3; //ノイズ除去回数
    
    bool bLearnBakground; //背景画像を登録
    bool showCvAnalysis; //解析結果を表示するか
    int threshold; //2値化の際の敷居値
    
    //gui
    ofxIntSlider Threshold;
    ofxPanel gui;
    
    
    //コンストラクタ
    IR_Viewer(){
        //デフォルトコンストラクタ　何もしない
    }
    IR_Viewer(int width, int height){
        //キャプチャ画像の解像度を初期化。多分画面サイズに合わせる必要はない
        WIDTH = width;
        HEIGHT= height;
    };
    
    //デストラクタ
    ~IR_Viewer(){
        gui.saveToFile("IR_ViewerSettings.xml");
    };
    
    enum IR_MODE{
        BACK,   //背景差分
        MOVE    //１フレーム前との差分
    };
    
    bool IR_debug = false;
    
    IR_MODE iR_Mode = MOVE;
    IR_MODE iR_Mode_tmp;        //DEBUGモードから戻る場合の元のモードを記録
    
    //キャプチャモード
    enum IR_CAP_MODE{
        NONE,       //結果を記録した画像のみ
        CONTOUR     //輪郭検出
    };
    IR_CAP_MODE iR_Cap_Mode = NONE;

};
