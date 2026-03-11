#pragma once

enum HandleWordStatus
{
    OK = 0,
    GOT_ERROR = 1,
    WRONG_ORDER = 2,
    NOT_JAPANESE_WORD = 3,
    NO_SPEACH_PART = 4,
    NO_FOUND_WORD = 5,
    GOT_END_WORD = 6,
    GOT_DOUBLED_WORD = 7,
    CANT_JOIN_WORDS = 8,
    GAME_NOT_FOUND = 9,
    GAME_STOPPED = 10,
    NO_FOUND_PLAYER = 11,
};