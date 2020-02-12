#include "cub3d.h"
#include "mlx.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <math.h>


void *mlx_ptr;
void *win_ptr;

//design morba3 (map 2D)
char **line;
int y_len;
int x;
int y;
int k = 0;
int remaind = 50;
int none = 1;

// Player movement
int X_player;
int Y_player;   
int radian = 3;
float rotationAngle = M_PI / 2;
float rotationSpeed = 5;
int len_angle = 30;
float turnDirection = 0;
int walkDirection = 0;

/*
 int len_y(int y,int fd)
{
    int i;

    i = 2;
    while (get_next_line(fd,&line))
        i++;
    return (y = y / i);
} */


int design_morba3(int i,unsigned int color, char **line, int j)
{
    int save;
    int y_copy;
    y_copy = y;
    save = k;

   // i = i + 1;
    while (k < x)
    {
        mlx_pixel_put(mlx_ptr, win_ptr, k, y, color);
        k++;
        if (k == x)
        {
            k = save;
            y = y - 1;
            if (y == remaind - 51)
            {
                k+=50;
                break;
            }
           
        } 
    }
    if (line[j][i] == 'N' && none == 1)
    {
        mlx_pixel_put(mlx_ptr, win_ptr, k, y, 0xFF0000);
        X_player = k;
        Y_player = y;
        none++;
    }
    y = y_copy;
    x = x + 50;
    return k;
}


void ft_morba3(char **line)
{
    int i;
    int j;  
    unsigned int color;

   
    i = 0;
    j = 0;
    while(line[j][i])
    {
        if (line[j][i] == '1')
        {
            color = 0xFFFFFF;
            design_morba3(i, color, line, j);
        }
        else if(line[j][i] == '0' || line[j][i] == 'N')
        {
            color = 0xFFF600;
            design_morba3(i, color, line, j);
        }
        i++;
        if (line[j][i] == '\0')
        {
            i = 0;
            if (line[j + 1] != NULL)
            {
                j++;
                y = y + 50;
                x = 50;
                remaind = remaind + 50;
                k = 0;
            }
            else
                break;
        }    
    }
}





int abs (int n)
{ 
    return ( (n>0) ? n : ( n * (-1))); 
} 
  
//DDA Function for line generation 
void DDA(int X0, int Y0, int X1, int Y1) 
{ 
    // calculate dx & dy 
    int dx = X1 - X0; 
    int dy = Y1 - Y0; 
  
    // calculate steps required for generating pixels 
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); 
  
    // calculate increment in x & y for each steps 
    float Xinc = dx / (float) steps; 
    float Yinc = dy / (float) steps; 
  
    // Put pixel for each step 
    float X = X0; 
    float Y = Y0; 
    for (int i = 0; i <= steps; i++) 
    { 
       

        mlx_pixel_put(mlx_ptr, win_ptr, X, Y, 0xFF0000);
        X += Xinc;           // increment in x at each step 
        Y += Yinc;           // increment in y at each step 
         // for visualization of line- 
                             // generation step by step 
    } 
} 
 
int deal_key(int key, void *param)
{
    x = 50;
    y = 50;
    k = 0;
    int i = 0;
    int j = 0;
    remaind = 50;
    ft_morba3(line);

    int X_player2;
    int Y_player2;
    int moveStep;



    DDA(X_player, Y_player,  X_player  +  150  *  cos(rotationAngle + M_PI / 8) , Y_player +  150 * sin(rotationAngle + M_PI / 8));
    DDA(X_player, Y_player,  X_player  +  150  *  cos(rotationAngle - M_PI / 8) , Y_player +  150 * sin(rotationAngle - M_PI / 8));
    X_player2 = X_player  +  10  *  cos(rotationAngle );
    Y_player2 = Y_player +  10 * sin(rotationAngle);
    if(key == 125)
    {
        //Y_player = Y_player + 1;
    
    }
    if (key == 126)
    {
        //Y_player = Y_player - 1;
        X_player += cos(rotationAngle) * 5;
        Y_player += sin(rotationAngle) * 5;
       

    }
    if (key == 123)
    {
         rotationAngle -= rad(rotationSpeed);
    }
    if (key == 124)
    {
         rotationAngle += rad(rotationSpeed);
    }
    printf("%f\n",rotationAngle );
    return 0;
}

char  **fd_tab(int fd)
{
    line = malloc(sizeof(char *) * 6);
    while(get_next_line(fd,&line[y_len]))
        y_len++;
    line[y_len + 1] = NULL;
    return (line);
}

int main()
{
    int i = 0;
    int j = 0;
    x = 50;
    y = 50;
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 1000, 1000,"mlx 42");
    int fd = open("map.txt", O_RDONLY);
    line = fd_tab(fd);
    ft_morba3(line);
    mlx_key_hook(win_ptr, deal_key, (void *)0);
   // ft_morba3(x,y,fd);
   // mlx_key_hook(win_ptr, deal_key, (void *)0);
   mlx_loop(mlx_ptr);
}