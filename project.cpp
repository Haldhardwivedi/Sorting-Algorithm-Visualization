#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include<bits/stdc++.h>
#include <unistd.h>
#include <pthread.h>


using namespace std;

int delay=10000;
vector<int>arr;
int n;
bool fullscreen=false;

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
        {
            min_idx = j;
            usleep(delay);
        }
        swap(min_idx, i);
        usleep(delay);
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
            usleep(delay);
            j = j - 1;
        }
        arr[j + 1] = key;
        renderfunction();
        usleep(delay);
    }
}
//quick sort
int partition (int low, int high) 
{ 
    int pivot = arr[high]; // pivot 
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far
  
    for (int j = low; j <= high - 1; j++) 
    { 
        if (arr[j] < pivot) 
        { 
            i++; 
            swap(i,j); 
        } 
    } 
    swap(i + 1, high); 
    return (i + 1); 
}

void quickSort(int low, int high) 
{ 
    if (low < high) 
    { 
        int pi = partition(low, high); 
        quickSort(low, pi - 1); 
        quickSort(pi + 1, high); 
    } 
}

//keyboard event function
void keyboardEvent(unsigned char c, int x, int y)
{
	if(c == 27)
	{
		// exit on escape key pressed
		//exit(0);
        for(int i=0;i<n;i++)
        cout<<arr[i]<<" ";
        cout<<endl;
        glutDestroyWindow(glutGetWindow());
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
    else if(c=='q')
    {
        quickSort(0,n-1);
    }
    else if(c=='f')
    {
        fullscreen = !fullscreen;
        if (fullscreen) 
        {
            glutFullScreen();
        } 
        else 
        {
            glutReshapeWindow(1200, 900);
            glutPositionWindow(0,0);
        }
    }
}

int main(int argc, char** argv)
{
    pthread_t thread_id;
    srand(time(0));
    n=rand()%400;
    //n=300;
    if(n==0)
            n=30;
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
