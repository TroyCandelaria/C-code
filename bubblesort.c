int main(){
        char students[10][50];
        int count = 0;
        char temp[50];
        while(scanf("%s",students[count]) != EOF){
                count++;
        }
        for(int i=0; i<count; i++){
                for(int j=0; j<count-1; j++){
                        if(strcmp(students[j],students[j+1]) > 0){
                                strcpy(temp, students[j]);
                                strcpy(students[j], students[j+1]);
                                strcpy(students[j+1], temp);
                        }
                }
        }
        for(int i=0; i<count; i++){
                printf("%s\n", students[i]);
        }
}