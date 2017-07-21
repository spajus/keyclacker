#include "keyclacker.h"

int main(int argc, const char *argv[]) {

  if (argc == 2) {
    volume = (int) strtol(argv[1], (char **) NULL,  10);
  }

  // Test if sounds are available locally (which means daemon is not installed)
  if (access("./sounds/key_0_down.wav", F_OK) != -1) {
    strcpy(sounds_path, "./sounds");
  } else {
    strcpy(sounds_path, "/usr/local/keyclacker");
  }

  // Create an event tap to retrieve keypresses.
  CGEventMask eventMask = (CGEventMaskBit(kCGEventKeyUp) |
      CGEventMaskBit(kCGEventKeyDown) | CGEventMaskBit(kCGEventFlagsChanged));

  CFMachPortRef eventTap = CGEventTapCreate(kCGSessionEventTap,
      kCGHeadInsertEventTap, 0, eventMask, CGEventCallback, NULL);

  // Exit the program if unable to create the event tap.
  if(!eventTap) {
    fprintf(stderr, "ERROR: Unable to create event tap.\n");
    exit(1);
  }

  // Create a run loop source and add enable the event tap.
  CFRunLoopSourceRef runLoopSource = CFMachPortCreateRunLoopSource(
      kCFAllocatorDefault, eventTap, 0);

  CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource,
      kCFRunLoopCommonModes);

  CGEventTapEnable(eventTap, true);

  CFRunLoopRun();

  return 0;
}

// The following callback method is invoked on every keypress.
CGEventRef CGEventCallback(CGEventTapProxy proxy, CGEventType type,
    CGEventRef event, void *refcon) {

  char command[1024];
  char *direction = NULL;
  char sound[24];

  if (type != kCGEventKeyDown && type != kCGEventFlagsChanged &&
      type != kCGEventKeyUp) {
    return event;
  }

  // Retrieve the incoming keycode.
  CGKeyCode keyCode = (CGKeyCode) CGEventGetIntegerValueField(event,
      kCGKeyboardEventKeycode);

  switch (keyCode) {
    case 36:
      strcpy(sound, "enter");
      break;
    case 49:
      strcpy(sound, "space");
      break;
    default:
      snprintf(sound, sizeof(sound), "%i", rand_interval(0, NUM_SOUNDS));
  }

  // Handle modifier key presses
  if (type == kCGEventFlagsChanged) {
    strcpy(sound, "shift");

    CGEventFlags flags = CGEventGetFlags(event);

    // Not ideal, but simple solution, if any of flags is on, then we assume
    // that it's pressed, if not, we assume it's being released. Works with 1
    // modifier key at a time.
    // TODO: remember modifiers and play sounds according to actual situation
    if (flags & kCGEventFlagMaskShift ||
        flags & kCGEventFlagMaskControl ||
        flags & kCGEventFlagMaskAlternate ||
        flags & kCGEventFlagMaskSecondaryFn ||
        flags & kCGEventFlagMaskNumericPad ||
        flags & kCGEventFlagMaskCommand) {
      direction = "down";
    } else {
      direction = "up";
    }
  }

  // Regular key presses

  if (type == kCGEventKeyDown) {
    direction = "down";
  }

  if (type == kCGEventKeyUp) {
    direction = "up";
  }

  if (direction) {
    // And here's the point where everyone gets disappointed
    // TODO: proper reimplementation without shelling out
    snprintf(command, sizeof(command), "afplay -v %i %s/key_%s_%s.wav &",
        volume, sounds_path, sound, direction);
    system(command);
  }

  return event;
}

unsigned int rand_interval(unsigned int min, unsigned int max) {
  int r;
  const unsigned int range = 1 + max - min;
  const unsigned int buckets = RAND_MAX / range;
  const unsigned int limit = buckets * range;

  do {
    r = rand();
  } while (r >= limit);

  return min + (r / buckets);
}
