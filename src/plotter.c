#include <gtk/gtk.h>
#include <cairo/cairo.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "install_option.h"
#include "math1.h"
#include "stringutils.h"
#include "function.h"
#include "extvar.h"
#include "plotter.h"

int x, y;
//drawable functions
function f, g, h;
GtkBuilder *builder;
//draw area
GtkWidget *plot;
//activity log area
GtkTextBuffer *buffer;
//points of f, g and h
double **f_array, **g_array, **h_array;
//convolution's points
double *convolution;
//strings representing f, g and h
string fs, gs, hs;
//useful parameters
int par, conv;
//used for animating
clock_t t1, t2;
//fps counter
int fps;
//fps label
GtkLabel *speed;
//speed label's text
char *speed_lab;

void on_convol_clicked (GtkButton *button, gpointer   user_data) {
	conv = 1;
	convol();
}

void on_window_destroy (GtkWidget *widget, gpointer user_data) {
	gtk_main_quit ();
}

void print(char *c) {
	gtk_text_buffer_insert_at_cursor(buffer, c, length(c));
}

void ComputeFunction(function f, double** arr) {
	par = 0;
	int i;
	double incr, val;
	incr = (2*x)/840.0;
	val = -x;
	double k = 644.0/(2*y);
	int m = 26+fs.len+10;
	char *c = (char *) calloc(m, sizeof(char));
	sprintf(c, "calculating %s from -%d to %d...",  fs.str, x, x);
	print(c);
	free(c);
	if (!f->animated) {
		for (i = 0; i < 840; i++) {
			arr[0][i] = -k*Compute(f, val, 0);
			val += incr;
		}
	}
	else {
		int j;
		double param = -x;
		for (i = 0; i < 840; i++) {
			for (j = 0; j < 840; j++) {
				arr[i][j] = -k*Compute(f, val, param);
				val += incr;
			}
			val = -x;
			param += incr;
		}
	}
	print(" done!\n");
}

void on_done4_clicked (GtkButton *button, gpointer   user_data) {
	GtkWidget *box;
	box = GTK_WIDGET (gtk_builder_get_object (builder, "y_axis"));
	char *a = (char *) gtk_entry_get_text(GTK_ENTRY(box));
	y = (int) valueOf(new_string(a));
	ComputeFunction(f, f_array);
	ComputeFunction(g, g_array);
	ComputeFunction(h, h_array);
	gtk_widget_queue_draw_area (plot, 0, 0, 850, 650);
}

void on_done5_clicked (GtkButton *button, gpointer   user_data) {
	GtkWidget *box;
	box = GTK_WIDGET (gtk_builder_get_object (builder, "x_axis"));
	char *a = (char *) gtk_entry_get_text(GTK_ENTRY(box));
	x = (int) valueOf(new_string(a));
	ComputeFunction(f, f_array);
	ComputeFunction(g, g_array);
	ComputeFunction(h, h_array);
	gtk_widget_queue_draw_area (plot, 0, 0, 850, 650);
}

string done_clicked(char *a, function func, double** array) {
	string s = new_string(a);

	free_function(func);
	f = new_function(s);
	ComputeFunction(func, array);
	if (f->animated && !conv) {
		for (par = 0; par < 840; par++) {
			t1 = clock();
			gtk_widget_queue_draw_area (plot, 0, 0, 850, 650);
			while (gtk_events_pending() == TRUE) {
				gtk_main_iteration_do(TRUE);
			}
			par++;
			t2 = clock();
			while ((difftime(t2, t1) / CLOCKS_PER_SEC) < 1.0/fps) {
				t2 = clock();
			}
		}
		par = 839;
		gtk_widget_queue_draw_area (plot, 0, 0, 850, 650);
	}
	else {
		gtk_widget_queue_draw_area (plot, 0, 0, 850, 650);
	}

	return s;
}

void on_done1_clicked (GtkButton *button, gpointer   user_data) {
	conv = 0;
	GtkWidget *box;
	box = GTK_WIDGET (gtk_builder_get_object (builder, "f"));
	char *a = (char *) gtk_entry_get_text(GTK_ENTRY(box));

	fs = done_clicked(a, f, f_array);
}

void on_done2_clicked (GtkButton *button, gpointer   user_data) {
	conv = 0;
	GtkWidget *box;
	box = GTK_WIDGET (gtk_builder_get_object (builder, "g"));
	char *a = (char *) gtk_entry_get_text(GTK_ENTRY(box));

	gs = done_clicked(a, g, g_array);
}

void on_done3_clicked (GtkButton *button, gpointer   user_data) {
	conv = 0;
	GtkWidget *box;
	box = GTK_WIDGET (gtk_builder_get_object (builder, "h"));
	char *a = (char *) gtk_entry_get_text(GTK_ENTRY(box));

	hs = done_clicked(a, h, h_array);
}

void on_speed_up_clicked (GtkButton *button, gpointer   user_data) {
	fps+=10;
	refresh_speed();
}

void on_speed_down_clicked (GtkButton *button, gpointer   user_data) {
	fps-=10;
	refresh_speed();
}

void axes(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
	cairo_set_source_rgb (cr, 255, 255, 255);
	cairo_rectangle (cr, 0, 0, 850, 650);
	cairo_fill(cr);

	cairo_set_source_rgba (cr, 0, 0, 0, 0.3);
	int i, j;
	int c = 0, d = 0;
	for (i = 0; i < 20; i++) {
		cairo_move_to(cr, c, 0);
		cairo_line_to(cr, c, 644);
		c+=42;
	}

	for (j = 0; j <	14; j++) {
		cairo_move_to(cr, 0, d);
		cairo_line_to(cr, 840, d);
		d+=46;
	}

	cairo_set_line_width(cr, 1);
	cairo_stroke (cr);

	cairo_set_source_rgba (cr, 0, 0, 0, 0.1);
	c = 21;
	d = 23;
	for (i = 0; i < 20; i++) {
		cairo_move_to(cr, c, 0);
		cairo_line_to(cr, c, 650);
		c+=42;
	}

	for (j = 0; j <	14; j++) {
		cairo_move_to(cr, 0, d);
		cairo_line_to(cr, 850, d);
		d+=46;
	}

	cairo_set_line_width(cr, 1);
	cairo_stroke (cr);

	cairo_set_source_rgb (cr, 0, 0, 0);
	cairo_move_to (cr, 0, 322);
	cairo_line_to (cr, 840, 322);
	cairo_move_to (cr, 420, 0);
	cairo_line_to (cr, 420, 645);

	cairo_set_line_width (cr, 2);
	cairo_stroke (cr);
}

gboolean draw (GtkWidget *widget, cairo_t *cr, gpointer user_data) {
	double k = 644.0/(2*y);
	axes(widget, cr, user_data);
	int i;

	if (!conv) {
		for (i = 1; i < 840; i++) {
			cairo_set_source_rgb (cr, 1, 0, 0);
			if (f->animated) {
				if (par < 840 && !isnan(f_array[par][i-1]) && !isnan(f_array[par][i]) && f_array[par][i-1]/k<=y*1000 && f_array[par][i]/k<=y*1000 && f_array[par][i-1]/k>=-y*1000 && f_array[par][i]/k>=-y*1000) {
					cairo_move_to (cr, i-1, (f_array[par][i-1])+322);
					cairo_line_to (cr, i, (f_array[par][i])+322);
				}
			}
			else {
				if (!isnan(f_array[0][i-1]) && !isnan(f_array[0][i]) && f_array[0][i-1]/k<=y*1000 && f_array[0][i]/k<=y*1000 && f_array[0][i-1]/k>=-y*1000 && f_array[0][i]/k>=-y*1000) {
					cairo_move_to (cr, i-1, (f_array[0][i-1])+322);
					cairo_line_to (cr, i, (f_array[0][i])+322);
				}
			}

			cairo_set_line_width (cr, 2);
			cairo_stroke (cr);

			cairo_set_source_rgb (cr, 0, 1, 0);
			if (g->animated) {
				if (!isnan(g_array[par][i]) && !isnan(g_array[par][i-1]) && g_array[par][i-1]/k<=y*1000 && g_array[par][i]/k<=y*1000 && g_array[par][i-1]/k>=-y*1000 && g_array[par][i]/k>=-y*1000) {
					cairo_move_to (cr, i-1, (g_array[par][i-1])+322);
					cairo_line_to (cr, i, (g_array[par][i])+322);
				}
			}
			else {
				if (!isnan(g_array[0][i]) && !isnan(g_array[0][i-1]) && g_array[0][i-1]/k<=y*1000 && g_array[0][i]/k<=y*1000 && g_array[0][i-1]/k>=-y*1000 && g_array[0][i]/k>=-y*1000) {
					cairo_move_to (cr, i-1, (g_array[0][i-1])+322);
					cairo_line_to (cr, i, (g_array[0][i])+322);
				}
			}
			cairo_set_line_width (cr, 2);
			cairo_stroke (cr);

			cairo_set_source_rgb (cr, 0, 0, 1);
			if (h->animated) {
				if (!isnan(h_array[par][i]) && !isnan(h_array[par][i-1]) && h_array[par][i-1]/k<=y*1000 && h_array[par][i]/k<=y*1000 && h_array[par][i-1]/k>=-y*1000 && h_array[par][i]/k>=-y*1000) {
					cairo_move_to (cr, i-1, (h_array[par][i-1])+322);
					cairo_line_to (cr, i, (h_array[par][i])+322);
				}
			}
			else {
				if (!isnan(h_array[0][i]) && !isnan(h_array[0][i-1]) && h_array[0][i-1]/k<=y*1000 && h_array[0][i]/k<=y*1000 && h_array[0][i-1]/k>=-y*1000 && h_array[0][i]/k>=-y*1000) {
					cairo_move_to (cr, i-1, (h_array[0][i-1])+322);
					cairo_line_to (cr, i, (h_array[0][i])+322);
				}
			}
			cairo_set_line_width (cr, 2);
			cairo_stroke (cr);
		}
	}
	else {
		if (par > 0) {
			for (i = 1; i < 840; i++) {
				cairo_set_source_rgb (cr, 1, 0, 0);
				if (par < 840 && !isnan(f_array[par][i-1]) && !isnan(f_array[par][i]) && f_array[par][i-1]/k<=y*1000 && f_array[par][i]/k<=y*1000 && f_array[par][i-1]/k>=-y*1000 && f_array[par][i]/k>=-y*1000) {
					cairo_move_to (cr, i-1, (f_array[par][i-1])+322);
					cairo_line_to (cr, i, (f_array[par][i])+322);
				}

				cairo_set_line_width (cr, 2);
				cairo_stroke (cr);

				cairo_set_source_rgb (cr, 0, 1, 0);

				if (!isnan(g_array[0][i]) && !isnan(g_array[0][i-1]) && g_array[0][i-1]/k<=y*1000 && g_array[0][i]/k<=y*1000 && g_array[0][i-1]/k>=-y*1000 && g_array[0][i]/k>=-y*1000) {
					cairo_move_to (cr, i-1, (g_array[0][i-1])+322);
					cairo_line_to (cr, i, (g_array[0][i])+322);
				}

				cairo_set_line_width (cr, 2);
				cairo_stroke (cr);

				cairo_set_source_rgb (cr, 0, 0, 1);
				cairo_set_line_width (cr, 2);
				if (i <= par) {
					cairo_move_to (cr, i-1, (convolution[i-1])+322);
					cairo_line_to (cr, i, (convolution[i])+322);
				}

				cairo_stroke (cr);
			}
		}
	}

	return TRUE;
}

void convol() {
	GtkWidget *box;
	int i;
	double incr;

	//RESETTING PARAMETER
	par = 0;

	/*READING F FROM TEXT BOX AND PREPARING IT FOR A CONVOLUTION
	(REPLACING EVERY X WITH (-X+A)*/
	box = GTK_WIDGET (gtk_builder_get_object (builder, "f"));
	fs = prepare_for_convolution(fs);
	fs = clean(fs);

	gtk_entry_set_text(GTK_ENTRY(box), fs.str);
	f = new_function(fs);
	ComputeFunction(f, f_array);

	incr = (2*x)/840.0;

	//CALCULATING CONVOLUTION FUNCTION
	for (i = 0; i < 840; i++) {
		convolution[i] = -integral(f_array[i], g_array[0], incr);
	}

	//ANIMATION
	for (par = 0; par < 840; par++) {
		t1 = clock();
		gtk_widget_queue_draw_area (plot, 0, 0, 850, 650);
		while (gtk_events_pending() == TRUE) {
			gtk_main_iteration_do(TRUE);
		}
		t2 = clock();
		while ((difftime(t2, t1) / CLOCKS_PER_SEC) < 1.0/fps) {
			t2 = clock();
		}
	}
	par = 839;

	//LAST FRAME
	gtk_widget_queue_draw_area (plot, 0, 0, 850, 650);
	conv = 0;
}

void refresh_speed() {
	reset(speed_lab, 32);
	sprintf(speed_lab, "Speed: %d fps", fps);
	gtk_label_set_text(speed, speed_lab);
}

int main (int argc, char *argv[]) {
	int i;

	fps = 120;
	conv = 0;
	par = 0;
	x = 10;
	y = 7;

	//ALLOCATING RESOURCES
	speed_lab = (char *) malloc(32);
	convolution = (double *) malloc(840*sizeof(double));
	f_array = (double **) malloc(840*sizeof(double *));
	g_array = (double **) malloc(840*sizeof(double *));
	h_array = (double **) malloc(840*sizeof(double *));

	for (i = 0; i < 840; i++) {
		f_array[i] = (double *) malloc(840*sizeof(double));
		g_array[i] = (double *) malloc(840*sizeof(double));
		h_array[i] = (double *) malloc(840*sizeof(double));
	}

	//GENERATING FIRST FUNCTIONS ("0")
	string arg = new_string("0");
	fs = new_string(arg.str);
	hs = new_string(arg.str);
	gs = new_string(arg.str);
	f = new_function(arg);
	g = new_function(arg);
	h = new_function(arg);
	ComputeFunction(f, f_array);
	ComputeFunction(g, g_array);
	ComputeFunction(h, h_array);

	//BUILDING INTERFACE
  GtkWidget *window;
  gtk_init (&argc, &argv);

  builder = gtk_builder_new ();
  gtk_builder_add_from_file (builder, get_glade_path(), NULL);

	speed = GTK_LABEL(GTK_WIDGET (gtk_builder_get_object (builder, "fps")));
	refresh_speed();
	window = GTK_WIDGET (gtk_builder_get_object (builder, "window"));
	plot = GTK_WIDGET (gtk_builder_get_object (builder, "plot"));
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(gtk_builder_get_object (builder, "log")));
	gtk_builder_connect_signals (builder, NULL);

  gtk_widget_show_all (window);

	//STARTING GTK LOOP
  gtk_main ();

  return 0;
}
