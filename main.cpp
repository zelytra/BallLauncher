#include "mbed.h"
#include <math.h>

//------------------------//
//       Projet E&R       //
//      Air Bouboule      //
//------------------------//
//  Par Alexandre Petit   //
//        S2 2019         //
//------------------------//
//  Programmer pour carte //
//    MBED NXP LPC1768    //
//------------------------//



//Initialisation des ports//

BusIn encodeur(p20,p19,p18,p17,p13,p14,p15,p16); //Encodeur
Serial pc(USBTX, USBRX);
Serial Automate(p9,p10);                         // tx, rx
DigitalOut direction_m (p28);                    //Direction Moteur Insertion balle
DigitalOut break_m (p29);                        //Break Moteur Insertion balle
DigitalOut direction_v (p24);                    //Direction Verin
DigitalOut break_v (p23);                        //Break Verin
PwmOut  pwm_m (p21);                             //PWM Moteur Insertion balle
PwmOut  pwm_v (p22);                             //PWM Verin
PwmOut  pwm_1 (p26);                             //PWM Moteur Lanceur

//------------------------//


int encodeur_int(); //Fonction de position de l'encodeur

int main()
{
    
// Init des variables //
    char chaine[100],chaine_serie[100];
    int i=0;

    float V_balle=0.0;
    float Angle=0.0;

    double enc=0.0;
    double erreur=0.0;
    double k=0.03;
//--------------------//

    //  Set des PWM   //
    pwm_1.period_us(50);
    pwm_v.period_us(50);
    pwm_m.period_us(50);
    //----------------//

//Initialisation des variables//
    break_v=0;
    direction_m=0;
    break_m=0;
    pwm_1.write(0);
//----------------------------//



    while(1) {
        enc= encodeur_int();
        //pc.printf("pos:%f angle:%f err:%f \r\n",enc,Angle,erreur); // Commande d'initialisation
        
        //----Traitement de la commande d'Angle---//
        enc= encodeur_int();
        erreur=(Angle-enc)*k;
        //pc.printf("     %f     ",enc );
        // Direction //
        if (erreur<0.0) {
            direction_v=0;
        } else if (erreur>=0.0) {
            direction_v=1;
        }        
        //-----------//
        //    PWM    //
        if (erreur >1.0) {
            erreur=1.0;
        } else if (erreur<-1.0) {
            erreur=-1.0;
        }     
        pwm_v.write(fabs(erreur));
        //-----------//

//----------- Entrée de variable dans la consol-----------//
        if(pc.readable()) {
            chaine[i]=pc.getc();
            pc.printf("%c",chaine[i]);

            if (chaine[i]=='!') {

                sscanf(chaine, "%f,%f!",&V_balle,&Angle);
                enc= encodeur_int();
                pc.printf("     %3.0f%%      %3.0f      %3.0f",V_balle,Angle,enc );

                i++;
                chaine[i]='\0';
                //pc.printf("\r\n%s",chaine);
                pc.printf("\r\n\r\n");
                wait(0.01);

                // Ecriture des variables dans le système //
                pwm_1.write(V_balle/100.0);
                //---------------------------------------//
                i=0;
            } else {
                i++;
            }           
//--------------------------------------------------------//
            wait(0.01);
        }
        //----------- Entrée de variable de l'Automate-----------//
        if(Automate.readable()) {
            chaine_serie[i]=Automate.getc();
            pc.printf("%c",chaine_serie[i]);

            if (chaine_serie[i]=='!') {  
                 sscanf(chaine_serie, "%f,%f!",&V_balle,&Angle);     
                       
                enc= encodeur_int();        
                i++;
                chaine_serie[i]='\0';
                //pc.printf("\r\n%s",chaine);
                pc.printf("\r\n\r\n");
                wait(0.02);
                // Ecriture des variables dans le système //
                pwm_1.write(V_balle/100.0);
                //---------------------------------------//
                i=0;
            } else {
                i++;
            }           
//--------------------------------------------------------//
            wait(0.01);
    }
}

}
// Bibliothèque de la carte encodeur//
int encodeur_int(){
    int codeur;
    double position=0.0,x=0.0,ratio=0.25;
    codeur=encodeur.read();

    switch(codeur) {
        case 127:
            position=0.0;
            break;
        case 63:
            position=1.0;
            break;
        case 62:
            position=2.0;
            break;
        case 58:
            position=3.0;
            break;
        case 56:
            position=4.0;
            break;
        case 184:
            position=5.0;
            break;
        case 152:
            position=6.0;
            break;
        case 24:
            position=7.0;
            break;
        case 8:
            position=8.0;
            break;
        case 72:
            position=9.0;
            break;
        case 73:
            position=10.0;
            break;
        case 77:
            position=11.0;
            break;
        case 79:
            position=12.0;
            break;
        case 15:
            position=13.0;
            break;
        case 47:
            position=14.0;
            break;
        case 175:
            position=15.0;
            break;
        case 191:
            position=16.0;
            break;
        case 159:
            position=17.0;
            break;
        case 31:
            position=18.0;
            break;
        case 29:
            position=19.0;
            break;
        case 28:
            position=20.0;
            break;
        case 92:
            position=21.0;
            break;
        case 76:
            position=22.0;
            break;
        case 12:
            position=23.0;
            break;
        case 4:
            position=24.0;
            break;
        case 36:
            position=25.0;
            break;
        case 164:
            position=26.0;
            break;
        case 166:
            position=27.0;
            break;
        case 167:
            position=28.0;
            break;
        case 135:
            position=29.0;
            break;
        case 151:
            position=30.0;
            break;
        case 215:
            position=31.0;
            break;
        case 223:
            position=32.0;
            break;
        case 207:
            position=33.0;
            break;
        case 143:
            position=34.0;
            break;
        case 142:
            position=35.0;
            break;
        case 14:
            position=36.0;
            break;
        case 46:
            position=37.0;
            break;
        case 38:
            position=38.0;
            break;
        case 6:
            position=39.0;
            break;
        case 2:
            position=40.0;
            break;
        case 18:
            position=41.0;
            break;
        case 82:
            position=42.0;
            break;
        case 83:
            position=43.0;
            break;
        case 211:
            position=44.0;
            break;
        case 195:
            position=45.0;
            break;
        case 203:
            position=46.0;
            break;
        case 235:
            position=47.0;
            break;
        case 239:
            position=48.0;
            break;
        case 231:
            position=49.0;
            break;
        case 199:
            position=50.0;
            break;
        case 71:
            position=51.0;
            break;
        case 7:
            position=52.0;
            break;
        case 23:
            position=53.0;
            break;
        case 19:
            position=54.0;
            break;
        case 3:
            position=55.00;
            break;
        case 1:
            position=56.0;
            break;
        case 9:
            position=57.0;
            break;
        case 41:
            position=58.0;
            break;
        case 169:
            position=59.0;
            break;
        case 233:
            position=60.0;
            break;
        case 225:
            position=61.0;
            break;
        case 229:
            position=62.0;
            break;
        case 245:
            position=63.0;
            break;
        case 247:
            position=64.0;
            break;
        case 243:
            position=65.0;
            break;
        case 227:
            position=66.0;
            break;
        case 163:
            position=67.0;
            break;
        case 131:
            position=68.0;
            break;
        case 139:
            position=69.0;
            break;
        case 137:
            position=70.0;
            break;
        case 129:
            position=71.0;
            break;
        case 128:
            position=72.0;
            break;
        case 132:
            position=73.0;
            break;
        case 148:
            position=74.0;
            break;
        case 212:
            position=75.0;
            break;
        case 244:
            position=76.0;
            break;
        case 240:
            position=77.0;
            break;
        case 242:
            position=78.0;
            break;
        case 250:
            position=79.0;
            break;
        case 251:
            position=80.0;
            break;
        case 249:
            position=81.0;
            break;
        case 241:
            position=82.0;
            break;
        case 209:
            position=83.0;
            break;
        case 193:
            position=84.0;
            break;
        case 197:
            position=85.0;
            break;
        case 196:
            position=86.0;
            break;
        case 192:
            position=87.0;
            break;
        case 64:
            position=88.0;
            break;
        case 66:
            position=89.0;
            break;
        case 74:
            position=90.0;
            break;
        case 106:
            position=91.0;
            break;
        case 122:
            position=92.0;
            break;
        case 120:
            position=93.0;
            break;
        case 121:
            position=94.0;
            break;
        case 125:
            position=95.0;
            break;
        case 253:
            position=96.0;
            break;
        case 252:
            position=97.00;
            break;
        case 248:
            position=98.0;
            break;
        case 232:
            position=99.0;
            break;
        case 224:
            position=100.0;
            break;
        case 226:
            position=101.0;
            break;
        case 98:
            position=102.0;
            break;
        case 96:
            position=103.0;
            break;
        case 32:
            position=104.0;
            break;
        case 33:
            position=105.0;
            break;
        case 37:
            position=106.0;
            break;
        case 53:
            position=107.0;
            break;
        case 61:
            position=108.00;
            break;
        case 60:
            position=109.0;
            break;
        case 188:
            position=110.0;
            break;
        case 190:
            position=111.0;
            break;
        case 254:
            position=112.0;
            break;
        case 126:
            position=113.0;
            break;
        case 124:
            position=114.0;
            break;
        case 116:
            position=115.0;
            break;
        case 112:
            position=116.0;
            break;
        case 113:
            position=117.0;
            break;
        case 49:
            position=118.0;
            break;
        case 48:
            position=119.0;
            break;
        case 16:
            position=120.0;
            break;
        case 144:
            position=121.0;
            break;
        case 146:
            position=122.0;
            break;
        case 154:
            position=123.0;
            break;
        case 158:
            position=124.0;
            break;
        case 30:
            position=125.0;
            break;
        case 94:
            position=126.0;
            break;
        case 95:
            position=127.0;
            break;
    }
    // Transformation de la donner envoyer par l'encodeur en degrés : 0-90°//
    x= fabs( ((position)*360.0*ratio)/127.0);
    //---------------------------------------------------------------------//
    return (x);
}
//-------------------------------------------------//


