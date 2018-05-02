/*
 *2016/03/09 IR_viewer
 *赤外線カメラを使って背景差分で動体を検知する。
 *ISOの自動調整で検知しちゃうノイズが一定以上出るとリセットする。
 *背景差分か
 *前フレームとの差分で検知するモードを選ぶ
 *
 *
 */


#include "IR_Viewer.h"

//--------------------------------------------------------------
void IR_Viewer::setup(){
    gui.setup(); // most of the time you don't need a name
    gui.add(Threshold.setup("threshold", 123, 0, 255));
    gui.loadFromFile("IR_ViewerSettings.xml");                //閾値保存
    
    //画面の基本設定
    ofBackground(0, 0, 0);
    ofEnableAlphaBlending();
    
    //カメラから映像を取り込んで表示
    vidGrabber.setVerbose(true);
    vidGrabber.setDeviceID(1);          //カメラID指定 mac mini だと０番かも
    vidGrabber.initGrabber(WIDTH,HEIGHT);
    
    //使用する画像の領域を確保
    colorImg.allocate(WIDTH,HEIGHT);
    grayImage.allocate(WIDTH,HEIGHT);
    grayBg.allocate(WIDTH,HEIGHT);
    grayDiff.allocate(WIDTH,HEIGHT);
    
    //変数の初期化
    bLearnBakground = true;
    showCvAnalysis = false;
    threshold = 200;    //初期化、でもすぐguiので上書き 意味なし
    
}

//--------------------------------------------------------------
void IR_Viewer::update(){
    threshold = Threshold;                         //guiの値を代入。直接使えない
    

    bool bNewFrame = false;                      //新規フレームの取り込みをリセット
    vidGrabber.update();                        //カメラ使用の場合はカメラから新規フレーム取り込み
    bNewFrame = vidGrabber.isFrameNew();        //新規にフレームが切り替わったか判定
    //フレームが切り替わった際のみ画像を解析
    if (bNewFrame){
        //取り込んだフレームを画像としてキャプチャ
        colorImg.setFromPixels(vidGrabber.getPixels(), WIDTH,HEIGHT);
        colorImg.mirror(false, true);       //左右反転
        grayImage = colorImg;               //カラーのイメージをグレースケールに変換
        
        grayImage.absDiff(grayBg, grayImage);//背景または１フレーム前の画像と差分
        grayDiff = grayImage;               //コピー
        grayDiff.threshold(threshold);      //画像を2値化(白と黒だけに)する
        //収縮、膨張でノイズ除去
        for(int i=0; i<eraseNoise;i++){
            grayDiff.erode();
        }
        for(int i=0; i<eraseNoise;i++){
            grayDiff.dilate();
        }
        
        //2値化した画像から輪郭を抽出する
        if(iR_Cap_Mode == CONTOUR){
            contourFinder.findContours(grayDiff, 5, grayDiff.width * grayDiff.height, 10, false, true);
        }

        //現在のフレームを背景として保存
        if(iR_Mode == BACK && bLearnBakground){
            grayBg = colorImg;
            bLearnBakground = false;
        }
        //フレームを保存（１フレーム前となる
        if(iR_Mode == MOVE)grayBg = colorImg;
    }
    
}

//--------------------------------------------------------------
void IR_Viewer::draw(){
    if(IR_debug){
        grayDiff.draw(0, 0, ofGetWidth(), ofGetHeight());            //差分後に2値化された映像
        //差分後画像
        grayImage.draw(ofGetWidth()  -ofGetWidth() *3/5,
                    ofGetHeight() -ofGetHeight()*1/5,
                    ofGetWidth()/5, ofGetHeight()/5);
        //背景画像
        grayBg.draw(ofGetWidth()  -ofGetWidth() *2/5,
                    ofGetHeight() -ofGetHeight()*1/5,
                    ofGetWidth()/5, ofGetHeight()/5);
        // カメラ映像
        colorImg.draw(ofGetWidth()  -ofGetWidth() *1/5,
                      ofGetHeight() -ofGetHeight()*1/5,
                      ofGetWidth()/5, ofGetHeight()/5);
        gui.draw();
        //輪郭結果を表示する
        if(iR_Cap_Mode == CONTOUR){
            //検出した解析結果を表示
            for (int i = 0; i < contourFinder.nBlobs; i++){
                ofPushMatrix();
                //画面サイズいっぱいに表示されるようリスケール
                glScalef((float)ofGetWidth() / (float)grayDiff.width,
                         (float)ofGetHeight() / (float)grayDiff.height,
                         1.0f);
                contourFinder.blobs[i].draw(0,0);
                ofFill();
                ofSetColor(255, 0, 0);
                ofEllipse(contourFinder.blobs[i].centroid.x, contourFinder.blobs[i].centroid.y, 4, 4);
                ofPopMatrix();
            }
        }
    }
}

//--------------------------------------------------------------
void IR_Viewer::keyPressed(int key){
    //キー入力
    switch (key){
        case ' ':
            //背景画像を新規に取り込む
            bLearnBakground = true;
            break;
            
        case '+':
            //2値化の閾値を増加
            threshold ++;
            if (threshold > 255) threshold = 255;
            break;
            
        case '-':
            //2値化の閾値を減少
            threshold --;
            if (threshold < 0) threshold = 0;
            break;
        
        case 'd':
            //デバッグモード
            IR_debug  = !IR_debug;
            break;
            
        case 'm':
            //モードチェンジ
            if(iR_Mode == 0){iR_Mode=MOVE;}
            else if(iR_Mode == 1){iR_Mode=BACK;}
    }
    
}

//--------------------------------------------------------------
void IR_Viewer::keyReleased(int key){
    
}

//--------------------------------------------------------------
void IR_Viewer::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void IR_Viewer::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void IR_Viewer::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void IR_Viewer::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void IR_Viewer::windowResized(int w, int h){

}

//--------------------------------------------------------------
void IR_Viewer::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void IR_Viewer::dragEvent(ofDragInfo dragInfo){ 

}
