#include <iostream>
#include <fstream>
#include <cmath>
#include <gtk/gtk.h>
#include <cstdlib>
#include <cstring>

#define Empty 0

using namespace std;
void initGUI(int*,char***);
bool solve(int arr[9][9]);
int a[9][9];
static GtkWidget* wid[9][9],*window;
void open_dialog();
static void menu_event(GtkWidget*,gpointer);
void no_Soln();
void init_matrix();



//void check_number(GtkWidget* entry,mypair* data);
bool chkIllegalEntries(int arr[9][9])
{

    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(arr[i][j]==-1)
            {
                return true;
            }
        }
    }
    return false;
}


bool isValid(int arr[9][9])
{

        if(chkIllegalEntries(arr))
            {
                cout<<"Illegal";
                return false;
            }
        bool r[9][9], c[9][9], s[3][3][9];
        memset(r, false, sizeof(r));
        memset(c, false, sizeof(c));
        memset(s, false, sizeof(s));
        int number;

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (arr[i][j] > 0 && arr[i][j] <=9) {

                    number = a[i][j]-1 ;
                    if (r[i][number]) return false;
                    r[i][number] = true;

                    if (c[j][number]) return false;
                    c[j][number] = true;

                    if (s[i / 3][j / 3][number]) return false;
                    s[i / 3][j / 3][number] = true;
                }
            }
        }
        return true;
}





static void get_elements(GtkWidget* widget,gpointer data)
{
        for(int i=0;i<9;i++)
        {
                for(int j=0;j<9;j++)
                {
                         const gchar* c=gtk_entry_get_text(GTK_ENTRY(wid[i][j]));
                        if(strlen(c)!=1)
                            a[i][j]=-1;
                        else if(strlen(c)==1&&!isdigit(c[0]))
                            a[i][j]=-1;
                        else if(strlen(c)==1)
                            a[i][j]=atoi(c);
                }
        cout << endl;
        }
        init_matrix();
        if(!isValid(a))
        {
                        GtkWidget* dialog,*label;
                        dialog=gtk_dialog_new_with_buttons("Error",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
                        label=gtk_label_new("The sudoku is invalid");
                        gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG( dialog ))),label,0,0,0);
                        gtk_widget_show_all(dialog);
                        gtk_dialog_run(GTK_DIALOG(dialog));
                        gtk_widget_destroy(dialog);
        }
        int x=solve(a);
        if(!x)
            no_Soln();
        else if(x==1)
        {
            for(int i=0;i<9;i++)
                {
                        for(int j=0;j<9;j++)
                        {
                                char c[2];
                                sprintf(c,"%d",a[i][j]);
                                gtk_entry_set_text(GTK_ENTRY(wid[i][j]),c);
                        }
                }
        }
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                cout<<a[i][j]<<" ";
            }
            cout<<endl;
        }
}




void init_matrix()
{
    for(int i=0;i<9;i++)
        {
                for(int j=0;j<9;j++)
                {
                        const gchar* c=gtk_entry_get_text(GTK_ENTRY(wid[i][j]));
                        //cout<<c<<" ";
                        if(strlen(c)!=1)
                        {
                            a[i][j]=-1;
                            cout<<"trigger1"<<endl;
                        }
                        else if(strlen(c)==1&&!isdigit(c[0]))
                        {
                            a[i][j]=-1;
                             cout<<"trigger2"<<endl;
                        }
                        else if(strlen(c)==1)
                            a[i][j]=atoi(c);
                }
        }

}


void widgetinsert(string s,int r)
{
    s+=" ";
    int words=0;
    string w="";
    int i=0;
    while(i!=s.length()&&words<9)
    {
        char x=s.at(i++);
        if(x!=' ')
            w+=x;
        else
        {
            gtk_entry_set_text(GTK_ENTRY(wid[r][words++]),w.c_str());
            w="";
        }
    }
}


void initGUI(int* argc,char*** argv)
{
        const char* file[] = {"New","Open","Check","Exit"};
        const char* help[] = {"About"};

        gtk_init(argc,argv);

        GtkWidget *vbox,*hbox,*separator,*button,*menu,*file_menu,*help_menu,*menu_bar;

        vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
        window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
        menu=gtk_menu_new();
        menu_bar=gtk_menu_bar_new();

        file_menu=gtk_menu_item_new_with_label("File");
        help_menu=gtk_menu_item_new_with_label("Help");

        for(int i=0;i<4;i++)
        {
                GtkWidget* menu_item=gtk_menu_item_new_with_label(file[i]);
                gtk_menu_shell_append(GTK_MENU_SHELL(menu),menu_item);
                g_signal_connect(menu_item,"activate",G_CALLBACK(menu_event),window);
        }

        gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_menu),menu);
        gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar),file_menu);
        menu=gtk_menu_new();

        for(int i=0;i<1;i++)
        {
                GtkWidget* menu_item=gtk_menu_item_new_with_label(help[i]);
                gtk_menu_shell_append(GTK_MENU_SHELL(menu),menu_item);
                g_signal_connect(menu_item,"activate",G_CALLBACK(menu_event),window);
        }

        gtk_menu_item_set_submenu(GTK_MENU_ITEM(help_menu),menu);
        gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar),help_menu);

        gtk_box_pack_start(GTK_BOX(vbox),menu_bar,0,0,0);


        for(int i=0;i<9;i++)
        {
                 hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
                for(int j=0;j<9;j++)
                {
                        wid[i][j]=gtk_entry_new();
                        //g_signal_connect(wid[i][j],"activate",G_CALLBACK(check_number),NULL);
                        gtk_entry_set_width_chars(GTK_ENTRY(wid[i][j]),1);
                        gtk_entry_set_max_length(GTK_ENTRY(wid[i][j]),1);
                        gtk_entry_set_text(GTK_ENTRY(wid[i][j]),"0");
                        gtk_widget_set_size_request(wid[i][j],50,50);
                        gtk_box_pack_start(GTK_BOX(hbox),wid[i][j],0,0,0);
                        if((j+1)%3==0)
                        {
                                separator=gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
                                gtk_box_pack_start(GTK_BOX(hbox),separator,0,0,0);
                        }
                }
                gtk_box_pack_start(GTK_BOX(vbox),hbox,0,0,0);
                if((i+1)%3==0)
                {
                        separator=gtk_separator_new(GTK_ORIENTATION_VERTICAL);
                        gtk_box_pack_start(GTK_BOX(vbox),separator,0,0,0);
                }
        }


        button=gtk_button_new_with_label("Solve the sudoku");
        g_signal_connect(button,"clicked",G_CALLBACK(get_elements),NULL);
        gtk_box_pack_start(GTK_BOX(vbox),button,0,0,0);

        g_signal_connect(window,"delete-event",G_CALLBACK(gtk_main_quit),NULL);/*These are boilerplate*/
        gtk_container_add(GTK_CONTAINER(window),vbox);
        gtk_widget_show_all(window);
        gtk_main();
}

bool FindEmptyLocation(int arr[9][9],int &row, int &col)
{
    for (row = 0; row < 9; row++)
        for (col = 0; col < 9; col++)
            if (arr[row][col] == Empty)
                return true;
    return false;
}
bool UsedInRow(int grid[9][9], int row, int num)
{
    for (int col = 0; col < 9; col++)
        if (grid[row][col] == num)
            return true;
    return false;
}


bool UsedInCol(int grid[9][9], int col, int num)
{
    for (int row = 0; row < 9; row++)
        if (grid[row][col] == num)
            return true;
    return false;
}


bool UsedInBox(int grid[9][9], int boxStartRow, int boxStartCol, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row+boxStartRow][col+boxStartCol] == num)
                return true;
    return false;
}


bool isSafe(int grid[9][9], int row, int col, int num)
{
    /* Check if 'num' is not already placed in current row,
       current column and current 3x3 box */
    return !UsedInRow(grid, row, num) &&
           !UsedInCol(grid, col, num) &&
           !UsedInBox(grid, row - row%3 , col - col%3, num);
}

bool FindUnassignedLocation(int arr[9][9],int &row, int &col)
{
    for (row = 0; row < 9; row++)
        for (col = 0; col < 9; col++)
            if (arr[row][col] == Empty)
                return true;
    return false;
}
bool solve(int grid[9][9])
{
    int row, col;

    // If there is no unassigned location, we are done
    if (!FindUnassignedLocation(grid, row, col))
       return true; // success!

    // consider digits 1 to 9
    for (int num = 1; num <= 9; num++)
    {
        // if looks promising
        if (isSafe(grid, row, col, num))
        {
            // make tentative assignment
            grid[row][col] = num;

            // return, if success, yay!
            if (solve(grid))
                return true;

            // failure, unmake & try again
            grid[row][col] = Empty;
        }
    }
    return false; // this triggers backtracking
}

void no_Soln()//attempted solving.no solution
{
        GtkWidget* dialog,*label;
        dialog=gtk_dialog_new_with_buttons("Error",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
        label=gtk_label_new("No solution exists");
        gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area( GTK_DIALOG( dialog ) )),label,0,0,0);
        gtk_widget_show_all(dialog);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
}


/*void check_number(GtkWidget* entry,mypair* data)//entry checking
{
        const gchar* c=gtk_entry_get_text(GTK_ENTRY(entry));
        if(!isdigit(c[0]))
        {
                GtkWidget* dialog,*label;
                dialog=gtk_dialog_new_with_buttons("Error",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
                label=gtk_label_new("This is not a number!");
                gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area( GTK_DIALOG( dialog ) )),label,0,0,0);
                gtk_widget_show_all(dialog);
                gtk_dialog_run(GTK_DIALOG(dialog));
                gtk_widget_destroy(dialog);
        }
}*/

bool bad_number(int i)//during file read
{
        if(!(i>=0 && i<10))
        {
                GtkWidget* dialog,*label;
                dialog=gtk_dialog_new_with_buttons("Error",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
                label=gtk_label_new("This number is bigger than 9 or less than 0\nOr maybe not event a number");
                gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area( GTK_DIALOG( dialog ) )),label,0,0,0);
                gtk_widget_show_all(dialog);
                gtk_dialog_run(GTK_DIALOG(dialog));
                gtk_widget_destroy(dialog);
                return 1;
        }
        return 0;
}


static void menu_event(GtkWidget* menu_item,gpointer data)
{
        if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)),"New")==0)
        {
                for(int i=0;i<9;i++)
                        for(int j=0;j<9;j++)
                        {
                                a[i][j]=0;
                                gtk_entry_set_text(GTK_ENTRY(wid[i][j]),"0");
                        }
        }

        else if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)),"Open")==0)
        {
                GtkWidget *dialog;
                dialog=gtk_file_chooser_dialog_new("Choose the sudoku file",GTK_WINDOW(data),GTK_FILE_CHOOSER_ACTION_OPEN,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
                gtk_widget_show_all(dialog);
                gint resp=gtk_dialog_run(GTK_DIALOG(dialog));
                if(resp==GTK_RESPONSE_OK)
                {
                        ifstream in(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
                        string str;
                        int c=0;
                        while(getline(in,str))
                        {
                            widgetinsert(str,c++);
                        }
                }
                gtk_widget_destroy(dialog);
        }
        else if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)),"Check")==0)
        {
                init_matrix();
                bool b=isValid(a);

                if(!b)
                {
                        GtkWidget* dialog,*label;
                        dialog=gtk_dialog_new_with_buttons("Error",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
                        label=gtk_label_new("The sudoku is invalid");
                        gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG( dialog ))),label,0,0,0);
                        gtk_widget_show_all(dialog);
                        gtk_dialog_run(GTK_DIALOG(dialog));
                        gtk_widget_destroy(dialog);
                }
                else
                {
                        GtkWidget* dialog,*label;
                        dialog=gtk_dialog_new_with_buttons("OKAY",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
                        label=gtk_label_new("The sudoku is valid.Though,this doesn't guarantee solvability.");
                        gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG( dialog ))),label,0,0,0);
                        gtk_widget_show_all(dialog);
                        gtk_dialog_run(GTK_DIALOG(dialog));
                        gtk_widget_destroy(dialog);
                }
        }
        else if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)),"About")==0)
        {
                        GtkWidget* dialog,*label;
                        dialog=gtk_dialog_new_with_buttons("Info!",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
                        label=gtk_label_new("SudokuSolver v1.0(Owner-n00body)");
                        gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG( dialog ))),label,0,0,0);
                        gtk_widget_show_all(dialog);
                        gtk_dialog_run(GTK_DIALOG(dialog));
                        gtk_widget_destroy(dialog);
        }
        else if(strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item)),"Exit")==0)
        {
                gtk_main_quit();
        }
}

int main(int argc,char* argv[])
{
        for(int i=0;i<9;i++)
                for(int j=0;j<9;j++)
                        a[i][j]=0;
        initGUI(&argc,&argv);
        return 0;
}
