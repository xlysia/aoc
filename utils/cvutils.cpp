#include "cvutils.h"

cv::Mat img;
cv::Mat background;
cv::Mat resized;
bool bGotBackground = false;
int keyboard;
void drawCircle( double x, double y,double r, cv::Scalar c, std::string msg){
    circle(img, cv::Point(x,y),r, c,cv::FILLED, 8,0);
    putText(img, msg, cv::Point(x - .75*r, y + r/2),
     cv::FONT_HERSHEY_SIMPLEX, 1 , cv::Scalar() ,1, cv::LINE_AA);
}

void drawText(double x,double y , cv::Scalar c , std::string msg,int s){
    putText(resized, msg, cv::Point(x, y),
     cv::FONT_HERSHEY_SIMPLEX, s , c ,1, cv::LINE_AA);
}

void setPixel(int x,int y,cv::Vec3b c){
    
    img.at<cv::Vec3b>(cv::Point(x,y)) = c;
}
void setBackgroundPixel(int x,int y,cv::Vec3b c){
    background.at<cv::Vec3b>(cv::Point(x,y)) = c;
}

cv::Vec3b getPixel(int x,int y){
    return img.at<cv::Vec3b>(cv::Point(x,y));
}

void show(std::string title,int i){
    cv::imshow(title, img);
    cv::waitKey(i);
}

void resize(int x){
    cv::resize(img, resized, cv::Size(), x, x,cv::INTER_AREA);
}
void  showResize(std::string title,int i){
    cv::imshow(title, resized);
    keyboard = cv::waitKey(i);
}


void newFrame(cv::Size s,cv::Scalar c){
    if(!bGotBackground)img = cv::Mat(s, CV_8UC3, c);
    else background.copyTo(img);
}
void newBackgroundFrame(cv::Size s,cv::Scalar c){
    newFrame(s,c);
    background = cv::Mat(s, CV_8UC3, c);
    bGotBackground = true;
}

void newFrameBW(cv::Size s){
    img = cv::Mat(s, CV_8UC1, cv::Scalar(0));
}

void drawLine( std::vector<cv::Point> pts , cv::Scalar c, int thickness, std::string msg){
    
    for(int i = 0; i < (int)pts.size()-1 ; i++){
        line(img, pts[i], pts[i+1], c,thickness , cv::LineTypes::LINE_8);
        putText(img, msg, (pts[i]+pts[i+1])/2,
        cv::FONT_HERSHEY_SIMPLEX, 1 , c,1, cv::LINE_AA);
    }

}

void saveFrame(std::string title){
    cv::imwrite(title+".png",img);
}

void showROI(cv::Rect r,std::string title , int i){
    cv::Mat roi = img(r);
    // resize to fit h = 1000
    int h = 1000;
    int w = h*r.width/r.height;
    cv::resize(roi, roi, cv::Size(w,h), 0, 0, cv::INTER_AREA);
    cv::imshow(title, roi);
    cv::waitKey(i);
}
cv::Rect memoROi = cv::Rect(0,0,0,0);
void showROI(int x,int y,int w,std::string title , int i){

    
    if(memoROi.width == 0){
        x = std::min(std::max(0,x-w/2),img.cols-w);
        y = std::min(std::max(0,y-w/2),img.rows-w);
        memoROi = cv::Rect(x,y,w,w);
    }

    if( x < std::max(0,memoROi.x - w/2) || x > memoROi.x + w/2 || y < std::max(0,memoROi.y-w/2) || y > memoROi.y+w/2){
        x = std::min(std::max(0,x-w/2),img.cols-w);
        y = std::min(std::max(0,y-w/2),img.rows-w);
        memoROi = cv::Rect(x,y,w,w);
    }

    cv::Rect r = memoROi;


    cv::Mat roi = img(r);
    // resize to fit h = 1000
    int h = 1000;
    w = h*r.width/r.height;
    cv::resize(roi, roi, cv::Size(w,h), 0, 0, cv::INTER_AREA);
    cv::imshow(title, roi);
    cv::waitKey(i);
}