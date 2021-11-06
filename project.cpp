#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include<bits/stdc++.h>
#include <unistd.h>


using namespace std;

int delay=5000;
vector<int>arr;
int n;

void renderfunction()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    
    float l = (float) n;
    float widthAdder = 1/l;
    //cout<<n<<endl;
    for(int i = 0; i < n; ++i)
    {
        glBegin(GL_POLYGON);
        
        // + 1 so value of 0 has height of 1
        float arrayIndexHeightRatio = 2*(arr[i] + 1)/l;
        float widthIndexAdder = 2*i/l;

        float leftX   = -1 + widthIndexAdder;
        float rightX  = leftX + widthAdder;
        float bottomY = -1;
        float topY    = bottomY + arrayIndexHeightRatio;

        // bottom left
        glColor4f(1,0,0,0);
        glVertex2f(leftX, bottomY);

        // bottom right
        glColor4f(0,1,0,0);
        glVertex2f(rightX, bottomY);

        // top right
        glColor4f(0,0,1,0);
        glVertex2f(rightX, topY);

        // top left
        glColor4f(0,0,0,1);
        glVertex2f(leftX, topY);

        glEnd();
    }
    glFlush();
    
}
void randomizearray()
{
    int i;
    for(i=0;i<n;i++)
    {
        arr[i]=rand()%100;
    }
}
void swap(int index1, int index2)
{
	std::swap(arr[index1], arr[index2]);
	renderfunction();
	usleep(delay);
}
void bubblesort()
{
    int i, j;
    for (i = 0; i < n-1; i++)    
    for (j = 0; j < n-i-1; j++)
        if (arr[j] > arr[j+1])
            swap(j,j+1);
}

void selectionsort()
{
    int i, j, min_idx;
    for (i = 0; i < n-1; i++)
    {
        min_idx = i;
        for (j = i+1; j < n; j++)
        if (arr[j] < arr[min_idx])
            min_idx = j;
        swap(min_idx, i);
    }
}

void insertionsort()
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            renderfunction();
            j = j - 1;
        }
        arr[j + 1] = key;
        renderfunction();
    }
}

void keyboardEvent(unsigned char c, int x, int y)
{
	if(c == 27)
	{
		// exit on escape key pressed
		exit(0);
        //free(arr);
	}
	else if(c == 98)
	{
        //enter b to run bubble sort visualizer 
        bubblesort();
	}
    else if(c==115)
    {
        //enter s for selection
        selectionsort();
    }
    else if(c==105)
    {
        //i for insertion
        insertionsort();
    }
    else if(c=='f')
    {
        glutFullScreen();
    }
}



int main(int argc, char** argv)
{
    srand(time(0));
    n=rand()%200;
    if(n==0)
            n=10;
    int i;
    for(i=0;i<n;i++)
    arr.push_back(i);
    randomizearray();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Sort ALgo Visualizer");
    glMatrixMode(GL_PROJECTION); 
    //gluOrtho2D (0,1000,0,1000);  
    glutDisplayFunc(renderfunction);
    glutKeyboardFunc(keyboardEvent);
    glutMainLoop();
    return 0;
}