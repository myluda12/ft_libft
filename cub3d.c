/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayajrhou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 21:57:55 by ayajrhou          #+#    #+#             */
/*   Updated: 2019/10/31 22:14:02 by ayajrhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>


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
//wall
int wall = 50;
// Player movement
int X_player;
int Y_player;   
int radian = 3;
float rotationAngle = - (M_PI / 2);
float rotationSpeed = 6;
int len_angle = 30;
float turnDirection = 0;
int walkDirection = 0;
int j;
float rotation;

float rot;
//Remainding the old position of X && Y Player
int Y_remainder;
int X_remainder;
//Ray Intersaction && steps
 float xintercept;
 float yintercept;

 float ystep;
 float xstep;

 float nextHoriX;
 float nextHoriY;
 //check if wall is hited
 float wallHoriHit;
 float wallVertHit;
 float HorizwallHitX;
 float HorizwallHitY;
 float VertwallHitX;
 float VertwallHitY;

 float WallHitX;
 float WallHitY;
// Ray Direction 
int rayFacingDown;
int rayFacingUp;
int rayFacingRight;
int rayFacingLeft;

// Distance between Vertical && Horizontal
float HorzHitDistance;
float VertHitDistance;
float distance;
float wasHitVertical;

//key UP / DOWN
int up;
int down;
int left;
int right;
//Rendering 3D MAP
float distanceProjectionPlan;
float wallStripHeight;
float WallStripWidth = 1;

//The Raycasting variables
//float isRaydown = ;



/* int len_y(int y,int fd)
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
       // mlx_pixel_put(mlx_ptr, win_ptr, k, y, color);
        k++;
        if (k == x)
        {
            k = save;
            y = y - 1;
            if (y == remaind - wall - 1)
            {
                k+=wall;
                break;
            }
           
        } 
    }
    if (line[j][i] == 'N' && none == 1)
    {
      //  mlx_pixel_put(mlx_ptr, win_ptr, k, y, 0x000000);
        X_player = k;
        Y_player = y;
        none++;
    }
    y = y_copy;
    x = x + wall;
    return k;
}


void ft_morba3(char **line)
{
    int i;
    unsigned int color;

   
    i = 0;
    j = 0;
    while(line[j][i])
    {
        if (line[j][i] == '1')
        {
            color = 0x6f665d;
            design_morba3(i, color, line, j);
        }
        else if(line[j][i] == '0' || line[j][i] == 'N')
        {
            color = 0xFFFFFF;
            design_morba3(i, color, line, j);
        }
        i++;
        if (line[j][i] == '\0')
        {
            i = 0;
            if (line[j + 1] != NULL)
            {
                j++;
                y = y + wall;
                x = wall;
                remaind = remaind + wall;
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
       
        if(X >= 0 && X <= 650 && Y >= 0 && Y <= 300)
          //  mlx_pixel_put(mlx_ptr, win_ptr, X, Y, 0xFF0000);
        X += Xinc;           // increment in x at each step 
        Y += Yinc;           // increment in y at each step 
         // for visualization of line- 
                             // generation step by step 
    } 
} 

int wall_checker()
{
    int X_pos;
    int Y_pos;

    X_pos = nextHoriX / wall;
    Y_pos = nextHoriY / wall;
    //printf("\n|==>|'%c'||\n",line[Y_pos][X_pos]);
    if ((X_pos >= 0 &&  X_pos < 13) && (Y_pos >= 0 &&  Y_pos < 6))
    {
        if (line[Y_pos][X_pos] == '1')
        {
            return (1);
        }
    }
    return 0;

}
 int wall_collision()
{
    int X_pos;
    int Y_pos;

    X_pos = X_remainder / wall;
    Y_pos = Y_remainder / wall;
   // printf("\n|==>|'%c'||\n",line[Y_pos][X_pos]);
    if (line[Y_pos][X_pos] == '1')
    {
        return (1);
    }
    return 0;

}

float ft_normalize_angle(float angle)
{
    while (angle > 2 * M_PI)
        angle -= 2 * M_PI;
    if (angle < 0)
    {
        angle += (2 * M_PI);
    }
    return (angle);
}

void render_colomn(int i)
{
    int start;
    int j;
    start = (1000 / 2) - (wallStripHeight / 2);
    if (start < 0)
        start = 0;
    j = start;
    while(j < start + wallStripHeight && j < 1000)
    {
        mlx_pixel_put(mlx_ptr,win_ptr,i,j,0x006400);
        j++;
    }

}
void render_map3D(int i)
{

        distanceProjectionPlan = (1000 / 2) / tan(rad(45) / 2);
        wallStripHeight = (50 / distance) * distanceProjectionPlan;

        render_colomn(i);
}
int ray_Direction()
{
    rayFacingDown = 0;
    rayFacingUp = 0;
    rayFacingRight = 0;
    rayFacingLeft = 0;

    rayFacingDown = (deg(rotation) > 0 && deg(rotation) < 180) ? 1 : 0;
    rayFacingUp = !(rayFacingDown) ? 1 : 0;

    rayFacingRight = ((deg(rotation) > 0 && (deg(rotation) < 90)) || (deg(rotation) > 270 && (deg(rotation) < 360))) ? 1 : 0;
    rayFacingLeft = !(rayFacingRight) ? 1 : 0;
    // printf("%d\n",rayFacingUp);
     //printf("%f\n",deg(rotation));

}
float Distance_between_HorVer(int x1,int y1, int x2, int y2)
{
    return sqrtf(powf((x2 - x1),2) + powf((y2 - y1),2));
}

int ft_cast_ray()
{
    WallHitX = 0;
    WallHitY = 0;
    distance = 0;

    int i = 0;
    int check;
    wallHoriHit = 0;
    ray_Direction();

    yintercept = (int)(Y_player / wall) * wall;
    yintercept += rayFacingDown ? wall : 0;
    xintercept = X_player + (yintercept - Y_player) / tan(rotation);

    ystep = wall;
    ystep *= rayFacingUp ? -1 : 1;

    // ==> 
    xstep = ystep / tan(rotation);
    // ==>
    //xstep *= (rayFacingLeft && xstep > 0) ? -1 : 1;
    //xstep *= (rayFacingRight && xstep < 0) ? -1 : 1;

    nextHoriX = xintercept;
    nextHoriY = yintercept;

    if(rayFacingUp)
        nextHoriY--;
        //increment x & y step until we find  a wall
    while(nextHoriX >= 0 && nextHoriX < 650 && nextHoriY >= 0 && nextHoriY < 300)
    {
        check = wall_checker();
        if (check == 1)
        {
            wallHoriHit = 1;
            HorizwallHitX = nextHoriX;
            HorizwallHitY = nextHoriY;
            //DDA(X_player, Y_player,  HorizwallHitX, HorizwallHitY);
            break;
        }
        else
        {
            nextHoriX += xstep;
            nextHoriY += ystep; 
        }
        
    }
    // VERITICAL RAYCAST

    wallVertHit = 0;
    ray_Direction();
    xintercept = (int)(X_player / wall) * wall;
    xintercept += rayFacingRight ? wall : 0;
    yintercept = Y_player - (X_player - xintercept) * tan(rotation);

    xstep = wall;
    xstep *= rayFacingLeft ? -1 : 1;
    // ==>
    ystep = xstep * tan(rotation);
    // == <
    //ystep *= (rayFacingUp && ystep > 0) ? -1 : 1;
    //ystep *= (rayFacingDown && ystep < 0) ? -1 : 1;

    nextHoriX = xintercept;
    nextHoriY = yintercept;

    if(rayFacingLeft)
        nextHoriX--;

    while(nextHoriX >= 0 && nextHoriX < 650 && nextHoriY >= 0 && nextHoriY < 300)
    {
        check = wall_checker();
        if (check == 1)
        {
            wallVertHit = 1;
            VertwallHitX = nextHoriX;
            VertwallHitY = nextHoriY;
          //  DDA(X_player, Y_player,  HorizwallHitX, HorizwallHitY);
            break;
        }
        else
        {
            nextHoriX += xstep;
            nextHoriY += ystep; 
        }
    }

    // The Distance between vert and horizontal distances and precist the smallest value

    HorzHitDistance = (wallHoriHit) ? Distance_between_HorVer(X_player , Y_player, HorizwallHitX,HorizwallHitY) : MAX_INT;
    VertHitDistance = (wallVertHit) ? Distance_between_HorVer(X_player , Y_player, VertwallHitX,VertwallHitY) : MAX_INT;
// store the smallest of the distances

    WallHitX = (HorzHitDistance) < (VertHitDistance) ? HorizwallHitX : VertwallHitX;
    WallHitY = (HorzHitDistance) < (VertHitDistance) ? HorizwallHitY : VertwallHitY;
    distance = (HorzHitDistance) < (VertHitDistance) ? HorzHitDistance : VertHitDistance;
    wasHitVertical = (VertHitDistance) < (HorzHitDistance);

    DDA(X_player,Y_player,WallHitX,WallHitY); 
 
}

int mlx_key_press(int key)
{
    if(key == 123)
        left = 1;
    if (key == 124)
        right = 1;
    if (key == 125)
        down = 1;
    if (key == 126)
        up = 1;
    return 0;
}
int key_release(int key)
{
    if(key == 123)
        left = 0;
    if(key == 124)
        right = 0;
    if (key == 125)
        down = 0;
    if (key == 126)
        up = 0;
    return 0;
}

int deal_key(void)
{
    int p = 0;
    x = wall;
    y = wall;
    k = 0;
    int i = 0;
    int j = 0;
    int ray_lenght;
    remaind = wall;
    ft_morba3(line);
    mlx_clear_window(mlx_ptr,win_ptr);
    rotation = rotationAngle - M_PI / 8;
    rot = rad(45) / 1000;

    if (rotationAngle > 2 * M_PI || rotationAngle < 0)
            rotationAngle = ft_normalize_angle(rotationAngle);
   // printf("rotationAngle :|%f|\n",deg(rotationAngle));
    while(i < 1000)
    {
        if (rotation > 2 * M_PI || rotation < 0)
            rotation = ft_normalize_angle(rotation);
        //DDA(X_player, Y_player,  wallHitX, wallHitY);
       ft_cast_ray();
        rotation += rot;
        render_map3D(i);
        i++;
      //  printf("Only Rotation |%f|\n",deg(rotation));
     //   printf("rotationAngle :|%f|\n",deg(rotationAngle));
    }  
    //DDA(X_player, Y_player,  X_player  +  150  *  cos(rotationAngle - M_PI / 8) , Y_player +  150 * sin//(rotationAngle - M_PI / 8));
    if(down == 1)
    {
        X_remainder = X_player;
        Y_remainder = Y_player;
        X_remainder -= cos(rotationAngle) * 5;
        Y_remainder -= sin(rotationAngle) * 5;
        p = wall_collision();
        if (p != 1)
        {
            X_player -= cos(rotationAngle) * 5;
            Y_player -= sin(rotationAngle) * 5;
        }
        // printf("%f",deg(rotation));
    }
    if (up == 1)
    {
        X_remainder = X_player;
        Y_remainder = Y_player;
        X_remainder += cos(rotationAngle) * 5;
        Y_remainder += sin(rotationAngle) * 5;
         p = wall_collision();
        if (p != 1)
        {
            X_player += cos(rotationAngle) * 5;
            Y_player += sin(rotationAngle) * 5;
        }
    }
    if (left == 1)
    {
         rotationAngle -= rad(rotationSpeed);
    }
    if (right == 1)
    {
         rotationAngle += rad(rotationSpeed);
    }
    /*printf("x = |%d| \ny = |%d|",X_player,Y_player);
    printf("\n====> X_remainder : ||%d||\n",X_remainder);
    printf("\n====> Y_remainder : ||%d||\n",Y_remainder);
    //printf("%f\n",rotationAngle );*/
   // rotation = ft_normalize_angle(rotation);
    return 0;
}

int loop_key()
{
    mlx_hook(win_ptr,2,0,mlx_key_press,0);
    mlx_hook(win_ptr,3,0,key_release,0);
    deal_key();
    return 0;
}

char  **fd_tab(int fd)
{
    line = malloc(sizeof(char *) * 7);
    while(get_next_line(fd,&line[y_len]))
        y_len++;
    line[y_len + 1] = NULL;
    return (line);
}
int main()
{
    int i = 0;
    int j = 0;

    //printf("ayoub")
    x = wall;
    y = wall;
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, 1000, 1000,"mlx 42");
    int fd = open("map.txt", O_RDONLY);
    line = fd_tab(fd);
    ft_morba3(line);

    rotation = rotationAngle - M_PI / 8;
    rot = rad(45) / 1000;
    while(i < 1000)
    {
        if (rotation > 2 * M_PI || rotation < 0)
            rotation = ft_normalize_angle(rotation);
        //DDA(X_player, Y_player,  wallHitX, wallHitY);
       ft_cast_ray();
        rotation += rot;
        i++;
      //  printf("Only Rotation |%f|\n",deg(rotation));
     //   printf("rotationAngle :|%f|\n",deg(rotationAngle));


    } 
    mlx_loop_hook(mlx_ptr,loop_key,0);

   // mlx_key_hook(win_ptr, deal_key, (void *)0);
   // ft_morba3(x,y,fd);
   // mlx_key_hook(win_ptr, deal_key, (void *)0);
   mlx_loop(mlx_ptr);
}