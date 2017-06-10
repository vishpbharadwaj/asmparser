/*
 * main.h
 *
 *  Created on: 24-May-2017
 *      Author: vishnu
 */

#ifndef INCLUDES_MAIN_H_
#define INCLUDES_MAIN_H_

#include "commons.h"


#define GEN_CHECK(x) \
    do { \
        if (!(x)) { \
            fprintf(stderr, "%s:%d: ", __func__, __LINE__); \
            perror(#x); \
            exit(-1); \
        } \
    } while (0) \

unsigned char proc_init();

unsigned char mnemonic_parser();

#endif /* INCLUDES_MAIN_H_ */
