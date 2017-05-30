#include<stdlib.h>

#include<stdio.h>

#include<time.h>




typedef struct tabl

{

    double num;

    unsigned int time;

} tab;




void quicksort(tab *mas,int low, int high);



int main(int argc,char *argv[])

{

    int i,j,imin,imax;

    unsigned long int length=0,datemin,datemax;

    double Tstart,Tend,T,number=1.0;

    char c;

    FILE *f;

    tab *mas;

    struct tm m_time;

    time_t convert;



    if (argc>1)

    {

        f = fopen(argv[1],"rb");

        if (f==0)

        {

            printf("Enter correct file name\n");

            return 1;

        }

    }

    else

    {

        printf("No file name entered\n");

        return 2;

    }




    c=fgetc(f);

    while (c!=EOF)

    {

        if (c=='\n') ++length;

        c=fgetc(f);

    }




    mas=(tab*)malloc(length*sizeof(tab));




    fseek(f,0,SEEK_SET);




    for (i=0; i<length; i++)

    {

        fscanf(f,"%lf,%u\n",&mas[i].num,&mas[i].time);

    }


    Tstart=clock();

    quicksort(mas,0,length-1);

    Tend=clock();

    T=(Tend-Tstart)/(double)CLOCKS_PER_SEC;



    for (i=0; i<length; i++) {

        convert = mas[i].time;

        printf("%.9lf,%s\n",mas[i].num,ctime(&convert));

    }






    if (T!=0) printf("quicksort time:  %.3lf sec\n",T);

    else printf("quicksort time: <0.001 sec\n");




    m_time.tm_sec = 0; m_time.tm_min = 0; m_time.tm_hour = 0;

    m_time.tm_mday = 1; m_time.tm_mon = 0; m_time.tm_year = 80;

    datemin=mktime(&m_time);




    m_time.tm_sec = 0; m_time.tm_min = 0; m_time.tm_hour = 0;

    m_time.tm_mday = 31; m_time.tm_mon = 11; m_time.tm_year = 84;

    datemax=mktime(&m_time);



    for(i=0;i<length;i++)

        if (mas[i].time>datemin)

            {

                imin=i;

                break;

            }




    for(i=0;i<length;i++)

        if (mas[i].time<datemax)

            imax=i;

        else break;




    for (i=imin;i<imax;i++) if (mas[i].num<number) number=mas[i].num;



    printf("The smallest number between 01.01.1980 and 31.121984 is %.9lf\n",number);



    //I?enoea ianneaa no?oeoo?

    free(mas);

    return 0;

}




void quicksort(tab *mas, int low, int high)

{

    int l=low,r=high;

    static int i,sred,min,max;

    tab temp;

    min=l;

    max=r;

    for (i=l; i<r; ++i)

    {

        if (mas[i].time > mas[max].time) max=i;

        if (mas[i].time < mas[min].time) min=i;

    }

    sred=(mas[max].time + mas[min].time)/2;

    while (l <= r)

    {

        while (mas[l].time < sred)

        {

            ++l;

        }

        while (mas[r].time > sred)

        {

            --r;

        }

        if (l <= r)

        {

            temp=mas[l];

            mas[l]=mas[r];

            mas[r]=temp;

            --r;

            ++l;

        }

    }

    if (low < r)

        quicksort(mas,low,r);

    if (high > l)

        quicksort(mas,l,high);

}
