//
//  OpenCVWrapper.m
//  ARVision
//
//  Created by Ian Applebaum on 9/8/18.
//  Copyright © 2018 PennAppsXVIII. All rights reserved.
//

#import "OpenCVWrapper.h"
#import <opencv2/opencv.hpp>
#import <opencv2/imgcodecs/ios.h>
@implementation OpenCVWrapper
+(NSString *) openCVVersionString
{
    return [NSString stringWithFormat:@"OpenCV Version %s", CV_VERSION];
}
+(UIImage *) makeCVfromImage:(UIImage *)image{
   
   
        //    Transform image
        cv::Mat imageMat;
        UIImageToMat(image, imageMat);
        return image;
   

}
@end
