#ifndef GRADIENTS_H
#define GRADIENTS_H

#include <cstddef>

#define GRADIENT_0 " .,:!/rH$#@"

#define GRADIENT_1 " .:-=+*#%@"
#define GRADIENT_2 " .:-!/?7ilI#%@"
#define GRADIENT_3 " .:;i1tfLCG08@"
// you can add more at your discretion

inline void setGradientSize(char gradient[], size_t& gradientSize) {
	gradientSize = strlen(gradient) - 1;
}

#endif // GRADIENTS_H
