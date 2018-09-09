//
//  OpenCVWrapper.h
//  ARVision
//
//  Created by Ian Applebaum on 9/8/18.
//  Copyright © 2018 PennAppsXVIII. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
NS_ASSUME_NONNULL_BEGIN

@interface OpenCVWrapper : NSObject

//define here interface with openCV

//func to get openCV
+(NSString *) openCVVersionString;
+(UIImage *)makeCVfromImage:(UIImage *) image;
@end

NS_ASSUME_NONNULL_END
