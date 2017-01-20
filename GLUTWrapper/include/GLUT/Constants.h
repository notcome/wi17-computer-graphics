/* -------------------------------------------------------------------------- *
 * GLUT Wrapper :: Constants.h
 *
 * This file declares several common constants for GL operations.
 *
 * Author: Minsheng Liu.
 */


#ifndef Constants_h
#define Constants_h

#include "Common.h"

namespace GLUT {
    struct Color {
        static const GLfloat white[];
        static const GLfloat red[];
        static const GLfloat green[];
        static const GLfloat blue[];
        static const GLfloat yellow[];
        static const GLfloat lightGray[];
        static const GLfloat darkGray[];
    };
}

#endif
