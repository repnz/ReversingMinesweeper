#pragma once


#define SMILE_NORMAL 0
#define SMILE_WOW    1
#define SMILE_LOST   2
#define SMILE_WINNER 3
#define SMILE_CLICKED 4


#define NUMBER_WIDTH 13
#define NUMBER_HEIGHT 23
#define NUMBER_Y 16

// Block Data:
// 8 bits:
// [ 8 7 6_5 4 3 2 1 ] 
// 1-4: The first 4 bits specifies the state of the block
// The next bit is unknown.. 
// 0x60: 
// 0x40: 7: Is Revealed?
// 0x80: 8: Is Bomb?

#define GET_SCREEN_WIDTH 0
#define GET_SCREEN_HEIGHT 1


#define BLOCK_IS_REVEALED 0x40
#define BLOCK_IS_BOMB 0x80

#define BLOCK_STATE_MASK 0x1f

#define BLOCK_STATE_BORDER_VALUE 0x10
#define BLOCK_STATE_EMPTY_UNCLICKED 0xF
#define BLOCK_STATE_FLAG 0xE
#define BLOCK_STATE_QUESTION_MARK 0xD
#define BLOCK_STATE_BOMB_RED_BACKGROUND 0xC
#define BLOCK_STATE_BOMB_WITH_X 0xB
#define BLOCK_STATE_BLACK_BOMB 0xA
#define BLOCK_STATE_CLICKED_QUESTION_MARK 9
#define BLOCK_STATE_NUMBER_8 8
#define BLOCK_STATE_NUMBER_7 7
#define BLOCK_STATE_NUMBER_6 6
#define BLOCK_STATE_NUMBER_5 5
#define BLOCK_STATE_NUMBER_4 4
#define BLOCK_STATE_NUMBER_3 3
#define BLOCK_STATE_NUMBER_2 2
#define BLOCK_STATE_NUMBER_1 1
#define BLOCK_STATE_READ_EMPTY 0

#define BLOCK_IS_STATE(Block, State) ((Block & BLOCK_STATE_MASK) == State)

#define BLOCK_WIDTH 16
#define BLOCK_HEIGHT 16

#define SMILE_BITMAP_WIDTH 24
#define SMILE_BITMAP_HEIGHT 24

#define BLACK_COLOR 0
#define WHITE_COLOR 0x00FFFFFF

typedef struct _HelpEntry {
    DWORD ControlIdentifier;
    DWORD ContextIdentifier;
} HelpEntry;

typedef struct _BOARD_POINT {
	DWORD Column;
	DWORD Row;
} BoardPoint;


#define HtmlHelpW_ExportOrdinal 0x0E

#define TIMER_ID 1
#define SOUND_ON 3
#define SOUNDTYPE_TICK 1
#define SOUNDTYPE_WIN 2
#define SOUNDTYPE_LOSE 3

#define DIFFICULTY_BEGINNER 0
#define DIFFICULTY_INTERMEDIATE 1
#define DIFFICULTY_EXPERT 2
#define DIFFICULTY_CUSTOM 3

#define POINT_BIG_NUM_X 17
#define POINT_MID_NUM_X 30
#define POINT_LOW_NUM_X 43

#define NUM_MINUS 11


#define GAME_MENU_INDEX 0
#define HELP_MENU_INDEX 1

#define MOVE_WINDOW 2
#define REPAINT_WINDOW 4


typedef enum _RegistryValue {
	Difficulty,
	Mines,
	Height,
	Width,
	Xpos,
	Ypos,
	Sound,
	Mark,
	Menu,
	Tick,
	Color,
	Time1,
	Name1,
	Time2,
	Name2,
	Time3,
	BestExpertName,
	AlreadyPlayed
} RegistryValue;

typedef struct _DifficultyConfigItem {
	DWORD Mines;
	DWORD Height;
	DWORD Width;
} DifficultyConfigItem;

#define BEGINNER_MINES 10
#define BEGINEER_HEIGHT 9
#define BEGINNER_WIDTH 9

#define INTERMIDIATE_MINES 40
#define INTERMIDIATE_HEIGHT 16
#define INTERMIDIATE_WIDTH 16

#define EXPERT_MINES 99
#define EXPERT_HEIGHT 16
#define EXPERT_WIDTH 30

