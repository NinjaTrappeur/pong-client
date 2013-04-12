#ifndef _PongTypes
#define _PongTypes

struct PongTypes
{
    enum E_PlayerState{
        CONNECTED,
        WAITING,
        ACCEPTED,
        READY,
        PLAYING,
        DISCARDED,
        DISCONNECTED
    };

    enum E_GameState{
        NOPARTY, //1
        WAITING_PLAYERS, //3
        INITIALIZING, //2
        RUNNING, //4
        PAUSED,
        GAMEOVER,
        EXITED
    };

    enum E_BallDir{
        RIGHT,
        LEFT,
        UP,
        DOWN,
        RND_DIR
    };
};

#endif
