#ifndef SCORES_Hint userScore = 0;char strUserScore[200000];void drawScoreWindow(){    int score_x = board_x - BoardGap - next_dx;    int score_y = next_y - BoardGap - next_dy - 28;    iSetColor(gameBoard[0][0].R, gameBoard[0][0].G, gameBoard[0][0].B);    iFilledRectangle(score_x, score_y, next_dx, next_dy);    iSetColor(220, 220, 250                                                                                                                                                                                                                                                                                                                                              );    iFilledRectangle(score_x, score_y+next_dy, next_dx, 28);    // Writes "SCORE"    iSetColor(0, 0, 230);    RetroMiddleText((double)(score_x+(double)next_dx/2.0), (double)(score_y+next_dy+(double)block_width/2.0), "SCORE", 2);    // Writes the score in the window    convertToString(userScore, strUserScore);    RetroMiddleText((double)(score_x+(double)next_dx/2.0), (double)(score_y+(double)next_dy/2.0), strUserScore, 3);}#endif // SCORES_H