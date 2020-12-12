#ifndef LEVEL_CONTROL_h#define MAX_LEVEL 10int curLevel, levelTime[MAX_LEVEL+1];int godSpeedStartTime, godSpeedDuration = 2000;int levelUpTimeGap = 15000;char strLevel[5];/* Draws the level screen.*/void drawLevelWindow(){    int level_x = board_x - BoardGap - next_dx;    int level_y = next_y;    iSetColor(gameBoard[0][0].R, gameBoard[0][0].G, gameBoard[0][0].B);    iFilledRectangle(level_x, level_y, next_dx, next_dy);    iSetColor(220, 220, 250);    iFilledRectangle(level_x, nextCellY[3][0]+nextBlock_len, next_dx, 28);    iSetColor(0, 0, 230);    RetroText(level_x+30, nextCellY[3][0]+nextBlock_len+7, "LEVEL",2);    iSetColor(0, 0, 230);    if(curLevel < MAX_LEVEL){        convertToString(curLevel, strLevel);        RetroMiddleText(level_x+next_dx/2, level_y+next_dy/2, strLevel, 4);    }    else        RetroMiddleText(level_x+next_dx/2, level_y+next_dy/2, "X", 4);    if(curLevel == MAX_LEVEL && gameTime - godSpeedStartTime <= godSpeedDuration){        iSetColor(255, 0, 0);        RetroMiddleText(board_x+board_dx/2.0, board_y+board_dy/2.0+50, "GODSPEED", 4);    }}/* levelTime[i] indicates the time per dropDown for the shape in   i-th level*/void fillLevelUps(){    levelTime[0] = 850;    levelTime[1] = 800; levelTime[6] = 350;    levelTime[2] = 720; levelTime[7] = 260;    levelTime[3] = 640; levelTime[8] = 200;    levelTime[4] = 560; levelTime[9] = 160;    levelTime[5] = 480; levelTime[10] = 80;}/* After every levelUpTimeGap milliseconds, curLevel is inscreased.   Level 0 -> gameTime = 0 to levelUpTimeGap   Level 1 -> gameTime = levelUpTimeGap to 2*levelUpTimeGap   Level 2 -> gameTime = 2*levelUpTimeGap to 3*levelUpTimeGap   ... and so on. So basically, curLevel ==  gameTime/levelUpTimeGap*/void levelUp(){    if(GAMESTATE != GAMEPLAYING) return;    if(curLevel < MAX_LEVEL){        curLevel = gameTime/levelUpTimeGap;        if(curLevel == MAX_LEVEL){            godSpeedStartTime = gameTime;            PlaySound(TEXT("ominous intro.wav"), NULL, SND_LOOP | SND_ASYNC);        }    }}#endif // LEVEL_CONTROL_h