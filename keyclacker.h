#ifndef __KEYCLACKER_H__
#define __KEYCLACKER_H__

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>
// https://developer.apple.com/library/mac/documentation/Carbon/Reference/QuartzEventServicesRef/Reference/reference.html

const int NUM_SOUNDS = 4;
int volume = 1;
char sounds_path[256];

CGEventRef CGEventCallback(CGEventTapProxy, CGEventType, CGEventRef, void*);
unsigned int rand_interval(unsigned int min, unsigned int max);

#endif
