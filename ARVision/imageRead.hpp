//
//  imageRead.hpp
//  ARVision
//
//  Created by Tommy Tan on 9/9/18.
//  Copyright © 2018 PennAppsXVIII. All rights reserved.
//

#ifndef imageRead_hpp
#define imageRead_hpp

//#include <fstream>
//#include <sstream>
//#include <iostream>
//#include <algorithm>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

const char* keys =
"{help h usage ? | | Usage examples: \n\t\t./object_detection_yolo.out --image=dog.jpg \n\t\t./object_detection_yolo.out --video=run_sm.mp4}"
"{image i        |<none>| input image   }"
"{video v       |<none>| input video   }"
;


using namespace cv;
using namespace dnn;
using namespace std;

// Initialize the parameters
float confThreshold = 0.5; // Confidence threshold
float nmsThreshold = 0.4;  // Non-maximum suppression threshold
int inpWidth = 416;  // Width of network's input image
int inpHeight = 416; // Height of network's input image
float KNOWN_DISTANCE = 24.0;
float KNOWN_WIDTH = 11.0;
vector<string> classes;

class imageRead {
    
public:
    imageRead(Mat readFrame){
        frame = readFrame;
    }
    float distance_to_camera(float bruh, float focalLength, int n);
    void drawPred(int classId, float conf, int left, int top, int right, int bottom, Mat& frame);
    
    RotatedRect find_marker(Mat image, Mat & outputImage);
    void postprocess(Mat& frame, const vector<Mat>& outs);
    vector<String> getOutputsNames(const Net& net);
    
    float outputFrame();
private:
    Mat frame;
    float inches;
    
};

#endif /* imageRead_hpp */
