#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
int s_row,s_col;unsigned char data[100];int result[20];int total=0;
int reference2[95]={
212222,
222122,
222221,
121223,
121322,
131222,
122213,
122312,
132212,
221213,
221312,
231212,
112232,
122132,
122231,
113222,
123122,
123221,
223211,
221132,
221231,
213212,
223112,
312131,
311222,
321122,
321221,
312212,
322112,
322211,
212123,
212321,
232121,
111323,
131123,
131321,
112313,
132113,
132311,
211313,
231113,
231311,
112133,
112331,
132131,
113123,
113321,
133121,
313121,
211331,
231131,
213113,
213311,
213131,
311123,
311321,
331121,
312113,
312311,
332111,
314111,
221411,
431111,
111224,
111422,
121124,
121421,
141122,
141221,
112214,
112412,
122114,
122411,
142112,
142211,
241211,
221114,
413111,
241112,
134111,
111242,
121142,
121241,
114212,
124112,
124211,
411212,
421112,
421211,
212141,
214121,
412121,
111143,
111341,
131141
};
void code(){
    int j=0;
while(1){    
    for(int i=0;i<6;i++)
        result[j]+=data[j*6+i]*(pow(10,5-i));
    j++;
    if(data[6*(j+1)]==0){
        total=j;
        for(int k=0;k<j;k++){
            printf("%d ",result[k]);
        }
        break;}    
}
}
void decode(){
for(int i=1;i<total-2;i++){
    for(int j=0;j<95;j++){
        if(reference2[j]==result[i])
            printf("%c",j+32);
    }
}
}

void lmain(){    
    
    int width,height,channel;
    unsigned char *img = stbi_load("result.jpg",&width,&height,&channel,1);
    if(img==NULL){
        printf("File couldnt be loaded\n");
        exit(1);}
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            if(img[i*height+j]<100){
                s_row=i;
                s_col=j;
                break;}
            }
        break;        
    }
    memset(result,0,sizeof(int)*20);   
    
    int j=s_col,val_b=0,val_w=0;int count=0;
    while(1){
        
        if(img[s_row*height+j]<128){
            while(1){
                val_b++;                
                j++;
                if(img[s_row*height+j]>128)
                    break;
                
            }
        }
        data[count]=val_b;
        count++;val_b=0;
        if(img[s_row*height+j]>128){
            while(1){
                val_w++;
                j++;
                if(img[s_row*height+j]<128)
                    break;
            }
        }
        data[count]=val_w;
        count++;val_w=0;    
        if(j>width)
            break;    
    }
    int factor;
    for(int i=2;i<100;i++){
        if((data[0]%i)==0 && (data[1]%i)==0){
            factor=i;
            break;
        }
    }
    for(int i=0;i<width;i++)
        data[i]/=factor;
    printf("\nImage information:\n");     
    printf("Width=%dpx\t\tHeight=%dpx\t\tChannels=%d\n\n",width,height,channel);
    printf("\nThe numeric code is:\n");    
    code();
    printf("\n\nThe decoded text is:\n");
    decode();
    stbi_image_free(img);
}