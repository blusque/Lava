#pragma once

/* The unknown key */
#define LV_KEY_UNKNOWN            -1

/* Printable keys */
#define LV_KEY_SPACE              32
#define LV_KEY_APOSTROPHE         39  /* ' */
#define LV_KEY_COMMA              44  /* , */
#define LV_KEY_MINUS              45  /* - */
#define LV_KEY_PERIOD             46  /* . */
#define LV_KEY_SLASH              47  /* / */
#define LV_KEY_0                  48
#define LV_KEY_1                  49
#define LV_KEY_2                  50
#define LV_KEY_3                  51
#define LV_KEY_4                  52
#define LV_KEY_5                  53
#define LV_KEY_6                  54
#define LV_KEY_7                  55
#define LV_KEY_8                  56
#define LV_KEY_9                  57
#define LV_KEY_SEMICOLON          59  /* ; */
#define LV_KEY_EQUAL              61  /* = */
#define LV_KEY_A                  65
#define LV_KEY_B                  66
#define LV_KEY_C                  67
#define LV_KEY_D                  68
#define LV_KEY_E                  69
#define LV_KEY_F                  70
#define LV_KEY_G                  71
#define LV_KEY_H                  72
#define LV_KEY_I                  73
#define LV_KEY_J                  74
#define LV_KEY_K                  75
#define LV_KEY_L                  76
#define LV_KEY_M                  77
#define LV_KEY_N                  78
#define LV_KEY_O                  79
#define LV_KEY_P                  80
#define LV_KEY_Q                  81
#define LV_KEY_R                  82
#define LV_KEY_S                  83
#define LV_KEY_T                  84
#define LV_KEY_U                  85
#define LV_KEY_V                  86
#define LV_KEY_W                  87
#define LV_KEY_X                  88
#define LV_KEY_Y                  89
#define LV_KEY_Z                  90
#define LV_KEY_LEFT_BRACKET       91  /* [ */
#define LV_KEY_BACKSLASH          92  /* \ */
#define LV_KEY_RIGHT_BRACKET      93  /* ] */
#define LV_KEY_GRAVE_ACCENT       96  /* ` */
#define LV_KEY_WORLD_1            161 /* non-US #1 */
#define LV_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define LV_KEY_ESCAPE             256
#define LV_KEY_ENTER              257
#define LV_KEY_TAB                258
#define LV_KEY_BACKSPACE          259
#define LV_KEY_INSERT             260
#define LV_KEY_DELETE             261
#define LV_KEY_RIGHT              262
#define LV_KEY_LEFT               263
#define LV_KEY_DOWN               264
#define LV_KEY_UP                 265
#define LV_KEY_PAGE_UP            266
#define LV_KEY_PAGE_DOWN          267
#define LV_KEY_HOME               268
#define LV_KEY_END                269
#define LV_KEY_CAPS_LOCK          280
#define LV_KEY_SCROLL_LOCK        281
#define LV_KEY_NUM_LOCK           282
#define LV_KEY_PRINT_SCREEN       283
#define LV_KEY_PAUSE              284
#define LV_KEY_F1                 290
#define LV_KEY_F2                 291
#define LV_KEY_F3                 292
#define LV_KEY_F4                 293
#define LV_KEY_F5                 294
#define LV_KEY_F6                 295
#define LV_KEY_F7                 296
#define LV_KEY_F8                 297
#define LV_KEY_F9                 298
#define LV_KEY_F10                299
#define LV_KEY_F11                300
#define LV_KEY_F12                301
#define LV_KEY_F13                302
#define LV_KEY_F14                303
#define LV_KEY_F15                304
#define LV_KEY_F16                305
#define LV_KEY_F17                306
#define LV_KEY_F18                307
#define LV_KEY_F19                308
#define LV_KEY_F20                309
#define LV_KEY_F21                310
#define LV_KEY_F22                311
#define LV_KEY_F23                312
#define LV_KEY_F24                313
#define LV_KEY_F25                314
#define LV_KEY_KP_0               320
#define LV_KEY_KP_1               321
#define LV_KEY_KP_2               322
#define LV_KEY_KP_3               323
#define LV_KEY_KP_4               324
#define LV_KEY_KP_5               325
#define LV_KEY_KP_6               326
#define LV_KEY_KP_7               327
#define LV_KEY_KP_8               328
#define LV_KEY_KP_9               329
#define LV_KEY_KP_DECIMAL         330
#define LV_KEY_KP_DIVIDE          331
#define LV_KEY_KP_MULTIPLY        332
#define LV_KEY_KP_SUBTRACT        333
#define LV_KEY_KP_ADD             334
#define LV_KEY_KP_ENTER           335
#define LV_KEY_KP_EQUAL           336
#define LV_KEY_LEFT_SHIFT         340
#define LV_KEY_LEFT_CONTROL       341
#define LV_KEY_LEFT_ALT           342
#define LV_KEY_LEFT_SUPER         343
#define LV_KEY_RIGHT_SHIFT        344
#define LV_KEY_RIGHT_CONTROL      345
#define LV_KEY_RIGHT_ALT          346
#define LV_KEY_RIGHT_SUPER        347
#define LV_KEY_MENU               348

#define LV_KEY_LAST               LV_KEY_MENU

/*! @} */

/*! @defgroup mods Modifier key flags
 *  @brief Modifier key flags.
 *
 *  See [key input](@ref input_key) for how these are used.
 *
 *  @ingroup input
 *  @{ */

/*! @brief If this bit is set one or more Shift keys were held down.
 *
 *  If this bit is set one or more Shift keys were held down.
 */
#define LV_MOD_SHIFT           0x0001
/*! @brief If this bit is set one or more Control keys were held down.
 *
 *  If this bit is set one or more Control keys were held down.
 */
#define LV_MOD_CONTROL         0x0002
/*! @brief If this bit is set one or more Alt keys were held down.
 *
 *  If this bit is set one or more Alt keys were held down.
 */
#define LV_MOD_ALT             0x0004
/*! @brief If this bit is set one or more Super keys were held down.
 *
 *  If this bit is set one or more Super keys were held down.
 */
#define LV_MOD_SUPER           0x0008
/*! @brief If this bit is set the Caps Lock key is enabled.
 *
 *  If this bit is set the Caps Lock key is enabled and the @ref
 *  LV_LOCK_KEY_MODS input mode is set.
 */
#define LV_MOD_CAPS_LOCK       0x0010
/*! @brief If this bit is set the Num Lock key is enabled.
 *
 *  If this bit is set the Num Lock key is enabled and the @ref
 *  LV_LOCK_KEY_MODS input mode is set.
 */
#define LV_MOD_NUM_LOCK        0x0020