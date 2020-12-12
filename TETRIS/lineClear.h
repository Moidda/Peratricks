#define BOMB_ANIMATIONS 5int Max_animate = Period+22*Period;int nclear = 0;int cur_bomb_animation = 0;int animations[BOMB_ANIMATIONS][10] = {{7,5,0,9,4,2,6,3,8,1}, {3,1,4,8,9,7,2,6,0,5},        {6,3,0,4,1,8,5,9,2,7}, {9,2,3,6,0,4,7,1,8,5}, {1,4,7,9,0,3,2,5,8,6}};void ProcessBomb()
{
    if(AnimateTimer > 0)
        AnimateTimer -= Period;

    if(AnimateTimer == 0)
    {
        if(bombfell_y == 0)
        {
            gameBoard[bombfell_y][bombfell_x].occupied = -1;
            bombfell_x = -1;
            bombfell_y = -1;        }
        else
        {
            bombcolor = gameBoard[bombfell_y-1][bombfell_x].occupied;
            gameBoard[bombfell_y][bombfell_x].occupied = -1;            cur_bomb_animation = rand() % BOMB_ANIMATIONS;
            AnimateTimer = Max_animate;
        }
    }
    else if(AnimateTimer == 20)
    {
        int i, j;
        for(j = 0; j < column_no; j++)
        {
            int shift = 0;
            for(i = 0; i<row_no; i++)
            {
                if(gameBoard[i][j].blip == -1)
                {
                    shift++;
                    gameBoard[i][j].blip = 0;
                }
                else
                {
                    int tmp = gameBoard[i][j].occupied;
                    gameBoard[i][j].occupied = -1;
                    gameBoard[i-shift][j].occupied = tmp;
                }
            }
        }

        bombfell_x = -1;
        bombfell_y = -1;
        bombcolor = -1;
    }
    else
    {        int whitepos = (Max_animate - AnimateTimer)/Period - 1;        int blipmode = (whitepos % 2) + 1;        whitepos = whitepos/2;

        int i;
        for(i = 0; i<row_no && whitepos > 0; i++)
        {            int t = animations[cur_bomb_animation][whitepos-1];
            if(gameBoard[i][t].blip == 2)
            {
                gameBoard[i][t].blip = -1;
            }
        }

        for(i = 0; i<row_no && whitepos<column_no; i++)
        {            int t = animations[cur_bomb_animation][whitepos];
            if(gameBoard[i][t].occupied == bombcolor)
            {                if(blipmode == 2)
                    gameBoard[i][t].occupied = -1;
                gameBoard[i][t].blip = blipmode;
            }
        }
    }

    return;
}
void LineClear(){    if(userPause)        return;    if(bombfell_x != -1)    {        ProcessBomb();        return;    }    if(AnimateTimer > 0)        AnimateTimer -= Period;    if(AnimateTimer == 0)    {        int checkflag = 1;        for(int i = 0; i<row_no; i++)        {            int clearflag = 1;            for(int j = 0; j<column_no; j++)            {                if(gameBoard[i][j].occupied < 0)                {                    clearflag = 0;                    break;                }            }            if(clearflag)            {                AnimateTimer = Max_animate;                destroyRow[i] = 1;                checkflag = 0;            }        }        if(checkflag == 1)        {            for(int d = 0; d<Diag_no; d++)            {                int clearflag = 1;                int color = -1;                for(int j = 0, i = d + j - 7; i < row_no && j < column_no; i++, j++)                {                    if(i<0 || j<0)                        continue;                    if(color == -1)                    {                        color = gameBoard[i][j].occupied;                        if(color == -1)                        {                            clearflag = 0;                            break;                        }                    }                    else if(color != gameBoard[i][j].occupied)                    {                        clearflag = 0;                        break;                    }                }                if(clearflag)                {                    AnimateTimer = Max_animate;                    destroyDiagF[d] = 1;                    checkflag = 0;                }            }        }        if(checkflag == 1)        {            for(int d = 0; d<Diag_no; d++)            {                int clearflag = 1;                int color = -1;                for(int j = 0, i = d - j + 2; i >= 0 && j < column_no; i--, j++)                {                    if(i>=row_no || j<0)                        continue;                    if(color == -1)                    {                        color = gameBoard[i][j].occupied;                        if(color == -1)                        {                            clearflag = 0;                            break;                        }                    }                    else if(color != gameBoard[i][j].occupied)                    {                        clearflag = 0;                        break;                    }                }                if(clearflag)                {                    AnimateTimer = Max_animate;                    destroyDiagB[d] = 1;                    checkflag = 0;                }            }        }    }    else if(AnimateTimer == 20)    {        int shift = 0;        for(int i = 0; i<row_no; i++)        {            if(destroyRow[i] == 1)            {                destroyRow[i] = 0;                nclear++;                shift++;                continue;            }            for(int j = 0; j<column_no; j++)            {                int tmp = gameBoard[i][j].occupied;                gameBoard[i][j].occupied = -1;                gameBoard[i-shift][j].occupied = tmp;            }        }        for(int j = 0; j<column_no; j++)        {            shift = 0;            for(int i = 0; i<row_no; i++)            {                int d = i - j + 7;                int e = i + j - 2;                if(destroyDiagF[d] == 1 || destroyDiagB[e] == 1)                {                    shift++;                    if(i == row_no - 1 || j == column_no - 1)                    {                        nclear += destroyDiagF[d];                        destroyDiagF[d] = 0;                    }                    if(i == 0 || j == column_no - 1)                    {                        nclear += destroyDiagB[e];                        destroyDiagB[e] = 0;                    }                    continue;                }                int tmp = gameBoard[i][j].occupied;                gameBoard[i][j].occupied = -1;                gameBoard[i-shift][j].occupied = tmp;            }        }    }    else    {        int whitepos = (Max_animate - AnimateTimer)/Period - 1;        int blipmode = (whitepos % 2) + 1;        whitepos = whitepos/2;        for(int i = 0; i<row_no; i++)        {            if(destroyRow[i] == 0)                continue;            if(whitepos > 0)                gameBoard[i][whitepos-1].blip = 0;            if(whitepos == column_no)                continue;            gameBoard[i][whitepos].blip = blipmode;            if(blipmode == 2)                gameBoard[i][whitepos].occupied = -1;        }        for(int d = 0; d<Diag_no; d++)        {            if(destroyDiagF[d] == 0)                continue;            int j = whitepos;            int i = d + j - 7;            if(i<0 || j<0 || i>row_no || j >column_no)                continue;            if(i > 0 && j > 0)                gameBoard[i-1][j-1].blip = 0;            if(i==row_no || j==column_no)                continue;            gameBoard[i][j].blip = blipmode + 2;            if(blipmode == 2)                gameBoard[i][j].occupied = -1;        }        for(int d = 0; d<Diag_no; d++)        {            if(destroyDiagB[d] == 0)                continue;            int j = whitepos;            int i = d - j + 2;            if(i>=row_no || i<-1 || j<0 || j > column_no)                continue;            if(i < row_no-1 && j > 0)                gameBoard[i+1][j-1].blip = 0;            if(i==-1 || j==column_no)                continue;            gameBoard[i][j].blip = 7 - blipmode;            if(blipmode == 2)                gameBoard[i][j].occupied = -1;        }    }    return;}void drawLineClearWindow(){    int lineclear_x = next_x;    int lineclear_y = next_y - BoardGap - next_dy - 28; // lineclear_y == score_y    // Draws the title rectangle    iSetColor(gameBoard[0][0].R, gameBoard[0][0].G, gameBoard[0][0].B);    iFilledRectangle(lineclear_x, lineclear_y, next_dx, next_dy);    // Draws the body rectangle    iSetColor(220, 220, 250);    iFilledRectangle(lineclear_x, lineclear_y+next_dy, next_dx, 28);    // Writes "LINE CLEARS"    iSetColor(0, 0, 230);    RetroMiddleText((double)(lineclear_x + (double)next_dx/2.0), (double)(lineclear_y + next_dy + (double) block_width/2.0), "ROW CLEAR", 2);    // Writes nclears in the window    char strLineClears[5];    convertToString(nclear, strLineClears);    RetroMiddleText((double)(lineclear_x + (double)next_dx/2.0), (double)(lineclear_y + (double)next_dy/2.0), strLineClears, 3);}