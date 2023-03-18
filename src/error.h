#ifndef __ERROR_H__
#define __ERROR_H__

// Error 
enum error {
    OK                         = 0, // Everything is ok
    ERR_NOT_FOUND              = 1, // Resource not found
    ERR_WITH_VALUE             = 2, // Incorrect value
    ERR_RDV_OVERLAP            = 3, // Incorrect value
};


#endif