#ifndef PLOTTERH_
#define PLOTTERH_

//INTERFACE FUNCTIONS
void on_convol_clicked (GtkButton *button, gpointer   user_data);
void on_window_destroy (GtkWidget *widget, gpointer user_data);
//resizes y_axis
void on_done4_clicked (GtkButton *button, gpointer   user_data);
//resizes x_axis
void on_done5_clicked (GtkButton *button, gpointer   user_data);
//reads a function (f(x)) from the text box
void on_done1_clicked (GtkButton *button, gpointer   user_data);
//reads a function (g(x)) from the text box
void on_done2_clicked (GtkButton *button, gpointer   user_data);
//reads a function (h(x)) from the text box
void on_done3_clicked (GtkButton *button, gpointer   user_data);
void on_speed_up_clicked (GtkButton *button, gpointer   user_data);
void on_speed_down_clicked (GtkButton *button, gpointer   user_data);


/**
*Makes a new function from a char array read from a text box
*@ret the function's string
*/
string done_clicked(char *a, function f, double** array);

/**
*Prints a string in the buffer
*/
void print(char *c);

/**
*They calculate every point of f, g and h
*/
void ComputeF();
void ComputeG();
void ComputeH();

/**
*Draws axes in draw area
*/
void axes(GtkWidget *widget, cairo_t *cr, gpointer user_data);

/**
*Draws functions in draw area
*/
gboolean draw (GtkWidget *widget, cairo_t *cr, gpointer user_data);

/**
*Makes a convolution between f and g
*/
void convol();

/**
*Refreshes fps label
*/
void refresh_speed();

#endif
