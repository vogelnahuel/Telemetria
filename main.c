#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
/**4000 tamanio de registro total **/
/** short  tomo de a 2 bytes*/
/** 2354-2355 donde tengo que buscar */
/** registro 1177 de datos*/


/********************************************SABER SI ES LITTLE  O BIG ENDIAN  PARTE D**************************/
int isLittleEndian(void){

    int16_t i = 1;
    int8_t *p = (int8_t *) &i;

    return (*p == 1);
}
/*********************************************************************************************************************************/


int main()
{
    if(isLittleEndian()){
        printf("Es little");
    }else{
        printf("Es big");
    }

    float gain = 0.01873128;
    float offset = -38.682956;

    char linea[4000];

    int dato;
    FILE *pf,*pf1,*pf2;

    pf=fopen("HKTMST.bin","rb");
    if(pf==NULL)
    {
        printf("Error no se abrio");
        return -1;
    }

    pf1=fopen("datos_para_graficar.txt","wt");
    if(pf1==NULL)
    {
       printf("Error no se creo");
        return -2;
    }

    pf2=fopen("datos_para_graficar.txt","r+t");
    if(pf2==NULL)
    {
       printf("Error no se abrio");
        return -3;
    }
    /************************************** PARTE   A **********************************************************/

    fseek(pf,0l,SEEK_END);
    dato=ftell(pf);
    dato=dato%4000;
    printf(" 0-es divisible por 4000 \n!=0  no es divisible por 4000 los bytes del archivo ----> el resultado es :%d\n",dato);
    fseek(pf,0l,SEEK_SET);/** DEVUELTA AL PRINCIPIO*/

    /*********************************************************************************************/





/*** COMO SE QUE EL DATO ESTA EN LOS BYTES 2354-2355 ENTONCES SI AGARRO DE A 2 BYTES EL DATO ESTA EN 1177 DE CADA REGISTRO***/

    float dato2;
    char * s,*s1,aux;
    fread(linea,sizeof(linea),1,pf);
    while(!feof(pf))
    {

        short* x =(short*)&linea[2354];
        s=&linea[2355];
        s1=&linea[2354];
        /** intercambio*/
        aux=*s;
        *s=*s1;
        *s1=aux;
        /***/
        //dar vuelta

        dato2=*x*gain+offset;
        printf("%f\n",dato2);
        fprintf(pf2,"%f\n",dato2);
    fread(linea,sizeof(linea),1,pf);
    }



    return 0;
}
