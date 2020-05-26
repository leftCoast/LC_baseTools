#include "colorObj.h"

// Having the basics handy is very handy!
colorObj red(LC_RED);
colorObj blue(LC_BLUE);
colorObj white(LC_WHITE);
colorObj black(LC_BLACK);
colorObj green(LC_GREEN);
colorObj cyan(LC_CYAN);
colorObj magenta(LC_MAGENTA);
colorObj yellow(LC_YELLOW);


// colormapper extremes..
#define START_COLOR     0
#define END_COLOR       100

colorMapper mixMapper;

// ****** colorObj ******

colorObj::colorObj(RGBpack* buff) {
 
	red	= buff->r;
	green	= buff->g;
	blue	= buff->b;
}



colorObj::colorObj(byte inRed, byte inGreen, byte inBlue) { setColor(inRed,inGreen,inBlue); }


//colorObj::colorObj(colorObj* inColor) { setColor(inColor); }


colorObj::colorObj(word inColor16) { setColor(inColor16); }


colorObj::colorObj(void) { setColor(0,0,0); }


colorObj::~colorObj(void) {  }


void colorObj::setColor(byte inRed, byte inGreen, byte inBlue) {

  red = inRed;
  green = inGreen;
  blue = inBlue;
}


// Handed a packed 16 bit color we want to create one of our 24 bit colors.
// If it falls on one of our known colors, possibly it started out as one of ours?
// The switch statement will quickly bring it back to our original.
// Otherwise, we do the best we can with whatever bits we have to play with.
void colorObj::setColor(word color16) {

  switch(color16) {

/*****************************************************************************************/
/************** This case block is auto generated by colorListGenerator.ino **************/
/*****************************************************************************************/

	case 0x0 : // BLACK
		red = 0;
		green = 0;
		blue = 0;
	break;
	case 0x3186 : // LC_CHARCOAL
		red = 50;
		green = 50;
		blue = 50;
	break;
	case 0x8C71 : // DARK_GREY
		red = 140;
		green = 140;
		blue = 140;
	break;
	case 0xBDD7 : // LC_GREY
		red = 185;
		green = 185;
		blue = 185;
	break;
	case 0xFFDF : // LIGHT_GREY
		red = 250;
		green = 250;
		blue = 250;
	break;
	case 0xFFFF : // WHITE
		red = 255;
		green = 255;
		blue = 255;
	break;
	case 0xF800 : // RED
		red = 255;
		green = 0;
		blue = 0;
	break;
	case 0xFC1A : // PINK
		red = 255;
		green = 130;
		blue = 208;
	break;
	case 0x7E0 : // GREEN
		red = 0;
		green = 255;
		blue = 0;
	break;
	case 0xE0 : // DARK_GREEN
		red = 0;
		green = 30;
		blue = 0;
	break;
	case 0x18E0 : // OLIVE
		red = 30;
		green = 30;
		blue = 1;
	break;
	case 0x1F : // BLUE
		red = 0;
		green = 0;
		blue = 255;
	break;
	case 0xA67F : // LIGHT_BLUE
		red = 164;
		green = 205;
		blue = 255;
	break;
	case 0x3 : // NAVY
		red = 0;
		green = 0;
		blue = 30;
	break;
	case 0x881F : // PURPLE
		red = 140;
		green = 0;
		blue = 255;
	break;
	case 0xDCBF : // LAVENDER
		red = 218;
		green = 151;
		blue = 255;
	break;
	case 0xFC00 : // ORANGE
		red = 255;
		green = 128;
		blue = 0;
	break;
	case 0x7FF : // CYAN
		red = 0;
		green = 255;
		blue = 255;
	break;
	case 0xF81F : // MAGENTA
		red = 255;
		green = 0;
		blue = 255;
	break;
	case 0xFFE0 : // YELLOW
		red = 255;
		green = 255;
		blue = 0;
	break;

/*****************************************************************************************/
/*****************************************************************************************/
/*****************************************************************************************/

  default :
    red = highByte(color16);
    red = red & 0b11111000;
    green = lowByte(color16>>5);
    green = green << 2;
    blue = lowByte(color16);
    blue = blue << 3;
  }
}


void colorObj::setColor(RGBpack* buff) {

	red = buff->r;
	green = buff->g;
	blue = buff->b;
}

	
void colorObj::setColor(colorObj* inColor) {
    
    red =inColor->getRed();
    green =inColor->getGreen();
    blue = inColor->getBlue();
}


// Copied from Adafruit'
word colorObj::getColor16(void) { 
  return ((red & 0xF8) << 8) | ((green & 0xFC) << 3) | (blue >> 3);
}


byte colorObj::getRed(void) { return red; }


byte colorObj::getGreen(void) { return green; }


byte colorObj::getBlue(void) { return blue; }


// Pack up our color info.
RGBpack  colorObj::packColor(void) {

	RGBpack	temp;
	
	temp.r = red;
	temp.g = green;
	temp.b = blue;
	return temp;
}


//Creates a new color by mixing yourself with some new color.
colorObj colorObj::mixColors(colorObj* mixinColor,byte mixPercent) {
    
    if (mixPercent>=100) return *mixinColor;
    else if (mixPercent<=0) return *this;
    else {
        mixMapper.setColors(this,mixinColor);
        return mixMapper.Map(mixPercent);
    }
}


//Changes yourself by blending in some new color.
void colorObj::blend(colorObj* mixinColor,byte mixPercent) {
    
    if (mixPercent>=100) {          // If >= 100 means totally mixin color.
        setColor(mixinColor);
    } else if (mixPercent>0) {      // So its NOT >= 100 but it is > 0.. Blend it.
        mixMapper.setColors(this,mixinColor);
        colorObj temp = mixMapper.Map(mixPercent);
        setColor(&temp);
    }                               // Otherwise, there is no change.
}



#ifdef PRINT_COLOR	
 void colorObj::printRGB(void) {

  Serial.print( "ColorObj RGB : ");
  Serial.print(red);
  Serial.print(", ");
  Serial.print(green);
  Serial.print(", ");
  Serial.println(blue);
  Serial.flush();
}
#endif


// ****** colorMapper ******

                       
colorMapper::colorMapper(void) {
    
    redMapper = new mapper(START_COLOR,END_COLOR,0,0);
    greenMapper = new mapper(START_COLOR,END_COLOR,0,0);
    blueMapper = new mapper(START_COLOR,END_COLOR,0,0);
}
     
                       
colorMapper::colorMapper(colorObj* inStart, colorObj* inEnd) {

  redMapper = new mapper(START_COLOR,END_COLOR,inStart->getRed(),inEnd->getRed());
  greenMapper = new mapper(START_COLOR,END_COLOR,inStart->getGreen(),inEnd->getGreen());
  blueMapper = new mapper(START_COLOR,END_COLOR,inStart->getBlue(),inEnd->getBlue());
}


colorMapper::colorMapper(word startC16,word endC16) {

  colorObj startColor(startC16);
  colorObj endColor(endC16);

  redMapper = new mapper(START_COLOR,END_COLOR,startColor.getRed(),endColor.getRed());
  greenMapper = new mapper(START_COLOR,END_COLOR,startColor.getGreen(),endColor.getGreen());
  blueMapper = new mapper(START_COLOR,END_COLOR,startColor.getBlue(),endColor.getBlue());
}


colorMapper::~colorMapper(void) {
   
   delete(redMapper);
   delete(greenMapper);
   delete(blueMapper);
}


void colorMapper::setColors(colorObj* inStart, colorObj* inEnd) {
    
    redMapper->setValues(START_COLOR,END_COLOR,inStart->getRed(),inEnd->getRed());
    greenMapper->setValues(START_COLOR,END_COLOR,inStart->getGreen(),inEnd->getGreen());
    blueMapper->setValues(START_COLOR,END_COLOR,inStart->getBlue(),inEnd->getBlue());
}
                                                   
                                                   
colorObj colorMapper::Map(float percent) {

   colorObj theColor(
  (byte)round(redMapper->Map(percent)),
  (byte)round(greenMapper->Map(percent)),
  (byte)round(blueMapper->Map(percent))
    );
  return theColor;
}
  

#ifdef PRINT_COLOR
void colorMapper::printColors(void) {

  colorObj startColor(
  (byte)round(redMapper->Map(START_COLOR)),
  (byte)round(greenMapper->Map(START_COLOR)),
  (byte)round(blueMapper->Map(START_COLOR))
    );
  colorObj endColor(
  (byte)round(redMapper->Map(END_COLOR)),
  (byte)round(greenMapper->Map(END_COLOR)),
  (byte)round(blueMapper->Map(END_COLOR))
    );
  Serial.println("Mapper start / end");
  startColor.printRGB();
  endColor.printRGB();
}
#endif

// ****** colorMultiMap ******



colorMultiMap::colorMultiMap(void) {  }


colorMultiMap::~colorMultiMap(void) {  }

void colorMultiMap::addColor(double inX, colorObj* color) {
    
    if (color) {
        redMap.addPoint(inX,color->getRed());
        greenMap.addPoint(inX,color->getGreen());
        blueMap.addPoint(inX,color->getBlue());
    }
}


void colorMultiMap::clearMap(void) {
    
    redMap.clearMap();
    greenMap.clearMap();
    blueMap.clearMap();
}


colorObj colorMultiMap::Map(double inVal) {
    
    colorObj  result;
    byte      red;
    byte      green;
    byte      blue;
    
    red = round(redMap.Map(inVal));
    green = round(greenMap.Map(inVal));
    blue = round(blueMap.Map(inVal));
    result.setColor(red,green,blue);
    return result;
}

