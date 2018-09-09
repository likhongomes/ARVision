//
//  OpenCVWrapper.m
//  ARVision
//
//  Created by Ian Applebaum on 9/8/18.
//  Copyright © 2018 PennAppsXVIII. All rights reserved.
//

#import "OpenCVWrapper.h"
#import <opencv2/opencv.hpp>
@implementation OpenCVWrapper
+(NSString *) openCVVersionString
{
    return [NSString stringWithFormat:@"OpenCV Version %s", CV_VERSION];
}

@end
