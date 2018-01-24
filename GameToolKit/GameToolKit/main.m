//
//  main.m
//  GameToolKit
//
//  Created by soulghost on 29/12/2017.
//  Copyright © 2017 soulghost. All rights reserved.
//

#import <Foundation/Foundation.h>

NSString* nameMapper(NSString *name) {
    NSInteger location = [name rangeOfString:@"_"].location;
    if (location == NSNotFound) {
        return name;
    }
    NSString *numStr = [name substringToIndex:location];
    numStr = [numStr substringFromIndex:numStr.length - 3];
    return [NSString stringWithFormat:@"fusushu%d.png", [numStr integerValue] + 1];
}

void changeNames() {
    NSString *path = @"/Users/soulghost/Downloads/紫莲花/";
    NSString *output = @"fusushu";
    NSString *outputDir = [path stringByAppendingPathComponent:output];
    NSArray *items = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:path error:nil];
    [[NSFileManager defaultManager] createDirectoryAtPath:outputDir withIntermediateDirectories:YES attributes:nil error:nil];
    for (NSString *item in items) {
        if ([item hasSuffix:@".png"]) {
            NSString *filePath = [path stringByAppendingPathComponent:item];
            NSData *file = [NSData dataWithContentsOfFile:filePath];
            NSString *name = nameMapper(item);
            NSString *outputPath = [outputDir stringByAppendingPathComponent:name];
            [file writeToFile:outputPath atomically:YES];
        }
    }
}

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        changeNames();
    }
    return 0;
}
