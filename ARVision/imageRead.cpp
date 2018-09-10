//
//  imageRead.cpp
//  ARVision
//
//  Created by Tommy Tan on 9/9/18.
//  Copyright © 2018 PennAppsXVIII. All rights reserved.
//

#include "imageRead.hpp"

// Usage example:  ./object_detection_yolo.out --video=run.mp4
//                 ./object_detection_yolo.out --image=bird.jpg


float imageRead::outputFrame() {
    
    // Remove the bounding boxes with low confidence using non-maxima suppression
    void postprocess(Mat& frame, const vector<Mat>& out);
    
    // Draw the predicted bounding box
    void drawPred(int classId, float conf, int left, int top, int right, int bottom, Mat& frame);
    
    // Get the names of the output layers
    vector<String> getOutputsNames(const Net& net);
    
    // Give the configuration and weight files for the model
    String modelConfiguration = "yolov3.cfg";
    String modelWeights = "yolov3.weights";
    
    // Load the network
    Net net = readNetFromDarknet(modelConfiguration, modelWeights);
    net.setPreferableBackend(DNN_BACKEND_OPENCV);
    net.setPreferableTarget(DNN_TARGET_CPU);
    
    // Open a video file or an image file or a camera stream.
    string str, outputFile;
    VideoCapture cap;
    VideoWriter video;
    Mat frame, blob;
    
    outputFile = "yolo_out_cpp.avi";
    
    // Create a window
    static const string kWinName = "Deep learning object detection in OpenCV";
    namedWindow(kWinName, WINDOW_NORMAL);
    // Process frames.
    
    // get frame from the video
    
    // Stop the program if reached end of video
    
    // Create a 4D blob from a frame.
    blobFromImage(frame, blob, 100/255.0, cvSize(inpWidth, inpHeight), Scalar(0,0,0), true, false);
    
    //Sets the input to the network
    net.setInput(blob);
    
    // Runs the forward pass to get output of the output layers
    vector<Mat> outs;
    net.forward(outs, getOutputsNames(net));
    
    // Remove the bounding boxes with low confidence
    postprocess(frame, outs);
    
    // Put efficiency information. The function getPerfProfile returns the overall time for inference(t) and the timings for each of the layers(in layersTimes)
    vector<double> layersTimes;
    
    // Write the frame with the detection boxes
    Mat detectedFrame;
    frame.convertTo(detectedFrame, CV_8U);
    float focalLength = (300 * KNOWN_DISTANCE)/KNOWN_WIDTH;
    inches = distance_to_camera(KNOWN_WIDTH, focalLength, 300 );
    cap.release();
    
    return inches;
}






// Remove the bounding boxes with low confidence using non-maxima suppression
void imageRead::postprocess(Mat& frame, const vector<Mat>& outs)
{
    vector<int> classIds;
    vector<float> confidences;
    vector<Rect> boxes;
    
    for (size_t i = 0; i < outs.size(); ++i)
    {
        // Scan through all the bounding boxes output from the network and keep only the
        // ones with high confidence scores. Assign the box's class label as the class
        // with the highest score for the box.
        float* data = (float*)outs[i].data;
        for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols)
        {
            Mat scores = outs[i].row(j).colRange(5, outs[i].cols);
            Point classIdPoint;
            double confidence;
            // Get the value and location of the maximum score
            minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
            if (confidence > confThreshold)
            {
                int centerX = (int)(data[0] * frame.cols);
                int centerY = (int)(data[1] * frame.rows);
                int width = (int)(data[2] * frame.cols);
                int height = (int)(data[3] * frame.rows);
                int left = centerX - width / 2;
                int top = centerY - height / 2;
                
                classIds.push_back(classIdPoint.x);
                confidences.push_back((float)confidence);
                boxes.push_back(Rect(left, top, width, height));
            }
        }
    }
    
    // Perform non maximum suppression to eliminate redundant overlapping boxes with
    // lower confidences
    vector<int> indices;
    NMSBoxes(boxes, confidences, confThreshold, nmsThreshold, indices);
    for (size_t i = 0; i < indices.size(); ++i)
    {
        int idx = indices[i];
        Rect box = boxes[idx];
        drawPred(classIds[idx], confidences[idx], box.x, box.y,
                 box.x + box.width, box.y + box.height, frame);
    }
}

/*RotatedRect imageRead::find_marker(Mat image, Mat & outputImage){
    
    vector<vector<Point > > contours;
    cvtColor(image, outputImage, CV_BGR2GRAY );
    GaussianBlur(image, outputImage, Size(5, 5), 0, 0);
    Canny(image, outputImage, 35, 125);
    
    findContours(outputImage, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
    //std::max_element(contours.begin(), contours.end(), comp);
    
}*/

// Draw the predicted bounding box
void imageRead::drawPred(int classId, float conf, int left, int top, int right, int bottom, Mat& frame)
{
    //Draw a rectangle displaying the bounding box
    rectangle(frame, Point(left, top), Point(right, bottom), Scalar(255, 178, 50), 3);
    
    //Get the label for the class name and its confidence
    string label = format("%.2f", conf);
    if (!classes.empty())
    {
        CV_Assert(classId < (int)classes.size());
        label = classes[classId] + ":" + label;
    }
    
    //Display the label at the top of the bounding box
    int baseLine;
    Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
    top = max(top, labelSize.height);
    rectangle(frame, Point(left, top - round(1.5*labelSize.height)), Point(left + round(1.5*labelSize.width), top + baseLine), Scalar(255, 255, 255), FILLED);
    putText(frame, label, Point(left, top), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0,0,0),1);
}

// Get the names of the output layers
vector<String> imageRead::getOutputsNames(const Net& net)
{
    static vector<String> names;
    if (names.empty())
    {
        //Get the indices of the output layers, i.e. the layers with unconnected outputs
        vector<int> outLayers = net.getUnconnectedOutLayers();
        
        //get the names of all the layers in the network
        vector<String> layersNames = net.getLayerNames();
        
        // Get the names of the output layers in names
        names.resize(outLayers.size());
        for (size_t i = 0; i < outLayers.size(); ++i)
            names[i] = layersNames[outLayers[i] - 1];
    }
    return names;
}

float imageRead::distance_to_camera(float bruh, float focalLength, int n)
{
    
    return (bruh * focalLength) / n;
}
