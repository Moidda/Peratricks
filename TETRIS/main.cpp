# include "iGraphics.h"
        {
            bombfell_x = shape[shapeIndex].blockCol[0];
            bombfell_y = shape[shapeIndex].blockRow[0];
        }
void iDraw() {
	iClear();

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my) {


/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if(GAMESTATE == GAMEMENU) checkMenuOption(mx, my);
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {

	}
}


void iKeyboard(unsigned char key) {
	/* Taking userName from the user */
		if(GAMESTATE == GAMEPLAYING) userPause ^= 1;
	}
		/* Stop game to exit to main menu */
	}
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
	*/
void iSpecialKeyboard(unsigned char key) {

	if (key == GLUT_KEY_END) {
		exit(0);
	}


int main() {
	//place your own initialization codes here.

	return 0;
}