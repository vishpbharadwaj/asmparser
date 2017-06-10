/*
 * commons.h
 *
 *  Created on: 24 May 2017
 *      Author: vishnu
 */

#ifndef INCLUDE_FILES_COMMONS_H_
#define INCLUDE_FILES_COMMONS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <mqueue.h>
#include <pthread.h>

#define debug_print(format, ...)\
			printf("%s:%d : " format, __FILE__, __LINE__, __VA_ARGS__)

#define error_print(format, ...)\
			printf(" < error > %s:%d : " format, __FILE__, __LINE__, __VA_ARGS__)

#define TRUE 1
#define FALSE 0

#endif /* INCLUDE_FILES_COMMONS_H_ */
