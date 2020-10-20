#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct tran {
    char scrittura;
    char movimento;
    int statoFin;
    struct tran *next;
    };
struct mucca{
    char *nastro;
    int utilizzi;
    };
struct codaBfs{
    int stato;
    int puntina;
    int lunghezza;
    long int passi;
    struct mucca *nastroMucca;
    struct codaBfs *next;
    };
struct codaBfs *testa,*coda,*pop;
struct tran *aux;
struct tran ***v;
struct mucca *primaMucca;
int n,m,o,f=1,*acc,uno,U;
long int max;
char c;
char *primoNastro; //stringa iniziale per nastro TM
int AcquisizioneTran(){        //acquisizione transizioni TM
    int i=1,j=1,k=0,z ,q,x,t;
    char *tran,w,e,b;
    tran=malloc(50*sizeof(char));
    gets(tran);
    if(strcmp(tran,"tr")==0){
        v=malloc(sizeof(struct tran**));
        v[0]=NULL;
        while(1){
        gets(tran);
        if(strcmp(tran,"acc")==0){break;}
        sscanf(tran,"%d %c %c %c %d",&z,&b,&w,&e,&x);
        if(b>96){ /** a-z **/
            q=b-60;
            }
            else{
                if(b==95){ /** _ **/
                    q=36;
                    }
                    else{
                        if(b>64){  /** A-Z **/
                            q=b-55;
                            }
                            else if(b>47){  /** 0-9 **/
                                q=b-48;
                                }
                        }
                }
        if((z+1>i)||(x+1>i)){
            j=i;
            if(x>z){
                i=x+1;
            }else{i=z+1;}
            v=realloc(v,i*sizeof(struct tran**));
            for(k=j;k<i;k++){
                v[k]=NULL;
                }
        }
        if(v[z]==NULL){
        v[z]=malloc(63*sizeof(struct tran*));
        t=0;
        while(t<63){
            v[z][t]=NULL;
            t++;
            }
        }
        struct tran *newtr;
        newtr=malloc(sizeof(struct tran));
        newtr->scrittura=w;
        newtr->movimento=e;
        newtr->statoFin=x;
        newtr->next=v[z][q];
        v[z][q]=newtr;
        }
    }
    free(tran);
    return i;
    }
int AcquisizioneAcc(){         //acquisizione stati accettazione
    int i=0,t=1;
    char StatiAcc[7];
    acc=malloc(sizeof(int));
    while(t==1){
        gets(StatiAcc);
        if(strcmp(StatiAcc,"max")==0){break;}
        i=i+1;
        if(i>1){acc=realloc(acc,i*sizeof(int));}
        sscanf(StatiAcc,"%d",&acc[i-1]);
        }
  return i;
}
int CreazioneNastro(){
    int i=0,t=1;
    if(c==EOF){return 0;}
    while((c=='\r')||(c=='\n')){c=getchar();}
    while((c!='\n')&&(c!='\r')&&(c!=EOF)){
            i=i+1;
            if(i==1){primoNastro=malloc(sizeof(char));}
            else{primoNastro=realloc(primoNastro,(i+1)*sizeof(char));}
            primoNastro[i-1]=c;
            c=getchar();
            }
    primoNastro[i]='\0';
    return i;
 }
void TM_BFS(int l){
    int t=0;
    testa=NULL;
    coda=NULL;
    struct codaBfs *zero;
    zero=malloc(sizeof(struct codaBfs));
    zero->stato=0;
    zero->nastroMucca=primaMucca;
    zero->puntina=0;
    zero->lunghezza=l;
    zero->passi=max;
    zero->next=NULL;
    testa=zero;
    coda=zero;
    do{
        if(testa->passi==0){
                U=U+1;
                return;
                }
        if(v[testa->stato]==NULL){
            int i;
            for(i=0;i<m;i++){
                if(testa->stato==acc[i]){
                    uno=uno+1;
                    return;
                    }
                }
            }
            else{
        int v_colonna;
        if(testa->nastroMucca->nastro[testa->puntina]>96){//a-z
            v_colonna=testa->nastroMucca->nastro[testa->puntina]-60;
            }
            else{
                if(testa->nastroMucca->nastro[testa->puntina]==95){//_
                    v_colonna=36;
                    }
                    else{
                        if(testa->nastroMucca->nastro[testa->puntina]>64){//A-Z
                            v_colonna=testa->nastroMucca->nastro[testa->puntina]-55;
                            }
                            else if(testa->nastroMucca->nastro[testa->puntina]>47){//0-9
                                v_colonna=testa->nastroMucca->nastro[testa->puntina]-48;
                                }
                        }
                }
        if(v[testa->stato][v_colonna]!=NULL){
            for(aux=v[testa->stato][v_colonna];aux!=NULL;aux=aux->next){
              if(testa->nastroMucca->nastro[testa->puntina]==aux->scrittura){ /** CASO SENZA COPIA DEL NASTRO **/
                if(((testa->nastroMucca->nastro[testa->puntina]==aux->scrittura)&&(testa->stato==aux->statoFin)&&(aux->movimento=='S'))||((testa->nastroMucca->nastro[testa->puntina]=='_')&&(testa->puntina==((testa->lunghezza-50)/3)+49)&&(testa->stato==aux->statoFin)&&(aux->movimento=='L'))||((testa->nastroMucca->nastro[testa->puntina]=='_')&&(testa->puntina==testa->lunghezza-((testa->lunghezza-50)/3)-50)&&(testa->stato==aux->statoFin)&&(aux->movimento=='R'))){
                    U=U+1;
                    }
                     else{
                struct codaBfs *nuovo;
                nuovo=malloc(sizeof(struct codaBfs));
                nuovo->stato=aux->statoFin;
                nuovo->passi=(testa->passi)-1;
                nuovo->next=coda->next;
                coda->next=nuovo;
                coda=nuovo;
                if(aux->movimento=='L'){
                    if(testa->puntina==0){
                        nuovo->nastroMucca=malloc(sizeof(struct mucca));
                        nuovo->nastroMucca->utilizzi=1;
                        nuovo->nastroMucca->nastro=malloc(((testa->lunghezza)+(testa->lunghezza)/2+51)*sizeof(char));
                        memset(nuovo->nastroMucca->nastro,'_',(testa->lunghezza)/2+50);
                        memcpy(&(nuovo->nastroMucca->nastro[(testa->lunghezza)/2+50]),testa->nastroMucca->nastro,testa->lunghezza+1);
                        nuovo->puntina=(testa->lunghezza)/2+49;
                        nuovo->lunghezza=testa->lunghezza+(testa->lunghezza)/2+50;
                        }else{
                            nuovo->nastroMucca=testa->nastroMucca;
                            nuovo->nastroMucca->utilizzi=nuovo->nastroMucca->utilizzi+1;
                            nuovo->puntina=testa->puntina-1;
                            nuovo->lunghezza=testa->lunghezza;
                            }
                    }
                if(aux->movimento=='R'){
                    if(testa->puntina==testa->lunghezza-1){
                        nuovo->nastroMucca=malloc(sizeof(struct mucca));
                        nuovo->nastroMucca->utilizzi=1;
                        nuovo->nastroMucca->nastro=malloc(((testa->lunghezza)+(testa->lunghezza)/2+51)*sizeof(char));
                        memcpy(nuovo->nastroMucca->nastro,testa->nastroMucca->nastro,testa->lunghezza+1);
                        memset(&(nuovo->nastroMucca->nastro[testa->lunghezza]),'_',(testa->lunghezza)/2+50);
                        nuovo->nastroMucca->nastro[(testa->lunghezza)+(testa->lunghezza)/2+50]='\0';
                        nuovo->puntina=testa->puntina+1;
                        nuovo->lunghezza=testa->lunghezza+(testa->lunghezza)/2+50;
                        }else{
                            nuovo->nastroMucca=testa->nastroMucca;
                            nuovo->nastroMucca->utilizzi=nuovo->nastroMucca->utilizzi+1;
                            nuovo->puntina=testa->puntina+1;
                            nuovo->lunghezza=testa->lunghezza;
                            }
                    }
                 if(aux->movimento=='S'){
                    nuovo->nastroMucca=testa->nastroMucca;
                    nuovo->nastroMucca->utilizzi=nuovo->nastroMucca->utilizzi+1;
                    nuovo->puntina=testa->puntina;
                    nuovo->lunghezza=testa->lunghezza;
                    }
                    }
              }
              else{  /** CASO CON COPIA DEL NASTRO **/
                if(((testa->nastroMucca->nastro[testa->puntina]==aux->scrittura)&&(testa->stato==aux->statoFin)&&(aux->movimento=='S'))||((testa->nastroMucca->nastro[testa->puntina]=='_')&&(testa->puntina==((testa->lunghezza-50)/3)+49)&&(testa->stato==aux->statoFin)&&(aux->movimento=='L'))||((testa->nastroMucca->nastro[testa->puntina]=='_')&&(testa->puntina==testa->lunghezza-((testa->lunghezza-50)/3)-50)&&(testa->stato==aux->statoFin)&&(aux->movimento=='R'))){
                    U=U+1;
                    }
                else{
                struct codaBfs *nuovo;
                nuovo=malloc(sizeof(struct codaBfs));
                nuovo->stato=aux->statoFin;
                nuovo->passi=(testa->passi)-1;
                nuovo->next=coda->next;
                coda->next=nuovo;
                coda=nuovo;
                if(aux->movimento=='L'){
                    if(testa->puntina==0){
                        nuovo->nastroMucca=malloc(sizeof(struct mucca));
                        nuovo->nastroMucca->utilizzi=1;
                        nuovo->nastroMucca->nastro=malloc(((testa->lunghezza)+(testa->lunghezza)/2+51)*sizeof(char));
                        memset(nuovo->nastroMucca->nastro,'_',(testa->lunghezza)/2+50);
                        memcpy(&(nuovo->nastroMucca->nastro[(testa->lunghezza)/2+50]),testa->nastroMucca->nastro,testa->lunghezza+1);
                        nuovo->nastroMucca->nastro[(testa->lunghezza)/2+50]=aux->scrittura;
                        nuovo->puntina=(testa->lunghezza)/2+49;
                        nuovo->lunghezza=testa->lunghezza+(testa->lunghezza)/2+50;
                        }else{
                            nuovo->nastroMucca=malloc(sizeof(struct mucca));
                            nuovo->nastroMucca->utilizzi=1;
                            nuovo->nastroMucca->nastro=malloc(((testa->lunghezza)+1)*sizeof(char));
                            memcpy(nuovo->nastroMucca->nastro,testa->nastroMucca->nastro,testa->lunghezza+1);
                            nuovo->nastroMucca->nastro[testa->puntina]=aux->scrittura;
                            nuovo->puntina=testa->puntina-1;
                            nuovo->lunghezza=testa->lunghezza;
                            }
                    }
                if(aux->movimento=='R'){
                    if(testa->puntina==testa->lunghezza-1){
                        nuovo->nastroMucca=malloc(sizeof(struct mucca));
                        nuovo->nastroMucca->utilizzi=1;
                        nuovo->nastroMucca->nastro=malloc(((testa->lunghezza)+(testa->lunghezza)/2+51)*sizeof(char));
                        memcpy(nuovo->nastroMucca->nastro,testa->nastroMucca->nastro,testa->lunghezza);
                        memset(&(nuovo->nastroMucca->nastro[testa->lunghezza]),'_',(testa->lunghezza)/2+50);
                        nuovo->nastroMucca->nastro[(testa->lunghezza)+(testa->lunghezza)/2+50]='\0';
                        nuovo->nastroMucca->nastro[testa->puntina]=aux->scrittura;
                        nuovo->puntina=testa->puntina+1;
                        nuovo->lunghezza=testa->lunghezza+(testa->lunghezza)/2+50;
                        }else{
                            nuovo->nastroMucca=malloc(sizeof(struct mucca));
                            nuovo->nastroMucca->utilizzi=1;
                            nuovo->nastroMucca->nastro=malloc((testa->lunghezza+1)*sizeof(char));
                            memcpy(nuovo->nastroMucca->nastro,testa->nastroMucca->nastro,testa->lunghezza+1);
                            nuovo->nastroMucca->nastro[testa->puntina]=aux->scrittura;
                            nuovo->puntina=testa->puntina+1;
                            nuovo->lunghezza=testa->lunghezza;
                            }
                    }
                 if(aux->movimento=='S'){
                    nuovo->nastroMucca=malloc(sizeof(struct mucca));
                    nuovo->nastroMucca->utilizzi=1;
                    nuovo->nastroMucca->nastro=malloc((testa->lunghezza+1)*sizeof(char));
                    memcpy(nuovo->nastroMucca->nastro,testa->nastroMucca->nastro,testa->lunghezza+1);
                    nuovo->nastroMucca->nastro[testa->puntina]=aux->scrittura;
                    nuovo->puntina=testa->puntina;
                    nuovo->lunghezza=testa->lunghezza; /** QUA **/
                    }
                } /**/
                    }
                   }
            }
            }
            pop=testa;
            testa=testa->next;
            pop->nastroMucca->utilizzi=pop->nastroMucca->utilizzi-1;
            if(pop->nastroMucca->utilizzi==0){
                free(pop->nastroMucca->nastro);
                free(pop->nastroMucca);
                }
            free(pop);
        }while(testa!=NULL);
    }
int main(){
    n=AcquisizioneTran();
    m=AcquisizioneAcc();
    scanf("%ld",&max);
    char  *run;
    run=malloc(4*sizeof(char));
    gets(run);
    gets(run);
    free(run);
    c=getchar();
    while(1){
        o=CreazioneNastro();
        if(o==0){break;}
        primaMucca=malloc(sizeof(struct mucca));
        primaMucca->nastro=primoNastro;
        primaMucca->utilizzi=1;
        uno=0;
        U=0;
        TM_BFS(o);
        while(1){
            if(testa==NULL){break;}
            coda=testa;
            testa=testa->next;
            coda->nastroMucca->utilizzi=coda->nastroMucca->utilizzi-1;
            if(coda->nastroMucca->utilizzi==0){
                free(coda->nastroMucca->nastro);
                free(coda->nastroMucca);
                }
            free(coda);
            }
        if(uno>0){
            printf("1\n");
            }else{
                if(U>0){
                    printf("U\n");
                    }else{
                        printf("0\n");
                        }
                }
        }
    return 0;
    }
