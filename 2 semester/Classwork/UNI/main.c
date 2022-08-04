#include<stdio.h>
#define PI 3.14
#include <math.h>
#include <stdlib.h>
typedef enum  {
    red,
    green,
    blue,
}figure_color_t;

typedef struct
{
    float R;

}circle_t;
circle_t* p_circle;

typedef struct
{
    float width;
    float height;
}rectangle_t;
rectangle_t* p_rectangle;

typedef struct
{
    int quantity;
    float size;
}polygon_t;
polygon_t* p_polygon;

typedef enum  {
    CIRCLE,
    RECTANGLE,
    POLYGON,
}figure_type_t;

typedef struct {
    figure_type_t type;
    figure_color_t color;
    union {
        circle_t circle;
        rectangle_t rectangle;
        polygon_t polygon;
    }sizes;
}figure_t;

int main(void)
{

    FILE *file;
    file = fopen("uni_shapes.bin", "rb");

    if (file == NULL) {
        printf("Error opening file");
        return(1);
    }


    figure_t* figures;

    int c_count = 0;
    int r_count = 0;
    int p_count = 0;

    int red_count = 0;
    int green_count = 0;
    int blue_count = 0;

    float c_square = 0;
    float r_square = 0;
    float p_square = 0;
    float square = 0;

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    int num = 0;

    num = size / sizeof(figure_t);
    figures = (figure_t*)malloc((num+1) * sizeof(char));
    int i = 0;

    int j = 0;
    fseek(file, 0, SEEK_SET);

    while(!feof(file))
    {

        if (fread(figures, sizeof(char), sizeof(*figures) / sizeof(char), file) > 0)
        {
            if (figures[i].type == CIRCLE)
            {
                c_count++;
                c_square += PI * (double)(figures[i].sizes.circle.R) * (double)(figures[i].sizes.circle.R);

            }
            if (figures[i].type == RECTANGLE)
            {
                r_count++;
                r_square += (double)(figures[i].sizes.rectangle.width) * (double)(figures[i].sizes.rectangle.height);

            }
            if (figures[i].type == POLYGON)
            {
                p_count++;
                p_square += (double)(figures[i].sizes.polygon.quantity) * (double)(figures[i].sizes.polygon.size)* (double)(figures[i].sizes.polygon.size)*1/tan(PI/ (double)(figures[i].sizes.polygon.quantity))/4;

            }

            if (figures[i].color == red)
            {
                red_count++;
            }
            else
            if (figures[i].color == green)
            {
                green_count++;
            }
            else
            if (figures[i].color == blue)
            {
                blue_count++;
            }
        }

    }

    square = (c_square + r_square + p_square);
    printf("Number of figures:%d\n", num);
    printf("Circles:%d\n", c_count);
    printf("Rectangles:%d\n", r_count);
    printf("Polygons:%d\n", p_count);
    printf("Red figures:%d\n", red_count);
    printf("Green figures:%d\n", green_count);
    printf("Blue figures:%d\n", blue_count);
    printf("Square of all figures:%.2f\n", square);
    if (fclose(file)==EOF) {
        printf("Error closing file");
    }
    else {
        fclose(file);
    }

    //getch();
    return 0;
}
