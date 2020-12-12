#ifndef GAME_FLOW_H/* Finds coordinate of all 20*10 cells of the board.   gameCellX[i][j] contains abscissa of ith row, jth col.   gameCellY[i][j] contains ordinate of ith row, jth col.   The south-west cell is row 0, col 0 and is numbered in a manner   similar to cartesian coordinate system. */void createGameBoard(){    int i = 0, j, tempX, tempY;    board_dx = column_no*block_width + 2*column_no*wall_width;    board_dy = row_no*block_width + 2*row_no*wall_width;    for(i = 0; i < row_no; i++)        for(j = 0; j < column_no; j++){            tempX = board_x + wall_width + j*(block_width + 2*wall_width);            tempY = board_y + wall_width + i*(block_width + 2*wall_width);            gameCellX[i][j] = tempX;            gameCellY[i][j] = tempY;        }    // gameBoard[i][j].occupied contains the shapeIndex of the block/shape    // that is present in ith row jth col. -1 indicates the cell is empty    for(i = 0; i < row_no+3; i++)        for(j = 0; j < column_no; j++){            gameBoard[i][j].occupied = -1;            gameBoard[i][j].R = 77;            gameBoard[i][j].G = 195;            gameBoard[i][j].B = 255;            gameBoard[i][j].blip = 0;        }    memset(destroyRow, 0, sizeof destroyRow);    memset(destroyDiagF, 0, sizeof destroyDiagF);    memset(destroyDiagB, 0, sizeof destroyDiagB);}/* Initializes the position of every shape at the top   of the board. */void createShapes(){    FILE *fp;    if((fp = fopen("Create Shapes.txt", "r")) == NULL){        printf("Cannot open \"Create Shapes.txt\".\n");        exit(0);    }    int i, j;    while(!feof(fp)){        for(i = 0; i < 7; i++)            for(j = 0; j < 4; j++)                fscanf(fp, "%d %d", &shape[i].blockRow[j], &shape[i].blockCol[j]);    }    fclose(fp);    for(i = 0; i < 4; i++){        shape[7].blockRow[i] = 20;        shape[7].blockCol[i] = 5;    }}/* Draws the shadow of the currently falling shape. */void drawShadow(){    int shift, i;    int found = 0;    for(shift = 0; shift<25; shift++)    {        for(i = 0; i < 4; i++)        {            int tempRow = shape[shapeIndex].blockRow[i] - shift - 1;            int tempCol = shape[shapeIndex].blockCol[i];            if(tempRow < 0 || (gameBoard[tempRow][tempCol].occupied > -1 && gameBoard[tempRow][tempCol].blip >= 0))                found = 1;        }        if(found == 1)            break;    }    if(shift == 0)        return;    iSetColor(100, 100, 155);    for(i = 0; i < 4; i++){        int tempRow = shape[shapeIndex].blockRow[i] - shift;        int tempCol = shape[shapeIndex].blockCol[i];        if(tempRow < row_no)        iFilledRectangle(gameCellX[tempRow][tempCol]-1*wall_width, gameCellY[tempRow][tempCol]-1*wall_width, block_width+2*wall_width, block_width+2*wall_width);    }}/* Draws the current shape which is levitating/falling down, i.e. the   shape which has still not taken its position on the gameBoard */void drawShape(){    int i;    drawShadow();    for(i = 0; i < 4; i++){        int tempRow = shape[shapeIndex].blockRow[i];        int tempCol = shape[shapeIndex].blockCol[i];        if(tempRow < row_no){                block(gameCellX[tempRow][tempCol], gameCellY[tempRow][tempCol], block_width, shapeIndex);        }    }}/* Draws the board. The cells of the board are either empty or occupied by some blocks    of some shapes. The coloring is done accordingly. */void drawBoard(){    // Draws a white rectangle    iSetColor(255, 255, 255);    iFilledRectangle(board_x, board_y, board_dx, board_dy);    int i, j;    // Draws all the cells over the white rectangle    for(i = 0; i < row_no; i++)        for(j = 0; j < column_no; j++){            if(gameBoard[i][j].occupied == -1 || gameBoard[i][j].occupied == 7){                iSetColor(gameBoard[i][j].R, gameBoard[i][j].G, gameBoard[i][j].B);                iFilledRectangle(gameCellX[i][j], gameCellY[i][j], block_width, block_width);            }            else{                block(gameCellX[i][j], gameCellY[i][j], block_width, gameBoard[i][j].occupied);            }            if(bombfell_x != -1)                iSetColor(0, 0, 0);            else                iSetColor(255, 255, 255);            if(gameBoard[i][j].blip == 1){                iFilledRectangle(gameCellX[i][j], gameCellY[i][j], block_width/2, block_width);            }            else if(gameBoard[i][j].blip == 2){                iFilledRectangle(gameCellX[i][j]+block_width/2, gameCellY[i][j], block_width/2, block_width);            }            else if(gameBoard[i][j].blip == 3){                double triangleX[3] = {gameCellX[i][j], gameCellX[i][j]+block_width, gameCellX[i][j]};                double triangleY[3] = {gameCellY[i][j], gameCellY[i][j], gameCellY[i][j]+block_width};                iFilledPolygon(triangleX, triangleY, 3);            }            else if(gameBoard[i][j].blip == 4){                double triangleX[3] = {gameCellX[i][j], gameCellX[i][j]+block_width, gameCellX[i][j]+block_width};                double triangleY[3] = {gameCellY[i][j]+block_width, gameCellY[i][j]+block_width, gameCellY[i][j]};                iFilledPolygon(triangleX, triangleY, 3);            }            else if(gameBoard[i][j].blip == 5){                double triangleX[3] = {gameCellX[i][j], gameCellX[i][j]+block_width, gameCellX[i][j]+block_width};                double triangleY[3] = {gameCellY[i][j], gameCellY[i][j], gameCellY[i][j]+block_width};                iFilledPolygon(triangleX, triangleY, 3);            }            else if(gameBoard[i][j].blip == 6){                double triangleX[3] = {gameCellX[i][j], gameCellX[i][j], gameCellX[i][j]+block_width};                double triangleY[3] = {gameCellY[i][j], gameCellY[i][j]+block_width, gameCellY[i][j]+block_width};                iFilledPolygon(triangleX, triangleY, 3);            }        }}void drawPauseScreen(){    int pause_dx = 600, pause_dy = 500;    double pause_x = board_x - BoardGap - next_dx; //(score_x + next_dx/2)    double pause_y = (700-pause_dy)/2;    //255, 255, 204    // Draws the pause screen background    iSetColor(240, 240, 240);    iFilledRectangle(pause_x, pause_y, pause_dx, pause_dy);    // Writes "PAUSED"    int PAUSED_DY = 140;    iSetColor(77, 148, 255);    RetroMiddleText(pause_x+pause_dx/2, pause_y+pause_dy-PAUSED_DY/2, "PAUSED", 9);    int tempX = pauseBarX, tempY = pauseBarY;    int selected = 0;    if(tempX<=Mx && Mx<=tempX+menuBardx && tempY<=My && My<=tempY+menuBardy) selected = 1;    else if(dis(Mx,My, tempX,tempY+menuBardy/2) <= menuBardy/2) selected = 1;    else if(dis(Mx,My, tempX+menuBardx,tempY+menuBardy/2) <= menuBardy/2) selected = 1;    else selected = 0;    iSetColor(77, 195, 255);    drawBar(tempX, tempY, menuBardx, menuBardy, popUpSize, selected);    int tempfnt = (selected) ? 4 : 3;    iSetColor(0, 0, 230);    RetroMiddleText(tempX+menuBardx/2, tempY+menuBardy/2, "RESUME", tempfnt);    selected = 0;    tempY = pauseBarY-menuBarGap-menuBardy;    if(tempX<=Mx && Mx<=tempX+menuBardx && tempY<=My && My<=tempY+menuBardy) selected = 1;    else if(dis(Mx,My, tempX,tempY+menuBardy/2) <= menuBardy/2) selected = 1;    else if(dis(Mx,My, tempX+menuBardx,tempY+menuBardy/2) <= menuBardy/2) selected = 1;    else selected = 0;    iSetColor(77, 195, 255);    drawBar(tempX, tempY, menuBardx, menuBardy, popUpSize, selected);    tempfnt = (selected) ? 4 : 3;    iSetColor(0, 0, 230);    RetroMiddleText(tempX+menuBardx/2, tempY+menuBardy/2, "MENU", tempfnt);}void checkPauseOption(int mx, int my){    int tempX = pauseBarX, tempY = pauseBarY;    /* resume the game */    int selected = isBarSelected(mx, my, tempX, tempY, menuBardx, menuBardy);    if(selected){        userPause ^= 1;        return;    }    /* quit the current game to exit to main menu */    tempY = pauseBarY-menuBarGap-menuBardy;    selected = isBarSelected(mx, my, tempX, tempY, menuBardx, menuBardy);    if(selected){//        userPause ^= 1;//        GAMESTATE = GAMEMENU;        GAMESTATE = GAMEPAUSEMENU;    }}void playGame(){    drawBoard();    drawShape();    drawNextWindow();    drawLevelWindow();    drawScoreWindow();    drawLineClearWindow();    if(userPause){        drawPauseScreen();    }}int IsGameOver(){    int i, tempR, tempC;    for(i = 0; i < 4; i++){        tempR = shape[shapeIndex].blockRow[i];        tempC = shape[shapeIndex].blockCol[i];        if(tempR-1 >= row_no) return 1;    }    return 0;}/* This function is called inside dropDown(). If a shape cannot be dropped down,   then check if game is over not */void processForGameOver(){    if(IsGameOver()){        GAMESTATE = GAMEOVER;    }}/* Writes GAME OVER on the screen */void drawGameOverWindow(){    iSetColor(goR, 0, 0);    double x = board_x+board_dx/2+10;    double y = 350+50;    RetroMiddleText(x, y, "GAME OVER", 12);}/* GAMESTATE == GAMEOVER */void printGameOver(){    drawBoard();    drawNextWindow();    drawLevelWindow();    drawScoreWindow();    drawLineClearWindow();    drawGameOverWindow();}/* Same dimensions as the pause screen */void drawUserScoreWindow(){    int UserScore_dx = 600, UserScore_dy = 500;    double UserScore_x = board_x - BoardGap - next_dx; //(score_x + next_dx/2)    double UserScore_y = (700-UserScore_dy)/2;    // Draws the score screen background    iSetColor(240, 240, 240);    iFilledRectangle(UserScore_x, UserScore_y, UserScore_dx, UserScore_dy);    // Writes "STATUS"    int USERSCORE_DY = 140;    iSetColor(77, 148, 255);    RetroMiddleText(UserScore_x+UserScore_dx/2, UserScore_y+UserScore_dy-USERSCORE_DY/2, "STAT", 9);    char str[50], tempStr[50];    strcpy(str, "SCORE  ");    convertToString(userScore, tempStr);    strcat(str, tempStr);    double y = (double)UserScore_y + 3.5*(double)((UserScore_dy-USERSCORE_DY)/5);    RetroMiddleText(UserScore_x+UserScore_dx/2, y, str, 3);    strcpy(str, "LINE CLEARS  ");    convertToString(nclear, tempStr);    strcat(str, tempStr);    y = (double)UserScore_y + 2.5*(double)((UserScore_dy-USERSCORE_DY)/5);    RetroMiddleText(UserScore_x+UserScore_dx/2, y+10, str, 3);    strcpy(str, "TOTAL SCORE  ");    convertToString(userScore+nclear*bonus, tempStr);    strcat(str, tempStr);    y = (double)UserScore_y + 1.5*(double)((UserScore_dy-USERSCORE_DY)/5);    RetroMiddleText(UserScore_x+UserScore_dx/2, y+20, str, 3);}/* GAMESTATE == GAMESCORE */void printScore(){    drawBoard();    drawNextWindow();    drawLevelWindow();    drawScoreWindow();    drawLineClearWindow();    drawUserScoreWindow();}/* Resets everything for another new game to be played */void resetToNewGame(){    createGameBoard();    createShapes();    createNextBoard();    gameTime = 0;    userScore = 0;    prevDropTime = 0;    prevBombTime = 0;    nclear = 0;    curLevel = 0;    userPause = 0;    bombfell_x = -1;    bombfell_y = -1;    bombcolor = -1;    AnimateTimer = 0;    shapeIndex = rand() % 7;    nextShapeIndex = (rand() + rand()) % 7;    PlaySound(TEXT("tetris-gameboy-02.wav"), NULL, SND_LOOP | SND_ASYNC);    GAMESTATE = GAMEPLAYING;}#endif // GAME_FLOW_H