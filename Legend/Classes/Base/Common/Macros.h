//
//  Macros.h
//  Legend
//
//  Created by soulghost on 11/7/2017.
//
//

#ifndef Macros_h
#define Macros_h

#define CCMAX(a, b) (a) > (b) ? (a) : (b)
#define CCMIN(a, b) (a) < (b) ? (a) : (b)
#define CCMAXINT (~0U >> 1)

#define CCString(desc) #desc

#define RGBA4F(r,g,b,a) Color4F(r/255.0f, g/255.0f, b/255.0f, a)

#endif /* Macros_h */
