#include <Adafruit_NeoPixel.h>

// arduino pin
#define LED_PIN 6
// display dimentions in pixels: hight * width
#define HIGHT 5
#define WIDTH 8
// brightness from 0 (min) to 255 (max)
#define BRIGHTNESS 5

#define SHIFT 0

// defining LED strip, in this case NEO_GRB LEDs
Adafruit_NeoPixel strip = Adafruit_NeoPixel(HIGHT*WIDTH, LED_PIN, NEO_GRB+NEO_KHZ800);

int extended_matrix[HIGHT+10][WIDTH+6];
// int LED_matrix[HIGHT][WIDTH];
int l_A[15] = {1,1,1,1,1,0,0,1,0,1,1,1,1,1,1};
int l_a[15] = {1,1,1,0,1,1,0,1,0,1,1,1,1,1,1};
int l_B[15] = {1,1,1,1,1,1,0,1,0,1,0,1,0,1,0};
int l_b[15] = {1,1,1,1,1,1,0,1,0,0,1,1,1,0,0};
int l_C[15] = {0,1,1,1,0,1,0,0,0,1,1,0,0,0,1};
int l_c[15] = {1,1,1,0,0,1,0,1,0,0,1,0,1,0,0};
int l_D[15] = {1,1,1,1,1,1,0,0,0,1,0,1,1,1,0};
int l_d[15] = {1,1,1,0,0,1,0,1,0,0,1,1,1,1,1};
int l_O[15] = {1,1,1,1,1,1,0,0,0,1,1,1,1,1,1};
int l_N[15] = {1,1,1,1,1,0,0,0,0,1,1,1,1,1,1};

void drowing_character(int* table, int row, int column, uint32_t color){
  if(row<=-5 || row>=(HIGHT-1)+5 || column <=-3 || column >=(WIDTH-1)+3){
    return 0;
  } else {
    uint32_t display;
    for(int i=0; i<=14;i++){
      if(table[i]==1){
        display = color;
      } else {
        display = strip.Color(0,0,0);
      }
        strip.setPixelColor(extended_matrix[(i%5)+5+row][((int)i/5)+3+column], display);
    }
  }
  // strip.show();
}

void shining_column(int column,uint32_t color){
  for(int i=0; i<=4; i++){
    strip.setPixelColor(extended_matrix[i][column], color);
  }
}


void setup()
{
  // Serial.begin(9600);
	strip.begin();
  strip.show();
  strip.setBrightness(BRIGHTNESS);
  // display matrix
  for(int i=-5; i<=(HIGHT-1)+5; i++){
    for(int j=-3; j<=(WIDTH-1)+3; j++){
      if(i>=0 && i<=(HIGHT-1) && j>=0 && j<=(WIDTH-1)){
        extended_matrix[i+5][j+3]={j+(((HIGHT-1)-i)*WIDTH)};
      } else {
        extended_matrix[i+5][j+3]=-1;
      }
    }
  }
  // for(int i=0; i<=(HIGHT-1); i++){
  //   for(int j=0; j<=(WIDTH-1); j++){
  //     LED_matrix[i][j]={(((HIGHT-1)-i)*WIDTH)+j};
  //   }
  // }
}

void ss(int* table,int column){
  drowing_character(table, SHIFT, column, strip.Color(255, 0, 0));
  // drowing_character(table, SHIFT, column, strip.Color(0, 0, 0));
}

void loop()
{
  for(int i=9; i>=-38;i--){
    ss(l_A,i);
    ss(l_a,i+4);
    ss(l_B, i+8);
    ss(l_b, i+12);
    ss(l_C, i+16);
    ss(l_c, i+20);
    ss(l_D, i+24);
    ss(l_d, i+28);
    strip.show();
    delay(200);
    strip.clear();
  }
}

