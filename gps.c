#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Structure{
    char name[50];
    double time;
    double lat;
    double lon;
    double alt;
};

struct distances{
    char name[50];
    double distance;
};

//function protoypes
struct Structure scan_user(struct Structure user_t);
int scan_user_file();
void fill_users(int i);
void calcDist(int j);
struct distances searchClose(int j);
void calcDist(int j);

//declaring global variables
struct Structure user_t;
struct Structure our_user;
struct Structure other_users[15];
struct distances dist[15];

int main(void){
    
    char ans;
    char ans2 = 'y';
    int i = 0;


    printf("Do you have a file? Y/N\n");
    scanf("%c", &ans);

    if(ans == 'y'){
        i = scan_user_file(our_user);
    }else{
        our_user = scan_user(our_user);

        while(ans2 == 'y'){
            fill_users(i);

            i++;

            printf("Is there another user?\n");
            fflush(stdin);
            scanf("%c", &ans2);
        }

        
    }

    calcDist(i);

    struct distances closest = searchClose(i);

    printf("The closest user to ours is %s who is %lf meters away", closest.name, closest.distance);

}

struct Structure scan_user(struct Structure tmp_user){
    char name[50];

    printf("Please enter the name of the user\n");
    scanf("%s", name);
    strcpy(tmp_user.name, name);


    printf("Please enter the time\n");
    scanf("%lf", &tmp_user.time);

    printf("Please enter the latitude of the user\n");
    scanf("%lf", &tmp_user.lat);
    
    printf("Please enter the longitude of the user\n");
    scanf("%lf", &tmp_user.lon);

    printf("Please enter the altitude of the user\n");
    scanf("%lf", &tmp_user.alt);

    return tmp_user;
}

void fill_users(int i){
    double lat;
    double lon;
    double alt;
    double time;
    char name[50];

    printf("\n");
    user_t = scan_user(user_t);

            strcpy(other_users[i].name, user_t.name);
            other_users[i].time = user_t.time;
            other_users[i].lat = user_t.lat;
            other_users[i].lon = user_t.lon;
            other_users[i].alt = user_t.alt;
}

//one function fills all structs from file
int scan_user_file(){
    char fName [50];
    FILE *fp1;
    char line[5][15];
    int users;
    struct Structure user_t;
    char *ptr;
    char tmp;

    printf("Please enter the file name.\n");
    scanf("%s", fName);

    fp1 = fopen(fName, "r");

    if (fp1 == NULL)
    {
        printf("File is empty\n");
        exit(1);
    }

    fscanf (fp1, "%d", &users);
    fgetc(fp1);

    for(int i = 0; i <= 4; i++){
        fgets(line[i], 15, fp1);
        fflush(stdin);
    }

    strcpy(our_user.name, line[0]);
    our_user.time = strtod(line[1], &ptr);
    our_user.lat = strtod(line[2], &ptr);
    our_user.lon = strtod(line[3], &ptr);
    our_user.alt = strtod(line[4], &ptr);

    for(int i = 0; i < users; i++){
        for(int j = 0; j <= 4; j++){
            fgets(line[j], 15, fp1);
            fflush(stdin);
        }

        strcpy(other_users[i].name, line[0]);
        other_users[i].time = strtod(line[1], &ptr);
        other_users[i].lat = strtod(line[2], &ptr);
        other_users[i].lon = strtod(line[3], &ptr);
        other_users[i].alt = strtod(line[4], &ptr);
    }

    return users;

}

void calcDist(int j){
    double tmp;

    for(int i = 0; i < j; i++){
        tmp = pow(our_user.lat - other_users[i].lat, 2) + pow(our_user.lon - other_users[i].lon, 2) + pow(our_user.alt - other_users[i].alt, 2);
        tmp = sqrt(tmp);

        dist[i].distance = tmp;
        strcpy(dist[i].name, other_users[i].name);
    }
}

struct distances searchClose(int j){

    struct distances tmp;
    tmp.distance = dist[0].distance;
    strcpy(tmp.name, dist[0].name);

    for(int i = 0; i < j; i++){
        if(dist[i].distance < tmp.distance){
            tmp.distance = dist[i].distance;
            strcpy(tmp.name, dist[i].name);
        }
    }
    return tmp;
}