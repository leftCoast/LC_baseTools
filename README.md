# LC_baseTools

## Arduino Library for Simplified Programming

This library provides a collection of tools designed to simplify common Arduino programming tasks. 

**IMPORTANT INSTALLATION NOTE:** 

**Do not download these files directly from the repository.** In most cases, they will not compile correctly. Instead, install the library using the Arduino IDE Library Manager. 

**(Ignore the .ZIP files; their presence is a mystery!)**

## Available Tools:

- **autoPOT:** Automatic analog pin reader with callbacks for value changes.
- **blinker:** Blink an LED on any output pin without using `delay()`. No interrupts or hardware PWM required. [Example](examples/auto_blinkers)
- **colorObj:**  Comprehensive color management – store, translate, transfer between computer and hardware, blend, and perform linear/non-linear color mapping.
- **heapStr:**  (part of **strTools**) Heap allocation/de-allocation of string copies. 
- **idlers:**  Create background tasks using the `idler` class. The library handles automatic background execution.
- **lists:**  Foundation for dynamic linked lists used throughout the LC libraries. Includes linked lists, double-linked lists, stacks, and queues.
- **lwrCase():** (part of **strTools**) C-string utility for case conversion.
- **mapper:** Linear mapping function using doubles for input and output. Optimizes calculations between calls.
- **maxBuff:** (part of **resizeBuff**) Stack-based class for large data transfers (e.g., file copying), calculating the number of transfers required.
- **mechButton:** Create debounced buttons with three user levels: Beginner (simple polling), Intermediate (callbacks), and Pro (custom actions via subclass). [Example](examples/mechButton_Beginner)
- **multiMap:** Non-linear mapping function. Define the mapping by adding x,y points.
- **resizeBuff:** Streamlined memory management. Use `resizeBuff()` to allocate/de-allocate dynamic buffers, returning `true` for success and `false` for failure. 
- **runningAvg:** Data smoothing using a running average. Input a number, get the average of the last 'n' inputs. Includes statistical functions. [Example](examples/runningAvg)
- **serialStr:** Process complete C-strings received from the serial port. Provide a callback function to handle the received strings. [Example](examples/serialStr)
- **squareWave:**  Base class for objects based on square waves (e.g., blinking lights, flashing text, RC servo signals). No interrupts or hardware PWM used; runs in the background.
- **strTools:** C-string utilities: `upCase()`, `lwrCase()`, `heapStr()`, `freeStr()`, and `tempStr()` for case conversion, heap allocation/de-allocation of string copies, and temporary string storage (automatically recycled).
- **tempStr():** (part of **strTools**) Temporary string storage (automatically recycled).
- **textBuff:** Ring buffer for text, useful for handling bursts of text input from hardware.
- **timeObj:** Timer using milliseconds as a float input. Query the timer to check for expiration. Handles rollover. Useful for non-blocking timing.
- **upCase():** (part of **strTools**) C-string utility for case conversion.

## Contributing

If you'd like to contribute to this library, please open an issue or submit a pull request on the [GitHub repository]([link-to-your-repo-here](https://github.com/leftCoast/LC_baseTools)). 
