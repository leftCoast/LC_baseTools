#ifndef colorObj_h
#define colorObj_h

#include <mapper.h>
#include <multiMap.h>
// uncomment for debug stuff.
//#define PRINT_COLOR

//                       Red,Grn,blu
#define LC_BLACK          0,  0,  0
#define LC_CHARCOAL      50, 50, 50
#define LC_DARK_GREY    140,140,140
#define LC_GREY         185,185,185
#define LC_LIGHT_GREY   250,250,250
#define LC_WHITE        255,255,255

#define LC_RED          255,  0,  0
#define LC_PINK         255,130,208

#define LC_GREEN          0,255,  0
#define LC_DARK_GREEN     0, 30,  0
#define LC_OLIVE         30, 30,  1

#define LC_BLUE           0,  0,255
#define LC_LIGHT_BLUE   164,205,255
#define LC_NAVY           0,  0, 30

#define LC_PURPLE       140,  0,255
#define LC_LAVENDER     218,151,255
#define LC_ORANGE       255,128,  0

#define LC_CYAN           0,255,255
#define LC_MAGENTA      255,  0,255
#define LC_YELLOW       255,255,  0

/*
  Need to store lots of colors efficiently, like in a bitmap image? 

  The `RGBpack` structure offers a compact alternative to `colorObj` 
  for storing color information. While a `colorObj` uses 8 bytes per color, 
  `RGBpack` achieves the same using just 3 bytes per pixel. This makes 
  `RGBpack` ideal for situations where storage space and processing speed 
  are critical.
*/

struct RGBpack {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};


class colorObj {

public:
                colorObj(RGBpack* buff);
                colorObj(byte inRed, byte inGreen, byte inBlue);
                //colorObj(colorObj* inColor);             // Wanted this one, but the compiler mixes it up with color16.
                colorObj(word color16);
                colorObj(void);
  virtual   ~colorObj(void);

  virtual   void        setColor(RGBpack* buff);
  virtual   void        setColor(byte inRed, byte inGreen, byte inBlue);
  virtual   void        setColor(word color16);
  virtual   void        setColor(colorObj* inColor);       // Why doesn't this one get confused? Who knows?
                word        getColor16(void);
                byte        getGrayscale(void);

                byte        getRed(void);
                byte        getGreen(void);
                byte        getBlue(void);
                RGBpack packColor(void);

                colorObj    mixColors(colorObj* mixinColor,byte mixPercent);  // Create a new color by mixing. (Like the old blend)
                void        blend(colorObj* mixinColor,byte mixPercent);      // Just blend with myself. Percent 0% -> 100% of new color.

#ifdef PRINT_COLOR
                void        printRGB(void);
#endif

protected :
  byte red;
  byte green;
  byte blue;
};

extern colorObj red;
extern colorObj blue;
extern colorObj white;
extern colorObj black;
extern colorObj green;
extern colorObj cyan;
extern colorObj magenta;
extern colorObj yellow;


// ****** colorMapper ******

class colorMapper {

    public:
                colorMapper(void);
                colorMapper(colorObj* inStart, colorObj* inEnd);
                colorMapper(word startC16,word endC16);
    virtual ~colorMapper(void);

                void        setColors(colorObj* inStart, colorObj* inEnd);
                colorObj Map(float percent);
                colorObj map(float percent);

#ifdef PRINT_COLOR
                void     printColors(void);
#endif

    private :
                mapper* redMapper;
                mapper* greenMapper;
                mapper* blueMapper;
};


// ****** colorMultiMap ******


class colorMultiMap {

    public:
                colorMultiMap(void);
    virtual ~colorMultiMap(void);

                void    addColor(double inX, colorObj* color);  // At some numeric value we resolve to this color.
                void    clearMap(void);
                colorObj    map(double inVal);

    protected:
                multiMap  redMap;
                multiMap  greenMap;
                multiMap  blueMap;
};


#endif
