#define BOMB_ANIMATIONS 5
{
    if(AnimateTimer > 0)
        AnimateTimer -= Period;

    if(AnimateTimer == 0)
    {
        if(bombfell_y == 0)
        {
            gameBoard[bombfell_y][bombfell_x].occupied = -1;
            bombfell_x = -1;
            bombfell_y = -1;
        else
        {
            bombcolor = gameBoard[bombfell_y-1][bombfell_x].occupied;
            gameBoard[bombfell_y][bombfell_x].occupied = -1;
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
    {

        int i;
        for(i = 0; i<row_no && whitepos > 0; i++)
        {
            if(gameBoard[i][t].blip == 2)
            {
                gameBoard[i][t].blip = -1;
            }
        }

        for(i = 0; i<row_no && whitepos<column_no; i++)
        {
            if(gameBoard[i][t].occupied == bombcolor)
            {
                    gameBoard[i][t].occupied = -1;
                gameBoard[i][t].blip = blipmode;
            }
        }
    }

    return;
}
