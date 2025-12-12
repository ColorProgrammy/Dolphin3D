/*
File: gradients.h
Developer: ColorProgrammy

Description:
Stores gradient patterns inside, which are applied as pixels
*/

/*
---
You can create your own gradients. 
And remember that gradients are made by the intensity of the characters from smaller to larger.
---
*/

#ifndef GRADIENTS_H
#define GRADIENTS_H

#include <cstddef>

#define GRADIENT_0 " .,:!/rH#$@"

#define GRADIENT_1 " .:-=+*#%@"
#define GRADIENT_2 " .:-!/?7ilI#%@"
#define GRADIENT_3 " .:;i1tfLCG08@"
// you can add more at your discretion

inline void setGradientSize(char gradient[], size_t& gradientSize, int maxGradientSize, const char* gradientName) {
	strncpy(gradient, gradientName, maxGradientSize);
    gradient[maxGradientSize - 1] = '\0';
	gradientSize = strlen(gradient) - 1;
}

#endif // GRADIENTS_H