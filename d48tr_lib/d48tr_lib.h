#ifndef D48TR_LIB_H
#define D48TR_LIB_H

#include "Keyboard_jp.h"
#include <Wire.h>
#include "Mouse.h"


#define MouseClickAction MOUSE_LEFT

#define KC_EXLM        0x21             //!
#define KC_HASH        0x23             //#
#define KC_DLR         0x24             //$
#define KC_AMPR        0x26             //&
#define KC_QUOT        0x27             //'
#define KC_LPRN        0x28             //(
#define KC_RPRN        0x29             //)
#define KC_PAST        0x2A             //*
#define KC_PPLS        0x2B             //+
#define KC_COMM        0x2C             //,
#define KC_PMNS        0x2D             //-
#define KC_DOT         0x2E             //.
#define KC_SLSH        0x2F             ///
#define KC_0           0x30             //0
#define KC_1           0x31             //1
#define KC_2           0x32             //2
#define KC_3           0x33             //3
#define KC_4           0x34             //4
#define KC_5           0x35             //5
#define KC_6           0x36             //6
#define KC_7           0x37             //7
#define KC_8           0x38             //8
#define KC_9           0x39             //9
#define KC_COLN        0x3A             //:
#define KC_SCLN        0x3B             //;
#define KC_LABK        0x3C             //<
#define KC_EQL         0x3D             //=
#define KC_RABK        0x3E             //>
#define KC_QUES        0x3F             //?
#define KC_JYEN        0x5C             //\
#define KC_RBRC        0x5D             //]
#define KC_CIRC        0x5E             //^
#define KC_UNDS        0x5F             //_
#define KC_GRV         0x60             //`
#define KC_A           0x61             //a
#define KC_B           0x62             //b
#define KC_C           0x63             //c
#define KC_D           0x64             //d
#define KC_E           0x65             //e
#define KC_F           0x66             //f
#define KC_G           0x67             //g
#define KC_H           0x68             //h
#define KC_I           0x69             //i
#define KC_J           0x6A             //j
#define KC_K           0x6B             //k
#define KC_L           0x6C             //l
#define KC_M           0x6D             //m
#define KC_N           0x6E             //n
#define KC_O           0x6F             //o
#define KC_P           0x70             //p
#define KC_Q           0x71             //q
#define KC_R           0x72             //r
#define KC_S           0x73             //s
#define KC_T           0x74             //t
#define KC_U           0x75             //u
#define KC_V           0x76             //v
#define KC_W           0x77             //w
#define KC_X           0x78             //x
#define KC_Y           0x79             //y
#define KC_Z           0x7A             //z
#define KC_LCBR        0x7B             //{
#define KC_PIPE        0x7C             //|
#define KC_RCBR        0x7D             //}
#define KC_TILD        0x7E             //~
#define KC_ENT         0x80             //Return (Enter)
#define KC_ESC         0x81             //Escape
#define KC_BSPC        0x82             //Delete (Backspace)
#define KC_TAB         0x83             //Tab
#define KC_SPC         0x84             //space
#define KC_MINS        0x85             //-
#define KC_CIRC        0x86             //^
#define KC_AT          0x87             //@
#define KC_LBRC        0x88             //[
#define KC_RBRC        0x89             //]
#define KANJI          0x8d             //0x35
#define KC_CAPS        0x91             //0x39
#define KC_F1          0x92             //0x3a
#define KC_F2          0x93             //0x3b
#define KC_F3          0x94             //0x3c
#define KC_F4          0x95             //0x3d
#define KC_F5          0x96             //0x3e
#define KC_F6          0x97             //0x3f
#define KC_F7          0x98             //0x40
#define KC_F8          0x99             //0x41
#define KC_F9          0x9a             //0x42
#define KC_F10         0x9b             //0x43
#define KC_F11         0x9c             //0x44
#define KC_F12         0x9d             //0x45
#define KC_PSCR        0x9e             //0x46
#define KC_SLCK        0x9f             //0x47
#define KC_PAUS        0xa0             //0x48
#define KC_INS         0xa1             //0x49
#define KC_HOME        0xa2             //0x4a
#define KC_PGUP        0xa3             //0x4b
#define KC_DEL         0xa4             //0x4c
#define KC_END         0xa5             //0x4d
#define KC_PGDN        0xa6             //0x4e
#define KC_RGHT        0xa7             //0x4f
#define KC_LEFT        0xa8             //0x50
#define KC_DOWN        0xa9             //0x51
#define KC_UP          0xaa             //0x52
#define KANA           0xe0             //0x88
#define HENKAN         0xe2             //0x8a
#define MUHENKAN       0xe3             //0x8b
#define KC_LCTL        0xf8             //0xe0
#define KC_LSFT        0xf9             //0xe1
#define KC_LALT        0xfa             //0xe2
#define KC_LGUI        0xfb             //0xe3
#define KC_RCTL        0xfc             //0xe4
#define KC_RSFT        0xfd             //0xe5
#define KC_RALT        0xfe             //0xe6
#define KC_RGUI        0xff             //0xe7


void SetLedMode(void);
void SetDefault(void);
void WriteReg(void);
void PrintTrackData(int wheel);

#endif
