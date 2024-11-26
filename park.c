#include<stdio.h>
#include<stdbool.h>
#include<string.h>

//macros needed
#define NAME 100
#define  VEHICLE_DB 100
#define SPACE_DB 50
#define TIME 10
#define DATE 15
#define VEH_NUM_LEN 20
#define MEM_TYPE 10
#define FREE 0
#define NOT_FREE 1

//structure of vehicles information
struct vehicle_info {
   char veh_num[VEH_NUM_LEN];
   char name[NAME];
   char arr_time[TIME];
   char arr_date[DATE];
   char dep_date[DATE];
   char dep_time[TIME];
   char arr_AMPM[3];
   char dep_AMPM[3];
   char membership[MEM_TYPE];
   int hours;
   int ID;
   int price;
   int occupied_num;
};

//structure for parking spaces
struct parking_space {
   int space_id;
   bool occupied_status;
   int revenue;
   int count;
};

//required functions prototypes
void initialise_space_db(struct parking_space records[]);
void initialise_vehicle_db(struct vehicle_info records[]);
void vehicle_registration(struct vehicle_info veh_db[], struct parking_space space_db[]);
void exiting_vehicle(struct vehicle_info veh_db[],struct parking_space space_db[]);
int calculate_space_id(char member[],struct parking_space space_db[]);
void membership_updation(struct vehicle_info records[],int i);
int payment_calculate(struct vehicle_info records[],struct parking_space records_s[],int i);

//function prototypes for sorting
void sortbyParking(struct vehicle_info records[]);
void sortbyAmount(struct vehicle_info records[]);
void sortbyOccupancy(struct parking_space records[]);
void sortbyRevenue(struct parking_space records[]);

//function prototypes for time calculation
int isLeapYear(int year);
int DaystoMonth(int month, int year);
int changeToMinutes(int day, int month, int year, int hour, int minute, char ampm[]);
void findDate(char date[], int result[3]);
void findTime(char time[], int result[2], char ampm[]);
int calculateTotalHours(struct vehicle_info records[],int i);

//###################### main function ###########################
int main()
{
   struct vehicle_info veh_db[VEHICLE_DB];
   struct parking_space space_db[SPACE_DB];

   initialise_space_db(space_db); //to initialise parking spaces database 
   initialise_vehicle_db(veh_db); //to initialise vehicle database

   int flag=1;
   while( flag ) {
   int choice;
   printf("Smart Parking Lot System\n");
   printf("1] Vehicle Registration\n");
   printf("2] Vehicle Exit\n");
   printf("3] Sorted list of vehicles based on number of parkings done\n");
   printf("4] Sorted list of vehicles based on parking amount paid\n");
   printf("5] Sorted list of parking spaces based on occupancy\n");
   printf("6] Sorted list of parking spaces based on maximum revenue generation\n");
   printf("Enter Any other number to Quit the process\n");
   printf("Enter the number of your choice :");
   if (scanf("%d", &choice) != 1) {
     printf("Invalid input! Please enter a valid number.\n");
     while(getchar() != '\n'); // Clear the input buffer
          continue;
        }

   switch (choice)//for user friendly environment
   {
   case 1:
      vehicle_registration(veh_db, space_db);
      break;
   case 2:
      exiting_vehicle(veh_db,space_db);
      break;
   case 3:
      sortbyParking(veh_db);
      break;
   case 4:
      sortbyAmount(veh_db);
      break;
   case 5:
      sortbyOccupancy(space_db);
      break;
   case 6:
      sortbyRevenue(space_db);
      break;              
   default:
      flag=0;
      break;
   }
 }   
   return 0;
}

//initialisation of parking space database 
void initialise_space_db(struct parking_space records[])
{
   for(int i=0;i<SPACE_DB;i++)
   {
      records[i].space_id=i+1;
      records[i].occupied_status=FREE;
      records[i].count=0;
      records[i].revenue=0;
   }
}

//initialise of vehicle database
void initialise_vehicle_db(struct vehicle_info records[])
{
   for(int i=0;i<VEHICLE_DB;i++)
   {
      records[i].veh_num[0]='\0';
      records[i].name[0]='\0';
      records[i].arr_time[0]='\0';
      records[i].dep_time[0]='\0';
      records[i].arr_date[0]='\0';
      records[i].dep_date[0]='\0';
      records[i].arr_AMPM[0]='\0';
      records[i].dep_AMPM[0]='\0';
      records[i].membership[0]='\0';
      records[i].hours = 0;
      records[i].ID = 0;
      records[i].price = 0;
      records[i].occupied_num = 0;
   }
}

//#########################  vehicle registration  ############################
void vehicle_registration(struct vehicle_info veh_db[], struct parking_space space_db[])
{
  int n,i ,flag=0;
  while (!flag) {
    printf("How many vehicles to be registered? "); 
    if (scanf("%d", &n) != 1) {
        printf("Invalid input! Please enter a valid number of vehicles.\n");
        while (getchar() != '\n'); // Clear the input buffer
    } else {
        flag = 1;  // Input is valid, exit the loop
    }
  }

   char vehicle[VEH_NUM_LEN],name_main[NAME],mem_ship[MEM_TYPE],arrival[TIME],departure[TIME];
   char arrival_date[DATE],departure_date[DATE],arrivalAMPM[3],departureAMPM[3];

   for(i=0;i<n;i++)
   {
      printf("enter vehicle number for vehicle %d in given format xxyyxxyyyy(x->letters in capital,y->numbers):\n",i+1);
      scanf("%s",vehicle);
      int found=0;

      //if vehicle is already registered
      int flag3=0;
      for(int j=0; (j<VEHICLE_DB) && (flag3==0) ; j++)
      {
         if(strcmp(veh_db[j].veh_num,vehicle)==0)
         {
            found=1;
            printf("vehicle is already registered\n");
            printf("Enter arrival date (dd-mm-yyyy): ");
            scanf("%10s", arrival_date);
            printf("Enter arrival time (HH:MM AM/PM): ");
            scanf("%s %s", arrival, arrivalAMPM);
            // printf("Enter departure date (dd-mm-yyyy): ");
            // scanf("%s", departure_date);
            // printf("Enter departure time (HH:MM AM/PM): ");
            // scanf("%s %s", departure, departureAMPM);

            strcpy(veh_db[j].arr_time, arrival);
            strcpy(veh_db[j].arr_date, arrival_date);
            strcpy(veh_db[j].arr_AMPM, arrivalAMPM);
            // strcpy(veh_db[j].dep_time, departure);
            // strcpy(veh_db[j].dep_date, departure_date);
            // strcpy(veh_db[j].dep_AMPM, departureAMPM);
            
            int parking_space_id=calculate_space_id(veh_db[j].membership,space_db);

            if(parking_space_id==-1)
            {
               printf("no free parking spaces are available\n");
               return;
            }
            veh_db[j].ID=parking_space_id+1; // Store the parking space ID
            printf("parking space %d has been assigned to vehicle %s\n",veh_db[j].ID,vehicle);
            //flag3=1;
         }
         flag3=1;
      }

      //if vehicle is new
      if(!found)
      {
         printf("New Registration\n");
         printf("owner name:");
         scanf("%s",name_main);
         printf("Enter arrival date (dd-mm-yyyy): ");
         scanf("%s", arrival_date);
         printf("Enter arrival time (HH:MM AM/PM): ");
         scanf("%s %s", arrival, arrivalAMPM);
         // printf("Enter departure date (dd-mm-yyyy): ");
         // scanf("%s", departure_date);
         // printf("Enter departure time (HH:MM AM/PM): ");
         // scanf("%s %s", departure, departureAMPM);

         //parking space allocation
         int parking_space_assign=-1,flag=0;
         for(int j=20;j<SPACE_DB && flag==0;j++)
         {
            if(space_db[j].occupied_status == FREE)
            {
               parking_space_assign=j;
               space_db[j].occupied_status = NOT_FREE;
               space_db[j].count++;
               flag=1;
            }
         }

         if(parking_space_assign==-1) 
            {
                printf("No free parking spaces available\n");
                return;
            }

         //inserting data in vehicle database
         int flag2=0;   
         for(int j=0;j<VEHICLE_DB && flag2==0;j++)
         {
            if(veh_db[j].veh_num[0]=='\0')
            {
               strcpy(veh_db[j].veh_num,vehicle);
               strcpy(veh_db[j].name,name_main);
               strcpy(veh_db[j].arr_time,arrival);
               strcpy(veh_db[j].arr_date,arrival_date);
               strcpy(veh_db[j].arr_AMPM, arrivalAMPM);
               // strcpy(veh_db[j].dep_time,departure);
               // strcpy(veh_db[j].dep_date,departure_date);
               // strcpy(veh_db[j].dep_AMPM, departureAMPM);
               strcpy(veh_db[j].membership,"none");
               veh_db[j].hours=0;
               veh_db[j].ID = parking_space_assign+1;
               veh_db[j].price = 0;
               veh_db[j].occupied_num += 1;
               flag2=1;
            }

         }
      }
   }

}

//#################### function for the operations done on leaving the parking lot####################
void exiting_vehicle(struct vehicle_info veh_db[],struct parking_space space_db[])
{
   char vehicle[VEH_NUM_LEN];
   char departure[TIME],departure_date[DATE],departureAMPM[3];
   
   printf("enter vehicle number in given format xxyyxxyyyy(x->letters in capital,y->numbers):\n");
   scanf("%s",vehicle);
   int found=0;
   for(int i=0;i<VEHICLE_DB;i++)
   {
      if(strcmp(veh_db[i].veh_num,vehicle)==0)
      {
         found=1;
         printf("Enter departure date (dd-mm-yyyy): ");
         scanf("%s", departure_date);
         printf("Enter departure time (HH:MM AM/PM): ");
         scanf("%s %s", departure, departureAMPM);
         strcpy(veh_db[i].dep_time, departure);
         strcpy(veh_db[i].dep_date, departure_date);
         strcpy(veh_db[i].dep_AMPM, departureAMPM);

         int totalHours = calculateTotalHours(veh_db,i);
         if (totalHours < 0) 
            totalHours = -totalHours;
         
         veh_db[i].hours += totalHours;

         membership_updation(veh_db,i);
         int revenue= payment_calculate(veh_db,space_db,i);
         veh_db[i].price=revenue;
         printf("total parking charge: %d rupess\n", revenue);
         printf("updated membership: %s\n", veh_db[i].membership);
      }
   }
   if(!found)//in case if vehicle is not found 
      printf("vehicle is not in database, Please register vehicle first.\n");
}

//##################### parking payment calculation and parking space revenue total calculator ######################
int payment_calculate(struct vehicle_info records[],struct parking_space records_s[],int i)
{
   int parking_hours=records[i].hours;
   int charges;

   if(parking_hours<=3)
      charges=100;
   else  
      charges=100+(parking_hours-3)*50;

   if( (strcmp(records[i].membership,"golden")==0) || (strcmp(records[i].membership,"premium")==0))
   {
      charges = charges *0.9;
   }

   int space_id=records[i].ID-1; 
   records_s[space_id].revenue += charges;

   return charges;   
}

//########################### membership updation ###############################
void membership_updation(struct vehicle_info records[],int i)
{  
   int parking_hours=records[i].hours;
   if (parking_hours >= 200)
    { // golden membership for 200+ hours
      strcpy(records[i].membership, "golden");  
    }
   else if (parking_hours >= 100)
   { // premium membership for 100+ hours
      strcpy(records[i].membership, "premium"); 
   }
   else
   { // no membership for < 100 hours
      strcpy(records[i].membership, "none"); 
   }

}

//###############function for allocating parking spaces on the basis of membership and allocation policy###############
int calculate_space_id(char member[],struct parking_space space_db[])
{
   int ans=-1,parking_space_assign=-1;
   int flag=0;
   if(strcmp(member,"golden")==0)
   {
      for(int h=0;h<50 && flag==0;h++)
      {
         if (space_db[h].occupied_status == FREE)
         {
            parking_space_assign = h;
            space_db[h].occupied_status = NOT_FREE;
            space_db[h].count++;
            ans=parking_space_assign;
            flag=1;
         }
      }
   }
   else if(strcmp(member,"premium")==0)
   {
      for(int h=10;h<50 && flag==0;h++)
      {
         if (space_db[h].occupied_status == FREE)
         {
            parking_space_assign = h;
            space_db[h].occupied_status = NOT_FREE;
            space_db[h].count++;
            ans=parking_space_assign;
            flag=1;
         }
      }
   }
   else
   {
      for(int h=0;h<50 && flag==0;h++)
      {
         if (space_db[h].occupied_status == FREE)
         {
            parking_space_assign = h;
            space_db[h].occupied_status = NOT_FREE;
            space_db[h].count++;
            ans=parking_space_assign;
            flag=1;
         }
      }
   }
   return ans;
}

//#################### starting of functions for total hours calculation#####################
int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
int DaystoMonth(int month, int year) {
    if (month == 2) {
        return isLeapYear(year) ? 29 : 28;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    return 31;
}
int changeToMinutes(int day, int month, int year, int hour, int minute, char ampm[]) {
    int totalMins = 0;
    for (int y = 0; y < year; y++) {
        totalMins += (isLeapYear(y) ? 366 : 365) * 1440;
    }
    for (int m = 1; m < month; m++) {
        totalMins += DaystoMonth(m, year) * 1440;
    }
    totalMins += (day - 1) * 1440;
    if (strcmp(ampm, "PM") == 0 && hour != 12) {
        hour += 12;
    } else if (strcmp(ampm, "AM") == 0 && hour == 12) {
        hour = 0;
    }
    totalMins += hour * 60 + minute;

    return totalMins;
}
void findDate(char date[], int result[3]) {
    result[0] = (date[0] - '0') * 10 + (date[1] - '0');
    result[1] = (date[3] - '0') * 10 + (date[4] - '0');
    result[2] = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + (date[8] - '0') * 10 + (date[9] - '0');
}

void findTime(char time[], int result[2], char ampm[]) {
    result[0] = (time[0] - '0') * 10 + (time[1] - '0');
    result[1] = (time[3] - '0') * 10 + (time[4] - '0');
    if (time[5] == 'P' && time[6] == 'M') {
        strcpy(ampm, "PM");
    } else {
        strcpy(ampm, "AM");
    }
}
int calculateTotalHours(struct vehicle_info records[],int i) {
    char arrivalDate[DATE], arrivalTime[TIME], arrivalAMPM[3];
    char departureDate[DATE], departureTime[TIME], departureAMPM[3];

    strcpy(arrivalDate, records[i].arr_date);
    strcpy(arrivalTime, records[i].arr_time);
    strcpy(arrivalAMPM, records[i].arr_AMPM);
    strcpy(departureDate, records[i].dep_date);
    strcpy(departureTime, records[i].dep_time);
    strcpy(departureAMPM, records[i].dep_AMPM);
    
    int arrival[3], arrivalT[2];
    int departure[3], departureT[2];
    char arrivalAMPMStr[3], departureAMPMStr[3];
    findDate(arrivalDate, arrival);
    findTime(arrivalTime, arrivalT, arrivalAMPMStr);
    findDate(departureDate, departure);
    findTime(departureTime, departureT, departureAMPMStr);

    int totalArrivalMinutes = changeToMinutes(arrival[0], arrival[1], arrival[2], arrivalT[0], arrivalT[1], arrivalAMPMStr);
    int totalDepartureMinutes = changeToMinutes(departure[0], departure[1], departure[2], departureT[0], departureT[1], departureAMPMStr);

    strcpy(arrivalAMPM, arrivalAMPMStr);
    strcpy(departureAMPM, departureAMPMStr);

    return (totalDepartureMinutes - totalArrivalMinutes) / 60;
} 
//######################## endiing of functions for total hours calculation ########################

// function for sorting the list of vehicles based on number of parkings done
void sortbyParking(struct vehicle_info records[])
{
    int i, j , flag=0;
    struct vehicle_info temp;
    for(i=0 ; (i<VEHICLE_DB-1) && (flag==0) ; i++)  {
       flag = 1;
        for( j=0; j<VEHICLE_DB-i-1 ; j++) {
            if( records[j].occupied_num < records[j+1].occupied_num) {
                temp = records[j];
                records[j] = records[j+1];
                records[j+1] = temp;
                flag = 0; 
            }
        }
    }
    printf("Sorted list of vehicles based on number of parkings :\n");
    for( i=0; i<VEHICLE_DB ; i++) {
        if(records[i].veh_num[0] != '\0') // Print only if vehicle exists
        {
            printf("Vehicle : %s, Parkings : %d\n", records[i].veh_num, records[i].occupied_num);
        }
    }
}

// function for sorting the list of vehicles based on parking amount paid
void sortbyAmount(struct vehicle_info records[]) 
{
    int i, j, flag=0;
    struct vehicle_info temp;
    for( i=0; (i<VEHICLE_DB-1) && (flag==0) ; i++)  {
        flag = 1;
        for( j=0; j<VEHICLE_DB-i-1 ; j++) {
            if( records[j].price < records[j+1].price) {
                temp = records[j];
                records[j] = records[j+1];
                records[j+1] = temp;
                flag = 0;
             }
         }
     }
    printf("Sorted list of vehicles based on parking amount paid :\n");
    for( i=0; i<VEHICLE_DB ; i++) {
        if(records[i].veh_num[0]!= '\0') // Print only if vehicle exists
       {
         printf("Vehicle Number: %s, Amount Paid: %d\n", records[i].veh_num, records[i].price);
      }
   }
}

// function for sorting the list of vehicles based on their occupancy
void sortbyOccupancy(struct parking_space records[]) {
    int i, j;
    struct parking_space temp;
    for ( i=1 ; i<SPACE_DB ; i++)
    {
        temp=records[i]; 
        j=i-1;
        while ( j>=0 && records[j].count < temp.count ) {
            records[j+1]=records[j];
            j=j-1;
        }
        records[j+1]=temp;  
    }
    printf("Sorted list of parking spaces based on occupancy:\n");
    for ( i=0 ; i<SPACE_DB ; i++)
    {
        printf("Parking Space ID: %d, Occupied Count: %d\n", records[i].space_id, records[i].count);
    }
}

// function for sorting the list of parking spaces based revenue
void sortbyRevenue(struct parking_space records[])
{
    int i, j ,flag=0;
    struct parking_space temp;

    for(i = 0; (i < SPACE_DB - 1) && (flag == 0); i++) { 
       flag =1;
        for(j = 0; j < SPACE_DB - i - 1; j++)
        {
            if(records[j].revenue < records[j+1].revenue)
            {
                temp = records[j];
                records[j] = records[j+1];
                records[j+1] = temp;
                flag = 0;
            }
        }
    }
    printf("Sorted list of parking spaces based on revenue:\n");
    for(i = 0; i < SPACE_DB; i++)
    {
        printf("Parking Space ID: %d, Revenue: %d\n", records[i].space_id, records[i].revenue);
    }
}

