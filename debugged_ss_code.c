/*As promised to some in the class this is a  completely debugged version of sajid sirs code that we have been studying for a week now .
I have only cleaned it up and added the view function partially 
this code runs smoothly and will not cause any error if u add new functions
>>>>NOTE: I have added an about section in each part of the code that explains it(atleast i hope it does).Go through it and u most probably will understand the entire code and if u still have any doubts feel free to ask me .Honestly this code can and will make u cry  .·´¯`(>▂<)´¯`·. 


Shoutout to A.Nowshehri and Shaheer Shah for helping out and cancerous tea to make this possible
*/
/*implemented a timer on this */
#include<time.h>
#include<stdio.h>
#include<string.h>
/*I have removed conio.h coz it does not work on my linux
->to use getch again just remove the comments here and replace scanf with getch 
  as in the original code.
*/
//#include<conio.h>
/*timer pointer*/
struct tm* time_ptr; 
/*these are the only universal variables in the code*/
int no_cust=0,no_items=0,no_orders=0;
/*s
t           ABOUT:  This is a struct of the name Customer,
r           ->it contains an int var and 5 arrays of varying lengths.
u
c
t 
C
U
S
T
O
M
E
R*/
typedef struct C{
        int C_ID;
        char name[20];
        char address[30];
        long int mobile;
        char email[30];
    }Customer;
/*
i               ABOUT: this struct named Item has 4 int and 2 char arrays.
t               
e
m*/
    typedef struct I{
        int I_ID;
        char name[20];
        char description[100];
        int category;
        int rate;
        int quantity;
    }Item;
/*O

R               ABOUT : the order struct has 4 int ,1 long and a one Item struct 
D
E
R
*/
    typedef struct O{
        int O_ID;
        int C_ID;
        Item itm[10];
        int no_items;
        //int items[10];
        int total;
        long int time;
        int status;
    }Order;
/*F
U
N 
C
T
I
O
N
D
E
C
L
A
R
A
TI
ON*/
Customer add_customer();
Item add_item();    
Order place_order();
void display_items(Item [],int);
void display_customer(int);
void copy_item(Item *, Item);
/*added 24-4-25 display_order()*/
void display_order(int);
int get_total(Item [], int);
int read_itm_file(char []);
int read_cust_file(char []);
/*
s
t
r
u           ABOUT:Here we are declaring the universal cust ,items and orders structs.
c           ->however declaring them as arrays limits the maximum numver of these things we can
t               have.Like we can have a max of 10 items .
d
e
cl
a
r
at
i
o
n*/
Customer custs[30];
Item items[10];
Order orders[50];
/*
M
A
I
N
*/  
void main(){
    /*time_t is a predefined function in time_t*/
    time_t te;
    /*the no_cust and no_items are integers from above(check top),they get int values from 
    read cust file and read itm file respecitvely .
    -> how this basically works is that read_cust_file which is decalared below reads the files
    of the name the fucntion here gives (since they take values of char arrays(see declaration))
     and then return integer values that are stored here.
     ->read the declaration in those function to undestand this.
     */
    no_cust = read_cust_file("Customers.txt");
    no_items = read_itm_file("Items.txt");
    /*
    this is basicallly done to say that the functions could find no file or no added values in
    them
    */
    if(no_cust > 0)
        printf("\nDetails of %d customers loaded\n",no_cust);
    if(no_items > 0)
        printf("\nDetails of %d items loaded\n",no_items);
    /*main 
                                 switch 
                                                            variable*/

    int o;                                                        
    while(1){
        printf("Select option:\n1.\tAdd Customer\n2.\tAdd Item\n3.\tPlace Order\n4.\tView\n");
        scanf("%d",&o);
        switch(o){
            case 1:
            /*here we are adding values to the already declared custs[] array above*/
                custs[no_cust++] = add_customer();
                break;
            case 2:
            /*same as above but for items*/
                items[no_items++] = add_item();
                break;
            case 3:
            /*same as above but for orders*/
                orders[no_orders++] = place_order();
                break;
            case 4:{
                /*using a switch to select bw items customers and orders*/
                /*added 24-4-25*/
                printf("Select:\n1-Customers\n2-Items\n3-Orders");
                int sw_var;
                scanf("%d",&sw_var);
                switch(sw_var){
                    case 1:{
                        printf("%-5s %-5s %-5s %-5s %-5s","C_ID","NAME","ADDRESS","MOBILE","EMAIL");
                        for(int i = 0;i < no_cust;i++){
                            printf("%-5d %-5s %-5s %-5ld %-5s\n",custs[i].C_ID,custs[i].name,custs[i].address,custs[i].mobile,custs[i].email);
                        }
                        break;

                    }
                    case 2:{
                        for (int i = 0;i < no_items;i++){
                            printf("%-5d %-5s %-5s %-5d %-5d %-5d\n",items[i].I_ID, items[i].name, items[i].description, items[i].category, items[i].rate, items[i].quantity);
                        }
                        break;
                    }
                    case 3:
                        // Orders display case can be added here
                        break;
                }
                break;
            }
            default:
                printf("\nTry again\n");
        }
    }
}
/*
A   ABOUT:  This function basically adds new customers to the terminal (to cust[]) as well as.
D           to the file .
D           ->this function returns cst (which is of struct type Customer),basically it means
C           that all the details of customer we type in will be sent to the cust[] and printed
U           to the file "Customers.txt".
S
T
O
M
ER
*/
Customer add_customer(){
    /*this is a local file pointer used to append the file */
    FILE *cust_file;
    /*this is a local Customer type variable that we use to temporarily store data before 
    returning it to the main function
    */
    Customer cst;
    cust_file = fopen("Customers.txt", "a");


    printf("\nEnter customer details in the following format\n");
    printf("\n\tName\tAddress\tMobile\temail\n");
    scanf("%s %s %ld %s", cst.name, cst.address, &cst.mobile, cst.email);
    /*We are assigning the values fro C_ID using the universal no_cust variable(check top)*/
    cst.C_ID = no_cust;
    /*function to print to file*/
    fprintf(cust_file, "%d %s %s %ld %s\n",cst.C_ID, cst.name, cst.address, cst.mobile, cst.email);
    fclose(cust_file);
    return cst;
}
/*
D
I   ABOUT:this function takes an int parameter that it uses to identify the index of the cust we
        we want to display.
S       ->this function of type void so it doesnt return anything.
P
L       ->int cid is a  local variable which is assigned the value whenever the function is called.
A
Y
*/
void display_customer(int cid){
    Customer c = custs[cid];
    printf("\n\tName\tAddress\tMobile\temail\n");
    printf("\n%s %s %ld %s\n", c.name, c.address, c.mobile, c.email);
}
/*
A
D
D       ABOUT: This fucntion uses the same mechanism as add customer and returns values both into the 
        universal items[] and prints into file "Items.txt"
 
 I
 T
 E
 M
 */
Item add_item(){
    Item i;
    FILE *itm_file;
    itm_file = fopen("Items.txt", "a");
    printf("\nEnter item details in the following format\n");
    printf("\n\tName\tDescription\tCategory\tRate\tQuantity\n");
    scanf("%s %s %d %d %d", i.name, i.description, &i.category, &i.rate, &i.quantity);
    i.I_ID = no_items;
    fprintf(itm_file, "%d %s %s %d %d %d\n",i.I_ID, i.name, i.description, i.category, i.rate, i.quantity);
    fclose(itm_file);
    return i;
}
/*
D
i
s
p

l       ABOUT: this function is used to display single items .It takes an Item type array and an int 
a           it then copies them to lst[] and count to then run a loop of length count and display the items
y
i
t
e
m
s
*/
void display_items(Item lst[],int count){
    printf("\nSNo.\tName\tDescription\tCategory\tRate\tQuantity\n");
    for(int i = 0; i < count;i++){
        printf("\n\t%d\t%s\t%s\t%d\t%d\t%d\n", i+1, lst[i].name, lst[i].description, lst[i].category, lst[i].rate, lst[i].quantity);
    }
}
/*
P
L               ABOUT: This function creates and returns an Order struct after collecting
A               item details from the user.
C               ->It uses the universal items[] array to display available items
E               ->The user can add multiple items to their order before checkout
_
O               ->The function calculates the total bill amount automatically
R               ->It displays the order summary before returning the Order struct
D
E
R
*/
Order place_order(){
    Order O;
    int id, Q,count=0;
    printf("\nEnter Customer ID to Proceed\n");
    scanf("%d",&O.C_ID);
    O.C_ID-=1;
    O.O_ID = no_orders++;
    while(1){
        printf("Select option:\n1.\tAdd Item\n2.\tCancel\n3.\tCheckout\n");
        char o = getchar();
        switch(o){
            case '1':
                display_items(items, no_items);
                printf("\nSelect item and quantity\n");
                scanf("%d %d", &id, &Q);
                puts("response recorded");
                copy_item(&O.itm[count], items[id-1]);
                puts("item added");
                O.itm[count].quantity = Q;
                //printf("number of items = %d", )
                O.total = get_total(O.itm,count+1);
                puts("total modified");
                count++;
                O.no_items = count;
                break;
            case '2':
                break;
            case '3':
                printf("\nDear:\n");
                display_customer(O.C_ID);
                printf("\nYour Order Details are:\n");
                display_items(O.itm,O.no_items);
                printf("\nYour total bill is: %d\n",O.total);
                //printf("%d", O.total);
                break;
            default:
                printf("\nTry again\n");
        }
        if(o=='3')
            break;
    }


    //printf("\nEnter item details in the following format\n");
    //printf("\n\tName\tDescription\tCategory\tRate\tQuantity\n");
    //scanf("%s %s %d %d %d", &i.name, &i.description, &i.category, &i.rate, &i.quantity);
    O.O_ID = no_orders;
    return O;
}
/*
C
O               ABOUT: This function copies contents from one Item struct to another,
P               ->it takes pointer to destination and source Item as parameters
                ->It handles both integer values and string arrays carefully
Y             ->  used when adding items to an order to create a separate copy
_               ->Presves all item details (ID, name, description, etc.)
I               
T               ->Doesn't return anything
                ->this funciton direcly modifies destinations.
E               
                ps:this shit was causing all the major run problems 
M
*/
void copy_item(Item *dst, Item src){

    /*since all the data of the items selceted is being already copied in this file i am going to use this to print to file as well*/
    dst->I_ID = src.I_ID;
    strcpy(dst->name,src.name);
    dst->category = src.category;
    strcpy(dst->description,src.description);
    dst->rate = src.rate;
}
/*

d
i
s
p
l
a
y
_
o
r
d
e
r
*/

/*void display_order(){
    int id;
    printf("\nEnter the Order_ID to display\n");
    scanf("%d",&id);
    printf("\n\tN\tDescription\tCategory\tRate\tQuantity\n");
    printf("\n\t%d\t%s\t%s\t%d\t%d\n", items[id].I_ID, items[id].name, items[id].description, items[id].category, items[id].rate);
}*/
/*
g
e
t
_
t
o
t
a
l
*/
int get_total(Item itms[], int count2){
    int total = 0;

    for(int i = 0; i<count2; i++){
        total+=itms[i].quantity*itms[i].rate;
        //printf("item : %s\n", itms[i].name);
        //puts("Amount added to total");
    }
    return total;
}

/*

r
e
a
d
_       ABOUT: both the read cust file and read cust item use the same mechanism 
c       ->they take a string with the name of file as input 
u        ->it reads the file in read mode and then scans the contents before storing in the univesal 
s           cust[] and items[] respectfully.
t       ->>improtantly it returns a counter used for no_cust and no_items in main fucntion which if  
_           we were allowed could be used for dynamic memory allcation.
f

il
e*/
int read_cust_file(char f_name[20]){
    FILE *cf;
    int counter = 0;
    cf = fopen(f_name, "r");
    puts("Reading Customer File");
    if(cf==NULL){
        puts("No Customer file found: Kindly add details first");
        return 0;
    }
    else{
            while(fscanf(cf, "%d %s %s %ld %s",&custs[counter].C_ID, custs[counter].name, custs[counter].address, &custs[counter].mobile, custs[counter].email)!=EOF){
                counter++;
                //printf("\nRecord %d read\n",counter);
            }
            fclose(cf);
            return counter;
    }
}
/*
r
e
a
d

_
i
tm
_

f
i
l
e
*/
int read_itm_file(char f_name[20]){
    FILE *itf;
    int counter = 0;
    itf = fopen(f_name, "r");
    puts("Reading Items File");
    if(itf==NULL){
        puts("No Items file found: Kindly add details first");
        return 0;
    }
    else{
            while(fscanf(itf, "%d %s %s %d %d %d", &items[counter].I_ID, items[counter].name, items[counter].description, &items[counter].category, &items[counter].rate, &items[counter].quantity)!=EOF){
                counter++;
            }
            fclose(itf);
            return counter;
    }
}