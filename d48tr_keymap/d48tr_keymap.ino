#include "d48tr_lib.h"

/*---------------------------------------------------------------------------------------//
 * define the parameters
 */
#define Delay 34
#define TAPPING_TERM 200

/*---------------------------------------------------------------------------------------//
 * This parameters are default
 */
#define key_press 0
#define Tap 1
#define Hold 2
#define Hold_release 3
#define key_release 3

#define MO(layer) (0x2000+layer*16*16)
#define LT(layer, kc) (0x9000+layer*16*16+kc)

int wheel = 0;
const int tap_count_max = TAPPING_TERM/Delay;

const int rowNum = 4;
const int colNum = 12;

const int rowPin[rowNum] = { 0, 1, 19, 18 };
const int colPin[colNum] = { 15, 14, 16, 10, 9, 8, 7, 6, 5, 4, 20, 21};

bool currentState[rowNum][colNum];
bool beforeState[rowNum][colNum];
int tap_count[rowNum][colNum] = {};
int i,j;

/*---------------------------------------------------------------------------------------//
 * define the keymap
 */
enum custom_keycodes {
  XXXXXXX = 0x1001,
  MS_L,
  MS_R,
  MS_WH
};

enum tap_custom_keycodes {
  ALT_MS_R = 0x8001
};

//up to 16
enum layer_number {
  _QWERTY = 0,
  _RAISE,
  _LOWER
};

int defaultLayer = _QWERTY;
int currentLayer = defaultLayer;

const uint16_t keyMap[][rowNum][colNum]  = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   -  | Enter|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  |Alt/  |MS_WH |MS_L  |Space |Lower/|Raise/| Left | Down |  Up  |Right |
 * |      |      |MS_R  |      |      |      |Space |KANJI |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
*/
  [_QWERTY] = {
    { KC_ESC ,  KC_Q,      KC_W,      KC_E,    KC_R,    KC_T,      KC_Y,             KC_U,               KC_I,    KC_O,    KC_P,    KC_BSPC },
    { KC_TAB ,  KC_A,      KC_S,      KC_D,    KC_F,    KC_G,      KC_H,             KC_J,               KC_K,    KC_L,    KC_MINS, KC_ENT  },
    { KC_LSFT,  KC_Z,      KC_X,      KC_C,    KC_V,    KC_B,      KC_N,             KC_M,               KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT },
    { KC_LCTL,  KC_LGUI,   ALT_MS_R,  MS_WH,   MS_L,    KC_SPC,    LT(_LOWER,KC_SPC),LT(_RAISE,KC_KANJI),KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT }
    }, 

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | Enter|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |      |      | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  |Alt/  |MS_WH |MS_L  |Space |Lower/|Raise/| Left | Down |  Up  |Right |
 * |      |      |MS_R  |      |      |      |Space |KANJI |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
*/
  [_RAISE] = {
    { KC_ESC ,  KC_1,      KC_2,      KC_3,    KC_4,    KC_5,      KC_6,             KC_7,               KC_8,    KC_9,    KC_0,    KC_BSPC  },
    { KC_TAB ,  KC_F1,     KC_F2,     KC_F3,   KC_F4,   KC_F5,     KC_F6,            KC_F7,              KC_F8,   KC_F9,   KC_F10,  KC_ENT   },
    { KC_LSFT,  KC_F7,     KC_F8,     KC_F9,   KC_F10,  KC_F11,    KC_F12,           XXXXXXX,            XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT  },
    { KC_LCTL,  KC_LGUI,   ALT_MS_R,  MS_WH,   MS_L,    KC_SPC,    LT(_LOWER,KC_SPC),LT(_RAISE,KC_KANJI),KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  }
    },

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |  F1  |  F2  |  F3  |      |      |   ^  |   \  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   4  |   5  |   6  |  F4  |  F5  |  F6  |      |      |   @  |   [  | Enter|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   7  |   8  |   9  |  F7  |  F8  |  F9  |      |      |   *  |   ]  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  |Alt/  |MS_WH |MS_L  |Space |Lower/|Raise/| Left |   /  |   _  |Right |
 * |      |      |MS_R  |      |      |      |Space |KANJI |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
*/
  [_LOWER] = {
    { KC_ESC ,  KC_1,      KC_2,      KC_3,    KC_F1,   KC_F2,     KC_F3,            XXXXXXX,            XXXXXXX, KC_CIRC, KC_JYEN, KC_BSPC  },
    { KC_TAB ,  KC_4,      KC_5,      KC_6,    KC_F4,   KC_F5,     KC_F6,            XXXXXXX,            XXXXXXX, KC_AT  , KC_LBRC, KC_ENT   },
    { KC_LSFT,  KC_7,      KC_8,      KC_9,    KC_F7,   KC_F8,     KC_F9,            XXXXXXX,            XXXXXXX, KC_PAST, KC_RBRC, KC_RSFT  },
    { KC_LCTL,  KC_LGUI,   ALT_MS_R,  MS_WH,   MS_L,    KC_SPC,    LT(_LOWER,KC_SPC),LT(_RAISE,KC_KANJI),KC_LEFT, KC_SLSH, KC_UNDS, KC_RGHT  }
    }
};


/*---------------------------------------------------------------------------------------//
 * key functions
 */

void function_key(uint16_t keycode, int state){
  int function_digit = keycode/4096;
  int layer_digit = keycode%4096/256;
  int kc_digit = keycode%256;

  //MO
  if (function_digit == 2){
    switch(state) {
      case key_press:
        currentLayer = layer_digit;
        break;
      case key_release:
        currentLayer = defaultLayer;
        break; 
    } 
  }
  //LT
  else if (function_digit == 9){
    switch(state) {
      case key_press:
        break;
      case Tap:
        Keyboard.press( kc_digit );
        Keyboard.release( kc_digit );
        break;
      case Hold:
        currentLayer = layer_digit;
        break;
      case Hold_release:
        currentLayer = defaultLayer;
        break;
    }
  }


  //custom_keycodes
  else if (function_digit == 1){
    
    switch(keycode) {  
      case XXXXXXX:
        switch(state) {
          case key_press:
            break;
          case key_release:
            break;
        }
      break;
        
      case MS_L:
        switch(state) {
          case key_press:
            Mouse.press(MOUSE_LEFT);
            break;
          case key_release:
            Mouse.release(MOUSE_LEFT);
            break;
        }
      break;

      case MS_R:
        switch(state) {
          case key_press:
            Mouse.press(MOUSE_RIGHT);
            break;
          case key_release:
            Mouse.release(MOUSE_RIGHT);
            break;
        }
      break;

      case MS_WH:
        switch(state) {
          case key_press:
            wheel = 1;
            break;
          case key_release:
            wheel = 0;
            break;
        }
      break;
    }
  }
  
  //custom_keycodes(Tap enable)
  else if (function_digit == 8){
    
    switch(keycode) {
      case ALT_MS_R:
        switch(state) {
          case key_press:
          break;
        case Tap:
          Mouse.press(MOUSE_RIGHT);
          Mouse.release(MOUSE_RIGHT);
          break;
        case Hold:
          Keyboard.press(KC_LALT);
          break;
        case Hold_release:
          Keyboard.release(KC_LALT);
          break;
        }

        
   }
 }
}


/*---------------------------------------------------------------------------------------//
 * main
 */

void setup() {
  Mouse.begin();
  Wire.begin();
  Serial.begin(9600);
  Keyboard.begin();
  SetLedMode();
  SetDefault();
  WriteReg(); 

  for( i = 0; i < rowNum; i++){
    pinMode(rowPin[i],OUTPUT);
  }

  for( i = 0; i < colNum; i++){
    pinMode(colPin[i],INPUT_PULLUP);
  }

  for( i = 0; i < rowNum; i++){
    for( j = 0; j < colNum; j++){
      currentState[i][j] = HIGH;
      beforeState[i][j] = HIGH;
    }
    digitalWrite(rowPin[i],HIGH);
  }
}

void loop() {
  for( i = 0; i < rowNum; i++){
    digitalWrite( rowPin[i], LOW );

    for( j = 0; j < colNum; j++){
      currentState[i][j] = digitalRead(colPin[j]);
        
      if ( currentState[i][j] != beforeState[i][j] ){
        
        
        //------key press
        if ( currentState[i][j] == LOW){
          
          //Tap function key
          if ( keyMap[currentLayer][i][j] >= 0x8000) { 
            function_key( keyMap[currentLayer][i][j], key_press);
            tap_count[i][j]++;
            
          //Function key
          }else if ( keyMap[currentLayer][i][j] >= 0x1000) { 
            function_key( keyMap[currentLayer][i][j], key_press);
            
          //nomal key
          } else {
            Keyboard.press(keyMap[currentLayer][i][j] );
          }

        //-------key release
        } else {
          
          //Tap function key
          if ( keyMap[currentLayer][i][j] >= 0x8000) { 
            
            //****Tap
            if ( tap_count[i][j] < tap_count_max){              
              function_key( keyMap[currentLayer][i][j], Tap);
              tap_count[i][j] = 0;
            }
            
            //****Hold release
            else if ( tap_count[i][j] >= tap_count_max){
              function_key( keyMap[currentLayer][i][j], Hold_release);
              tap_count[i][j] = 0;
            }
            
          //Function key
          } else if ( keyMap[currentLayer][i][j] >= 0x1000) {
            //****key release
            function_key( keyMap[currentLayer][i][j], key_release);
          
          //Nomal key
          } else {
            Keyboard.release( keyMap[currentLayer][i][j] );
          }  
        }
        beforeState[i][j] = currentState[i][j];

      //-------key pressing
      } else {     
        //pressing...
        if ((tap_count[i][j] >= 1) && (tap_count[i][j] < tap_count_max)){
          tap_count[i][j]++;
        }

        //****Hold
        else if (tap_count[i][j] == tap_count_max){ 
          tap_count[i][j]++;
          function_key( keyMap[currentLayer][i][j], Hold);
        }
      }
      
    }
    digitalWrite( rowPin[i], HIGH );
  }
  PrintTrackData( wheel );

  delay(Delay);
}
